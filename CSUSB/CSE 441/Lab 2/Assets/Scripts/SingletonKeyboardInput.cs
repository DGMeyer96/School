using Unity.Entities;

public struct SingletonKeyboardInput : IComponentData
{
    public bool ForwardArrowKey;
    public bool BackArrowKey;
    public bool LeftArrowKey;
    public bool RightArrowKey;
    public float HorizontalMovement;
    public float VerticalMovement;
}
