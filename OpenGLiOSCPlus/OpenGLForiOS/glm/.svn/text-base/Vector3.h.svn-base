//
//  Vector3.h
//  SOSOStreetViewMapAPI
//
//  Created by SAMCZLI on 8/4/14.
//  Copyright (c) 2014 lv wei. All rights reserved.
//

#ifndef SOSOStreetViewMapAPI_Vector3_h
#define SOSOStreetViewMapAPI_Vector3_h

#include "math_type.h"

namespace glm {
    
    template <typename T>
    class Vector3
    {
        
    public:
        
        union
        {
            struct{ T x, y, z;  };
            struct{ T r, g, b;  };
            T p[3];
        };
        
        
    public:
        
        Vector3()
        :x(0)
        ,y(0)
        ,z(0)
        {
            
        }
        
        template <typename A, typename B, typename C>
        Vector3(const A& _x, const B& _y, const C& _z)
        :x(_x)
        ,y(_y)
        ,z(_z)
        {
            
        }
        
        explicit Vector3(const T& scalar)
        :x(scalar)
        ,y(scalar)
        ,z(scalar)
        {
            
        }
        
        template <typename Q>
        explicit Vector3(const Q *_p)
        :x(_p[0])
        ,y(_p[1])
        ,z(_p[2])
        {
            
        }
        
        template <typename Q>
        explicit Vector3(const Vector3<Q>& vec3)
        :x(vec3.x)
        ,y(vec3.y)
        ,z(vec3.z)
        {
            
        }
        
        template <typename Q>
        explicit Vector3(const Vector4<Q>& vec4)
        :x(vec4.x)
        ,y(vec4.y)
        ,z(vec4.z)
        {
            
        }
        
        template<typename Q>
        explicit Vector3(const Vector2<Q>& vec2, const T& scalar)
        :x(vec2.x)
        ,y(vec2.y)
        ,z(scalar)
        {
            
        }
        
        template<typename Q>
        explicit Vector3(const T& scalar, const Vector2<Q>& vec2)
        :x(scalar)
        ,y(vec2.x)
        ,z(vec2.y)
        {
            
        }
        
        
    public:
        
        T& operator [] (const length_t i)
        {
            map_assert(i < 3);
            return p[i];
        }
        
