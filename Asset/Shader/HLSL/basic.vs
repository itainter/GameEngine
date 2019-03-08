#include "basic.h"

BasicPrimitive_VertexAttr BasicPrimitive_VS(BasicPrimitive_Input input)
{
    BasicPrimitive_VertexAttr output = (BasicPrimitive_VertexAttr)0;

    float offset = 2.f / 64.f;

    int row = floor(input.InstanceID * offset / 2.f);
    int col = input.InstanceID % 64.f;

    int id = input.VertexID;

    float startX = -1.f + offset * col;
    float startY = -1.f + offset * row;

    if (id == 0)
        output.position.xyz = float3(startX, startY, 1.0f);
    else if(id == 1)
        output.position.xyz = float3(startX, startY + offset, 1.0f);
    else
        output.position.xyz = float3(startX + offset, startY + offset, 1.0f);

    output.position.w = 1.0f;

    return output;
}