// Starting the update of a particle system state (unit around 0x1073F400 - 0x10740000; the file name is a guess, the
// unit also holds the particle renderer). Names are guesses.
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/engine/display.h"
#include "code/pure3d/context.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/view.h"

namespace pure3d
{
	// 0x111372B8, 0x1127EDE8 (data of the particle module with unknown meanings)
	extern float gParticleUnknown111372B8;
	extern int gParticleUnknown1127EDE8;

	// FUNCTION: ENGINE 0x1073FD30
	// EQUIVALENT: the camera position is copied through x87 for its first component (554 bytes against 558); the rest
	// is identical
	void ParticleSystemState::BeginUpdate(float x, float y, float z, bool flag)
	{
		if (generator)
		{
			if (dynamic_cast<ParticlePointGenerator*>(generator))
			{
				generatorType = 1;
			}
			else if (dynamic_cast<ParticlePlaneGenerator*>(generator))
			{
				generatorType = 2;
			}
			else if (dynamic_cast<ParticleSphereGenerator*>(generator))
			{
				generatorType = 3;
			}
			else if (dynamic_cast<ParticleGridGenerator*>(generator))
			{
				generatorType = 4;
			}
			else
			{
				generatorType = dynamic_cast<ParticleMeshGenerator*>(generator) ? 5 : 0;
			}
		}
		unknown8C = x;
		unknown90 = y;
		unknown94 = z;
		unknown98 = flag;
		unknown99 = GetParticleManager()->HasUnknown1A0();
		unknownA0 = GetParticleManager()->GetUnknown1B0();
		unknownA8 = GetParticleManager()->unknown1A0;
		unknownAC = (unsigned int)gParticleUnknown111372B8;
		unknownB0 = gParticleUnknown1127EDE8;
		unknownB4 = engine::gDisplay->GetWidth();
		unknownB8 = engine::gDisplay->GetUnknown8();
		if (context)
		{
			const math::Matrix& camera = context->GetView()->camera->transform;
			unknownBC.Set(camera.m[3][0], camera.m[3][1], camera.m[3][2]);
		}
		heap = core::GetCurrentHeap();
		core::EventReset(event, 1);
		job.Submit(1);
	}
}
