//
// Created by andreas on 6/6/15.
//

#include "Watcher.h"

#include <sys/inotify.h>
#include <linux/limits.h>
#include <unistd.h>
#include <iostream>

Watcher::Watcher(const std::string& filename, std::function<void()> onChange)
{
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
    int watch_desc = inotify_add_watch(inotfd, filename.c_str(), IN_MODIFY);
    size_t bufsiz = sizeof(struct inotify_event) + PATH_MAX + 1;
    auto event = std::unique_ptr<struct inotify_event, decltype(free)*>(reinterpret_cast<struct inotify_event*>(malloc(bufsiz)), free);

    watching.set_value();
    /* wait for an event to occur */
    read(inotfd, event.get(), bufsiz);
    onChange();
    std::cout << "After read" << std::endl;

    /* process event struct here */
}

void Watcher::join() {
   thread_.join();
}
