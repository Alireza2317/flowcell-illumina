#pragma once
#include <opencv2/opencv.hpp>

struct Cluster {
	cv::Point2f pos;
	std::string sequence;

	std::string to_string() const {
		return std::format("({: 6.1f},{: 6.1f}) {}", pos.x, pos.y, sequence);
	}
};
