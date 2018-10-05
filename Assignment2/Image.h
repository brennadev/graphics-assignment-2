//
//  Image.h
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

#ifndef Image_h
#define Image_h


//#include <string>
// TODO: not sure if these will be needed or not
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>

//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
//#include "CustomTypes.h"
#include "DefaultValues.h"
#include <vector>
using namespace std;






class Image {
private:
    
    string outputFileName;
    int width;
    int height;
    Color **data;   // dynamically allocated memory
    Camera camera;
    vector<Sphere> spheres;
    
    // there could be multiple lights of the same light type in the scene
    vector<DirectionalLight> directionalLights;
    vector<PointLight> pointLights;
    vector<SpotLight> spotLights;
    vector<Color> ambientLights;
    
    int maxDepth;
    
    
public:
    void writeImageToFile();
    
};


#endif /* Image_h */
