#include "utils.h"
#include <fstream>

const std::string kListOfFilesFileName = "ListOfFiles.txt";

void SetSpriteSize(sf::Sprite& sprite, const vector2d& size) {
	sprite.setScale(
		size[0].to_double() / sprite.getLocalBounds().width,
		size[1].to_double() / sprite.getLocalBounds().height
	);
}

/*
FileName::FileName(std::string path) {
	int i = path.size() - 1;
	while (i >= 0 && path[i] != '.' && path[i] != '\\' && path[i] != '/') {
		--i;	// path[--i];
	}
	if (i < 0) {
		name = path;
		type = "";
	}
	else {
		name = path.substr(0, i);
		type = path.substr(i + 1, path.size() - i);
	}
}
*/

std::vector<FileName> ListOfFiles(std::string path) {
	if (path[path.size() - 1] != '/' && path[path.size() - 1] != '\\') {
		path += '/';
	}
	std::vector<FileName> files;
	std::ifstream list_of_files_file(path + kListOfFilesFileName);
	if (!list_of_files_file.is_open()) {
		throw std::runtime_error(path + kListOfFilesFileName + " file wasn't open");
	}

	int line_number = 1;
	while (!list_of_files_file.eof()) {
		std::string key_name, path;
		list_of_files_file >> key_name >> path;
		if (key_name == "" || path == "") {
			throw std::logic_error("key or path to resource is empty, check \'" + path + kListOfFilesFileName + "\' file " + std::to_string(line_number) + "line");
		}
		files.push_back({ key_name, path });

		++line_number;
	}

	return files;
}

std::unordered_map<std::string, sf::Texture> LoadTextures(const std::string& path) {
	std::unordered_map<std::string, sf::Texture> textures;
	for (auto& file : ListOfFiles(path)) {
		textures[file.key] = sf::Texture();
		if (!textures[file.key].loadFromFile(path + file.path)) {
			throw std::runtime_error("Wasn't able to load texture: " + path + file.path);
		}
	}
	return textures;
}

std::unordered_map<std::string, sf::Sprite> MakeSpritersFromTextures(const std::unordered_map<std::string, sf::Texture>& textures) {
	std::unordered_map<std::string, sf::Sprite> sprites;
	for (auto& texture : textures) {
		sprites[texture.first] = sf::Sprite();
		sprites[texture.first].setTexture(texture.second);
	}
	return sprites;
}
