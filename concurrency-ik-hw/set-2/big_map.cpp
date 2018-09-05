// Simple example of shared_mutex
//

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <vector>
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
    // TODO: check if lock_guard can be used
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

class BigMap {
   public:
      BigMap(size_t map_vec_size);
      std::shared_ptr<ReadWriteMap> get_small_map(int key);
      bool get(int key, int &val);
      void put(int key, int val);
   private:
      std::vector<std::shared_ptr<ReadWriteMap>> map_vec_;
      size_t  map_vec_size_;
      std::mutex map_vec_lock_;
};

std::shared_ptr<ReadWriteMap> BigMap::get_small_map(int key)
{
   {
      std::shared_ptr<ReadWriteMap> map;
      std::lock_guard<std::mutex> lk(map_vec_lock_);
      if (map_vec_[key % map_vec_size_]) {
         map = map_vec_[key % map_vec_size_];
      } else {
        map = std::make_shared<ReadWriteMap>();
        map_vec_[key % map_vec_size_] = map;
      }
      return map;
   }
}

BigMap::BigMap(size_t map_vec_size): map_vec_size_(map_vec_size)
{
   for( int i = 0; i < map_vec_size_; i++ ) {
      //auto map = std::make_shared<ReadWriteMap>();
      map_vec_.push_back(nullptr);
   }
}

bool BigMap::get(int key, int &val)
{
   if (key < 0) {
      return false;
   }
   auto map = get_small_map(key);
   return map->get(key, val);
}

void BigMap::put(int key, int val)
{
   if (key < 0) {
      return;
   }
   auto map = get_small_map(key);
   map->put(key, val);
}


void thread_func(BigMap& big_map, SafePrint& printer, int id)
{
   int i = 1;
   while(i < 1000) {
      int key = i * id;
      int val_in = i;
      big_map.put(key, val_in);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      int val;
      if (big_map.get(key, val)) {
        printer.print(id, key, val);
      }
      i++;
   }
}

int main()
{
   BigMap big_map(10);
   SafePrint printer;
   std::thread t1(thread_func, std::ref(big_map), std::ref(printer), 10);
   std::thread t2(thread_func, std::ref(big_map), std::ref(printer), 20);
  
   t1.join(); 
   t2.join(); 

   return 0;
}
