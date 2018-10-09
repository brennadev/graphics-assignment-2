//
//  Image.h
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

#ifndef Image_h
#define Image_h

#include "DefaultValues.h"
#include <vector>
using namespace std;


class Image {
private:
    
    string outputFileName_;
    int width_;
    int height_;
    /// Image data - stored row first
    vector<Color> data_;
    Camera camera_;
    vector<Sphere> spheres_;
    
    // there could be multiple lights of the same light type in the scene
    vector<DirectionalLight> directionalLights_;
    vector<PointLight> pointLights_;
    vector<SpotLight> spotLights_;
    vector<Color> ambientLights_;
    
    int maxDepth_;
    
    
    Ray generateRay(int xPosition, int yPosition);
    
    /// Intersection between ray and sphere
    /// Precondition: make sure ray's direction vector is normalized
    /// Returns: Location of intersection if one exists; else returns -1 to indicate no intersection exists
    float findIntersection(Ray ray, Sphere sphere);
    
    Color getColor(Vector3 location);
    
    
    
public:
    
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
    
    /// Does all the work of the actual ray tracing and outputs it to an image file
    void performRayTrace();
    
    // TODO: eventually make this private (as it'll get called by performRayTrace)
    /// Final output of the image to an image file
    void writeImageToFile();
};


#endif /* Image_h */
