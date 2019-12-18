using System;
using System.Collections.Generic;
using UnityEngine;
using Unity.Entities;
using Unity.Mathematics;

namespace Assignment1.ECS1
{
    [RequiresEntityConversion]
    public class SpawnCubeProxy : MonoBehaviour, IConvertGameObjectToEntity
    {
        //Allows HP to be seen in editor
        public int HP = 100;

        public void Convert(Entity entity, EntityManager dstManager, GameObjectConversionSystem conversionSystem)
        {
            var mouseInput = new MouseInput
            {
                MousePosition = float3.zero,
                MouseRaycastPosition = float3.zero,
                LeftClickDown = false,
                LeftClickUp = false,
                RightClickDown = false,
                RightClickUp = false
            };
            dstManager.AddComponentData(entity, mouseInput);

            //Sets entity's health value to what was given in editor
            var health = new Health
            {
                Value = HP
            };
            //var data1 = new Position { };
            dstManager.AddComponentData(entity, health);
            //dstManager.AddComponentData(entity, data1);

            var copyTransform = new Unity.Transforms.CopyTransformToGameObject { };
            dstManager.AddComponentData(entity, copyTransform);
        }
    }
}
