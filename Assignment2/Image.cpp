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
    triangles_ = vector<Triangle>();
    
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
      vector<Triangle> triangles,
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
    triangles_ = triangles;
    
    setUpCameraValues();
    
    // set all points in the image to the background color
    for (int i = 0; i < width * height; i++) {
        data_.push_back(background);
    }
}


void Image::setUpCameraValues() {
    // calculate the camera's right vector as that isn't provided in the input (using a right-handed coordinate system)
    camera_.right = cross(camera_.viewingDirection, camera_.up);
    
    camera_.v = cross(camera_.viewingDirection, camera_.right);
    camera_.up = camera_.v;     // make sure all camera vectors are orthogonal to each other
    
    // normalize to ensure math works right
    normalize(camera_.up);
    normalize(camera_.viewingDirection);
    normalize(camera_.right);
    
    imagePlaneDistance = height_ / 2.0 / tan(camera_.halfAngle * (M_PI / 180.0f));
}


Ray Image::generateRay(const int &xPosition, const int &yPosition) {
    float u = (float)width_ / 2.0 - width_ * (xPosition / (float)width_);
    float v = (float)height_ / 2.0 - height_ * (yPosition / (float)height_);
    
    return {camera_.position,
        normalize(imagePlaneDistance * camera_.viewingDirection + u * camera_.right - v * camera_.up), {false, {0,0,0}, {0,0,0}, DEFAULT_MATERIAL}};
}


void Image::findIntersection(Ray &ray) {
    float t = 9e99;    // set to some really big value so the first calculated t is always less
    
    for (int i = 0; i < spheres_.size(); i++) {
        // use the discriminant to determine if there's an intersection
        float discriminant = pow(dot(ray.direction, camera_.position - spheres_.at(i).center), 2) - dot(ray.direction, ray.direction) *
        (dot(camera_.position - spheres_.at(i).center, camera_.position - spheres_.at(i).center) - pow(spheres_.at(i).radius, 2));
        
        // no intersection occurs with current sphere
        if (discriminant < 0) {
            continue;
            
        // intersection occurs with current sphere
        } else {
            // want min of t > 0
            float firstT = dot(-1 * ray.direction, camera_.position - spheres_.at(i).center) + sqrt(discriminant);
            float secondT = dot(-1 * ray.direction, camera_.position - spheres_.at(i).center) - sqrt(discriminant);
            
            // keep track so we know if the other values of the intersection need to be updated
            float oldT = t;
            
            // the first and possibly the second t values are positive
            if (firstT > 0) {
                // both the first and second t values are positive
                if (secondT > 0) {
             
                    t = min(min(firstT, secondT), t);
                    
                // only the first t value is positive
                } else {
                    t = min(t, firstT);
                }
            // only the second t value is positive
            } else if (secondT > 0) {
                t = min(t, secondT);
                
            // t is 0
            } else {
                continue;
            }
            // all the other values associated with the intersection need updating if t has changed
            if (t < oldT) {
                ray.intersection.hasIntersection = true;
                ray.intersection.location = ray.origin + t * ray.direction;
                ray.intersection.normal = normalize(ray.intersection.location - spheres_.at(i).center);
                ray.intersection.material = spheres_.at(i).material;
            }
        }
    }
}


Color Image::calculatePhong(Ray ray) {
    // as each light's diffuse and specular needs to be added together, accumulate a total
    Color totalDiffuseSpecular = {0, 0, 0};
    
    // point lights
    for (int i = 0; i < pointLights_.size(); i++) {
        float attenuation = 1.0 / pow(length(pointLights_.at(i).location - ray.intersection.location), 2);
        
        // both
        Vector3 N = ray.intersection.normal;
        
        // diffuse
        Color kd = ray.intersection.material.diffuse;
        Vector3 l = normalize(pointLights_.at(i).location - ray.intersection.location);
        
        // specular
        float n = ray.intersection.material.phongCosinePower;
        Color ks = ray.intersection.material.specular;
        
        Vector3 d = ray.direction;
        Color I = pointLights_.at(i).color;
        
        
        Vector3 v = -1 * d;
        // either v or l
        
        // reflected view vector
        Vector3 r = 2 * dot(N, v) * N - v;
        // the only thing I'm wondering about is if any direction vectors are flipped
        
        // calculation with attenuation (but causes non-ambient stuff to be really dim)
        totalDiffuseSpecular = totalDiffuseSpecular
        // diffuse
        + kd * (I * attenuation) * max((float)0.0, dot(N, l))
        // specular
        + ks * pow(clamp(dot(l, r)), n) * (I * attenuation);
    }
    
    
    
    // directional lights
    for (int i = 0; i < directionalLights_.size(); i++) {
        totalDiffuseSpecular = totalDiffuseSpecular + ray.intersection.material.diffuse * directionalLights_.at(i).color * max((float)0.0, dot(ray.intersection.normal, normalize(directionalLights_.at(i).direction)))
        + ray.intersection.material.specular * pow(dot(camera_.viewingDirection, 2 * dot(ray.intersection.normal, ray.direction * -1) * ray.intersection.normal + ray.direction), ray.intersection.material.phongCosinePower) * directionalLights_.at(i).color;
    }
    
    return ray.intersection.material.ambient * ambientLights_.at(0) + totalDiffuseSpecular;
}


void Image::performRayTrace() {
    // go through each pixel
    for (int i = 0; i < width_ * height_; i++) {
        Ray ray = generateRay(i % width_, i / width_);
        findIntersection(ray);
        
        if (ray.intersection.hasIntersection) {
            data_.at(i) = calculatePhong(ray);
        }
        // do nothing if not hit since it's already on the background color
    }
    writeImageToFile();
}


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
