//
//  main.cpp
//  GameChooser
//
//  Created by Dominic Loftus on 4/13/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main() {
    int sys, game;
    srand(static_cast<unsigned int>(time(0)));
    sys = rand() % 3;
    if(sys == 0){
        srand(static_cast<unsigned int>(time(0)));
        game = rand() % 5;
        cout << "PS1" << game + 1 << endl;
    }
    if(sys == 1){
        srand(static_cast<unsigned int>(time(0)));
        game = rand() % 8;
        cout << "XBox" << game + 1 << endl;
    }
    if(sys == 2){
        srand(static_cast<unsigned int>(time(0)));
        game = rand() % 9;
        cout << "Wii" << game + 1 << endl;
    }
    return 0;
}
