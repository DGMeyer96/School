using Unity.Jobs;
using Unity.Entities;
using UnityEngine;

public class KeyboardInputSystem : JobComponentSystem
{
    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var keyboardInput = GetSingleton<SingletonKeyboardInput>();

        keyboardInput.HorizontalMovement = Input.GetAxis("Horizontal");
        keyboardInput.VerticalMovement = Input.GetAxis("Vertical");

        if ( Input.GetKeyDown(KeyCode.Space) )
        {
            keyboardInput.SpaceBar = true;
        }
        else
        {
            keyboardInput.SpaceBar = false;
        }

        SetSingleton<SingletonKeyboardInput>(keyboardInput);

        return inputDeps;
    }
}
