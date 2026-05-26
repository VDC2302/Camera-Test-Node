#include <VcmAlgorithm.h>

namespace Automation {
	VcmResult VcmAlgorithm::verifyActuator(double strokeUm, double currentMa) {
		VcmResult result;

		//safeguard: prevent division by zero
		if (currentMa <= 0.001) {
			result.isPass = false;
			result.sensitivity = 0;
			return result;
		}

		result.sensitivity = strokeUm / currentMa;

		const double LSL = 0.32;
		const double USL = 0.38;

		result.isPass = (result.sensitivity >= LSL && result.sensitivity <= USL);

		return result;
	}
}