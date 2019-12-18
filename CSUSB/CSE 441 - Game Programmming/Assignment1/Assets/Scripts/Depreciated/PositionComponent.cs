using System;
using UnityEngine;
using Unity.Entities;

namespace Assignment1.ECS1
{
    //Makes it visible in editor
    [Serializable]
    public struct Position : IComponentData
    {
        public Vector3 Value;
    }

    //CompnentDataProxy<> replaces ComponentDataWrapper<>
    //public class PositionComponent : ComponentDataProxy<Position> { };
}
