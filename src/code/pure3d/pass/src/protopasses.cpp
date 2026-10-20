// The passes of the render pipeline built on pure3d::Pass: the decal, the lit and opaque, the shadow, the slow Z and
// the view pass (0x10765330 - 0x1077C000; the file name is a guess, the units of this range are not told apart). Only
// the functions listed below are reconstructed.
#include "code/container/sort.h"
#include "code/math/aabb.h"
#include "code/math/matrix.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/light.h"
#include "code/pure3d/lightselection.h"
#include "code/pure3d/pass/rendertargetmanager.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/scene.h"
#include "code/pure3d/shaderconstants.h"
#include "code/pure3d/shadows/shadowrendermanager.h"
#include "code/pure3d/view.h"

#include <math.h>

// The kept copies of the part filter's array (sixteen entries) and the light list's append (eight lights)
// FUNCTION: ENGINE 0x10766000
template pure3d::PassEntry* container::ConstructCopiesN<pure3d::PassEntry>(const pure3d::PassEntry*, unsigned int,
	pure3d::PassEntry*);

// FUNCTION: ENGINE 0x10766040
template container::ArrayFixed<pure3d::PassEntry, 16>::ArrayFixed(const ArrayFixed&);

// FUNCTION: ENGINE 0x10766090
template container::ArrayFixed<pure3d::PassEntry, 16>& container::ArrayFixed<pure3d::PassEntry, 16>::operator=(
	const ArrayFixed&);

// FUNCTION: ENGINE 0x1076BE40
template bool container::ArrayFixed<pure3d::Light*, 8>::PushBack(pure3d::Light* const&);

namespace pure3d
{
	// FUNCTION: ENGINE 0x10761750
	void DrawablePart::Draw(const core::Name<core::CaseInsensitiveKey32>* shader, const PrimStreamParameters* parameters)
	{
		if (renderBits.Test(9))
		{
			pddi->DrawBatch(shader, &batch, parameters);
		}
		else
		{
			primitive->Draw(shader, state, &worldMatrix, parameters, binding);
		}
	}

	namespace
	{
		// The sphere around a box (zero for an empty one): math::AABB::GetSphere as the engine inlines it
		__forceinline math::Sphere BoxSphere(const math::AABB& box)
		{
			math::Sphere sphere;
			if (!box.IsEmpty())
			{
				float hx = (box.max.x - box.min.x) * 0.5f;
				float hz = (box.max.z - box.min.z) * 0.5f;
				float hy = (box.max.y - box.min.y) * 0.5f;
				sphere.centre.x = hx + box.min.x;
				sphere.centre.y = hy + box.min.y;
				sphere.centre.z = hz + box.min.z;
				float squared = hx * hx;
				squared += hz * hz;
				squared += hy * hy;
				sphere.radius = sqrtf(squared);
			}
			else
			{
				sphere.centre.x = 0.0f;
				sphere.centre.y = 0.0f;
				sphere.centre.z = 0.0f;
				sphere.radius = 0.0f;
			}
			return sphere;
		}
	}

