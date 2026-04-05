#pragma once
#include "common/types.hpp"
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <random>
#include <string>
#include <vector>

namespace datagen {
	inline constexpr uint16_t FRAME_SIZE = 800;

	// Setup random engines
	inline std::random_device rd;
	inline std::mt19937 gen{rd()};

	// Position distribution
	inline std::uniform_real_distribution<float> pos_dist{FRAME_SIZE * 0.05f, FRAME_SIZE * 0.95f};

	// Char/Base distribution
	inline std::uniform_int_distribution<uint8_t> base_dist{0, 3};

	/// @brief Converts a base character (A, C, G, T) to its corresponding BGR color.
	/// @param base The base character.
	/// @return A cv::Scalar representing the BGR color.
	cv::Scalar base_to_BGR(const char base);

	/// @brief Generates a single frame (image) for a given set of clusters and cycle.
	/// @param clusters A vector of Cluster objects to be rendered.
	/// @param cycle The current sequencing cycle.
	/// @return A cv::Mat representing the generated frame.
	cv::Mat generate_frame(const std::vector<Cluster>& clusters, size_t cycle);

	/// @brief Generates a random DNA base (A, C, G, T).
	/// @return A randomly generated base character.
	char generate_random_base();

	/// @brief Generates a random DNA sequence of a specified length.
	/// @param length The desired length of the sequence.
	/// @return A string containing the random DNA sequence.
	std::string generate_random_sequence(const size_t length);

	/// @brief Generates a random 2D position within the frame boundaries.
	/// @return A cv::Point2f representing the random position.
	cv::Point2f generate_random_position();

	/// @brief Sorts a vector of clusters based on its position.
	/// @param clusters A reference to the vector of Cluster objects to be sorted.
	void sort_clusters(std::vector<Cluster>& clusters);

	/// @brief Creates a dataset of clusters for a specified number of clusters and cycles.
	/// @param num_clusters The total number of clusters to create.
	/// @param num_cycles The number of sequencing cycles.
	/// @return A vector of generated Cluster objects.
	std::vector<Cluster> create_dataset(const size_t num_clusters, const size_t num_cycles);

	/// @brief Generates a timestamp string in a specific format.
	/// @return A string representing the current timestamp.
	std::string get_timestamp();

	/// @brief Creates and saves a dataset to the specified output directory.
	/// @param output_dir The directory where the dataset will be saved.
	/// @param num_clusters The number of clusters in the dataset.
	/// @param num_cycles The number of cycles for the dataset.
	void create_and_save_dataset(
		std::filesystem::path output_dir, const size_t num_clusters, const size_t num_cycles);
} // namespace datagen