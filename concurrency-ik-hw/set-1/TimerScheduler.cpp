//
//  TimerScheduler.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/23/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "TimerScheduler.hpp"
#include <iostream>

bool operator<(const TimerTask& t_left, const TimerTask& t_right)
{
    return (t_left.target_time() > t_right.target_time());
}

TimerScheduler::TimerScheduler(): shutdown_(false)
{
    service_ = (std::unique_ptr<std::thread>) new std::thread(&TimerScheduler::service_func, this);
    
}

TimerScheduler::~TimerScheduler()
{
    if (service_->joinable()) {
        service_->join();
    }
}

void TimerScheduler::service_func()
{
    while(!shutdown_) {
        int default_wait_ms = 100;
        std::chrono::time_point<std::chrono::system_clock> next_wakeup = std::chrono::system_clock::now() + std::chrono::milliseconds(default_wait_ms);
        std::unique_lock<std::mutex> lk(task_queue_lock_);
        // when is the next task's target time
        if (!task_queue_.empty()) {
            next_wakeup = task_queue_.top()->target_time();
            std::cout << "waiting for task: " << task_queue_.top()->id() << std::endl;
        } else {
            std::cout << "waiting for " << default_wait_ms << " ms: " << std::endl;
        }
        
        // wait until the next task's target_time
        
        auto res = task_queue_cv_.wait_until(lk, next_wakeup);
        std::cout << " wokeup " << std::endl;

        if (res == std::cv_status::timeout) {
            // execute everything that has crossed now()

            while(!task_queue_.empty()) {
                if (task_queue_.top()->target_time() <= std::chrono::system_clock::now()) {
                    auto task = task_queue_.top();
                    task_queue_.pop();
                    task->call();
                } else {
                    break;
                }
            }
        } else {
            // may be we wokeup because some new task
            // with sooner target time has been added
            // in that case, go back to the queue
            // and repeat - wait until top()'s target time
        }
        lk.unlock();
    }
}

void TimerScheduler::submit_task(std::shared_ptr<TimerTask> t)
{
    //bool wakeup = false;
    {
        std::lock_guard<std::mutex> lk(task_queue_lock_);
        // check if wakeup is needed
//        if (task_queue_.empty()) {
//            wakeup = true;
//        }
//        else if (t->target_time() < task_queue_.top()->target_time()) {
//            wakeup = true;
//        }
        task_queue_.push(t);
    }
    task_queue_cv_.notify_one();
//    if (wakeup) {
//        task_queue_cv_.notify_one();
//    }
    
}



/// sample output
//Hello, World!
//Task 0 should wait: 100 seconds
//Task 1 should wait: 90 seconds
//Task 2 should wait: waiting for task: 801 seconds
//
//Task 3 should wait: 70 seconds
//Task 4 should wait: 60 seconds
//wokeup
//waiting for task: 4
//wokeup
//task id: 4
//waiting for task: 3
//wokeup
//task id: 3
//waiting for task: 2
//wokeup
//task id: 2
//waiting for task: 1
//wokeup
//task id: 1
//waiting for task: 0
//wokeup
//task id: 0
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//wokeup
//waiting for 100 ms:
//Program ended with exit code: 9
