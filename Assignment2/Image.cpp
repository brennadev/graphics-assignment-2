//
//  Image.cpp
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


Image::Image() {
    
}


Image::Image(Camera camera,
      int width,
      int height,
      string outputFileName,
      vector<Sphere> spheres,
      Color background,
      vector<DirectionalLight> directionalLights,
      vector<PointLight> pointLights,
      vector<SpotLight> spotLights,
      vector<Color> ambientLights,
      int maxDepth) {
    
    // set all values
    camera_ = camera;
    width_ = width;
    height_ = height;
    outputFileName_ = outputFileName;
    spheres_ = spheres;
    directionalLights_ = directionalLights;
    pointLights_ = pointLights;
    spotLights_ = spotLights;
    ambientLights_ = ambientLights;
    
    // calculate the camera's right vector as that isn't provided in the input (using a right-handed coordinate system)
    camera_.right = cross(camera_.up, camera_.viewingDirection);
    camera_.v = cross(camera_.viewingDirection, camera_.right);
    
    // normalize to ensure math works right
    normalize(camera_.up);
    normalize(camera_.viewingDirection);
    normalize(camera_.right);
    
    // set all points in the image to the background color
    for (int i = 0; i < width * height; i++) {
        data_.push_back(background);
    }
}


Ray Image::generateRay(int xPosition, int yPosition) {
    float u = static_cast<float>(width_) / 2 * -1 + width_ * xPosition / width_;
    float v = static_cast<float>(height_) / 2 * -1 + height_ * yPosition / height_;
    
    return {camera_.position,
        normalize(-1 * camera_.viewingDirection + u * camera_.right + v * camera_.v), {0,0,0}};
}

// TODO: set ray's normal
float Image::findIntersection(Ray &ray, Sphere sphere) {
    cout << "ray direction: " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z << endl;
    cout << "ray length: " << length(ray.direction) << endl;
    // use the discriminant to determine if there's an intersection
    float discriminant = pow(dot(ray.direction, camera_.position - sphere.center), 2) - dot(ray.direction, ray.direction) *
        (dot(camera_.position - sphere.center, camera_.position - sphere.center) - pow(sphere.radius, 2));
    //cout << "discriminant: " << discriminant << endl;
    //cout << "sphere radius power: " << pow(sphere.radius, 2) << endl;
    
    // when there's no intersection
    if (discriminant < 0) {
        //cout << "discriminant < 0" << endl;
        return -1;
        
    // when there's an intersection
    } else {
        // want min of t > 0
        
        float firstT = dot(-1 * ray.direction, camera_.position - sphere.center) + sqrt(discriminant);
        float secondT = dot(-1 * ray.direction, camera_.position - sphere.center) - sqrt(discriminant);
        
        cout << "firstT: " << firstT << endl;
        cout << "secondT: " << secondT << endl;
        
        // the first and possibly the second t values are positive
        if (firstT > 0) {
            // both the first and second t values are positive
            if (secondT > 0) {
                return min(firstT, secondT);
            
            // only the first t value is positive
            } else {
                return firstT;
            }
            
        // only the second t value is positive
        } else if (secondT > 0) {
            return secondT;
            
        // no intersection in front of the camera as both t values are negative
        } else {
            return -1;
        }
    }
}


Color Image::calculateDiffuse(Sphere sphere, Ray ray, PointLight light) {
    return sphere.material.diffuse * light.color * max((float)0.0, dot(ray.normal, light.location));
}


Color Image::calculatePhong(Ray ray, Sphere sphere, PointLight light, Color ambientLight) {
    
    // TODO: when I start taking advantage of multiple lights, just sum the diffuse and specular and just pull directly from the attributes rather than having the light types as params (there will only be one ambient light)
    
    // where does the R in specular come from (that goes in the dot product)?
    //return sphere.material.ambient * ambientLight + sphere.material.diffuse * light.color * max((float)0.0, dot(ray.normal, light.location)) + sphere.material.specular * dot(camera_.viewingDirection, );
    return {0, 0, 0};
}

// I don't think this is needed as the diffuse is already accounted for in Phong - therefore, the calculateDiffuse method won't be needed once I get the Phong lighting working
Color Image::getColor(Vector3 location) {
    // TODO: finish this (or remove if not needed)
    
    
    //return calculateDiffuse(<#Sphere sphere#>, <#Ray ray#>, <#PointLight light#>) + calculatePhong(<#Ray ray#>, <#Sphere sphere#>);
        return {1, 1, 1};
}


void Image::performRayTrace() {
    // go through each pixel
    for (int i = 0; i < width_ * height_; i++) {
        //cout << "i: " << i << endl;
        Ray ray = generateRay(i % width_, i / width_);
        
        float t = findIntersection(ray, spheres_.at(0));
        
        if (t > 0) {
            //cout << "t > 0" << endl;
            // TODO: shading - call getColor and set the corresponding pixel in the image to the color
            data_.at(i) = getColor(ray.origin + t * ray.direction);
            
        }
        // do nothing if not hit since it's already on the background color
    }
    
    // TODO: writeImageToFile call (and then remove the separate call that's in main)
}


// TODO: multiple spheres

void Image::writeImageToFile() {
    ofstream outputfile(outputFileName_);
    
    // file heading
    outputfile << "P3\n";
    outputfile << width_ << " " << height_ << endl;
    outputfile << "255\n";
    
    // actual pixels
    for (int i = 0; i < width_ * height_; i++) {
        // the actual pixel
        outputfile << static_cast<int>(data_.at(i).red * 255) << " "
                   << static_cast<int>(data_.at(i).green * 255) << " "
                   << static_cast<int>(data_.at(i).blue * 255) << " ";
        
        // if we're at the end of a line in the image, we need to start a new line
        if (i % width_ == width_ - 1) {
            outputfile << endl;
        }
    }
}
