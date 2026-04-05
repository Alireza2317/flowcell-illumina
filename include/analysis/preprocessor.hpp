#pragma once
#include <cstdint>
#include <opencv2/opencv.hpp>

namespace analysis {
	namespace prep {
		struct Config {
			uint8_t blur_ksize = 3;	  // Gaussian blur kernel size
			float sigma = 1.0;		  // Gaussian sigma
			uint8_t morph_ksize = 15; // Size for background estimation
		};

		class Preprocessor {
		  public:
			explicit Preprocessor(Config cfg);

			[[nodiscard]] cv::Mat process(const cv::Mat& input) const;

		  private:
			Config m_cfg;
		};
	} // namespace prep
} // namespace analysis