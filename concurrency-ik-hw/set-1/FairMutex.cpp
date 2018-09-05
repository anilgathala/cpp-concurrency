//
//  FairMutex.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/26/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "FairMutex.hpp"
#include <chrono>
#include <string>

void FairMutex::fair_lock(int thread_id_debug)
{
    std::string msg;
    std::unique_lock<std::mutex> lk (internal_lock_);
    if (cv_vec_.empty() && state()) {
        state_ = false;
        msg = "(free)lock acquired thread: " + std::to_string(thread_id_debug);
        print(msg);
        return;
    }
    
    auto cv = std::make_shared<std::condition_variable>();
    cv_vec_.push(cv);
    msg = "waiting for lock, thread: " + std::to_string(thread_id_debug);
    print(msg);
    cv->wait(lk, [this]() { return state(); });
//    if (cv == cv_vec_.front()) {
//        cv_vec_.pop();
//    }
    state_ = false;
    msg = "lock acquired thread: " + std::to_string(thread_id_debug);
    print(msg);
}

void FairMutex::fair_unlock(int thread_id_debug)
{
    std::string msg = "unlocking: " + std::to_string(thread_id_debug);
    print(msg);
    std::unique_lock<std::mutex> lk (internal_lock_);
    if (!cv_vec_.empty()) {
        cv_vec_.front()->notify_one();
        cv_vec_.pop();
        msg += " signalled a cv in queue";
        print(msg);
    } else {
        msg += " not signalled - cv queue empty!";
        print(msg);
    }
    state_ = true;
}

void FairMutex::print(std::string msg)
{
    std::lock_guard<std::mutex> lk(print_lock_);
    std::cout << msg << std::endl;
}

std::vector<int> shared_vars;
void fair_mutex_thread_func(FairMutex& f_mutex, int thread_id)
{
    int i = 0;
    while (i < 100) {
        f_mutex.fair_lock(thread_id);
        shared_vars.push_back(thread_id);
        std::string msg = std::to_string(thread_id) + " set shared_var to " + std::to_string(shared_vars[i]);
        f_mutex.print(msg);
        f_mutex.fair_unlock(thread_id);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        i++;
    }
}

void test_fair_mutex()
{
    FairMutex f_mutex;

    
    std::thread t1(fair_mutex_thread_func, std::ref(f_mutex), 1);
    std::thread t2(fair_mutex_thread_func, std::ref(f_mutex), 2);
    
    t1.join();
    t2.join();
    
    for (int i = 0; i < shared_vars.size(); i++) {
        std::cout << "shared_vars[" << i << "] = " << shared_vars[i] << std::endl;
        if (i > 0 && shared_vars[i] != shared_vars[i-1]) {
            //std::cout << " looks good: " << i << std::endl;
        }
        else {
            std::cout << " failure: " << shared_vars[i-1] << ", " << shared_vars[i] << std::endl;
        }
    }
}

