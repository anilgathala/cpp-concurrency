/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <memory>

using namespace std;

class Point {
public:
  int x_;
  int y_;
  Point(int x, int y): x_(x), y_(y) {};

};

struct cmp {
   bool operator()(std::shared_ptr<Point>& p1, std::shared_ptr<Point>& p2) {
      // std::cout << " called!" << std::endl;
      return (p1->x_ > p2->x_);
  } 
};


int main()
{
    cout<<"Hello World" << std::endl;
    std::priority_queue<std::shared_ptr<Point>, std::vector<std::shared_ptr<Point>>, cmp> pq;
    
    pq.push(make_shared<Point>(10, 2));
    pq.push(make_shared<Point>(1, 3));
    pq.push(make_shared<Point>(5, 4));
    pq.push(make_shared<Point>(30, 2));
    pq.push(make_shared<Point>(60, 2));
    pq.push(make_shared<Point>(8, 2));
    
    while(! pq.empty()) {
        std::cout << "(" << pq.top()->x_ << ", " << pq.top()->y_ << ")" << std::endl;
        pq.pop();
    }
    
    return 0;
}
