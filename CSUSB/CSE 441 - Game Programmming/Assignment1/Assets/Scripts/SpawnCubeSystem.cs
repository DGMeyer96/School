using Unity.Collections;
using UnityEngine;
using Unity.Transforms;
using Unity.Mathematics;
using Unity.Entities;
using Unity.Jobs;
using Unity.Burst;

/*
namespace Assignment1.ECS1
{
    public class SpawnCubeSystem : ComponentSystem
    {
        protected override void OnUpdate()
        {
            
            
        }
        
    }
}
*/

namespace Assignment1.ECS1
{
    public class SpawnCubeSystem : ComponentSystem
    {
        
        public GameObject Prefab;
        public int health;
        public int damage;

        Entity entity;
        EntityManager manager;

        protected override void OnCreateManager()    //Equal to Start()
        {
            entity = GameObjectConversionUtility.ConvertGameObjectHierarchy(Prefab, World.Active);
            manager = World.Active.EntityManager;
        }

        protected override void OnUpdate()
        {
            var mouseInput = GetSingleton<MouseInput>();

            mouseInput.MousePosition = Input.mousePosition; //float3 <- Vector3

            var ray = Camera.main.ScreenPointToRay(mouseInput.MousePosition);
            RaycastHit hit;

            if (Physics.Raycast(ray, out hit))
            {
                mouseInput.MousePosition = hit.point;
            }

            if (Input.GetMouseButtonDown(0))
            {
                mouseInput.LeftClickDown = true;
            }
            if(Input.GetMouseButtonDown(1))
            {
                mouseInput.RightClickDown = true;
            }

            SetSingleton<MouseInput>(mouseInput);
        }

        void SpawnCube()
        {
            
            var instance = manager.Instantiate(entity);

            /*
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
            manager.SetComponentData(instance, new Translation { Value =  worldPos });
            */
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
    }
}

/*
            Vector3 mousePos = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0.0f);
            
            //Spawn objects w/ right mouse click
            if (Input.GetMouseButtonDown(1))    //Right Mouse click = 1; Left Mouse click = 0
            {
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

                /*
                Entities.ForEach((ref Health health, ref Position position) =>
                {
                    //health.Value = 100;
                    position.Value = worldPos;
                });
                
            }
*/
