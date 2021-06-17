#pragma once
#pragma intrinsic(memcpy,strcpy,strcmp,strlen)
#include <windows.h>
#include <proofofpossessioncookieinfo.h>
// #include <combaseapi.h>

//KERNEL32
#ifdef BOF
WINBASEAPI void *__cdecl MSVCRT$calloc(size_t _NumOfElements, size_t _SizeOfElements);
WINBASEAPI size_t __cdecl MSVCRT$wcslen(const wchar_t *_Str);
WINBASEAPI void __cdecl MSVCRT$free(void *_Memory);
WINBASEAPI int __cdecl MSVCRT$vsnprintf(char * __restrict__ d,size_t n,const char * __restrict__ format,va_list arg);
WINBASEAPI errno_t __cdecl MSVCRT$mbstowcs_s(size_t *pReturnValue, wchar_t * wcstr, size_t smt,const char *mbstr, size_t count);
WINBASEAPI size_t __cdecl MSVCRT$strlen(const char *_Str);

WINBASEAPI int WINAPI KERNEL32$lstrlenW (LPCWSTR lpString);
WINBASEAPI LPWSTR WINAPI KERNEL32$lstrcpynW (LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength);
WINBASEAPI LPWSTR WINAPI KERNEL32$lstrcatW (LPWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI int WINAPI Kernel32$WideCharToMultiByte (UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);
#define intAlloc(size) KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define intFree(addr) KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, addr)
WINBASEAPI void * WINAPI KERNEL32$HeapAlloc (HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
WINBASEAPI BOOL WINAPI KERNEL32$HeapFree (HANDLE, DWORD, PVOID);
WINBASEAPI HANDLE WINAPI KERNEL32$GetProcessHeap();

DECLSPEC_IMPORT HRESULT WINAPI OLE32$CLSIDFromString (LPCOLESTR lpsz, LPCLSID pclsid);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$IIDFromString (LPCOLESTR lpsz, LPIID lpiid);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoInitializeEx (LPVOID pvReserved, DWORD dwCoInit);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoCreateInstance (REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID *ppv);
DECLSPEC_IMPORT void	WINAPI OLE32$CoTaskMemFree(LPVOID pv);

DECLSPEC_IMPORT HRESULT WINAPI COOKIE$GetCookieInfoForUri(LPCWSTR uri, DWORD *cookieInfoCount, ProofOfPossessionCookieInfo **cookieInfo);

#else
#define MSVCRT$calloc calloc
#define MSVCRT$wcslen wcslen
#define MSVCRT$free free
#define MSVCRT$vsnprintf vsnprintf
#define MSVCRT$mbstowcs_s mbstowcs_s
#define MSVCRT$strlen strlen

#define Kernel32$WideCharToMultiByte  WideCharToMultiByte
#define intAlloc(size) KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define intFree(addr) KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, addr)
#define KERNEL32$HeapAlloc  HeapAlloc
#define KERNEL32$HeapFree  HeapFree
#define KERNEL32$GetProcessHeap GetProcessHeap
#define KERNEL32$lstrcpynW  lstrcpynW
#define KERNEL32$lstrcatW  lstrcatW
#define KERNEL32$lstrlenW lstrlenW

#define OLE32$CLSIDFromString CLSIDFromString
#define OLE32$IIDFromString IIDFromString
#define OLE32$CoInitializeEx CoInitializeEx
#define OLE32$CoCreateInstance CoCreateInstance
#define OLE32$CoTaskMemFree CoTaskMemFree

#define COOKIE$GetCookieInfoForUri GetCookieInfoForUri

#define internal_printf printf




#endif
