using System;
using System.Collections.Generic;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;

[RequiresEntityConversion]
public class AddPlayerSingletons : MonoBehaviour, IConvertGameObjectToEntity
{
    public float playerSpeed = 200.0f;

    public void Convert(Entity entity, EntityManager dstManager, GameObjectConversionSystem conversionSystem)
    {
        var mouseInput = new SingletonMouseInput
        {
            RightClickDown = false,
            LeftClickDown = false,
            RightClickUp = false,
            LeftClickUp = false,
            MousePosition = float3.zero,
            MouseRaycastPosition = float3.zero
        };
        dstManager.AddComponentData(entity, mouseInput);

        var keyboardInput = new SingletonKeyboardInput
        {
            ForwardArrowKey = false,
            BackArrowKey = false,
            LeftArrowKey = false,
            RightArrowKey = false
        };
        dstManager.AddComponentData(entity, keyboardInput);

        var movementSpeed = new MovementSpeed
        {
            Value = playerSpeed
        };
        dstManager.AddComponentData(entity, movementSpeed);

        var copyTransform = new Unity.Transforms.CopyTransformToGameObject { };
        dstManager.AddComponentData(entity, copyTransform);

        var player = new Player { };
        dstManager.AddComponentData(entity, player);
    }
}
