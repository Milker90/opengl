//
//  math_type.h
//  SOSOMap
//
//  Created by samczli on 24/12/14.
//  Copyright (c) 2014 Tencent. All rights reserved.
//

#ifndef SOSOMap_math_type_h
#define SOSOMap_math_type_h

#include <stdio.h>
#include <math.h>
namespace glm {
    
    typedef int length_t;           // Follow the GLSL specification.
    
    template <typename T> class Vector2;
    template <typename T> class Vector3;
    template <typename T> class Vector4;
    template <typename T> class Matrix3;
    template <typename T> class Matrix4;
    template <typename T> class Box2;
    template <typename T> class Box3;
    
    typedef Vector2<float>          Vector2f;
    typedef Vector2<double>         Vector2d;
    typedef Vector2<int>            Vector2i;
    typedef Vector2<unsigned int>   Vector2ui;
    typedef Vector2<long>			Vector2l;
    typedef Vector2<unsigned long>  Vector2ul;
    typedef Vector2<char>           Vector2b;
    typedef Vector2<unsigned char>  Vector2ub;
    
    typedef Vector3<float>          Vector3f;
    typedef Vector3<double>         Vector3d;
    typedef Vector3<int>            Vector3i;
    typedef Vector3<unsigned int>   Vector3ui;
    typedef Vector3<long>			Vector3l;
    typedef Vector3<unsigned long>  Vector3ul;
    typedef Vector3<char>           Vector3b;
    typedef Vector3<unsigned char>  Vector3ub;
    
    typedef Vector4<float>          Vector4f;
    typedef Vector4<double>         Vector4d;
    typedef Vector4<int>            Vector4i;
    typedef Vector4<unsigned int>   Vector4ui;
    typedef Vector4<long>			Vector4l;
    typedef Vector4<unsigned long>  Vector4ul;
    typedef Vector4<char>           Vector4b;
    typedef Vector4<unsigned char>  Vector4ub;
    
    typedef Matrix3<float>          Matrix3f;
    typedef Matrix3<double>         Matrix3d;
//    typedef Matrix3<int>            Matrix3i;
//    typedef Matrix3<unsigned int>   Matrix3ui;
//    typedef Matrix3<long>           Matrix3l;
//    typedef Matrix3<unsigned long>  Matrix3ul;
//    typedef Matrix3<char>           Matrix3b;
//    typedef Matrix3<unsigned char>  Matrix3ub;
    
    typedef Matrix4<float>          Matrix4f;
    typedef Matrix4<double>         Matrix4d;
//    typedef Matrix4<int>            Matrix4i;
//    typedef Matrix4<unsigned int>   Matrix4ui;
//    typedef Matrix4<long>           Matrix4l;
//    typedef Matrix4<unsigned long>  Matrix4ul;
//    typedef Matrix4<char>           Matrix4b;
//    typedef Matrix4<unsigned char>  Matrix4ub;
    
    typedef Box2<float>             Box2f;
    typedef Box2<double>            Box2d;
    typedef Box2<int>               Box2i;
    typedef Box3<float>             Box3f;
    typedef Box3<double>            Box3d;
    typedef Box3<int>               Box3i;
    
}

#include <cstddef>
#include "MapCompileDef.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Box2.h"
#include "Box3.h"

namespace glm {
    
//    extern template class Vector2<float>;
//    extern template class Vector2<double>;
//    extern template class Vector2<int>;
//    extern template class Vector2<unsigned int>;
//    extern template class Vector2<long>;
//    extern template class Vector2<unsigned long>;
//    extern template class Vector2<char>;
//    extern template class Vector2<unsigned char>;
//    
//    
//    extern template class Vector3<float>;
//    extern template class Vector3<double>;
//    extern template class Vector3<int>;
//    extern template class Vector3<unsigned int>;
//    extern template class Vector3<long>;
//    extern template class Vector3<unsigned long>;
//    extern template class Vector3<char>;
//    extern template class Vector3<unsigned char>;
//    
//    extern template class Vector4<float>;
//    extern template class Vector4<double>;
//    extern template class Vector4<int>;
//    extern template class Vector4<unsigned int>;
//    extern template class Vector4<long>;
//    extern template class Vector4<unsigned long>;
//    extern template class Vector4<char>;
//    extern template class Vector4<unsigned char>;
//    
//    extern template class Matrix4<float>;
//    extern template class Matrix4<double>;
//
//    extern template class Matrix3<float>;
//    extern template class Matrix3<double>;
    
}


#endif
