//
//  main.cpp
//  Project6
//
//  Created by Dominic Loftus on 5/28/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#include <iostream>
using namespace std;

int* minimart(int* a, int* b)
{
    if (*a < *b)
        return a;
    else
        return b;
}

void swap1(int* a, int *b)
{
    int* temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void deleteG(char* str){
    for(;;){
        if(*str == 0){
            break;
        }
        if(*str == 'g' || *str == 'G'){
            char* temp = str;
            for(;;){
                if(*str == 0)
                    break;
                *str = *(str+1);
                str++;
            }
            str = temp-1;
        }
        str++;
    }
}

int main()
{
    char f[] = "whatggggggg tghGGGGGGe fugggGGGGggGgck  GGGGGgggGGG is up kylegggggggggggg";
    deleteG(f);
    cout << f << endl;
}
