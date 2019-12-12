using System.Collections;
using System.Collections.Generic;
using Unity.Entities;
using Unity.Transforms;
using UnityEngine;


namespace Assignment1.ECS1
{
    public class EntityTest : MonoBehaviour
    {
        public GameObject Prefab;
        EntityManager manager;
        Entity entity;
        public int health;
        public int damage;

        // Start is called before the first frame update
        void Start()
        {
            manager = World.Active.EntityManager;
            entity = GameObjectConversionUtility.ConvertGameObjectHierarchy(Prefab, World.Active);
        }

        // Update is called once per frame
        void Update()
        {
            //Spawn objects w/ right mouse click
            if (Input.GetMouseButtonDown(1))    //Right Mouse click = 1; Left Mouse click = 0
            {
                SpawnCube();
            }
        }

        void SpawnCube()
        {
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

            manager.Instantiate(entity);
            manager.SetComponentData(entity, new Translation { Value = worldPos });
        }
    }
}
