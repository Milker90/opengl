//
//  Box2.h
//  GLMapLib2.0
//
//  Created by fullname on 12/7/16.
//  Copyright © 2016 nopwang. All rights reserved.
//

#ifndef Box2_h
#define Box2_h

#include "math_type.h"

namespace glm
{
    template <typename T>
    class Box2
    {
    public:
        Vector2<T>  min;
        Vector2<T>  max;
        
        Box2()
        :min(0)
        ,max(0)
        {
        }
        
        Box2(const Vector2<T> &_min, const Vector2<T> &_max)
        :min(_min)
        ,max(_max)
        {
        }
        
        Box2(T minx, T miny, T maxx, T maxy)
        :min(minx, miny)
        ,max(maxx, maxy)
        {
        }
        
        template <typename Q>
        explicit Box2(const Box2<Q>& box)
        :min(box.min)
        ,max(box.max)
        {
        }
        
        template <typename Q>
        Box2(const Vector2<Q> *p, const size_t num)
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
            }
        }
        
    public:
        
        bool operator == (const Box2& rhs) const
        {
            return min == rhs.min && max == rhs.max;
        }
        
        bool operator != (const Box2& rhs) const
        {
            return min != rhs.min || max != rhs.max;
        }
        
        template <typename Q>
        Box2& operator += (const Vector2<Q> rhs)
        {
            min += rhs;
            max += rhs;
            return *this;
        }
        
        template <typename Q>
        Box2& operator -= (const Vector2<Q> rhs)
        {
            min -= rhs;
            max -= rhs;
            return *this;
        }
        
    public:
        
        const Box2 shrink(T v) const { return Box2(min + v, max - v); }
        
        const Box2 expand(T v) const { return Box2(min - v, max + v); }
        
        const Box2 shrink(const Vector2<T> &v) const { return Box2(min + v, max - v); }
        
        const Box2 expand(const Vector2<T> &v) const { return Box2(min - v, max + v); }
        
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
    
}   // namespace glm end

#endif /* Box2_h */
