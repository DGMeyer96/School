using System;
using System.Collections.Generic;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;

[RequiresEntityConversion]
public class CubeProxy : MonoBehaviour, IDeclareReferencedPrefabs, IConvertGameObjectToEntity
{
    public GameObject prefab;
    public int hp;
    public int dmg;

    // Referenced prefabs have to be declared so that the conversion system knows about them ahead of time
    public void DeclareReferencedPrefabs(List<GameObject> gameObjects)
    {
        gameObjects.Add(prefab);
    }

    public void Convert(Entity entity, EntityManager dstManager, GameObjectConversionSystem conversionSystem)
    {
        var health = new Health
        {
            Value = hp
        };
        dstManager.AddComponentData(entity, health);

        var spawner = new CubeSpawner
        {
            Prefab = conversionSystem.GetPrimaryEntity(prefab)
        };
        dstManager.AddComponentData(entity, spawner);
    }
}
