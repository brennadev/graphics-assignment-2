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
    
    width_ = width;
    height_ = height;
    outputFileName_ = outputFileName;
    spheres_ = spheres;
    directionalLights_ = directionalLights;
    pointLights_ = pointLights;
    spotLights_ = spotLights;
    ambientLights_ = ambientLights;
    
    // set all points in the image to the background color
    for (int i = 0; i < width * height; i++) {
        data_.push_back(background);
    }
    
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



Ray Image::generateRay(int xPosition, int yPosition) {
    float u = width_ / 2 * -1 + width_ * xPosition / width_;
    float v = height_ / 2 * -1 + height_ * yPosition / height_;
    
    
    
    // TODO: eventually get return value changed to correct value
    return {{0, 0, 0}, {0, 0, 0}};
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
