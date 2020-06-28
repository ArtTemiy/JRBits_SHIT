#include "Utils/utils.h"

int main() {
	std::string path;
	std::cin >> path;
	auto files = ListOfFiles(path);
	for (auto& file : files) {
		std::cout << file.key << " " << file.path << std::endl;
	}
	std::cout << "---" << std::endl;
	std::cin >> path;
}