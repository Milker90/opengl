//
//  Matrix3.h
//  SOSOMap
//
//  Created by samczli on 15/1/15.
//  Copyright (c) 2015 Tencent. All rights reserved.
//

#ifndef SOSOMap_Matrix3_h
#define SOSOMap_Matrix3_h

#include "math_type.h"

namespace glm{

    template <typename T>
    class Matrix3
    {
    public:
        typedef T value_type;
        typedef std::size_t size_type;
        typedef Vector3<T>  col_type;
        typedef Vector3<T>  row_type;
        typedef Matrix3<T>  type;
        typedef Matrix3<T>& reference_type;
        
        col_type col0;
        col_type col1;
        col_type col2;
        
    public:
        
        Matrix3()
        {
            value_type zero(0);
            value_type one(1);
            col0 = col_type(one, zero, zero);
            col1 = col_type(zero, one, zero);
            col2 = col_type(zero, zero, one);
        }
        
        Matrix3(const T& scalar)
        {
            value_type zero(0);
            col0 = col_type(scalar, zero, zero);
            col1 = col_type(zero, scalar, zero);
            col2 = col_type(zero, zero, scalar);
        }
        
        template <typename Q>
        Matrix3(const Q* ptr)
        :col0(ptr)
        ,col1(ptr + 3)
        ,col2(ptr + 6)
        {
            
        }
        
        template<typename Q>
        explicit Matrix3(const Matrix3<Q>& m)
        :col0(m.col0)
        ,col1(m.col1)
        ,col2(m.col2)
        {
            
        }
        
        template <typename Q>
        explicit Matrix3(const Matrix4<Q>& m)
        :col0(m.col0)
        ,col1(m.col1)
        ,col2(m.col2)
        {
            
        }
        
        template<typename Q1, typename Q2, typename Q3>
        Matrix3(const Vector3<Q1>& c0, const Vector3<Q2>& c1, const Vector3<Q3>& c2)
        :col0(c0)
        ,col1(c1)
        ,col2(c2)
        {
            
        }
        
        Matrix3(const T& x0, const T& y0, const T& z0,
                const T& x1, const T& y1, const T& z1,
                const T& x2, const T& y2, const T& z2)
        {
            col0 = col_type(x0, y0, z0);
            col1 = col_type(x1, y1, z1);
            col2 = col_type(x2, y2, z2);
        }
        
        
    public:
        col_type& operator [] (length_t i)
        {
            map_assert(i < 3 && i >= 0);
            return (&col0)[i];
        }
        
        const col_type& operator [] (length_t i) const
        {
            map_assert(i < 3 && i >= 0);
            return (&col0)[i];
        }
        
        T* ptr()
        {
            return (T*)static_cast<col_type*>(&col0);
        }
        
        const T* ptr() const
        {
            return (const T*)static_cast<const col_type*>(&col0);
        }
        
        row_type row(length_t i)
        {
            map_assert(i < 3 && i >=0);
            return row_type(col0[i], col1[i], col2[i]);
        }
        
        reference_type operator = (const Matrix3<T>& m);
        
        template <typename Q>
        reference_type operator = (const Matrix3<Q>& m);
        template <typename Q>
        reference_type operator += (const Q& scalar);
        template <typename Q>
        reference_type operator += (const Matrix3<Q>& m);
        template <typename Q>
        reference_type operator -= (const Q& scalar);
        template <typename Q>
        reference_type operator -= (const Matrix3<Q>& m);
        template <typename Q>
        reference_type operator *= (const Q& scalar);
        template <typename Q>
        reference_type operator *= (const Matrix3<Q>& m);
        template <typename Q>
        reference_type operator /= (const Q& scalar);
        template <typename Q>
        reference_type operator /= (const Matrix3<Q>& m);
        
        type operator + (const T& scalar) const;
        type operator - (const T& scalar) const;
        type operator * (const T& scalar) const;
        type operator / (const T& scalar) const;
        
