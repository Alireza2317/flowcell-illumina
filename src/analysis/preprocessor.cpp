#include "analysis/preprocessor.hpp"
#include <opencv2/opencv.hpp>

namespace analysis {
	namespace prep {
		Preprocessor::Preprocessor(Config cfg) : m_cfg(cfg) {
		}

		[[nodiscard]] cv::Mat Preprocessor::process(const cv::Mat& input) const {
			cv::Mat gray;
			cv::Mat blurred;
			cv::Mat bg_subtracted;

			// Convert to grayscale
			if (input.channels() == 3) {
				std::vector<cv::Mat> channels;
				cv::split(input, channels);
				cv::max(channels[0], channels[1], gray);
				cv::max(gray, channels[2], gray);
			} else {
				gray = input.clone();
			}

			// Denoise
			cv::GaussianBlur(
				gray, blurred, cv::Size(m_cfg.blur_ksize, m_cfg.blur_ksize), m_cfg.sigma);

			// Subtract background (morphological top-hat)
			// Removing low-frequency noise, and keeping blobs
			cv::Mat kernel = cv::getStructuringElement(
				cv::MORPH_ELLIPSE, cv::Size(m_cfg.morph_ksize, m_cfg.morph_ksize));

			cv::morphologyEx(blurred, bg_subtracted, cv::MORPH_TOPHAT, kernel);

			return bg_subtracted;
		}
	} // namespace prep
} // namespace analysis