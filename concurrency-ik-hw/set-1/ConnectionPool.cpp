//
//  ConnectionPool.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/25/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "ConnectionPool.hpp"
#include <chrono>
#include <string>
#include <thread>

class SafePrint {
public:
    void print(const std::string& msg);
private:
    std::mutex print_lock_;
};

void SafePrint::print(const std::string& msg)
{
    {
        std::lock_guard<std::mutex> lk(print_lock_);
        std::cout << msg << std::endl;
    }
}


void get_thread(ConnectionPool& pool, SafePrint& printer)
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        printer.print("get 1 resource: begin!");
        pool.get();
        printer.print("get 1 resource: Done!");
        
    }
}

void put_thread(ConnectionPool& pool, SafePrint& printer)
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        pool.put(1);
        printer.print("just put 1 resource");
    }
}

void test_connection_pool()
{
    ConnectionPool pool(4);
    SafePrint printer;
    std::thread t1(get_thread, std::ref(pool), std::ref(printer));
    std::thread t2(put_thread, std::ref(pool), std::ref(printer));
    
    t1.join();
    t2.join();
}

ConnectionPool::ConnectionPool(int max_num)
{
    max_num_ = max_num;
    
    for (int i = 0; i < max_num_; i++) {
        obj_list_.push_back(0);
    }
}

int ConnectionPool::get()
{
    int val = 0;
    {
        std::unique_lock<std::mutex> lk(lock_);
        if (obj_list_.size() == 0) {
            cv_.wait(lk, [this](){return (obj_list_.size() > 0);});
        }
        val = obj_list_.back();
        obj_list_.pop_back();
    }
    return val;
}

void ConnectionPool::put(int val)
{
    {
        std::unique_lock<std::mutex> lk(lock_);
        if (obj_list_.size() == (max_num_ - 1)) {
            return;
        }
        obj_list_.push_back(val);
        if (obj_list_.size() == 1) {
            cv_.notify_one();
        }
    }
}
