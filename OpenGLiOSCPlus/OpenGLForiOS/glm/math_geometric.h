//
//  math_geometric.h
//  SOSOMap
//
//  Created by samczli on 25/12/14.
//  Copyright (c) 2014 Tencent. All rights reserved.
//

#ifndef SOSOMap_math_geometric_h
#define SOSOMap_math_geometric_h

#include "math_type.h"
#include <limits>
#include <math.h>

namespace glm {
    
    template <typename T>
    T dot(const T& x, const T& y);
    template <typename T>
    T dot(const Vector2<T>& v1, const Vector2<T>& v2);
    template <typename T>
    T dot(const Vector3<T>& v1, const Vector3<T>& v2);
    template <typename T>
    T dot(const Vector4<T>& v1, const Vector4<T>& v2);
    
//    template <typename T>
//    T length(const T& x);
    template <typename T>
    T length(const Vector2<T>& x);
    template <typename T>
    T length(const Vector3<T>& x);
//    template <typename T>
//    T length(const Vector4<T>& x);
    
//    template <typename T>
//    T squareDistance(const T& p0, const T& p1);
    template <typename T>
    T squareDistance(const Vector2<T>& p0, const Vector2<T>& p1);
    template <typename T>
    T squareDistance(const Vector3<T>& p0, const Vector3<T>& p1);
    
//    template <typename T>
//    T distance(const T& p0, const T& p1);
    template <typename T>
    T distance(const Vector2<T>& p0, const Vector2<T>& p1);
    template <typename T>
    T distance(const Vector3<T>& p0, const Vector3<T>& p1);
    
    template <typename T>
    Vector3<T> cross(const Vector3<T>& p0, const Vector3<T>& p1);
    
    
    // According to issue 10 GLSL 1.10 specification, if length(x) == 0 then result is undefine and generate an error,
    // while current implemtation does not accepted this kind of input for easier debugging.
    template <typename T>
    T normalize(const T& p);
    template <typename T>
    Vector2<T> normalize(const Vector2<T>& p);
    template <typename T>
    Vector3<T> normalize(const Vector3<T>& p);
    template <typename T>
    Vector4<T> normalize(const Vector4<T>& p);
    
    // reflect
    template <typename T>
    T reflect(const T& I, const T& N);
    
    // refract
    template <typename T>
    T refract(const T& I, const T& N, const T& eta);
    template <typename T, template <typename> class vecType>
    vecType<T> refract(vecType<T> const & I, vecType<T> const & N, T const & eta);
    
    // max
    template <typename T>
    T max(const T *p, const size_t num);
    template <typename T>
    Vector2<T> max(const Vector2<T> *p, const size_t num);
    template <typename T>
    Vector3<T> max(const Vector3<T> *p, const size_t num);
    template <typename T>
    Vector4<T> max(const Vector4<T> *p, const size_t num);
    
    // min
    template <typename T>
    T min(const T *p, const size_t num);
    template <typename T>
    Vector2<T> min(const Vector2<T> *p, const size_t num);
    template <typename T>
    Vector3<T> min(const Vector3<T> *p, const size_t num);
    template <typename T>
    Vector4<T> min(const Vector4<T> *p, const size_t num);
    
    // implementations
    /////////////////////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    inline T dot(const T& x, const T& y)
    {
        return x * y;
    }
    
    template <typename T>
    inline T dot(const Vector2<T>& v1, const Vector2<T>& v2)
    {
        Vector2<T> tmp(v1 * v2);
        return tmp.x + tmp.y;
    }
    
    template <typename T>
    inline T dot(const Vector3<T>& v1, const Vector3<T>& v2)
    {
        Vector3<T> tmp(v1 * v2);
        return tmp.x + tmp.y + tmp.z;
    }
    
    template <typename T>
    inline T dot(const Vector4<T>& v1, const Vector4<T>& v2)
    {
        Vector4<T> tmp(v1 * v2);
        return tmp.x + tmp.y + tmp.z + tmp.w;
    }
    
