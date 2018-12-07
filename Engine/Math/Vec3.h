#pragma once

#include <array>

namespace Engine
{
    template<typename T>
    class Vec3
    {
    public:
        typedef Vec3<T> type;
        typedef T value_type;
        typedef size_t size_type;

        union
        {
            T mData[3];
            std::array<T, 3> mArray;
            struct{ T x, y, z; };
        };

        Vec3();
        Vec3(const Vec3& vec);
        Vec3(Vec3&& vec);
        Vec3(const T& val);
        Vec3(const T& val1, const T& val2, const T& val3);

        size_type Size() const;

        const T& operator[] (size_type index) const;
        T& operator[](size_type index);

        Vec3& operator= (const Vec3& vec);
        template<typename U>
        Vec3& operator= (const Vec3<U>& vec);

        template<typename U>
        Vec3& operator+= (const U& scalar);
        template<typename U>
        Vec3& operator+= (const Vec3<U>& vec);

        template<typename U>
        Vec3& operator-= (const U& scalar);
        template<typename U>
        Vec3& operator-= (const Vec3<U>& vec);

        template<typename U>
        Vec3& operator*= (const U& scalar);
        template<typename U>
        Vec3& operator*= (const Vec3<U>& vec);

        template<typename U>
        Vec3& operator/= (const U& scalar);
        template<typename U>
        Vec3& operator/= (const Vec3<U>& vec);
    };

    template<typename T>
    Vec3<T> operator+ (const Vec3<T>& vec, const T& scalar);
    template<typename T>
    Vec3<T> operator+ (const T& scalar, const Vec3<T>& vec);
    template<typename T>
    Vec3<T> operator+ (const Vec3<T>& vec1, const Vec3<T>& vec2);

    template<typename T>
    Vec3<T> operator- (const Vec3<T>& vec, const T& scalar);
    template<typename T>
    Vec3<T> operator- (const T& scalar, const Vec3<T>& vec);
    template<typename T>
    Vec3<T> operator- (const Vec3<T>& vec1, const Vec3<T>& vec2);

    template<typename T>
    Vec3<T> operator* (const Vec3<T>& vec, const T& scalar);
    template<typename T>
    Vec3<T> operator* (const T& scalar, const Vec3<T>& vec);
    template<typename T>
    Vec3<T> operator* (const Vec3<T>& vec1, const Vec3<T>& vec2);

    template<typename T>
    Vec3<T> operator/ (const Vec3<T>& vec, const T& scalar);
    template<typename T>
    Vec3<T> operator/ (const T& scalar, const Vec3<T>& vec);
    template<typename T>
    Vec3<T> operator/ (const Vec3<T>& vec1, const Vec3<T>& vec2);

    template<typename T>
    bool operator== (const Vec3<T>& vec1, const Vec3<T>& vec2);
    template<typename T>
    bool operator!= (const Vec3<T>& vec1, const Vec3<T>& vec2);

    template<typename T>
    bool operator< (const Vec3<T>& vec1, const Vec3<T>& vec2);
    template<typename T>
    bool operator<= (const Vec3<T>& vec1, const Vec3<T>& vec2);

    template<typename T>
    bool operator> (const Vec3<T>& vec1, const Vec3<T>& vec2);
    template<typename T>
    bool operator>= (const Vec3<T>& vec1, const Vec3<T>& vec2);

    template<typename T>
    Vec3<T> operator- (const Vec3<T>& vec);
}