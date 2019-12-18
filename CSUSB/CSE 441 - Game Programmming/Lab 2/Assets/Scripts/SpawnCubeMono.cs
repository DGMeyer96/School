using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Entities;
using Unity.Transforms;

public class SpawnCubeMono : MonoBehaviour
{
    public GameObject Prefab;
    public EntityManager manager;
    public Entity entity;

    // Start is called before the first frame update
    void Start()
    {
        Entity prefab = GameObjectConversionUtility.ConvertGameObjectHierarchy(Prefab, World.Active);
        manager = World.Active.EntityManager;
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButton(0))
        {
            var instance = manager.Instantiate(entity);
            //manager.SetComponentData(entity, new Translation{Value =)
        }
    }
}
