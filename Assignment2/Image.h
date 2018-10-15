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
    
    /// Maximum number of times rays bounce back and forth
    int maxDepth_;
    
    /// Image data - stored row first
    vector<Color> data_;
    
    Camera camera_;
    float imagePlaneDistance;
    vector<Sphere> spheres_;
    
    
    #pragma mark - Lights
    // there could be multiple lights of the same light type in the scene
    vector<DirectionalLight> directionalLights_;
    vector<PointLight> pointLights_;
    vector<SpotLight> spotLights_;
    vector<Color> ambientLights_;
    
    
    # pragma mark - Setup
    /// Camera vector setup used in constructors
    void setUpCameraValues();
    
    
    # pragma mark - Ray Generation
    /// Create the ray that goes to a given pixel in the raster image
    Ray generateRay(const int &xPosition, const int &yPosition);
    
    /// Intersection between ray and sphere
    /// Precondition: make sure ray's direction vector is normalized
    /// Returns: Location of intersection if one exists; else returns -1 to indicate no intersection exists
    void findIntersection(Ray &ray, const Sphere &sphere);
    
    // TODO: the intersection method below is the one to keep; remove the one above once the new one works
    void findIntersection(Ray &ray);
    
    # pragma mark - Color Generation
    /// Calculate the color for a given pixel in the raster image
    Color getColor(const Vector3 &location);
    
    /// Diffuse color for a point light
    Color calculateDiffuse(Sphere sphere, Ray ray, PointLight light);
    
    Color calculatePhong(Ray ray, Sphere sphere, PointLight light, Color ambientLight);
    
    /// Final output of the image to an image file
    void writeImageToFile();
    
public:
    /// Initializes all attributes to default values. See DefaultValues.h for more details on what the default values are.
    Image();
    
    /// Will initialize all attributes to specified values - made to be called in main when taking in input from a file
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
    
    /// Does all the work of the actual ray tracing and outputs it to an image file
    void performRayTrace();
};

#endif
