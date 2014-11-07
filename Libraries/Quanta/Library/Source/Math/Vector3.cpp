#include <math.h>
#include "Quanta/Math/Vector3.h"

namespace Quanta {
    Vector3::Vector3() {
        components[0] = 0;
        components[1] = 0;
        components[2] = 0;
    }

    Vector3::Vector3(float x, float y, float z) {
        components[0] = x;
        components[1] = y;
        components[2] = z;
    }

    void Vector3::negate() {
        operator*=(-1);
    }

    Vector3 Vector3::getNegated() const {
        Vector3 negated = *this;
        negated.negate();
        return negated;
    }

    Vector3 Vector3::operator*(float factor) const {
        Vector3 result = *this;
        result *= factor;
        return result;
    }

    Vector3& Vector3::operator*=(float factor) {
        components[0] *= factor;
        components[1] *= factor;
        components[2] *= factor;
        return *this;
    }

    Vector3& Vector3::operator/=(float factor) {
        components[0] /= factor;
        components[1] /= factor;
        components[2] /= factor;
        return *this;
    }

    float& Vector3::operator[](const int index) {
        return components[index];
    }

    const float& Vector3::operator[](const int index) const {
        return components[index];
    }

    float Vector3::dot(Vector3 operand1, Vector3 operand2) {
        return operand1[0]*operand2[0] + operand1[1]*operand2[1] + operand1[2]*operand2[2];
    }

    Vector3 Vector3::operator+(Vector3 vector) {
        Vector3 result = *this;
        result += vector;
        return result;
    }

    Vector3& Vector3::operator+=(Vector3 other) {
        components[0] += other[0];
        components[1] += other[1];
        components[2] += other[2];
        return *this;
    }

    Vector3 Vector3::operator-(const Vector3 vector) const {
        Vector3 result = *this;
        result -= vector;
        return result;
    }

    Vector3& Vector3::operator-=(Vector3 other) {
        components[0] -= other[0];
        components[1] -= other[1];
        components[2] -= other[2];
        return *this;
    }

    void Vector3::reset() {
        components[0] = 0;
        components[1] = 0;
        components[2] = 0;
    }

    Vector3 Vector3::cross(Vector3 operand1, Vector3 operand2) {
        Vector3 result;

        result[0] = operand1[1]*operand2[2] - operand1[2]*operand2[1];
        result[1] = operand1[2]*operand2[0] - operand1[0]*operand2[2];
        result[2] = operand1[0]*operand2[1] - operand1[1]*operand2[0];

        return result;
    }

    Vector3 Vector3::getNormalized() {
        Vector3 result = *this;
        result.normalize();
        return result;
    }

    void Vector3::normalize() {
        operator/=(getLength());
    }

    Vector3 Vector3::zero() {
        return Vector3(0, 0, 0);
    }

    float Vector3::getLength() {
        return sqrt(getSquaredLength());
    }

    float Vector3::getSquaredLength() {
        return pow(components[0], 2) + pow(components[1], 2) + pow(components[2], 2);
    }
}
