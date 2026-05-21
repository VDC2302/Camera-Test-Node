#include <iostream>
#include <iomanip>
#include <LogParser.h>

int main() {
	std::vector<CameraTestData> results = Automation::LogParser::parseCsv("test_log.csv");

	if (results.empty()) {
		std::cerr << "No records found to analyze" << std::endl;
		return 1;
	}

	size_t totalTested = results.size();
	size_t passedCount = 0;
	size_t failedCount = 0;

	size_t vcmFailures = 0;
	size_t currentFailures = 0;

	for (const auto& record : results) {
		if (record.status == "PASS") {
			passedCount++;
		}
		else if (record.status == "FAIL") {
			failedCount++;

			// Example: VCM Stroke must be > 15.0 um
			if (record.vcmStroke <= 15.0) {
				vcmFailures++;
			}
			// Example: Leakage Current must be < 150.0 mA
			if (record.currentMa >= 150.0) {
				currentFailures++;
			}
		}
	}

	double yieldRate = (static_cast<double>(passedCount) / totalTested) * 100.0;

	std::cout << "====================================" << std::endl;
	std::cout << "     CAMERA PRODUCTION ANALYSIS     " << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "Total Modules Tested : " << totalTested << std::endl;
	std::cout << "Passed Modules       : " << passedCount << std::endl;
	std::cout << "Failed Modules       : " << failedCount << std::endl;

	std::cout << std::fixed << std::setprecision(2);
	std::cout << "First Pass Yield (FPY): " << yieldRate << "%\n";
	std::cout << "------------------------------------" << std::endl;
	std::cout << "FAILURE INVESTIGATION ROOT CAUSES:" << std::endl;
	std::cout << " - VCM Actuator Stroke Defects: " << vcmFailures << std::endl;
	std::cout << " - Electrical Current Leakage : " << currentFailures << std::endl;
	std::cout << "====================================" << std::endl;

	return 0;
}