#ifndef _FORWARD_BASE_H_
#define _FORWARD_BASE_H_

struct ForwardBase_Input
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
};

struct ForwardBase_VertexAttr
{
    noperspective float4 position : SV_Position;
    noperspective float3 normal : NORMAL;
    noperspective float4 lightViewPosition : TEXCOORD0;
};

#endif