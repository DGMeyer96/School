using System;
using Unity.Entities;
using Unity.Mathematics; //float3

namespace Assignment1.ECS1
{
    //Makes it visible in editor
    [Serializable]
    public struct MouseInput : IComponentData
    {
        public float3 MousePosition;
        public float3 MouseRaycastPosition;
        public bool LeftClickDown;
        public bool LeftClickUp;
        public bool RightClickDown;
        public bool RightClickUp;
    }

    //CompnentDataProxy<> replaces ComponentDataWrapper<>
    //public class DamageComponent : ComponentDataProxy<Damage> { };
}

