using Unity.Jobs;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using Unity.Collections;
using UnityEngine;

[UpdateAfter(typeof(KeyActivationSystem))]
public class SpawnMeteorSystem : JobComponentSystem
{
    BeginInitializationEntityCommandBufferSystem m_EntityCommandBufferSystem;

    protected override void OnCreate()
    {
        m_EntityCommandBufferSystem = World.GetOrCreateSystem<BeginInitializationEntityCommandBufferSystem>();
    }

    struct SpawnMeteorJob : IJobForEachWithEntity<SpawnMeteor, Translation, Rotation>
    {
        public EntityCommandBuffer CommandBuffer;
        public float3 MouseRaycastPosition;

        //public float fallSpeed;
        //[ReadOnly] public float deltaTime;

        public void Execute(Entity entity, int index, ref SpawnMeteor spawner, ref Translation position, ref Rotation rotation)
        {
            Debug.Log("Spawning Meteor");

            var instance = CommandBuffer.Instantiate(spawner.Prefab);

            CommandBuffer.SetComponent(instance, new Translation { Value = new float3(MouseRaycastPosition.x, MouseRaycastPosition.y + 250, MouseRaycastPosition.z) });
            CommandBuffer.AddComponent(instance, new Target { Destination = float3.zero });
            CommandBuffer.AddComponent(instance, new MovementSpeed { Value = 100 });
            CommandBuffer.AddComponent(instance, new Meteor { Damage = 50, Radius = 150.0f });
        }
    };

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var spellType = GetSingleton<SingletonKeyboardInput>();
        var mouse = GetSingleton<SingletonMouseInput>();

        var jobHandle = inputDeps;

        //If Q pressed then Meteor Strike mouse position
        if (spellType.Q_key)
        {
            /*
             * Requires a mouse position
             */

            Debug.Log("Meteor Strike");

            var spawnMeteorJob = new SpawnMeteorJob
            {
                CommandBuffer = m_EntityCommandBufferSystem.CreateCommandBuffer(),
                MouseRaycastPosition = mouse.CurrentMouseRaycastPosition,
                //deltaTime = Time.deltaTime,
                //fallSpeed = 20.0f,
            }.ScheduleSingle(this, inputDeps);

            m_EntityCommandBufferSystem.AddJobHandleForProducer(spawnMeteorJob);

            return spawnMeteorJob;
        }

        return jobHandle;
    }
}