    template <typename T>
    inline T length(const Vector2<T>& v)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'length' only accept floating-point inputs");
        double sqr = v.x * v.x + v.y * v.y;
        return sqrt(sqr);
    }
    
    template <typename T>
    inline T length(const Vector3<T>& v)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'length' only accept floating-point inputs");
        double sqr = v.x * v.x + v.y * v.y + v.z * v.z;
        return sqrt(sqr);
    }
    
//    template <typename T>
//    inline T distance(const T& p0, const T& p1)
//    {
//        assertmsg(std::numeric_limits<T>::is_iec559, "'distance' only accept floating-point inputs");
//        return length(p1 - p0);
//    }
    
    template <typename T>
    inline T distance(const Vector2<T>& p0, const Vector2<T>& p1)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'distance' only accept floating-point inputs");
        return length(p1 - p0);
    }
    
    template <typename T>
    inline T distance(const Vector3<T>& p0, const Vector3<T>& p1)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'distance' only accept floating-point inputs");
        return length(p1 - p0);
    }

//    template <typename T>
//    inline T squareDistance(const T& p0, const T& p1)
//    {
//        assertmsg(std::numeric_limits<T>::is_iec559, "'distance' only accept floating-point inputs");
//        T v = p1 - p0;
//        return v * v;
//    }
    
    template <typename T>
    inline T squareDistance(const Vector2<T>& p0, const Vector2<T>& p1)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'distance' only accept floating-point inputs");
        return (p1 - p0).squareLength();
    }
    
    template <typename T>
    inline T squareDistance(const Vector3<T>& p0, const Vector3<T>& p1)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'distance' only accept floating-point inputs");
        return (p1 - p0).squareLength();
    }
    
    template <typename T>
    inline Vector3<T> cross(const Vector3<T>& p0, const Vector3<T>& p1)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'cross' only accept floating-point inputs");
        return Vector3<T>(p0.y * p1.z - p1.y * p0.z, p0.z * p1.x - p1.z * p0.x, p0.x * p1.y - p1.x * p0.y);
    }
    
    template <typename T>
    inline T normalize(const T& p)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'normalize' only accept floating-point inputs");
        return p < T(0) ? T(-1) : T(1);
    }
    
    template <typename T>
    inline Vector2<T> normalize(const Vector2<T>& p)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'normalize' only accept floating-point inputs");
        T len = length(p);
        assertmsg(len != 0, "Zero vector is not accepted.");
        return p / len;
    }
    
    template <typename T>
    inline Vector3<T> normalize(const Vector3<T>& p)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'normalize' only accept floating-point inputs");
        T len = length(p);
        assertmsg(len != 0, "Zero vector is not accepted.");
        return p / len;
    }
    
    template <typename T>
    inline Vector4<T> normalize(const Vector4<T>& p)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'normalize' only accept floating-point inputs");
        T len = length(p);
        assertmsg(len != 0, "Zero vector is not accepted.");
        return p / len;
    }
    
    template <typename T>
    inline T reflect(const T& I, const T& N)
    {
        return I - N * dot(N, I) * T(2);
    }
    
    template <typename T>
    inline T refract(const T& I, const T& N, const T& eta)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'refract' only accept floating-point inputs");
        T dotValue = dot(N, I);
        T k = T(1) - eta * eta * (T(1) - dotValue * dotValue);
        if(k < T(0))
            return T(0);
        else
            return eta * I - (eta * dotValue + sqrt(k)) * N;
    }
    
    template <typename T, template <typename> class vecType>
    inline vecType<T> refract(vecType<T> const & I, vecType<T> const & N, T const & eta)
    {
        assertmsg(std::numeric_limits<T>::is_iec559, "'refract' only accept floating-point inputs");
        T dotValue = dot(N, I);
        T k = T(1) - eta * eta * (T(1) - dotValue * dotValue);
        if(k < T(0))
            return vecType<T>(0);
        else
            return eta * I - (eta * dotValue + sqrt(k)) * N;
    }
    
    // clamp
    template <typename T>
    inline T clamp(T x, const T &min, const T &max)
    {
        x = x < min ? min : x;
        x = x > max ? max : x;
        return x;
    }
    
    template <typename T>
    inline Vector2<T> clamp(Vector2<T> v, const Vector2<T> &min, const Vector2<T> &max)
    {
        v.x = clamp(v.x, min.x, max.x);
        v.y = clamp(v.y, min.y, max.y);
        return v;
    }
    
    template <typename T>
    inline Vector3<T> clamp(Vector3<T> v, const Vector3<T> &min, const Vector3<T> &max)
    {
        v.x = clamp(v.x, min.x, max.x);
        v.y = clamp(v.y, min.y, max.y);
        v.z = clamp(v.z, min.z, max.z);
        return v;
    }
    
    template <typename T>
    inline Vector4<T> clamp(Vector4<T> v, const Vector4<T> &min, const Vector4<T> &max)
    {
        v.x = clamp(v.x, min.x, max.x);
        v.y = clamp(v.y, min.y, max.y);
        v.z = clamp(v.z, min.z, max.z);
        v.w = clamp(v.w, min.w, max.w);
        return v;
    }
    
    // mix
    template <typename T, typename F>
    inline T mix(T x, T y, F a)
    {
        return x * (F(1) - a) + y * a;
    }
    
    // max
    template <typename T>
    inline T max(const T *p, const size_t num)
    {
        T max = -std::numeric_limits<T>::max();
        for (size_t i = 0; i < num; ++i)
            max = (p[i] > max) ? p[i] : max;
        return max;
    }
    
    template <typename T>
    inline Vector2<T> max(const Vector2<T> *p, const size_t num)
    {
        Vector2<T> max(-std::numeric_limits<T>::max());
        for (size_t i = 0; i < num; ++i)
        {
            max.x = (p[i].x > max.x) ? p[i].x : max.x;
            max.y = (p[i].y > max.y) ? p[i].y : max.y;
        }
        return max;
    }
    
    template <typename T>
    inline Vector3<T> max(const Vector3<T> *p, const size_t num)
    {
        Vector3<T> max(-std::numeric_limits<T>::max());
        for (size_t i = 0; i < num; ++i)
        {
            max.x = (p[i].x > max.x) ? p[i].x : max.x;
            max.y = (p[i].y > max.y) ? p[i].y : max.y;
            max.z = (p[i].z > max.z) ? p[i].z : max.z;
        }
        return max;
    }
    
    template <typename T>
    inline Vector4<T> max(const Vector4<T> *p, const size_t num)
    {
        Vector4<T> max(-std::numeric_limits<T>::max());
        for (size_t i = 0; i < num; ++i)
        {
            max.x = (p[i].x > max.x) ? p[i].x : max.x;
            max.y = (p[i].y > max.y) ? p[i].y : max.y;
            max.z = (p[i].z > max.z) ? p[i].z : max.z;
            max.w = (p[i].w > max.w) ? p[i].w : max.w;
        }
        return max;
    }
    
    template <typename T>
    inline Vector2<T> max(const Vector2<T> &v0, const Vector2<T> &v1)
    {
        T x = v0.x > v1.x ? v0.x : v1.x;
        T y = v0.y > v1.y ? v0.y : v1.y;
        return Vector2<T>(x, y);
    }
    
    template <typename T>
    inline Vector3<T> max(const Vector3<T> &v0, const Vector3<T> &v1)
    {
        T x = v0.x > v1.x ? v0.x : v1.x;
        T y = v0.y > v1.y ? v0.y : v1.y;
        T z = v0.z > v1.z ? v0.z : v1.z;
        return Vector3<T>(x, y, z);
    }
    
    template <typename T>
    inline Vector4<T> max(const Vector4<T> &v0, const Vector4<T> &v1)
    {
        T x = v0.x > v1.x ? v0.x : v1.x;
        T y = v0.y > v1.y ? v0.y : v1.y;
        T z = v0.z > v1.z ? v0.z : v1.z;
        T w = v0.w > v1.w ? v0.w : v1.w;
        return Vector4<T>(x, y, z, w);
    }
    
    // min
    template <typename T>
    inline T min(const T *p, const size_t num)
    {
        T min = std::numeric_limits<T>::max();
        for (size_t i = 0; i < num; ++i)
            min = (p[i] < min) ? p[i] : min;
        return min;
    }
    
    template <typename T>
    inline Vector2<T> min(const Vector2<T> *p, const size_t num)
    {
        Vector2<T> min(std::numeric_limits<T>::max());
        for (size_t i = 0; i < num; ++i)
        {
            min.x = (p[i].x < min.x) ? p[i].x : min.x;
            min.y = (p[i].y < min.y) ? p[i].y : min.y;
        }
        return min;
    }
    
    template <typename T>
    inline Vector3<T> min(const Vector3<T> *p, const size_t num)
    {
        Vector2<T> min(std::numeric_limits<T>::max());
        for (size_t i = 0; i < num; ++i)
        {
            min.x = (p[i].x < min.x) ? p[i].x : min.x;
            min.y = (p[i].y < min.y) ? p[i].y : min.y;
            min.z = (p[i].z < min.z) ? p[i].z : min.z;
        }
        return min;
    }
    
    template <typename T>
    inline Vector4<T> min(const Vector4<T> *p, const size_t num)
    {
        Vector2<T> min(std::numeric_limits<T>::max());
        for (size_t i = 0; i < num; ++i)
        {
            min.x = (p[i].x < min.x) ? p[i].x : min.x;
            min.y = (p[i].y < min.y) ? p[i].y : min.y;
            min.z = (p[i].z < min.z) ? p[i].z : min.z;
            min.w = (p[i].w < min.w) ? p[i].w : min.w;
        }
        return min;
    }
    
    template <typename T>
    inline Vector2<T> min(const Vector2<T> &v0, const Vector2<T> &v1)
    {
        T x = v0.x < v1.x ? v0.x : v1.x;
        T y = v0.y < v1.y ? v0.y : v1.y;
        return Vector2<T>(x, y);
    }
    
    template <typename T>
    inline Vector3<T> min(const Vector3<T> &v0, const Vector3<T> &v1)
    {
        T x = v0.x < v1.x ? v0.x : v1.x;
        T y = v0.y < v1.y ? v0.y : v1.y;
        T z = v0.z < v1.z ? v0.z : v1.z;
        return Vector3<T>(x, y, z);
    }
    
    template <typename T>
    inline Vector4<T> min(const Vector4<T> &v0, const Vector4<T> &v1)
    {
        T x = v0.x < v1.x ? v0.x : v1.x;
        T y = v0.y < v1.y ? v0.y : v1.y;
        T z = v0.z < v1.z ? v0.z : v1.z;
        T w = v0.w < v1.w ? v0.w : v1.w;
        return Vector4<T>(x, y, z, w);
    }
    
    template <typename T>
    Box2<T> merge(const Box2<T>& b0, const Box2<T>& b1)
    {
        Vector2<T> min = glm::min(b0.min, b1.min);
        Vector2<T> max = glm::max(b0.max, b1.max);
        return Box2<T>(min, max);
    }
    
    template <typename T>
    Box3<T> merge(const Box3<T>& b0, const Box3<T>& b1)
    {
        Vector3<T> min = glm::min(b0.min, b1.min);
        Vector3<T> max = glm::max(b0.max, b1.max);
        return Box3<T>(min, max);
    }
    
    template <>
    inline float length(const Vector2<float>& v)
    {
        return sqrtf(v.squareLength());
    }
    
    template <>
    inline float length(const Vector3<float>& v)
    {
        return sqrtf(v.squareLength());
    }
    
}

#endif
