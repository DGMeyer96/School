using Unity.Jobs;
using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using Unity.Collections;
using UnityEngine;

[UpdateAfter(typeof(KeyActivationSystem))]
public class TeleportSystem : JobComponentSystem
{
    [RequireComponentTag(typeof(TagSelected))]
    struct TeleportJob : IJobForEachWithEntity<Translation>
    {
        [ReadOnly] public NativeArray<Translation> unitPositions;
        [ReadOnly] public float3 MouseRaycastPosition;

        public void Execute(Entity entity, int index, ref Translation position)
        {
            /*
            //UnitPosition += MousePosition - CurrentUnitPosition
            if (unitPositions.Length > 1)
            {
                for (int i = 0; i < unitPositions.Length; i++)
                {
                    unitPositions[i].Value += initialMouseRaycastPosition - unitPositions[i].Value;
                }
                //offset /= unitPositions.Length;
            }
            */
            var centerOffset = CalculateOffset(unitPositions);
            if (centerOffset.Equals(float3.zero))
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

    protected override JobHandle OnUpdate(JobHandle inputDeps)
    {
        var spellType = GetSingleton<SingletonKeyboardInput>();
        var mouse = GetSingleton<SingletonMouseInput>();

        var jobHandle = inputDeps;

        //If E pressed then Teleport Selected to mouse position
        if (spellType.E_key)
        {
            /*
             * Requires a TagSelected
             * Requires a mouse position
             */

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

        return jobHandle;
    }
}
