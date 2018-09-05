//
//  ThreadPool.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/7/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "ThreadPool.hpp"

bool ThreadPool::add_task(std::function<void()> fn)
{
    
    /// TODO: add size-limit check on task queue
    std::unique_lock<std::mutex> lk(mut);
    cv_empty.wait(lk, [this](){ return (task_queue.size() < max_tasks_);});
//    if ( task_queue.size() == max_tasks_ ) {
//        return false;
//    }
    task_queue.push_back(fn);
    lk.unlock();
    cv_full.notify_one();
    
    return true;
}

void ThreadPool::run_tasks()
{
    while(1) {
        std::function<void()> task_fn;
        std::unique_lock<std::mutex> lk(mut);
        cv_full.wait(lk, [this](){ return !task_queue.empty();});
        task_fn = task_queue.front();
        task_queue.pop_front();
        lk.unlock();
        cv_empty.notify_one();
        
        try {
            task_fn();
        } catch (...) {
            std::cout << " exception!" << std::endl;
            return;
        }
    }
}

void ThreadPool::join_all()
{
    for (int i = 0; i <  threads.size(); i++) {
        threads[i].join();
    }
    
}

ThreadPool::ThreadPool(int num_threads, int max_tasks):
    max_tasks_(max_tasks), num_threads_(num_threads)
{
    // TODO: create threads
    for (int i = 0; i <  num_threads; i++) {
        threads.push_back(std::thread(&ThreadPool::run_tasks, this));
    }
}
