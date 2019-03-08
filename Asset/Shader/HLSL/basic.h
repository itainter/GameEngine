#ifndef _BASIC_H_
#define _BASIC_H_

struct BasicPrimitive_Input
{
    int VertexID : TEXCOORD0;
    int InstanceID : TEXCOORD1;
};

struct BasicPrimitive_VertexAttr
{
    noperspective float4 position : SV_Position;
};

#endif