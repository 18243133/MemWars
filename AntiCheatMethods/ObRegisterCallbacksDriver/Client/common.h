#pragma once

#pragma warning (disable: 4201) // nonstandard extension used : nameless struct/union

#include <windows.h>
#include <stdio.h>
#include "shared.h"

//
// Logging support macros.
//
// LOG_INFO
// LOG_INFO_FAILURE
// LOG_PASSED
// LOG_ERROR
//

#define DEBUG

#ifdef DEBUG
#define LOG_INFO(fmt, ...)         \
    _tprintf(_T("%hs: ") fmt, __FUNCTION__, __VA_ARGS__);_tprintf(_T("\n"));
#define LOG_INFO_FAILURE(fmt, ...) \
    _tprintf(_T("ReportFailure %hs: ") fmt, __FUNCTION__, __VA_ARGS__);_tprintf(_T("\n"));

#define LOG_PASSED(fmt, ...)       \
    _tprintf(_T("\n!!!PASSED: %hs (%hs:%u): ") fmt, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);_tprintf(_T("\n"));
#define LOG_ERROR(fmt, ...)        \
    _tprintf(_T("\n!!!FAILED: %hs (%hs:%u): ") fmt, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); _tprintf(_T("\n"));

#else

#define LOG_INFO(FormatString, ...)
    // std::cout << (wchar_t*)FormatString << std::endl;//printf(FormatString);
#define LOG_INFO_FAILURE(FormatString, ...) 

#define LOG_PASSED(FormatString, ...)      
#define LOG_ERROR(FormatString, ...)   

#endif


extern HANDLE TcDeviceHandle;

BOOL TcInitialize();
BOOL TcUnInitialize();
BOOL TcCleanupSCM();

BOOL TcInstallDriver();

BOOL TcUninstallDriver();

BOOL TcRemoveProtection ();

BOOL TcProcessName (
    _In_ int argc,
    _In_reads_(argc) LPCWSTR argv[],
    _In_ ULONG ulOperation
);

BOOL TcUnprotectCallback ();

BOOL TcProcessNameCallback (
    _In_reads_(NAME_SIZE+1) PCWSTR  pnametoprotect,
    _In_ ULONG ulOperation
);

//
// Utility functions
//

BOOL TcInitializeGlobals();
BOOL TcLoadDriver();
BOOL TcUnloadDriver();

BOOL TcCreateService();
BOOL TcDeleteService();
BOOL TcStartService();
BOOL TcStopService();

BOOL TcOpenDevice();
BOOL TcCloseDevice();