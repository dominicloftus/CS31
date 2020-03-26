//
//  main.cpp
//  Project4
//
//  Created by Dominic Loftus on 5/12/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>

using namespace std;

int tally(const string a[], int n, string target);
int findMatch(const string a[], int n, string target);
bool findRun(const string a[], int n, string target, int& begin, int& end);
int positionOfMin(const string a[], int n);
int moveToEnd(string a[], int n, int pos);//
int moveToBeginning(string a[], int n, int pos);//
int findDifference(const string a1[], int n1, const string a2[], int n2);
int eliminateDups(string a[], int n);//
bool subsequence(const string a1[], int n1, const string a2[], int n2);
int makeMerger(const string a1[], int n1, const string a2[], int n2,
               string result[], int max);//
int separate(string a[], int n, string separator);//


int tally(const string a[], int n, string target){
    int count = 0;
    if(n < 0)
        return -1;
    for(int i = 0; i < n; i++){
        if(target == a[i])
            count++;
    }
    return count;
}

int findMatch(const string a[], int n, string target){
    if(n < 0)
        return -1;
    for(int i = 0; i < n; i++){
        if(target == a[i])
            return i;
    }
    return -1;
}

bool findRun(const string a[], int n, string target, int& begin, int& end){
    if(n < 0)
        return false;
    int run = 0;
    for(int i = 0; i < n; i++){
        if(target == a[i] && run == 0){                     //for first of run
            begin = i;
            run++;
        }else if(run != 0 && target != a[i]){               //all others in run
            end = i-1;
            return true;
        }
    }
    return false;
}

int positionOfMin(const string a[], int n){
    if(n < 0)
        return -1;
    int min = 0;
    for(int i = 0; i < n; i++){
        if(a[i] < a[min])
            min = i;
    }
    return min;
}

int moveToEnd(string a[], int n, int pos){
    if(n < 0 || pos >= n)
        return -1;
    string temp = a[pos];                               //saves value of position
    for(int i = pos; i < n-1; i++)                      //moves positions to right, left one
        a[i] = a[i+1];
    a[n-1] = temp;                                      //sets last value to value at pos
    return pos;
}

int moveToBeginning(string a[], int n, int pos){
    if(n < 0 || pos >= n)
        return -1;
    string temp = a[pos];                               //save value at pos
    for(int i = pos; i > 0; i--)                        //moves positions to left, right one
        a[i] = a[i-1];
    a[0] = temp;                                        //sets first value to value at pos
    return pos;
}

int findDifference(const string a1[], int n1, const string a2[], int n2){
    int n;
    if(n1 < n2)                             //uses smaller array
        n = n1;
    else
        n = n2;
    if(n < 0){
        return -1;
    }
    for(int i = 0; i < n; i++){
        if(a1[i] != a2[i])
            return i;
    }
    return n;
}

int eliminateDups(string a[], int n){
    if(n < 0)
        return -1;
    string run = a[0];
    int retain = 1;
    for(int i = 1; i < n-1; i++){
        if(a[i] == run){                //same string in a row
            moveToEnd(a, n, i);         //moves it to end
            i--;                        //adjust for new value at a[i]
            n--;                        //adjust for shortened array length
        }
        else{
            run = a[i];                 //different value, updates current value
            retain++;
        }
    }
    return retain;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0 || n2 > n1)             //n1 must be larger or equal to n2
        return false;
    
    int n1count = 0;
    for(int i = 0; i < n2; i++){
        while(true){
            if(a1[n1count] == a2[i]){           //checks for a match
                n1count++;
                break;
            }
            else if(n1count == n1-1){           //checks for end of a1
                return false;
            }
            else{
                n1count++;
            }
        }
    }
    return true;
}


int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max){
    if(n1 + n2 > max || n1 < 0 || n2 < 0){
        return -1;
    }
    for(int i = 0; i < n1-1; i++){              //non decreasing order
        if(a1[i] > a1[i+1])
            return -1;
    }
    for(int i = 0; i < n2-1; i++){
        if(a2[i] > a2[i+1])
            return -1;
    }
   
    
    int n1count = 0;
    int n2count = 0;
    for(int i = 0; i < n1+n2+1; i++){
        if(n1count == n1){                      //end of n1
            for(int j = n2count; j < n2; j++){
                result[i] = a2[j];
                i++;
            }
            break;
        }
        if(n2count == n2){                      //end of n2
            for(int j = n1count; j < n1; j++){
                result[i] = a1[j];
                i++;
            }
            break;
        }
        if(a1[n1count] < a2[n2count]){          //puts smaller value into result
            result[i] = a1[n1count];
            n1count++;
        }else{
            result[i] = a2[n2count];
            n2count++;
        }
    }
    return n1+n2;
}

int separate(string a[], int n, string separator){
    if(n < 0)
        return -1;
    int count = 0;
    for(int i = 0; i < n; i++){
        if(a[i] < separator){           //checks if value at position i needs to move to front or back
            moveToBeginning(a, n, i);
            count++;                    //counts amount before separator to return
        }
        else if(a[i] > separator)
            moveToEnd(a, n, i);
    }
    if(count == 0)
        return n;
    return count;
}











/*
int main()
{
    string h[7] = { "romanoff", "thor", "rogers", "banner", "banner", "", "rogers" };
    assert(tally(h, 7, "rogers") == 2);
    assert(tally(h, 7, "") == 1);
    assert(tally(h, 7, "rhodes") == 0);
    assert(tally(h, 0, "rogers") == 0);
    assert(findMatch(h, 7, "rogers") == 2);
    assert(findMatch(h, 2, "rogers") == -1);
    int bg;
    int en;
    assert(findRun(h, 7, "banner", bg, en) && bg == 3 && en == 4);
    
    string g[4] = { "romanoff", "thor", "banner", "parker" };
    assert(positionOfMin(g, 4) == 2);
    assert(findDifference(h, 4, g, 4) == 2);
    assert(!subsequence(h, 7, g, 4));
    assert(moveToEnd(g, 4, 1) == 1 && g[1] == "banner" && g[3] == "thor");
    
    string f[4] = { "parker", "banner", "thor", "rogers" };
    assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "thor" && f[2] == "banner");
    
    string e[5] = { "parker", "parker", "parker", "thor", "thor" };
    assert(eliminateDups(e, 5) == 2 && e[1] == "thor");
    
    string x[4] = { "rhodes", "rhodes", "tchalla", "thor" };
    string y[4] = { "banner", "parker", "rhodes", "rogers" };
    string z[10];
    assert(makeMerger(x, 4, y, 4, z, 10) == 8 && z[5] == "rogers");
    
    assert(separate(h, 7, "rogers") == 3);
    
    cout << "All tests succeeded" << endl;
}
*/


/*
int main(){
    string x[10] = { "banner", "captain", "desert", "rhodes", "rogers", "stark", "tchalla" };
    string y[5] = { "parker", "rogers", "rogers", "thor", "zamora" };
    string z[20];
    makeMerger(x, 7, y, 5, z, 20);
    for(int i = 0; i < 12; i++){
        cout << z[i] << endl;
    }
    cout << makeMerger(x, 7, y, 5, z, 20) << endl;
}

*/









