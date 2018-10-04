//
//  main.cpp
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    
    // make sure we have the correct number of arguments before anything is done
    if (argc != 2) {
        cout << "Incorrect number of arguments passed" << endl;
        exit(1);
    }
    
    ifstream sceneInputFile(argv[1]);

    if (sceneInputFile.fail()) {
        cout << "Unable to open input file" << endl;
        exit(2);
    }
    
    
    
    
    
    return 0;
}
