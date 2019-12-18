//using System.Collections;
//using System.Collections.Generic;
using Unity.Collections;
using Unity.Entities;
using Unity.Transforms;
using UnityEngine;


namespace Assignment1.ECS1
{
    public class CubeSpawner : MonoBehaviour
    {
        
        public GameObject Prefab;
        public int health;
        public int damage;

        Entity entity;
        EntityManager manager;

        void Start()
        {
            entity = GameObjectConversionUtility.ConvertGameObjectHierarchy(Prefab, World.Active);
            manager = World.Active.EntityManager;
        }

        void Update()
        {
            if (Input.GetMouseButtonDown(1))    //Right Mouse click = 1; Left Mouse click = 0
            {
                print("Right Click");

                //var instance = manager.Instantiate(entity);
                //manager.SetComponentData(instance, new Translation { Value = Input.mousePosition });
                //entity = GameObjectConversionUtility.ConvertGameObjectHierarchy(Prefab, World.Active);


                var instance = manager.Instantiate(entity);
                manager.SetComponentData<MouseInput>(entity, new MouseInput { MousePosition = Input.mousePosition });
            }

            if (Input.GetMouseButtonDown(0))
            {
                //manager.DestroyEntity(entity);

                Debug.Log("" + manager.GetComponentData<Health>(entity).Value);

                print("Left Click");

                manager.DestroyEntity(entity);

                //Need to iterate each entity
                if (manager.GetComponentData<Health>(entity).Value < 0)
                {
                    UnityEngine.Debug.Log("Destroying");
                    print("Destroying");
                    //manager.Exists(entity) = false;
                    
                }
            }
        }

        /*
        void Update()
        {
            //Spawn objects w/ right mouse click
            if (Input.GetMouseButtonDown(1))    //Right Mouse click = 1; Left Mouse click = 0
            {
                SpawnCube();
            }
            
            if(Input.GetMouseButtonDown(0))
            {
                //Need to iterate each entity
                DamageCubes();
            }
            
        }

        void SpawnCube()
        {
            var instance = manager.Instantiate(entity);

            Vector3 mousePos = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0.0f);
            Vector3 worldPos;
            Ray ray = Camera.main.ScreenPointToRay(mousePos);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, 1000f))
            {
                worldPos = hit.point;
            }
            else
            {
                worldPos = Camera.main.ScreenToWorldPoint(mousePos);
            }
            worldPos.y += 0.25f;

            //Translation (using Unity.Transforms) supplies translation component of GameObject
            manager.SetComponentData(instance, new Translation { Value = worldPos });
        }

        //Current problem lies here, need a way to damage all entities and then if their HP <= 0, destroy the entity
        void DamageCubes()
        {
            //Update entity's health
            int currentHealth = manager.GetComponentData<Health>(entity).Value - damage;

            //Entity dead, destroy entity
            if (currentHealth <= 0)
            {
                manager.DestroyEntity(entity);
            }
        }
        */
    }
}
