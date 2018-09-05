//
//  AsyncRequestDispatcher.cpp
//  concurrency
//
//  Created by Anil Gathala on 8/22/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#include "AsyncRequestDispatcher.hpp"

Response AsyncRequestDispatcher::product(std::shared_ptr<Request> req)
{
    Response resp;
    resp.status = false;
    if (req) {
        resp.result = req->a * req->b;
        resp.status = true;
    }
    return resp;
}

std::future<Response> AsyncRequestDispatcher::submit_request(std::shared_ptr<Request> req)
{
    std::packaged_task<Response(std::shared_ptr<Request>)> req_task(&AsyncRequestDispatcher::product);
    std::future<Response> resp_future = req_task.get_future();
    {
        std::lock_guard<std::mutex> lk(req_queue_lock_);
        req_queue_.push(std::make_pair(std::move(req_task), std::ref(req)));
    }
    req_queue_cv_.notify_one();
    return resp_future;
}

void AsyncRequestDispatcher::service_func()
{
    while(1) {
        {
            std::unique_lock<std::mutex> lk(req_queue_lock_);
            req_queue_cv_.wait(lk, [this](){return (!req_queue_.empty() || shutdown_);});
            if (shutdown_) {
                return;
            }
            auto task_pair = std::move(req_queue_.front());
            req_queue_.pop();
            
            lk.unlock(); // we do this here, so we do not lock while running the task
            
            // now run the task
            task_pair.first(task_pair.second);
        }
        
        
    }
}

void AsyncRequestDispatcher::shutdown()
{
    shutdown_ = true;
    req_queue_cv_.notify_one();
}
AsyncRequestDispatcher::AsyncRequestDispatcher(): shutdown_(false)
{
    /// It is important to pass "this", otherwise you'd get
    /// the mysterious "attempting to use deleted function"
    service_ = (std::unique_ptr<std::thread>) new std::thread(&AsyncRequestDispatcher::service_func, this);
}

AsyncRequestDispatcher::~AsyncRequestDispatcher()
{
    service_->join();
}
