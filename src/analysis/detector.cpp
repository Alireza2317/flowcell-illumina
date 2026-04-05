#include "analysis/detector.hpp"
#include <opencv2/core/types.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

namespace analysis {
	namespace detect {
		cv::SimpleBlobDetector::Params get_params() {
			cv::SimpleBlobDetector::Params params;

			// Filter by Area
			params.filterByArea = true;
			params.minArea = 5.0f; // Approx area of a circle
			params.maxArea = 100.0f;

			// Filter by Circularity
			params.filterByCircularity = true;
			params.minCircularity = 0.8f;

			// Ensure we find bright blobs on dark background
			// params.filterByColor = true;
			// params.blobColor = 255;

			return params;
		}

		BlobDetector::BlobDetector() {
			m_detector = cv::SimpleBlobDetector::create(get_params());
		}

		std::vector<DetectedBlob> BlobDetector::detect(const cv::Mat& processed_frame) const {
			std::vector<cv::KeyPoint> keypoints;

			m_detector->detect(processed_frame, keypoints);

			std::vector<DetectedBlob> detections;
			detections.reserve(keypoints.size());

			for (const auto& kp : keypoints) {
				detections.push_back({kp.pt, kp.size});
			}

			return detections;
		}
	} // namespace detect
} // namespace analysis