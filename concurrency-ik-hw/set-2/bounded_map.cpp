// Simple example of shared_mutex
//

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
//#include <utility>
//#include <iterator>

class BoundedReadWriteMap{
   public:
      BoundedReadWriteMap(size_t max_size): max_size_(max_size), size_(0) {};
      bool get(int key, int &val);
      void put(int key, int val);
      void erase(int key);

   private:
      size_t max_size_;
      size_t size_;
      std::condition_variable size_cv_;
      std::unordered_map<int, int> map_;
      std::mutex lock_;
};

bool BoundedReadWriteMap::get(int key, int &val)
{
   bool ret = false;
   {
    std::lock_guard<std::mutex> lk(lock_);
    auto found = map_.find(key);
    if (found == map_.end()) {
       return ret;
    }
    val = found->second;
    ret = true;
   }
   return ret;
}

void BoundedReadWriteMap::put(int key, int val)
{
   std::unique_lock<std::mutex> cv_lk(lock_);
   if (size_ == max_size_) {
      std::cout << "waiting on condition variable, size = " << size_ << std::endl;
      size_cv_.wait(cv_lk, [this]() { return (size_ < max_size_); });
      std::cout << "woke up from condition variable, size = " << size_ << std::endl;
   }

   auto result = map_.insert(std::pair<int, int>(key, val));
   if (!result.second) {
      map_[key] = val;
   } else {
      size_++;
   }
}

void BoundedReadWriteMap::erase(int key)
{
  int cnt = 0;
  {
    std::cout << " erase waiting for lock " << std::endl;
    std::unique_lock<std::mutex> lk(lock_);
    cnt = map_.erase(key);
    std::cout << " erase returns, cnt = " << cnt << std::endl;
    if (cnt > 0) {
       size_ -= cnt;
       // unlock here
       lk.unlock();
       size_cv_.notify_one();
    }
  }
}

class SafePrint {
   public:
      void print(int id, int key, int val);
   private:
      std::mutex print_lock_;
};

void SafePrint::print(int id, int key, int val)
{
   {
      std::lock_guard<std::mutex> lk(print_lock_);
      std::cout << "id: " << id << " key: " << key << " val: " << val << std::endl;
   }
}

void thread_func(BoundedReadWriteMap& bound_map, SafePrint& printer, int id)
{
   int i = 1;
   while(i < 1000) {
      int key = i * id;
      int val_in = i;
      printer.print(id, key, val_in);
      bound_map.put(key, val_in);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      int val;
      if (bound_map.get(key, val)) {
        printer.print(id, key, val);
      }
      i++;
   }
}

void erase_thread_func(BoundedReadWriteMap& bound_map, SafePrint& printer, int id)
{
   int i = 1;
   while(i < 1000) {
      int key = i * 10;
      int val_in = i;
      printer.print(10, -1*key, -1*key);
      int val;
      if (bound_map.get(key, val)) {
        bound_map.erase(key);
      }
      key = i * 20;
      val_in = i;
      printer.print(20, -1*key, -1*key);
      if (bound_map.get(key, val)) {
        bound_map.erase(key);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      i++;
   }
}

int main()
{
   BoundedReadWriteMap bound_map(4);
   SafePrint printer;
   std::thread t1(thread_func, std::ref(bound_map), std::ref(printer), 10);
   std::thread t2(thread_func, std::ref(bound_map), std::ref(printer), 20);
   std::thread terase(erase_thread_func, std::ref(bound_map), std::ref(printer), 20);
  
   t1.join(); 
   t2.join(); 
   terase.join(); 
   
   return 0;
}
