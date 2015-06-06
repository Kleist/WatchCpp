#include "Watcher.h"

#include <limits.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <iostream>

Watcher::Watcher(const std::string& filename, std::function<void()> onChange)  {
    std::promise<void> threadStarted;
    std::thread thread([this, filename, onChange, &threadStarted]() {
        run_(filename, onChange, threadStarted);
    });
    using std::swap;
    swap(thread_, thread);
    threadStarted.get_future().get();
}

void Watcher::run_(const std::string& filename, std::function<void()> onChange, std::promise<void>& watching) {
    std::cout << "Thread running" << std::endl;
    int inotfd = inotify_init();
    /*int watch_desc = */ inotify_add_watch(inotfd, filename.c_str(), IN_MODIFY);
    size_t bufsiz = sizeof(struct inotify_event) + PATH_MAX + 1;
    typedef decltype(free)* FreeFunction;
    auto event = std::unique_ptr<struct inotify_event, FreeFunction>(reinterpret_cast<struct inotify_event*>(malloc(bufsiz)), free);

    watching.set_value();
    read(inotfd, event.get(), bufsiz);
    onChange();
    std::cout << "After read" << std::endl;
}

void Watcher::join() {
   thread_.join();
}
