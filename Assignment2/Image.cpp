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
    camera_ = DEFAULT_CAMERA;
    width_ = DEFAULT_WIDTH;
    height_ = DEFAULT_HEIGHT;
    outputFileName_ = DEFAULT_OUTPUT_FILE;
    spheres_ = vector<Sphere>();
    directionalLights_ = vector<DirectionalLight>();
    pointLights_ = vector<PointLight>();
    spotLights_ = vector<SpotLight>();
    ambientLights_ = vector<Color>();
    
    setUpCameraValues();
    
    // set all points in the image to the background color
    for (int i = 0; i < width_ * height_; i++) {
        data_.push_back(DEFAULT_BACKGROUND_COLOR);
    }
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
    
    setUpCameraValues();
    
    // set all points in the image to the background color
    for (int i = 0; i < width * height; i++) {
        data_.push_back(background);
    }
}


void Image::setUpCameraValues() {
    // calculate the camera's right vector as that isn't provided in the input (using a right-handed coordinate system)
    camera_.right = cross(camera_.up, camera_.viewingDirection);
    camera_.v = cross(camera_.viewingDirection, camera_.right);
    camera_.up = camera_.v;     // make sure all camera vectors are orthogonal to each other
    
    // normalize to ensure math works right
    normalize(camera_.up);
    normalize(camera_.viewingDirection);
    normalize(camera_.right);
    
    imagePlaneDistance = height_ / 2.0 / tan(camera_.halfAngle * (M_PI / 180.0f));
}


Ray Image::generateRay(const int &xPosition, const int &yPosition) {
    float u = static_cast<float>(width_) / 2 * -1 + width_ * xPosition / width_;
    float v = static_cast<float>(height_) / 2 * -1 + height_ * yPosition / height_;
    //float imagePlaneDistance = height_ / 2.0 / tan(camera_.halfAngle * (M_PI / 180.0f));
    
    return {camera_.position,
        normalize(-1 * imagePlaneDistance * camera_.viewingDirection + u * camera_.right + v * camera_.v), {false, {0,0,0}, {0,0,0}, DEFAULT_MATERIAL}};
}



void Image::findIntersection(Ray &ray) {
    float t = -1;
    
    for (int i = 0; i < spheres_.size(); i++) {
        // use the discriminant to determine if there's an intersection
        float discriminant = pow(dot(ray.direction, camera_.position - spheres_.at(i).center), 2) - dot(ray.direction, ray.direction) *
        (dot(camera_.position - spheres_.at(i).center, camera_.position - spheres_.at(i).center) - pow(spheres_.at(i).radius, 2));
        
        // no intersection occurs with current sphere
        if (discriminant < 0) {
            ray.intersection.hasIntersection = false;
            
        // intersection occurs with current sphere
        } else {
            // want min of t > 0
            float firstT = dot(-1 * ray.direction, camera_.position - spheres_.at(i).center) + sqrt(discriminant);
            float secondT = dot(-1 * ray.direction, camera_.position - spheres_.at(i).center) - sqrt(discriminant);
            float potentialNewT;
            
            // the first and possibly the second t values are positive
            if (firstT > 0) {
                ray.intersection.hasIntersection = true;
                
                // both the first and second t values are positive
                if (secondT > 0) {
                    potentialNewT = max(firstT, secondT);
                    
                // only the first t value is positive
                } else {
                    potentialNewT = firstT;
                }
            // only the second t value is positive
            } else if (secondT > 0) {
                potentialNewT = secondT;
            } else {
                
            }
        }
    }
}

