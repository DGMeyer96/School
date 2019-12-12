using Unity.Jobs;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using Unity.Collections;
using UnityEngine;

[UpdateAfter(typeof(KeyActivationSystem))]
public class EmbiggenSystem : JobComponentSystem
{
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

        //If R pressed then Embiggen Selected
        if (spellType.R_key)
        {
            /*
             * Requires a TagSelected
             */

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
