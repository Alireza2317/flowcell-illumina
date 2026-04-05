#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

namespace analysis {
	namespace detect {
		/// @brief Represents a detected blob with its center coordinates and size.
		struct DetectedBlob {
			cv::Point2f center;
			float size;
		};

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
			/// @return A vector of DetectedBlob objects, each containing the center and size of a
			/// detected blob.
			[[nodiscard]] std::vector<DetectedBlob> detect(const cv::Mat& processed_frame) const;
		};
	} // namespace detect
} // namespace analysis
