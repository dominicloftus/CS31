//
//  main.cpp
//  IOShit
//
//  Created by Dominic Loftus on 5/17/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX = 140;
const int FILEMAX = 50000;


/*int main() {
    ifstream infile("/Users/dominicloftus/Desktop/Project5/IOShit/test.txt");
    ofstream outfile("/Users/dominicloftus/Desktop/yewww.txt");
    if(!outfile)
        cout << "double fuck you" << endl;
    else
        cout << "double yeet" << endl;
    if(!infile)
        cout << "fuck you" << endl;
    else
        cout << "yeet" << endl;
    
    string total;
    for(int i = 0; i < 100; i++){
        string s;
        infile >> s;
        if(s != "")
            cerr << s << endl;
        total += s + " ";
    }
    
    for(int i = 97; i < 97+26; i++){
        char c = i;
        outfile << c << " ";
    }
    
    cout << total << endl;
    
    
}*/


int main(){
    ifstream infile("/Users/dominicloftus/Desktop/Project5/IOShit/test.txt");
    ofstream outfile("/Users/dominicloftus/Desktop/yewww.txt");
    
    
    
    
    
    char orig[FILEMAX] = "";
    int lineCount = 0;
    char line[MAX];
    while (infile.getline(line, MAX)){

        strcat(orig,line);
        strcat(orig," ");
    }
    //cout << lineCount << endl;
    
    cout << orig << endl;
    
    //t[0] = ' ';
    

    
    
    char processed[FILEMAX] = "";
    int pCount = 0;
    for(int k = 0; orig[k] != '\0'; k++){
        if(k == 0 && orig[k] == ' '){
            while(true){
                k++;
                if(orig[k] != ' ')
                    break;
            }
            k--;
        }
        else if(orig[k] == '\n');
        else if(orig[k] == '-'){
            processed[pCount] = orig[k];
            processed[pCount+1] = ' ';
            pCount += 2;
        }
        else if(orig[k] != ' ' || (orig[k] == ' ' && orig[k+1] != ' ')){
            processed[pCount] = orig[k];
            pCount++;
        }
    }
    
    cout << processed << endl;
    
    
}






/*

        char x[lineCount * MAX];
        int xCount = 0;
        for(int i = 0; t[i] != '\0'; i++){
            if(i == 0 && t[i] == ' '){
                while(true){
                    if(t[i] == ' ')
                        i++;
                    else
                        break;
                }
            }
            else if(t[i] == '\n' || t[i] == 13){
                x[xCount] = ' ';
                xCount++;
            }
            else if(t[i] != ' ' || (t[i] == ' ' && t[i+1] != ' ')){
                x[xCount] = t[i];
                xCount++;
            }
        }
        cout << x << endl;
        
        for(int i = 0; x[i] != '\0'; i++){
            int a = x[i];
            cout << a << endl;
        }



*/






