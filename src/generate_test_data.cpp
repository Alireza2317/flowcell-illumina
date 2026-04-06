#include "data-generation/datagen.hpp"

std::filesystem::path ROOT_PATH = PROJECT_ROOT_PATH;

void generate_data() {
	datagen::create_and_save_dataset(ROOT_PATH / "data" / "test_data", 100, 20, false);
}

int main() {
	generate_data();
	return 0;
}