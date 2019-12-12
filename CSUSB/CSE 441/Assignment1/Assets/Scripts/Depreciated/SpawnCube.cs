using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnCube : MonoBehaviour
{
    public int damage = 50;

    public Transform thePrefab;

    // Update is called once per frame
    void Update()
    {
        Vector3 mousePos = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0.0f);

        //Spawn objects w/ right mouse click
        if (Input.GetMouseButtonDown(1))    //Right Mouse click = 1; Left Mouse click = 0
        {
            Vector3 wordPos;
            Ray ray = Camera.main.ScreenPointToRay(mousePos);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, 1000f))
            {
                wordPos = hit.point;
            }
            else
            {
                wordPos = Camera.main.ScreenToWorldPoint(mousePos);
            }
            wordPos.y += 0.25f;
            Instantiate(thePrefab, wordPos, Quaternion.identity);
        }

        if (Input.GetMouseButtonDown(0))
        {
            DestroyAllObjects();
        }
    }

    void DestroyAllObjects()
    {
        GameObject[] gameObjects = GameObject.FindGameObjectsWithTag("Unit");

        for (var i = 0; i < gameObjects.Length; i++)
        {
            gameObjects[i].GetComponent<Health>().health -= damage;
            Debug.Log("Current Health: " + gameObjects[i].GetComponent<Health>().health);
            if(gameObjects[i].GetComponent<Health>().health <= 0)
            {
                Destroy(gameObjects[i]);
            }
        }
    }
}
