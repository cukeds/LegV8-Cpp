#include <iostream>
#include "Components/Processor.h"
#include "Display/Display.h"
#include <thread>
#include <cstring>
#include "Compiler/parser.h"


using std::chrono::milliseconds;


std::vector<uint16_t> getDisplayMemory(std::vector<uint8_t> data) {
    std::vector<uint16_t> displayMemory;
    for(int i = 0; i < data.size(); i+=2) {
        displayMemory.push_back((data[i] << 8) | data[i+1]);
    }
    return displayMemory;
}

std::vector<std::string> readAssemblyCode(std::string filename) {
    auto legv8Code = std::fstream(filename, std::ios::in);
    std::string line;
    std::vector<std::string> assemblyCode;
    while(std::getline(legv8Code, line)) {
        assemblyCode.push_back(line);
    }
    legv8Code.close();
    return assemblyCode;
}


int main(int argc, char* argv[]) {
    #if defined(NOSYNC)
        //std::cout.sync_with_stdio(false);
    #endif

    bool optimizeRendering = false;
    bool debug = false;
    int display_width = 512;
    bool running = true;
    int i = 0;
    int j = 0;
    bool file = false;
    vector<std::string> assemblyCode;
    // read args
    // 1. -d for debug
    // 2. -w for display width
    // 3. -o for optimization
    // 4. -s for source file

     for(j = 1; j < argc; j++){
        if(strcmp(argv[j], "-d") == 0){
            debug = true;
        }else if(strcmp(argv[j], "-w") == 0){
            display_width = atoi(argv[j+1]);
        }else if(strcmp(argv[j], "-o") == 0){
            optimizeRendering = true;
        }else if(strcmp(argv[j], "-s") == 0){
            file = true;
            assemblyCode = readAssemblyCode(argv[j+1]);
        }
     }

     if(!file){
        std::cerr << "No source file provided\n";
        return 1;
     }


    vector<uint32_t> machineCode = compile(assemblyCode, "output.bin");


    int display_height = display_width;

    auto display = Display(display_width, display_height);

    // set null

    if(!debug) std::cout.rdbuf(NULL);


    Processor processor((display.height * display.width * PIXEL_SIZE) + 1, (int) machineCode.size()*4, &display);

    processor.setup(machineCode);


    sf::Event event;


    while (running) {
        // Process the processor logic here

        processor.process();
//        while (display.window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                running = false;
//            }
//        }
        if(i++ >= display.height*display.width * 4 && optimizeRendering){
            auto data = processor.getDataMemory();
            display.setPixels(getDisplayMemory(data));
            display.render();
            i=0;

        }else if(!optimizeRendering && i >= display_width * 4){
            auto data = processor.getDataMemory();
            display.setPixels(getDisplayMemory(data));
            display.render();
            i = 0;
        }


    }
    return 0;
}