        const T& operator [] (const length_t i) const
        {
            map_assert(i < 3);
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
        
        template <typename Q>
        Vector3& operator = (const Vector3<Q>& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }
        
        Vector3& operator = (const T& scalar)
        {
            x = scalar;
            y = scalar;
            z = scalar;
            return *this;
        }
        
        bool operator == (const Vector3& rhs) const
        {
            return (rhs.x == x && rhs.y == y && rhs.z == z);
        }
        
        bool operator != (const Vector3& rhs) const
        {
            return (rhs.x != x || rhs.y != y || rhs.z != z);
        }
        
        bool operator < (const Vector3& rhs) const
        {
            if (x != rhs.x) return x < rhs.x;
            if (y != rhs.y) return y < rhs.y;
            return z < rhs.z;
        }
        
        template<typename Q>
        Vector3 operator + (const Vector3<Q>& rhs) const
        {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }
        
        template<typename Q>
        Vector3 operator + (const Q& scalar) const
        {
            return Vector3(x + scalar, y + scalar, z + scalar);
        }
        
        template<typename Q>
        Vector3 operator - (const Vector3<Q>& rhs) const
        {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }
        
        template<typename Q>
        Vector3 operator - (const Q& scalar) const
        {
            return Vector3(x - scalar, y - scalar, z - scalar);
        }
        
        template<typename Q>
        Vector3 operator * (const Vector3<Q>& rhs) const
        {
            return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
        }
        
        template<typename Q>
        Vector3 operator * (const Q& scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        
        template<typename Q>
        Vector3 operator / (const Vector3<Q>& rhs) const
        {
            map_assert(0 != rhs.x && 0 != rhs.y && 0 != rhs.z);
            return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
        }
        
        template<typename Q>
        Vector3 operator / (const Q& scalar) const
        {
            map_assert(0 != scalar);
            return Vector3(x / scalar, y / scalar, z / scalar);
        }
        
        const Vector3& operator + () const
        {
            return *this;
        }
        
        // We'll specialize this template for unsigned type.
        Vector3 operator - () const
        {
            return Vector3(-x, -y, -z);
        }
        
        template <typename Q>
        Vector3& operator += (const Vector3<Q>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator += (const Q& scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator -= (const Vector3<Q>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator -= (const Q& scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator *= (const Vector3<Q>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator *= (const Q& scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator /= (const Vector3<Q>& rhs)
        {
            map_assert(0 != rhs.x && 0 != rhs.y && 0 != rhs.z);
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator /= (const Q& scalar)
        {
            map_assert(0 != scalar);
            x = x / scalar;
            y = y / scalar;
            z = z / scalar;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator %= (const Q& s)
        {
            x %= s;
            y %= s;
            z %= s;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator %= (const Vector3<Q>& v)
        {
            x %= v.x;
            y %= v.y;
            z %= v.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator &= (Q s)
        {
            x &= s;
            y &= s;
            z &= s;
            return *this;
        }
        template <typename Q>
        Vector3& operator &= (const Vector3<Q>& v)
        {
            x &= v.x;
            y &= v.y;
            z &= v.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator |= (Q s)
        {
            x |= s;
            y |= s;
            z |= s;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator |= (const Vector3<Q>& v)
        {
            x |= v.x;
            y |= v.y;
            z |= v.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator ^= (Q s)
        {
            x ^= s;
            y ^= s;
            z ^= s;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator ^= (const Vector3<Q>& v)
        {
            x ^= v.x;
            y ^= v.y;
            z ^= v.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator <<=(Q s)
        {
            x <<= s;
            y <<= s;
            z <<= s;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator <<=(const Vector3<Q>& v)
        {
            x <<= v.x;
            y <<= v.y;
            z <<= v.z;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator >>=(Q s)
        {
            x >>= s;
            y >>= s;
            z >>= s;
            return *this;
        }
        
        template <typename Q>
        Vector3& operator >>=(const Vector3<Q>& v)
        {
            x >>= v.x;
            y >>= v.y;
            z >>= v.z;
            return *this;
        }

        Vector3& operator ++ ()
        {
            ++x;
            ++y;
            ++z;
            return *this;
        }
        
        Vector3& operator -- ()
        {
            --x;
            --y;
            --z;
            return *this;
        }
        
        Vector3 operator ++ (int)
        {
            Vector3 result(*this);
            ++*this;
            return result;
        }
        
        Vector3 operator -- (int)
        {
            Vector3 result(*this);
            --*this;
            return result;
        }
        
        
    public:
        
        friend Vector3 operator * (const T& scalar, const Vector3& rhs)
        {
            return Vector3(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
        }
        
        friend Vector3 operator / (const T& scalar, const Vector3& rhs)
        {
            map_assert(0 != rhs.x && 0 != rhs.y && 0 != rhs.z);
            return Vector3(scalar / rhs.x, scalar / rhs.y, scalar / rhs.z);
        }
        
        friend Vector3 operator + (const T& scalar, const Vector3& rhs)
        {
            return Vector3(scalar + rhs.x, scalar + rhs.y, scalar + rhs.z);
        }
        
        friend Vector3 operator - (const T& scalar, const Vector3& rhs)
        {
            return Vector3(scalar - rhs.x, scalar - rhs.y, scalar - rhs.z);
        }
        
        friend Vector3 operator%(const Vector3& v, T const & s)
        {
            return Vector3(v.x % s, v.y % s, v.z % s);
        }
        
        friend Vector3 operator%(T const & s, const Vector3& v)
        {
            return Vector3(s % v.x, s % v.y, s % v.z);
        }
        
        friend Vector3 operator%(const Vector3& v1, const Vector3& v2)
        {
            return Vector3(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z);
        }
        
        friend Vector3 operator&(const Vector3& v, T const & s)
        {
            return Vector3(v.x & s, v.y & s, v.z & s);
        }
        
        friend Vector3 operator&(T const & s, const Vector3& v)
        {
            return Vector3(s & v.x, s & v.y, s & v.z);
        }
        
        friend Vector3 operator&(const Vector3& v1, const Vector3& v2)
        {
            return Vector3(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z);
        }
        
        friend Vector3 operator|(const Vector3& v, T const & s)
        {
            return Vector3(v.x | s, v.y | s, v.z | s);
        }
        
        friend Vector3 operator|(T const & s, const Vector3& v)
        {
            return Vector3(s | v.x, s | v.y, s | v.z);
        }
        
        friend Vector3 operator|(const Vector3& v1, const Vector3& v2)
        {
            return Vector3(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z);
        }
        
        friend Vector3 operator^(const Vector3& v, T const & s)
        {
            return Vector3(v.x ^ s, v.y ^ s, v.z ^ s);
        }
        
        friend Vector3 operator^(T const & s, const Vector3& v)
        {
            return Vector3(s ^ v.x, s ^ v.y, s ^ v.z);
        }
        
        friend Vector3 operator^(const Vector3& v1, const Vector3& v2)
        {
            return Vector3(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z);
        }
        
        friend Vector3 operator<<(const Vector3& v, T const & s)
        {
            return Vector3(v.x << s, v.y << s, v.z << s);
        }
        
        friend Vector3 operator<<(T const & s, const Vector3& v)
        {
            return Vector3(s << v.x, s << v.y, s << v.z);
        }
        
        friend Vector3 operator<<(const Vector3& v1, const Vector3& v2)
        {
            return Vector3(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z);
        }
        
        friend Vector3 operator>>(const Vector3& v, T const & s)
        {
            return Vector3(v.x >> s, v.y >> s, v.z >> s);
        }
        
        friend Vector3 operator>>(T const & s, const Vector3& v)
        {
            return Vector3(s >> v.x, s >> v.y, s >> v.z);
        }
        
        friend Vector3 operator>>(const Vector3& v1, const Vector3& v2)
        {
            return Vector3(v1.x >> v2.x ,v1.y >> v2.y, v1.z >> v2.z);
        }
        
        friend Vector3 operator~(const Vector3& v)
        {
            return Vector3(~v.x, ~v.y, ~v.z);
        }
        
    public:
        
        const Vector2<T> xy() const
        {
            return Vector2<T>(x, y);
        }
        
        const Vector2<T> xz() const
        {
            return Vector2<T>(x, z);
        }
        
        const Vector2<T> yz() const
        {
            return Vector2<T>(y, z);
        }
        
        void swap(Vector3& other)
        {
            T t(x); x = other.x; other.x = t;
            t = y;  y = other.y; other.y = t;
            t = z;  y = other.z; other.z = t;
        }
        
        T squareLength() const
        {
            return x * x + y * y + z * z;
        }
        
        T dot(const Vector3& rhs)const
        {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }
        
        const Vector3 cross(const Vector3& rhs) const
        {
            return Vector3(y * rhs.z - z * rhs.y,
                           z * rhs.x - x * rhs.z,
                           x * rhs.y - y * rhs.x);
        }
        
        const Vector3 abs() const
        {
            return Vector3(x >= 0 ? x : -x, y >= 0 ? y : -y, z >= 0 ? z : -z);
        }
        
        const Vector3 ceil() const
        {
            map_assert(false);
            return *this;
        }
        
        const Vector3 floor() const
        {
            map_assert(false);
            return *this;
        }
        
        bool isNan() const
        {
            return isnan(x) || isnan(y) || isnan(z);
        }
        
        void print(const char *title = NULL) const;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // Error calling for unsigned type.
    template<>
    inline Vector3<unsigned char> Vector3<unsigned char>::operator - () const
    {
        map_assert(false);
        return Vector3(x, y, z);
    }
    
    template<>
    inline Vector3<unsigned int> Vector3<unsigned int>::operator - () const
    {
        map_assert(false);
        return Vector3(x, y, z);
    }
    
    template<>
    inline Vector3<unsigned long> Vector3<unsigned long>::operator - () const
    {
        map_assert(false);
        return Vector3(x, y, z);
    }
    
    template<>
    inline Vector3<unsigned long long> Vector3<unsigned long long>:: operator - () const
    {
        map_assert(false);
        return Vector3(x, y, z);
    }
    
    template<>
    const inline Vector3<float> Vector3<float>::abs() const
    {
        return Vector3(fabsf(x), fabsf(y), fabsf(z));
    }
    
    template<>
    const inline Vector3<double> Vector3<double>::abs() const
    {
        return Vector3(fabs(x), fabs(y), fabs(z));
    }
    
    template<>
    const inline Vector3<float> Vector3<float>::ceil() const
    {
        return Vector3(ceilf(x), ceilf(y), ceilf(z));
    }
    
    template<>
    const inline Vector3<double> Vector3<double>::ceil() const
    {
        return Vector3(::ceil(x), ::ceil(y), ::ceil(z));
    }
    
    template<>
    const inline Vector3<float> Vector3<float>::floor() const
    {
        return Vector3(floorf(x), floorf(y), floorf(z));
    }
    
    template<>
    const inline Vector3<double> Vector3<double>::floor() const
    {
        return Vector3(::floor(x), ::floor(y), ::floor(z));
    }
    
    template<typename T>
    inline void Vector3<T>::print(const char *title) const
    {
        if (!title) title = "Vector3i";
        map_printf("%s: (%i %i %i)\n", title, (int)x, (int)y, (int)z);
    }
    
    template<>
    inline void Vector3<float>::print(const char *title) const
    {
        if (!title) title = "Vector3f";
        map_printf("%s: (%f %f %f)\n", title, x, y, z);
    }
    
    template<>
    inline void Vector3<double>::print(const char *title) const
    {
        if (!title) title = "Vector3d";
        map_printf("%s: (%f %f %f)\n", title, x, y, z);
    }
}

#endif
