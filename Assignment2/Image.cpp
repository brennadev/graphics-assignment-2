//
//  Image.cpp
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

#include "Image.h"

void Image::writeImageToFile() {
    /*const char *outputNameAsCString = outputFileName.c_str();
    
    int onePast = strlen(outputNameAsCString);
    
    switch (onePast - 1) {
        case 'g':
            const int secondToLastLocation = outputFileName.length() - 2;
            if (outputNameAsCString[onePast - 2] == 'p' || outputNameAsCString[onePast - 2] == 'e') {
                // jpeg
                stbi_write_jpg(outputNameAsCString, width, height, 4, data, 95);
            } else {
                // png
                stbi_write_png(outputNameAsCString, width, height, 4, data, width * 4);
            }
            break;
            
        case 'a':
            // tga
            stbi_write_tga(outputNameAsCString, width, height, 4, data);
            break;
            
        case 'p':
            // bmp
            stbi_write_bmp(outputNameAsCString, width, height, 4, data);
            break;
        default:
            // bmp
            stbi_write_bmp(outputNameAsCString, width, height, 4, data);
            break;
    }*/
}
