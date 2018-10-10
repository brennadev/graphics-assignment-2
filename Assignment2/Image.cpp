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
    
    // set all points in the image to the background color
    for (int i = 0; i < width * height; i++) {
        data_.push_back(background);
    }
    
    
    
    // TODO: test code to remove later (everything to end of constructor)
    /*data_.at(12).red = 1.0;
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
    data_.at(652).blue = 1.0;*/
}

// TODO: remove later if there's no implementation
Image::~Image() {
    
}


Ray Image::generateRay(int xPosition, int yPosition) {
    float u = static_cast<float>(width_) / 2 * -1 + width_ * xPosition / width_;
    float v = static_cast<float>(height_) / 2 * -1 + height_ * yPosition / height_;
    std::cout << "u: " << u << std::endl;
    std::cout << "v: " << v << std::endl;
    std::cout << "right: " << camera_.right.x << " " << camera_.right.y << " " << camera_.right.z << endl;
    
    // I think the v value is totally off
    std::cout << "camera v: " << camera_.v.x << " " << camera_.v.y << " " << camera_.v.z << endl;
    std::cout << "camera viewing direction: " << camera_.viewingDirection.x << " " << camera_.viewingDirection.y << " " << camera_.viewingDirection.z << std::endl;
    //std::cout << "v vector: " << cross(camera_.right, camera_.viewingDirection).x << " " << cross(camera_.right, camera_.viewingDirection).y << " " << cross(camera_.right, camera_.viewingDirection).z << std::endl;
    
    return {camera_.position,
            normalize(-1 * camera_.viewingDirection + u * camera_.right + v * camera_.v)};
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


Color Image::calculateDiffuse(Sphere sphere, Ray ray, PointLight light) {
    return sphere.material.diffuse * light.color * max((float)0.0, dot(ray.normal, light.location));
}


Color Image::calculatePhong(Ray ray, Sphere sphere) {
    return {0, 0, 0};
}

Color Image::getColor(Vector3 location) {
    // TODO: finish this (or remove if not needed)
    
    
    //return calculateDiffuse(<#Sphere sphere#>, <#Ray ray#>, <#PointLight light#>) + calculatePhong(<#Ray ray#>, <#Sphere sphere#>);
        return {0, 0, 0};
}


void Image::performRayTrace() {
    // go through each pixel
    for (int i = 0; i < width_ * height_; i++) {
        Ray ray = generateRay(i % width_, i / width_);
        //std::cout << "ray origin: " << ray.origin.x << " " << ray.origin.y << " " << ray.origin.z << std::endl;
        std::cout << "ray direction at (" << i % width_ << ", " << i / width_ << "): " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z << std::endl;
        
        std::cout << "ray origin: " << ray.origin.x << " " << ray.origin.y << " " << ray.origin.z << std::endl;
        /*float t = findIntersection(ray, spheres_.at(0));
        
        if (t > 0) {
            // TODO: shading - call getColor
            
        }*/
        // do nothing if not hit since it's already on the background color
    }
    
    // TODO: writeImageToFile call
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
