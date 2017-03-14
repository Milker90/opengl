//
//  Vector2.h
//  SOSOStreetViewMapAPI
//
//  Created by SAMCZLI on 8/4/14.
//  Copyrhs (c) 2014 lv wei. All rhss reserved.
//

#ifndef SOSOStreetViewMapAPI_Vector2_h
#define SOSOStreetViewMapAPI_Vector2_h

#include "math_type.h"

namespace glm {
    
    template <typename T>
    class Vector2
    {
        typedef Vector2<T>      type;
        typedef Vector2<bool>   bool_type;
        typedef T               value_type;
        typedef int             size_type;
        
    public:
        
        union
        {
            struct{ T x, y; };
            struct{ T r, g; };
            struct{ T width, height; };
            T p[2];
        };
        
    public:
        
        Vector2()
        :x(0)
        ,y(0)
        {
            
        }
        
        template <typename A, typename B>
        Vector2(const A& _x, const B& _y)
        :x(_x)
        ,y(_y)
        {
            
        }
        
        explicit Vector2(const T& scalar)
        :x(scalar)
        ,y(scalar)
        {
            
        }
        
        template <typename Q>
        explicit Vector2(const Q *_p)
        :x(_p[0])
        ,y(_p[1])
        {
            
        }
        
        template <typename Q>
        explicit Vector2(const Vector2<Q>& vec2)
        :x(vec2.x)
        ,y(vec2.y)
        {
            
        }
        
        template <typename Q>
        explicit Vector2(const Vector3<Q>& vec3)
        :x(vec3.x)
        ,y(vec3.y)
        {
            
        }
        
        template <typename Q>
        explicit Vector2(const Vector4<Q>& vec4)
        :x(vec4.x)
        ,y(vec4.y)
        {
            
        }
        
    public:
        
        T& operator [] (length_t i)
        {
            map_assert(i < 2);
            return p[i];
        }
        
