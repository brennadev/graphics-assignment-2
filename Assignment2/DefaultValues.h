//
//  DefaultValues.h
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

// A bunch of default values based off of the input file specification

#ifndef DefaultValues_h
#define DefaultValues_h

#include <string>
#include "CustomTypes.h"

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGHT = 480;

const string DEFAULT_OUTPUT_FILE = "raytraced.bmp";
const Camera DEFAULT_CAMERA = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, 45};
const Color DEFAULT_BACKGROUND_COLOR = {0, 0, 0};
const Material DEFAULT_MATERIAL = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0}, 5};
const Color DEFAULT_AMBIENT_LIGHT = {0, 0, 0};
const int DEFAULT_MAX_DEPTH = 5;

#endif /* DefaultValues_h */
