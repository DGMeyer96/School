using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointToMousePosition : MonoBehaviour
{
    public Camera mainCamera;

    // Start is called before the first frame update
    void Start()
    {
        //RaycastHit hit;
        //Ray mouseRay = mainCamera.ScreenPointToRay(Input.mousePosition);
        

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        RaycastHit2D hit;
        Ray mouseRay = mainCamera.ScreenPointToRay(Input.mousePosition);
        hit = Physics2D.Raycast(new Vector2(mouseRay.direction.x,
                                mouseRay.direction.y), 
                                mouseRay.direction);

        //if (hit)
        //{
        //    Debug.Log("I am hitting it");
        //}

        Vector3 mousePosition = Input.mousePosition;
        Vector3 objectPosition = mainCamera.WorldToScreenPoint(transform.position);

        mousePosition.x = mousePosition.x - transform.position.x;
        mousePosition.y = mousePosition.y - transform.position.y;

        float angle = Mathf.Atan2(mousePosition.y, mousePosition.x) * Mathf.Rad2Deg;

        transform.localRotation = Quaternion.Euler(new Vector3(0, 0, angle));
    }
}
