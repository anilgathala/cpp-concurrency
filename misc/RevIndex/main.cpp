//
//  main.cpp
//  RevIndex
//
//  Created by Anil Gathala on 3/23/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

#include "Trie.hpp"

const std::string filename = "/Users/agathala/workspace/cppwork/data/readme.txt";

/// Implementation of rev Index with unordered_map

std::unordered_map<std::string, std::vector<uint64_t>*> revIndexMap;

void buildRevIndexWithMap(const std::string fname) {
    std::ifstream file;
    file.open (fname);
    if (!file.is_open()) return;
    uint64_t offset = 0;
    std::string word;
    while (file >> word)
    {
        offset = file.tellg();
        offset -= (word.length() - 1);
        std::cout<< "adding to map: " << word << " at offset: " << offset << std::endl;
        auto itr = revIndexMap.find(word);
        if (itr != revIndexMap.end()) {
            itr->second->push_back(offset);
        } else {
            std::vector<uint64_t> * vec = new std::vector<uint64_t>();
            vec->push_back(offset);
            revIndexMap.insert(make_pair(word, vec));
        }
        //offset += word.length();
    }
}

void displayIndexWithMap(std::string keyword) {
    //std::vector<=uint64_t> *vec = revIndexMap.find
    auto itr = revIndexMap.find(keyword);
    if (itr != revIndexMap.end()) {
        std::cout << " offsets for " << keyword << ": ";
        for (auto &x: (*(itr->second))) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "keyword: " << keyword << " not found!" << std::endl;
    }
}

/////////////////////////

/// rev index implementation using a trie

Trie revIndexTrie;

void buildRevIndexWithTrie(const std::string fname) {
    std::ifstream file;
    file.open (fname);
    if (!file.is_open()) return;
    uint64_t offset = 0;
    std::string word;
    while (file >> word)
    {
        offset = file.tellg();
        offset -= (word.length() - 1);
        
        std::cout<< "adding to trie: " << word << " at offset: " << offset << std::endl;
        revIndexTrie.putKey(word, offset);
    }
}

void displayIndexWithTrie(std::string keyword) {
    std::vector<uint64_t> vec = revIndexTrie.getKey(keyword);
    std::cout << " offsets for " << keyword << ": ";
    for (auto &x: vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

////////////////////

int main(int argc, const char * argv[]) {
    buildRevIndexWithMap(filename);
    displayIndexWithMap("complex");
    std::cout << "//////////////////////" << std::endl;
    buildRevIndexWithTrie(filename);
    displayIndexWithTrie("complex");
    std::cout << "//////////////////////" << std::endl;
    return 0;
}
