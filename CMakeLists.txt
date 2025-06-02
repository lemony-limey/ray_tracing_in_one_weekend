cmake_minimum_required(VERSION 3.30)
project(ray_tracing_in_one_weekend)

set(CMAKE_CXX_STANDARD 23)

add_executable(ray_tracing_in_one_weekend src/main.cpp
        src/camera.h
        src/colour.h
        src/hittable.h
        src/hittable_list.h
        src/interval.h
        src/ray.h
        src/sphere.h
        src/vec3.h
)
