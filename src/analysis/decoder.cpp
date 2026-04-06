#include "analysis/decoder.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace analysis::decode {
	char SequenceDecoder::pixel2char(const cv::Vec3b& pixel) {
		const auto [b, g, r] = pixel.val;
		constexpr uint8_t threshold = 120;

		// Blue (G): Blue channel is significantly dominant
		if (b > r and b > g and b > threshold)
			return 'G';

		// Yellow (A): High Red and High Green
		if (r > threshold and g > threshold)
			return 'A';

		// Red (C): Red channel is significantly dominant
		if (r > g and r > b and r > threshold)
			return 'C';

		// Green (T): Green channel is significantly dominant
		if (g > r and g > b and g > threshold)
			return 'T';

		return 'X'; // Error/Noise
	}

	std::vector<std::string> SequenceDecoder::decode_all(
		const std::vector<cv::KeyPoint>& coordinates, const std::vector<cv::Mat>& frames) const {

		std::vector<std::string> sequences(coordinates.size());
		for (auto& s : sequences) {
			s.reserve(frames.size());
		}

		for (const auto& frame : frames) {
			for (size_t i = 0; i < coordinates.size(); i++) {
				const auto pixel = frame.at<cv::Vec3b>(coordinates[i].pt);
				sequences[i] += pixel2char(pixel);
			}
		}
		return sequences;
	}
} // namespace analysis::decode