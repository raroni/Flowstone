namespace Quanta {
    class Matrix4;

    class Quaternion {
    public:
        Quaternion(float real, Vector3 imaginaries);
        float real;
        Vector3 imaginaries;
        Quaternion operator*(Quaternion &other);
        Quaternion& operator*=(Quaternion other);
        static Quaternion identity();
        operator Matrix4();
        Quaternion getConjugate();
        static Quaternion slerpWithLimit(Quaternion &origin, Quaternion &destination, float angleLimit);
        static float dot(Quaternion &operandA, Quaternion &operandB);
        Quaternion& operator*=(float factor);
        Quaternion operator*(float factor);
        Quaternion& operator+=(Quaternion other);
        Quaternion operator+(Quaternion other);
        float getLength();
    };
}
