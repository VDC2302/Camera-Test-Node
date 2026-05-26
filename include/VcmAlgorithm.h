#pragma once

namespace Automation {
	struct VcmResult {
		bool isPass;
		double sensitivity;
	};

	class VcmAlgorithm {
	public:
		static VcmResult verifyActuator(double strokeUm, double currentMa);
	};
}