using Unity.Entities;
using Unity.Mathematics;

public struct SingletonMouseInput : IComponentData
{
    public boolean LeftClickDown;
    public boolean RightClickDown;
    public boolean LeftClickUp;
    public boolean RightClickUp;
    public float3 MousePosition;
    public float3 MouseRaycastPosition;
}