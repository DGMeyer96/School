using Unity.Jobs;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using Unity.Collections;
using UnityEngine;

[UpdateAfter(typeof(KeyActivationSystem))]
public class HealProxy : JobComponentSystem
{
    [RequireComponentTag(typeof(TagSelected))]
    struct HealJob : IJobForEachWithEntity<Health>
    {
        public void Execute(Entity entity, int index, ref Health health)
        {
            health.Value += 25;
            Debug.Log("Life: " + health.Value);
        }
    };

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var spellType = GetSingleton<SingletonKeyboardInput>();
        var mouse = GetSingleton<SingletonMouseInput>();

        var jobHandle = inputDeps;

        //If W pressed then Heal Selected
        if (spellType.W_key)
        {
            /*
             * Requires a TagSelected
             */
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

        return jobHandle;
    }
}
