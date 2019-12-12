using Unity.Burst;
using Unity.Collections;
using Unity.Entities;
using Unity.Jobs;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;

namespace Assignment1.ECS1
{
    public class SpawnSystem : JobComponentSystem
    {
        [BurstCompile]
        struct SpawnJob : IJobForEach<Health, Translation>
        {
            public MouseInput mouseInput;
            public int damage;

            public void Execute(ref Health health, ref Translation translation)
            {
                
                if(mouseInput.RightClickDown == true)
                {
                    translation.Value = mouseInput.MouseRaycastPosition;
                    mouseInput.RightClickDown = false;
                }
                
                if (mouseInput.LeftClickDown == true)
                {
                    health.Value -= damage;
                    mouseInput.LeftClickDown = false;
                }
            }
        }

        protected override JobHandle OnUpdate(JobHandle inputDeps)
        {
            var spawnJob = new SpawnJob
            {
                mouseInput = GetSingleton<MouseInput>(),
                damage = 50
            };

            return spawnJob.Schedule(this, inputDeps);
        }
    }
}

