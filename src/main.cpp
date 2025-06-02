#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main()
{
    // The list stores all objects that exist within the world.
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera camera;
    camera.aspect_ratio      = 16.0 / 9.0;  // This is an ideal value.
    camera.image_width       = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth         = 50;

    // Generate the image
    camera.render(world);

    return 0;
}