//
//  main.cpp
//  InsertOnlyTrie
//
//  Created by Anil Gathala on 4/25/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "InsertOnlyTrie.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    if (argc != 2) {
        cout << "usage: ./a.out <ip_filename>" << endl;
    }
    std::ifstream infile(argv[1]);
    
    struct TrieNode *root = getNode();
    
    // Construct trie
    string line;
    while (std::getline(infile, line)) {
        insert(root, line);
    }
    int numNodes = getNumNodes();

    cout << argv[1] << " " << numNodes << endl;
    return 0;
}
