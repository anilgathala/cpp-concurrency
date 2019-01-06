//
//  ConnectionPool.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/25/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef ConnectionPool_hpp
#define ConnectionPool_hpp

#include <condition_variable>
#include <mutex>
#include <iostream>
#include <vector>

// this is just a pool of ints
// TODO: templatize

void test_connection_pool();

class ConnectionPool {
public:
    ConnectionPool(int max_num);
    int get();
    void put(int);
private:
    int max_num_;
    std::vector<int> obj_list_;
    std::mutex lock_;
    std::condition_variable cv_;
};

#endif /* ConnectionPool_hpp */
