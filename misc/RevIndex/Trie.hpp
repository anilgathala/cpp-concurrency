//
//  Trie.hpp
//  RevIndex
//
//  Created by Anil Gathala on 3/23/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <stdio.h>
#include <unordered_map>
#include <vector>

/// Assumption: alphabet is ascii - chars 0 to 255

const unsigned short alphabet_size = 256; // ascii

class Node {
public:
    // these node pointers in links live until the death of the class / program
    // so we do not need to manage them using smart pointers
    std::unordered_map<char, Node*> links;
    //int val;
    std::vector<uint64_t> *value_vec;
    bool isKey;
    
    Node() {
        //links = new std::unordered_map<char, Node*>();
        for (unsigned short i = 0; i < alphabet_size; i++) {
            links.insert(std::make_pair((char)i, nullptr));
        }
        isKey = false;
        value_vec = nullptr; // new std::vector<uint64_t>();
    }
    
    ~Node() {
        if (value_vec != nullptr) {
            delete value_vec;
        }
        
        for (auto &x: links) {
            if (x.second != nullptr) {
                delete x.second;
            }
        }
    }
    
    bool haveChildNodes() {
        for (auto &x: links) {
            if (x.second != nullptr) {
                return true;
            }
        }
        return false;
    }
};

class Trie {
private:
    
    Node* root;
    int numKeys;
    
    void doPutKey(std::string key, int pos, int64_t val, Node* head);
    std::vector<uint64_t> doGetKey(std::string key, int pos, Node* head);
    Node* doDeleteKey(std::string key, int pos, Node * head);
    void doGetAllKeys(Node *head, std::string &key, int pos, std::vector<std::string> &vec);
    void getKeysThatMatch(Node *head, std::string s, int pos, std::string key, std::vector<std::string> &vec);
    void deleteAllNodes(Node *head);
    
public:
    Trie() {
        root = new Node();
        numKeys = 0;
    }
    ~Trie() {
        // delete all nodes
        deleteAllNodes(root);
    }
    //Node* getRoot() { return root;};
    void putKey(std::string key, uint64_t val);
    std::vector<uint64_t> getKey(std::string key);
    //int deleteKey(std::string key);
    void deleteKey(std::string key);
    bool contains(std::string key);
    std::vector<std::string> getAllKeys();
    // TODO: a better way to return a vector
    //       in the above, we are copying the entire vector upon return
    bool isEmpty();
    int size();
    
    std::string longestPrefixOf(std::string s);
    std::vector<std::string> keysWithPrefix(std::string s);
    std::vector<std::string> keysThatMatch(std::string s);
};

#endif /* Trie_hpp */
