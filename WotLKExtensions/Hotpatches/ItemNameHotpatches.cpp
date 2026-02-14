#include <windows.h>
#include "Hotpatches/ItemNameHotpatches.h"
#include <cstring>
#include <cstdint>
#include "MinHook.h"

// Original function type.
typedef char* (__cdecl* GetFullItemName_t)(char* dest, size_t maxchars, int a3, int a4);

// Target function address.
const uintptr_t TARGET_FUNC = 0x706D70;

// Pointer that MinHook will fill to call the original function
GetFullItemName_t Original_GetFullItemName = nullptr;

// Your item patch structure (unchanged)
struct ItemHotpatch {
    char originalName[256];
    char hotpatchName[256];
};

// This is simply a testing array with our hotpatches.
// When we move into making the packet later down the line, the packet will be able to send the hot patched data to the client.
static ItemHotpatch g_ItemHotpatches[] = {
    { "Merciless Gladiator's Crossbow of the Phoenix", "The custom Merciless Gladiator's Crossbow of the Phoenix" },
    { "Hearthstone", "My Awesome Item" },
};

// Your hook function (now calls Original_GetFullItemName via pointer)
char* __cdecl ItemNameHotpatches::Hooked_GetFullItemName(char* dest, size_t maxchars, int a3, int a4)
{
    // Call the original function using MinHook's pointer
    char* result = Original_GetFullItemName(dest, maxchars, a3, a4);

    if (result && dest != nullptr) {
        for (const auto& patch : g_ItemHotpatches) {
            if (strstr(result, patch.originalName) != nullptr) {
                strncpy_s(dest, maxchars, patch.hotpatchName, maxchars - 1);
                dest[maxchars - 1] = '\0';
                break;
            }
        }
    }
    return result;
}


// Update the InstallHook method to use the static function pointer
void ItemNameHotpatches::InstallHook()
{
    // Initialize MinHook (do this once; you might already call it elsewhere)
    if (MH_Initialize() != MH_OK) {
        // Handle error (optional)
        return;
    }

    // Create the hook – MinHook automatically builds a trampoline
    if (MH_CreateHook((LPVOID)TARGET_FUNC, &ItemNameHotpatches::Hooked_GetFullItemName,
        (LPVOID*)&Original_GetFullItemName) != MH_OK) {
        // Handle error
        return;
    }

    // Enable the hook
    if (MH_EnableHook((LPVOID)TARGET_FUNC) != MH_OK) {
        // Handle error
        return;
    }
}

// Uninstallation – replaces your manual UninstallHook
void ItemNameHotpatches::UninstallHook()
{
    // Disable the hook
    MH_DisableHook((LPVOID)TARGET_FUNC);

    // Optionally remove the hook (MH_RemoveHook) – not strictly necessary
    // MH_RemoveHook((LPVOID)TARGET_FUNC);

    // Uninitialize MinHook (if no other hooks are active)
    MH_Uninitialize();
}