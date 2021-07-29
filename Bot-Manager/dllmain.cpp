#include "pch.h"
#include <iostream>
#include "acf.hpp"
#include "bot.hpp"
#include "mem.h"
Bot Bot::instance;

DWORD WINAPI MainThread(const HMODULE hModule)
{
    const char* BM_str = "Bot Manager";
    MessageBoxA(nullptr, "Successfully attached Bot Manager to Assault Cube.\n(Press F9 to detach bot manager)\n\nPress OK to continue.", BM_str, MB_OK | MB_ICONINFORMATION);
    auto& bot = Bot::Get();
    bot.Config();
	
    // Hook to function
    acf::PrintF = reinterpret_cast<acf::_PrintF>(acf::mod_base + 0x6B060);
    acf::Get_Bot_Connected = reinterpret_cast<acf::_Get_Bot_Connected>(acf::mod_base + 0x93160);
    acf::Draw_Beam_To_Bots = reinterpret_cast<acf::_Draw_Beam_To_Bots>(acf::mod_base + 0x932E0);
    acf::Get_Teleport_Bot = reinterpret_cast<acf::_Get_Teleport_Bot>(acf::mod_base + 0x93790);
    acf::Change_Bots_Shoot = reinterpret_cast<acf::_Change_Bots_Shoot>(acf::mod_base + 0x93240);
    acf::Change_Bot_Idle = reinterpret_cast<acf::_Change_Bot_Idle>(acf::mod_base + 0x93290);
    acf::Rotate_Bot_Skill = reinterpret_cast<acf::_Rotate_Bot_Skill>(acf::mod_base + 0x93650);
    acf::Kick_All_Bots = reinterpret_cast<acf::_Kick_All_Bots>(acf::mod_base + 0x93440);
	
	// Info
    acf::PrintF(acf::sFormat, BM_str, 1, "Bot Manager has started.");
    acf::PrintF(acf::sFormat, BM_str, 1, "Github Link - https://github.com/dehoisted/AC-Bot-Manager");
    acf::PrintF(acf::sFormat, BM_str, 1, "All keybinds will be listed in the opened console.");
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitleA("Bot Manager Keybinds");
    std::cout << "F1 - Turn OP mode on and off.\n";
    std::cout << "F2 - Connect single bot into the lobby.\n";
    std::cout << "F3 - Draw beam pointing to all bots in the lobby.\n";
    std::cout << "F4 - Teleport single bot to you.\n";
    std::cout << "F5 - Change whether all bots will shoot or not.\n";
    std::cout << "F6 - Idle or unidle all bots.\n";
    std::cout << "F7 - Rotate all bots skill.\n";
    std::cout << "F8 - Disconnect all bots in your current lobby.\n";
    std::cout << "F9 - Detach bot manager from Assault Cube.\n";
	
	while (true)
    {
        if (GetAsyncKeyState(VK_F1) & 1) {
	        switch (static bool op_mode = true; op_mode) {
            case true:
                acf::PrintF(acf::sFormat, BM_str, 1, "OP mode on.");
                *reinterpret_cast<int*>(*acf::LPP + 0xf8) = 1337;
                *reinterpret_cast<int*>(mem::FindDMAAddy(acf::mod_base + 0x10f4f4, {0x374, 0x14, 0x0})) = 1337;
                *reinterpret_cast<int*>(*acf::LPP + 0x158) = 1337;
                mem::Nop(reinterpret_cast<BYTE*>(acf::mod_base + 0x63786), 10);
                op_mode = false;
                break;

            case false:
                acf::PrintF(acf::sFormat, BM_str, 1, "OP mode off.");
                *reinterpret_cast<int*>(*acf::LPP + 0xf8) = 100;
                *reinterpret_cast<int*>(mem::FindDMAAddy(acf::mod_base + 0x10f4f4, {0x374, 0x14, 0x0})) = 30;
                *reinterpret_cast<int*>(*acf::LPP + 0x158) = 1;
                mem::Patch((BYTE*)acf::mod_base + 0x63786, (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10);
                op_mode = true;
                break;
            }
            Sleep(250);
        }

        if (GetAsyncKeyState(VK_F2) & 1) {
            acf::PrintF(acf::sFormat, BM_str, 1, "Trying to connect bot...");
            acf::Get_Bot_Connected(nullptr, Bot::Get().skill.c_str(), Bot::Get_Random_Name(6).c_str());
            Sleep(250);
        }
		
		if (GetAsyncKeyState(VK_F3) & 1) {
            acf::PrintF(acf::sFormat, BM_str, 1, "Trying to draw beam to all bots...");
            acf::Draw_Beam_To_Bots();
            acf::PrintF(acf::sFormat, BM_str, 1, "Finished drawing beams.");
            Sleep(250);
		}

        if (GetAsyncKeyState(VK_F4) & 1) {
            acf::PrintF(acf::sFormat, BM_str, 1, "Trying to teleport random bot to you...");
            acf::Get_Teleport_Bot();
            acf::PrintF(acf::sFormat, BM_str, 1, "Done teleporting bot.");
            Sleep(250);
        }

		if (GetAsyncKeyState(VK_F5) & 1) {
            acf::PrintF(acf::sFormat, BM_str, 1, "Trying to change whether bots shoot or not...");
			switch (bot.shooting)
			{
            case true:
                acf::Change_Bots_Shoot(&Bot::yes_shoot);
                bot.shooting = false;
                break;
            case false:
                acf::Change_Bots_Shoot(&Bot::no_shoot);
                bot.shooting = true;
                break;
			}
            Sleep(250);
		}
		
        if (GetAsyncKeyState(VK_F6) & 1) {
            acf::PrintF(acf::sFormat, BM_str, 1, "Trying to idle bots...");
            switch (bot.idling)
        	{
            case true:
                acf::Change_Bot_Idle(&Bot::yes_idle);
                bot.idling = false;
                break;
            case false:
                acf::Change_Bot_Idle(&Bot::no_idle);
                bot.idling = true;
                break;
            }
            Sleep(250);
        }

        if (GetAsyncKeyState(VK_F7) & 1) {
            static short skill_inc = 0;
            acf::PrintF(acf::sFormat, BM_str, 1, "Trying to change all bots skill...");
            acf::Rotate_Bot_Skill(nullptr, bot.skills[skill_inc]);
            skill_inc++;
            if (skill_inc == 5)
                skill_inc = 0;
            Sleep(250);
        }
		
		if (GetAsyncKeyState(VK_F8) & 1) {
            acf::PrintF(acf::sFormat, BM_str, 1, "Trying to disconnect all bots...");
            acf::Kick_All_Bots();
            Sleep(250);
		}

        if (GetAsyncKeyState(VK_F9) & 1) {
	        switch (const int question = MessageBoxA(nullptr, "Are you sure you want to detach bot manager?", "Question", MB_ICONQUESTION | MB_YESNO); question)
        	{
            case IDYES:
                fclose(f);
                FreeConsole();
                acf::PrintF(acf::sFormat, BM_str, 1, "Detached.");
                FreeLibraryAndExitThread(hModule, 0);
            case IDNO:
                break;
            }
        }
	    Sleep(200);
    }
}

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD ul_reason_for_call, [[maybe_unused]] const LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, nullptr);
    return 1;
}