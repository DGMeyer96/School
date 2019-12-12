using Unity.Jobs;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using Unity.Collections;
using UnityEngine;

/*
[UpdateAfter(typeof(KeyActivationSystem))]
public class SpellSystem : JobComponentSystem
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

        public float fallSpeed;
        [ReadOnly] public float deltaTime;

        public void Execute(Entity entity, int index, ref SpawnMeteor spawner, ref Translation position, ref Rotation rotation)
        {
            Debug.Log("Spawning Meteor");

            var instance = CommandBuffer.Instantiate(spawner.Prefab);

            CommandBuffer.SetComponent(instance, new Translation { Value = new float3(MouseRaycastPosition.x, MouseRaycastPosition.y + 250, MouseRaycastPosition.z) });
            CommandBuffer.AddComponent(instance, new Meteor { Damage = 50, Radius = 150.0f });
        }
    };
    
    struct MeteorStrikeJob : IJobForEachWithEntity<SpawnMeteor, Translation, Rotation>
    {
        public float3 MouseRaycastPosition;
        public float spinSpeed;
        public float fallSpeed;
        [ReadOnly] public float deltaTime;

        public void Execute(Entity entity, int index, ref SpawnMeteor spawner, ref Translation position, ref Rotation rotation)
        {
            Debug.Log("Meteor Falling");

            //position.Value += fallSpeed * deltaTime;
            //rotation.Value = quaternion.LookRotation(spinSpeed * position.Value, math.up());

            var direction = math.normalize(MouseRaycastPosition - position.Value);

            //If the meteor hasn't hit the ground
            if (math.distance(position.Value.y, MouseRaycastPosition.y) >= 0)
            {
                //Fall and rotate while falling
                position.Value += direction * fallSpeed * deltaTime;
                rotation.Value = Quaternion.AngleAxis(math.sin(deltaTime), Vector3.up);
            }
            
        }
    };

    [RequireComponentTag(typeof(TagSelected))]
    struct HealJob : IJobForEachWithEntity<Health>
    {
        public void Execute(Entity entity, int index, ref Health health)
        {
            health.Value += 25;
            Debug.Log("Life: " + health.Value);
        }
    };

    [RequireComponentTag(typeof(TagSelected))]
    struct TeleportJob : IJobForEachWithEntity<Translation>
    {
        [ReadOnly] public NativeArray<Translation> unitPositions;
        [ReadOnly] public float3 MouseRaycastPosition;

        public void Execute(Entity entity, int index, ref Translation position)
        {
            var centerOffset = CalculateOffset(unitPositions);
            if(centerOffset.Equals(float3.zero))
            {
                position.Value = MouseRaycastPosition;
            }
            else
            {
                position.Value = MouseRaycastPosition + (position.Value - centerOffset); 
            }

            //position.Value += initialMouseRaycastPosition - (position.Value + CalculateOffset(unitPositions));
        }

        public float3 CalculateOffset(NativeArray<Translation> unitPos)
        {
            var offset = float3.zero;

            if (unitPos.Length > 1)
            {
                for (int i = 0; i < unitPos.Length; i++)
                {
                    offset += unitPos[i].Value;
                }
                offset /= unitPos.Length;
            }

            return offset;
        }
    };

    [RequireComponentTag(typeof(TagSelected))]
    struct EmbiggenJob : IJobForEachWithEntity<Target, Selectable, NonUniformScale, MovementSpeed>
    {
        public void Execute(Entity entity, int index, ref Target target, ref Selectable selectable, ref NonUniformScale size, ref MovementSpeed movementSpeed)
        {
            size.Value *= 2.0f;
            movementSpeed.Value *= 2.0f;
            Debug.Log("Getting BIGGER!");
        }
    };

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var spellType = GetSingleton<SingletonKeyboardInput>();
        var mouse = GetSingleton<SingletonMouseInput>();

        var jobHandle = inputDeps;

        //If Q pressed then Meteor Strike mouse position
        if(spellType.Q_key)
        {
            Debug.Log("Meteor Strike");

            var spawnMeteorJob = new SpawnMeteorJob
            {
                CommandBuffer = m_EntityCommandBufferSystem.CreateCommandBuffer(),
                MouseRaycastPosition = mouse.CurrentMouseRaycastPosition,
                deltaTime = Time.deltaTime,
                fallSpeed = 20.0f,
            }.ScheduleSingle(this, inputDeps);

            m_EntityCommandBufferSystem.AddJobHandleForProducer(spawnMeteorJob);

            var meteorJob = new MeteorStrikeJob
            {
                deltaTime = Time.deltaTime,
                fallSpeed = 20.0f,
                spinSpeed = 10.0f
            };

            jobHandle = meteorJob.Schedule(this, inputDeps);

            jobHandle.Complete();
            
            return spawnMeteorJob;
        }
        //If W pressed then Heal Selected
        else if(spellType.W_key)
        {
            Debug.Log("Heal");

            EntityQuery m_SelectedUnitHealth = GetEntityQuery(typeof(Health), ComponentType.ReadOnly<TagSelected>());

            NativeArray<Health> m_HealSelected = m_SelectedUnitHealth.ToComponentDataArray<Health>(Allocator.Persistent);

            var healJob = new HealJob
            {
                
            };
            
            jobHandle = healJob.ScheduleSingle(this, inputDeps);
            jobHandle.Complete();

            m_HealSelected.Dispose();
        }
        //If E pressed then Teleport Selected to mouse position
        else if(spellType.E_key)
        {
            Debug.Log("Teleport");

            EntityQuery m_SelectedUnitPosition = GetEntityQuery(typeof(Translation), ComponentType.ReadOnly<TagSelected>());

            NativeArray<Translation> m_TeleportSelected = m_SelectedUnitPosition.ToComponentDataArray<Translation>(Allocator.Persistent);

            var teleportJob = new TeleportJob
            {
                unitPositions = m_TeleportSelected,
                MouseRaycastPosition = mouse.CurrentMouseRaycastPosition
            };

            jobHandle = teleportJob.ScheduleSingle(this, inputDeps);
            jobHandle.Complete();

            m_TeleportSelected.Dispose();
        }
        //If R pressed then Embiggen Selected
        else if(spellType.R_key)
        {
            Debug.Log("Embiggen");

            EntityQuery m_SelectedUnitScale = GetEntityQuery(typeof(NonUniformScale), ComponentType.ReadOnly<TagSelected>());

            NativeArray<NonUniformScale> m_EmbiggenSelected = m_SelectedUnitScale.ToComponentDataArray<NonUniformScale>(Allocator.Persistent);

            var embiggenJob = new EmbiggenJob
            {

            };

            jobHandle = embiggenJob.ScheduleSingle(this, inputDeps);
            jobHandle.Complete();

            m_EmbiggenSelected.Dispose();
        }

        return jobHandle;
    }
}
*/