	// FUNCTION: ENGINE 0x107654E0
	// EQUIVALENT: register allocation and the frame (the engine keeps the part in a stack slot in the first loop); every call, store and float operation is the engine's
	void ProtoDecalPass::Render(PassContext* context)
	{
		pddiSurface* colour = (pddiSurface*)RenderTargetManager::sSingleton->colour;
		pddiSurface* depth = (pddiSurface*)RenderTargetManager::sSingleton->currentDepth;
		pddiRenderTargets targets = {0, 0, 0, 0, 0};
		targets.colour = decalTarget->surface->GetHandle();
		targets.depth = depth->GetHandle();
		pddi->SetRenderTargets(&targets);
		RenderStateBackup backup(pddi, 1, 0);
		pddi->EnableZWrite(false);
		pddi->EnableZBuffer(true);
		pddi->SetZCompare(3);
		pddi->SetColourWrite(true, true, true, true);
		pddi->SetViewUnknown4(0);
		pddi->Clear(1);
		pddi->EnableFog(true);
		pddi->SetFogRange(gFogRangeNear, gFogRangeFar);
		PrimStreamParameters parameters;
		parameters.blendMode = 6;
		parameters.blendFactor = 7;
		parameters.unknown4Bits14 = 0x21;
		parameters.flag0 = 1;
		parameters.flag2 = 1;
		parameters.unknown4Bits10 = 4;
		parameters.unknown0 = 0.0f;
		PartList* list = GetParts(context->scene);
		const math::Matrix& cameraMatrix = context->camera->transform;
		math::Vector cameraPosition;
		cameraMatrix.GetTranslation(cameraPosition);
		// The sphere's radius keeps the value of the last part that had a state (the engine does not clear it)
		math::Sphere sphere;
		// The parts that are not decals fade in by their distance
		for (DrawablePart** it = list->begin, **end = list->end; it != end; it++)
		{
			DrawablePart* part = *it;
			sphere.centre.x = 0.0f;
			sphere.centre.y = 0.0f;
			sphere.centre.z = 0.0f;
			if (part->state)
			{
				math::AABB box;
				part->state->GetBoundingBox(&box);
				math::Sphere found = BoxSphere(box);
				sphere.centre.x = found.centre.x;
				sphere.centre.y = found.centre.y;
				sphere.centre.z = found.centre.z;
				sphere.radius = found.radius;
			}
			else
			{
				part->primitive->GetCentre(&sphere.centre);
			}
			sphere.centre.Transform(part->worldMatrix);
			float dy = sphere.centre.y - cameraPosition.y;
			float dz = sphere.centre.z - cameraPosition.z;
			float dx = sphere.centre.x - cameraPosition.x;
			float squared = dx * dx;
			squared += dz * dz;
			squared += dy * dy;
			if (part->primitive->type != 0x200 && !(sqrtf(squared) - sphere.radius > 175.0f))
			{
				float lod = part->unknown1C;
				if (lod > 0.0f)
				{
					*pddi->GetConstant(gConstantShaderLODGeo, pddiBaseContext::CONSTANT_FLOAT) = lod;
					part->Draw(&gShaderLit, &parameters);
				}
			}
		}
		// The decals fade out by their distance
		for (DrawablePart** it = list->begin, **end = list->end; it != end; it++)
		{
			DrawablePart* part = *it;
			if (part->primitive->type == 0x200)
			{
				sphere.centre.x = 0.0f;
				sphere.centre.y = 0.0f;
				sphere.centre.z = 0.0f;
				if (part->state)
				{
					math::AABB box;
					part->state->GetBoundingBox(&box);
					math::Sphere found = BoxSphere(box);
					sphere.centre.x = found.centre.x;
					sphere.centre.y = found.centre.y;
					sphere.centre.z = found.centre.z;
					sphere.radius = found.radius;
				}
				else
				{
					part->primitive->GetCentre(&sphere.centre);
				}
				sphere.centre.Transform(part->worldMatrix);
				float dx = sphere.centre.x - cameraPosition.x;
				float dy = sphere.centre.y - cameraPosition.y;
				float dz = sphere.centre.z - cameraPosition.z;
				float squared = dx * dx;
				squared += dz * dz;
				squared += dy * dy;
				float distance = (sqrtf(squared) - 100.0f) * 0.013333334f;
				float fade = distance >= 0.0f ? distance : 0.0f;
				if (fade - 1.0f >= 0.0f)
				{
					fade = 1.0f;
				}
				float alpha = (1.0f - fade * fade) * part->unknown1C;
				if (alpha > 0.0f)
				{
					*pddi->GetConstant(gConstantShaderLODGeo, pddiBaseContext::CONSTANT_FLOAT) = alpha;
					if (part->renderBits.Test(9))
					{
						pddi->DrawBatch(&gShaderLit, &part->batch, &parameters);
					}
					else
					{
						part->primitive->Draw(&gShaderLit, part->state, &part->worldMatrix, &parameters, part->binding);
					}
				}
			}
		}
		// The buffer the decals were drawn into becomes the decal textures of the lit passes
		pddi->Unknown7(0, decalTarget->surface, 0, 0, 0, 0);
		targets.colour = colour->GetHandle();
		targets.depth = depth->GetHandle();
		pddi->SetRenderTargets(&targets);
		pddi->constantsDirty |= pddiBaseContext::CONSTANT_TEXTURE;
		pddi->constants->SetTexture(&gConstantDecalColourBuffer, decalTarget->surface);
		unsigned int* texture = pddi->GetTextureConstant(gConstantDecalColourBuffer);
		texture[1] = (texture[1] & 0xf8444754) | 0x444454;
		texture = pddi->GetTextureConstant(gConstantDecalColourBuffer);
		texture[1] = (texture[1] & 0xf8488bff) | 0x488800;
		pddi->constantsDirty |= pddiBaseContext::CONSTANT_TEXTURE;
		pddi->constants->SetTexture(&gConstantDecalNormalBuffer, 0);
		texture = pddi->GetTextureConstant(gConstantDecalNormalBuffer);
		texture[1] = (texture[1] & 0xf8444752) | 0x444452;
		pddiSize* size = decalTarget->surface->info->size;
		float halfWidth = 0.5f / size->width;
		float halfHeight = 0.5f / size->height;
		float* halfPixel = pddi->GetConstant(gConstantHalfPixel, pddiBaseContext::CONSTANT_FLOAT2);
		halfPixel[0] = halfWidth;
		halfPixel[1] = halfHeight;
	}

