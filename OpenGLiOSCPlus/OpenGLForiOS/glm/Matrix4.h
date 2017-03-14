//
//  Matrix4.h
//  SOSOMap
//
//  Created by samczli on 23/12/14.
//  Copyright (c) 2014 Tencent. All rights reserved.
//

#ifndef __SOSOMap__Matrix4__
#define __SOSOMap__Matrix4__

#include "math_type.h"

// 附：OpenGL按列存储，此处Matrix按照OpenGL实现，其中col_type相当于OpenGL所指的列。左乘右乘与存储无关，只与参数存放在矩阵中的位置有关。OpenGL采用左乘，即变换矩阵必须出现在乘号左边。DirectX采用右乘，因为其变换矩阵的表达形式为OpenGL的转置。与此同时，DirectX按行存储，因此对于同一个变换矩阵，DirectX与OpenGL存储的数据是完全相同的。


namespace glm {
    
    template <typename T>
    class Matrix4
    {
        
    public:
        typedef T value_type;
        typedef std::size_t size_type;
        typedef Vector4<T>  col_type;
        typedef Vector4<T>  row_type;
        typedef Matrix4<T>  type;
        typedef Matrix4<T>& reference_type;
        
        col_type col0;
        col_type col1;
        col_type col2;
        col_type col3;
        
        
    public:
        
        Matrix4()
        {
            value_type zero(0);
            value_type one(1);
            col0 = col_type(one, zero, zero, zero);
            col1 = col_type(zero, one, zero, zero);
            col2 = col_type(zero, zero, one, zero);
            col3 = col_type(zero, zero, zero, one);
        }
        
        Matrix4(const T& scalar)
        {
            value_type zero(0);
            col0 = col_type(scalar, zero, zero, zero);
            col1 = col_type(zero, scalar, zero, zero);
            col2 = col_type(zero, zero, scalar, zero);
            col3 = col_type(zero, zero, zero, scalar);
        }
        
        template <typename Q>
        Matrix4(const Q* ptr)
        :col0(ptr)
        ,col1(ptr + 4)
        ,col2(ptr + 8)
        ,col3(ptr + 12)
        {
            
        }
        
        template<typename Q>
        explicit Matrix4(const Matrix4<Q>& m)
        :col0(m.col0)
        ,col1(m.col1)
        ,col2(m.col2)
        ,col3(m.col3)
        {
            
        }
        
        template<typename Q1, typename Q2, typename Q3, typename Q4>
        Matrix4(const Vector4<Q1>& c0, const Vector4<Q2>& c1, const Vector4<Q3>& c2, const Vector4<Q4>& c3)
        :col0(c0)
        ,col1(c1)
        ,col2(c2)
        ,col3(c3)
        {
            
        }
        
        Matrix4(const T& x0, const T& y0, const T& z0, const T& w0,
                const T& x1, const T& y1, const T& z1, const T& w1,
                const T& x2, const T& y2, const T& z2, const T& w2,
                const T& x3, const T& y3, const T& z3, const T& w3
                )
        {
            col0 = col_type(x0, y0, z0, w0);
            col1 = col_type(x1, y1, z1, w1);
            col2 = col_type(x2, y2, z2, w2);
            col3 = col_type(x3, y3, z3, w3);
        }
        
        
    public:
        
        col_type& operator [] (length_t i)
        {
            map_assert(i < 4 && i >= 0);
            return (&col0)[i];
        }
        
        const col_type& operator [] (length_t i) const
        {
            map_assert(i < 4 && i >= 0);
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
            map_assert(i < 4 && i >= 0);
            return row_type(col0[i], col1[i], col2[i], col3[i]);
        }
        
        reference_type operator = (const Matrix4<T>& m);
        
        template <typename Q>
        reference_type operator = (const Matrix4<Q>& m);
        template <typename Q>
        reference_type operator += (const Q& scalar);
        template <typename Q>
        reference_type operator += (const Matrix4<Q>& m);
        template <typename Q>
        reference_type operator -= (const Q& scalar);
        template <typename Q>
        reference_type operator -= (const Matrix4<Q>& m);
        template <typename Q>
        reference_type operator *= (const Q& scalar);
        template <typename Q>
        reference_type operator *= (const Matrix4<Q>& m);
        template <typename Q>
        reference_type operator /= (const Q& scalar);
        template <typename Q>
        reference_type operator /= (const Matrix4<Q>& m);
        
        type operator + (const T& scalar) const;
        type operator - (const T& scalar) const;
        type operator * (const T& scalar) const;
        type operator / (const T& scalar) const;
        
