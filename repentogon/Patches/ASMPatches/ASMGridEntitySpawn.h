#pragma once
#include "IsaacRepentance.h"
#include "ASMPatcher.hpp"
#include "../ASMPatches.h"

// sorry sylmir
constexpr ASMPatch::Registers NO_VARIANT_REG = (ASMPatch::Registers)-1;

struct GridEntitySpawnPatchInfo {
	char* signature;
	char* comment; // for log
	int sigOffset; // offset from address found by scanner
	GridEntityType type;
	ASMPatch::Registers variantReg = NO_VARIANT_REG; // register containing variant. -1 / NO_VARIANT_REG if not used
	int variantOffset; // if no register is set, contains variant, otherwise contains offset to variant
	ASMPatch::Registers idxReg; // register containing grid idx
	int idxOffset; // offset from idxReg to grid idx
	ASMPatch::Registers seedReg; // register containing seed
	int seedOffset; // offset from seedReg to seed
	int jumpOffset; // offset from start of patch to jumped address
};

// reference for future maintainers:
// these patches all start at the point where g_Game is loaded into ecx, slightly before the grid idx is checked if between 0-447,
// and then end immediately after GridEntity::Init (or in some cases, to where the ai function jumps to immediately after this call)
const GridEntitySpawnPatchInfo patches[11] = {
	{"8b0d????????8985????????8b81????????8985????????85f678??81fec00100007c??68????????6a03e8????????8b85????????83c40881febf0100000f87????????81bc??????????840300000f8f????????689c010000e8????????8bf083c40489b5????????8bcec745??06000000e8????????c706????????c786????????00000000c786????????00000000c786????????0f000000c686????????00c786????????00000000c786????????00000000c786????????00000000c786????????00000000a1????????8b0d????????8986????????898e????????a1????????8b0d????????8986????????898e????????8b8d????????c745??ffffffff8b85????????c786????????00000000c786????????00000000c746??0e0000008946??8b54????85d274??8b028bca6a01ff108b85????????8b8d????????ffb5????????8974????8bcec746??01000000",
	"ai_mega_fatty (red champion)", 0, GRID_POOP, NO_VARIANT_REG, 1, ASMPatch::Registers::ESI, 0, ASMPatch::Registers::EAX, 0, 0x166},

	{"8b0d????????8985????????8b81????????8985????????85f678??81fec00100007c??68????????6a03e8????????83c408",
	"ai_larryjr", 0, GRID_POOP, NO_VARIANT_REG, 0, ASMPatch::Registers::ESI, 0, ASMPatch::Registers::EAX, 0, 0x186},

	{"8b0d????????8945??8b81????????8985",
	"ai_chub (carrion queen)", 0, GRID_POOP, NO_VARIANT_REG, 1, ASMPatch::Registers::ESI, 0, ASMPatch::Registers::EAX, 0, 0x172},

	{"8b0d????????8985????????8b81????????8985????????85f678??81fec00100007c??68????????6a03e8????????8b85????????83c40881febf0100000f87????????81bc??????????840300000f8f????????689c010000e8????????8bf083c40489b5????????8bcec745??06000000e8????????c706????????c786????????00000000c786????????00000000c786????????0f000000c686????????00c786????????00000000c786????????00000000c786????????00000000c786????????00000000a1????????8b0d????????8986????????898e????????a1????????8b0d????????8986????????898e????????8b8d????????c745??ffffffff8b85????????c786????????00000000c786????????00000000c746??0e0000008946??8b54????85d274??8b028bca6a01ff108b85????????8b8d????????ffb5????????8974????8bcec746??00000000",
	"ai_dingle (normal)", 0, GRID_POOP, NO_VARIANT_REG, 0, ASMPatch::Registers::ESI, 0, ASMPatch::Registers::EAX, 0, 0x190},

	{"8b0d????????8985????????8b81????????8985????????85f678??81fec00100007c??68????????6a03e8????????8b85????????83c40881febf0100000f87????????81bc??????????840300000f8f????????689c010000e8????????8bf083c40489b5????????8bcec745??1c000000",
	"ai_dingle (red champion)", 0, GRID_POOP, NO_VARIANT_REG, 1, ASMPatch::Registers::ESI, 0, ASMPatch::Registers::EAX, 0, 0x107},

	// idx is being pulled from Entity_NPC._projectileDelay because it gets moved to a register AFTER we patch
	{"8b0d????????8bbb",
	"ai_gideon", 0, GRID_STAIRS, NO_VARIANT_REG, 1, ASMPatch::Registers::EBX, 0xb9c, ASMPatch::Registers::EAX, 0, 0xa5},

	{"8b0d????????8945??8b81????????8945",
	"Entity_NPC_Raglich::UpdateAI_Arm", 0, GRID_PIT, NO_VARIANT_REG, 0, ASMPatch::Registers::ESI, 0, ASMPatch::Registers::EAX, 0, 0xa5},

	// overwriting the move of the seed to ebx should be inconsequential
	// this fires AFTER the existing GridEntity is destroyed! custom handling will be needed to fix this
	{"8bd885f678",
	"Entity_NPC_Singe::DoExplosiveFart", 0, GRID_PIT, NO_VARIANT_REG, 0, ASMPatch::Registers::ESI, 0, ASMPatch::Registers::EAX, 0, 0xcb},

	{"8945??85ff78??81ffc00100007c??68????????6a03e8????????83c40881ffbf01000077",
	"make_wall (crawlspace ladder)", 0, GRID_DECORATION, NO_VARIANT_REG, 10, ASMPatch::Registers::EDI, 0, ASMPatch::Registers::EAX, 0, 0x92},

	{"8945??85ff78??81ffc00100007c??68????????6a03e8????????83c40885ff",
	"make_wall (crawlspace gravity)", 0, GRID_GRAVITY, NO_VARIANT_REG, 0, ASMPatch::Registers::EDI, 0, ASMPatch::Registers::EAX, 0, 0x9a},

	{"8b80????????8945??85ff",
	"update_card_against_humanity", 0, GRID_POOP, ASMPatch::Registers::EBP, -0x14, ASMPatch::Registers::EDI, 0, ASMPatch::Registers::ESI, 0, 0x152},
};

void PatchGridSpawnCallback();