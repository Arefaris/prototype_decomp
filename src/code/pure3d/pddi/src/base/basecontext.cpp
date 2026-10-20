// pure3d::pddiBaseContext, the base of the render device (unit 0x10614640 - 0x10616xxx; file pddi/src/base/
// basecontext.cpp): the state accessors over the four state stacks, the clocks and the frame counter. Names of
// the states' words are guesses.
#include "code/core/debug.h"
#include "code/core/time.h"
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10614AB0
	unsigned __int64 pddiBaseContext::GetTimeUnknown600()
	{
		return timeUnknown600.value;
	}

	// FUNCTION: ENGINE 0x10614AC0
	void pddiBaseContext::SetTimeUnknown600(unsigned __int64 time)
	{
		timeUnknown600.value = time;
	}

	// FUNCTION: ENGINE 0x10614AE0
	void pddiBaseContext::ReadTimeUnknown608()
	{
		timeUnknown608.value = core::GetElapsedMicroseconds();
	}

	// FUNCTION: ENGINE 0x10614B00
	void pddiBaseContext::ReadTimeUnknown610()
	{
		timeUnknown610.value = core::GetElapsedMicroseconds();
		timeUnknown620.value = timeUnknown610.value - timeUnknown608.value - GetTimeUnknown600();
	}

	// FUNCTION: ENGINE 0x10614B50
	void pddiBaseContext::SetTimeUnknown618(unsigned __int64 time)
	{
		timeUnknown618.value = time;
	}

	// FUNCTION: ENGINE 0x10614B70
	unsigned __int64 pddiBaseContext::GetTimeUnknown618()
	{
		return timeUnknown618.value;
	}

	// FUNCTION: ENGINE 0x10614B80
	unsigned __int64 pddiBaseContext::GetTimeUnknown620()
	{
		return timeUnknown620.value;
	}

	// FUNCTION: ENGINE 0x10614B90
	// EQUIVALENT: the unsigned frame number is loaded into a register before it is converted, 74.3%
	void pddiBaseContext::Unknown27()
	{
		OLD_ASSERT_AT("..\\..\\..\\code\\pure3d\\pddi\\src\\base\\basecontext.cpp", 0x179, initialized, "mInitialized",
			"pddiBaseContext: Not initialized.  Call Init().");
		frameNumber += 1;
		frameActive = 1;
		clocks[0] = (float)frameNumber;
	}

	// FUNCTION: ENGINE 0x10614C00
	void pddiBaseContext::Unknown28()
	{
		frameActive = 0;
	}

	// FUNCTION: ENGINE 0x10614C10
	void pddiBaseContext::Unknown26()
	{
	}

	// FUNCTION: ENGINE 0x10614C20
	bool pddiBaseContext::IsUnknown14Set()
	{
		return frameActive > 0;
	}

	// FUNCTION: ENGINE 0x10614C30
	void pddiBaseContext::SetViewUnknown4(int value)
	{
		viewState->unknown4 = value;
	}

	// FUNCTION: ENGINE 0x10614C40
	// EQUIVALENT: the output pointer sits in edx, 86.7%
	void pddiBaseContext::GetViewUnknown4(int* value)
	{
		pddiViewState* state = viewState;
		int current = state->unknown4;
		*value = current;
	}

	// FUNCTION: ENGINE 0x10614C50
	void pddiBaseContext::SetViewUnknown8(float value)
	{
		viewState->unknown8 = value;
	}

	// FUNCTION: ENGINE 0x10614C70
	float pddiBaseContext::GetViewUnknown8()
	{
		return viewState->unknown8;
	}

	// FUNCTION: ENGINE 0x10614C80
	void pddiBaseContext::SetViewUnknownC(int value)
	{
		viewState->unknownC = value;
	}

	// FUNCTION: ENGINE 0x10614C90
	int pddiBaseContext::GetViewUnknownC()
	{
		return viewState->unknownC;
	}

	// FUNCTION: ENGINE 0x10614CA0
	void pddiBaseContext::SetViewUnknown10(int value)
	{
		viewState->unknown10 = value;
		Unknown67();
	}

	// FUNCTION: ENGINE 0x10614CC0
	int pddiBaseContext::GetViewUnknown10()
	{
		return viewState->unknown10;
	}

	// FUNCTION: ENGINE 0x10614D10
	void pddiBaseContext::GetViewUnknown14(float* a, float* b, float* c, float* d)
	{
		pddiViewState* state = viewState;
		*a = state->unknown14[0];
		*b = state->unknown14[1];
		*c = state->unknown14[2];
		*d = state->unknown14[3];
	}

	// FUNCTION: ENGINE 0x10614D40
	void pddiBaseContext::GetViewUnknown24(float* a, float* b, float* c, float* d)
	{
		pddiViewState* state = viewState;
		*a = state->unknown24[0];
		*b = state->unknown24[1];
		*c = state->unknown24[2];
		*d = state->unknown24[3];
	}

	// FUNCTION: ENGINE 0x10614D70
	void pddiBaseContext::GetViewUnknown34(float* a, float* b)
	{
		pddiViewState* state = viewState;
		*a = state->unknown24[4];
		*b = state->unknown24[5];
	}

	// FUNCTION: ENGINE 0x10614D90
	void pddiBaseContext::SetCullMode(int mode)
	{
		renderState->cullMode = mode;
	}

	// FUNCTION: ENGINE 0x10614DA0
	int pddiBaseContext::GetCullMode()
	{
		return renderState->cullMode;
	}

	// FUNCTION: ENGINE 0x10614DB0
	void pddiBaseContext::SetColourWrite(bool red, bool green, bool blue, bool alpha)
	{
		renderState->colourWrite[0] = red;
		renderState->colourWrite[1] = green;
		renderState->colourWrite[2] = blue;
		renderState->colourWrite[3] = alpha;
	}

	// FUNCTION: ENGINE 0x10614DE0
	void pddiBaseContext::GetColourWrite(bool* red, bool* green, bool* blue, bool* alpha)
	{
		*red = renderState->colourWrite[0];
		*green = renderState->colourWrite[1];
		*blue = renderState->colourWrite[2];
		*alpha = renderState->colourWrite[3];
	}

	// FUNCTION: ENGINE 0x10614E20
	void pddiBaseContext::EnableZBuffer(bool enable)
	{
		zState->zBuffer = enable;
	}

	// FUNCTION: ENGINE 0x10614E30
	bool pddiBaseContext::IsZBufferEnabled()
	{
		return zState->zBuffer;
	}

	// FUNCTION: ENGINE 0x10614E40
	void pddiBaseContext::SetZCompare(int compare)
	{
		zState->zCompare = compare;
	}

	// FUNCTION: ENGINE 0x10614E50
	int pddiBaseContext::GetZCompare()
	{
		return zState->zCompare;
	}

	// FUNCTION: ENGINE 0x10614E60
	void pddiBaseContext::EnableZWrite(bool enable)
	{
		zState->zWrite = enable;
	}

	// FUNCTION: ENGINE 0x10614E70
	bool pddiBaseContext::IsZWriteEnabled()
	{
		return zState->zWrite;
	}

	// FUNCTION: ENGINE 0x10614E80
	void pddiBaseContext::SetZBias(float bias, float slope)
	{
		zState->zBias = bias;
		zState->zSlope = slope;
	}

	// FUNCTION: ENGINE 0x10614EA0
	void pddiBaseContext::GetZBias(float* bias, float* slope)
	{
		pddiZState* state = zState;
		*bias = state->zBias;
		*slope = state->zSlope;
	}

	// FUNCTION: ENGINE 0x10614EC0
	void pddiBaseContext::EnableStencilBuffer(bool enable)
	{
		stencilState->enabled = enable;
	}

	// FUNCTION: ENGINE 0x10614ED0
	bool pddiBaseContext::IsStencilBufferEnabled()
	{
		return stencilState->enabled;
	}

	// FUNCTION: ENGINE 0x10614EE0
	void pddiBaseContext::SetStencilCompare(int compare)
	{
		stencilState->compare = compare;
	}

	// FUNCTION: ENGINE 0x10614EF0
	int pddiBaseContext::GetStencilCompare()
	{
		return stencilState->compare;
	}

	// FUNCTION: ENGINE 0x10614F00
	void pddiBaseContext::SetStencilRef(int ref)
	{
		stencilState->ref = ref;
	}

	// FUNCTION: ENGINE 0x10614F10
	int pddiBaseContext::GetStencilRef()
	{
		return stencilState->ref;
	}

	// FUNCTION: ENGINE 0x10614F20
	void pddiBaseContext::SetStencilMask(int mask)
	{
		stencilState->mask = mask;
	}

	// FUNCTION: ENGINE 0x10614F30
	int pddiBaseContext::GetStencilMask()
	{
		return stencilState->mask;
	}

	// FUNCTION: ENGINE 0x10614F40
	void pddiBaseContext::SetStencilWriteMask(int mask)
	{
		stencilState->writeMask = mask;
	}

	// FUNCTION: ENGINE 0x10614F50
	int pddiBaseContext::GetStencilWriteMask()
	{
		return stencilState->writeMask;
	}

	// FUNCTION: ENGINE 0x10614F60
	void pddiBaseContext::SetStencilOp(int fail, int zFail, int zPass)
	{
		stencilState->fail = fail;
		stencilState->zFail = zFail;
		stencilState->zPass = zPass;
	}

	// FUNCTION: ENGINE 0x10614F90
	void pddiBaseContext::GetStencilOp(int* fail, int* zFail, int* zPass)
	{
		*fail = stencilState->fail;
		*zFail = stencilState->zFail;
		*zPass = stencilState->zPass;
	}

	// FUNCTION: ENGINE 0x10614FC0
	void pddiBaseContext::Unknown51(bool enable)
	{
		stencilState->unknown24 = enable;
	}

	// FUNCTION: ENGINE 0x10614FD0
	void pddiBaseContext::Unknown52(int compare)
	{
		stencilState->unknown28 = compare;
	}

	// FUNCTION: ENGINE 0x10614FE0
	void pddiBaseContext::Unknown53(int fail, int zFail, int zPass)
	{
		stencilState->unknown2C = fail;
		stencilState->unknown30 = zFail;
		stencilState->unknown34 = zPass;
	}

	// FUNCTION: ENGINE 0x10615010
	void pddiBaseContext::SetRenderUnknown38(bool value)
	{
		renderState->unknown38 = value;
	}

	// FUNCTION: ENGINE 0x10615020
	void pddiBaseContext::SetFillMode(int mode)
	{
		renderState->fillMode = mode;
	}

	// FUNCTION: ENGINE 0x10615030
	int pddiBaseContext::GetFillMode()
	{
		return renderState->fillMode;
	}

	// FUNCTION: ENGINE 0x10615040
	void pddiBaseContext::SetRenderUnknownC(int value)
	{
		renderState->unknownC = value;
	}

	// FUNCTION: ENGINE 0x10615050
	int pddiBaseContext::GetRenderUnknownC()
	{
		return renderState->unknownC;
	}

	// FUNCTION: ENGINE 0x10615060
	void pddiBaseContext::EnableAlphaTest(bool enable)
	{
		renderState->alphaTest = enable;
	}

	// FUNCTION: ENGINE 0x10615070
	bool pddiBaseContext::IsAlphaTestEnabled()
	{
		return renderState->alphaTest;
	}

	// FUNCTION: ENGINE 0x10615080
	void pddiBaseContext::SetBlendMode(int source, int destination, int sourceAlpha, int destinationAlpha)
	{
		renderState->blend[0] = source;
		renderState->blend[1] = destination;
		renderState->blend[2] = sourceAlpha;
		renderState->blend[3] = destinationAlpha;
	}

	// FUNCTION: ENGINE 0x106150F0
	void pddiBaseContext::EnableFog(bool enable)
	{
		renderState->fog = enable;
	}

	// FUNCTION: ENGINE 0x10615100
	bool pddiBaseContext::IsFogEnabled()
	{
		return renderState->fog;
	}

	// FUNCTION: ENGINE 0x10615110
	void pddiBaseContext::SetFogRange(float nearZ, float farZ)
	{
		renderState->fogNear = nearZ;
		renderState->fogFar = farZ;
	}

	// FUNCTION: ENGINE 0x10615130
	void pddiBaseContext::GetFogRange(float* nearZ, float* farZ)
	{
		pddiRenderState* state = renderState;
		*nearZ = state->fogNear;
		*farZ = state->fogFar;
	}

	// FUNCTION: ENGINE 0x10615150
	void pddiBaseContext::SetAlphaRef(float ref)
	{
		renderState->alphaRef = ref;
	}

	// FUNCTION: ENGINE 0x10615170
	float pddiBaseContext::GetAlphaRef()
	{
		return renderState->alphaRef;
	}

	// FUNCTION: ENGINE 0x10615180
	int pddiBaseContext::GetFrameCount(int index)
	{
		return (int)clocks[index];
	}

	// FUNCTION: ENGINE 0x10615190
	float pddiBaseContext::GetFrameTimeUnknown(int index)
	{
		return clocks[index];
	}

	// FUNCTION: ENGINE 0x10615DA0
	void pddiBaseContext::Unknown8(int a)
	{
	}

	// FUNCTION: ENGINE 0x10615DB0
	void pddiBaseContext::Unknown9()
	{
	}

	// FUNCTION: ENGINE 0x10615DC0
	IDirect3DQuery9* pddiBaseContext::Unknown10()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10615DD0
	void pddiBaseContext::Unknown11(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615DE0
	bool pddiBaseContext::Unknown12(IDirect3DQuery9* query)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10615DF0
	IDirect3DQuery9* pddiBaseContext::Unknown18()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10615E00
	void pddiBaseContext::Unknown19(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615E10
	void pddiBaseContext::Unknown20(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615E20
	void pddiBaseContext::Unknown21(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615E30
	void pddiBaseContext::Unknown54(int a)
	{
	}

	// FUNCTION: ENGINE 0x10615E40
	void pddiBaseContext::Unknown55(int a)
	{
	}

	// FUNCTION: ENGINE 0x10615E50
	void pddiBaseContext::Unknown56(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10615E60
	void pddiBaseContext::Unknown57(int a)
	{
	}

	// The engine's out-of-line copies of the inline members of ConstantMatrix and ConstantVector3 (pddi.h)
	// FUNCTION: ENGINE 0x10614650 is ConstantMatrix::Multiply
	// FUNCTION: ENGINE 0x10614690 is ConstantMatrix::Assign
	// FUNCTION: ENGINE 0x106146D0 is ShaderMatrices::SetProjection
	// FUNCTION: ENGINE 0x1061DA00 is ConstantMatrix::Bind
	// FUNCTION: ENGINE 0x1061DA20 is ConstantVector3::ConstantVector3
	// FUNCTION: ENGINE 0x1061DA60 is ConstantVector3::Assign
	// EQUIVALENT: 71 %, the same stores; the copy's address is formed after the first store (scheduling) since the
	// merge of the pddi.h declarations
	// FUNCTION: ENGINE 0x1061DE20 is ConstantMatrix::ConstantMatrix

	// FUNCTION: ENGINE 0x1061DAA0
	void ShaderMatrices::MakeViewProjection()
	{
		viewProjection.Multiply(view, projection);
		dirty &= ~0x1;
	}

	// FUNCTION: ENGINE 0x10614760
	void ShaderMatrices::MakeWorldViewProjection()
	{
		worldViewProjection.Multiply(worldView, projection);
		dirty &= ~0x2;
	}

	// FUNCTION: ENGINE 0x1061DE40
	void ShaderMatrices::MakeProjectionInverse()
	{
		math::Matrix inverse = projection;
		inverse.Invert();
		projectionInverse.Assign(inverse);
		dirty &= ~0x10;
	}

	// FUNCTION: ENGINE 0x1061DF70
	void ShaderMatrices::MakeWorldViewInverse()
	{
		math::Matrix inverse;
		inverse = worldView;
		inverse.Invert();
		worldViewInverse.Assign(inverse);
		dirty &= ~0x20;
	}

	// FUNCTION: ENGINE 0x1061DFD0
	// EQUIVALENT: the engine writes the product's copy with the loads of the device's constants after the flag update, this compiler before it (one instruction apart), 87.1 %
	void ShaderMatrices::MakeWorldViewProjectionInverse()
	{
		math::Matrix inverse;
		inverse.Multiply(worldView, projection);
		inverse.Invert();
		worldViewProjectionInverse.Assign(inverse);
		dirty &= ~0x80;
	}

	// FUNCTION: ENGINE 0x1061E040
	void ShaderMatrices::MakeProjectionTranspose()
	{
		math::Matrix transpose = projection;
		transpose.Transpose();
		projectionTranspose.Assign(transpose);
		dirty &= ~0x400;
	}

	// FUNCTION: ENGINE 0x1061E170
	void ShaderMatrices::MakeWorldViewTranspose()
	{
		math::Matrix transpose = worldView;
		transpose.Transpose();
		worldViewTranspose.Assign(transpose);
		dirty &= ~0x800;
	}

	// FUNCTION: ENGINE 0x1061E2A0
	// EQUIVALENT: as the inverse of the product: the loads of the device's constants are scheduled one instruction earlier, 87.1 %
	void ShaderMatrices::MakeWorldViewProjectionTranspose()
	{
		math::Matrix transpose;
		transpose.Multiply(worldView, projection);
		transpose.Transpose();
		worldViewProjectionTranspose.Assign(transpose);
		dirty &= ~0x2000;
	}

	// FUNCTION: ENGINE 0x1061E310
	void ShaderMatrices::MakeWorldInverseTranspose()
	{
		math::Matrix result;
		result = world;
		result.Invert();
		result.Transpose();
		worldInverseTranspose.Assign(result);
		dirty &= ~0x4000;
	}

	// FUNCTION: ENGINE 0x1061E380
	void ShaderMatrices::MakeProjectionInverseTranspose()
	{
		math::Matrix result;
		result = projection;
		result.Invert();
		result.Transpose();
		projectionInverseTranspose.Assign(result);
		dirty &= ~0x10000;
	}

	// FUNCTION: ENGINE 0x1061E3F0
	void ShaderMatrices::MakeWorldViewInverseTranspose()
	{
		math::Matrix result;
		result = worldView;
		result.Invert();
		result.Transpose();
		worldViewInverseTranspose.Assign(result);
		dirty &= ~0x20000;
	}

	// FUNCTION: ENGINE 0x1061E460
	void ShaderMatrices::MakeWorldViewProjectionInverseTranspose()
	{
		math::Matrix product = worldView;
		product.Multiply(worldView, projection);
		product.Invert();
		math::Matrix result;
		result.Transpose(product);
		worldViewProjectionInverseTranspose.Assign(result);
		dirty &= ~0x80000;
	}

	// FUNCTION: ENGINE 0x1061E590
	// EQUIVALENT: the load of the second component of the vector is scheduled before the address of the copy, 93.9 %
	void ShaderMatrices::MakeEyePosition()
	{
		math::Matrix inverse;
		inverse = worldView;
		inverse.Orthonormalize();
		inverse.InvertOrthonormal();
		eyePosition.Assign(&inverse.m[3][0]);
		dirty &= ~0x100000;
	}

	// FUNCTION: ENGINE 0x1061E810
	// EQUIVALENT: register allocation (the engine keeps this in edi and the pending bits in esi, this compiler esi and ebx), 33.0 %
	void ShaderMatrices::Update(unsigned int mask)
	{
		if (dirty != 0)
		{
			unsigned int pending = mask & dirty;
			if ((pending & 0x1) != 0)
			{
				MakeViewProjection();
			}
			if ((pending & 0x2) != 0)
			{
				MakeWorldViewProjection();
			}
			if ((pending & 0x10) != 0)
			{
				MakeProjectionInverse();
			}
			if ((pending & 0x20) != 0)
			{
				MakeWorldViewInverse();
			}
			if ((pending & 0x80) != 0)
			{
				MakeWorldViewProjectionInverse();
			}
			if ((pending & 0x400) != 0)
			{
				MakeProjectionTranspose();
			}
			if ((pending & 0x800) != 0)
			{
				MakeWorldViewTranspose();
			}
			if ((pending & 0x2000) != 0)
			{
				MakeWorldViewProjectionTranspose();
			}
			if ((pending & 0x4000) != 0)
			{
				MakeWorldInverseTranspose();
			}
			if ((pending & 0x10000) != 0)
			{
				MakeProjectionInverseTranspose();
			}
			if ((pending & 0x20000) != 0)
			{
				MakeWorldViewInverseTranspose();
			}
			if ((pending & 0x80000) != 0)
			{
				MakeWorldViewProjectionInverseTranspose();
			}
			if ((pending & 0x100000) != 0)
			{
				MakeEyePosition();
			}
		}
	}

	// FUNCTION: ENGINE 0x1061E670
	ShaderMatrices::ShaderMatrices() : dirty(0), context(0)
	{
	}

	// FUNCTION: ENGINE 0x10615270
	void ShaderMatrices::SetView(const math::Matrix* matrix)
	{
		view.Assign(*matrix);
		math::Matrix product;
		product.Multiply(world, view);
		worldView.Assign(product);
		dirty |= 0x1A28A3;
	}

	// FUNCTION: ENGINE 0x10615300
	void ShaderMatrices::SetWorld(const math::Matrix* matrix)
	{
		world.Assign(*matrix);
		math::Matrix product;
		product.Multiply(world, view);
		worldView.Assign(product);
		dirty |= 0x1A68A2;
	}

	// Finds the constant a matrix is kept under (the name is made twice, as the engine's code does)
#define BIND_MATRIX(matrix, text) 	{ 		core::Name<core::CaseInsensitiveKey32> text_(text, 0); 		core::Name<core::CaseInsensitiveKey32> name(text_); 		matrix.Bind(newContext, &name); 	}

	// FUNCTION: ENGINE 0x1061E8F0
	void ShaderMatrices::Bind(pddiBaseContext* newContext)
	{
		context = newContext;
		BIND_MATRIX(world, "p3dWorldMatrix");
		BIND_MATRIX(view, "p3dViewMatrix");
		BIND_MATRIX(projection, "p3dProjectionMatrix");
		BIND_MATRIX(worldView, "p3dWorldViewMatrix");
		BIND_MATRIX(viewProjection, "p3dViewProjectionMatrix");
		BIND_MATRIX(projectionInverse, "p3dProjectionMatrixInverse");
		BIND_MATRIX(worldViewProjection, "p3dWorldViewProjectionMatrix");
		BIND_MATRIX(worldViewInverse, "p3dWorldViewMatrixInverse");
		BIND_MATRIX(worldViewProjectionInverse, "p3dWorldViewProjectionMatrixInverse");
		BIND_MATRIX(projectionTranspose, "p3dProjectionMatrixTranspose");
		BIND_MATRIX(worldViewTranspose, "p3dWorldViewMatrixTranspose");
		BIND_MATRIX(worldViewProjectionTranspose, "p3dWorldViewProjectionMatrixTranspose");
		BIND_MATRIX(worldInverseTranspose, "p3dWorldMatrixInverseTranspose");
		BIND_MATRIX(projectionInverseTranspose, "p3dProjectionMatrixInverseTranspose");
		BIND_MATRIX(worldViewInverseTranspose, "p3dWorldViewMatrixInverseTranspose");
		BIND_MATRIX(worldViewProjectionInverseTranspose, "p3dWorldViewProjectionMatrixInverseTranspose");
		{
			core::Name<core::CaseInsensitiveKey32> text("p3dEyePositionObjectSpace", 0);
			core::Name<core::CaseInsensitiveKey32> name(text);
			eyePosition.context = newContext;
			newContext->constants->Find(&eyePosition.slot, 3, &name);
		}
		SetWorld(&world);
		SetView(&view);
		projection.Assign(projection);
		dirty = 0x1B6CB3;
		Update(0x1B6CB3);
	}

	// FUNCTION: ENGINE 0x106147E0
	void pddiBaseContext::SetProjectionMatrix(const math::Matrix* matrix)
	{
		ConstantMatrix* projection = &matrices.projection;
		if (matrix != projection && !(*matrix == *projection))
		{
			matrices.SetProjection(matrix);
			constantsDirty |= CONSTANT_MATRIX;
		}
	}

	// FUNCTION: ENGINE 0x10614840
	const math::Matrix* pddiBaseContext::GetUnknown10614840()
	{
		return &matrices.view;
	}

	// FUNCTION: ENGINE 0x10614850
	const math::Matrix* pddiBaseContext::GetUnknown10614850()
	{
		return &matrices.world;
	}

	// FUNCTION: ENGINE 0x10614860
	const math::Matrix* pddiBaseContext::GetUnknown10614860()
	{
		return &matrices.worldViewProjection;
	}

	// FUNCTION: ENGINE 0x10614870
	const math::Matrix* pddiBaseContext::GetUnknown10614870()
	{
		return &matrices.projection;
	}

	// FUNCTION: ENGINE 0x10614880
	void pddiBaseContext::UpdateMatrices(unsigned int mask)
	{
		matrices.Update(mask);
	}

	// FUNCTION: ENGINE 0x10614890
	void pddiBaseContext::Unknown10614890()
	{
		matrices.worldViewProjection.Multiply(matrices.worldView, matrices.projection);
		matrices.dirty &= ~0x2;
	}

	// FUNCTION: ENGINE 0x10615390
	void pddiBaseContext::SetViewMatrix(const math::Matrix* matrix)
	{
		ConstantMatrix* view = &matrices.view;
		if (matrix != view && !(*matrix == *view))
		{
			matrices.SetView(matrix);
			constantsDirty |= CONSTANT_MATRIX;
		}
	}

	// FUNCTION: ENGINE 0x10615770
	void pddiBaseContext::SetWorldMatrix(const math::Matrix* matrix)
	{
		ConstantMatrix* world = &matrices.world;
		if (matrix != world && !(*world == *matrix))
		{
			matrices.SetWorld(matrix);
			constantsDirty |= CONSTANT_MATRIX;
		}
	}

	// FUNCTION: ENGINE 0x10614910
	void pddiBaseContext::Unknown10614910()
	{
		float zero = 0.0f;
		drawnPrimitives = zero;
		drawnVertices = zero;
		drawnIndexedPrimitives = zero;
		drawnIndexedVertices = zero;
		drawCalls = zero;
		primitivesPerDraw = zero;
		unknown84 = zero;
		batchedPrimitives = zero;
		batchDraws = zero;
		unknown90 = zero;
		unknown94[0] = zero;
		unknown94[1] = zero;
		unknown94[2] = zero;
		unknown94[3] = zero;
		unknown94[4] = zero;
		unknown94[5] = zero;
		unknown94[6] = zero;
		unknown94[7] = zero;
		unknown94[8] = zero;
		unknown94[9] = zero;
		unknownFC[0] = zero;
		unknownFC[1] = zero;
		unknownFC[2] = zero;
		unknown110[0] = zero;
		unknown110[1] = zero;
		unknown110[2] = zero;
		unknown110[3] = zero;
		unknown110[4] = zero;
		unknown110[5] = zero;
		unknown110[6] = zero;
		unknown110[7] = zero;
		unknown110[8] = zero;
		unknown110[9] = zero;
	}

	// FUNCTION: ENGINE 0x10614A10
	// EQUIVALENT: xmm register allocation of the two divisions and the store of the first average is scheduled after the second test, 67.6 %
	void pddiBaseContext::Unknown10614A10()
	{
		float draws = drawCalls;
		float average = draws > 0.0f ? (drawnIndexedPrimitives + drawnPrimitives) / draws : 0.0f;
		primitivesPerDraw = average;
		float batches = batchDraws;
		if (batches > 0.0f)
		{
			unknown90 = unknown84 / batches;
		}
		else
		{
			unknown90 = 0.0f;
		}
	}

	// FUNCTION: ENGINE 0x106148E0
	void pddiBaseContext::ApplyStates()
	{
		viewState->Apply(this);
		renderState->Apply(this);
		zState->Apply(this);
		stencilState->Apply(this);
	}

	// FUNCTION: ENGINE 0x106156F0
	pddiRenderState::pddiRenderState()
	{
	}

	// FUNCTION: ENGINE 0x10615700
	pddiZState::pddiZState()
	{
	}

	// FUNCTION: ENGINE 0x10615710
	pddiStencilState::pddiStencilState()
	{
	}

	// FUNCTION: ENGINE 0x1061DBA0
	void pddiRenderState::Apply(pddiBaseContext* context)
	{
		context->SetCullMode(cullMode);
		context->SetColourWrite(colourWrite[0], colourWrite[1], colourWrite[2], colourWrite[3]);
		context->SetFillMode(fillMode);
		context->EnableAlphaTest(alphaTest);
		context->SetBlendMode(blend[0], blend[1], blend[2], blend[3]);
		context->EnableFog(fog);
		context->SetFogRange(fogNear, fogFar);
		context->SetAlphaRef(alphaRef);
		context->SetRenderUnknown38(unknown38);
	}

	// FUNCTION: ENGINE 0x1061DC70
	void pddiViewState::Apply(pddiBaseContext* context)
	{
		context->SetViewUnknown4(unknown4);
		context->SetViewUnknown8(unknown8);
		context->SetViewUnknownC(unknownC);
		context->SetViewUnknown10(unknown10);
		context->SetViewUnknown14(unknown14[0], unknown14[1], unknown14[2], unknown14[3]);
		context->SetViewUnknown24(unknown24[0], unknown24[1], unknown24[2], unknown24[3], unknown24[4], unknown24[5]);
	}

	// FUNCTION: ENGINE 0x1061DD10
	void pddiZState::Apply(pddiBaseContext* context)
	{
		context->EnableZBuffer(zBuffer);
		context->SetZCompare(zCompare);
		context->EnableZWrite(zWrite);
		context->SetZBias(zBias, zSlope);
	}

	// FUNCTION: ENGINE 0x1061DD70
	void pddiStencilState::Apply(pddiBaseContext* context)
	{
		context->EnableStencilBuffer(enabled);
		context->SetStencilCompare(compare);
		context->SetStencilRef(ref);
		context->SetStencilMask(mask);
		context->SetStencilWriteMask(writeMask);
		context->SetStencilOp(fail, zFail, zPass);
		context->Unknown51(unknown24);
		context->Unknown52(compare);
		context->Unknown53(unknown2C, unknown30, unknown34);
	}

	// FUNCTION: ENGINE 0x106150B0
	void pddiBaseContext::GetBlendMode(int* a, int* b, int* c, int* d)
	{
		*a = renderState->blend[0];
		*b = renderState->blend[1];
		*c = renderState->blend[2];
		*d = renderState->blend[3];
	}
}