	// FUNCTION: ENGINE 0x1076F010
	void ProtoSlowZPass::Render(PassContext* context)
	{
		PartList* list = GetParts(context->scene);
		for (DrawablePart** it = list->begin; it != list->end; it++)
		{
			DrawablePart* part = *it;
			const PrimStreamParameters* parameters = &((PartBindingSource*)part->primitive->unknown18)->parameters;
			PrimitiveState* state = part->state;
			if (state)
			{
				state->Unknown9();
			}
			float* joint = pddi->GetConstant(gConstantProtoJointMatrix, pddiBaseContext::CONSTANT_MATRIX);
			joint[0] = part->jointMatrix.m[0][0];
			joint[1] = part->jointMatrix.m[0][1];
			joint[2] = part->jointMatrix.m[0][2];
			joint[3] = part->jointMatrix.m[0][3];
			joint[4] = part->jointMatrix.m[1][0];
			joint[5] = part->jointMatrix.m[1][1];
			joint[6] = part->jointMatrix.m[1][2];
			joint[7] = part->jointMatrix.m[1][3];
			joint[8] = part->jointMatrix.m[2][0];
			joint[9] = part->jointMatrix.m[2][1];
			joint[10] = part->jointMatrix.m[2][2];
			joint[11] = part->jointMatrix.m[2][3];
			joint[12] = part->jointMatrix.m[3][0];
			joint[13] = part->jointMatrix.m[3][1];
			joint[14] = part->jointMatrix.m[3][2];
			joint[15] = part->jointMatrix.m[3][3];
			if (part->renderBits.Test(9))
			{
				pddi->DrawBatch(&gShaderZFill, &part->batch, parameters);
			}
			else
			{
				part->primitive->Draw(&gShaderZFill, part->state, &part->worldMatrix, parameters, part->binding);
			}
		}
	}

