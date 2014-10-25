#include "Quanta/Math/Vector3.h"

namespace Quanta {
    class Quaternion;

    class Point3D {
        Vector3 vector;
    public:
        Point3D(float x, float y, float z);
        Point3D(Vector3 vector);
        Point3D();
        Vector3& getVector();
        float& operator[](const int index);
        const float& operator[](const int index) const;
        Point3D operator-(Vector3 other);
        Vector3 operator-(Point3D other);
        Point3D operator+(Vector3 other);
        Point3D& operator+=(Vector3 other);
        operator Vector3();
        Point3D getRotated(Quaternion &rotation);
    };
}
