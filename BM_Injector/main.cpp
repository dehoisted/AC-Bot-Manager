#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>
#include <filesystem>
namespace fs = std::filesystem;

[[noreturn]]
void error(const char* error_message)
{
    std::cout << "Error was thrown, " << error_message << "\n";
    system("pause");
    exit(1);
}

void Get_ProcID(const char* window_title, DWORD& process_id)
{
    GetWindowThreadProcessId(FindWindow(nullptr, window_title), &process_id);
}

int main()
{
    SetConsoleTitleA("Bot Manager Injector");
    constexpr auto window_name = "AssaultCube";
    constexpr auto dll_name = "Bot-Manager.dll";
    std::cout << "Official Github Link: https://github.com/dehoisted/AC-Bot-Manager" << std::endl;
    std::cout << "\nStarting Injection\n";

    DWORD proc_id = 0;
    char dll_path[MAX_PATH];

    switch (fs::exists(dll_name)) {
    case true:
        std::cout << dll_name << " exists...\n";
        break;

    case false:
        error("Bot-Manager.dll doesn't exist");
    }

    if (!GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr))
    {
        error("Failed to get full path name");
    }

    Get_ProcID(window_name, proc_id);
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
    std::cout << "Success injecting Bot Manager into AssaultCube." << std::endl;
    system("pause");
    exit(0);
}