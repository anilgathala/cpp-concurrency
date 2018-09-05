// Simple example of shared_mutex
//

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <vector>

std::vector<std::mutex> m(2);

class SafePrint {
   public:
      void print(int thread_id, int lock_id);
   private:
      std::mutex print_lock_;
};

void SafePrint::print(int thread_id, int lock_id)
{
   {
      std::lock_guard<std::mutex> lk(print_lock_);
      if (lock_id == 100) {
        std::cout << "thread " << thread_id << " acquired both locks!" << std::endl;
      } else if (lock_id == 1 || lock_id == 0) {
        std::cout << "thread " << thread_id << " waiting for lock: " << lock_id << std::endl;
      } else {
        std::cout << "bad lock_id: " << lock_id << std::endl;
      }
   }
}

void thread_func(SafePrint& printer, int id)
{
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
   {
      printer.print(id, 0);
      //std::lock_guard<std::mutex> lk1 (m[id]);
      std::lock_guard<std::mutex> lk1 (m[0]);
      printer.print(id, 1);
      //std::lock_guard<std::mutex> lk_2 (m[1-id]);
      std::lock_guard<std::mutex> lk_2 (m[1]);
      // second param 100 indicates acquired both locks
      printer.print(1, 100);
   }
}

int main()
{
   SafePrint printer;
   std::thread t1(thread_func, std::ref(printer), 0);
   std::thread t2(thread_func, std::ref(printer), 1);
  
   t1.join(); 
   t2.join(); 

   return 0;
}
