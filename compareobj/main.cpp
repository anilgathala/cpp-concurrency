//
//  main.cpp
//  compareobj
//
//  Created by Anil Gathala on 3/16/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "Member.hpp"

void displayMembers(std::vector<Member*> &members) {
    for(auto itr = members.begin(); itr != members.end(); itr++) {
        std::cout << "name: " << (*itr)->getName() << " ;age = " << (*itr)->getAge() << std::endl;
    }
}

void displayMemberList(std::vector<Member> &members) {
    for(auto itr = members.begin(); itr != members.end(); itr++) {
        std::cout << "name: " << (*itr).getName() << " ;age = " << (*itr).getAge() << std::endl;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::vector<Member*> members;
    
    //int i;
    for(int i = 1; i < 10; i++)
    {
        std::stringstream ss;
        ss << i;

        members.push_back(new Member("John Lewis " + ss.str(), (1000 / i)));
    }
    
    std::cout << " unsorted list ------- " << std::endl;
    
    // display
    displayMembers(members);
    
    
    // sort
    sort(members.begin(), members.end(), Compare);
    //sort(members.begin(), members.end());
    
    std::cout << " sorted list ------- " << std::endl;
    // display
    displayMembers(members);
    
    std::vector<Member> memberList;
    for(int i = 1; i < 10; i++)
    {
        std::stringstream ss;
        ss << i;
        
        memberList.push_back(*(new Member("John Lewis " + ss.str(), (1000 / i))));
    }
    
    sort(memberList.begin(), memberList.end());
    
    std::cout << " sorted member-list ------- " << std::endl;
    displayMemberList(memberList);
    
    
    
    return 0;
}
