#pragma once

#include <array>
#include <Matrix.h>

namespace Engine
{
    template <typename T>
    class Vec2;

    template<typename T>
    class Mat2x2 : public Mat
    {
    public:
        typedef Mat2x2<T> type;
        typedef Vec2<T> col_type;
        typedef Vec2<T> row_type;
        typedef T value_type;
        typedef size_t size_type;

        constexpr static int COL = 2;
        constexpr static int ROW = 2;
        union
        {
            T mData[2][2];
            std::array<row_type, 2> mArray;
            struct
            {
                T x00, x01,
                  x10, x11;
            };
        };

        Mat2x2();
        Mat2x2(const Mat2x2& mat);
        Mat2x2(Mat2x2&& mat);
        Mat2x2(const T& val);
        Mat2x2(const T& val00, const T& val01,
               const T& val10, const T& val11);
        Mat2x2(const row_type& vec0, const row_type& vec1);

        size_type Size() const;

        void Identity();

        const row_type operator[] (size_type index) const;
        row_type& operator[](size_type index);

        const row_type Row(size_type index) const;
        row_type& Row(size_type index);

        const col_type Col(size_type index) const;
        col_type& Col(size_type index);

        Mat2x2& operator= (const Mat2x2& mat);
        template<typename U>
        Mat2x2& operator= (const Mat2x2<U>& mat);

        template<typename U>
        Mat2x2& operator+= (const U& scalar);
        template<typename U>
        Mat2x2& operator+= (const Mat2x2<U>& mat);

        template<typename U>
        Mat2x2& operator-= (const U& scalar);
        template<typename U>
        Mat2x2& operator-= (const Mat2x2<U>& mat);

        template<typename U>
        Mat2x2& operator*= (const U& scalar);
        template<typename U>
        Mat2x2& operator*= (const Mat2x2<U>& mat);

        template<typename U>
        Mat2x2& operator/= (const U& scalar);
        template<typename U>
        Mat2x2& operator/= (const Mat2x2<U>& mat);
    };

    template<typename T>
    Mat2x2<T> operator+ (const Mat2x2<T>& mat, const T& scalar);
    template<typename T>
    Mat2x2<T> operator+ (const T& scalar, const Mat2x2<T>& mat);
    template<typename T>
    Mat2x2<T> operator+ (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);

    template<typename T>
    Mat2x2<T> operator- (const Mat2x2<T>& mat, const T& scalar);
    template<typename T>
    Mat2x2<T> operator- (const T& scalar, const Mat2x2<T>& mat);
    template<typename T>
    Mat2x2<T> operator- (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);

    template<typename T>
    Mat2x2<T> operator* (const Mat2x2<T>& mat, const T& scalar);
    template<typename T>
    Mat2x2<T> operator* (const T& scalar, const Mat2x2<T>& mat);
    template<typename T>
    Mat2x2<T> operator* (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);

    template<typename T>
    Mat2x2<T> operator/ (const Mat2x2<T>& mat, const T& scalar);
    template<typename T>
    Mat2x2<T> operator/ (const T& scalar, const Mat2x2<T>& mat);
    template<typename T>
    Mat2x2<T> operator/ (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);

    template<typename T>
    bool operator== (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);
    template<typename T>
    bool operator!= (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);

    template<typename T>
    bool operator< (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);
    template<typename T>
    bool operator<= (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);

    template<typename T>
    bool operator> (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);
    template<typename T>
    bool operator>= (const Mat2x2<T>& mat1, const Mat2x2<T>& mat2);

    template<typename T>
    Mat2x2<T> operator- (const Mat2x2<T>& mat);
}

#include "Mat2x2_imp.h"