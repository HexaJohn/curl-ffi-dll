// dll7.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "dll7.h"

// Test variable for FFI exports
DLL7_API int nDll7=7;

// Test function for FFI exports
DLL7_API int fnDll7(void)
{
    return 77;
}
