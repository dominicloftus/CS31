//
//  main.cpp
//  Project2
//
//  Created by Dominic Loftus on 4/18/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    
    string importer;
    cout << "Importer: ";
    getline(cin, importer);
    if(importer == ""){
        cout << "---\nYou must enter an importer.";
        return 0;
    }
    
    double value;
    cout << "Product value (in trillions): ";
    cin >> value;
    cin.ignore(10000, '\n');
    if(value < 0){
        cout << "---\nThe product value must not be negative.";
        return 0;
    }
    
    string product;
    cout << "Product: ";
    getline(cin, product);
    if(product == ""){
        cout << "---\nYou must enter a product.";
        return 0;
    }
    
    double tariff = 0;
    
    if(value < 500){            //finds first part of duty
        tariff = .31 * value;
        value = 0;
    }else{
        tariff = 500 * .31;
        value -= 500;
    }
    
    if(value < 400){            //finds second part of duty
        if(product == "mud" || product == "pigs"){      //sorts products by tariff amount 
            tariff += value * .29;
        }else{
            tariff += value * .25;
        }
    }else{
        if(product == "mud" || product == "pigs"){
            tariff += 400 * .29;
            value -= 400;
            tariff += value * .22;
        }else{
            tariff += 400 * .25;
            value -= 400;
            tariff += value * .22;
        }
    }
    
    cout.setf(ios::fixed);
    cout.precision(2);
    
    cout << "---\nThe import duty for " << importer << " is G" << tariff << " trillion.";
}










