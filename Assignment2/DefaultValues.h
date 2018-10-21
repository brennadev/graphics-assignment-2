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
using namespace std;

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGHT = 480;

const string DEFAULT_OUTPUT_FILE = "raytraced.ppm";

/// Note: right vector and v vector aren't set - will be set in `Image` when `Image` instance is created
const Camera DEFAULT_CAMERA = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, 45};

const Color DEFAULT_BACKGROUND_COLOR = {0, 0, 0};
const Material DEFAULT_MATERIAL = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0}, 5, {0, 0, 0}, 1};
/// Intersection where everything is 0/false and has the default material
const Intersection DEFAULT_INTERSECTION = {false, {0,0,0}, {0,0,0}, DEFAULT_MATERIAL, -1};
const Color DEFAULT_AMBIENT_LIGHT = {0, 0, 0};

const int DEFAULT_MAX_DEPTH = 5;

const Color BLACK_COLOR = {0, 0, 0};

#endif
