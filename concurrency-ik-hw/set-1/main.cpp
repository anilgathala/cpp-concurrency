//
//  main.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/7/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "AsyncRequestDispatcher.hpp"
#include "EvenOdd.hpp"
#include "PackagedTask.hpp"
#include "RateLimit.hpp"
#include "ThreadPool.hpp"
#include "TimerScheduler.hpp"
#include "ConnectionPool.hpp"
#include "ThreadLocalStorage.hpp"
#include "FairMutex.hpp"

void test_func2()
{
    std::cout << " test_func2: " << std::endl;
}


void test_func1()
{
    std::cout << " test_func1: " << std::endl;
}

void quit_task()
{
    std::cout << " quit_task: " << std::endl;
    throw "quit task!";
}

void test_threadpool()
{
    ThreadPool tpool(5, 10);
    
    
    tpool.add_task(test_func1);
    tpool.add_task(test_func2);
    tpool.add_task(test_func1);
    tpool.add_task(test_func2);
    tpool.add_task(test_func1);
    tpool.add_task(test_func2);
    tpool.add_task(test_func1);
    tpool.add_task(test_func2);
    
    tpool.add_task(quit_task);
    
    tpool.join_all();
}

void test_even_odd()
{
    EvenOdd even_odd(100);
    even_odd.print_start();
    return;
}

void test_rate_limiter()
{
    // 5 messages per 8 seconds
    RateLimit rt(8, 5);
    test_rate_limitter(10, 6, rt);
    
}

void test_request_dispatcher()
{
    AsyncRequestDispatcher dispatcher;
    std::vector<std::future<Response>> future_vec;
    for (int i = 0; i < 10; i++) {
        auto req = std::make_shared<Request>(i, i);
        auto fut = dispatcher.submit_request(req);
        future_vec.push_back(std::move(fut));
    }
    std::cout << "test_request_dispatcher: submitted all requests!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    std::cout << "test_request_dispatcher: checking results..." << std::endl;
    for (int i = 0; i < 10; i++) {
        auto resp = future_vec[i].get();
        if(!resp.status || resp.result != (i*i)) {
            std::cout << "test_request_dispatcher failed!" << std::endl;
            dispatcher.shutdown();
            return;
        }
    }

    std::cout << "test_request_dispatcher passed! " << std::endl;
    
    dispatcher.shutdown();
}

void timer_task_func(int id)
{
    std::cout << " task id: " << id << std::endl;
}

void test_timer_scheduler()
{
    //std::vector<TimerTask*> task_list;
    TimerScheduler timer_queue;
    for (int i = 0; i < 5; i++) {
        int wait_seconds = (100 - 10 * i);
        std::cout << "Task " << i << " should wait: " << wait_seconds << " seconds" << std::endl;
        auto task = std::make_shared<TimerTask>(i, timer_task_func, std::chrono::system_clock::now() + std::chrono::seconds(wait_seconds));
        //task_list.push_back(task);
        timer_queue.submit_task(task);
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    //test_threadpool();
    //test_even_odd();
    //test_rate_limiter();
    //test_packaged_task();
    //test_request_dispatcher();
    //test_timer_scheduler();
    //test_connection_pool();
    //test_thread_local_storage();
    test_fair_mutex();
    return 0;
}
