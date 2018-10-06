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
    
    //data_ = new Color[width * height];
    
    outputFileName_ = outputFileName;
    
    // set all points in the image to the background color
    for (int i = 0; i < width * height; i++) {
        data_.push_back(background);
    }
}

Image::~Image() {
    //delete data_;
}

void Image::writeImageToFile() {
    const char *outputNameAsCString = outputFileName_.c_str();
    
    int onePast = strlen(outputNameAsCString);
    
    switch (outputNameAsCString[onePast - 1]) {
        case 'g':
            if (outputNameAsCString[onePast - 2] == 'p' || outputNameAsCString[onePast - 2] == 'e') {
                // jpeg
                stbi_write_jpg(outputNameAsCString, width_, height_, 4, data_.data(), 95);
            } else {
                // png
                stbi_write_png(outputNameAsCString, width_, height_, 4, data_.data(), width_ * 4);
            }
            break;
            
        case 'a':
            // tga
            stbi_write_tga(outputNameAsCString, width_, height_, 4, data_.data());
            break;
            
        case 'p':
            // bmp
            stbi_write_bmp(outputNameAsCString, width_, height_, 4, data_.data());
            break;
        default:
            // bmp
            stbi_write_bmp(outputNameAsCString, width_, height_, 4, data_.data());
            break;
    }
}
