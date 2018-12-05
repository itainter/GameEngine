#include "DrawingParameter.h"

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