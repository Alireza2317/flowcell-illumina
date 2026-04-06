#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace analysis::decode {
	class SequenceDecoder {
	  public:
		/// @brief Decodes a single BGR pixel into a base character.
		/// @param pixel The input pixel to be decoded.
		/// @return A character representing the base: 'A', 'T', 'C' or 'G'
		[[nodiscard]] static char pixel2char(const cv::Vec3b& pixel);

		/// @brief Extracts sequences for all detected points across a frame sequence.
		/// @param coordinates A vector of KeyPoint objects, the actual blob detections.
		/// @param frames A vector of frame objects, in the order of the sequence.
		/// @return A vector containing the sequences(as string) for all blobs.
		[[nodiscard]] std::vector<std::string> decode_all(
			const std::vector<cv::KeyPoint>& coordinates, const std::vector<cv::Mat>& frames) const;
	};
} // namespace analysis::decode