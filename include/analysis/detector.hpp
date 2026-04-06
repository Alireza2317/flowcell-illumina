#pragma once
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

namespace analysis::detect {
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
} // namespace analysis::detect
