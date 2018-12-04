#pragma once

#include <string>
#include <memory>

namespace Engine
{
    enum
    {
        Object_Type_Bits = 4,
        Object_Type_Offset = 28,

        DataSet_Type_Bits = 4,
        DataSet_Type_Offset = 24,

        Basic_Type_Bits = 4,
        Basic_Type_Offset = 20,

        Array_Size_Bits = 8,
        Array_Size_Offset = 12,

        Row_Size_Bits = 4,
        Row_Size_Offset = 8,

        Col_Size_Bits = 4,
        Col_Size_Offset = 4,

        Struct_Size_Bits = 4,
        Struct_Size_Offset = 0,
    };

    enum EObjectType
    {
        eObject_Value = 0,
        eObject_Texture,
        eObject_Buffer,
        eObject_RWBuffer,
        eObject_TexBuffer,
        eObject_Sampler,
    };

    enum EDataSetType
    {
        eDataSet_Scalar = 0,
        eDataSet_Vector,
        eDataSet_Matrix,
        eDataSet_Struct,
        eDataSet_Object,
    };

    enum EBasicType
    {
        eBasic_Bool = 0,
        eBasic_UInt32,
        eBasic_Int32,
        eBasic_FP32,
        eBasic_FP64,
    };

    #define SET_BITS(val, bits, offset) ((val & ((0x1 << bits) - 1)) << offset)

    #define COMPOSE_TYPE(object, dataset, basic, array, row, col)       \
        SET_BITS(object, Object_Type_Bits, Object_Type_Offset) |        \
        SET_BITS(dataset, DataSet_Type_Bits, DataSet_Type_Offset) |     \
        SET_BITS(basic, Basic_Type_Bits, Basic_Type_Offset) |           \
        SET_BITS(array, Array_Size_Bits, Array_Size_Offset) |           \
        SET_BITS(row, Row_Size_Bits, Row_Size_Offset) |                 \
        SET_BITS(col, Col_Size_Bits, Col_Size_Offset)

    #define COMPOSE_STRUCT_TYPE(object, dataset, basic, array, struct)  \
        SET_BITS(object, Object_Type_Bits, Object_Type_Offset) |        \
        SET_BITS(dataset, DataSet_Type_Bits, DataSet_Type_Offset) |     \
        SET_BITS(basic, Basic_Type_Bits, Basic_Type_Offset) |           \
        SET_BITS(array, Array_Size_Bits, Array_Size_Offset) |           \
        SET_BITS(struct, Struct_Size_Bits, Struct_Size_Offset)

    #define COMPOSE_SCALAR(basic)           COMPOSE_TYPE(eObject_Value, eDataSet_Scalar, basic, 0, 0, 0)
    #define COMPOSE_VECTOR(basic, size)     COMPOSE_TYPE(eObject_Value, eDataSet_Vector, basic, 0, size, 0)
    #define COMPOSE_MATRIX(basic, row, col) COMPOSE_TYPE(eObject_Value, eDataSet_Matrix, basic, 0, row, col)
    #define COMPOSE_OBJECT(object)          COMPOSE_TYPE(object, eDataSet_Object, eBasic_FP32, 0, 0, 0)
    #define COMPOSE_STRUCT(size)            COMPOSE_STRUCT_TYPE(eObject_Value, eDataSet_Struct, eBasic_FP32, 0, size)

    enum EParamType
    {
        EParam_Bool = COMPOSE_SCALAR(eBasic_Bool),
        EParam_UInt = COMPOSE_SCALAR(eBasic_UInt32),
        EParam_Int = COMPOSE_SCALAR(eBasic_Int32),
        EParam_Float = COMPOSE_SCALAR(eBasic_FP32),
        EParam_Double = COMPOSE_SCALAR(eBasic_FP64),

        EParam_Bool2 = COMPOSE_VECTOR(eBasic_Bool, 2),
        EParam_UInt2 = COMPOSE_VECTOR(eBasic_UInt32, 2),
        EParam_Int2 = COMPOSE_VECTOR(eBasic_Int32, 2),
        EParam_Float2 = COMPOSE_VECTOR(eBasic_FP32, 2),
        EParam_Double2 = COMPOSE_VECTOR(eBasic_FP64, 2),

        EParam_Bool3 = COMPOSE_VECTOR(eBasic_Bool, 3),
        EParam_UInt3 = COMPOSE_VECTOR(eBasic_UInt32, 3),
        EParam_Int3 = COMPOSE_VECTOR(eBasic_Int32, 3),
        EParam_Float3 = COMPOSE_VECTOR(eBasic_FP32, 3),
        EParam_Double3 = COMPOSE_VECTOR(eBasic_FP64, 3),

        EParam_Bool4 = COMPOSE_VECTOR(eBasic_Bool, 4),
        EParam_UInt4 = COMPOSE_VECTOR(eBasic_UInt32, 4),
        EParam_Int4 = COMPOSE_VECTOR(eBasic_Int32, 4),
        EParam_Float4 = COMPOSE_VECTOR(eBasic_FP32, 4),
        EParam_Double4 = COMPOSE_VECTOR(eBasic_FP64, 4),

        EParam_Bool3x3 = COMPOSE_MATRIX(eBasic_Bool, 3, 3),
        EParam_UInt3x3 = COMPOSE_MATRIX(eBasic_UInt32, 3, 3),
        EParam_Int3x3 = COMPOSE_MATRIX(eBasic_Int32, 3, 3),
        EParam_Float3x3 = COMPOSE_MATRIX(eBasic_FP32, 3, 3),
        EParam_Double3x3 = COMPOSE_MATRIX(eBasic_FP64, 3, 3),

        EParam_Bool4x4 = COMPOSE_MATRIX(eBasic_Bool, 4, 4),
        EParam_UInt4x4 = COMPOSE_MATRIX(eBasic_UInt32, 4, 4),
        EParam_Int4x4 = COMPOSE_MATRIX(eBasic_Int32, 4, 4),
        EParam_Float4x4 = COMPOSE_MATRIX(eBasic_FP32, 4, 4),
        EParam_Double4x4 = COMPOSE_MATRIX(eBasic_FP64, 4, 4),

        EParam_Texture = COMPOSE_OBJECT(eObject_Texture),
        EParam_Buffer = COMPOSE_OBJECT(eObject_Buffer),
        EParam_RWBuffer = COMPOSE_OBJECT(eObject_RWBuffer),
        EParam_TexBuffer = COMPOSE_OBJECT(eObject_TexBuffer),
        EParam_Sampler = COMPOSE_OBJECT(eObject_Sampler),
    };

    class DrawingParameter
    {
    public:
        DrawingParameter();
        DrawingParameter()

    private:
        std::shared_ptr<const std::string> m_pName;
        std::shared_ptr<const std::string> m_pSemantic;
        void* m_pValue;
    }
}