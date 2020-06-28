#pragma once

#include "Physics/physics.h"
#include <SFML/Graphics.hpp>

// converts vector2d to sf::Vector2f
sf::Vector2f ToSFv2f(const vector2d& vector);

class Camera : public Object {
public:
	Camera(const vector2d& size) : Object(size) {}
};

class Drawable {
protected:
	sf::Sprite sprite_;

public:
	Drawable(const sf::Sprite& sprite = sf::Sprite()) : sprite_(sprite) {}
	Drawable(const Drawable& other) = default;
	virtual ~Drawable() = default;

	virtual void Draw(sf::RenderWindow& window, const Camera& camera) = 0;
	sf::Sprite& GetSprite();
	void SetSprite(sf::Sprite sprite);
};

class Sprite : public DynObject, public Drawable {
public:
	Sprite(const DynObject& obj, sf::Sprite sprite = sf::Sprite()) : DynObject(obj), Drawable(sprite) {}
	Sprite(const Sprite& other) = default;
	virtual void Draw(sf::RenderWindow & window, const Camera & camera) override;
};

typedef std::shared_ptr<Sprite> SpriteP;

class GameWorld : public World {
	Camera camera_;
	Sprite background_;

public:
	GameWorld(const vector2d& world_size, const vector2d& camera_size) : World(world_size), camera_(camera_size), background_(world_size) {}
	GameWorld& SetBackground(const sf::Sprite& background);
	void Draw(sf::RenderWindow& window);
};