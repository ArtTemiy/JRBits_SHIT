#include "drawable.h"

sf::Vector2f ToSFv2f(const vector2d& vector) {
	return sf::Vector2f(vector[0].to_double(), vector[1].to_double());
}

sf::Sprite& Drawable::GetSprite() {
	return sprite_;
}
void Drawable::SetSprite(sf::Sprite sprite) {
	sprite_ = sprite;
}

void Sprite::Draw(sf::RenderWindow& window, const Camera& camera) {
	sprite_.setPosition(ToSFv2f(p_ - camera.p()));
	window.draw(sprite_);
}

GameWorld& GameWorld::SetBackground(const sf::Sprite& background) {
	background_.SetSprite(background);
	return *this;
}

void GameWorld::Draw(sf::RenderWindow& window) {
	background_.Draw(window, camera_);
	for (auto& obj : objects_) {
		if (auto poiter = std::dynamic_pointer_cast<Drawable>(obj.second)) {
			poiter->Draw(window, camera_);
		} else {
			std::cerr << "Not drawable object" << std::endl;
		}
	}
}