#include <ImageAnalyzer.h>
#include <iostream>
#include <vector>
#include <stdexcept>

namespace Automation {
	size_t ImageAnalyzer::countDeadPixels(const ImageBuffer& image) {
		size_t deadCount = 0;

		for (uint8_t pixelValue : image.data) {
			if (pixelValue == 0) {
				deadCount++;
			}
		}
		return deadCount;
	}

	uint8_t ImageAnalyzer::getPixelAt(const ImageBuffer& image, size_t x, size_t y) {
		if (x >= image.width || y >= image.height) {
			throw std::out_of_range("Pixel coordinates out of bound");
		}

		size_t index = (y * image.width) + x; //2D to 1D formula: i = (y * width) + x;

		return image.data[index];
	}
}