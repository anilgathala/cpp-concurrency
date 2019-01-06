//
//  ThreadLocalStorage.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/26/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef ThreadLocalStorage_hpp
#define ThreadLocalStorage_hpp

#include <stdio.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <string>
#include <unordered_map>

class ThreadLocalStorage {
public:
    // creates an entry in big map for thread
    // this is run with lock held

    void create_thread_local_storage(int thread_id);
    std::string get(int thread_id, int key);
    void put(int thread_id, int key, std::string val);
    void remove(int thread_id, int key);
    
private:
    // TODO: string should be templatized
    // for now it is string for simplicity
    std::shared_ptr<std::unordered_map<int, std::string>> get_small_map(int thread_id);
    std::unordered_map<int, std::shared_ptr<std::unordered_map<int, std::string>>> big_map_;
    std::mutex big_map_lock_;

};

void test_thread_local_storage();

#endif /* ThreadLocalStorage_hpp */
