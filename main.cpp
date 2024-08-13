#include <iostream>
#include "Components/Processor.h"
#include "Display/Display.h"
#include <thread>
#include "Compiler/parser.h"


using std::chrono::milliseconds;


int main() {
    #if defined(NOSYNC)
        //std::cout.sync_with_stdio(false);
    #endif
    // 0xFFFF FFFF FFFF FFFF
    //

    auto legv8Code = std::fstream("../assembly.s", std::ios::in);
    std::string line;
    std::vector<std::string> assemblyCode;
    while(std::getline(legv8Code, line)) {
        assemblyCode.push_back(line);
        std::cout<<line<<"\n";
    }
    legv8Code.close();

    vector<uint32_t> machineCode = compile(assemblyCode, "output.bin");


    int display_width = 120;
    int display_height = display_width;

    auto display = Display(display_width, display_height);

    Processor processor((display.height * display.width * 2) + 1, (int) machineCode.size()*4, &display);

    processor.setup(machineCode);

    bool running = true;
    int i = 0;
    sf::Event event;
    bool optimizeRendering = true;
    while (running) {
        // Process the processor logic here

        processor.process();

        while (display.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }

        if(i++ >= display.height*display.width && optimizeRendering){
            display.render();
            i = 0;
        }else{
            display.render();
        }

    }
    return 0;
}
