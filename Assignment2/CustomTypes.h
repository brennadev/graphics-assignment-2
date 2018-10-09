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

// 3d vector math
Vector3 operator+(const Vector3 &leftVector, const Vector3 &rightVector);
Vector3 operator-(const Vector3 &leftVector, const Vector3 &rightVector);
Vector3 operator*(const float &constant, const Vector3 &vector);
Vector3 operator/(const Vector3 &vector, const float &constant);
float dot(const Vector3 &firstVector, const Vector3 &secondVector);
Vector3 cross(const Vector3 &firstVector, const Vector3 &secondVector);
float length(const Vector3 &vector);
Vector3 normalize(const Vector3 &vector);


struct Ray {
    Vector3 origin;
    Vector3 direction;
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
    Vector3 right;
    float halfAngle;
};


struct Material {
    Color ambient;
    Color diffuse;
    Color specular;
    float phongCosinePower;
};


struct Sphere {
    Vector3 center;
    float radius;
    Material material;
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
