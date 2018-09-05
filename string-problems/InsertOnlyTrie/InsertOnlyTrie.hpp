//
//  InsertOnlyTrie.hpp
//  InsertOnlyTrie
//
//  Created by Anil Gathala on 4/25/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#ifndef InsertOnlyTrie_hpp
#define InsertOnlyTrie_hpp

#include <stdio.h>
#include <unordered_map>
#include <string>
using namespace std;

// trie node
struct TrieNode
{
    // struct TrieNode *children[ALPHABET_SIZE];
    std::unordered_map<char, struct TrieNode*> children;
    
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

struct TrieNode *getNode(void);
void insert(struct TrieNode *root, string key);
bool search(struct TrieNode *root, string key);

int getNumNodes();


#endif /* InsertOnlyTrie_hpp */
