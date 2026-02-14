#pragma once
#include <functional>
#include <vector>

class ItemNameHotpatches {
public:
	static char* __cdecl Hooked_GetFullItemName(char* dest, size_t maxchars, int a3, int a4);
    static void InstallHook();          // Called once during DLL load
    static void UninstallHook();            // Optional: restore hooks on unload
};