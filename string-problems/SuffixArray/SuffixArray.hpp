//
//  SuffixArray.hpp
//  SuffixArray
//
//  Created by Anil Gathala on 3/12/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#ifndef SuffixArray_hpp
#define SuffixArray_hpp

#include <stdio.h>
#include <string>
#include <vector>

// TODO: how to define a class inside another class in cpp

class Suffix {
private:
    std::string text;
    unsigned long index;
public:
    Suffix(std::string & str, unsigned long idx);
    
    unsigned long getLength();

    char charAt(int i);

    std::string toString() const;

    unsigned long getIndex();
    
    int Compare(const Suffix *s1, const Suffix *s2) const;

    // TODO: compareTo method
    
};

class SuffixArray {
private:
    std::vector<Suffix*> suffixes;
    int findRank(std::string key, int begin, int end, int pos);
public:
    
    SuffixArray(std::string text);

    unsigned long getIndex(int i);

    unsigned long getLength();
    
    std::string select(int i);
    
    int lcp(int i); //TODO: return the largest common prefix of suffixes[i] and suffixes[i+1]
    
    int rank(std::string key); // TODO: rank of a string is the index of first possible suffix with that string
    void displayAll();
};

#endif /* SuffixArray_hpp */
