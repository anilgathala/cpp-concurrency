//
//  Member.hpp
//  compareobj
//
//  Created by Anil Gathala on 3/16/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#ifndef Member_hpp
#define Member_hpp

#include <iostream>
#include <stdio.h>
#include <string.h>


class Member {
private:
    std::string name_;
    int age_;
public:
    Member(std::string name, int age): name_(name), age_(age) {};
    int getAge() const { return age_; }
    std::string getName() { return name_; }
    //int Compare(const Member &m);
    void setName(std::string name) { name_ = name;}
    void setAge(int age) { age_ = age;}
    bool operator< (const Member &m) const;
};

int Compare(const Member *m1, const Member *m2);

#endif /* Member_hpp */