        type operator + (const Matrix4& m) const;
        type operator - (const Matrix4& m) const;
        type operator * (const Matrix4& m) const;
        type operator / (const Matrix4& m) const;
        
        Vector4<T> operator * (const Vector4<T>& vec4) const;
        Vector4<T> operator / (const Vector4<T>& vec4) const;
        
        reference_type operator ++ ();
        reference_type operator -- ();
        type operator ++ (int);
        type operator -- (int);
        type operator - ();
        
        bool operator == (const Matrix4<T>& m) const;
        bool operator != (const Matrix4<T>& m) const;
        
    public:
        
//        friend type operator + (const T& scalar, const Matrix4<T>& m);
//        friend type operator - (const T& scalar, const Matrix4<T>& m);
//        friend type operator * (const T& scalar, const Matrix4<T>& m);
//        friend type operator / (const T& scalar, const Matrix4<T>& m);
//        
//        friend Vector4<T> operator * (const Vector4<T>& vec4, const Matrix4<T>& m);
//        friend Vector4<T> operator / (const Vector4<T>& vec4, const Matrix4<T>& m);
        
        type transpose() const;           // 转置矩阵
        type inverse() const;             // 逆矩阵
        
        void print() const;
    };
    
    template <typename T>
    inline Matrix4<T>& Matrix4<T>::operator = (const Matrix4<T>& m)
    {
        // memcpy could be faster.
        col0 = m.col0;
        col1 = m.col1;
        col2 = m.col2;
        col3 = m.col3;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator = (const Matrix4<Q>& m)
    {
        col0 = m.col0;
        col1 = m.col1;
        col2 = m.col2;
        col3 = m.col3;
        return *this;
    }
    
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator+= (const Q& scalar)
    {
        col0 += scalar;
        col1 += scalar;
        col2 += scalar;
        col3 += scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator += (const Matrix4<Q>& m)
    {
        col0 += m.col0;
        col1 += m.col1;
        col2 += m.col2;
        col3 += m.col3;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator -= (const Q& scalar)
    {
        col0 -= scalar;
        col1 -= scalar;
        col2 -= scalar;
        col3 -= scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator -= (const Matrix4<Q>& m)
    {
        col0 -= m.col0;
        col1 -= m.col1;
        col2 -= m.col2;
        col3 -= m.col3;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator *= (const Q& scalar)
    {
        col0 *= scalar;
        col1 *= scalar;
        col2 *= scalar;
        col3 *= scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator *= (const Matrix4<Q>& m)
    {
        return (*this = *this * m);
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator /= (const Q& scalar)
    {
        col0 /= scalar;
        col1 /= scalar;
        col2 /= scalar;
        col3 /= scalar;
        return *this;
    }
    
    template <typename T>
    template <typename Q>
    inline Matrix4<T>& Matrix4<T>::operator /= (const Matrix4<Q>& m)
    {
        *this = (*this * m.inverse());
        return *this;
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator + (const T& scalar) const
    {
        return Matrix4<T>(col0 + scalar, col1 + scalar, col2 + scalar, col3 + scalar);
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator - (const T& scalar) const
    {
        return Matrix4<T>(col0 - scalar, col1 - scalar, col2 - scalar, col3 - scalar);
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator * (const T& scalar) const
    {
        return Matrix4<T>(col0 * scalar, col1 * scalar, col2 * scalar, col3 * scalar);
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator / (const T& scalar) const
    {
        return Matrix4<T>(col0 / scalar, col1 / scalar, col2 / scalar, col3 / scalar);
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator + (const Matrix4<T>& m) const
    {
        return Matrix4<T>(col0 + m.col0, col1 + m.col1, col2 + m.col2, col3 + m.col3);
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator - (const Matrix4<T>& m) const
    {
        return Matrix4<T>(col0 - m.col0, col1 - m.col1, col2 - m.col2, col3 - m.col3);
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator * (const Matrix4<T>& m) const
    {
        Matrix4<T> Result(0);
        Result[0] = col0 * m.col0[0] + col1 * m.col0[1] + col2 * m.col0[2] + col3 * m.col0[3];
        Result[1] = col0 * m.col1[0] + col1 * m.col1[1] + col2 * m.col1[2] + col3 * m.col1[3];
        Result[2] = col0 * m.col2[0] + col1 * m.col2[1] + col2 * m.col2[2] + col3 * m.col2[3];
        Result[3] = col0 * m.col3[0] + col1 * m.col3[1] + col2 * m.col3[2] + col3 * m.col3[3];
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator / (const Matrix4<T>& m) const
    {
        Matrix4<T> this_copy(*this);
        return this_copy /= m;
    }
    
    template <typename T>
    inline Vector4<T> Matrix4<T>::operator * (const Vector4<T>& vec4) const
    {
        const Vector4<T> Mul0 = col0 * vec4[0];
        const Vector4<T> Mul1 = col1 * vec4[1];
        const Vector4<T> Mul2 = col2 * vec4[2];
        const Vector4<T> Mul3 = col3 * vec4[3];
        return Mul0 + Mul1 + Mul2 + Mul3;
    }
    
    template <typename T>
    inline Vector4<T> Matrix4<T>::operator / (const Vector4<T>& vec4) const
    {
        return inverse() * vec4;
    }
    
    template <typename T>
    inline Matrix4<T>& Matrix4<T>::operator ++ ()
    {
        ++col0;
        ++col1;
        ++col2;
        ++col3;
        return *this;
    }
    
    template <typename T>
    inline Matrix4<T>& Matrix4<T>::operator -- ()
    {
        --col0;
        --col1;
        --col2;
        --col3;
        return *this;
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator ++ (int)
    {
        Matrix4<T> result(*this);
        ++*this;
        return result;
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator -- (int)
    {
        Matrix4<T> result(*this);
        --*this;
        return result;
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::operator - ()
    {
        return Matrix4<T>(-col0, -col1, -col2, - col3);
    }
    
    template <typename T>
    inline bool Matrix4<T>::operator == (const Matrix4<T>& m) const
    {
        return col0 == m.col0 && col1 == m.col1 && col2 == m.col2 && col3 == m.col3;
    }
    
    template <typename T>
    inline bool Matrix4<T>::operator != (const Matrix4<T>& m) const
    {
        return col0 != m.col0 || col1 != m.col1 || col2 != m.col2 || col3 != m.col3;
    }
    
    template <typename T>
    inline Matrix4<T> operator + (const T& scalar, const Matrix4<T>& m)
    {
        return Matrix4<T>(scalar + m.col0, scalar + m.col1,  scalar + m.col2, scalar + m.col3);
    }
    
    template <typename T>
    inline Matrix4<T> operator - (const T& scalar, const Matrix4<T>& m)
    {
        return Matrix4<T>(scalar - m.col0, scalar - m.col1,  scalar - m.col2, scalar - m.col3);
    }
    
    template <typename T>
    inline Matrix4<T> operator * (const T& scalar, const Matrix4<T>& m)
    {
        return Matrix4<T>(scalar * m.col0, scalar * m.col1,  scalar * m.col2, scalar * m.col3);
    }
    
    template <typename T>
    inline Matrix4<T> operator / (const T& scalar, const Matrix4<T>& m)
    {
        return Matrix4<T>(scalar / m.col0, scalar / m.col1,  scalar / m.col2, scalar / m.col3);
    }
    
    template <typename T>
    inline Vector4<T> operator * (const Vector4<T>& vec4, const Matrix4<T>& m)
    {
        return Vector4<T>(vec4.dot(m.col0), vec4.dot(m.col1), vec4.dot(m.col2), vec4.dot(m.col3));
    }
    
    template <typename T>
    inline Vector4<T> operator / (const Vector4<T>& vec4, const Matrix4<T>& m)
    {
        return vec4 * m.inverse();
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::transpose() const
    {
        Matrix4<T> result = *this;
        result.col0.y = col1.x;
        result.col0.z = col2.x;
        result.col0.w = col3.x;
        result.col1.x = col0.y;
        result.col1.z = col2.y;
        result.col1.w = col3.y;
        result.col2.x = col0.z;
        result.col2.y = col1.z;
        result.col2.w = col3.z;
        result.col3.x = col0.w;
        result.col3.y = col1.w;
        result.col3.z = col2.w;
        return result;
    }
    
    template <typename T>
    inline Matrix4<T> Matrix4<T>::inverse() const
    {
        const Matrix4<T>& m = *this;
        T Coef00 = m.col2[2] * m.col3[3] - m.col3[2] * m.col2[3];
        T Coef02 = m.col1[2] * m.col3[3] - m.col3[2] * m.col1[3];
        T Coef03 = m.col1[2] * m.col2[3] - m.col2[2] * m.col1[3];
        
        T Coef04 = m.col2[1] * m.col3[3] - m.col3[1] * m.col2[3];
        T Coef06 = m.col1[1] * m.col3[3] - m.col3[1] * m.col1[3];
        T Coef07 = m.col1[1] * m.col2[3] - m.col2[1] * m.col1[3];
        
        T Coef08 = m.col2[1] * m.col3[2] - m.col3[1] * m.col2[2];
        T Coef10 = m.col1[1] * m.col3[2] - m.col3[1] * m.col1[2];
        T Coef11 = m.col1[1] * m.col2[2] - m.col2[1] * m.col1[2];
        
        T Coef12 = m.col2[0] * m.col3[3] - m.col3[0] * m.col2[3];
        T Coef14 = m.col1[0] * m.col3[3] - m.col3[0] * m.col1[3];
        T Coef15 = m.col1[0] * m.col2[3] - m.col2[0] * m.col1[3];
        
        T Coef16 = m.col2[0] * m.col3[2] - m.col3[0] * m.col2[2];
        T Coef18 = m.col1[0] * m.col3[2] - m.col3[0] * m.col1[2];
        T Coef19 = m.col1[0] * m.col2[2] - m.col2[0] * m.col1[2];
        
        T Coef20 = m.col2[0] * m.col3[1] - m.col3[0] * m.col2[1];
        T Coef22 = m.col1[0] * m.col3[1] - m.col3[0] * m.col1[1];
        T Coef23 = m.col1[0] * m.col2[1] - m.col2[0] * m.col1[1];
        
        Vector4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
        Vector4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
        Vector4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
        Vector4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
        Vector4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
        Vector4<T> Fac5(Coef20, Coef20, Coef22, Coef23);
        
        Vector4<T> Vec0(m.col1[0], m.col0[0], m.col0[0], m.col0[0]);
        Vector4<T> Vec1(m.col1[1], m.col0[1], m.col0[1], m.col0[1]);
        Vector4<T> Vec2(m.col1[2], m.col0[2], m.col0[2], m.col0[2]);
        Vector4<T> Vec3(m.col1[3], m.col0[3], m.col0[3], m.col0[3]);
        
        Vector4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
        Vector4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
        Vector4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
        Vector4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
        
        Vector4<T> SignA(+1, -1, +1, -1);
        Vector4<T> SignB(-1, +1, -1, +1);
        Matrix4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
        
        Vector4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);
        
        Vector4<T> Dot0(m.col0 * Row0);
        T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
        
        map_assert(0 != Dot1);
        if (0 == Dot1)  return Matrix4<T>(1.0);
        
        T OneOverDeterminant = static_cast<T>(1) / Dot1;
        
        return Inverse * OneOverDeterminant;
    }

    template<typename T>
    inline void Matrix4<T>::print() const
    {
        map_printf("Matrix4i:\n");
        map_printf("| %i %i %i %i |\n", (int)col0.x, (int)col1.x, (int)col2.x, (int)col3.x);
        map_printf("| %i %i %i %i |\n", (int)col0.y, (int)col1.y, (int)col2.y, (int)col3.y);
        map_printf("| %i %i %i %i |\n", (int)col0.z, (int)col1.z, (int)col2.z, (int)col3.z);
        map_printf("| %i %i %i %i |\n", (int)col0.w, (int)col1.w, (int)col2.w, (int)col3.w);
        map_printf("\n");
    }
    
    template<>
    inline void Matrix4<float>::print() const
    {
        map_printf("Matrix4f:\n");
        map_printf("| %f %f %f %f |\n", col0.x, col1.x, col2.x, col3.x);
        map_printf("| %f %f %f %f |\n", col0.y, col1.y, col2.y, col3.y);
        map_printf("| %f %f %f %f |\n", col0.z, col1.z, col2.z, col3.z);
        map_printf("| %f %f %f %f |\n", col0.w, col1.w, col2.w, col3.w);
        map_printf("\n");
    }
    
    template<>
    inline void Matrix4<double>::print() const
    {
        map_printf("Matrix4d:\n");
        map_printf("| %f %f %f %f |\n", col0.x, col1.x, col2.x, col3.x);
        map_printf("| %f %f %f %f |\n", col0.y, col1.y, col2.y, col3.y);
        map_printf("| %f %f %f %f |\n", col0.z, col1.z, col2.z, col3.z);
        map_printf("| %f %f %f %f |\n", col0.w, col1.w, col2.w, col3.w);
        map_printf("\n");
    }
}

#endif /* defined(__SOSOMap__Matrix4__) */
