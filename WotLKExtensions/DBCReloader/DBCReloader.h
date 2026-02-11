#pragma once

#include "SharedDefines.h"

class DBCReloader {
public:
	static int LoadAllDBCs();
    static int ReloadDBCByName(const char* name);
};
