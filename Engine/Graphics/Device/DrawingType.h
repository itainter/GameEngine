#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat2x2.h"
#include "Mat3x3.h"
#include "Mat4x4.h"

namespace Engine
{
    using bool2 = Vec2<bool>;
    using bool3 = Vec3<bool>;
    using bool4 = Vec4<bool>;

    using uint2 = Vec2<uint32_t>;
    using uint3 = Vec3<uint32_t>;
    using uint4 = Vec4<uint32_t>;

    using int2 = Vec2<int32_t>;
    using int3 = Vec3<int32_t>;
    using int4 = Vec4<int32_t>;

    using float2 = Vec2<float>;
    using float3 = Vec3<float>;
    using float4 = Vec4<float>;

    using double2 = Vec2<double>;
    using double3 = Vec3<double>;
    using double4 = Vec4<double>;

    using uint2x2 = Mat2x2<uint32_t>;
    using uint3x3 = Mat3x3<uint32_t>;
    using uint4x4 = Mat4x4<uint32_t>;

    using int2x2 = Mat2x2<int32_t>;
    using int3x3 = Mat3x3<int32_t>;
    using int4x4 = Mat4x4<int32_t>;

    using float2x2 = Mat2x2<float>;
    using float3x3 = Mat3x3<float>;
    using float4x4 = Mat4x4<float>;

    using double2x2 = Mat2x2<double>;
    using double3x3 = Mat3x3<double>;
    using double4x4 = Mat4x4<double>;
}