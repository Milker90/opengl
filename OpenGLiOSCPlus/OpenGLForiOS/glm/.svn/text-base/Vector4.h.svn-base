//
//  Vector4.h
//  SOSOMap
//
//  Created by samczli on 22/12/14.
//  Copyright (c) 2014 Tencent. All rights reserved.
//

#ifndef __SOSOMap__Vector4__
#define __SOSOMap__Vector4__

#include "math_type.h"

namespace glm {
    
    template <typename T>
    class Vector4
    {
        
    public:
        
        union
        {
            struct{ T x, y, z, w;   };
            struct{ T r, g, b, a;   };
            struct{ T originx, originy, width, height; };
            // struct{ T minx, miny, maxx, maxy; };
            T p[4];
        };
        
        
    public:
        
        Vector4()
        :x(0)
        ,y(0)
        ,z(0)
        ,w(0)
        {
            
        }
        
        template <typename A, typename B, typename C, typename D>
        Vector4(const A& _x, const B& _y, const C& _z, const D& _w)
        :x(_x)
        ,y(_y)
        ,z(_z)
        ,w(_w)
        {
            
        }
        
        explicit Vector4(const T& scalar)
        :x(scalar)
        ,y(scalar)
        ,z(scalar)
        ,w(scalar)
        {
            
        }
        
        template <typename Q>
        explicit Vector4(const Q *_p)
        :x(_p[0])
        ,y(_p[1])
        ,z(_p[2])
        ,w(_p[3])
        {
            
        }
        
        template<typename Q>
        explicit Vector4(const Vector3<Q>& vec3, const T& scalar)
        :x(vec3.x)
        ,y(vec3.y)
        ,z(vec3.z)
        ,w(scalar)
        {
            
        }
        
        template<typename Q>
        explicit Vector4(const T& scalar, const Vector3<Q>& vec3)
        :x(scalar)
        ,y(vec3.x)
        ,z(vec3.y)
        ,w(vec3.z)
        {
            
        }
        
        template<typename Q1, typename Q2>
        explicit Vector4(const Vector2<Q1>& lhs, const Vector2<Q2> rhs)
        :x(lhs.x)
        ,y(lhs.y)
        ,z(rhs.x)
        ,w(rhs.y)
        {
            
        }
        
        template <typename Q>
        explicit Vector4(const Vector2<Q> v2, const T& _z, const T& _w)
        :x(v2.x)
        ,y(v2.y)
        ,z(_z)
        ,w(_w)
        {
            
        }
        
        template <typename Q>
        explicit Vector4(const T& _x, const Vector2<Q>& v2, const T& _w)
        :x(_x)
        ,y(v2.x)
        ,z(v2.y)
        ,w(_w)
        {
            
        }
        
        template <typename Q>
        explicit Vector4(const T& _x, const T& _y, const Vector2<Q>& v2)
        :x(_x)
        ,y(_y)
        ,z(v2.x)
        ,w(v2.y)
        {
            
        }
        
        
        template <typename Q>
        explicit Vector4(const Vector4<Q>& vec4)
        :x(vec4.x)
        ,y(vec4.y)
        ,z(vec4.z)
        ,w(vec4.w)
        {
            
        }
        
    public:
        
        T& operator [] (const length_t i)
        {
            map_assert(i < 4);
            return p[i];
        }
        
        const T& operator [] (const length_t i) const
        {
            map_assert(i < 4);
            return p[i];
        }
        
        T* ptr()
        {
            return p;
        }
        
        const T* ptr() const
        {
            return p;
        }
        
        template<typename Q>
        Vector4& operator = (const Vector4<Q>& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            w = rhs.w;
            return *this;
        }
        
        Vector4& operator = (const T& scalar)
        {
            x = scalar;
            y = scalar;
            z = scalar;
            w = scalar;
            return *this;
        }
        
        bool operator == (const Vector4& rhs) const
        {
            return (rhs.x == x && rhs.y == y && rhs.z == z && rhs.w == w);
        }
        
        bool operator != (const Vector4& rhs) const
        {
            return (rhs.x != x || rhs.y != y || rhs.z != z || rhs.w != w);
        }
        
        template<typename Q>
        Vector4 operator + (const Vector4<Q>& rhs) const
        {
            return Vector4(x + rhs.x, y + rhs.y , z + rhs.z, w + rhs.w);
        }
        
        template<typename Q>
        Vector4 operator + (const Q& scalar) const
        {
            return Vector4(x + scalar, y + scalar, z + scalar, w + scalar);
        }
        
        template<typename Q>
        Vector4 operator - (const Vector4<Q>& rhs) const
        {
            return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }
        
