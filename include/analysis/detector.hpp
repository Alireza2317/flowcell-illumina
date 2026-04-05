#pragma once
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

namespace analysis {
	namespace detect {
		/// @brief A class for detecting blobs in an image using OpenCV's SimpleBlobDetector.
		class BlobDetector {
		  private:
			cv::Ptr<cv::SimpleBlobDetector> m_detector;

		  public:
			/// @brief Constructs a BlobDetector object and initializes the SimpleBlobDetector.
			BlobDetector();
			/// @brief Detects blobs in a given processed frame.
			/// @param processed_frame The input image frame, typically pre-processed.
			/// grayscale, thresholded, ...
			/// @return A vector of KeyPoint objects, each containing the center and size of a
			/// detected blob.
			[[nodiscard]] std::vector<cv::KeyPoint> detect(const cv::Mat& processed_frame) const;
		};

		void draw_detections(
			const cv::Mat& img, cv::Mat& out_img, const std::vector<cv::KeyPoint>& detections);
	} // namespace detect

	namespace decode {
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
				const std::vector<cv::KeyPoint>& coordinates,
				const std::vector<cv::Mat>& frames) const;
		};
	} // namespace decode
} // namespace analysis
