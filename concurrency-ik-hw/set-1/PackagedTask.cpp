//
//  PackagedTask.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/22/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "PackagedTask.hpp"

#include <iostream>
#include <thread>
#include <future>
#include <functional>

int task_func(int a)
{
    return (a*a);
}

void thread_func(std::packaged_task<int(int)> && ptask, int arg)
{
    // inside packaged_task
    // the following function call translates to
    // -- call underneath function and then store the result in it's future
    ptask(arg);
}

void test_packaged_task()
{
    std::packaged_task<int(int)> ptask(task_func);
    std::future<int> f = ptask.get_future();
    std::thread th(thread_func, std::move(ptask), 10);
    //th.join();
    std::cout << " future output: " << f.get() << std::endl;
    th.join();
}
