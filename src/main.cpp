#include <iostream>
#include <LogParser.h>

int main() {
	std::vector<CameraTestData> results = Automation::LogParser::parseCsv("test_log.csv");
	std::cout << "Successfully parsed " << results.size() << " camera test records." << std::endl;

	if (!results.empty()) {
		double totalStroke = 0.0;
		
		for (const auto& record : results) {
			totalStroke += record.vcmStroke;
		}

		double avgStroke = totalStroke / results.size();
		std::cout << "Average VCM Stroke: " << avgStroke << " um" << std::endl;	
	}

	return 0;
}