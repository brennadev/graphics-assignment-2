//
//  CustomTypes.cpp
//  Assignment2
//
//  Created by Brenna Olson on 10/7/18.
//  Copyright © 2018 Brenna Olson. All rights reserved.
//

// Vector math operations

#include "CustomTypes.h"

Vector3 operator+(const Vector3 &leftVector, const Vector3 &rightVector) {
    return {leftVector.x + rightVector.x, leftVector.y + rightVector.y, leftVector.z + rightVector.z};
}

Vector3 operator-(const Vector3 &leftVector, const Vector3 &rightVector) {
    return {leftVector.x - rightVector.x, leftVector.y - rightVector.y, leftVector.z - rightVector.z};
}

Vector3 operator*(const float &constant, const Vector3 &vector) {
    return {constant * vector.x, constant * vector.y, constant * vector.z};
}

Vector3 operator/(const Vector3 &vector, const float &constant) {
    return {vector.x / constant, vector.y / constant, vector.z / constant};
}

Vector3 cross(const Vector3 &firstVector, const Vector3 &secondVector) {
    return {firstVector.y * secondVector.z - firstVector.z * secondVector.y,
            firstVector.z * secondVector.x - firstVector.x * secondVector.z,
            firstVector.x * secondVector.y - firstVector.y * secondVector.x};
}
