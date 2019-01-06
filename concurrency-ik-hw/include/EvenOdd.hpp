//
//  EvenOdd.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/17/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef EvenOdd_hpp
#define EvenOdd_hpp

#include <stdio.h>
#include <iostream>
#include <thread>

class EvenOdd {
public:
    EvenOdd(int num);
    ~EvenOdd();
    void print_num(bool even);
    void print_start();
    void do_print(int n);
    void wait_for_start();
private:
    int num_;
    std::unique_ptr<std::thread> even_;
    std::unique_ptr<std::thread> odd_;
    
    // this is not really needed, see commnets in cpp
    std::mutex print_mut_;
    
    bool start_flag_;
    std::mutex start_mut_;
    std::condition_variable start_cv_;
    
    int go_; // 0 (even) or 1 (odd)
    std::mutex go_mut_;
    std::condition_variable go_cv_;
    

};

#endif /* EvenOdd_hpp */
