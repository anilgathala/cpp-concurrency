//
//  InsertOnlyTrie.cpp
//  InsertOnlyTrie
//
//  Created by Anil Gathala on 4/25/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include "InsertOnlyTrie.hpp"

// C++ implementation of search and insert
// operations on Trie
//#include <bits/stdc++.h>
#include <unordered_map>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

static int num_nodes = 0;


// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
    
    pNode->isEndOfWord = false;
    
//    for (int i = 0; i < ALPHABET_SIZE; i++)
//        pNode->children[i] = NULL;
    num_nodes++;
    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    
    for (int i = 0; i < key.length(); i++)
    {
        //int index = key[i] - 'a';
        auto itr = pCrawl->children.find(key[i]);
        if (itr == pCrawl->children.end()) {
            //miss
            pCrawl->children.insert(make_pair(key[i], getNode()));
        }
        
        pCrawl = pCrawl->children[key[i]];
    }
    
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    
    for (int i = 0; i < key.length(); i++)
    {
        auto itr = pCrawl->children.find(key[i]);
        if (itr != pCrawl->children.end()) {
            //miss
            return false;
        }
        
        pCrawl = pCrawl->children[key[i]];
    }
    
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

int getNumNodes() {
    return num_nodes;
}
