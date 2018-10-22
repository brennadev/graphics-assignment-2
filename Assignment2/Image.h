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
    
    Color backgroundColor_;
    
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
    vector<Triangle> triangles_;
    
    
    # pragma mark - Setup
    /// Camera vector setup used in constructors
    void setUpCameraValues();
    
    
    # pragma mark - Ray Generation
    /// Create the ray that goes to a given pixel in the raster image
    Ray generateRay(const int &xPosition, const int &yPosition);
    
    /// Checks all object types for an intersection with the passed-in ray and finds the closest object that intersects if one exists
    /// Postcondition: ray.intersection.hasIntersection will be true if an intersection is found. ray.intersection contains all necessary information about the intersection for later determining the color at the position.
    void findIntersectionAllObjects(Ray &ray);
    
    // TODO: get t in param
    /// Intersection between ray and sphere
    /// Precondition: make sure ray's direction vector is normalized
    void findSphereIntersection(Ray &ray, float t);
    
    /// Intersection between ray and plane
    void findPlaneIntersection(Ray &ray, Vector3 point);
    
    /// Intersection between ray and triangle
    bool findTriangleIntersection(Ray &ray, float t);
    
    bool triangleSameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b);
    bool pointInTriangle(Vector3 p, Triangle triangle);
    
    
    # pragma mark - Color Generation
    /// Calculate the color for a given pixel in the raster image
    Color getColor(const Vector3 &location);
    
    Color ambient(Color coefficient);
    Color diffuse(Ray ray, PointLight light);
    Color diffuse(Ray ray, DirectionalLight light);
    Color specular(Ray ray, PointLight light);
    Color specular(Ray ray, DirectionalLight light);
    
    /// Get reflection direction for the passed in ray's intersection
    Vector3 reflect(Ray ray);
    
    /// Get refraction direction for the passed in ray's intersection
    Vector3 refract(Ray ray, float currentIOR, Vector3 lightDirection);
    
    // TODO: remove eventually
    Color calculatePhong(Ray ray);
    
    /// Handles all lighting calculations
    Color calculateLight(Ray ray, int index);
    
    /// Recursive part of the ray tracer
    Color evaluateRayTree(Ray ray, int index);
    
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
          vector<Triangle> triangles,
          int maxDepth);
    
    /// Does all the work of the actual ray tracing and outputs it to an image file
    void performRayTrace();
};

#endif
