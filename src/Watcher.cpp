#include "Watcher.h"

// Linux
#include <linux/limits.h>
#include <sys/inotify.h>
#include <unistd.h>

namespace {
    typedef decltype(free)* FreeFunction;
    template <typename T>
    std::unique_ptr<T, FreeFunction> autoFreeMalloc(size_t bufsiz) {
        return std::unique_ptr<T, FreeFunction>(reinterpret_cast<T*>(malloc(bufsiz)), &free);
    }
}

Watcher::Watcher(const std::string& filename, std::function<void()> onChange) {
    std::promise<void> threadStarted;
    std::thread thread([this, filename, onChange, &threadStarted]() {
        run_(filename, onChange, threadStarted);
    });
    using std::swap;
    swap(thread_, thread);
    threadStarted.get_future().get();
}

void Watcher::run_(const std::string& filename, std::function<void()> onChange, std::promise<void>& watching) {
    int inotfd = inotify_init();
    /*int watch_desc = */ inotify_add_watch(inotfd, filename.c_str(), IN_MODIFY);
    size_t bufsiz = sizeof(struct inotify_event) + PATH_MAX + 1;
    auto event = autoFreeMalloc<struct inotify_event>(bufsiz);
    watching.set_value();
    read(inotfd, event.get(), bufsiz);
    onChange();
}

void Watcher::join() {
   thread_.join();
}
