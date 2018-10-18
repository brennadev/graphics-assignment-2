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
    
    // trying to switch the cross product order to see what difference it makes
    
    // old
    //camera_.right = cross(camera_.up, camera_.viewingDirection);
    
    // new
    camera_.right = cross(camera_.viewingDirection, camera_.up);
    
    camera_.v = cross(camera_.viewingDirection, camera_.right);
    camera_.up = camera_.v;     // make sure all camera vectors are orthogonal to each other
    
    // normalize to ensure math works right
    normalize(camera_.up);
    normalize(camera_.viewingDirection);
    normalize(camera_.right);
    
    imagePlaneDistance = height_ / 2.0 / tan(camera_.halfAngle * (M_PI / 180.0f));
    
    cout << "camera forward: " << camera_.viewingDirection.x << " " << camera_.viewingDirection.y << " " << camera_.viewingDirection.z << endl;
    cout << "camera eye: " << camera_.position.x << " " << camera_.position.y << " " << camera_.position.z << endl;
    cout << "camera v: " << camera_.v.x << " " << camera_.v.y << " " << camera_.v.z << endl;
    cout << "camera up: " << camera_.up.x << " " << camera_.up.y << " " << camera_.up.z << endl;
    cout << "camera right: " << camera_.right.x << " " << camera_.right.y << " " << camera_.right.z << endl;
}


Ray Image::generateRay(const int &xPosition, const int &yPosition) {
    float u = (float)width_ / 2.0 - width_ * (xPosition / (float)width_);
    float v = (float)height_ / 2.0 - height_ * (yPosition / (float)height_);
    
    return {camera_.position,
        normalize(/*-1 **/ imagePlaneDistance * camera_.viewingDirection + u * camera_.right + v * camera_.up), {false, {0,0,0}, {0,0,0}, DEFAULT_MATERIAL}};
}


void Image::findIntersection(Ray &ray) {
    float t = -1;
    
    for (int i = 0; i < spheres_.size(); i++) {
        // use the discriminant to determine if there's an intersection
        float discriminant = pow(dot(ray.direction, camera_.position - spheres_.at(i).center), 2) - dot(ray.direction, ray.direction) *
        (dot(camera_.position - spheres_.at(i).center, camera_.position - spheres_.at(i).center) - pow(spheres_.at(i).radius, 2));
        
        // no intersection occurs with current sphere
        if (discriminant < 0) {
            // I originally had some stuff in here, but I don't want to remove this if statement so close to the due date so I don't accidentally break something last-minute
        // intersection occurs with current sphere
        } else {
            // want min of t > 0
            float firstT = dot(-1 * ray.direction, camera_.position - spheres_.at(i).center) + sqrt(discriminant);
            float secondT = dot(-1 * ray.direction, camera_.position - spheres_.at(i).center) - sqrt(discriminant);
            
            
            // the first and possibly the second t values are positive
            if (firstT > 0) {
                // both the first and second t values are positive
                if (secondT > 0) {
                    ray.intersection.hasIntersection = true;
                    t = max(firstT, secondT);
                    ray.intersection.location = ray.origin + t * ray.direction;
                    ray.intersection.normal = normalize(ray.intersection.location - spheres_.at(i).center);
                    ray.intersection.material = spheres_.at(i).material;
                    
                // only the first t value is positive
                } else {
                    ray.intersection.hasIntersection = true;
                    t = firstT;
                    ray.intersection.location = ray.origin + t * ray.direction;
                    ray.intersection.normal = normalize(ray.intersection.location - spheres_.at(i).center);
                    ray.intersection.material = spheres_.at(i).material;
                }
            // only the second t value is positive
            } else if (secondT > 0) {
                ray.intersection.hasIntersection = true;
                t = secondT;
                ray.intersection.location = ray.origin + t * ray.direction;
                ray.intersection.normal = normalize(ray.intersection.location - spheres_.at(i).center);
                ray.intersection.material = spheres_.at(i).material;
                
            // t is 0
            } else {
                continue;
            }
        }
    }
}


Color Image::calculateDiffuse(Sphere sphere, Ray ray, PointLight light) {
    return sphere.material.diffuse * light.color * max((float)0.0, dot(ray.intersection.normal, normalize(light.location - ray.intersection.location)));
}


Color Image::calculatePhong(Ray ray) {
    // as each light's diffuse and specular needs to be added together, accumulate a total
    Color totalDiffuseSpecular = {0, 0, 0};
    
    for (int i = 0; i < pointLights_.size(); i++) {
        float attenuation = 1.0 / pow(length(pointLights_.at(i).location - ray.intersection.location), 2);
        
        // comment/uncomment one line for the totalDiffuseSpecular assignment depending on what you want to do
        
        // calculation with attenuation (but causes non-ambient stuff to be really dim)
        totalDiffuseSpecular = totalDiffuseSpecular + ray.intersection.material.diffuse * (pointLights_.at(i).color * attenuation) * max((float)0.0, dot(ray.intersection.normal, normalize(pointLights_.at(i).location - ray.intersection.location)))
        + ray.intersection.material.specular * pow(dot(camera_.viewingDirection, 2 * dot(ray.intersection.normal, ray.direction * -1) * ray.intersection.normal + ray.direction), ray.intersection.material.phongCosinePower) * (pointLights_.at(i).color * attenuation);
        
        // calculation without attenuation
        /*totalDiffuseSpecular = totalDiffuseSpecular + ray.intersection.material.diffuse * pointLights_.at(i).color * max((float)0.0, dot(ray.intersection.normal, normalize(pointLights_.at(i).location - ray.intersection.location)))
        + ray.intersection.material.specular * pow(dot(camera_.viewingDirection, 2 * dot(ray.intersection.normal, ray.direction * -1) * ray.intersection.normal + ray.direction), ray.intersection.material.phongCosinePower) * pointLights_.at(i).color;*/
        
        
        // diffuse only - no attenuation
        //totalDiffuseSpecular = totalDiffuseSpecular + ray.intersection.material.diffuse * pointLights_.at(i).color * max((float)0.0, dot(ray.intersection.normal, normalize(pointLights_.at(i).location - ray.intersection.location)));
    }
    return ray.intersection.material.ambient * ambientLights_.at(0) + totalDiffuseSpecular;
}


void Image::performRayTrace() {
    // go through each pixel
    for (int i = 0; i < width_ * height_; i++) {
        Ray ray = generateRay(i % width_, i / width_);
        findIntersection(ray);
        
        if (ray.intersection.hasIntersection) {
            // below will just calculate the diffuse on a single sphere with a single light (will just take the first of each) - shows how the diffuse works (NOTE: this doesn't appear to work now, but it worked in a previous iteration of my code - see earlier commits)
            //data_.at(i) = calculateDiffuse(spheres_.at(0), ray, pointLights_.at(0));
            
            // the full Phong lighting
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
