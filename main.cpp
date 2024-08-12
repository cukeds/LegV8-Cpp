#include <iostream>
#include "Components/Processor.h"
#include "Display/Display.h"
#include <thread>
#include "Compiler/parser.h"


using std::chrono::milliseconds;
vector<uint16_t> getFromData(const Memory&);
vector<uint16_t> pixels;

int main() {
    #if defined(NOSYNC)
        //std::cout.sync_with_stdio(false);
    #endif
    // 0xFFFF FFFF FFFF FFFF
    //
    std::vector<std::string> assemblyCode = {
            "STUR x5, [x6, #0]",    // Store color (x5) in memory (x6 + 0 offset)
            "ADD X6, X6, X3",       // Add 4
            "SUBS X7, X2, X6",      // Compare with width
            "CBNZ X7, #-3",         // Loop back
            "ADD X5, X5, X3",       // Add 4 to color
            "ADD X6, X31, X31",     // Set x6 to 0
            "CBZ X31, #-6",         // Loop back
    };

    vector<uint32_t> machineCode = compile(assemblyCode, "output.bin");


    auto display = Display(100, 100);

    Processor processor((display.height * display.width * 2) + 1, 10, &display);
    processor.setup(machineCode);
    bool running = true;
    int i = 0;
    while (running) {
        // Process the processor logic here

        processor.process();

        // Handle events and render
        sf::Event event;
        while (display.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }
        display.render();
//        if(i++ >= display.height*display.width) {
//
//            i = 0;
//        }
    }
    return 0;
}
