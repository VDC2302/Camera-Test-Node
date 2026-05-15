#pragma once

#include <string>
#include <vector>

struct CameraTestData {
	std::string moduleId;
	double vcmStroke;
	double currentMa;
	std::string status;
};

namespace Automation {
	class LogParser {
	public:
		static std::vector<CameraTestData> parseCsv(const std::string& filepath);
	};
}