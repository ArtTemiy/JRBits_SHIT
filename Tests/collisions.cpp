#include "../Physics/physics.h"
#include "../drawable.h"
#include "../Utils/utils.h"
#include "../Utils/logger.hpp"
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
    auto small_box_sprite = all_sprites["big_texture_1000x1000"];
    auto top_botom_box_sprite = all_sprites["big_texture_1000x1000"];
    auto sides_box_sprite = all_sprites["big_texture_1000x1000"];
    SetSpriteSize(small_box_sprite, { 10, 10 });
    SetSpriteSize(top_botom_box_sprite, { kScreenWidth, 10 });
    SetSpriteSize(sides_box_sprite, { 10, kScreenHeight - 20 });

    // top
    //world.AddObject(new Sprite(DynObject(Object({ 800, 10 }, { 0, 0 }), double_i(1, true), 1), top_botom_box_sprite), true);
    // bottom
    world.AddObject(new Sprite(DynObject(Object({ 800, 10 }, { 0, 600 - 10 }), double_i(1, true), 0), top_botom_box_sprite), true);

    // left
    //world.AddObject(new Sprite(DynObject({ 10, 600 - 20 }, { 0, 10 }, double_i(1, true)), sides_box_sprite), true);
    // right
    //world.AddObject(new Sprite(DynObject({ 10, 600 - 20 }, { 800 - 10, 10 }, double_i(1, true)), sides_box_sprite), true);
    class ObjectCreator {
        const sf::Time time_;
        sf::Clock clock_;
    public:
        ObjectCreator(int milliseconds) : time_(sf::milliseconds(milliseconds)) {
            clock_.restart();
        }
        void Try(GameWorld& world, const sf::Sprite& small_box_sprite) {
            if (clock_.getElapsedTime() > time_) {
                world.AddObject(new Sprite(DynObject({ 10, 10 }, { 15 + (rand() % (800 / 20 - 2)) * 20, 20 }, 1, 0.5), small_box_sprite)).AddSpeed({ (1 - 2 * (rand() % 2)) * (rand() % 200 + 100), 100 + rand() % 200 });
                clock_.restart();
            }
        }
    } obj_creator(100);


    sf::Clock clock;
    while (window.isOpen()) {
        clock.restart();
        // ------ EVENT SECTION ------
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        obj_creator.Try(world, small_box_sprite);

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