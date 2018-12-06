#include "DrawingParameter.h"
#include "DrawingRawResource.h"

using namespace Engine;

DrawingParameter::DrawingParameter()
{
}

DrawingParameter::~DrawingParameter()
{
}

const uint32_t DrawingParameter::GetBitsValue(uint32_t val, uint32_t bits, uint32_t offset)
{
    return ((val >> offset) & ((0x1 << bits) - 1));
}

const uint32_t DrawingParameter::GetObjectType(uint32_t type)
{
    return GetBitsValue(type, Object_Type_Bits, Object_Type_Offset);
}

const uint32_t DrawingParameter::GetDataSetType(uint32_t type)
{
    return GetBitsValue(type, DataSet_Type_Bits, DataSet_Type_Offset);
}

const uint32_t DrawingParameter::GetBasicType(uint32_t type)
{
    return GetBitsValue(type, Basic_Type_Bits, Basic_Type_Offset);
}

const uint32_t DrawingParameter::GetArraySize(uint32_t type)
{
    return GetBitsValue(type, Array_Size_Bits, Array_Size_Offset);
}

const uint32_t DrawingParameter::GetRowSize(uint32_t type)
{
    return GetBitsValue(type, Row_Size_Bits, Row_Size_Offset);
}

const uint32_t DrawingParameter::GetColSize(uint32_t type)
{
    return GetBitsValue(type, Col_Size_Bits, Col_Size_Offset);
}

const uint32_t DrawingParameter::GetStructSize(uint32_t type)
{
    return GetBitsValue(type, Struct_Size_Bits, Struct_Size_Offset);
}

std::shared_ptr<const std::string> DrawingParameter::GetName() const
{
    return m_pName;
}

void DrawingParameter::SetName(std::shared_ptr<const std::string> name)
{
    m_pName = name;
}

std::shared_ptr<const std::string> DrawingParameter::GetSemantic() const
{
    return m_pSemantic;
}

void DrawingParameter::SetSemantic(std::shared_ptr<const std::string> semantic)
{
    m_pSemantic = semantic;
}

uint32_t DrawingParameter::GetSize() const
{
    return m_size;
}

void DrawingParameter::SetSize(uint32_t size)
{
    m_size = size;
}

uint32_t DrawingParameter::GetType() const
{
    return m_type;
}

void DrawingParameter::SetType(uint32_t type)
{
    m_type = type;
}

const void* const DrawingParameter::GetValuePtr() const
{
    return m_pValue;
}

uint32_t DrawingParameter::GetObjectType() const
{
    return GetObjectType(m_type);
}

uint32_t DrawingParameter::GetDataSetType() const
{
    return GetDataSetType(m_type);
}

uint32_t DrawingParameter::GetBasicType() const
{
    return GetBasicType(m_type);
}

uint32_t DrawingParameter::GetArraySize() const
{
    return GetArraySize(m_type);
}

uint32_t DrawingParameter::GetRowSize() const
{
    return GetRowSize(m_type);
}

uint32_t DrawingParameter::GetColSize() const
{
    return GetColSize(m_type);
}

uint32_t DrawingParameter::GetStructSize() const
{
    return GetStructSize(m_type);
}

uint32_t DrawingParameter::GetVectorSize() const
{
    return GetRowSize(m_type);
}

template <typename T>
const T& DrawingParameter::AsValue() const
{
    return *(T*)m_pValue;
}

template <typename T>
void DrawingParameter::AsValue(const T& val)
{
    if (memcmp(m_pValue, &val, sizeof(T)) != 0)
        *(T*)m_pValue = val;
}

template <typename T, EBasicType type>
const T& DrawingParameter::AsScalar() const
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Scalar);
    static_assert(GetBasicType() == type);

    return AsValue<T>();
}

template <typename T, EBasicType type>
void DrawingParameter::AsScalar(const T& val)
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Scalar);
    static_assert(GetBasicType() == type);

    AsValue<T>(val);
}

template <typename T, EBasicType type, uint32_t size>
const T& DrawingParameter::AsVector() const
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Vector);
    static_assert(GetBasicType() == type);
    static_assert(GetVectorSize() == size);

    return AsVector<T>();
}

template <typename T, EBasicType type, uint32_t size>
void DrawingParameter::AsVector(const T& val)
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Vector);
    static_assert(GetBasicType() == type);
    static_assert(GetVectorSize() == size);

    AsVector<T>(val);
}

template <typename T, EBasicType type, uint32_t row_size, uint32_t col_size>
const T& DrawingParameter::AsMatrix() const
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Matrix);
    static_assert(GetBasicType() == type);
    static_assert(GetRowSize() == row_size);
    static_assert(GetColSize() == col_size);

    return AsMatrix<T>();
}

template <typename T, EBasicType type, uint32_t row_size, uint32_t col_size>
void DrawingParameter::AsMatrix(const T& val)
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Matrix);
    static_assert(GetBasicType() == type);
    static_assert(GetRowSize() == row_size);
    static_assert(GetColSize() == col_size);

    AsMatrix<T>(val);
}

template <typename T>
const T* DrawingParameter::AsValueArray(uint32_t& array_size) const
{
    array_size = GetArraySize();
    return (T*)m_pValue;
}

template <typename T>
void DrawingParameter::AsValueArray(const T* val, uint32_t array_size)
{
    static_assert(GetArraySize() == array_size);

    if (memcmp(m_pValue, val, sizeof(T) * array_size) != 0)
        memcpy(m_pValue, val, m_size);
}

template <typename T, EBasicType type>
const T* DrawingParameter::AsScalarArray(uint32_t& array_size) const
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Scalar);
    static_assert(GetBasicType() == type);

    return AsValueArray<T>(array_size);
}

template <typename T, EBasicType type>
void DrawingParameter::AsScalarArray(const T* val, uint32_t array_size)
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Scalar);
    static_assert(GetBasicType() == type);

    AsValueArray<T>(val, array_size);
}

template <typename T, EBasicType type, uint32_t size>
const T* DrawingParameter::AsVectorArray(uint32_t& array_size) const
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Vector);
    static_assert(GetBasicType() == type);
    static_assert(GetVectorSize() == size);

    return AsValueArray<T>(array_size);
}

template <typename T, EBasicType type, uint32_t size>
void DrawingParameter::AsVectorArray(const T* val, uint32_t array_size)
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Vector);
    static_assert(GetBasicType() == type);
    static_assert(GetVectorSize() == size);

    AsValueArray<T>(val, array_size);
}

template <typename T, EBasicType type, uint32_t row_size, uint32_t col_size>
const T* DrawingParameter::AsMatrixArray(uint32_t& array_size) const
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Matrix);
    static_assert(GetBasicType() == type);
    static_assert(GetRowSize() == row_size);
    static_assert(GetColSize() == col_size);

    return AsMatrixArray<T>(array_size);
}

template <typename T, EBasicType type, uint32_t row_size, uint32_t col_size>
void DrawingParameter::AsMatrixArray(const T* val, uint32_t array_size)
{
    static_assert(GetObjectType() == eObject_Value);
    static_assert(GetDataSetType() == eDataSet_Matrix);
    static_assert(GetBasicType() == type);
    static_assert(GetRowSize() == row_size);
    static_assert(GetColSize() == col_size);

    AsMatrixArray<T>(val, array_size);
}

