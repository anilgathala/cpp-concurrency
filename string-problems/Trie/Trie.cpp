//
//  Trie.cpp
//  Trie
//
//  Created by Anil Gathala on 3/18/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include "Trie.hpp"

#include <iostream>
#include <string>
#include <vector>


// we want to be careful if we want to use smart pointers to the "root" of the trie
// as we do not want it to be destroyed when it goes out of scope of a function
// we do NOT need smart pointers here.
// unique_ptr - does not work
// shared_ptr - too much overhead

void Trie::doPutKey(std::string key, int pos, int val, Node* head) {
    if (pos == key.length()) {
        return;
    }
    //std::cout << "processing, pos = " << pos << " key[pos] = " << key[pos] << std::endl;
    auto itr = head->links.find(key[pos]);

    // this find will always be succ'ful as
    // Node's constructor fills these in apriori
    if (itr == head->links.end()) {
        std::cout << " links slot for char " << key[pos] << " is missing! " << std::endl;
        return;
    }
    
    Node* tmp;
    tmp = itr->second;
    if (tmp == nullptr) {
        tmp = new Node();
        // IMPORTANT NOTE:
        // In c++, if you were to update 'val' of an entry in an unordered_map
        // you NEED to use "array" style updating map[c] = val;
        // calling "insert" will not work - it wil quitely not update the val
        // for e.g., try: head->links->insert(std::make_pair((char)key[pos], tmp));
        head->links[(char)key[pos]] = tmp;
    }
    
    if (pos == key.length() - 1) {
        tmp->isKey = true;
        tmp->val = val;
        numKeys++;
        std::cout << "marking node as key " << key[pos] << std::endl;
        return;
    }
    
    doPutKey(key, pos + 1, val, std::move(tmp));
}


void Trie::putKey(std::string key, int val) {
    doPutKey(key, 0, val, root);
    return;
}

// TODO: check how do we do this the right way --> "int *val"
//       returning both val as well as telling if the val is valid
//       the following is a popular c style
bool Trie::doGetKey(std::string key, int pos, Node * head, int *val) {
    *val = -1;
    if (pos == key.length()) {
        return false;
    }
    auto itr = head->links.find((char)key[pos]);
    if (itr->second == nullptr) {
        std::cout << "node is null, " << key[pos] << std::endl;
        return false;
    }
    
    if (pos == key.length() - 1) {
        //std::cout << "last char, " << key[pos] << " isKey: " << itr->second->isKey << std::endl;

        if (itr->second->isKey) {
            *val = itr->second->val;
            return true;
        }
        return false;
    }
    
    return doGetKey(key, pos + 1, itr->second, val);
    
}

bool Trie::getKey(std::string key, int *val) {
    return doGetKey(key, 0, root, val);
}


Node* Trie::doDeleteKey(std::string key, int pos, Node * head) {
    if (head == nullptr) {
        return nullptr;
    }
    
    if (pos == key.length()) {
        head->isKey = false;
        head->val = -1;
        numKeys--;
    } else {
        char c = key[pos];
        head->links[c] = doDeleteKey(key, pos + 1, head->links[c]);
    }
    
    if (head->isKey) {
        return head;
    }
    
    if (!head->haveChildNodes()) {
        delete head;
        head = nullptr;
    }
    return head;
}


void Trie::deleteKey(std::string key) {
    doDeleteKey(key, 0, root);
}

bool Trie::contains(std::string key) {
    int val;
    return doGetKey(key, 0, root, &val);
}


bool Trie::isEmpty() {
    return root->haveChildNodes();
}

int Trie::size() {
    return numKeys;
}

void Trie::doGetAllKeys(Node *head, std::string &key, int pos, std::vector<std::string> &vec) {
    if (head == NULL) {
        return;
    }

    if (head->isKey) {
        std::cout << "head, key = " << key << std::endl;
        vec.push_back(key);
    }

    for (int i =0; i < alphabet_size; i++) {
        if (head->links[(char)i] != nullptr) {

            key.push_back((char)i);

            doGetAllKeys(head->links[(char)i], key, pos + 1, vec);
            
            key.pop_back();
        }
    }
}

std::vector<std::string> Trie::getAllKeys() {
    std::vector<std::string> vec;
    std::string key = " ";
    doGetAllKeys(root, key, 0, vec);
    return vec;
}

int getLengthOfKeyWhichIsAPrefixOf(Node *head, int pos, std::string s, int length) {
    if (head == nullptr) {
        return length;
    }
    
    if (pos == s.length()) {
        return length;
    }
    
    auto itr = head->links.find((char)s[pos]);
    
    if (itr == head->links.end()) {
        return length;
    }
    
    if ((*itr).second == nullptr) {
        return length;
    }
    
    if ((*itr).second->isKey) {
        length = pos + 1;
    }
    
    return getLengthOfKeyWhichIsAPrefixOf(head->links[(char)s[pos]], pos + 1, s, length);
    
}

// longest key which is a prefix of argument, 's'
std::string Trie::longestPrefixOf(std::string s) {
    int len = getLengthOfKeyWhichIsAPrefixOf(root, 0, s, 0);
    return s.substr(0, len);
}

std::vector<std::string> Trie::keysWithPrefix(std::string s) {
    Node *tmp = root;
    std::vector<std::string> vec;
    int pos = 0;
    auto itr = tmp->links.find(s[pos]);
    while (pos < s.length() && itr != tmp->links.end() && itr->second != nullptr) {
        tmp = tmp->links[s[pos]];
        pos++;
        itr = tmp->links.find(s[pos]);
    }
    
    doGetAllKeys(tmp, s, (int) s.length(), vec);
    
    return vec;
}

void Trie::getKeysThatMatch(Node* head, std::string s, int pos, std::string key, std::vector<std::string> &vec) {
    
    if (head == nullptr) {
        return;
    }
    
    if (head->isKey) {
        vec.push_back(key);
    }
    
    if (pos == s.length()) {
        return;
    }
    
    
    
    auto itr = head->links.find(s[pos]);
    
    if (itr == head->links.end()) {
        if (s[pos] != '.') {
            return;
        }
    }
    
    if (s[pos] == '.') {
        for (unsigned short i = 0; i < alphabet_size; i++) {
            key.push_back((char)i);
            getKeysThatMatch(head->links[(char)i], s, pos + 1, key, vec);
            key.pop_back();
        }
    } else {
        key.push_back(s[pos]);
        getKeysThatMatch(head->links[(char)s[pos]], s, pos + 1, key, vec);
        key.pop_back();
    }
    return;
}

std::vector<std::string> Trie::keysThatMatch(std::string s) {
    std::vector<std::string> vec;
    std::string key;
    getKeysThatMatch(root, s, 0, key, vec);
    return vec;
}

void Trie::deleteAllNodes(Node *head) {
    std::cout << "deleteAllNodes: " << std::endl;
    if (head == nullptr) {
        return;
    }
// The following loop is deleted/commented as the equivalent of this
// will be done in Node's destructor
//    for (auto &x: head->links) {
//        deleteAllNodes(x.second);
//    }
    delete head;
    return;
}
