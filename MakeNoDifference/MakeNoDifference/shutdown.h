#pragma once
#include <Windows.h>

typedef enum _SHUTDOWN_METHOD {
	ShutdownNormal,
	ShutdownTimeout,
	ShutdownFastPowerOff
} SHUTDOWN_METHOD;

BOOL InternalAdjustPrivilege(ULONG PrivilegeValue);

BOOL ShutdownSystem(SHUTDOWN_METHOD ShutdownMethod, LPWSTR ShutdownMessage, DWORD ShutdownTimeSec, BOOL bForce, BOOL bReboot);