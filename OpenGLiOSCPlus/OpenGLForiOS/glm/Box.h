//
//  Box.h
//  GLMapLib2.0
//
//  Created by fullname on 10/28/16.
//  Copyright © 2016 nopwang. All rights reserved.
//

#ifndef Box_h
#define Box_h

#include "math_type.h"

namespace glm
{
    template <typename T>
    class Box2
    {
    public:
        Vector2<T>  min;
        Vector2<T>  max;
        
        Box2():min(0), max(0) { }
        
        Box2(const Vector2<T> &_min, const Vector2<T> &_max):min(_min), max(_max) { }
        
        Box2(T minx, T miny, T maxx, T maxy):min(minx, miny), max(maxx, maxy) { }
        
        bool operator == (const Box2& rhs) const { return (min == rhs.min && max == rhs.max); }
        
    public:
        
        Box2 shrink(T v) const { return Box2(min + v, max - v); }
        
        Box2 expand(T v) const { return Box2(min - v, max + v); }
        
        Box2 shrink(const Vector2<T> &v) const { return Box2(min + v, max - v); }
        
        Box2 expand(const Vector2<T> &v) const { return Box2(min - v, max + v); }
        
        bool hold(const Vector2<T> &v) const
        {
            map_assert(min.x <= max.x && min.y <= max.y);
            return v.x >= min.x && v.x <= max.x && v.y >= min.y && v.y <= max.y;
        }
        
        void getVertices(Vector2<T> (&values)[4]) const
        {
            values[0] = min;
            values[1] = Vector2<T>(max.x, min.y);
            values[2] = max;
            values[3] = Vector2<T>(min.x, max.y);
        }
    };
    
    template <typename T>
    class Box3
    {
    public:
        Vector3<T>  min;
        Vector3<T>  max;
        
        Box3():min(0), max(0) { }
        
        Box3(const Vector3<T> &_min, const Vector3<T> &_max):min(_min), max(_max) { }
        
        Box3(T minx, T miny, T minz, T maxx, T maxy, T maxz):min(minx, miny, minz), max(maxx, maxy, maxz){ }
        
    };
}

#endif /* Box_h */
