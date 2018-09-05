//
//  Member.cpp
//  compareobj
//
//  Created by Anil Gathala on 3/16/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include "Member.hpp"


int Compare(const Member *m1, const Member *m2) {
    if (m1->getAge()== m2->getAge()) {
        return 0;
    }
    
    if (m1->getAge() < m2->getAge()) {
        return -1;
    }
    
    return 1;
}

bool Member::operator< (const Member &m) const {
    std::cout << "operator<: " << "age1 = " << this->getAge() << " age2 = " << m.getAge() << std::endl;
    if (this->getAge() > m.getAge()) {
        return false;
    }
    return true;
}
