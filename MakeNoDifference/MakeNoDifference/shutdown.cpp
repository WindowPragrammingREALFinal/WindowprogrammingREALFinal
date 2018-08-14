#include <Windows.h>

typedef long			NTSTATUS, *PNTSTATUS;
#define	NTAPI			__stdcall

#define	STATUS_SUCCESS	0

typedef enum _SHUTDOWN_ACTION {
	ShutdownNoReboot,
	ShutdownReboot,
	ShutdownPowerOff
} SHUTDOWN_ACTION, *PSHUTDOWN_ACTION;

typedef NTSTATUS(NTAPI *NTSHUTDOWNSYSTEM)(
	SHUTDOWN_ACTION ShutdownAction);

typedef NTSTATUS(NTAPI *RTLADJUSTPRIVILEGE)(
	ULONG Privilege,
	BOOL bEnable,
	BOOL bIsCurrentThread,
	PULONG PreviousPrivilege);

typedef enum _SHUTDOWN_METHOD {
	ShutdownNormal,
	ShutdownTimeout,
	ShutdownFastPowerOff
} SHUTDOWN_METHOD;

BOOL InternalAdjustPrivilege(ULONG PrivilegeValue)
{
	//Get Function Pointer : NTDLL!RtlAdjustPrivilege.
	RTLADJUSTPRIVILEGE RtlAdjustPrivilege = (RTLADJUSTPRIVILEGE)
		GetProcAddress(LoadLibrary(L"ntdll.dll"), "RtlAdjustPrivilege");
	//Check if function is existing......
	if (RtlAdjustPrivilege)
	{
		//got it!
		ULONG PreviousPrivilege;
		return (RtlAdjustPrivilege(PrivilegeValue, TRUE, FALSE, &PreviousPrivilege)
			== STATUS_SUCCESS);
	}
	//Maybe Operating System is Win9x.
	return FALSE;
}

BOOL ShutdownSystem(SHUTDOWN_METHOD ShutdownMethod, LPWSTR ShutdownMessage, DWORD ShutdownTimeSec, BOOL bForce, BOOL bReboot)
{
	//Get Function Pointer : NTDLL!NtShutdownSystem.
	NTSHUTDOWNSYSTEM NtShutdownSystem = (NTSHUTDOWNSYSTEM)
		GetProcAddress(LoadLibrary(L"ntdll.dll"), "NtShutdownSystem");
	DWORD dwFlags;
	//SE_SHUTDOWN_PRIVILEGE 0x13
	//Get Shutdown Privilege
	InternalAdjustPrivilege(0x13);
	switch (ShutdownMethod)
	{
	case ShutdownNormal:
		//Shutdown Normally
		dwFlags = EWX_POWEROFF;
		if (bForce) dwFlags |= EWX_FORCE;
		if (bReboot) dwFlags |= EWX_REBOOT;
		if (ExitWindowsEx(dwFlags, 0xFFFFFFFF) == 1)//dwReserved=0xffffffff
		{
			return TRUE;
		}
		//NtShutdownSystem Supported Only in Windows, which is Bulit-On NT-Technology.
		if (!NtShutdownSystem)
		{
			//Because of Windows is Not Bulit-On NT-Technology, Request USER to Power Off.
			WinExec("rundll.exe user.exe,ExitWindows", 0);
			return TRUE;
		}
		return FALSE;
		break;
	case ShutdownTimeout:
		//Use Timeout
		//This Method can be canceled by AbortSystemShutdown().
		//shutdown method is same as ExitWindowsEx().
		return InitiateSystemShutdown(NULL, (LPWSTR)ShutdownMessage, ShutdownTimeSec, bForce,
			bReboot);
		break;
	case ShutdownFastPowerOff:
		//Special Shutdown
		//Call Native API : NtShutdownSystem().
		if (NtShutdownSystem)
		{
			return (NtShutdownSystem(bReboot ? ShutdownReboot : ShutdownPowerOff)
				== STATUS_SUCCESS);
		}
		//Maybe, Operating System is Win9x.
		//Request KRNL386 to Power Off.
		WinExec("rundll.exe krnl386.exe,EXITKERNEL", 0);
		return TRUE;
	}
	return FALSE;
}
