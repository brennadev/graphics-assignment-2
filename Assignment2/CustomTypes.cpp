//
//  CustomTypes.cpp
//  Assignment2
//
//  Created by Brenna Olson on 10/7/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

// Vector math operations

#include "CustomTypes.h"
#include <cmath>

#pragma mark - Vector Operations
Vector3 operator+(const Vector3 &leftVector, const Vector3 &rightVector) {
    return {leftVector.x + rightVector.x, leftVector.y + rightVector.y, leftVector.z + rightVector.z};
}

Vector3 operator-(const Vector3 &leftVector, const Vector3 &rightVector) {
    return {leftVector.x - rightVector.x, leftVector.y - rightVector.y, leftVector.z - rightVector.z};
}

Vector3 operator*(const float &constant, const Vector3 &vector) {
    return {constant * vector.x, constant * vector.y, constant * vector.z};
}

Vector3 operator*(const Vector3 &vector, const float &constant) {
    return {constant * vector.x, constant * vector.y, constant * vector.z};
}

Vector3 operator/(const Vector3 &vector, const float &constant) {
    return {vector.x / constant, vector.y / constant, vector.z / constant};
}

float dot(const Vector3 &firstVector, const Vector3 &secondVector) {
    return firstVector.x * secondVector.x + firstVector.y * secondVector.y + firstVector.z * secondVector.z;
}

Vector3 cross(const Vector3 &firstVector, const Vector3 &secondVector) {
    return {firstVector.y * secondVector.z - firstVector.z * secondVector.y,
            firstVector.z * secondVector.x - firstVector.x * secondVector.z,
            firstVector.x * secondVector.y - firstVector.y * secondVector.x};
}


float length(const Vector3 &vector) {
    return sqrt(dot(vector, vector));
}

Vector3 normalize(const Vector3 &vector) {
    return vector / length(vector);
}


#pragma mark - Color Operations
float clamp(const float &value) {
    if (value < 0) {
        return 0;
    } else if (value > 1) {
        return 1;
    } else {
        return value;
    }
}


Color operator*(const Color &firstColor, const Color &secondColor) {
    return {clamp(firstColor.red * secondColor.red),
            clamp(firstColor.green * secondColor.green),
            clamp(firstColor.blue * secondColor.blue)};
}


Color operator*(const Color &color, const float &constant) {
    return {color.red * constant, color.green * constant, color.blue * constant};
}

Color operator+(const Color &firstColor, const Color &secondColor) {
    return {firstColor.red + secondColor.red, firstColor.green + secondColor.green, firstColor.blue + secondColor.blue};
}
