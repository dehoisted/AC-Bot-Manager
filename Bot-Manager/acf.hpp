#pragma once
#include <cstdint>
#include <minwindef.h>

namespace acf {
    // Module Base Addy
    inline auto mod_base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

    // Local Player Pointer
    inline uintptr_t* LPP = reinterpret_cast<uintptr_t*>(mod_base + 0x10f4f4);

	/*
	  Calling functions internally
	  (Prototypes)
	*/
	
    // Print text to screen
    using _PrintF = char* (__cdecl*)(char* sFormat, ...);
    // Format string for argument 1
    inline char* sFormat = const_cast<char*>("%s:\f%d %s");
    inline _PrintF PrintF;

    // Spawn single bot into the lobby.
    using _Get_Bot_Connected = void(__cdecl*)(BYTE* param_1, const char* b_skill, const char* b_name);
    inline _Get_Bot_Connected Get_Bot_Connected;

	// Draw beam(s) pointing to all bots in the lobby.
    using _Draw_Beam_To_Bots = void(__cdecl*)();
    inline _Draw_Beam_To_Bots Draw_Beam_To_Bots;

    // Teleport bot to your local player
    using _Get_Teleport_Bot = void(__cdecl*)();
    inline _Get_Teleport_Bot Get_Teleport_Bot;
	
	// Change whether all bots will shoot or not. (0 = won't shoot, 1 = will shoot)
    using _Change_Bots_Shoot = void(__cdecl*)(int* shooting);
    inline _Change_Bots_Shoot Change_Bots_Shoot;
	
    // Switch whether bots are idle or not. (0 = no idle, 1 = yes idle)
    using _Change_Bot_Idle = void(__cdecl*)(int* idling);
    inline _Change_Bot_Idle Change_Bot_Idle;

    // Rotate all bots skill
    using _Rotate_Bot_Skill = void(__cdecl*)(BYTE* param_1, const char* b_skill);
    inline _Rotate_Bot_Skill Rotate_Bot_Skill;

    // Kick all bots from current lobby
    using _Kick_All_Bots = void(__cdecl*)();
    inline _Kick_All_Bots Kick_All_Bots;
}