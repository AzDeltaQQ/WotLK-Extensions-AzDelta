#pragma once
#include <functional>
#include <vector>

class HotpatchManager {
public:
    static void InitializeAll();          // Called once during DLL load
    static void ShutdownAll();            // Optional: restore hooks on unload

private:
    static void RegisterItemNamePatches();
    static void RegisterNPCTextPatches();			// Not implemented yet.
    // ... other registration functions




    static bool allIsInitialized;
};