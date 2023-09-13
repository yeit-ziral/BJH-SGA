struct Group
{
    uint3 groupID;
    uint3 groupThreadID;
    uint3 dispatchTreadID;
    uint groupIndex;
};

struct ComputeInput
{
    uint3 groupID : SV_GroupID;
    uint3 groupThreadID : SV_GroupThreadID;
    uint3 dispatchTreadID : SV_DispatchThreadID;
    uint groupIndex : SV_GroupIndex;
};

RWByteAddressBuffer output : register(u0);

[numthreads(10, 8, 3)]
void main(ComputeInput input)
{
    Group group;
    group = input;
    
    uint index = input.groupID.x * 240 + input.groupIndex;
    uint address = index * 10 * 4;
    
    output.Store3(address +  0, group.groupID);
    output.Store3(address + 12, group.groupThreadID);
    output.Store3(address + 24, group.dispatchTreadID);
    output.Store (address + 36, group.groupIndex);
}

