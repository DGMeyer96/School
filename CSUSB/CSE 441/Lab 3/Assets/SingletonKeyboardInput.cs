using Unity.Entities;

public struct SingletonKeyboardInput : IComponentData
{
    public bool SpaceBar;
    public bool Q_key;
    public bool W_key;
    public bool E_key;
    public bool R_key;
    public float HorizontalMovement;
    public float VerticalMovement;
}
