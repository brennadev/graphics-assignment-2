//
//  CustomTypes.h
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

#ifndef CustomTypes_h
#define CustomTypes_h

//#include <iostream>
using namespace std;

struct Vector2 {
    float x;
    float y;
};


/// Point/vector in 3d space
struct Vector3 {
    float x;
    float y;
    float z;
};

/*istream &operator>>(istream &input, Vector3 &value) {
    input >> value.x >> value.y >> value.z;
    return input;
}*/


/// RGB-based color - all stored as floats from 0 to 1 to prevent math errors
struct Color {
    float red;
    float green;
    float blue;
};

/*istream &operator>>(istream &input, Color &value) {
    return input >> value.red >> value.green >> value.blue;
}*/


struct Camera {
    Vector3 position;
    Vector3 viewingDirection;
    Vector3 up;
    float halfAngle;
};


struct Sphere {
    Vector3 center;
    float radius;
};


struct Material {
    Color ambient;
    Color diffuse;
    Color specular;
    float phongCosinePower;
};


struct DirectionalLight {
    Color color;
    Vector3 direction;
};


struct PointLight {
    Color color;
    Vector3 location;
};


struct SpotLight {
    Color color;
    Vector3 location;
    Vector3 direction;
    float angle1;
    float angle2;
};




#endif /* CustomTypes_h */
