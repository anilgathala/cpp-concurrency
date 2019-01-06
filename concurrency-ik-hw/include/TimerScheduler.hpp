//
//  TimerScheduler.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/23/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef TimerScheduler_hpp
#define TimerScheduler_hpp


#include <chrono>
#include <condition_variable>
#include <functional>
#include <stdio.h>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>


class TimerTask {
public:
    bool operator<(const TimerTask & t_right);
    
    TimerTask(int id, std::function<void(int)> fn, std::chrono::time_point<std::chrono::system_clock> target_time): id_(id), fn_(fn), target_time_(target_time) {}
    
    std::chrono::time_point<std::chrono::system_clock> target_time() const { return target_time_; }
    
    void call() {
        fn_(id_);
    }
    int id() { return id_; }
private:
    int id_;
    std::function<void(int)> fn_;
    std::chrono::time_point<std::chrono::system_clock> target_time_;
};

class TimerScheduler {
public:
    TimerScheduler();
    ~TimerScheduler();
    // add this task to task_queue and schedule sleep accordingly
    void submit_task(std::shared_ptr<TimerTask> t);
    
private:
    void service_func();
    std::priority_queue<std::shared_ptr<TimerTask>, std::vector<std::shared_ptr<TimerTask>>> task_queue_;
    std::condition_variable task_queue_cv_;
    std::mutex task_queue_lock_;
    std::unique_ptr<std::thread> service_;
    std::atomic<bool> shutdown_;
    
};

#endif /* TimerScheduler_hpp */
