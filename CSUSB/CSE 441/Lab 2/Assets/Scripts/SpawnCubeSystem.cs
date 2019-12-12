using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Entities;
using Unity.Jobs;
using Unity.Burst;
using Unity.Mathematics;
using Unity.Transforms;
using Unity.Collections;

[UpdateInGroup(typeof(SimulationSystemGroup))]
public class SpawnCubeSystem : JobComponentSystem
{
    BeginInitializationEntityCommandBufferSystem m_EntityCommandBufferSystem;

    protected override void OnCreate()
    {
        // Cache the BeginInitializationEntityCommandBufferSystem in a field, so we don't have to create it every frame
        m_EntityCommandBufferSystem = World.GetOrCreateSystem<BeginInitializationEntityCommandBufferSystem>();
    }

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        //Instead of performing structural changes directly, a Job can add a command to an EntityCommandBuffer to perform such changes on the main thread after the Job has finished.
        //Command buffers allow you to perform any, potentially costly, calculations on a worker thread, while queuing up the actual insertions and deletions for later.

        
        // Schedule the job that will add Instantiate commands to the EntityCommandBuffer.
        var job = new SpawnJob
        {
            mouseInput = GetSingleton<SingletonMouseInput>(),
            CommandBuffer = m_EntityCommandBufferSystem.CreateCommandBuffer()
        }.ScheduleSingle(this, inputDeps);


        // SpawnJob runs in parallel with no sync point until the barrier system executes.
        // When the barrier system executes we want to complete the SpawnJob and then play back the commands (Creating the entities and placing them).
        // We need to tell the barrier system which job it needs to complete before it can play back the commands.
        m_EntityCommandBufferSystem.AddJobHandleForProducer(job);

        return job;
    }

    public struct SpawnJob : IJobForEachWithEntity<Health, CubeSpawner>
    {
        public SingletonMouseInput mouseInput;
        public EntityCommandBuffer CommandBuffer;

        public void Execute(Entity entity, int index, ref Health health, [ReadOnly] ref CubeSpawner spawner)
        {
            if (mouseInput.RightClickDown == true)
            {
                Debug.Log("Right Click");
                mouseInput.RightClickDown = false;

                var instance = CommandBuffer.Instantiate(spawner.Prefab);
                CommandBuffer.SetComponent(instance, new Translation { Value = mouseInput.MouseRaycastPosition });
            }

            
        }
    }
}
