//
//  RateLimit.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/21/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef RateLimit_hpp
#define RateLimit_hpp

#include <stdio.h>
#include <cstdint>
#include <chrono>



class RateLimit {
public:
    // return true (pass) or false (fail)
    bool rate_limit_gate();
    
    RateLimit(uint32_t rate_time_window, uint32_t rate_messages_per_time_window):
        last(std::chrono::high_resolution_clock::now()),
        rate_time_window_(rate_time_window),
        rate_messages_per_time_window_(rate_messages_per_time_window),
        current_allowance_messages_(5.0)
    {};
private:
    std::chrono::high_resolution_clock::time_point last;
    
    
    // e.g., 8 seconds
    double rate_time_window_;
    // e.g., 5 messages -> 5 messages per 8 seconds
    double rate_messages_per_time_window_;
    // how many messages / calls can be allowed now
    double current_allowance_messages_;
    
    // constraints by example:
    // allow 5 messages per 8 sec window
    // if you accumulate allowance more than 5 at any point
    // clamp it at 5
};

void test_rate_limitter(int num_messages, int seconds, RateLimit& rate_limiter);

#endif /* RateLimit_hpp */
