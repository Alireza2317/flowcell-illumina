#include "analysis/decoder.hpp"
#include "analysis/detector.hpp"
#include "analysis/preprocessor.hpp"
#include "io/frame_loader.hpp"
#include <filesystem>
#include <opencv2/opencv.hpp>

const std::filesystem::path ROOT_PATH = PROJECT_ROOT_PATH;

void test(const std::filesystem::path& data_dir) {
	io::FrameLoader fl(data_dir);
	const auto raw_frames = fl.get_frames();

	auto preper = analysis::prep::Preprocessor();

	const cv::Mat preped_frame = preper.process(raw_frames.at(0));

	auto detector = analysis::detect::BlobDetector();

	auto detections = detector.detect(preped_frame);

	auto decoder = analysis::decode::SequenceDecoder();

	auto results = decoder.decode_all(detections, raw_frames);

	for (const auto& r : results) {
		std::cout << r << '\n';
	}
}

int main() {
	test(ROOT_PATH / "data" / "dataset_10cl_7b_20260406_0151");
	return 0;
}
