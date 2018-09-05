// Simple example of shared_mutex
//

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

class Counter {
   public:
      Counter(): cnt_(1) {}
      unsigned int get() const;
      void put();

   private:
      unsigned int cnt_;
      mutable std::shared_mutex lock_;
};

unsigned int Counter::get() const
{
   int ret = 0;
   {
    std::shared_lock<std::shared_mutex> lk(lock_);
    ret = cnt_;
   }
   return ret;
}

void Counter::put()
{
   {
    // TODO: check if lock_guard can be used
    std::unique_lock<std::shared_mutex> lk(lock_);
    cnt_++;
   }
}

class SafePrint {
   public:
      void print(int id, int cnt);
   private:
      std::mutex print_lock_;
};

void SafePrint::print(int id, int cnt)
{
   {
      std::lock_guard<std::mutex> lk(print_lock_);
      std::cout << "id: " << id << " counter val: " << cnt << std::endl;
   }
}

void thread_func(Counter& counter, SafePrint& printer, int id)
{
   int i = 0;
   while(i < 1000) {
      counter.put();
      counter.put();
      printer.print(id, counter.get());
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      i++;
   }
}
int main()
{
   Counter counter;
   SafePrint printer;
   counter.put();
   counter.put();
   std::thread t1(thread_func, std::ref(counter), std::ref(printer), 1);
   std::thread t2(thread_func, std::ref(counter), std::ref(printer), 2);
  
   t1.join(); 
   t2.join(); 

   return 0;
}
