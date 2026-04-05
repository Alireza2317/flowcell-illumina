#pragma once
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace io {
	namespace fs = std::filesystem;

	/// @brief A class for loading image frames from a specified directory.
	class FrameLoader {
	  private:
		fs::path m_main_path;
		std::vector<fs::path> m_frame_paths;

	  public:
		/// @brief Constructs a FrameLoader object.
		/// @param data_dir The directory containing the image frames.
		explicit FrameLoader(fs::path data_dir);

		/// @brief Refreshes the list of frame paths in the data directory.
		void refresh();

		/// @brief Retrieves a frame (image) at the specified index.
		/// @param index The index of the frame to retrieve.
		/// @return A cv::Mat representing the image frame.
		[[nodiscard]] cv::Mat get_frame(size_t index) const;

		/// @brief Returns the total number of frames loaded.
		/// @return The count of available frames.
		[[nodiscard]] size_t count() const;
	};
} // namespace io