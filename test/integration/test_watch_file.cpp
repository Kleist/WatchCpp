#include <fstream>
#include <cassert>
#include <iostream>

#include "Watcher.h"

using namespace std;

int main() {
    const std::string filename = "touch-test";
    std::atomic_bool fileTouched{false};
    std::ofstream ofs(filename);
    ofs.close();
    Watcher watcher(filename, [&]() {
        fileTouched = true;
    });
    ofs.open(filename);
    ofs << "Test file";
    ofs.close();
    watcher.join();
    assert(fileTouched);
    return 0;
}