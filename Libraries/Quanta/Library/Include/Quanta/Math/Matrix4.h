#ifndef QUANTA_MATRIX4_H
#define QUANTA_MATRIX4_H

namespace Quanta {
    class Matrix4 {
    public:
        float components[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        static Matrix4 identity();
        float& operator[](const int index);
        const float& operator[](const int index) const;
        Matrix4 operator*(Matrix4 matrix);
        Matrix4& operator*=(Matrix4 matrix);
        void reset();
        void invert();
    };
}

#endif
