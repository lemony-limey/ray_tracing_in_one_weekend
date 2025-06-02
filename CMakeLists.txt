cmake_minimum_required(VERSION 3.30)
project(ray_tracing_in_one_weekend)

set(CMAKE_CXX_STANDARD 23)

add_executable(ray_tracing_in_one_weekend main.cpp
        colour.h
        hittable.h
        hittable_list.h
        ray.h
        sphere.h
        vec3.h
)