        type operator + (const Matrix3& m) const;
        type operator - (const Matrix3& m) const;
        type operator * (const Matrix3& m) const;
        type operator / (const Matrix3& m) const;
        
        Vector3<T> operator * (const Vector3<T>& vec3) const;
        Vector3<T> operator / (const Vector3<T>& vec3) const;
        
        reference_type operator ++ ();
        reference_type operator -- ();
        type operator ++ (int);
        type operator -- (int);
        type operator - ();
        
        bool operator == (const Matrix3<T>& m) const;
        bool operator != (const Matrix3<T>& m) const;
        
    public:
        
//        friend type operator + (const T& scalar, const Matrix3<T>& m);
//        friend type operator - (const T& scalar, const Matrix3<T>& m);
//        friend type operator * (const T& scalar, const Matrix3<T>& m);
//        friend type operator / (const T& scalar, const Matrix3<T>& m);
//        
//        friend Vector3<T> operator * (const Vector3<T>& vec3, const Matrix3<T>& m);
//        friend Vector3<T> operator / (const Vector3<T>& vec3, const Matrix3<T>& m);
        
        type transpose()const;           // 转置矩阵
        type inverse()  const;             // 逆矩阵

        
    };
    

    template <typename T>
    inline Matrix3<T>& Matrix3<T>::operator = (const Matrix3<T>& m)
    {
        // memcpy could be faster.
        col0 = m.col0;
        col1 = m.col1;
        col2 = m.col2;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator = (const Matrix3<Q>& m)
    {
        col0 = m.col0;
        col1 = m.col1;
        col2 = m.col2;
        return *this;
    }
    
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator+= (const Q& scalar)
    {
        col0 += scalar;
        col1 += scalar;
        col2 += scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator += (const Matrix3<Q>& m)
    {
        col0 += m.col0;
        col1 += m.col1;
        col2 += m.col2;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator -= (const Q& scalar)
    {
        col0 -= scalar;
        col1 -= scalar;
        col2 -= scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator -= (const Matrix3<Q>& m)
    {
        col0 -= m.col0;
        col1 -= m.col1;
        col2 -= m.col2;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator *= (const Q& scalar)
    {
        col0 *= scalar;
        col1 *= scalar;
        col2 *= scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator *= (const Matrix3<Q>& m)
    {
        return (*this = *this * m);
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator /= (const Q& scalar)
    {
        col0 /= scalar;
        col1 /= scalar;
        col2 /= scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix3<T>& Matrix3<T>::operator /= (const Matrix3<Q>& m)
    {
        *this = (*this * m.inverse());
        return *this;
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator + (const T& scalar) const
    {
        return Matrix3<T>(col0 + scalar, col1 + scalar, col2 + scalar);
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator - (const T& scalar) const
    {
        return Matrix3<T>(col0 - scalar, col1 - scalar, col2 - scalar);
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator * (const T& scalar) const
    {
        return Matrix3<T>(col0 * scalar, col1 * scalar, col2 * scalar);
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator / (const T& scalar) const
    {
        return Matrix3<T>(col0 / scalar, col1 / scalar, col2 / scalar);
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator + (const Matrix3<T>& m) const
    {
        return Matrix3<T>(col0 + m.col0, col1 + m.col1, col2 + m.col2);
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator - (const Matrix3<T>& m) const
    {
        return Matrix3<T>(col0 - m.col0, col1 - m.col1, col2 - m.col2);
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator * (const Matrix3<T>& m) const
    {
        Matrix3<T> Result(0);
        Result[0] = col0 * m.col0[0] + col1 * m.col0[1] + col2 * m.col0[2];
        Result[1] = col0 * m.col1[0] + col1 * m.col1[1] + col2 * m.col1[2];
        Result[2] = col0 * m.col2[0] + col1 * m.col2[1] + col2 * m.col2[2];
        return Result;
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator / (const Matrix3<T>& m) const
    {
        Matrix3<T> this_copy(*this);
        return this_copy /= m;
    }
    
    template <typename T>
    inline Vector3<T> Matrix3<T>::operator * (const Vector3<T>& vec3) const
    {
        const Vector3<T> Mul0 = col0 * vec3[0];
        const Vector3<T> Mul1 = col1 * vec3[1];
        const Vector3<T> Mul2 = col2 * vec3[2];
        return Mul0 + Mul1 + Mul2;
    }
    
    template <typename T>
    inline Vector3<T> Matrix3<T>::operator / (const Vector3<T>& vec3) const
    {
        return inverse() * vec3;
    }
    
    template <typename T>
    inline Matrix3<T>& Matrix3<T>::operator ++ ()
    {
        ++col0;
        ++col1;
        ++col2;
        return *this;
    }
    
    template <typename T>
    inline Matrix3<T>& Matrix3<T>::operator -- ()
    {
        --col0;
        --col1;
        --col2;
        return *this;
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator ++ (int)
    {
        Matrix3<T> result(*this);
        ++*this;
        return result;
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator -- (int)
    {
        Matrix3<T> result(*this);
        --*this;
        return result;
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::operator - ()
    {
        return Matrix3<T>(-col0, -col1, -col2);
    }
    
    template <typename T>
    inline bool Matrix3<T>::operator == (const Matrix3<T>& m) const
    {
        return col0 == m.col0 && col1 == m.col1 && col2 == m.col2;
    }
    
    template <typename T>
    inline bool Matrix3<T>::operator != (const Matrix3<T>& m) const
    {
        return col0 != m.col0 || col1 != m.col1 || col2 != m.col2;
    }
    
    template <typename T>
    inline Matrix3<T> operator + (const T& scalar, const Matrix3<T>& m)
    {
        return Matrix3<T>(scalar + m.col0, scalar + m.col1,  scalar + m.col2);
    }
    
    template <typename T>
    inline Matrix3<T> operator - (const T& scalar, const Matrix3<T>& m)
    {
        return Matrix3<T>(scalar - m.col0, scalar - m.col1,  scalar - m.col2);
    }
    
    template <typename T>
    inline Matrix3<T> operator * (const T& scalar, const Matrix3<T>& m)
    {
        return Matrix3<T>(scalar * m.col0, scalar * m.col1,  scalar * m.col2);
    }
    
    template <typename T>
    inline Matrix3<T> operator / (const T& scalar, const Matrix3<T>& m)
    {
        return Matrix3<T>(scalar / m.col0, scalar / m.col1,  scalar / m.col2, scalar / m.col3);
    }
    
    template <typename T>
    inline Vector3<T> operator * (const Vector3<T>& vec3, const Matrix3<T>& m)
    {
        return Vector3<T>(vec3.dot(m.col0), vec3.dot(m.col1), vec3.dot(m.col2), vec3.dot(m.col3));
    }
    
    template <typename T>
    inline Vector3<T> operator / (const Vector3<T>& vec3, const Matrix3<T>& m)
    {
        return vec3 * m.inverse();
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::transpose() const
    {
        Matrix3<T> result = *this;
        result.col0.y = col1.x;
        result.col0.z = col2.x;
        result.col1.x = col0.y;
        result.col1.z = col2.y;
        result.col2.x = col0.z;
        result.col2.y = col1.z;
        return result;
    }
    
    template <typename T>
    inline Matrix3<T> Matrix3<T>::inverse() const
    {
        const Matrix3<T>& m = *this;
        T OneOverDeterminant = static_cast<T>(1) /
        ( + m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
          - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
          + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));
        
        Matrix3<T> Inverse(0);
        Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
        Inverse[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]);
        Inverse[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
        Inverse[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]);
        Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
        Inverse[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]);
        Inverse[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
        Inverse[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]);
        Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
        
        return Inverse * OneOverDeterminant;
    }
    
    
} //namespace glm


#endif
