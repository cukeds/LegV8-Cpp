#include <iostream>
#include "Components/Processor.h"
#include "Display/Display.h"
#include <thread>
#include <cstring>
#include "Compiler/parser.h"


using std::chrono::milliseconds;

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
std::vector<uint16_t> getDisplayMemory(std::vector<uint8_t> data) {
    std::vector<uint16_t> displayMemory;
    for(int i = 0; i < data.size(); i+=2) {
        displayMemory.push_back((data[i] << 8) | data[i+1]);
    }
    return displayMemory;
}

std::vector<std::string> readAssemblyCode(std::string filename) {
    std::unordered_map<std::string, int> labels;
    auto legv8Code = std::fstream(filename, std::ios::in);
    std::string line;
    std::vector<std::string> assemblyCode;
    int currentLine = 0;
    while(std::getline(legv8Code, line)) {
        currentLine++;
        if(line.contains(':')) {
            labels.insert({line.substr(0, line.find(':')), currentLine});
            line = line.substr(line.find(':')+1);
            ltrim(line);
            rtrim(line);
        }
        assemblyCode.push_back(line);
    }
    legv8Code.close();

    currentLine = 0;
    //replace any labels with their corresponding line number
    for(auto & assemblyLine : assemblyCode) {
        currentLine++;
        if(assemblyLine.starts_with('B') || assemblyLine.starts_with("CB")) {
            for(auto const& [label, line_] : labels) {
                if(assemblyLine.contains(label)) {
                    assemblyLine.replace(assemblyLine.find(label), label.size(), std::to_string(line_ - currentLine));
                }
            }
        }
    }

    return assemblyCode;
}


int main(int argc, char* argv[]) {
    #if defined(NOSYNC)
        //std::cout.sync_with_stdio(false);
    #endif

    bool optimizeRendering = false;
    bool debug = false;
    int display_width = 512;
    int memory_size = 1024;
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
    // 5. -m for memory size

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
        }else if(strcmp(argv[j], "-m") == 0){
            memory_size = atoi(argv[j+1]);
        }
     }

     if(argc <= 1){
         std::cout<<"No arguments provided\n";
         optimizeRendering = true;
         assemblyCode = readAssemblyCode("assembly.s");
         file = true;
         if(assemblyCode.empty()){
             std::cerr << "No assembly.s file provided\n";
             return 1;
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


    Processor processor((display.height * display.width * PIXEL_SIZE) + memory_size, (int) machineCode.size()*4, &display);

    processor.setup(machineCode);


    sf::Event event;


    while (running) {
        // Process the processor logic here

        processor.process();

        if(i++ >= display.height*display.width * 4 && optimizeRendering){
            auto data = processor.getDataMemory();
            display.setPixels(getDisplayMemory(data));
            display.render();
            i=0;
            while (display.window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                }
            }
        }else if(!optimizeRendering && i >= display_width * 4){
            auto data = processor.getDataMemory();
            display.setPixels(getDisplayMemory(data));
            display.render();
            i = 0;
        }


    }
    return 0;
}
