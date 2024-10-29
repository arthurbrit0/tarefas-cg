#ifndef HEADER_H
#define HEADER_H
#include <cmath>

class Vector3D {
public:
    float x, y, z;

    Vector3D(float x_=0, float y_=0, float z_=0) : x(x_), y(y_), z(z_) {}

    Vector3D operator + (const Vector3D& v) const { return Vector3D(x + v.x, y + v.y, z + v.z); }
    Vector3D operator - (const Vector3D& v) const { return Vector3D(x - v.x, y - v.y, z - v.z); }
    Vector3D operator * (float s) const { return Vector3D(x * s, y * s, z * s); }
    Vector3D operator * (const Vector3D& v) const { return Vector3D(x * v.x, y * v.y, z * v.z); }
    Vector3D operator - () const { return Vector3D(-x, -y, -z); }

    float dot(const Vector3D& v) const { return x * v.x + y * v.y + z * v.z; }
    float length() const { return std::sqrt(this->dot(*this)); }
    Vector3D normalize() const {
        float n = this->length();
        return Vector3D(x / n, y / n, z / n);
    }
};

class Ray3D {
public:
    Vector3D origin;
    Vector3D direction;

    Ray3D(Vector3D origin_, Vector3D end_) : origin(origin_) {
        Vector3D dir = end_ - origin;
        direction = dir.normalize();
    }
};

class Sphere {
public:
    Vector3D center;
    float radius;

    Sphere(Vector3D center_, float radius_) : center(center_), radius(radius_) {}

    bool intersect(const Ray3D &ray, float &t) const {
        Vector3D v = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2 * ray.direction.dot(v);
        float c = v.dot(v) - radius * radius;
        float delta = b * b - 4 * a * c;

        if (delta > 0) {
            float t1 = (-b + std::sqrt(delta)) / (2.0f * a);
            float t2 = (-b - std::sqrt(delta)) / (2.0f * a);
            float t_cand = std::fmin(t1, t2);
            if (t_cand > 0 && t_cand < t) {
                t = t_cand;
                return true;
            }
        } else if (delta == 0) {
            float t1 = -b / (2.0f * a);
            if (t1 > 0 && t1 < t) {
                t = t1;
                return true;
            }
        }
        return false;
    }
};

class LightSource {
public:
    Vector3D position;
    Vector3D intensity;

    LightSource(Vector3D position_, Vector3D intensity_) : position(position_), intensity(intensity_) {}
};

#endif