	// FUNCTION: ENGINE 0x10766170
	// EQUIVALENT: the engine lays the key and scratch arrays out in the other order and reloads the list pointer in the last loop
	void ProtoOpaquePass::SortParts(PartList* parts)
	{
		unsigned int count = parts->end - parts->begin;
		if (count < 5000)
		{
			unsigned char indices[10000];
			unsigned char scratch[10000];
			unsigned int keys[5000];
			container::ArrayFixed<DrawablePart*, 5000> ordered;
			if (parts->begin != parts->end)
			{
				DrawablePart** it = parts->begin;
				for (unsigned int i = 0; i < count; i++)
				{
					DrawablePart* part = *it;
					it++;
					PartBindingSource* source = (PartBindingSource*)part->GetRenderBinding();
					unsigned int shaderKey = source->shader->GetSortKey() << 16;
					unsigned int sortKey;
					if (part->renderBits.Test(9))
					{
						sortKey = part->batch.sortKey;
					}
					else
					{
						sortKey = (unsigned int)part->primitive;
					}
					keys[i] = (sortKey & 0xffff) | shaderKey;
					ordered.PushBack(part);
				}
				unsigned short* sorted = container::RadixSort((unsigned char*)keys, ordered.Size(), (unsigned short*)indices,
					(unsigned short*)scratch, 0x83210, 4, true);
				parts->end = parts->begin;
				for (int n = ordered.Size(); n != 0; n--)
				{
					DrawablePart** end = parts->end;
					if (end < parts->capacity)
					{
						parts->end = end + 1;
						if (end != 0)
						{
							*end = ordered[*sorted];
						}
					}
					sorted++;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107678C0
	PartList* ProtoShadowPass::GetShadowParts(Scene* scene, int view)
	{
		return GetParts(scene);
	}

	// FUNCTION: ENGINE 0x10767B60
	// EQUIVALENT: stack slots of the spilled locals and the loop counters differ; every call and store is the engine's
	void ProtoShadowPass::DrawShadowCasters(RenderParams* params, int view, Scene* scene)
	{
		ShadowRenderManager* manager = ShadowRenderManager::Get();
		const void* camera = params->GetCameraData(view);
		const void* viewState = params->GetViewState(view);
		SetViewport(viewState);
		Unknown107678D0();
		pddi->drawFlags |= 1;
		pddi->drawFlags |= 8;
		const core::Name<core::CaseInsensitiveKey32>* shader;
		if (params->GetUnknown14() == 1)
		{
			shader = &gShaderShadowDepth;
		}
		else
		{
			shader = &gShaderZFill;
		}
		SetCamera(camera);
		PrimStreamParameters parameters;
		parameters.unknown0 = 0.5f;
		PassEntries saved = entries;
		entries = shadowEntries;
		PartList* list = GetParts(scene);
		int count = 0;
		for (DrawablePart** it = list->begin; it != list->end; it++)
		{
			scene->batches[count++] = &(*it)->batch;
			if ((*it)->state)
			{
				(*it)->state->Unknown9();
			}
		}
		if (count != 0)
		{
			pddi->DrawBatches(scene->batches, count);
		}
		entries = saved;
		LightGroups* groups = (LightGroups*)scene->GetUnknownD8();
		MergeLightBits(&groups->sets->merged0F0, &groups->sets->shared180, &groups->sets->shared90, groups, 1);
		PartList* parts = GetShadowParts(scene, view);
		for (DrawablePart** it = parts->begin; it != parts->end; it++)
		{
			DrawablePart* part = *it;
			part->renderBits.Set(10, false);
			SetObjectSpaceLightPosition(camera, &part->worldMatrix);
			float* joint = pddi->GetConstant(gConstantProtoJointMatrix, pddiBaseContext::CONSTANT_MATRIX);
			const float* from = &part->jointMatrix.m[0][0];
			float* to = joint;
			for (int row = 0; row < 4; row++)
			{
				for (int column = 0; column < 4; column++)
				{
					*to++ = *from++;
				}
			}
			PartBindingSource* source = (PartBindingSource*)part->primitive->unknown18;
			parameters = source->parameters;
			if (part->state)
			{
				part->state->Unknown9();
			}
			if (part->client.GetFlag(0x13))
			{
				if (!parameters.flag0)
				{
					parameters.flag0 = 1;
					parameters.unknown4Bits10 = 4;
					parameters.unknown0 = 0.0f;
					pddi->DrawBatch(&gShaderLitPR, &part->batch, &parameters);
				}
				else
				{
					pddi->DrawBatch(&gShaderZFill, &part->batch, &parameters);
				}
			}
			else
			{
				pddi->DrawBatch(shader, &part->batch, &parameters);
			}
		}
		manager->Unknown10715AC0(viewState);
		pddi->drawFlags &= ~8;
		pddi->drawFlags &= ~1;
	}

	// FUNCTION: ENGINE 0x1076AF90
	float ViewPass::GetUnknownE4()
	{
		return unknownE4;
	}

	// FUNCTION: ENGINE 0x1076B020
	bool ProtoLitPass::HasShadowMap()
	{
		if (ShadowRenderManager::Get()->shadowMap != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1076B030
	void ProtoLitPass::UploadVertexLights(int unused)
	{
		LightSelection::Get()->UploadVertexLights();
	}

	// FUNCTION: ENGINE 0x1076BB70
	// EQUIVALENT: one constant store sits before the loop's first load here, after its compare in the engine
	void ProtoLitPass::DrawParts(PartList* parts, PrimStreamParameters* parameters, PassContext* context)
	{
		pddi->ClearFlagConstant(gConstantLightIsLitPass);
		float* colour = pddi->GetConstant(gConstantLightColour, pddiBaseContext::CONSTANT_FLOAT4);
		colour[0] = 0.0f;
		colour[1] = 0.0f;
		colour[2] = 0.0f;
		colour[3] = 0.0f;
		float* ambient = pddi->GetConstant(gConstantLightAmbient, pddiBaseContext::CONSTANT_FLOAT4);
		ambient[0] = 0.0f;
		ambient[1] = 0.0f;
		ambient[2] = 0.0f;
		ambient[3] = 0.0f;
		float* bounds = pddi->GetConstant(gConstantLightObjectSpaceLightBounds, pddiBaseContext::CONSTANT_FLOAT4);
		bounds[0] = 0.0f;
		bounds[1] = 0.0f;
		bounds[2] = 0.0f;
		bounds[3] = 1e12f;
		*pddi->GetConstant(gConstantLightEnableSpotKill, pddiBaseContext::CONSTANT_FLOAT) = 0.0f;
		for (DrawablePart** it = parts->begin; it != parts->end; it++)
		{
			DrawablePart* part = *it;
			if (!part->renderBits.Test(1))
			{
				if (part->renderBits.Test(9))
				{
					pddi->DrawBatch(&gShaderLit, &part->batch, parameters);
				}
				else
				{
					part->primitive->Draw(&gShaderLit, part->state, &part->worldMatrix, parameters, part->binding);
				}
			}
		}
		pddi->drawFlags &= ~4;
	}

	namespace
	{
		// sum += colour * scale (the four components, w the intensity)
		inline math::Vector4 Scaled(const math::Vector4& colour, float scale)
		{
			return math::Vector4(colour.x * scale, colour.y * scale, colour.z * scale, colour.w * scale);
		}
		// constant = (colour * scale, w)

		inline void StoreScaled(float* constant, const math::Vector4& colour, float scale, float w)
		{
			math::Vector4 scaled = Scaled(colour, scale);
			constant[0] = scaled.x;
			constant[1] = scaled.y;
			constant[2] = scaled.z;
			constant[3] = w;
		}
		inline void AddScaled(math::Vector4& sum, const math::Vector4& colour, float scale)
		{
			math::Vector4 scaled = Scaled(colour, scale);
			sum.x = scaled.x + sum.x;
			sum.y = scaled.y + sum.y;
			sum.z = scaled.z + sum.z;
			sum.w = scaled.w + sum.w;
		}
	}

	// FUNCTION: ENGINE 0x1076CD90
	// NONMATCHING: register allocation and the stack layout of the four light lists differ; compiled into the game it
	// crashes at start-up (its static locals are ours, not the engine's 0x11282BD0 / 0x11282BE0 / guard 0x11282BE8),
	// so the body is not trusted yet
#ifdef NONMATCHING
	void ProtoLitPass::SetupLights(int mode)
	{
		LightList* lights = LightSelection::Get()->GetActiveLights();
		unsigned int shadowLightLimit = 1;
		if (LightSelection::Get()->GetMode() == 2)
		{
			shadowLightLimit = 0;
		}
		static core::Name<core::CaseSensitiveKey> shadowLight("shadowLight", 0);
		container::ArrayFixed<Light*, 8> cheapPoints;
		container::ArrayFixed<Light*, 8> points;
		container::ArrayFixed<Light*, 8> spots;
		container::ArrayFixed<Light*, 8> directional;
		math::Vector4 ambient(0.0f, 0.0f, 0.0f, 0.0f);
		Light* shadowLightSource = 0;
		for (unsigned int i = 0; i < (unsigned int)(lights->end - lights->begin); i++)
		{
			Light* light = lights->begin[i];
			ProtoLightUserData* data = dynamic_cast<ProtoLightUserData*>(light->GetUserData());
			switch (light->type)
			{
			case Light::TYPE_DIRECTIONAL:
				if (light->mName == shadowLight)
				{
					shadowLightSource = light;
				}
				else if (light->IsEnabled() && directional.Size() != 8)
				{
					directional.PushBack(light);
				}
				break;
			case Light::TYPE_POINT:
				if (data && data->cheap == 0)
				{
					if (points.Size() != 8)
					{
						points.PushBack(light);
					}
				}
				else
				{
					cheapPoints.PushBack(light);
				}
				break;
			case Light::TYPE_SPOT:
				if (light->IsEnabled())
				{
					spots.PushBack(light);
				}
				break;
			case Light::TYPE_AMBIENT:
				{
					const math::Vector4* colour = light->GetColour();
					AddScaled(ambient, *colour, LightSelection::Get()->GetIntensityScale(light, mode));
				}
				break;
			}
		}
		// The disabled directional lights and spots come after the enabled ones
		for (unsigned int i = 0; i < (unsigned int)(lights->end - lights->begin); i++)
		{
			Light* light = lights->begin[i];
			if (!light->IsEnabled())
			{
				switch (light->type)
				{
				case Light::TYPE_DIRECTIONAL:
					if (light->mName != shadowLight)
					{
						directional.PushBack(light);
					}
					break;
				case Light::TYPE_SPOT:
					spots.PushBack(light);
					break;
				}
			}
		}
		float* constant = pddi->GetConstant(gConstantPRLightAmbient, pddiBaseContext::CONSTANT_FLOAT4);
		constant[0] = ambient.x;
		constant[1] = ambient.y;
		constant[2] = ambient.z;
		constant[3] = ambient.w;
		constant = pddi->GetConstant(gConstantPRLightAmbientVertex, pddiBaseContext::CONSTANT_FLOAT4);
		int* colours[4] = {&gConstantPRLightColour1, &gConstantPRLightColour3, &gConstantPRLightColour4,
			&gConstantPRLightColour5};
		int* directions[4] = {&gConstantPRLightDirection1, &gConstantPRLightDirection3, &gConstantPRLightDirection4,
			&gConstantPRLightDirection5};
		bool lit = false;
		constant[0] = ambient.x;
		constant[1] = ambient.y;
		constant[2] = ambient.z;
		constant[3] = ambient.w;
		for (unsigned int i = 0; i < 4; i++)
		{
			if (i < (unsigned int)directional.Size())
			{
				Light* light = directional[i];
				float scale = LightSelection::Get()->GetIntensityScale(light, mode);
				float range = LightSelection::Get()->GetRangeScale(light);
				const math::Vector4* colour = light->GetColour();
				float* c = pddi->GetConstant(*colours[i], pddiBaseContext::CONSTANT_FLOAT4);
				StoreScaled(c, *colour, scale, range);
				float* d = pddi->GetConstant(*directions[i], pddiBaseContext::CONSTANT_FLOAT3);
				const math::Vector* direction = light->GetDirection();
				d[0] = direction->x;
				d[1] = direction->y;
				d[2] = direction->z;
				if (i < shadowLightLimit)
				{
					if (light->IsEnabled())
					{
						GetLightingInputs()->SetLight(light);
						GetLightingInputs()->SetSpotLight(light, HasShadowMap(), 0);
						lit = true;
					}
					else
					{
						GetLightingInputs()->SetSpotLight(0, false, 0);
					}
				}
			}
			else
			{
				float* c = pddi->GetConstant(*colours[i], pddiBaseContext::CONSTANT_FLOAT4);
				c[0] = 0.0f;
				c[1] = 0.0f;
				c[2] = 0.0f;
				c[3] = 0.0f;
				float* d = pddi->GetConstant(*directions[i], pddiBaseContext::CONSTANT_FLOAT3);
				d[0] = 1.0f;
				d[1] = 0.0f;
				d[2] = 0.0f;
			}
		}
		if (shadowLightSource)
		{
			float scale = LightSelection::Get()->GetIntensityScale(shadowLightSource, mode);
			float range = LightSelection::Get()->GetRangeScale(shadowLightSource);
			const math::Vector4* colour = shadowLightSource->GetColour();
			float* c = pddi->GetConstant(gConstantPRLightColour2, pddiBaseContext::CONSTANT_FLOAT4);
			StoreScaled(c, *colour, scale, range);
			float* d = pddi->GetConstant(gConstantPRLightDirection2, pddiBaseContext::CONSTANT_FLOAT3);
			const math::Vector* direction = shadowLightSource->GetDirection();
			d[0] = direction->x;
			d[1] = direction->y;
			d[2] = direction->z;
		}
		else
		{
			float* c = pddi->GetConstant(gConstantPRLightColour2, pddiBaseContext::CONSTANT_FLOAT4);
			c[0] = 0.0f;
			c[1] = 0.0f;
			c[2] = 0.0f;
			c[3] = 0.0f;
			float* d = pddi->GetConstant(gConstantPRLightDirection2, pddiBaseContext::CONSTANT_FLOAT3);
			d[0] = 1.0f;
			d[1] = 0.0f;
			d[2] = 0.0f;
		}
		UploadPointLights(&points);
		UploadVertexLights(mode);
		if (lit && HasShadowMap())
		{
			unsigned int* texture = pddi->GetTextureConstant(gConstantShadowMap);
			texture[1] = (texture[1] & 0xf8408bff) | 0x408800;
		}
		else
		{
			GetLightingInputs()->SetSpotLight(0, false, 0);
		}
		static math::Vector4 params(0.0f, 0.0f, 0.0f, 0.0f);
		constant = pddi->GetConstant(gConstantPRLightParams1, pddiBaseContext::CONSTANT_FLOAT4);
		constant[0] = params.x;
		constant[1] = params.y;
		constant[2] = params.z;
		constant[3] = params.w;
		constant = pddi->GetConstant(gConstantLightObjectSpaceLightBounds, pddiBaseContext::CONSTANT_FLOAT4);
		constant[0] = 0.0f;
		constant[1] = 0.0f;
		constant[2] = 0.0f;
		constant[3] = 1e12f;
		*pddi->GetConstant(gConstantLightEnableSpotKill, pddiBaseContext::CONSTANT_FLOAT) = 0.0f;
		pddi->SetFlagConstant(gConstantLightIsLitPass);
	}
#endif

	// FUNCTION: ENGINE 0x10768670
	// EQUIVALENT: the engine loads the device pointer before converting the clear colour and keeps the result in eax
	void ViewPass::Render(PassContext* context)
	{
		view->SetWindow(window[0], window[1], window[2], window[3]);
		bool replaced = false;
		if (context->views.Size() != 0)
		{
			if (viewLevel >= (unsigned int)context->views.Size())
			{
				return;
			}
			context->camera = context->views[viewLevel].camera;
			context->shadowCamera = context->views[viewLevel].shadowCamera;
			replaced = true;
			context->scene = context->views[viewLevel].scene;
		}
		BeginView(view, context->camera);
		if (shadowView)
		{
			if (!gVisibilityTestActive)
			{
				StartVisibilityTest(context, true);
			}
			FinishVisibilityTest(context);
		}
		if (unknownB8)
		{
			Unknown13(0x10);
		}
		RunChildren(context);
		if (clearAlpha)
		{
			pddi->SetColourWrite(false, false, false, true);
			pddi->SetViewUnknown4((unsigned int)(alpha * 255.0f) << 24 | 0xffffff);
			pddi->Clear(1);
			pddi->SetColourWrite(true, true, true, true);
		}
		EndView(view);
		if (replaced)
		{
			context->camera = context->views[0].camera;
			context->shadowCamera = context->views[0].shadowCamera;
			context->scene = context->views[0].scene;
		}
	}
}