        const T& operator [] (length_t i) const
        {
            map_assert(i < 2);
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
        Vector2& operator = (const Vector2<Q>& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }
        
        Vector2& operator = (const T& scalar)
        {
            x = scalar;
            y = scalar;
            return *this;
        }
        
        bool operator == (const Vector2& rhs) const
        {
            return (x == rhs.x && y == rhs.y);
        }
        
        bool operator != (const Vector2& rhs) const
        {
            return (x != rhs.x || y != rhs.y);
        }
        
        template <typename Q>
        Vector2 operator + (const Vector2<Q>& rhs) const
        {
            return Vector2(x + rhs.x, y + rhs.y);
        }
        
        template <typename Q>
        Vector2 operator + (const Q& scalar) const
        {
            return Vector2(x + scalar, y + scalar);
        }
        
        template <typename Q>
        Vector2 operator - (const Vector2<Q>& rhs) const
        {
            return Vector2(x - rhs.x, y - rhs.y);
        }
        
        template <typename Q>
        Vector2 operator - (const Q& scalar) const
        {
            return Vector2(x - scalar, y - scalar);
        }
        
        template <typename Q>
        Vector2 operator * (const Vector2<Q>& rhs) const
        {
            return Vector2(x * rhs.x, y * rhs.y);
        }
        
        template <typename Q>
        Vector2 operator * (const Q& scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }
        
        template <typename Q>
        Vector2 operator / (const Vector2<Q>& rhs) const
        {
            map_assert(0 != rhs.x && 0 != rhs.y);
            return Vector2(x / rhs.x, y / rhs.y);
        }
        
        template <typename Q>
        Vector2 operator / (const Q& scalar) const
        {
            map_assert(0 != scalar);
            return Vector2(x / scalar, y / scalar);
        }
        
        const Vector2& operator + () const
        {
            return *this;
        }
        
        // We'll specialize the template for unsigned type.
        Vector2 operator - () const
        {
            return Vector2(-x, -y);
        }
        
        template <typename Q>
        Vector2& operator += (const Vector2<Q>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator += (const Q& scalar)
        {
            x += scalar;
            y += scalar;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator -= (const Vector2<Q>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator -= (const Q& scalar)
        {
            x -= scalar;
            y -= scalar;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator *= (const Vector2<Q>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator *= (const Q& scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator /= (const Vector2<Q>& rhs)
        {
            map_assert(0 != rhs.x && 0 != rhs.y);
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator /= (const Q& scalar)
        {
            map_assert(0 != scalar);
            x /= scalar;
            y /= scalar;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator %= (const Q& s)
        {
            x %= s;
            y %= s;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator %= (const Vector2<Q>& v)
        {
            x %= v.x;
            y %= v.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator &= (Q s)
        {
            x &= s;
            y &= s;
            return *this;
        }
        template <typename Q>
        Vector2& operator &= (const Vector2<Q>& v)
        {
            x &= v.x;
            y &= v.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator |= (Q s)
        {
            x |= s;
            y |= s;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator |= (const Vector2<Q>& v)
        {
            x |= v.x;
            y |= v.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator ^= (Q s)
        {
            x ^= s;
            y ^= s;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator ^= (const Vector2<Q>& v)
        {
            x ^= v.x;
            y ^= v.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator <<=(Q s)
        {
            x <<= s;
            y <<= s;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator <<=(const Vector2<Q>& v)
        {
            x <<= v.x;
            y <<= v.y;
            return *this;
        }
        
        template <typename Q>
        Vector2& operator >>=(Q s)
        {
            x >>= s;
            y >>= s;
            return *this;
        }
        
        template <typename Q> 
        Vector2& operator >>=(const Vector2<Q>& v)
        {
            x >>= v.x;
            y >>= v.y;
            return *this;
        }
        
        
        Vector2& operator ++ ()
        {
            ++x;
            ++y;
            return *this;
        }
        
        Vector2& operator -- ()
        {
            --x;
            --y;
            return *this;
        }
        
        Vector2 operator ++ (int)
        {
            Vector2 result(*this);
            ++*this;
            return result;
        }
        
        Vector2 operator -- (int)
        {
            Vector2 result(*this);
            --*this;
            return result;
        }
        
    public:
        
        friend Vector2 operator * (const T& scalar, const Vector2& rhs)
        {
            return Vector2(scalar * rhs.x, scalar * rhs.y);
        }
        
        friend Vector2 operator / (const T& scalar, const Vector2& rhs)
        {
            map_assert(0 != rhs.x && 0 != rhs.y);
            return Vector2(scalar / rhs.x, scalar / rhs.y);
        }
        
        friend Vector2 operator + (const T& scalar, const Vector2& rhs)
        {
            return Vector2(scalar + rhs.x, scalar + rhs.y);
        }
        
        friend Vector2 operator - (const T& scalar, const Vector2& rhs)
        {
            return Vector2(scalar - rhs.x, scalar - rhs.y);
        }
        
        friend Vector2 operator%(const Vector2& v, T const & s)
        {
            return Vector2(v.x % s, v.y % s);
        }
        
        friend Vector2 operator%(T const & s, const Vector2& v)
        {
            return Vector2(s % v.x, s % v.y);
        }
        
        friend Vector2 operator%(const Vector2& v1, const Vector2& v2)
        {
            return Vector2(v1.x % v2.x, v1.y % v2.y);
        }
        
        friend Vector2 operator&(const Vector2& v, T const & s)
        {
            return Vector2(v.x & s, v.y & s);
        }
        
        friend Vector2 operator&(T const & s, const Vector2& v)
        {
            return Vector2(s & v.x, s & v.y);
        }
        
        friend Vector2 operator&(const Vector2& v1, const Vector2& v2)
        {
            return Vector2(v1.x & v2.x, v1.y & v2.y);
        }
        
        friend Vector2 operator|(const Vector2& v, T const & s)
        {
            return Vector2(v.x | s, v.y | s);
        }
        
        friend Vector2 operator|(T const & s, const Vector2& v)
        {
            return Vector2(s | v.x, s | v.y);
        }
        
        friend Vector2 operator|(const Vector2& v1, const Vector2& v2)
        {
            return Vector2(v1.x | v2.x, v1.y | v2.y);
        }
        
        friend Vector2 operator^(const Vector2& v, T const & s)
        {
            return Vector2(v.x ^ s, v.y ^ s);
        }
        
        friend Vector2 operator^(T const & s, const Vector2& v)
        {
            return Vector2(s ^ v.x, s ^ v.y);
        }
        
        friend Vector2 operator^(const Vector2& v1, const Vector2& v2)
        {
            return Vector2(v1.x ^ v2.x, v1.y ^ v2.y);
        }
        
        friend Vector2 operator<<(const Vector2& v, T const & s)
        {
            return Vector2(v.x << s, v.y << s);
        }
        
        friend Vector2 operator<<(T const & s, const Vector2& v)
        {
            return Vector2(s << v.x, s << v.y);
        }
        
        friend Vector2 operator<<(const Vector2& v1, const Vector2& v2)
        {
            return Vector2(v1.x << v2.x, v1.y << v2.y);
        }
        
        friend Vector2 operator>>(const Vector2& v, T const & s)
        {
            return Vector2(v.x >> s, v.y >> s);
        }
        
        friend Vector2 operator>>(T const & s, const Vector2& v)
        {
            return Vector2(s >> v.x, s >> v.y);
        }
        
        friend Vector2 operator>>(const Vector2& v1, const Vector2& v2)
        {
            return Vector2(v1.x >> v2.x ,v1.y >> v2.y);
        }
        
        friend Vector2 operator~(const Vector2& v)
        {
            return Vector2(~v.x, ~v.y);
        }
        
    public:
        
        void swap(Vector2& other)
        {
            T t(x); x = other.x; other.x = t;
            t = y;  y = other.y; other.y = t;
        }
        
        const Vector2 inner() const       // counter-clockwise
        {
            return Vector2(-y, x);
        }
        
        const Vector2 outer() const       // counter-clockwise
        {
            return Vector2(y, -x);
        }
        
        T squareLength() const
        {
            return x * x + y * y;
        }
        
        T dot(const Vector2& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }
        
        bool operator < (const Vector2& rhs) const
        {
            if (x != rhs.x)
                return x < rhs.x;
            return y < rhs.y;
        }
        
        const Vector2 abs() const
        {
            return Vector2(x >= 0 ? x : -x, y >= 0 ? y : -y);
        }
        
        const Vector2 ceil() const
        {
            map_assert(false);
            return *this;
        }
        
        const Vector2 floor() const
        {
            map_assert(false);
            return *this;
        }
        
        bool isNan() const
        {
            return isnan(x) || isnan(y);
        }
        
        void print(const char *title = NULL) const;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // Error calling for unsigned type.
    template<>
    inline Vector2<unsigned char> Vector2<unsigned char>::operator - () const
    {
        map_assert(false);
        return Vector2(x, y);
    }
    
    template<>
    inline Vector2<unsigned int> Vector2<unsigned int>::operator - () const
    {
        map_assert(false);
        return Vector2(x, y);
    }
    
    template<>
    inline Vector2<unsigned long> Vector2<unsigned long>::operator - () const
    {
        map_assert(false);
        return Vector2(x, y);
    }
    
    template<>
    inline Vector2<unsigned long long> Vector2<unsigned long long>:: operator - () const
    {
        map_assert(false);
        return Vector2(x, y);
    }
    
    template<>
    const inline Vector2<float> Vector2<float>::abs() const
    {
        return Vector2(fabsf(x), fabsf(y));
    }
    
    template<>
    const inline Vector2<double> Vector2<double>::abs() const
    {
        return Vector2(fabs(x), fabs(y));
    }
    
    template<>
    const inline Vector2<float> Vector2<float>::ceil() const
    {
        return Vector2(ceilf(x), ceilf(y));
    }
    
    template<>
    const inline Vector2<double> Vector2<double>::ceil() const
    {
        return Vector2(::ceil(x), ::ceil(y));
    }
    
    template<>
    const inline Vector2<float> Vector2<float>::floor() const
    {
        return Vector2(floorf(x), floorf(y));
    }
    
    template<>
    const inline Vector2<double> Vector2<double>::floor() const
    {
        return Vector2(::floor(x), ::floor(y));
    }
    
    template<typename T>
    inline void Vector2<T>::print(const char *title) const
    {
        if (!title) title = "Vector2i";
        map_printf("%s: (%i %i)\n", title, (int)x, (int)y);
    }
    
    template<>
    inline void Vector2<float>::print(const char *title) const
    {
        if (!title) title = "Vector2f";
        map_printf("%s: (%f %f)\n", title, x, y);
    }
    
    template<>
    inline void Vector2<double>::print(const char *title) const
    {
        if (!title) title = "Vector2d";
        map_printf("%s: (%f %f)\n", title, x, y);
    }
}

#endif
