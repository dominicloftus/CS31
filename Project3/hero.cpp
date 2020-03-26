//
//  main.cpp
//  Project3
//
//  Created by Dominic Loftus on 5/5/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;



bool validEntry(string song, int ind){                  //checks input
    if(song[ind] == 'g' || song[ind] == 'r' || song[ind] == 'y' || song[ind] == 'b'
       || song[ind] == 'o' || song[ind] == '/')
        return true;
    return false;
}


bool hasCorrectSyntax(string song){
    for(int i = 0; i != song.size(); i++)               //removes uppercase possibility
        song[i] = tolower(song[i]);

    for(int i = 0; i != song.size(); i++){
        if(!validEntry(song, i))
            return false;
        
        if(isalpha(song[i])){                           //goes through incrementally for all
            if(i == song.size()-1)                      //syntactically possible values
                return false;
            else if(song[i+1] == '/')
                i++;
            else if(isdigit(song[i+1]) && (i+1) == song.size()-1)
                return false;
            else if(isdigit(song[i+1]) && song[i+2] == '/')
                i += 2;
            else if(isdigit(song[i+1]) && isdigit(song[i+2]) && i+2 == song.size()-1)
                return false;
            else if(isdigit(song[i+1]) && isdigit(song[i+2]) && song[i+3] == '/')
                i += 3;

        }
    
    
    }
    return true;
}

int translateSong(string song, string& instructions, int& badBeat){
    int beat = 1, sustain = 0;
    string trans = "", color = "";
    
    if(!hasCorrectSyntax(song))                                     //check syntax
        return 1;
    
    for(int i = 0; i != song.size(); i++)
        song[i] = tolower(song[i]);

    for(int i = 0; i < song.size(); i++){
        if(song[i] == '/'){
            trans += "x";
            beat++;
        }
        else if(song[i+1] == '/'){
            trans += song[i];
            beat++;
            i++;
        }
        else if(isdigit(song[i+1]) && song[i+2] == '/'){            //check for single digit sustain
            color = toupper(song[i]);
            sustain = song[i+1] - '0';
            if(sustain < 2){                                        //check for short sustain
                badBeat = beat;
                return 2;
            }
            i += 2;
            for(int j = 0; j < sustain; j++){
                if(i == song.size()-1 && j != sustain - 1){         //check, not enough /'s at end
                    badBeat = beat+1;
                    return 4;
                }
                else if(song[i] != '/' ){                           //check, not enough /'s in middle
                    badBeat = beat;
                    return 3;
                }else{
                    trans += color;                                 //good sustain value
                    beat++;
                    i++;
                }
            }
            i--;
        }
        else if(isdigit(song[i+1]) && isdigit(song[i+2]) && song[i+3] =='/'){
            color = toupper(song[i]);
            sustain = (song[i+1]-'0')*10 + (song[i+2] - '0');
            if(sustain < 2){                                        //check for short sustain
                badBeat = beat;
                return 2;
            }
            i += 3;
            for(int j = 0; j < sustain; j++){
                if(i == song.size()-1 && j != sustain - 1){         //check, not enough /'s at end
                    badBeat = beat+1;
                    return 4;
                }
                else if(song[i] != '/' ){                           //check, not enough /'s in mid
                    badBeat = beat;
                    return 3;
                }else{
                    trans += color;                                 //good sustain value
                    beat++;
                    i++;
                }
            }
            i--;
        }
    }
    instructions = trans;
    return 0;
}

int main() {
    string test = "g2//r2//y2//o2//b2//";
    string instr = "fuck";
    if(hasCorrectSyntax(test))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    
    int beatie = 2;
    
    int t = translateSong(test, instr, beatie);
    
    cout << t << "\n" << test << "\n" << instr << "\n" << beatie;
}



















