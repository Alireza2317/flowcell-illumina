#include "io/frame_loader.hpp"
#include <algorithm>
#include <filesystem>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

namespace io {
	FrameLoader::FrameLoader(fs::path data_dir) : m_main_path(data_dir) {
		refresh();
	}

	void FrameLoader::refresh() {
		m_frame_paths.clear();

		for (const auto& entry : fs::directory_iterator(m_main_path)) {
			if (entry.path().extension() == ".png") {
				m_frame_paths.push_back(entry.path());
			}
		}
		std::ranges::sort(m_frame_paths);
	}

	[[nodiscard]] cv::Mat FrameLoader::get_frame(size_t index) const {
		if (index >= m_frame_paths.size()) {
			return {};
		}

		return cv::imread(m_frame_paths[index], cv::IMREAD_COLOR);
	}

	[[nodiscard]] size_t FrameLoader::count() const {
		return m_frame_paths.size();
	}

} // namespace io