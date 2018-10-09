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
#include <vector>
#include "Image.h"
using namespace std;

int main(int argc, const char * argv[]) {
    /// The image used throughout the program
    Image image;
    
    
    // make sure we have the correct number of arguments before anything is done
    if (argc != 2) {
        cout << "Incorrect number of arguments passed" << endl;
        exit(1);
    }
    
    
    // open the file
    ifstream sceneInputFile(argv[1]);

    if (sceneInputFile.fail()) {
        cout << "Unable to open input file" << endl;
        exit(2);
    }
    
    
    // begin reading file
    string command;     // temporarily store the command read
    string forGetLine;  // when getline is needed to get the data out
    
    // these values will eventually be assigned to an Image constructor - they are set to default values unless the loop below finds a different value in the input file
    Camera camera = DEFAULT_CAMERA;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    string outputFileName = DEFAULT_OUTPUT_FILE;
    vector<Sphere> spheres;
    Color background = DEFAULT_BACKGROUND_COLOR;
    Color ambientLight = DEFAULT_AMBIENT_LIGHT;
    vector<DirectionalLight> directionalLights;
    vector<PointLight> pointLights;
    vector<SpotLight> spotLights;
    vector<Color> ambientLights;
    int maxDepth = DEFAULT_MAX_DEPTH;
    // material is a state - the same value will get used until the input file reading hits a line that changes the material values, thereby changing the values in this variable
    Material currentMaterial = DEFAULT_MATERIAL;
    
    
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
            Vector3 center;
            float radius;
            sceneInputFile >> center.x >> center.y >> center.z >> radius;
            
            spheres.push_back({center, radius, currentMaterial});
            
        } else if (command == "background") {
            sceneInputFile >> background.red >> background.green >> background.blue;
            
        } else if (command == "material") {
            // we just need to store the current material somewhere so it's ready for use when the next sphere is read in
            sceneInputFile >> currentMaterial.ambient.red >> currentMaterial.ambient.green >> currentMaterial.ambient.blue >> currentMaterial.diffuse.red >> currentMaterial.diffuse.green >> currentMaterial.diffuse.blue >> currentMaterial.specular.red >> currentMaterial.specular.green >> currentMaterial.specular.blue >> currentMaterial.phongCosinePower;
            
        } else if (command == "directional_light") {
            DirectionalLight newLight;
            
            sceneInputFile >> newLight.color.red >> newLight.color.green >> newLight.color.blue >> newLight.direction.x >> newLight.direction.y >> newLight.direction.z;
            directionalLights.push_back(newLight);
            
        } else if (command == "point_light") {
            PointLight newLight;
            
            sceneInputFile >> newLight.color.red >> newLight.color.green >> newLight.color.blue >> newLight.location.x >> newLight.location.y >> newLight.location.z;
            
            pointLights.push_back(newLight);
            
        } else if (command == "spot_light") {
            SpotLight newLight;
            
            sceneInputFile >> newLight.color.red >> newLight.color.green >> newLight.color.blue >> newLight.location.x >> newLight.location.y >> newLight.location.z >> newLight.direction.x >> newLight.direction.y >> newLight.direction.z >> newLight.angle1 >> newLight.angle2;
            
            spotLights.push_back(newLight);
            
        } else if (command == "ambient_light") {
            //sceneInputFile >> ambientLight;
            
            Color newLight;
            
            sceneInputFile >> newLight.red >> newLight.green >> newLight.blue;
            
            ambientLights.push_back(newLight);
            
        } else if (command == "max_depth") {
            sceneInputFile >> maxDepth;
        } else {
            cout << "Command not recognized" << endl;
        }
    }
    
    // this will be initialized with default values if they haven't been set in the
    image = Image(camera, width, height, outputFileName, spheres, background, directionalLights, pointLights, spotLights, ambientLights, maxDepth);
    
    image.writeImageToFile();
    
    return 0;
}
