//
//  AsyncRequestDispatcher.hpp
//  concurrency
//
//  Created by Anil Gathala on 8/22/18.
//  Copyright © 2018 AG Inc. All rights reserved.
//

#ifndef AsyncRequestDispatcher_hpp
#define AsyncRequestDispatcher_hpp

#include <cstdint>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <queue>
#include <stdio.h>
#include <thread>

struct Request {
    int a;
    int b;
    Request(int aa, int bb): a(aa), b(bb) {}
};

struct Response {
    bool status;
    int result;
};


class AsyncRequestDispatcher {
public:
    std::future<Response> submit_request(std::shared_ptr<Request>);
    AsyncRequestDispatcher();
    ~AsyncRequestDispatcher();
    static Response product(std::shared_ptr<Request> req);
    void shutdown();
private:
    void service_func();
    
    
    std::queue<std::pair<std::packaged_task<Response(std::shared_ptr<Request>)>,std::shared_ptr<Request>>> req_queue_;
    std::mutex req_queue_lock_;
    std::condition_variable req_queue_cv_;
    std::unique_ptr<std::thread> service_;
    std::atomic<bool> shutdown_;
};

#endif /* AsyncRequestDispatcher_hpp */
