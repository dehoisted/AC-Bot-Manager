#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <filesystem>
namespace fs = std::filesystem;

[[noreturn]]
void error(const char* error_message)
{
    std::cout << "Error: " << error_message << "\n";
    std::cout << "Press any key to exit... ";
    (void)_getch();
    exit(1);
}

void get_proc_id(const char* window_title, DWORD& process_id)
{
    GetWindowThreadProcessId(FindWindow(nullptr, window_title), &process_id);
}

int main()
{
    SetConsoleTitleA("Bot Manager Injector");
    constexpr auto window_name = "AssaultCube";
    constexpr auto dll_name = "Bot-Manager.dll";
    std::cout << "Internal Assault Cube cheat made to manage bots easily using keybinds.\n";
    std::cout << "Official Github Link: https://github.com/dehoisted/AC-Bot-Manager\n";
    std::cout << "\nPress any key to start injection... ";
    (void)_getch();
    std::cout << "\nStarting injection...\n";
	
    DWORD proc_id = 0;
    char dll_path[MAX_PATH];
    switch (fs::exists(dll_name)) {
    case true:
        std::cout << dll_name << " exists...\n";
        break;
    case false:
        error("Bot-Manager.dll doesn't exist. (Is it not in this current directory?)\nTry downloading the latest release: https://github.com/dehoisted/AC-Bot-Manager/releases\n");
    }
    if (!GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr))
    {
        error("Failed to get full path name");
    }
    get_proc_id(window_name, proc_id);
    if (proc_id == NULL)
        error("Assault Cube isn't open.");
    std::cout << "Assault Cube is open...\n";
	
    const HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
    if (!h_process)
    {
        error("Failed to open a handle to process");
    }
    void* allocated_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!allocated_memory)
    {
        error("Failed to allocate memory");
    }
    if (!WriteProcessMemory(h_process, allocated_memory, dll_path, MAX_PATH, nullptr))
    {
        error("Failed to write memory to process");
    }
    if (const HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA),
        allocated_memory, NULL, nullptr); !h_thread)
    {
        error("Failed to create remote thread");
    }
    CloseHandle(h_process);
    VirtualFreeEx(h_process, allocated_memory, NULL, MEM_RELEASE);
    std::cout << "Success injecting Bot Manager into Assault Cube." << std::endl;
    std::cout << "Press any key to exit... ";
    (void)_getch();
    exit(0);
}