//
//  EvenOdd.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/17/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "EvenOdd.hpp"

void EvenOdd::do_print(int n)
{
    {
        std::unique_lock<std::mutex> lk(print_mut_);
        std::cout << n << std::endl;
    }
}

void EvenOdd::wait_for_start()
{
    {
        std::unique_lock<std::mutex> lk(start_mut_);
        // A conditional variable should always always needs a condition
        // even if it is a trivial situation
        // otherwise, we cannot distinguish between a spurious & legit wakeup
        start_cv_.wait(lk, [this]() { return start_flag_;});
    }
}

void EvenOdd::print_num(bool even)
{
    wait_for_start();
    
    int i = (even ? 0: 1);
    int count = 0;
    while (i <= num_) {
        {
            std::unique_lock<std::mutex> lk(go_mut_);
            go_cv_.wait(lk, [this, even]() { return (even ? (go_ %2 == 0): (go_ % 2 != 0));});
            // we do not really need do_print and a separate mut to protect cout
            //do_print(i);
            
            // cout is being protected by go_mut_ automatically
            // therefore, go_mut_ protects both "go_" as well as "cout"
            if (even) {
                std::cout << "even: " << i << std::endl;
            } else {
                std::cout << "odd: " << i << std::endl;
            }
            
            go_ = 1 - go_; // flip the bit so other end can proceed
        }
        go_cv_.notify_one();

        i = i + 2;
        count++;
    }
    
}

void EvenOdd::print_start()
{
    {
        std::lock_guard<std::mutex> lk(start_mut_);
        start_flag_ = true;
    }
    start_cv_.notify_all();
}

EvenOdd::EvenOdd(int num): num_(num), start_flag_(false), go_(0)
{
    even_ = (std::unique_ptr<std::thread>) new std::thread(&EvenOdd::print_num, this, true);
    odd_ = (std::unique_ptr<std::thread>) new std::thread(&EvenOdd::print_num, this, false);
}

EvenOdd::~EvenOdd(){
    even_->join();
    odd_->join();
}
