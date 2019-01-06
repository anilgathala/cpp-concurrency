//
//  ThreadPool.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/7/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <thread>
#include <vector>



class ThreadPool {
public:
    bool add_task(std::function<void()> fn);
    void run_tasks();
    void join_all();
    ThreadPool(int num_threads, int max_tasks);
private:
    std::mutex mut;
    std::condition_variable cv_empty;
    std::condition_variable cv_full;
    std::deque<std::function<void()>> task_queue;
    std::vector<std::thread> threads;
    int num_threads_;
    int max_tasks_;
};

#endif /* ThreadPool_hpp */
