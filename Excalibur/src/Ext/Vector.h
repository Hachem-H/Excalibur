#pragma once

#include <cglm/cglm.h>

typedef struct Vec2_t
{
    union 
    {
        vec2 glmvec;

        struct
        {
            float x; 
            float y;
        };

        struct
        {
            float width; 
            float height;
        };
    };
} Vec2;

typedef struct Vec3_t
{
    union 
    {
        vec3 glmvec;

        struct
        {
            float x; 
            float y;
            float z;
        };

        struct
        {
            float r; 
            float g;
            float b;
        };
    };
} Vec3;

typedef struct Vec4_t
{
    union 
    {
        vec4 glmvec;

        struct
        {
            float x; 
            float y;
            float z;
            float w;
        };

        struct
        {
            float r; 
            float g;
            float b;
            float a;
        };
    };
} Vec4;

typedef struct Rect
{
    union 
    {
        vec4 glmvec;
        Vec4 base;

        struct
        {
            float x; 
            float y;
            float w;
            float h;
        };
    };
} Rect;