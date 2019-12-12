using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Entities;
using Unity.Collections;

public class GameManager : MonoBehaviour
{
    public GameObject thePrefab;
    EntityManager manager;

    // Update is called once per frame
    void Update()
    {
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

            Entity converted = GameObjectConversionUtility.ConvertGameObjectHierarchy(thePrefab, World.Active);
            manager.Instantiate(converted);

            //SpawnCube();
        }

        /*
        if (Input.GetMouseButtonDown(0))
        {
            DestroyAllObjects();
        }
        */
    }
}
