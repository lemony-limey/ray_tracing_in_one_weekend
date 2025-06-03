#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& r_in,
        const hit_record& rec,
        colour& attenuation,
        ray& scattered
    ) const
    {
        return false;
    }
};

class lambertian : public material
{
public:
    // Constructors
    lambertian(const colour& albedo) : albedo(albedo) {}

    // Public methods
    bool scatter(
        const ray& r_in,
        const hit_record& rec,
        colour& attenuation,
        ray& scattered
    ) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Handle case where scatter direction is near zero
        if (scatter_direction.near_zero()) { scatter_direction = rec.normal; }

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true; // We have chosen to always scatter and attenuate light.
    }

private:
    colour albedo;
};

class metal : public material
{
public:
    // Constructors
    metal(const colour& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    // Public methods
    bool scatter(
        const ray& r_in,
        const hit_record& rec,
        colour& attenuation,
        ray& scattered
    ) const override
    {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }

private:
    colour albedo;
    double fuzz;
};

/**
 * A dielectric material is one which, when a light ray hits it, splits the ray into a
 * reflected ray and a refracted (transmitted) ray.
 * Clear materials such as water, glass and diamond are all dielectrics.
 * Instead of producing both rays here, we will randomly choose between reflection and
 * refraction, generating only one scattered ray per interaction.
 *
 * Ray attenuation is 1 here, as glass absorbs nothing.
 */
class dielectric : public material
{
public:
    // Constructors
    dielectric(double refraction_index) : refractive_index(refraction_index) {}

    // Public methods
    bool scatter(
        const ray& r_in,
        const hit_record& rec,
        colour& attenuation,
        ray& scattered
    ) const override
    {
        attenuation = colour(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0/refractive_index) : refractive_index;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - (cos_theta * cos_theta));

        bool cannot_refract = ri * sin_theta > 1;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
        {
            direction = reflect(unit_direction, rec.normal);
        }
        else
        {
            direction = refract(unit_direction, rec.normal, ri);
        }

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    // This value represents either the refractive index in a vacuum or air, or the
    // ratio of the material's refractive index over the refractive index of the
    // enclosing media.
    double refractive_index;

    // Private methods
    // We use Schlick's approximation for reflectance.
    static double reflectance(double cosine, double refractive_index)
    {
        auto r0 = (1 - refractive_index) / (1 + refractive_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};

#endif // MATERIAL_H