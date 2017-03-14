//
//  matrix_transform.h
//  SOSOMap
//
//  Created by samczli on 25/12/14.
//  Copyright (c) 2014 Tencent. All rights reserved.
//

#ifndef __SOSOMap__matrix_transform__
#define __SOSOMap__matrix_transform__

#include <stdio.h>
#include <math.h>
#include "math_type.h"

// 矩阵变换的translate 和 rotate 在开源的glm中有正常和添加后缀_slow的两个版本，_slow版本的实现更符合正常的运算思维，但效率较低，这里取效率较高的版本，
// 如果您有兴趣，可以手动验证较快版本的正确性。

namespace glm {
    
    /// Builds a translation 4 * 4 matrix created from a vector of 3 components.
    ///
    /// @param m Input matrix multiplied by this translation matrix.
    /// @param v Coordinates of a translation vector.
    /// glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f));
    /// // m[0][0] == 1.0f, m[0][1] == 0.0f, m[0][2] == 0.0f, m[0][3] == 0.0f
    /// // m[1][0] == 0.0f, m[1][1] == 1.0f, m[1][2] == 0.0f, m[1][3] == 0.0f
    /// // m[2][0] == 0.0f, m[2][1] == 0.0f, m[2][2] == 1.0f, m[2][3] == 0.0f
    /// // m[3][0] == 1.0f, m[3][1] == 1.0f, m[3][2] == 1.0f, m[3][3] == 1.0f
    template <typename T>
    Matrix4<T> translate(const Matrix4<T>& m, const Vector3<T>& v);
    template <typename T>
    Matrix4<T> translate(const Matrix4<T>& m, const T& x, const T& y, const T& z);
    
    /// Builds a rotation 4 * 4 matrix created from an axis vector and an angle.
    ///
    /// @param m Input matrix multiplied by this rotation matrix.
    /// @param angle Rotation angle expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
    /// @param axis Rotation axis, recommanded to be normalized.
    template <typename T>
    Matrix4<T> rotate(const Matrix4<T>& m, const T& angle, const Vector3<T>& axis);
    template <typename T>
    Matrix4<T> rotate(const Matrix4<T>& m, const T& angle, const T& x, const T& y, const T& z);
    
    /// Builds a scale 4 * 4 matrix created from 3 scalars.
    ///
    /// @param m Input matrix multiplied by this scale matrix.
    /// @param v Ratio of scaling for each axis.
    template <typename T>
    Matrix4<T> scale(const Matrix4<T>& m, const Vector3<T>& v);
    template <typename T>
    Matrix4<T> scale(const Matrix4<T>& m, const T& x, const T& y, const T& z);
    
    /// Creates a matrix for an orthographic parallel viewing volume.
    ///
    /// @param left
    /// @param right
    /// @param bottom
    /// @param top
    /// @param zNear
    /// @param zFar
    template <typename T>
    Matrix4<T> ortho(const T& left, const T& right, const T& bottom, const T& top, const T& zNear, const T& zFar);
    
    /// Creates a matrix for projecting two-dimensional coordinates onto the screen.
    ///
    /// @param left
    /// @param right
    /// @param bottom
    /// @param top
    template <typename T>
    Matrix4<T> ortho(const T& left, const T& right, const T& bottom, const T& top);
    
    /// Creates a frustum matrix.
    ///
    /// @param left
    /// @param right
    /// @param bottom
    /// @param top
    /// @param near
    /// @param far
    template <typename T>
    Matrix4<T> frustum(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far);
    
    /// Creates a matrix for a symetric perspective-view frustum.
    ///
    /// @param fovy Expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
    /// @param aspect
    /// @param near
    /// @param far
    template <typename T>
    Matrix4<T> perspective(const T& fovy, const T& aspect, const T& near, const T& far);
    
    /// Builds a perspective projection matrix based on a field of view.
    ///
    /// @param fov Expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
    /// @param width
    /// @param height
    /// @param near
    /// @param far
    template <typename T>
    Matrix4<T> perspectiveFov(const T& fov, const T& width, const T& height, const T& near, const T& far);
    
    /// Creates a matrix for a symmetric perspective-view frustum with far plane at infinite.
    ///
    /// @param fovy Expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
    /// @param aspect
    /// @param near
    template <typename T>
    Matrix4<T> infinitePerspective(T fovy, T aspect, T near);
    
    /// Creates a matrix for a symmetric perspective-view frustum with far plane at infinite for graphics hardware that doesn't support depth clamping.
    ///
    /// @param fovy Expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
    /// @param aspect
    /// @param near
    template <typename T>
    Matrix4<T> tweakedInfinitePerspective(T fovy, T aspect, T near);
    
    /// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
    ///
    /// @param obj
    /// @param model
    /// @param proj
    /// @param viewport
    template <typename T, typename U>
    Vector3<T> project(const Vector3<T>& obj, const Matrix4<T>& model, const Matrix4<T>& proj, Vector4<U> const & viewport);
    
