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

    // Connect 1 bot to game
    using _Get_Bot_Connected = void(__cdecl*)(BYTE* param_1, const char* param2, const char* param_3);
    inline _Get_Bot_Connected Get_Bot_Connected;

    // Rotate is all bots are idle or not
    using _Change_Bot_Idle = void(__cdecl*)(int* param_1);
    inline _Change_Bot_Idle Change_Bot_Idle;

    // Rotate all bots skill
    using _Change_Bot_Skill = void(__cdecl*)(BYTE* param_1, const char* param_2);
    inline _Change_Bot_Skill Change_Bot_Skill;

    // Teleport bot to your local player
    using _Get_Telebot = void(__cdecl*)();
    inline _Get_Telebot Get_Telebot;

    // Kick all bots from current lobby
    using _Kick_All_Bots = void(__cdecl*)();
    inline _Kick_All_Bots Kick_All_Bots;
}