#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main()
{
    // The list stores all objects that exist within the world.
    hittable_list world;

    // Lambertian materials diffuse light and appear dull.
    auto material_ground = make_shared<lambertian>(colour(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(colour(0.1, 0.2, 0.5));

    // Dielectric materials are clear and can reflect and refract light.
    auto material_left   = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);

    // Metallic materials reflect light and appear shiny.
    auto material_right  = make_shared<metal>(colour(0.8, 0.6, 0.2), 1.0);

    // Add the objects into the scene.
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0), 0.5, material_right));

    // Camera setup
    camera camera;
    camera.aspect_ratio      = 16.0 / 9.0;  // This is an ideal value.
    camera.image_width       = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth         = 50;

    // Generate the image
    camera.render(world);

    return 0;
}