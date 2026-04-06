#include "data-generation/datagen.hpp"
#include "common/types.hpp"
#include <array>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace datagen {
	cv::Scalar base_to_BGR(const char base) {
		switch (base) {
			case 'A':
				return {0, 255, 255}; // Yellow
			case 'C':
				return {0, 0, 255}; // Red
			case 'T':
				return {0, 255, 0}; // Green
			case 'G':
				return {250, 0, 0}; // Blue
			default:
				using namespace std::string_literals;
				throw std::invalid_argument("Base "s + base + " is unknown!");
		}
	}

	cv::Mat generate_frame(const std::vector<Cluster>& clusters, size_t cycle) {
		// Create dark background
		cv::Mat frame = cv::Mat::zeros(FRAME_SIZE, FRAME_SIZE, CV_8UC3);

		for (const auto& cluster : clusters) {
			char base = cluster.sequence[cycle];

			cv::Scalar color = base_to_BGR(base);

			cv::circle(frame, cluster.pos, 4, color, -1, cv::LINE_AA);
		}

		cv::Mat noise(frame.size(), frame.type());
		cv::randn(noise, 0, 15);

		return frame + noise;
	}

	char generate_random_base() {
		static constexpr std::array<char, 4> BASES{'A', 'C', 'T', 'G'};
		return BASES[base_dist(gen)];
	}

	std::string generate_random_sequence(const size_t length) {
		std::string sequence;
		sequence.reserve(length);

		for (size_t i = 0; i < length; i++) {
			sequence += generate_random_base();
		}

		return sequence;
	}

	cv::Point2f generate_random_position() {
		return {pos_dist(gen), pos_dist(gen)};
	}

	void sort_clusters(std::vector<Cluster>& clusters) {
		std::ranges::sort(clusters, [](const Cluster& a, const Cluster& b) {
			return std::tie(a.pos.y, a.pos.x) < std::tie(b.pos.y, b.pos.x);
		});
	}

	std::vector<Cluster> create_dataset(const size_t num_clusters, const size_t num_cycles) {
		std::vector<Cluster> clusters;
		clusters.reserve(num_clusters);

		// Generating the data
		for (size_t cluster_i = 0; cluster_i < num_clusters; cluster_i++) {
			clusters.emplace_back(generate_random_position(), generate_random_sequence(num_cycles));
		}

		return clusters;
	}

	std::string get_timestamp() {
		using namespace std::chrono;

		const auto now = zoned_time(current_zone(), system_clock::now());
		return std::format("{:%Y%m%d_%H%M}", now);
	}

	void create_and_save_dataset(
		std::filesystem::path output_dir,
		const size_t num_clusters,
		const size_t num_cycles,
		bool create_new_dir) {
		std::string unique_name = "dataset_" + std::to_string(num_clusters) + "cl_" +
								  std::to_string(num_cycles) + "b_" + get_timestamp();
		if (create_new_dir) {
			output_dir = output_dir / unique_name;
		}

		std::filesystem::create_directories(output_dir);

		auto clusters = create_dataset(num_clusters, num_cycles);

		// Saving the frames
		for (size_t cycle = 0; cycle < num_cycles; cycle++) {
			cv::Mat frame = generate_frame(clusters, cycle);

			cv::imwrite(output_dir / ("frame_" + std::to_string(cycle + 1) + ".png"), frame);
		}

		// Saving as text file
		std::ofstream file(output_dir / (unique_name + ".txt"));

		// Sorting the clusters by position
		sort_clusters(clusters);

		for (const auto& cluster : clusters) {
			file << cluster.to_string() << "\n";
		}
		file.close();
	}
} // namespace datagen