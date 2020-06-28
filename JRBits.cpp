#include "Physics/physics.h"
#include "drawable.h"
#include "Utils/utils.h"
#include "Utils/logger.hpp"
Logger mlog;

bool Logger::CONFIG_READ = false;
bool Logger::ENABLE_LOGGING = false;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
using namespace std;

// Frames Per Second
const int FPS = 60;
// Milliseconds Per Frame
const int MPF = 1000 / FPS;
const int kMillisecondsPerFrame = MPF;
const double SPF = 1. * MPF / 1000;
const double kSecondsPerFrame = SPF;

int main() {
    mlog << "Logging works!" << std::endl;

    // CREATING SYSTEM
    const int kScreenWidth = 800, kScreenHeight = 600;
    const vector2d kScreenVector2d{ kScreenWidth, kScreenHeight };
    sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight), "SFML works!");
    auto all_textures = LoadTextures("../../Images/");
    auto all_sprites = MakeSpritersFromTextures(all_textures);

    // SETUP GAME
    // create world
    GameWorld world(kScreenVector2d, kScreenVector2d);
    world.SetBackground(all_sprites["background_" + std::to_string(kScreenWidth) + "x" + std::to_string(kScreenHeight)]);
    const double_i G = 100;
    world.SetDefaulrForce(V2dE(1) * G);

    // create objects
    auto id1 = world.AddObject(new Sprite(DynObject({ 80, 80 }, { 100, 200 }), all_sprites["sprite_80x80"])).AddSpeed({ 50, -200 }).id;
    
    sf::Clock clock;
    while (window.isOpen()) {
        clock.restart();
        // ------ EVENT SECTION ------
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        // ------ ITERATION ------
        world.Tick(kSecondsPerFrame);

        // ------ DRAWING SECTION ------
        window.clear();
        world.Draw(window);

        // ------ FPS SECTION ------
        if (clock.getElapsedTime().asMilliseconds() < MPF) {
            sf::sleep(sf::milliseconds(MPF) - clock.getElapsedTime());
        }
        window.display();
    }

    return 0;
}