        template<typename Q>
        Vector4 operator - (const Q& scalar) const
        {
            return Vector4(x - scalar, y - scalar, z - scalar, w - scalar);
        }
        
        template<typename Q>
        Vector4 operator * (const Vector4<Q>& rhs) const
        {
            return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
        }
        
        template<typename Q>
        Vector4 operator * (const Q& scalar) const
        {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }
        
        template<typename Q>
        Vector4 operator / (const Vector4<Q>& rhs) const
        {
            map_assert(0 != rhs.x && 0 != rhs.y && 0 != rhs.z && 0 != rhs.w);
            return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
        }
        
        template<typename Q>
        Vector4 operator / (const Q& scalar) const
        {
            map_assert(0 != scalar);
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }
        
        const Vector4& operator + () const
        {
            return *this;
        }
        
        // We'll specialize this template for unsigned type.
        Vector4 operator - () const
        {
            return Vector4(-x, -y, -z, -w);
        }
        
        template<typename Q>
        Vector4& operator += (const Vector4<Q>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }
        
        template<typename Q>
        Vector4& operator += (const Q& scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            w += scalar;
            return *this;
        }
        
        template<typename Q>
        Vector4& operator -= (const Vector4<Q>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }
        
        template<typename Q>
        Vector4& operator -= (const Q& scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            w -= scalar;
            return *this;
        }
        
