#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

#include <LogParser.h>
#include <VcmAlgorithm.h>
#include <ImageAnalyzer.h>

Automation::ImageBuffer captureMockImage(const std::string& moduleId) {
	Automation::ImageBuffer img;
	img.width = 1920;
	img.height = 1080;

	//Allocate ~2MB of contigous memory and fill it with 255 (Perfect White)
	img.data.assign(img.width * img.height, 255);

	// Simulate a defective camera sensor for a specific module
	if (moduleId == "MOD_025") {
		img.data[100500] = 0;
		img.data[100501] = 0;
		img.data[100502] = 0;
		img.data[100503] = 0;
		img.data[100504] = 0;
	}
	return img;
}

int main() {
	std::vector<CameraTestData> logs = Automation::LogParser::parseCsv("test_log.csv");

	if (logs.empty()) {
		std::cerr << "[SYSTEM ERROR] Failed to load test sequence" << std::endl;
		return 1;
	}

	std::string outputFilename = "Results.csv";
	std::ofstream reportFile(outputFilename);

	//Check if write access is granted (File is currently opened)
	if (!reportFile.is_open()) {
		std::cerr << "[SYSTEM ERROR] Could not create output file: " << outputFilename << "\n";
		return 1;
	}

	// Write the CSV Header Row
	reportFile << "ModuleID,VCM_Sensitivity_um_mA,Dead_Pixels,Final_Status\n";

	size_t totalTested = logs.size();
	size_t passedCount = 0;
	size_t failedCount = 0;

	size_t vcmDefects = 0;
	size_t apsImageDefects = 0;

	for (const auto& record : logs) {

		bool isModulePass = true;

		// Run the customer algorithm
		Automation::VcmResult vcmEval = Automation::VcmAlgorithm::verifyActuator(record.vcmStroke, record.currentMa);

		if (!vcmEval.isPass) {
			isModulePass = false;
			vcmDefects++;
		}

		//Run simulated camera
		Automation::ImageBuffer rawImage = captureMockImage(record.moduleId);

		//Analyze dead pixels
		size_t deadPixels = Automation::ImageAnalyzer::countDeadPixels(rawImage);

		if (deadPixels > 3) {
			isModulePass = false;

			//console log for defected modules
			//std::cout << "[DEFECT] " << record.moduleId << " failed APS Calibration. Dead pixels: " << deadPixels << "\n";
		}

		reportFile << record.moduleId << "," << std::fixed << std::setprecision(3) << vcmEval.sensitivity << "," << deadPixels << "," << (isModulePass ? "PASS" : "FAIL") << std::endl;

		//logging

		if (isModulePass && record.status != "FAIL") {
			passedCount++;
		}
		else {
			failedCount++;

			// If it failed the sensitivity check, record the root cause
			//if (!vcmEval.isPass) {
			//	vcmDefects++;
			//	std::cout << "[DEFECT LOG] Module " << record.moduleId
			//		<< " failed VCM Linearity. Sensitivity: "
			//		<< std::fixed << std::setprecision(3) << vcmEval.sensitivity
			//		<< " um/mA\n";
			//}
		}
	}

	double yieldRate = (static_cast<double>(passedCount) / totalTested) * 100.0;

	//std::cout << "\n====================================\n";
	//std::cout << "      END OF SHIFT YIELD REPORT     \n";
	//std::cout << "====================================\n";
	//std::cout << "Total Modules Processed : " << totalTested << "\n";
	//std::cout << "Passed (BIN 1)          : " << passedCount << "\n";
	//std::cout << "Failed (BIN 2+)         : " << failedCount << "\n";
	//std::cout << "------------------------------------\n";
	//std::cout << "First Pass Yield (FPY)  : " << std::fixed << std::setprecision(2) << yieldRate << "%\n";
	//std::cout << "------------------------------------\n";
	//std::cout << "PARETO OF DEFECTS:\n";
	//std::cout << " - VCM Actuator Failures : " << vcmDefects << "\n";
	//std::cout << " - APS Sensor Blemishes  : " << apsImageDefects << "\n";
	//std::cout << "====================================\n";
	std::cout << "[SYSTEM] Test Complete. Yield: " << std::fixed << std::setprecision(2) << yieldRate << "%\n";
	std::cout << "[SYSTEM] Results successfully exported to " << outputFilename << "\n";
	return 0;
}