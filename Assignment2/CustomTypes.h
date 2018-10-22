//
//  CustomTypes.h
//  Assignment2
//
//  Created by Brenna Olson on 10/4/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

// Many types used throughout the ray tracer program


#ifndef CustomTypes_h
#define CustomTypes_h
#include <iostream>
using namespace std;

# pragma mark - Vectors and Vector Operations
// TODO: remove if not used
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


// 3d vector comparison
bool operator==(const Vector3 &leftVector, const Vector3 &rightVector);


// 3d vector math
Vector3 operator+(const Vector3 &leftVector, const Vector3 &rightVector);
Vector3 operator-(const Vector3 &leftVector, const Vector3 &rightVector);
Vector3 operator*(const float &constant, const Vector3 &vector);
Vector3 operator*(const Vector3 &vector, const float &constant);
Vector3 operator/(const Vector3 &vector, const float &constant);
float dot(const Vector3 &firstVector, const Vector3 &secondVector);
Vector3 cross(const Vector3 &firstVector, const Vector3 &secondVector);
float length(const Vector3 &vector);
Vector3 normalize(const Vector3 &vector);
float clamp(const float &value);

# pragma mark - Color and Color Operations
/// RGB-based color - all stored as floats from 0 to 1 to prevent math errors
struct Color {
    float red;
    float green;
    float blue;
};


/// Keep a color value between 0 and 1 (float)
float clamp(const float &value);

/// Multiply 2 colors together, component-by-component. Values below 0 or above 1 are clamped appropriately.
Color operator*(const Color &firstColor, const Color &secondColor);

Color operator*(const Color &color, const float &constant);
Color operator*(const float &constant, const Color &color);

Color operator+(const Color &firstColor, const Color &secondColor);
Color operator+=(const Color &firstColor, const Color &secondColor);


# pragma mark - Non-Light Objects
struct Material {
    Color ambient;
    Color diffuse;
    Color specular;
    float phongCosinePower;
    Color transmissive;
    float indexOfRefraction;
};


struct Intersection {
    bool hasIntersection;
    /// Where the intersection occurs if there is one (check hasIntersection first)
    Vector3 location;
    /// Normal at the location of intersection (only valid if hasIntersection is true)
    Vector3 normal;
    /// Material of the object at the intersection (only valid if hasIntersection is true)
    Material material;
    float t;
};


struct Ray {
    Vector3 origin;
    Vector3 direction;
    Intersection intersection;
};


struct Camera {
    // input-provided values
    Vector3 position;
    Vector3 viewingDirection;
    Vector3 up;
    
    // calculated values
    Vector3 right;
    Vector3 v;
    
    float halfAngle;
};


struct Sphere {
    Vector3 center;
    float radius;
    Material material;
};


# pragma mark - Lights
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


# pragma mark - Triangles

struct TriangleVertex {
    Vector3 location;
    Vector3 normal;
};

struct Triangle {
    TriangleVertex vertex1;
    TriangleVertex vertex2;
    TriangleVertex vertex3;
};


# pragma mark - ostream overloads
ostream &operator<<(ostream &output, Vector3 value);

#endif /* CustomTypes_h */
