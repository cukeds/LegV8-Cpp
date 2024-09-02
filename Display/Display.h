//
// Created by Juan on 8/11/2024.
//

#ifndef ARM_DISPLAY_H
#define ARM_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <SFML/Graphics.hpp>
#include <vector>

struct Pixel {
    int x;
    int y;
    std::vector<sf::Uint8> pixel;
};

class Display {
public:
    Display(int width, int height);
    void render();
    void setPixel(int x, int y, uint16_t color);

    sf::RenderWindow window;
    int width;
    int height;
    void setPixels(const std::vector<sf::Uint8>& _pixels);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::Uint8> convertRGB565ToRGBA(uint16_t pixel);
    std::vector<sf::Uint8> convertRGB565ToRGBA(const std::vector<sf::Uint16>& _pixels);
    std::vector<sf::Uint16> pixels;
};

#endif //ARM_DISPLAY_H
