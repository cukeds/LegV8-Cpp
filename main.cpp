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

std::vector<std::string> readAssemblyCode(const std::string& filename) {
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
    int j;
    bool file = false;
    vector<std::string> assemblyCode;
    // read args
    // 1. -d for debug
    // 2. -w for display width
    // 3. -o for optimization
    // 4. -s for source file
    // 5. -m for memory size
    // 6. -h for help

     for(j = 0; j < argc; j++){
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
        }else if(strcmp(argv[j], "-h") == 0){
            std::cout<<"Usage: ./main [-d] [-w display_width] [-o] [-s source_file] [-m memory_size] [-h]\n";
            std::cout<<"-d: Debug mode\n";
            std::cout<<"-w: Set display width\n";
            std::cout<<"-o: Optimize rendering\n";
            std::cout<<"-s: Source file\n";
            std::cout<<"-m: Memory size\n";
            std::cout<<"-h: Help\n";

            return 0;
        }
     }

     if(argc <= 1){
         std::cout<<"No arguments provided\n";
         optimizeRendering = true;
     }

     if(!file){
        assemblyCode = readAssemblyCode("../assembly.s");
        if(assemblyCode.empty()){
         std::cerr << "No assembly.s file provided\n";
         return 1;
        }
     }


    vector<uint32_t> machineCode = compile(assemblyCode, "output.bin");


    int display_height = display_width;

    auto display = Display(display_width, display_height);

    // set null

    if(!debug) std::cout.rdbuf(nullptr);


    Processor processor((display.height * display.width * PIXEL_SIZE) + memory_size, (int) machineCode.size()*4, {display_width, display_height});

    processor.setup(machineCode);


    sf::Event event;
    vector<uint8_t> data;
    while (running) {
        // Process the processor logic here

        processor.process();

        if(i++ >= display_width*display_height*4 && optimizeRendering){
            data = processor.getDataMemory();
            display.setPixels(data);
            display.render();
            i=0;
            while (display.window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                }
            }
        }else if(!optimizeRendering && i >= display_width * 4){
            data = processor.getDataMemory();
            display.setPixels(data);
            display.render();
            i = 0;
        }


    }
    return 0;
}
