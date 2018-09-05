//
//  snakestring.cpp
//  snakestring
//
//  Created by Anil Gathala on 3/20/18.
//  Copyright © 2018 Anil Gathala. All rights reserved.
//

#include "snakestring.hpp"

#include <iostream>

/*
 * Complete the function below.
 */

// Line #1: pick chars '2 + 4*i' in input string
//          and print 2 spaces, next char, 3 spaces, next char, 3 spaces, next char (2+4*i)
// Line #2: pick chars '1 + 2*i' in input string
//          and print 1 spaces, next char, 1 spaces, next char, 1 spaces, next char (1+2*i)
// Line #3: pick chars '0 + 4*i' in input string
//          and print 0 spaces, next char, 3 spaces, next char, 3 spaces, next char (0+4*i)

void printSpaces(int num) {
    while (num > 0) {
        std::cout << " ";
        num--;
    }
}

void printLine(std::string str, int cbase, int crec, int init_space, int rec_space) {
    int i = 0;
    int c = cbase;
    
    while ( c < str.length()) {
        //std::cout << "c = " << c << "; Str.len = " << str.length() << std::endl;
        if (i == 0) {
            printSpaces(init_space);
        } else {
            printSpaces(rec_space);
        }
        
        if (str[c] == ' ') {
            // print '~' for word separater
            std::cout << '~';
        } else {
            std::cout << str[c];
        }
        i++;
        c = cbase + crec * i;
    }
}
void printSnakeString() {
    std::string str = "Google Worked";
    printLine(str, 2, 4, 2, 3);
    std::cout << std::endl;
    printLine(str, 1, 2, 1, 1);
    std::cout << std::endl;
    printLine(str, 0, 4, 0, 3);
    std::cout << std::endl;
}
