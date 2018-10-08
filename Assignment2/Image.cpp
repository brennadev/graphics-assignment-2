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
    
    // calculate the camera's right vector as that isn't provided in the input
    camera_.right = cross(camera_.viewingDirection, camera_.up);
    
    // set all points in the image to the background color
    for (int i = 0; i < width * height; i++) {
        data_.push_back(background);
    }
    
    
    
    // TODO: test code to remove later (everything to end of constructor)
    data_.at(12).red = 1.0;
    data_.at(13).red = 1.0;
    data_.at(14).red = 1.0;
    data_.at(15).red = 1.0;
    data_.at(16).red = 1.0;
    data_.at(652).red = 1.0;
    data_.at(653).red = 1.0;
    data_.at(654).red = 1.0;
    data_.at(655).red = 1.0;
    data_.at(656).red = 1.0;
    data_.at(12).green = 1.0;
    data_.at(12).blue = 1.0;
    data_.at(652).green = 1.0;
    data_.at(652).blue = 1.0;
}

// TODO: remove later if there's no implementation
Image::~Image() {
    
}


// TODO: make sure direction vector is normalized when returned
Ray Image::generateRay(int xPosition, int yPosition) {
    float u = width_ / 2 * -1 + width_ * xPosition / width_;
    float v = height_ / 2 * -1 + height_ * yPosition / height_;
    
    
    
    // TODO: eventually get return value changed to correct value
    return {camera_.position, {0, 0, 0}};
}


float Image::findIntersection(Ray ray, Sphere sphere) {
    // use the discriminant to determine if there's an intersection
    float discriminant = pow(dot(ray.direction, camera_.position - sphere.center), 2) - (dot(camera_.position - sphere.center, camera_.position - sphere.center) - pow(sphere.radius, 2));
    
    // when there's no intersection
    if (discriminant < 0) {
        return -1;
        
    // when there's an intersection
    } else {
        // want min of t > 0
        
        float firstT = dot(-1 * ray.direction, camera_.position - sphere.center) + sqrt(discriminant);
        float secondT = dot(-1 * ray.direction, camera_.position - sphere.center) - sqrt(discriminant);
        
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


void Image::writeImageToFile() {
    const char *outputNameAsCString = outputFileName_.c_str();
    
    int onePast = strlen(outputNameAsCString);
    
    switch (outputNameAsCString[onePast - 1]) {
        case 'g':
            if (outputNameAsCString[onePast - 2] == 'p' || outputNameAsCString[onePast - 2] == 'e') {
                // jpeg
                stbi_write_jpg(outputNameAsCString, width_, height_, 3, data_.data(), 95);
            } else {
                // png
                stbi_write_png(outputNameAsCString, width_, height_, 3, data_.data(), width_ * 3);
            }
            break;
            
        case 'a':
            // tga
            stbi_write_tga(outputNameAsCString, width_, height_, 3, data_.data());
            break;
            
        case 'p':
            // bmp
            stbi_write_bmp(outputNameAsCString, width_, height_, 3, data_.data());
            break;
        default:
            // bmp
            stbi_write_bmp(outputNameAsCString, width_, height_, 3, data_.data());
            break;
    }
}
