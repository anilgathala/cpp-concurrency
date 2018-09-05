//
//  SuffixArray.cpp
//  SuffixArray
//
//  Created by Anil Gathala on 3/12/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include "SuffixArray.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

bool Compare(const Suffix *s1, const Suffix *s2) {
    std::cout << __func__ << ": " << s1->toString() << "; " << s2->toString() << std::endl;
    //return s1->toString().compare(s2->toString());
    int len = std::min(s1->toString().length(), s2->toString().length());
    for (int i = 0; i <  len; i++) {
        std::cout << __func__ << ": " << s1->toString()[i] << "; " << s2->toString()[i] << std::endl;
        if (s1->toString()[i] > s2->toString()[i]) {
            std::cout << "returning: " << (s1->toString()[i] - s2->toString()[i]) << std::endl;
            //return (s1->toString()[i] - s2->toString()[i]);
            return false;
        }
        else if (s1->toString()[i] < s2->toString()[i]) {
            std::cout << "returning " << (s1->toString()[i] - s2->toString()[i]) << std::endl;
            //return (s1->toString()[i] - s2->toString()[i]);
            return true;
            //return -1;
        }
    }
    std::cout << "s1.len = " << s1->toString().length() << " s2.len = "<< s2->toString().length() << std::endl;
    
    int len1 = (int) s1->toString().length();
    int len2 = (int) s2->toString().length();
    
    if (len1  == len2) {
        return true;
    }
    if (len1 > len2) {
        return false;
    }
    return true;
    //return (len1 - len2);
//    if ( s1->toString() < s2->toString()) {
//        return 1;
//    }
//    if (s1->toString() == s2->toString()) {
//        return 0;
//    }
//    return -1;
}



Suffix::Suffix(std::string & str, unsigned long idx) {
    text = str;
    index = idx;
}

unsigned long Suffix::getLength() {
    return text.length() - index;
}

char Suffix::charAt(int i) {
    return text[i];
}

std::string Suffix::toString() const {
    return text.substr(index);
}

unsigned long Suffix::getIndex() {
    return index;
}


SuffixArray::SuffixArray(std::string text) {
    long n = text.length();
    for (auto i = 0; i < n; i++) {
        suffixes.push_back(new Suffix(text, i));
    }
    std::cout << "before sort -------- " << std::endl;
    displayAll();
    // call sort, to sort these suffixes in place
    sort(suffixes.begin(), suffixes.end(), Compare);
    std::cout << "after sort -------- " << std::endl;
    displayAll();
}

unsigned long SuffixArray::getIndex(int i) {
    return suffixes[i]->getIndex();
}

unsigned long SuffixArray::getLength() {
    return suffixes.size();
}

std::string SuffixArray::select(int i) {
    return suffixes[i]->toString();
}

// TODO: return the len of largest common prefix of suffixes[i] and suffixes[i-1]
int SuffixArray::lcp(int i) {
    std::string str1 = suffixes[i]->toString();
    std::string str2 = suffixes[i - 1]->toString();
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    int cnt = 0;
    size_t j = 0;
    while ( j < len1 && j < len2 && str1[j] == str2[j]) {
        j++;
        cnt++;
    }
    return cnt;
}

int SuffixArray::findRank(std::string key, int begin, int end, int pos) {
    if (pos == key.length() - 1) {
        return begin;
    }
    if (begin == end) {
        return begin;
    }
    
    int mid = (begin + end) / 2;
    if (key[pos] > suffixes[mid]->toString()[pos]) {
        return findRank(key, mid + 1, end, pos);
    }
    if (key[pos] == suffixes[mid]->toString()[pos]) {
        if (pos == key.length() - 1) {
            return mid;
        }
        return findRank(key, mid + 1, end, pos + 1);
    }
    
    
    return findRank(key, begin, mid - 1, pos);
    
}

// TODO: rank of a string is the index of first possible suffix with that string
int SuffixArray::rank(std::string key) {
    // TODO: fix all these unsigned long business
    return findRank(key, 0, (int)getLength() - 1, 0);
}

// TODO: rank of a string is the index of first possible suffix with that string
void SuffixArray::displayAll() {
    auto len = getLength();
    for(auto i = 0; i < len; i++) {
        std::cout << "[" << i << "]: " << suffixes[i]->toString() << std::endl;
    }
}
