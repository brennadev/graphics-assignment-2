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
#include "Image.h"
#include <vector>
//#include "DefaultValues.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    // TODO: make sure to use actual constructor - probably would initialize it after all of the file is read
    /// The image used throughout the program
    Image image;
    
    
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
    
    
    // begin reading file
    string command;
    string forGetLine;
    
    // TODO: need to figure out if everything should be stored in one initialization or if it should be in a bunch of setters (if doing one initialization, then the parameters not specified will need to automatically pull from the default values in DefaultValues.h)
    
    
    // these values will eventually be assigned to an Image constructor - they are set to default values unless the loop below finds a different value in the input file
    Camera camera = DEFAULT_CAMERA;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    string outputFileName = DEFAULT_OUTPUT_FILE;
    vector<Sphere> spheres;
    Color background = DEFAULT_BACKGROUND_COLOR;
    Color ambientLight = DEFAULT_AMBIENT_LIGHT;
    
    
    
    while (sceneInputFile >> command) {
        // ignore comments
        if (command[0] == '#') {
            getline(sceneInputFile, forGetLine);
        } else if (command == "camera") {
            sceneInputFile >> camera.position.x >> camera.position.y >> camera.position.z >>
                              camera.viewingDirection.x >> camera.viewingDirection.y >> camera.viewingDirection.z >>
                              camera.up.x >> camera.up.y >> camera.up.z >>
                              camera.halfAngle;
            
        } else if (command == "film_resolution") {
            
            sceneInputFile >> width >> height;
            
        } else if (command == "output_image") {
            sceneInputFile >> outputFileName;
            
        } else if (command == "sphere") {
            
        } else if (command == "background") {
            
        } else if (command == "material") {
            
        } else if (command == "directional_light") {
            
        } else if (command == "point_light") {
            
        } else if (command == "spot_light") {
            
        } else if (command == "ambient_light") {
            //sceneInputFile >> ambientLight;
            
        } else if (command == "max_depth") {
            
        } else {
            
        }
    }
    
    
    return 0;
}
