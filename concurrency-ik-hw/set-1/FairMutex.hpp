//
//  FairMutex.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/26/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef FairMutex_hpp
#define FairMutex_hpp

#include <atomic>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

//namespace fairmutex {
//    class MyPrint {
//    public:
//        void print(const std::string& msg);
//    private:
//        std::mutex print_lock_;
//    };
//}
//void fairmutex::MyPrint::print(const std::string& msg)
//{
//    {
//        std::lock_guard<std::mutex> lk(print_lock_);
//        std::cout << msg << std::endl;
//    }
//}

class FairMutex {
public:
    FairMutex(): state_(true) {};
    void fair_lock(int thread_id_debug);
    void fair_unlock(int thread_id_debug);
    bool state() { return state_;}
    void print(std::string msg);
    
private:
    //fairmutex::MyPrint printer;
    std::mutex print_lock_;
    std::mutex internal_lock_;
    std::queue<std::shared_ptr<std::condition_variable>> cv_vec_;
    std::condition_variable internal_cv_;
    std::atomic<bool> state_;// true: available, false: unavailable
};

void test_fair_mutex();

#endif /* FairMutex_hpp */
