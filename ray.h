#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
public:
    ray() {}

    // Constructor
    ray(const point3& origin, const vec3& direction) : orig(origin),
        dir(direction)
    {}

    // Getters
    [[nodiscard]] const point3& origin() const { return orig; }
    [[nodiscard]] const vec3& direction() const { return dir; }

    // Methods
    point3 at(double t) const
    {
        return orig + (t * dir);
    }

private:
    // Attributes
    point3 orig;
    vec3 dir;
};

#endif // RAY_H