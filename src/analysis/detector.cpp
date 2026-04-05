#include "analysis/detector.hpp"
#include <cstddef>
#include <opencv2/core/types.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace analysis {
	namespace detect {
		cv::SimpleBlobDetector::Params get_params() {
			cv::SimpleBlobDetector::Params params;

			// Threshold
			params.minThreshold = 5.0f;
			params.maxThreshold = 255.0f;
			params.thresholdStep = 5.0f;

			// Filter by Area
			params.filterByArea = true;
			params.minArea = 30.0f; // Approx area of a circle
			params.maxArea = 60.0f;

			// Filter by Circularity
			params.filterByCircularity = true;
			params.minCircularity = 0.05f;

			// Ensure we find bright blobs on dark background
			params.filterByColor = true;
			params.blobColor = 255;

			params.minDistBetweenBlobs = 0.01f;

			return params;
		}

		BlobDetector::BlobDetector() {
			m_detector = cv::SimpleBlobDetector::create(get_params());
		}

		// std::vector<cv::KeyPoint> BlobDetector::detect(const cv::Mat& processed_frame) const {
		// 	std::vector<cv::KeyPoint> detections;
		// 	m_detector->detect(processed_frame, detections);

		// 	return detections;
		// }

		/// AI-GENERATED --- Will be modified and improved later
		std::vector<cv::KeyPoint> BlobDetector::detect(const cv::Mat& processed_frame) const {
			// 1. Binary Mask (Threshold high enough to remove background noise)
			cv::Mat mask;
			cv::threshold(processed_frame, mask, 60, 255, cv::THRESH_BINARY);

			// 2. Distance Transform
			// This turns each blob into a "mountain" where the peak is the center
			cv::Mat dist;
			cv::distanceTransform(mask, dist, cv::DIST_L2, 3);
			cv::normalize(dist, dist, 0, 1.0, cv::NORM_MINMAX); // Normalize for easier peaking

			// 3. Find peaks on the DISTANCE map, not the raw pixels
			cv::Mat local_max;
			cv::dilate(dist, local_max, cv::getStructuringElement(cv::MORPH_RECT, {5, 5}));

			cv::Mat peak_mask;
			cv::compare(dist, local_max, peak_mask, cv::CMP_EQ);
			// Only keep peaks that are actually inside a blob
			peak_mask &= (dist > 0.4); // 0.4 is a "depth" threshold (40% of max radius)

			// 4. Centroids of the Distance Peaks
			cv::Mat labels, stats, centroids;
			int num_labels = cv::connectedComponentsWithStats(peak_mask, labels, stats, centroids);

			std::vector<cv::KeyPoint> keypoints;
			for (int i = 1; i < num_labels; i++) {
				// Geometry filter: If the peak is too small, it's a noise fragment
				if (stats.at<int>(i, cv::CC_STAT_AREA) < 1)
					continue;

				double x = centroids.at<double>(i, 0);
				double y = centroids.at<double>(i, 1);
				keypoints.emplace_back(cv::Point2f(x, y), 2.0f);
			}

			return keypoints;
		}

		void draw_detections(
			const cv::Mat& img, cv::Mat& out_img, const std::vector<cv::KeyPoint>& detections) {
			if (img.channels() == 1) {
				cv::cvtColor(img, out_img, cv::COLOR_GRAY2BGR);
			} else {
				out_img = img.clone();
			}

			for (size_t i = 0; i < detections.size(); i++) {
				auto pt = detections[i].pt;
				cv::circle(out_img, pt, 5, {0, 0, 220}, 1, cv::LINE_AA);

				cv::putText(
					out_img,
					std::to_string(i),
					pt + cv::Point2f(4, -4),
					cv::FONT_HERSHEY_SIMPLEX,
					0.3,
					{0, 250, 0},
					1,
					cv::LINE_AA);
			}
		}
	} // namespace detect
} // namespace analysis