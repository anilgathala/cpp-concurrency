//
//  main.cpp
//  template-constructor
//
//  Created by Anil Gathala on 6/7/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include <iostream>

template<class T> class A
{
public:
    
    A(int a){};
    void start(int i) {};
};

template<class T> class B : public A<T>
{
public:  // THIS
    typedef std::function<void (const bool & is_final)> MyFunc;
    B(int a, int b = 0): A<T>(a){};
    void run(MyFunc &fn) {
        bool flag = true;
        fn(flag);
    }
};

//template<class T> B<T>::B(int a, int b /* =0 */)  
//{
//    
//}

class C : public B<int>
{
    using B::B;
public:

    void sample(const bool & flag) {
        std::cout << "flag = " << flag << std::endl;
    }
    B::MyFunc cb = std::bind(&C::sample, this, std::placeholders::_1);

};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    C obj(5);
    C obj2(5, 3);
    obj.start(10);
    B<int> o3(10);
    o3.start(20);
    
    o3.run(obj.cb);
    return 0;
}
