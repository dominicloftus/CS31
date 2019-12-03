//
//  main.cpp
//  Project5
//
//  Created by Dominic Loftus on 5/17/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

const int MAX = 140;
const int FILEMAX = 50000;

int containsHyphen(char s[]){
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == '-')
            return i;
    }
    return -1;
}

int stuff(int lineLength, istream& inf, ostream& outf){
    int ret = 0;
    if(lineLength < 1)
        return 2;
    
    int lineCount = 0;
    char line[MAX];
    while (inf.getline(line, MAX))                  //count lines
        lineCount++;
    
    inf.clear();                                    //reset file
    inf.seekg(0, ios::beg);
    
    
    char t[FILEMAX] = "";
    for(int i = 0; i < lineCount; i++){             //read lines into c string
        char temp[MAX];
        inf.getline(temp,MAX);
        strcat(t,temp);
        strcat(t," ");
    }
    
    char orig[FILEMAX] = "";
    int xCount = 0;
    for(int i = 0; t[i] != '\0'; i++){              //format c string
        if(i == 0 && t[i] == ' '){
            while(true){
                if(t[i] == ' ')
                    i++;
                else
                    break;
            }
            i--;
        }
        else if(t[i] == '\n' || t[i] == 13){
            orig[xCount] = ' ';
            xCount++;
        }
        else if(t[i] != ' ' || (t[i] == ' ' && t[i+1] != ' ')){
            orig[xCount] = t[i];
            xCount++;
        }
    }

    
    
    
    int lCount = 0;
    int wCount = 0;
    int xSpace = 0;
    char lastChar = ' ';
    char lastWord[MAX] = "";
    char word[MAX] = "";
    
    for(int i = 0; orig[i] != '\0'; i++){
        if(orig[i] != ' '){
            word[wCount] = orig[i];                     //read characters until space
            word[wCount+1] = '\0';
            wCount++;
            
        }
        else if(orig[i] == ' '){
            if(lastChar == '.' || lastChar == '?')
                xSpace = 2;
            else
                xSpace = 1;
            if(strcmp(word, "#P#") == 0 && strcmp(lastWord, "#P#") != 0     //handles all new
               && strcmp(lastWord, "") != 0 && orig[i+1] != '\0'){          //paragraph cases
                outf << "\n\n";
                lCount = 0;
                lastChar = ' ';
            }
            else if(strcmp(word, "#P#") == 0);
            else if((wCount > lineLength && containsHyphen(word) == -1)){   //word too long
                ret = 1;
                if(lCount != 0){
                    outf << "\n";
                    lCount = 0;
                    lastChar = ' ';
                }
                for(int i = 0; word[i] != '\0'; i++){
                    if(lCount == lineLength){
                        outf << "\n" << word[i];
                        lCount = 1;
                        lastChar = ' ';
                    }
                    else{
                        outf << word[i];
                        lCount++;
                    }
                }
            }
            else if(wCount > lineLength && containsHyphen(word) != -1){
                bool first = true;
                int increm = 1;
                while(containsHyphen(word) != -1){          //breaks word by hyphen and attempts
                    int hyphPos = containsHyphen(word);     //to fit onto line
                    char curWord[MAX] = "";
                    char latWord[MAX] = "";
                    for(int i = 0; i <= hyphPos; i++){
                        curWord[i] = word[i];
                        curWord[i+1] = '\0';
                    }
                    int cnt = 0;
                    for(int i = hyphPos+1; i <= wCount; i++){
                        latWord[cnt] = word[i];
                        cnt++;
                    }
                    strcpy(word, latWord);
                    
                    if(hyphPos+1 > lineLength){             //word portion is still too long
                        ret = 1;
                        if(lCount != 0){
                            outf << "\n";
                            lCount = 0;
                            lastChar = ' ';
                        }
                        for(int i = 0; curWord[i] != '\0'; i++){
                            if(lCount == lineLength){
                                outf << "\n" << curWord[i];
                                lCount = 1;
                                lastChar = ' ';
                            }
                            else{
                                outf << curWord[i];
                                lCount++;
                            }
                        }
                    }
                    else{                                   //word portion fits on line
                        if((lastChar == '.' || lastChar == '?') && first)
                            increm = 2;
                        else if(first)
                            increm = 1;
                        if(strlen(curWord)+lCount+increm > lineLength){
                            outf << "\n";
                            lCount = 0;
                            lastChar = ' ';
                        }
                        else if(first){
                            if(lastChar == '.' || lastChar == '?'){
                                outf << "  ";
                                lCount++;
                            }
                            else
                                outf << " ";
                            lCount++;
                        }
                        for(int i = 0; curWord[i] != '\0'; i++){
                            outf << curWord[i];
                            lCount++;
                        }
                    }
                    if(first){
                        increm = 0;
                        first = false;
                    }
                }
                if(strlen(word) > lineLength){                  //handles last word portion of
                    ret = 1;                                    //hyphenated word
                    if(lCount != 0){
                        outf << "\n";
                        lCount = 0;
                        lastChar = ' ';
                    }
                    for(int i = 0; word[i] != '\0'; i++){
                        if(lCount == lineLength){
                            outf << "\n" << word[i];
                            lCount = 1;
                            lastChar = ' ';
                        }
                        else{
                            outf << word[i];
                            lCount++;
                        }
                    }
                }
                else{
                    if(strlen(word)+lCount+increm > lineLength){
                        outf << "\n";
                        lCount = 0;
                        lastChar = ' ';
                    }
                    for(int i = 0; word[i] != '\0'; i++){
                        outf << word[i];
                        lCount++;
                    }
                }
            }
            
            
            else if((wCount + lCount + xSpace) > lineLength){       //word would go over line length
                bool first = true;
                bool check = false;
                int increm = xSpace+1;
                while(containsHyphen(word) != -1){          //checks for word portions that may
                    check = true;                           //fit on the line
                    char curWord[MAX] = "";
                    char latWord[MAX] = "";
                    int hyphPos = containsHyphen(word);
                    for(int i = 0; i <= hyphPos; i++){
                        curWord[i] = word[i];
                        curWord[i+1] = '\0';
                    }
                    int cnt = 0;
                    for(int i = hyphPos+1; i <= wCount; i++){
                        latWord[cnt] = word[i];
                        cnt++;
                    }
                    strcpy(word, latWord);
                    //cerr << curWord << " " << word << endl;
                    
                    if(lCount + hyphPos + increm > lineLength){
                        if(first){
                            increm = 1;
                            first = false;
                        }
                            
                        outf << "\n";
                        lCount = 0;
                        lastChar = ' ';
                        for(int i = 0; curWord[i] != '\0'; i++){
                            outf << curWord[i];
                            lCount++;
                        }
                    }
                    else{
                        if(first){
                            if(lCount != 0){
                                if(lastChar == '.' || lastChar == '?'){
                                    outf << "  ";
                                    lCount++;
                                }
                                else
                                    outf << " ";
                                lCount++;
                            }
                            increm = 1;
                            first = false;
                        }
                        for(int i = 0; curWord[i] != '\0'; i++){
                            outf << curWord[i];
                            lCount++;
                        }
                    }
                }
                if(check){                                      //accounts for last word portion
                    if(lCount + strlen(word) > lineLength){     //of a hyphenated word
                        outf << "\n";
                        lCount = 0;
                        lastChar = ' ';
                        for(int i = 0; word[i] != '\0'; i++){
                            outf << word[i];
                            lCount++;
                        }
                    }
                    else{
                        for(int i = 0; word[i] != '\0'; i++){
                            outf << word[i];
                            lCount++;
                        }
                    }
                }
                else{
                    outf << "\n";
                    lCount = 0;
                    lastChar = ' ';
                    for(int i = 0; word[i] != '\0'; i++){
                        outf << word[i];
                        lCount++;
                    }
                }
            }
            else{                                   //puts word normally onto line
                if(lCount != 0){
                    if(lastChar == '.' || lastChar == '?'){
                        outf << "  ";
                        lCount++;
                    }
                    else
                        outf << " ";
                    lCount++;
                }
                for(int i = 0; word[i] != '\0'; i++){
                    outf << word[i];
                    lCount++;
                }
            }
            for(int i = 0; word[i] != '\0'; i++)
                lastChar = word[i];
            strcpy(lastWord, word);
            wCount = 0;
        }
    }
    
    
    outf << "\n";
    return ret;
    
}

int main() {
    int lineLength = 9;
    ifstream infile("/Users/dominicloftus/Desktop/Project5/IOShit/test.txt");
    ofstream outfile("/Users/dominicloftus/Desktop/yewww.txt");
    
    if(!infile || !outfile)
        cout << "bad file" << endl;
    else
        cout << stuff(lineLength, infile, cout) << endl;
    
    
    
}