    /// Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
    ///
    /// @param win
    /// @param model
    /// @param proj
    /// @param viewport
    template <typename T, typename U>
    Vector3<T> unProject(const Vector3<T>& win, const Matrix4<T>& model, const Matrix4<T>& proj, Vector4<U> const & viewport);
    
    /// Define a picking region
    ///
    /// @param center
    /// @param delta
    /// @param viewport
    template <typename T, typename U>
    Matrix4<T> pickMatrix(const Vector2<T>& center, const Vector2<T>& delta, Vector4<U> const & viewport);
    
    /// Build a look at view matrix.
    ///
    /// @param eye Position of the camera
    /// @param center Position where the camera is looking at
    /// @param up Normalized up vector, how the camera is oriented. Typically (0, 0, 1)
    template <typename T>
    Matrix4<T> lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up);
    template <typename T>
    Matrix4<T> lookAt(T eyex, T eyey, T eyez, T centerx, T centery, T centerz, T upx, T upy, T upz);
    
    
    
    
    
    
    // implementations
    ////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    inline Matrix4<T> translate(const Matrix4<T>& m, const Vector3<T>& v)
    {
        Matrix4<T> result(m);
        result[3] =   m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
        return result;
    }
    
    template <typename T>
    inline Matrix4<T> translate(const Matrix4<T>& m, const T& x, const T& y, const T& z)
    {
        Matrix4<T> result(m);
        result[3] =   m[0] * x + m[1] * y + m[2] * z + m[3];
        return result;
    }
    
    
    template <typename T>
    inline Matrix4<T> rotate(const Matrix4<T>& m, const T& radian, const Vector3<T>& v)
    {
        T a = radian;
        T c = cosf(a);
        T s = sinf(a);
        
        Vector3<T> axis(normalize(v));
        Vector3<T> temp((T(1) - c) * axis);
        
        Matrix4<T> Rotate(0);
        Rotate[0][0] = c + temp[0] * axis[0];
        Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
        Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];
        
        Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
        Rotate[1][1] = c + temp[1] * axis[1];
        Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];
        
        Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
        Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
        Rotate[2][2] = c + temp[2] * axis[2];
        
        Matrix4<T> Result(0);
        Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
        Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
        Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
        Result[3] = m[3];
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> rotate(const Matrix4<T>& m, const T& angle, const T& x, const T& y, const T &z)
    {
        return rotate(m, angle, Vector3<T>(x, y, z));
    }
    
    template <typename T>
    inline Matrix4<T> scale(const Matrix4<T>& m, const Vector3<T>& v)
    {
        Matrix4<T> Result(0);
        Result[0] = m[0] * v[0];
        Result[1] = m[1] * v[1];
        Result[2] = m[2] * v[2];
        Result[3] = m[3];
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> scale(const Matrix4<T>& m, const T& x, const T& y, const T& z)
    {
        Matrix4<T> Result(0);
        Result[0] = m[0] * x;
        Result[1] = m[1] * y;
        Result[2] = m[2] * z;
        Result[3] = m[3];
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> ortho(const T& left, const T& right, const T& bottom, const T& top, const T& zNear, const T& zFar)
    {
        Matrix4<T> Result(1);
        Result[0][0] = static_cast<T>(2) / (right - left);
        Result[1][1] = static_cast<T>(2) / (top - bottom);
        Result[2][2] = - T(2) / (zFar - zNear);
        Result[3][0] = - (right + left) / (right - left);
        Result[3][1] = - (top + bottom) / (top - bottom);
        Result[3][2] = - (zFar + zNear) / (zFar - zNear);
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> ortho(const T& left, const T& right, const T& bottom, const T& top)
    {
        Matrix4<T> Result(1);
        Result[0][0] = static_cast<T>(2) / (right - left);
        Result[1][1] = static_cast<T>(2) / (top - bottom);
        Result[2][2] = - T(1);
        Result[3][0] = - (right + left) / (right - left);
        Result[3][1] = - (top + bottom) / (top - bottom);
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> frustum(const T& left, const T& right, const T& bottom, const T& top, const T& nearVal, const T& farVal)
    {
        Matrix4<T> Result(0);
        Result[0][0] = (T(2) * nearVal) / (right - left);
        Result[1][1] = (T(2) * nearVal) / (top - bottom);
        Result[2][0] = (right + left) / (right - left);
        Result[2][1] = (top + bottom) / (top - bottom);
        Result[2][2] = -(farVal + nearVal) / (farVal - nearVal);
        Result[2][3] = T(-1);
        Result[3][2] = -(T(2) * farVal * nearVal) / (farVal - nearVal);
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> perspective(const T& fovy, const T& aspect, const T& zNear, const T& zFar)
    {
        map_assert(aspect != T(0));
        map_assert(zFar != zNear);
        const T rad = fovy;
        
        T tanHalfFovy = tanf(rad / T(2));
        
        Matrix4<T> Result(T(0));
        Result[0][0] = T(1) / (aspect * tanHalfFovy);
        Result[1][1] = T(1) / (tanHalfFovy);
        Result[2][2] = - (zFar + zNear) / (zFar - zNear);
        Result[2][3] = - T(1);
        Result[3][2] = - (T(2) * zFar * zNear) / (zFar - zNear);
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> perspectiveFov(const T& fov, const T& width, const T& height, const T& zNear, const T& zFar)
    {
        map_assert(width > T(0));
        map_assert(height > T(0));
        map_assert(fov > T(0));
        
        T rad = fov;
        T h = cos(T(0.5) * rad) / sin(T(0.5) * rad);
        T w = h * height / width; ///todo max(width , Height) / min(width , Height)?
        
        Matrix4<T> Result(T(0));
        Result[0][0] = w;
        Result[1][1] = h;
        Result[2][2] = - (zFar + zNear) / (zFar - zNear);
        Result[2][3] = - T(1);
        Result[3][2] = - (T(2) * zFar * zNear) / (zFar - zNear);
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> infinitePerspective(T fovy, T aspect, T zNear)
    {
        const T range = tan(fovy / T(2)) * zNear;
        T left = -range * aspect;
        T right = range * aspect;
        T bottom = -range;
        T top = range;
        
        Matrix4<T> Result(T(0));
        Result[0][0] = (T(2) * zNear) / (right - left);
        Result[1][1] = (T(2) * zNear) / (top - bottom);
        Result[2][2] = - T(1);
        Result[2][3] = - T(1);
        Result[3][2] = - T(2) * zNear;
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> tweakedInfinitePerspective(T fovy, T aspect, T zNear)
    {
        T range = tan(fovy / T(2)) * zNear;
        T left = -range * aspect;
        T right = range * aspect;
        T bottom = -range;
        T top = range;
        
        Matrix4<T> Result(T(0));
        Result[0][0] = (T(2) * zNear) / (right - left);
        Result[1][1] = (T(2) * zNear) / (top - bottom);
        Result[2][2] = static_cast<T>(0.0001) - T(1);
        Result[2][3] = static_cast<T>(-1);
        Result[3][2] = - (T(0.0001) - T(2)) * zNear;
        return Result;
    }
    
    template <typename T, typename U>
    inline Vector3<T> project(const Vector3<T>& obj, const Matrix4<T>& model, const Matrix4<T>& proj, Vector4<U> const & viewport)
    {
        Vector4<T> tmp = Vector4<T>(obj, T(1));
        tmp = model * tmp;
        tmp = proj * tmp;
        
        tmp /= tmp.w;
        tmp = tmp * T(0.5) + T(0.5);
        tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
        tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);
        
        return Vector3<T>(tmp);
    }
    
    template <typename T, typename U>
    inline Vector3<T> unProject(const Vector3<T>& win, const Matrix4<T>& model, const Matrix4<T>& proj, Vector4<U> const & viewport)
    {
        Matrix4<T> Inverse = (proj * model).inverse();
        
        Vector4<T> tmp = Vector4<T>(win, T(1));
        tmp.x = (tmp.x - T(viewport[0])) / T(viewport[2]);
        tmp.y = (tmp.y - T(viewport[1])) / T(viewport[3]);
        tmp = tmp * T(2) - T(1);
        
        Vector4<T> obj = Inverse * tmp;
        obj /= obj.w;
        
        return Vector3<T>(obj);
    }
    
    template <typename T, typename U>
    inline Matrix4<T> pickMatrix(const Vector2<T>& center, const Vector2<T>& delta, Vector4<U> const & viewport)
    {
        map_assert(delta.x > T(0) && delta.y > T(0));
        Matrix4<T> Result(1.0f);
        
        if(!(delta.x > T(0) && delta.y > T(0)))
            return Result; // Error
        
        Vector3<T> Temp((T(viewport[2]) - T(2) * (center.x - T(viewport[0]))) / delta.x,
                        (T(viewport[3]) - T(2) * (center.y - T(viewport[1]))) / delta.y,
                        T(0));
        
        // Translate and scale the picked region to the entire window
        Result = translate(Result, Temp);
        return scale(Result, Vector3<T>(T(viewport[2]) / delta.x, T(viewport[3]) / delta.y, T(1)));
    }
    
    template <typename T>
    inline Matrix4<T> lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up)
    {
        Vector3<T> f(normalize(center - eye));
        Vector3<T> s(normalize(cross(f, up)));
        Vector3<T> u(cross(s, f));
        
        Matrix4<T> Result(1);
        Result[0][0] = s.x;
        Result[1][0] = s.y;
        Result[2][0] = s.z;
        Result[0][1] = u.x;
        Result[1][1] = u.y;
        Result[2][1] = u.z;
        Result[0][2] =-f.x;
        Result[1][2] =-f.y;
        Result[2][2] =-f.z;
        Result[3][0] =-dot(s, eye);
        Result[3][1] =-dot(u, eye);
        Result[3][2] = dot(f, eye);
        return Result;
    }
    
    template <typename T>
    inline Matrix4<T> lookAt(T eyex, T eyey, T eyez, T centerx, T centery, T centerz, T upx, T upy, T upz)
    {
        lookAt(Vector3<T>(eyex, eyey, eyez), Vector3<T>(centerx, centery, centerz), Vector3<T>(upx, upy, upz));
    }
}

#endif /* defined(__SOSOMap__matrix_transform__) */
