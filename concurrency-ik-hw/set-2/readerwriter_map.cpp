// Simple example of shared_mutex
//

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
//#include <utility>
//#include <iterator>

class ReadWriteMap{
   public:
      bool get(int key, int &val) const;
      void put(int key, int val);

   private:
      std::unordered_map<int, int> map_;
      mutable std::shared_mutex lock_;
};

bool ReadWriteMap::get(int key, int &val) const
{
   bool ret = false;
   {
    std::shared_lock<std::shared_mutex> lk(lock_);
    auto found = map_.find(key);
    if (found == map_.end()) {
       return ret;
    }
    val = found->second;
    ret = true;
   }
   return ret;
}

void ReadWriteMap::put(int key, int val)
{
   {
    // TODO: both unique_lock / lock_guard work here, below
    //std::unique_lock<std::shared_mutex> lk(lock_);
    std::lock_guard<std::shared_mutex> lk(lock_);
    auto result = map_.insert(std::pair<int, int>(key, val));
    if (!result.second) {
       map_[key] = val;
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

void thread_func(ReadWriteMap& rw_map, SafePrint& printer, int id)
{
   int i = 1;
   while(i < 1000) {
      int key = i * id;
      int val_in = i;
      rw_map.put(key, val_in);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      int val;
      if (rw_map.get(key, val)) {
        printer.print(id, key, val);
      }
      i++;
   }
}
int main()
{
   ReadWriteMap rw_map;
   SafePrint printer;
   std::thread t1(thread_func, std::ref(rw_map), std::ref(printer), 10);
   std::thread t2(thread_func, std::ref(rw_map), std::ref(printer), 20);
  
   t1.join(); 
   t2.join(); 

   return 0;
}
