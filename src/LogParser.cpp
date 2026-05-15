#include <LogParser.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Automation {
	std::vector<CameraTestData> LogParser::parseCsv(const std::string& filepath) {
		std::vector<CameraTestData> records;
		std::ifstream file(filepath);

		if (!file.is_open()) {
			std::cerr << "Error: Could not open " << filepath << std::endl;
			return records;
		}

		std::string line;

		if (!std::getline(file, line)) return records;

		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string token;
			CameraTestData data;

			std::getline(ss, data.moduleId, ',');

			std::getline(ss, token, ',');
			data.vcmStroke = std::stod(token);

			std::getline(ss, token, ',');
			data.currentMa = std::stod(token);

			std::getline(ss, data.status, ',');

			records.push_back(data);
		}

		return records;
	}
}