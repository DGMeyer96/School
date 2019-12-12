using Unity.Jobs;
using Unity.Entities;
using UnityEngine;

public class KeyActivationSystem : JobComponentSystem
{
    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var keyboardInput = GetSingleton<SingletonKeyboardInput>();

        if (Input.GetKeyDown(KeyCode.Q))
        {
            keyboardInput.Q_key = true;
        }
        else
        {
            keyboardInput.Q_key = false;
        }

        if (Input.GetKeyDown(KeyCode.W))
        {
            keyboardInput.W_key = true;
        }
        else
        {
            keyboardInput.W_key = false;
        }

        if (Input.GetKeyDown(KeyCode.E))
        {
            keyboardInput.E_key = true;
        }
        else
        {
            keyboardInput.E_key = false;
        }

        if (Input.GetKeyDown(KeyCode.R))
        {
            keyboardInput.R_key = true;
        }
        else
        {
            keyboardInput.R_key = false;
        }

        SetSingleton<SingletonKeyboardInput>(keyboardInput);

        return inputDeps;
    }
}
