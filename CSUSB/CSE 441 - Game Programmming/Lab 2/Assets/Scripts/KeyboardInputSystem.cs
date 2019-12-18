using System.Collections;
using System.Collections.Generic;
using Unity.Entities;
using UnityEngine;

public class KeyboardInputSystem : ComponentSystem
{
    protected override void OnUpdate()
    {
        var keyboardInput = GetSingleton<SingletonKeyboardInput>();

        keyboardInput.HorizontalMovement = Input.GetAxis("Horizontal");
        keyboardInput.VerticalMovement = Input.GetAxis("Vertical");

        if ( Input.GetKey(KeyCode.UpArrow) )
        {
            keyboardInput.ForwardArrowKey = true;
        }
        else if ( Input.GetKey(KeyCode.DownArrow) )
        {
            keyboardInput.BackArrowKey = true;
        }
        else
        {
            keyboardInput.ForwardArrowKey = false;
            keyboardInput.BackArrowKey = false;
        }
        if ( Input.GetKey(KeyCode.LeftArrow) )
        {
            keyboardInput.LeftArrowKey = true;
        }
        else if ( Input.GetKey(KeyCode.RightArrow) )
        {
            keyboardInput.RightArrowKey = true;
        }
        else
        {
            keyboardInput.LeftArrowKey = false;
            keyboardInput.RightArrowKey = false;
        }

        SetSingleton<SingletonKeyboardInput>(keyboardInput);
    }
}
