//
//  main.cpp
//  SuffixArray
//
//  Created by Anil Gathala on 3/12/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include <iostream>
#include <string>

#include "SuffixArray.hpp"

// TODO: implement rank

void print_longest_repeated_substring(std::string *str) {
    SuffixArray *sa = new SuffixArray(*str);
    std::string lrs = "";
    size_t len = str->length();
    unsigned long cnt = 0;
    for (size_t i = 1; i < len; i++) {
        cnt = sa->lcp((int)i);
        if (cnt > lrs.length()) {
            lrs = str->substr(sa->getIndex((int)i), cnt);
        }
    }
    std::cout << "lrs = " << lrs << std::endl;
    
}

int simple_lcp(std::string s1, std::string s2) {
    int i = 0;
    int len = (int) std::min(s1.length(), s2.length());
    //std::cout << __func__ << ": len = " << len << std::endl;
    for (i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            return i;
        }
    }
    return len;
}

void simple_lrs(std::string *str) {
    int i, j;
    int len = (int) str->length();
    int max = -1;
    int prefix_len = -1;
    int start_pos = -1;
    for ( i = 0; i < len; i++) {
        for ( j = i + 1; j < len; j++) {
            prefix_len = simple_lcp(str->substr(i), str->substr(j));
            if (prefix_len > max) {
                start_pos = i;
                max = prefix_len;
            }
        }
    }
    if (start_pos > -1) {
        std::cout << " simple_lrs: " << str->substr(start_pos, max) << std::endl;
    }
    else {
        std::cout << " simple_lrs: no lrs!" << std::endl;
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::string *str;
    char s[1024];
    std::cout << "Hello, World!\n" << std::endl;
    std::cin.getline(s, 1024);
    std::cout << "you entered: " << s << std::endl;
    str = new std::string(s);
    std::cout << "you entered: " << *str << std::endl;

    print_longest_repeated_substring(str);
    
    std::cout << "rank(to): ";
    
    SuffixArray *sa = new SuffixArray(*str);
    std::cout << "from main: " << std::endl;
    sa->displayAll();
    //std::cout << "lcp(10): " << sa->lcp(10);
    std::cout << "rank(to): " << sa->rank("to") << std::endl;
    
    simple_lrs(str);
    return 0;
}
