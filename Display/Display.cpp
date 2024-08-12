#include "Display.h"
#include <iostream>

Display::Display(int width, int height)
        : width(width), height(height), window(sf::VideoMode(width, height), "Pixel Matrix") {
    if (!texture.create(width, height)) {
        std::cerr << "Failed to create texture!" << "\n";
    }
    sprite.setTexture(texture);
}

std::vector<sf::Uint8> Display::convertRGB565ToRGBA(const uint16_t pixel) {
    std::vector<sf::Uint8> pixelsRGBA(4);
    // Extract RGB components from RGB565
    sf::Uint8 r = (pixel >> 11) & 0x1F;  // 5 bits for red
    sf::Uint8 g = (pixel >> 5) & 0x3F;   // 6 bits for green
    sf::Uint8 b = pixel & 0x1F;          // 5 bits for blue

    // Scale them up to 8 bits (from 5/6 bits)
    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);

    // Store in RGBA format
    pixelsRGBA[0] = r;
    pixelsRGBA[1] = g;
    pixelsRGBA[2] = b;
    pixelsRGBA[3] = 255; // Alpha channel


    return pixelsRGBA;
}


void Display::render() {
    window.clear();
    window.draw(sprite);
    window.display();
}

void Display::setPixel(int x, int y, uint16_t color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        std::cerr << x << " " << y << "\n";
        std::cerr << "Error: Pixel coordinates out of bounds!" << "\n";
        return;
    }

    // Convert RGB565 to RGBA
    std::vector<sf::Uint8> pixelRGBA = convertRGB565ToRGBA(color);

    // Update the texture with the converted pixel data
    texture.update(pixelRGBA.data(), 1, 1, x, y);
}