        template<typename Q>
        Vector4& operator *= (const Vector4<Q>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            w *= rhs.w;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator *= (const Q& scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }
        
        template<typename Q>
        Vector4& operator /= (const Vector4<Q>& rhs)
        {
            map_assert(0 != rhs.x && 0 != rhs.y && 0 != rhs.z);
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            w /= rhs.w;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator /= (const Q& scalar)
        {
            map_assert(0 != scalar);
            x = x / scalar;
            y = y / scalar;
            z = z / scalar;
            w = w / scalar;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator %= (const Q& s)
        {
            x %= s;
            y %= s;
            z %= s;
            w %= s;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator %= (const Vector4<Q>& v)
        {
            x %= v.x;
            y %= v.y;
            z %= v.z;
            w %= v.w;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator &= (Q s)
        {
            x &= s;
            y &= s;
            z &= s;
            w &= s;
            return *this;
        }
        template <typename Q>
        Vector4& operator &= (const Vector4<Q>& v)
        {
            x &= v.x;
            y &= v.y;
            z &= v.z;
            w &= v.w;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator |= (Q s)
        {
            x |= s;
            y |= s;
            z |= s;
            w |= s;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator |= (const Vector4<Q>& v)
        {
            x |= v.x;
            y |= v.y;
            z |= v.z;
            w |= v.w;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator ^= (Q s)
        {
            x ^= s;
            y ^= s;
            z ^= s;
            w ^= s;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator ^= (const Vector4<Q>& v)
        {
            x ^= v.x;
            y ^= v.y;
            z ^= v.z;
            w ^= v.w;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator <<=(Q s)
        {
            x <<= s;
            y <<= s;
            z <<= s;
            w <<= s;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator <<=(const Vector4<Q>& v)
        {
            x <<= v.x;
            y <<= v.y;
            z <<= v.z;
            w <<= v.w;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator >>=(Q s)
        {
            x >>= s;
            y >>= s;
            z >>= s;
            w >>= s;
            return *this;
        }
        
        template <typename Q>
        Vector4& operator >>=(const Vector4<Q>& v)
        {
            x >>= v.x;
            y >>= v.y;
            z >>= v.z;
            w >>= v.w;
            return *this;
        }
        
        Vector4& operator ++ ()
        {
            ++x;
            ++y;
            ++z;
            ++w;
            return *this;
        }
        
        Vector4& operator -- ()
        {
            --x;
            --y;
            --z;
            --w;
            return *this;
        }
        
        Vector4 operator ++ (int)
        {
            Vector4 result(*this);
            ++*this;
            return result;
        }
        
        Vector4 operator -- (int)
        {
            Vector4 result(*this);
            --*this;
            return result;
        }
        
    public:
        
        friend Vector4 operator * (const T& scalar, const Vector4& rhs)
        {
            return Vector4(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z, scalar * rhs.w);
        }
        
        friend Vector4 operator / (const T& scalar, const Vector4& rhs)
        {
            map_assert(0 != rhs.x && 0 != rhs.y && 0 != rhs.z && 0 != rhs.w);
            return Vector4(scalar / rhs.x, scalar / rhs.y, scalar / rhs.z, scalar / rhs.w);
        }
        
        friend Vector4 operator + (const T& scalar, const Vector4& rhs)
        {
            return Vector4(scalar + rhs.x, scalar + rhs.y, scalar + rhs.z, scalar + rhs.w);
        }
        
        friend Vector4 operator - (const T& scalar, const Vector4& rhs)
        {
            return Vector4(scalar - rhs.x, scalar - rhs.y, scalar - rhs.z, scalar - rhs.w);
        }
        
        friend Vector4 operator%(const Vector4& v, T const & s)
        {
            return Vector4(v.x % s, v.y % s, v.z % s, v.w % s);
        }
        
        friend Vector4 operator%(T const & s, const Vector4& v)
        {
            return Vector4(s % v.x, s % v.y, s % v.z, s % v.w);
        }
        
        friend Vector4 operator%(const Vector4& v1, const Vector4& v2)
        {
            return Vector4(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w);
        }
        
        friend Vector4 operator&(const Vector4& v, T const & s)
        {
            return Vector4(v.x & s, v.y & s, v.z & s, v.w & s);
        }
        
        friend Vector4 operator&(T const & s, const Vector4& v)
        {
            return Vector4(s & v.x, s & v.y, s & v.z, s & v.w);
        }
        
        friend Vector4 operator&(const Vector4& v1, const Vector4& v2)
        {
            return Vector4(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z, v1.w & v2.w);
        }
        
        friend Vector4 operator|(const Vector4& v, T const & s)
        {
            return Vector4(v.x | s, v.y | s, v.z | s, v.w | s);
        }
        
        friend Vector4 operator|(T const & s, const Vector4& v)
        {
            return Vector4(s | v.x, s | v.y, s | v.z, s | v.w);
        }
        
        friend Vector4 operator|(const Vector4& v1, const Vector4& v2)
        {
            return Vector4(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z, v1.w | v2.w);
        }
        
        friend Vector4 operator^(const Vector4& v, T const & s)
        {
            return Vector4(v.x ^ s, v.y ^ s, v.z ^ s, v.w ^ s);
        }
        
        friend Vector4 operator^(T const & s, const Vector4& v)
        {
            return Vector4(s ^ v.x, s ^ v.y, s ^ v.z, s ^ v.w);
        }
        
        friend Vector4 operator^(const Vector4& v1, const Vector4& v2)
        {
            return Vector4(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z, v1.w ^ v2.w);
        }
        
        friend Vector4 operator<<(const Vector4& v, T const & s)
        {
            return Vector4(v.x << s, v.y << s, v.z << s, v.w << s);
        }
        
        friend Vector4 operator<<(T const & s, const Vector4& v)
        {
            return Vector4(s << v.x, s << v.y, s << v.z, s << v.w);
        }
        
        friend Vector4 operator<<(const Vector4& v1, const Vector4& v2)
        {
            return Vector4(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z, v1.w << v2.w);
        }
        
        friend Vector4 operator>>(const Vector4& v, T const & s)
        {
            return Vector4(v.x >> s, v.y >> s, v.z >> s, v.w >> s);
        }
        
        friend Vector4 operator>>(T const & s, const Vector4& v)
        {
            return Vector4(s >> v.x, s >> v.y, s >> v.z, s >> v.w);
        }
        
        friend Vector4 operator>>(const Vector4& v1, const Vector4& v2)
        {
            return Vector4(v1.x >> v2.x ,v1.y >> v2.y, v1.z >> v2.z, v1.w >> v2.w);
        }
        
        friend Vector4 operator~(const Vector4& v)
        {
            return Vector4(~v.x, ~v.y, ~v.z, ~v.w);
        }

    public:
        
        void swap(Vector4& other)
        {
            T t(x); x = other.x; other.x = t;
            t = y;  y = other.y; other.y = t;
            t = z;  y = other.z; other.z = t;
            t = w;  w = other.w; other.w = t;
        }
        
        T squareLength() const
        {
            return x * x + y * y + z * z + w * w;
        }
        
        T dot(const Vector4& rhs)const
        {
            return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
        }
        
        
        bool operator < (const Vector4& rhs) const
        {
            if (x != rhs.x) return x < rhs.x;
            if (y != rhs.y) return y < rhs.y;
            if (z != rhs.z) return z < rhs.z;
            return w < rhs.w;
        }
        
        const Vector2<T> xy() const
        {
            return Vector2<T>(x, y);
        }
        
        const Vector2<T> xz() const
        {
            return Vector2<T>(x, z);
        }
        
        const Vector2<T> xw() const
        {
            return Vector2<T>(x, w);
        }
        
        const Vector2<T> yz() const
        {
            return Vector2<T>(y, z);
        }
        
        const Vector2<T> yw() const
        {
            return Vector2<T>(y, w);
        }
        
        const Vector2<T> zw() const
        {
            return Vector2<T>(z, w);
        }
        
        const Vector3<T> xyz() const
        {
            return Vector3<T>(x, y, z);
        }
        
        const Vector3<T> xyw() const
        {
            return Vector3<T>(x, y , w);
        }
        
        const Vector3<T> xzw() const
        {
            return Vector3<T>(x, z, w);
        }
        
        const Vector3<T> yzw() const
        {
            return Vector3<T>(y, z, w);
        }
        
        const Vector2<T>origin() const
        {
            return Vector2<T>(x, y);
        }
        
        const Vector2<T> size() const
        {
            return Vector2<T>(width, height);
        }
        
        const Vector4 abs() const
        {
            return Vector4(x >= 0 ? x : -x, y >= 0 ? y : -y, z >= 0 ? z : -z, w >= 0 ? w : -w);
        }
        
        const Vector4 ceil() const
        {
            map_assert(false);
            return *this;
        }
        
        const Vector4 floor() const
        {
            map_assert(false);
            return *this;
        }
        
        bool isNan() const
        {
            return isnan(x) || isnan(y) || isnan(z) || isnan(w);
        }
        
        void print(const char *title = NULL) const;
        
        Vector2<T>& xy() { return *(Vector2<T>*)p; }
        
        Vector2<T>& yz() { return *(Vector2<T>*)(p + 1); }
        
        Vector2<T>& zw() { return *(Vector2<T>*)(p + 2); }
        
        Vector3<T>& xyz() { return *(Vector3<T>*)p; }
        
        Vector3<T>& yzw() { return *(Vector3<T>*)(p + 1); }
        
        Vector2<T>& origin() { return xy(); }
        
        Vector2<T>& size() { return zw(); }
    };
    
    //////////////////////////////////////////////////////////////////////////
    // Error calling for unsigned type.
    template<>
    inline Vector4<unsigned char> Vector4<unsigned char>::operator - () const
    {
        map_assert(false);
        return Vector4(x, y, z, w);
    }
    
    template<>
    inline Vector4<unsigned int> Vector4<unsigned int>::operator - () const
    {
        map_assert(false);
        return Vector4(x, y, z, w);
    }
    
    template<>
    inline Vector4<unsigned long> Vector4<unsigned long>::operator - () const
    {
        map_assert(false);
        return Vector4(x, y, z, w);
    }
    
    template<>
    inline Vector4<unsigned long long> Vector4<unsigned long long>:: operator - () const
    {
        map_assert(false);
        return Vector4(x, y, z, w);
    }
    
    template<>
    const inline Vector4<float> Vector4<float>::abs() const
    {
        return Vector4(fabsf(x), fabsf(y), fabsf(z), fabsf(w));
    }
    
    template<>
    const inline Vector4<double> Vector4<double>::abs() const
    {
        return Vector4(fabs(x), fabs(y), fabs(z), fabs(w));
    }
    
    template<>
    const inline Vector4<float> Vector4<float>::ceil() const
    {
        return Vector4(ceilf(x), ceilf(y), ceilf(z), ceilf(w));
    }
    
    template<>
    const inline Vector4<double> Vector4<double>::ceil() const
    {
        return Vector4(::ceil(x), ::ceil(y), ::ceil(z), ::ceil(w));
    }
    
    template<>
    const inline Vector4<float> Vector4<float>::floor() const
    {
        return Vector4(floorf(x), floorf(y), floorf(z), floorf(w));
    }
    
    template<>
    const inline Vector4<double> Vector4<double>::floor() const
    {
        return Vector4(::floor(x), ::floor(y), ::floor(z), ::floor(w));
    }
    
    template<typename T>
    inline void Vector4<T>::print(const char *title) const
    {
        if (!title) title = "Vector4i";
        map_printf("%s: (%i %i %i %i)\n", title, (int)x, (int)y, (int)z, (int)w);
    }
    
    template<>
    inline void Vector4<float>::print(const char *title) const
    {
        if (!title) title = "Vector4f";
        map_printf("%s: (%f %f %f %f)\n", title, x, y, z, w);
    }
    
    template<>
    inline void Vector4<double>::print(const char *title) const
    {
        if (!title) title = "Vector4d";
        map_printf("%s: (%f %f %f %f)\n", title, x, y, z, w);
    }
}

#endif /* defined(__SOSOMap__Vector4__) */
