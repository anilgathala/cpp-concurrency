//
//  uniquepointer.cpp
//  smartpointers
//
//  Created by Anil Gathala on 3/19/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "uniquepointer.hpp"

class Car {
private:
    std::string name_;
    int numDoors_;
public:
    Car(std::string name, int numDoors): name_(name), numDoors_(numDoors) {
        std::cout << "Car constructor!" << std::endl;
    }
    ~Car() {
        std::cout << "Car destructor!" << std::endl;
    }
    std::string getName() { return name_; }
    int getNumDoors() { return numDoors_;}
};

void resetUniquePtr() {
    // creating via raw pointer
    std::unique_ptr<Car> car_ptr(new Car("Camry", 4));
    
    car_ptr.reset();
    
    std::cout << "after reset: " << std::endl;
    if (!car_ptr) {
        std::cout << " ptr is empty!" << std::endl;
    }
    if (car_ptr == nullptr) {
        std::cout << " ptr is empty!" << std::endl;
    }
    
}

void copyUniquePtr() {
    // copy doesn't work, you need to use move
    std::unique_ptr<Car> ptr1 (new Car("Honda", 2));
    //std::unique_ptr<Car> ptr2 = ptr1; // thows an error, cannot copy
    std::unique_ptr<Car> ptr3;
    //ptr3 = ptr1; // cannot copy throws an error
}

void moveUniquePtr() {
    // copy doesn't work, you need to use move
    std::unique_ptr<Car> ptr1 (new Car("Honda", 2));
    std::unique_ptr<Car> ptr2;
    std::cout << "before move ptr: " << std::endl;
    if (!ptr1) {
        std::cout << " ptr1 is empty!" << std::endl;
    } else {
        std::cout << " ptr1 is NOT empty!" << std::endl;
    }
    if (!ptr2) {
        std::cout << " ptr2 is empty!" << std::endl;
    } else {
        std::cout << " ptr2 is NOT empty!" << std::endl;
    }
    
    ptr2 = std::move(ptr1);
    
    std::cout << "after move ptr: " << std::endl;
    if (!ptr1) {
        std::cout << " ptr1 is empty!" << std::endl;
    } else {
        std::cout << " ptr1 is NOT empty!" << std::endl;
    }
    if (!ptr2) {
        std::cout << " ptr2 is empty!" << std::endl;
    } else {
        std::cout << " ptr2 is NOT empty!" << std::endl;
    }
    
    std::cout << "ptr2->name: " << ptr2->getName() << std::endl;

}

void releaseUniquePtr() {
    std::unique_ptr<Car> ptr(new Car("Lexus", 4));
    Car * rawptr = ptr.release();
    if (rawptr) {
        std::cout << "after release, using raw ptr, name: "
            << rawptr->getName() << "; num doors = "
            << rawptr->getNumDoors() << std::endl;
    }
    delete rawptr;  // if you comment this line, destrictor will not be called
                    // which means, after "release()" has been called,
                    // raw ptr needs to be managed / delete by app code
}

void createAndUse() {
    // creating via raw pointer
    std::unique_ptr<Car> car_ptr(new Car("Camry", 4));
    
    // this will throw a compilation error
    // std::unique_ptr<Car> ptr2 = new Car("Camry", 4);
    
    
    std::cout << "car: name = " << car_ptr->getName()
        << "; num of doors = " << car_ptr->getNumDoors() << std::endl;
}

void emptyUniquePtr() {
    std::unique_ptr<Car> ptr; //ptr is empty, doesn't point anywhere meaningful
    if (!ptr) {
        std::cout << " ptr is empty!" << std::endl;
    }
    if (ptr == nullptr) {
        std::cout << " ptr is empty!" << std::endl;
    }
    return;
}

// TODO: effective manipulation of strings (concatenating ints, floats and chars to strings)
void vectorOfUniquePtrs() {
    std::vector<std::unique_ptr<Car>> vec;
    for ( int i = 0; i < 4; i++) {
        std::unique_ptr<Car> tmp(new Car("my car", 2*(i+1)));
        //vec.push_back(tmp); --> build fails
        vec.push_back(std::move(tmp));
    }
    
    for (auto &c: vec) {
        std::cout << "name: " << c->getName() << "; #doors: " << c->getNumDoors() << std::endl;
    }
    
    std::cout << " ----------- " << std::endl;
    std::unique_ptr<Car> holder;
    while(!vec.empty()) {
        holder = std::move(vec.back());
        std::cout << "name: " << holder->getName() << "; #doors: " << holder->getNumDoors() << std::endl;
        // now top of the vector has a "nullptr" unique ptr
        // let us pop it out
        vec.pop_back();
    }
    
//    std::vector<std::unique_ptr<Car>> vec;
//    std::unique_ptr<Car> holder;
//    
    std::cout << " ----------- " << std::endl;
    
    for ( int i = 0; i < 4; i++) {
        vec.push_back(std::unique_ptr<Car>(new Car("Tesla", 2*(i+1))));
    }
    
    for (auto &c: vec) {
        std::cout << "name: " << c->getName() << "; #doors: " << c->getNumDoors() << std::endl;
    }
    
    std::cout << " ----------- " << std::endl;

    while(!vec.empty()) {
        std::cout << " ----------- " << std::endl;
        if (!holder) {
            std::cout << "holder nullptr to start with" << std::endl;
        }
        holder = std::move(vec.back()); // the that holder was previously holding will be freed here
        std::cout << "name: " << holder->getName() << "; #doors: " << holder->getNumDoors() << std::endl;
        // now top of the vector has a "nullptr" unique ptr
        // let us pop it out
        vec.pop_back();
        // holder.release();
        std::cout << " ----------- " << std::endl;
    }
    
    std::cout << " returning from func! (watch out freeing obj held by --holder-- variable) " << std::endl;
}



void demo_unqiue_pointer() {
    createAndUse();
    emptyUniquePtr();
    resetUniquePtr();
    moveUniquePtr();
    releaseUniquePtr();
    vectorOfUniquePtrs();
}
