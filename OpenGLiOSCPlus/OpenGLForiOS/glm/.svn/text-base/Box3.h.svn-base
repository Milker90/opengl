//
//  Box3.h
//  GLMapLib2.0
//
//  Created by fullname on 12/7/16.
//  Copyright © 2016 nopwang. All rights reserved.
//

#ifndef Box3_h
#define Box3_h

#include "math_type.h"

namespace glm
{
    template <typename T>
    class Box3
    {
    public:
        Vector3<T>  min;
        Vector3<T>  max;
        
        Box3()
        :min(0)
        ,max(0)
        {
        }
        
        Box3(const Vector3<T> &_min, const Vector3<T> &_max)
        :min(_min)
        ,max(_max)
        {
        }
        
        Box3(T minx, T miny, T minz, T maxx, T maxy, T maxz)
        :min(minx, miny, minz)
        ,max(maxx, maxy, maxz)
        {
        }
        
        template <typename Q>
        explicit Box3(const Box3<Q>& box)
        :min(box.min)
        ,max(box.max)
        {
        }
        
        template <typename Q>
        Box3(const Vector3<Q> *p, const size_t num)
        :min(0)
        ,max(0)
        {
            if (num == 0) return;
            min = max = *p;
            for (size_t i = 1; i < num; ++i)
            {
                if (p[i].x < min.x)
                    min.x = p[i].x;
                else if (p[i].x > max.x)
                    max.x = p[i].x;
                if (p[i].y < min.y)
                    min.y = p[i].y;
                else if (p[i].y > max.y)
                    max.y = p[i].y;
                if (p[i].z < min.z)
                    min.z = p[i].z;
                else if (p[i].z > max.z)
                    max.z = p[i].z;
            }
        }
        
    public:
        
        bool operator == (const Box3& rhs) const
        {
            return min == rhs.min && max == rhs.max;
        }
        
        bool operator != (const Box3& rhs) const
        {
            return min != rhs.min || max != rhs.max;
        }
        
        template <typename Q>
        Box3& operator += (const Vector3<Q> rhs)
        {
            min += rhs;
            max += rhs;
            return *this;
        }
        
        template <typename Q>
        Box3& operator -= (const Vector3<Q> rhs)
        {
            min -= rhs;
            max -= rhs;
            return *this;
        }
        
    public:
        const Box3 shrink(T v) const { return Box3(min + v, max - v); }
        
        const Box3 expand(T v) const { return Box3(min - v, max + v); }
        
        const Box3 shrink(const Vector2<T> &v) const { return Box3(min + v, max - v); }
        
        const Box3 expand(const Vector2<T> &v) const { return Box3(min - v, max + v); }
        
        bool hold(const Vector3<T> &v) const
        {
            map_assert(min.x <= max.x && min.y <= max.y && min.z <= max.z);
            return
            v.x >= min.x && v.x <= max.x &&
            v.y >= min.y && v.y <= max.y &&
            v.z >= min.z && v.z <= max.z;
        }
        
        void getVertices(Vector3<T> (&values)[8]) const
        {
            values[0] = Vector3<T>(min.x, min.y, min.z);
            values[1] = Vector3<T>(max.x, min.y, min.z);
            values[2] = Vector3<T>(max.x, max.y, min.z);
            values[3] = Vector3<T>(min.x, max.y, min.z);
            values[4] = Vector3<T>(min.x, min.y, max.z);
            values[5] = Vector3<T>(max.x, min.y, max.z);
            values[6] = Vector3<T>(max.x, max.y, max.z);
            values[7] = Vector3<T>(min.x, max.y, max.z);
        }
    };
    
}   // namespace glm end

#endif /* Box3_h */
