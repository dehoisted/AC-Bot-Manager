#include "pch.h"
#include "acf.hpp"
#include "bot.hpp"
#include "mem.h"
Bot Bot::instance;

DWORD WINAPI MainThread(const HMODULE hModule)
{
    MessageBoxA(nullptr, "Successfully attached Bot Manager to Assault Cube.\n(Press F7 to detach bot manager)\n\nPress OK to continue.", "Bot Manager", MB_OK | MB_ICONINFORMATION);
    auto& bot = Bot::Get();
    bot.Config();

    // Hook to function
    acf::PrintF = reinterpret_cast<acf::_PrintF>(acf::mod_base + 0x6B060);
    acf::Get_Bot_Connected = reinterpret_cast<acf::_Get_Bot_Connected>(acf::mod_base + 0x93160);
    acf::Change_Bot_Idle = reinterpret_cast<acf::_Change_Bot_Idle>(acf::mod_base + 0x93290);
    acf::Change_Bot_Skill = reinterpret_cast<acf::_Change_Bot_Skill>(acf::mod_base + 0x93650);
    acf::Get_Telebot = reinterpret_cast<acf::_Get_Telebot>(acf::mod_base + 0x93790);
    acf::Kick_All_Bots = reinterpret_cast<acf::_Kick_All_Bots>(acf::mod_base + 0x93440);

	// Info
    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Github Link - https://github.com/dehoisted/AC-Bot-Manager");
    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Press F1 to turn OP mode on and off");
    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Press F2 to spawn bot into the game & F6 to despawn all bots from game");
    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Press F3 to idle and unidle bots");
    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Press F4 to switch all bots skill");
    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Press F5 to teleport random bot to you");
	
	while (true)
    {
        if (GetAsyncKeyState(VK_F1) & 1) {
	        switch (static bool opmode = true; opmode) {
            case true:
                acf::PrintF(acf::sFormat, "Bot Manager", 1, "OP mode on.");
                *reinterpret_cast<int*>(*acf::LPP + 0xf8) = 1337;
                *reinterpret_cast<int*>(mem::FindDMAAddy(acf::mod_base + 0x10f4f4, {0x374, 0x14, 0x0})) = 1337;
                *reinterpret_cast<int*>(*acf::LPP + 0x158) = 1337;
                mem::Nop(reinterpret_cast<BYTE*>(acf::mod_base + 0x63786), 10);
                opmode = false;
                break;

            case false:
                acf::PrintF(acf::sFormat, "Bot Manager", 1, "OP mode off.");
                *reinterpret_cast<int*>(*acf::LPP + 0xf8) = 100;
                *reinterpret_cast<int*>(mem::FindDMAAddy(acf::mod_base + 0x10f4f4, {0x374, 0x14, 0x0})) = 30;
                *reinterpret_cast<int*>(*acf::LPP + 0x158) = 1;
                mem::Patch((BYTE*)acf::mod_base + 0x63786, (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10);
                opmode = true;
                break;
            }
            Sleep(250);
        }

	    if (GetAsyncKeyState(VK_F2) & 1) {
		    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Trying to spawn bot...");
            acf::Get_Bot_Connected(nullptr, Bot::Get().skill.c_str(), Bot::Get_Random_Name(6).c_str());
		    Sleep(250);
	    }

		if (GetAsyncKeyState(VK_F3) & 1) {
            acf::PrintF(acf::sFormat, "Bot Manager", 1, "Trying to idle bots...");
			switch (bot.idling) {
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

        if (GetAsyncKeyState(VK_F4) & 1) {
            static short skill_inc = 0;
            acf::PrintF(acf::sFormat, "Bot Manager", 1, "Trying to change all bot skill...");
            acf::Change_Bot_Skill(nullptr, bot.skills[skill_inc]);
            skill_inc++;
            if (skill_inc == 5)
                skill_inc = 0;
            Sleep(250);
        }

        if (GetAsyncKeyState(VK_F5) & 1) {
            acf::PrintF(acf::sFormat, "Bot Manager", 1, "Trying to teleport random bot to you...");
            acf::Get_Telebot();
            acf::PrintF(acf::sFormat, "Bot Manager", 1, "Done teleporting bot.");
            Sleep(250);
        }
		
		if (GetAsyncKeyState(VK_F6) & 1) {
            acf::PrintF(acf::sFormat, "Bot Manager", 1, "Trying to disconnect all bots...");
            acf::Kick_All_Bots();
            Sleep(250);
		}
		
	    if (GetAsyncKeyState(VK_F7) & 1) {
		    acf::PrintF(acf::sFormat, "Bot Manager", 1, "Detached Successfully.");
		    break;
	    }
	    Sleep(200);
    }
    MessageBoxA(nullptr, "Bot Manager has been detached.", "Bot Manager", MB_OK | MB_ICONINFORMATION);
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD ul_reason_for_call, [[maybe_unused]] const LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, nullptr);
    return 1;
}