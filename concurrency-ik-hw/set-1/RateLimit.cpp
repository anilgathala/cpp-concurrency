//
//  RateLimit.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/21/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "RateLimit.hpp"

#include <iomanip> // put_time
#include <iostream>
#include <thread>
#include <ctime> // localtime



void thread_func_make_calls(int num_messages, int seconds, RateLimit& rate_limiter)
{
    int i = 0;
    while( i < 5) {
        
        // take a nap
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        std::cout << "--------------" << std::endl;
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        
        int j = 0;
        while(j < num_messages) {
            bool status = rate_limiter.rate_limit_gate();
            std::cout << "call at ";
            std::cout << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
            if (status) {
                
                std::cout << " passed!" << std::endl;
            } else {
                std::cout << " failed!" << std::endl;
            }
            j++;
        }
        
        i++;
    }
    
}

void test_rate_limitter(int num_messages, int seconds, RateLimit& rate_limiter)
{
    /// It is important to pass "std::ref(rate_limiter)" (not  simple rate_limiter), otherwise you'd get
    /// the mysterious "attempting to use deleted function"
    std::thread foo(thread_func_make_calls, num_messages, seconds, std::ref(rate_limiter));

    if (foo.joinable()) {
        foo.join();
    }
    
}


bool RateLimit::rate_limit_gate()
{
    
    std::chrono::high_resolution_clock::time_point now =
        std::chrono::high_resolution_clock::now();
    
    // how much time passed ?
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( now - last ).count();
    std::cout << " duration = " << duration<< std::endl;
    last = now;
    double added_allowance = (duration) * (rate_messages_per_time_window_ / rate_time_window_); // messages per sec
    std::cout << " added_allowance = " << added_allowance << std::endl;
    current_allowance_messages_ += added_allowance;
    std::cout << " current_allowance_messages_ = " << current_allowance_messages_ << std::endl;
    
    if (current_allowance_messages_ > rate_messages_per_time_window_) {
        current_allowance_messages_ = rate_messages_per_time_window_;
    }
    
    if (current_allowance_messages_ >= 1) {
        current_allowance_messages_ = current_allowance_messages_ - 1;
        return true;
    }
    return false;
}
