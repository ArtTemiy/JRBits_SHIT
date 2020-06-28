# pragma once
#include <SFML/Graphics.hpp>
#include "../Physics/vectorNd.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void SetSpriteSize(sf::Sprite& sprite, const vector2d& size);

struct FileName {
	//FileName(std::string path);
	std::string key;
	std::string path;
};

std::vector<FileName> ListOfFiles(std::string path);

std::unordered_map<std::string, sf::Texture> LoadTextures(const std::string& path);
std::unordered_map<std::string, sf::Sprite> MakeSpritersFromTextures(const std::unordered_map<std::string, sf::Texture>& textures);