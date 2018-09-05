//
//  main.cpp
//  Trie
//
//  Created by Anil Gathala on 3/18/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include <iostream>
#include "Trie.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Trie *trie = new Trie();
    trie->putKey("science", 95);
    trie->putKey("social", 90);
    trie->putKey("math", 100);
    int val;
    trie->getKey("science", &val);
    std::cout << "lookup: science = " << val << std::endl;
    
    trie->getKey("social", &val);
    std::cout << "lookup: social = " << val << std::endl;
    
    trie->getKey("math", &val);
    std::cout << "lookup: math = " << val << std::endl;
    
    trie->deleteKey("math");
    trie->getKey("math", &val);
    std::cout << "lookup(after delete): math = " << val << std::endl;
    
    std::vector<std::string> allkeys = trie->getAllKeys();
    
    std::cout << " all keys: " << std::endl;
    for (auto &x: allkeys) {
        std::cout << x << std::endl;
    }
    
    std::string res = trie->longestPrefixOf("social message");
    std::cout << "longest prefix of -- social message -- is: " << res << std::endl;
    
    res = trie->longestPrefixOf("science fiction");
    std::cout << "longest prefix of -- science fiction -- is: " << res << std::endl;
    
    //std::cout << " keys with prefix: -- sc -- " << std::endl;
    std::vector<std::string> vec = trie->keysWithPrefix("s");
    std::cout << " keys with prefix: -- s -- " << std::endl;
    for (auto &x: vec) {
        std::cout << std::endl;
        std::cout << x << std::endl;
    }
    
    vec = trie->keysThatMatch("s......");
    std::cout << " keys that match: -- s...... (6 dots) -- " << std::endl;
    for (auto &x: vec) {
        std::cout << std::endl;
        std::cout << x << std::endl;
    }
    
    delete trie; //calls the constructor
    
    
    return 0;
}
