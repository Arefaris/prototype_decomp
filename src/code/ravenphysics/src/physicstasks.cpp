// The asynchronous tasks of the physics library: registered at start-up under their names, the ids the task system
// hands back kept in globals (0x1127EB70 on) and given back at shut-down. Names of functions and globals are guesses.
#include "code/core/asynctask.h"

namespace ravenphysics
{
	// The task ids
	int gRigidBodyBrokeringTaskId;     // 0x1127EB70
	int gDetectRestTaskId;             // 0x1127EB74
	int gRestDetectorTaskId;           // 0x1127EB78
	int gSimulatorKernelTaskId;        // 0x1127EB7C
	int gContactCacheReadTaskId;       // 0x1127EB90
	int gExternalConstraintTaskId;     // 0x1127EB94
	int gInternalConstraintTaskId;     // 0x1127EB98
	int gCollisionCheckTaskId;         // 0x1127EB9C
	int gBroadPhaseTaskId;             // 0x1127EBA0

	// What the task functions hand on (other units)
	void Unknown106906B0();
	void Unknown10690730();
	void RegisterMidPhaseTask();
	void UnregisterMidPhaseTask();
	void Unknown106ACA20(void* a, void* b, void* c, void* d, void* e, void* f);
	void Unknown106AC980(void* a, void* b, void* c, void* d);
	void Unknown106AD1A0(void* a, void* b, void* c, void* d, void* e, void* f);
	void Unknown106ACEE0(void* a, void* b, void* c, void* d);
	void BroadPhaseTask(void* data);
	void Unknown106ADF20(void* data);
	void Unknown106AD8B0(void* data);
	void Unknown106AE000(void* data);
	void SimulatorKernelTask(void* data);
	void RigidBodyBrokeringTask(void* data);

	// The words the rest detector's task starts from
	struct RestDetectorData
	{
		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
	};

	// FUNCTION: ENGINE 0x106A6E30
	void RestDetectorTask(RestDetectorData* data)
	{
		Unknown106ACA20(data->unknown0, data->unknown4, data->unknown8, data->unknownC, data->unknown10,
			data->unknown14);
	}

	// What the rigid body rest detection works over
	struct DetectRestData
	{
		unsigned char unknown0[0xC];
		unsigned char unknownC[8];
		unsigned char unknown14[0x6C];
		unsigned char unknown80[4];
	};

	// FUNCTION: ENGINE 0x106A6E60
	void DetectRestTask(DetectRestData* data)
	{
		Unknown106AC980(data, data->unknown14, data->unknownC, data->unknown80);
	}

	// FUNCTION: ENGINE 0x106B58A0
	void RegisterBroadPhaseTask()
	{
		core::RegisterAsyncTaskFunction("RavenBroadPhase", (void (*)(void*, core::AsyncTaskCallback*))BroadPhaseTask,
			&gBroadPhaseTaskId);
	}

	// FUNCTION: ENGINE 0x106B58C0
	void UnregisterBroadPhaseTask()
	{
		core::UnregisterAsyncTaskFunction(gBroadPhaseTaskId);
	}

	// FUNCTION: ENGINE 0x106A6E10
	void Unknown106A6E10()
	{
		Unknown106906B0();
		RegisterMidPhaseTask();
		RegisterBroadPhaseTask();
	}

	// FUNCTION: ENGINE 0x106A6E20
	void Unknown106A6E20()
	{
		UnregisterBroadPhaseTask();
		UnregisterMidPhaseTask();
		Unknown10690730();
	}

	// What the contact cache read works over
	struct ContactCacheData
	{
		unsigned char unknown0[8];
		unsigned char unknown8[0xC];
		unsigned char unknown14[8];
		void* unknown1C;
		void* unknown20;
		unsigned char unknown24[8];
		unsigned char unknown2C[4];
	};

	// FUNCTION: ENGINE 0x106AD200
	void ContactCacheReadTask(ContactCacheData* data)
	{
		Unknown106AD1A0(data->unknown8, data->unknown14, data->unknown1C, data->unknown20, data->unknown24,
			data->unknown2C);
		Unknown106ACEE0(data->unknown8, data->unknown1C, data->unknown20, data->unknown24);
	}

	// FUNCTION: ENGINE 0x106AD240
	void RegisterContactCacheReadTask()
	{
		core::RegisterAsyncTaskFunction("RavenSimulationContactCacheRead",
			(void (*)(void*, core::AsyncTaskCallback*))ContactCacheReadTask, &gContactCacheReadTaskId);
	}

	// FUNCTION: ENGINE 0x106ACBE0
	void UnregisterContactCacheReadTask()
	{
		core::UnregisterAsyncTaskFunction(gContactCacheReadTaskId);
	}

	// FUNCTION: ENGINE 0x106AE130
	void RegisterConstraintCheckTasks()
	{
		core::RegisterAsyncTaskFunction("External Constraint Check",
			(void (*)(void*, core::AsyncTaskCallback*))Unknown106ADF20, &gExternalConstraintTaskId);
		core::RegisterAsyncTaskFunction("Internal Constraint Check",
			(void (*)(void*, core::AsyncTaskCallback*))Unknown106AD8B0, &gInternalConstraintTaskId);
		core::RegisterAsyncTaskFunction("Collision Check",
			(void (*)(void*, core::AsyncTaskCallback*))Unknown106AE000, &gCollisionCheckTaskId);
	}

	// FUNCTION: ENGINE 0x106AD2E0
	void UnregisterConstraintCheckTasks()
	{
		core::UnregisterAsyncTaskFunction(gExternalConstraintTaskId);
		core::UnregisterAsyncTaskFunction(gInternalConstraintTaskId);
		core::UnregisterAsyncTaskFunction(gCollisionCheckTaskId);
	}

	// FUNCTION: ENGINE 0x106A7010
	void Unknown106A7010()
	{
		core::RegisterAsyncTaskFunction("ravenphysicsRestDetector", (void (*)(void*, core::AsyncTaskCallback*))RestDetectorTask,
			&gRestDetectorTaskId);
		core::RegisterAsyncTaskFunction("ravenphysicsDetectRigidBodiesAtRest",
			(void (*)(void*, core::AsyncTaskCallback*))DetectRestTask, &gDetectRestTaskId);
		core::RegisterAsyncTaskFunction("ravenphysicsRigidBodyBrokering",
			(void (*)(void*, core::AsyncTaskCallback*))RigidBodyBrokeringTask, &gRigidBodyBrokeringTaskId);
		core::RegisterAsyncTaskFunction("ravenphysicsSimulatorKernel",
			(void (*)(void*, core::AsyncTaskCallback*))SimulatorKernelTask, &gSimulatorKernelTaskId);
		RegisterContactCacheReadTask();
		RegisterConstraintCheckTasks();
	}

	// FUNCTION: ENGINE 0x106A6E80
	void Unknown106A6E80()
	{
		UnregisterConstraintCheckTasks();
		UnregisterContactCacheReadTask();
		core::UnregisterAsyncTaskFunction(gRestDetectorTaskId);
		core::UnregisterAsyncTaskFunction(gDetectRestTaskId);
		core::UnregisterAsyncTaskFunction(gRigidBodyBrokeringTaskId);
		core::UnregisterAsyncTaskFunction(gSimulatorKernelTaskId);
	}
}
