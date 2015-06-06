#include <fstream>
#include <cassert>
#include <iostream>

#include "Watcher.h"

using namespace std;

int main() {
    const std::string filename = "touch-test";
    std::cout << "Startup" << std::endl;
    std::atomic_bool fileTouched{false};
    std::ofstream ofs(filename);
    ofs.close();
    std::cout << "File created" << std::endl;
    Watcher watcher(filename, [&]() {
        fileTouched = true;
    });
    std::cout << "Watcher created" << std::endl;
    ofs.open(filename);
    ofs << "Test file";
    ofs.close();
    std::cout << "File touched" << std::endl;
    watcher.join();
    std::cout << "Joined" << std::endl;
    assert(fileTouched);
    return 0;
}