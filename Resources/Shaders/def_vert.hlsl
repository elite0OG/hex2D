struct VSout
{
    float3 cl : Color;         // COLOR output
    float4 pos : SV_POSITION; // SV_POSITION requires float4
   
};

cbuffer Cbuf
{
    matrix model;
    //matrix4x4 view;
    matrix projection;
    float4 uColor;
};
     

VSout main(float2 pos : Position, float3 c : Color)
{
    VSout output;
    output.pos = mul(mul(float4(pos, 0.0, 1.0), model), projection);
    //output.pos.w = 1.0;
   // output.pos.y *= -1.f;
    output.cl = uColor;
    return output;
}

