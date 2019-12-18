using Unity.Entities;
using Unity.Mathematics;
using UnityEngine;

namespace Assignment1.ECS1
{
    public class MouseInputSystem : ComponentSystem
    {
        protected override void OnUpdate()
        {
            var mouseInput = GetSingleton<MouseInput>();

            mouseInput.MousePosition = Input.mousePosition;
            var ray = Camera.main.ScreenPointToRay(mouseInput.MousePosition);

            UnityEngine.RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                mouseInput.MouseRaycastPosition = hit.point;
            }
            /*
            else
            {
                mouseInput.MouseRaycastPosition = Camera.main.ScreenToWorldPoint(mouseInput.MousePosition);
            }
            */
            if (Input.GetMouseButtonDown(0))
            {
                mouseInput.LeftClickDown = true;
                mouseInput.RightClickUp = false;
            }
            else if (Input.GetMouseButtonUp(0))
            {
                mouseInput.LeftClickUp = true;
                mouseInput.LeftClickDown = false;
            }
            if (Input.GetMouseButtonDown(1))
            {
                mouseInput.RightClickDown = true;
                mouseInput.RightClickUp = false;
            }
            else if (Input.GetMouseButtonUp(1))
            {
                mouseInput.RightClickUp = true;
                mouseInput.RightClickDown = false;
            }

            SetSingleton<MouseInput>(mouseInput);
        }
    }
}