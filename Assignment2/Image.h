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



#include "DefaultValues.h"
#include <vector>
using namespace std;


class Image {
private:
    
    string outputFileName_;
    int width_;
    int height_;
    //Color *data_;   // stored in one dimension since we don't know how much storage we'll need until initialization
    
    vector<Color> data_;
    Camera camera_;
    vector<Sphere> spheres_;
    
    // there could be multiple lights of the same light type in the scene
    vector<DirectionalLight> directionalLights_;
    vector<PointLight> pointLights_;
    vector<SpotLight> spotLights_;
    vector<Color> ambientLights_;
    
    int maxDepth_;
    
    
public:
    void writeImageToFile();
    Image();
    Image(Camera camera,
          int width,
          int height,
          string outputFileName,
          vector<Sphere> spheres,
          Color background,
          vector<DirectionalLight> directionalLights,
          vector<PointLight> pointLights,
          vector<SpotLight> spotLights,
          vector<Color> ambientLights,
          int maxDepth);
    
    ~Image();
    
};


#endif /* Image_h */
