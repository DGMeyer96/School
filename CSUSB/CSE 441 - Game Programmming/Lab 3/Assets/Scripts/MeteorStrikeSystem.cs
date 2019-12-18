using Unity.Jobs;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using Unity.Collections;
using UnityEngine;

[UpdateAfter(typeof(SpawnMeteorSystem))]
public class MeteorStrikeSystem : JobComponentSystem
{
    struct MeteorStrikeJob : IJobForEachWithEntity<Meteor, Translation, Rotation, MovementSpeed, Target>
    {
        public float3 MouseRaycastPosition;
        //public float spinSpeed;
        //public float fallSpeed;
        [ReadOnly] public float deltaTime;

        public void Execute(Entity entity, int index, ref Meteor meteor, ref Translation position, ref Rotation rotation, [ReadOnly] ref MovementSpeed movementSpeed, [ReadOnly] ref Target target)
        {
            Debug.Log("Meteor Falling");

            //position.Value += fallSpeed * deltaTime;
            //rotation.Value = quaternion.LookRotation(spinSpeed * position.Value, math.up());

            var direction = math.normalize(MouseRaycastPosition - position.Value);
            //var direction = math.normalize(target.Destination - position.Value);
            //var distance = math.distance(target.Destination, position.Value);
            var distance = math.distance(MouseRaycastPosition, position.Value);

            //If the meteor hasn't hit the ground
            //if (math.distance(position.Value.y, MouseRaycastPosition.y) >= 0)
            if (distance > 30)
            {
                //Fall and rotate while falling
                //position.Value += direction * fallSpeed * deltaTime;
                position.Value += direction * movementSpeed.Value * deltaTime;
                //rotation.Value = Quaternion.AngleAxis(math.sin(deltaTime), Vector3.up);
                rotation.Value = math.mul(math.normalize(rotation.Value), quaternion.AxisAngle(math.up(), (movementSpeed.Value / 20) * deltaTime));
            }

        }
    };

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var spellType = GetSingleton<SingletonKeyboardInput>();
        var mouse = GetSingleton<SingletonMouseInput>();

        var jobHandle = inputDeps;

        Debug.Log("Meteor Strike");

        var meteorJob = new MeteorStrikeJob
        {
            deltaTime = Time.deltaTime,
            //fallSpeed = 20.0f,
            //spinSpeed = 10.0f
        };

        jobHandle = meteorJob.Schedule(this, inputDeps);
        return jobHandle;
        /*
        if (spellType.Q_key)
        {
            //EntityQuery m_SpawnedMeteor = GetEntityQuery(typeof(SpawnMeteor));

            //NativeArray<SpawnMeteor> m_MeteorStrike = m_SpawnedMeteor.ToComponentDataArray<SpawnMeteor>(Allocator.Persistent);

            var meteorJob = new MeteorStrikeJob
            {
                deltaTime = Time.deltaTime,
                //fallSpeed = 20.0f,
                //spinSpeed = 10.0f
            };

            jobHandle = meteorJob.Schedule(this, inputDeps);
            //m_MeteorStrike.Dispose();

            jobHandle.Complete();

        }
        
        return jobHandle;
        */
    }
}
