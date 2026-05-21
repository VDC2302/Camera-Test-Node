#include <LogParser.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace Automation {
	std::vector<CameraTestData> LogParser::parseCsv(const std::string& filepath) {
		std::vector<CameraTestData> records;
		std::ifstream file(filepath);

		if (!file.is_open()) {
			std::cerr << "[SYSTEM ERROR] Could not open log file." << filepath << std::endl;
			return records;
		}

		std::string line;

		//Skip the header row (1st row)
		if (!std::getline(file, line)) {
			std::cerr << "[SYSTEM ERROR] File is empty or corrupt." << std::endl;
			return records;
		}

		while (std::getline(file, line)) {
			if (line.empty()) continue;

			std::stringstream ss(line);
			std::string token;

			// Temporary vector to check parsing
			std::vector<std::string> tokens;

			while (std::getline(ss, token, ',')) {
				tokens.push_back(token);
			}

			//Data Integrity check
			if (tokens.size() != 4) {
				std::cerr << "[TEST SYSTEM WARNING] Malformed log entry dropped: " << line << std::endl;
				continue; //Skip bad row
			}

			CameraTestData data;
			data.moduleId = tokens[0];
			data.status = tokens[3];

			//Exception Handling
			try {
				data.vcmStroke = std::stod(tokens[1]);
				data.currentMa = std::stod(tokens[2]);

				records.push_back(data);
			}
			catch(const std::invalid_argument& e){
				std::cerr << "[TEST SYSTEM WARNING] Corrupt number format in row: " << line << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "[TEST SYSTEM WARNING] Number overflow in row: " << line << std::endl;
			}

			//std::getline(ss, data.moduleId, ',');

			//std::getline(ss, token, ',');
			//data.vcmStroke = std::stod(token);

			//std::getline(ss, token, ',');
			//data.currentMa = std::stod(token);

			//std::getline(ss, data.status, ',');

			//records.push_back(data);
		}

		return records;
	}
}