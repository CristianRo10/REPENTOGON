#pragma once

#include <IsaacRepentance.h>

namespace ANM2Utils
{
	BlendMode GetFrameBlendMode(const LayerState& layer) noexcept;
	ColorMod GetFrameColor(const ANM2& anm2, const LayerState& layer, const AnimationFrame& frame, uint32_t flags) noexcept;
	SourceQuad GetFrameSourceQuad(const AnimationFrame& frame, LayerState& layerState, const Vector& topLeftClamp, const Vector& bottomRightClamp, const ANM2& anm2) noexcept;
	DestinationQuad GetFrameDestinationQuad(const AnimationFrame& frame, const Vector& position, LayerState& layerState, const Vector& topLeftClamp, const Vector& bottomRightClamp, const ANM2& anm2) noexcept;
}