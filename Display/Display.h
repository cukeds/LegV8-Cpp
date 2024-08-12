//
// Created by Juan on 8/11/2024.
//

#ifndef ARM_DISPLAY_H
#define ARM_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <SFML/Graphics.hpp>
#include <vector>

class Display {
public:
    Display(int width, int height);
    void render();
    void setPixel(int x, int y, uint16_t color);

    sf::RenderWindow window;
    int width;
    int height;
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::Uint8> convertRGB565ToRGBA(uint16_t pixel);
};

#endif //ARM_DISPLAY_H
