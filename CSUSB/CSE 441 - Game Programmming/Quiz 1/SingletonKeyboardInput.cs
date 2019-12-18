using Unity.Entities;

public struct SingletonKeyboardInput : IComponentData
{
    public boolean ForwardArrowKey;
    public boolean BackArrowKey;
    public boolean LeftArrowKey;
    public boolean RightArrowKey;
    public float HorizontalMovement;
    public float VerticalMovement;
}
