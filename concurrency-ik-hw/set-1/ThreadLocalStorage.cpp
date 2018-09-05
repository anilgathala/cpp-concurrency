//
//  ThreadLocalStorage.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/26/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "ThreadLocalStorage.hpp"

#include <mutex>
#include <thread>
#include <string>
#include <unordered_map>
#include <utility>

const std::string names[] = { "kiran", "anil", "sunil"};

class LocalSafePrint {
public:
    void print(const std::string& msg);
private:
    std::mutex print_lock_;
};

void LocalSafePrint::print(const std::string& msg)
{
    {
        std::lock_guard<std::mutex> lk(print_lock_);
        std::cout << msg << std::endl;
    }
}

void thread_func(LocalSafePrint& printer, ThreadLocalStorage& thread_local_storage, int thread_id)
{

    int i = 0;
    while (i < 100) {
        i++;
        thread_local_storage.put(thread_id, 1*i, names[(thread_id+i+1)%3]);
        thread_local_storage.put(thread_id, 2*i, names[(thread_id+i+2)%3]);
        thread_local_storage.put(thread_id, 3*i, names[(thread_id+i+3)%3]);
        std::string put_msg = "key: " + std::to_string(1*i) + " val: " + names[(thread_id+i+1)%3];
        printer.print(put_msg);
        put_msg = "key: " + std::to_string(2*i) + " val: " + names[(thread_id+i+2)%3];
        printer.print(put_msg);
        put_msg = "key: " + std::to_string(3*i) + " val: " + names[(thread_id+i+3)%3];
        printer.print(put_msg);
        if (thread_local_storage.get(thread_id, 1*i) != names[(thread_id+i+1)%3]) {
            std::string msg = "lookup failed, thread_id " + std::to_string(thread_id) + " key = " + std::to_string(1*i);
            msg += " i = " + std::to_string(i) + " key = " + std::to_string(1*i);
            printer.print(msg);
            continue;
        }
        if (thread_local_storage.get(thread_id, 2*i) != names[(thread_id+i+2)%3]) {
            std::string msg = "lookup failed, thread_id " + std::to_string(thread_id) + " key = " + std::to_string(2*i);
            msg += " i = " + std::to_string(i) + " key = " + std::to_string(2*i);
            printer.print(msg);
            continue;
        }
        if (thread_local_storage.get(thread_id, 3*i) != names[(thread_id+i+3)%3]) {
            std::string msg = "lookup failed, thread_id " + std::to_string(thread_id) + " key = " + std::to_string(3*i);
            msg += " i = " + std::to_string(i) + " key = " + std::to_string(3*i);
            printer.print(msg);
            continue;
        }
        std::string success_msg = "all is well, thread: " + std::to_string(thread_id);
        printer.print(success_msg);
    }

}

void test_thread_local_storage()
{
    ThreadLocalStorage thread_local_storage;
    LocalSafePrint printer;
    thread_local_storage.create_thread_local_storage(1);
    thread_local_storage.create_thread_local_storage(2);
    
    std::thread t1(thread_func, std::ref(printer), std::ref(thread_local_storage), 1);
    std::thread t2(thread_func, std::ref(printer), std::ref(thread_local_storage), 2);
    
    t1.join();
    t2.join();
}

void ThreadLocalStorage::create_thread_local_storage(int thread_id)
{
    {
        auto small_map = std::make_shared<std::unordered_map<int, std::string>>();
        std::pair<int, std::shared_ptr<std::unordered_map<int, std::string>>> entry(thread_id, small_map);
        
        std::lock_guard<std::mutex> lk(big_map_lock_);
        
        auto result = big_map_.insert(entry);
        if (!result.second) {
            // already existing
        }
        // either insert would've worked
    }
}

std::string ThreadLocalStorage::get(int thread_id, int key)
{
    auto small_map = get_small_map(thread_id);
    auto itr = small_map->find(key);
    if (itr != small_map->end()) {
        return itr->second;
    }
    return "";
}

void ThreadLocalStorage::put(int thread_id, int key, std::string val)
{
    auto small_map = get_small_map(thread_id);
    //std::pair<int, std::string> p(key, val);
    auto res = small_map->insert(std::make_pair(key, val));
    if (!res.second) {
        small_map->at(key) = val;
    }
}

void ThreadLocalStorage::remove(int thread_id, int key)
{
    auto small_map = get_small_map(thread_id);
    small_map->erase(key);
}

std::shared_ptr<std::unordered_map<int, std::string>> ThreadLocalStorage::get_small_map(int thread_id)
{
    {
        std::lock_guard<std::mutex> lk(big_map_lock_);
        auto itr = big_map_.find(thread_id);
        if (itr == big_map_.end()) {
            return nullptr;
        }
        return itr->second;
    }
}

