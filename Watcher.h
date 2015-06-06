#ifndef WATCH_WATCHER_H
#define WATCH_WATCHER_H


#include <functional>
#include <thread>
#include <future>

class Watcher {
private:
    std::thread thread_;

public:
    Watcher(const std::string& filename, std::function<void()> onChange);

    void join();
private:
    void run_(const std::string &filename, std::function<void()> onChange, std::function<void()> onWatching);
};


#endif //WATCH_WATCHER_H
