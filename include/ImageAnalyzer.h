#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

namespace Automation {
	struct ImageBuffer {
		size_t width;
		size_t height;
		std::vector<uint8_t> data; //1D memory block
	};

	class ImageAnalyzer {
	public:
		static size_t countDeadPixels(const ImageBuffer& image);

		static uint8_t getPixelAt(const ImageBuffer& image, size_t x, size_t y);
	};
}