// TODO: to handle multiple spheres, this will just find the smallest t > 0 by iterating through all spheres (thus the sphere parameter will no longer be needed
void Image::findIntersection(Ray &ray, const Sphere &sphere) {
    //cout << "ray direction: " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z << endl;
    //cout << "ray length: " << length(ray.direction) << endl;
    // use the discriminant to determine if there's an intersection
    float discriminant = pow(dot(ray.direction, camera_.position - sphere.center), 2) - dot(ray.direction, ray.direction) *
        (dot(camera_.position - sphere.center, camera_.position - sphere.center) - pow(sphere.radius, 2));
    //cout << "discriminant: " << discriminant << endl;
    //cout << "sphere radius power: " << pow(sphere.radius, 2) << endl;
    
    // when there's no intersection
    if (discriminant < 0) {
        //cout << "discriminant < 0" << endl;
        ray.intersection.hasIntersection = false;
        
    // when there's an intersection
    } else {
        // want min of t > 0
        float firstT = dot(-1 * ray.direction, camera_.position - sphere.center) + sqrt(discriminant);
        float secondT = dot(-1 * ray.direction, camera_.position - sphere.center) - sqrt(discriminant);
        
        //cout << "firstT: " << firstT << endl;
        //cout << "secondT: " << secondT << endl;
        
        // the first and possibly the second t values are positive
        if (firstT > 0) {
            ray.intersection.hasIntersection = true;
            // both the first and second t values are positive
            if (secondT > 0) {
                ray.intersection.location = ray.origin + min(firstT, secondT) * ray.direction;
            
            // only the first t value is positive
            } else {
                ray.intersection.location = ray.origin + firstT * ray.direction;
            }
            
            ray.intersection.normal = normalize(ray.intersection.location - sphere.center);
        // only the second t value is positive
        } else if (secondT > 0) {
            ray.intersection.location = ray.origin + secondT * ray.direction;
            ray.intersection.hasIntersection = true;
            ray.intersection.normal = normalize(ray.intersection.location - sphere.center);
        // no intersection in front of the camera as both t values are negative
        } else {
            ray.intersection.hasIntersection = false;
        }
    }
}


Color Image::calculateDiffuse(Sphere sphere, Ray ray, PointLight light) {
    //cout << "diffuse first part: " << firstPart.red << " " << firstPart.green << " " << firstPart.blue << endl;
    //cout << "diffuse coefficient: " << sphere.material.diffuse.red << " " << sphere.material.diffuse.green << " " << sphere.material.diffuse.blue << endl;
    //cout << "light color: " << light.color.red << " " << light.color.green << " " << light.color.blue << endl;
    return sphere.material.diffuse * light.color * max((float)0.0, dot(ray.intersection.normal, normalize(light.location - ray.intersection.location)));
}


Color Image::calculatePhong(Ray ray, Sphere sphere, PointLight light, Color ambientLight) {
    
    // TODO: when I start taking advantage of multiple lights, just sum the diffuse and specular and just pull directly from the attributes rather than having the light types as params (there will only be one ambient light)
    
    float attenuation = 1.0 / pow(length(light.location - ray.intersection.location), 2);
    
    return sphere.material.ambient * ambientLight * attenuation
         + sphere.material.diffuse * light.color * attenuation * max((float)0.0, dot(ray.intersection.normal, normalize(light.location - ray.intersection.location)))
         + sphere.material.specular * attenuation * pow(dot(camera_.viewingDirection, 2 * dot(ray.intersection.normal, ray.direction * -1) * ray.intersection.normal + ray.direction), sphere.material.phongCosinePower) * light.color;
}


void Image::performRayTrace() {
    // go through each pixel
    for (int i = 0; i < width_ * height_; i++) {
        Ray ray = generateRay(i % width_, i / width_);
        findIntersection(ray, spheres_.at(0));
        
        if (ray.intersection.hasIntersection) {
            //cout << "t > 0" << endl;
            //data_.at(i) = {1, 1, 1};
            //data_.at(i) = spheres_.at(0).material.diffuse;
            //data_.at(i) = calculateDiffuse(spheres_.at(0), ray, pointLights_.at(0));
            // TODO: uncomment this and remove line above once I know diffuse works
            data_.at(i) = calculatePhong(ray, spheres_.at(0), pointLights_.at(0), ambientLights_.at(0));
            
        }
        // do nothing if not hit since it's already on the background color
    }
    writeImageToFile();
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
