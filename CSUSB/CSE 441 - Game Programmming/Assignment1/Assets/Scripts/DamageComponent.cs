using System;
using Unity.Entities;

namespace Assignment1.ECS1
{
    //Makes it visible in editor
    [Serializable]
    public struct Damage : IComponentData
    {
        public int Value;
    }

    //CompnentDataProxy<> replaces ComponentDataWrapper<>
    //public class DamageComponent : ComponentDataProxy<Damage> { };
}