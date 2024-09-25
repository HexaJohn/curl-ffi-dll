// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DLL7_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DLL7_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLL7_EXPORTS
#define DLL7_API __declspec(dllexport)
#else
#define DLL7_API __declspec(dllimport)
#endif

/*
// This class is exported from the dll
class DLL7_API CDll7 {
public:
	CDll7(void);
	// TODO: add your methods here.
};
*/

/*
#pragma once
#ifndef CONSOLE_C_CONNECTOR_H 
#define CONSOLE_C_CONNECTOR_H 

#ifdef __cplusplus
extern "C" {
#endif

	void CONSOLE_init(const char* echo);

#ifdef __cplusplus
}
#endif


#endif
*/

struct ExpandedPolicy
{
    char* key;
    char* x_amz_credential;
    char* x_amz_algorithm;
    char* x_amz_date;
    char* encoded;
    char* x_amz_signature;
    char* x_amz_security_token;
    char* x_amz_storage_class;
};


extern "C" DLL7_API void CONSOLE_init(const char* echo);

extern "C" DLL7_API int CONSOLE_test(
    char* key,
    char* x_amz_credential,
    char* x_amz_algorithm,
    char* x_amz_date,
    char* encoded,
    char* x_amz_signature,
    char* x_amz_security_token,
    char* x_amz_storage_class,
    char* bucket_key,
    char* file_path);

extern "C" DLL7_API int nDll7;

extern "C" DLL7_API int fnDll7(void);

extern "C" DLL7_API struct ExpandedPolicy CONSOLE_create_policy(
char *key,
char *x_amz_credential,
char *x_amz_algorithm,
char *x_amz_date,
char *encoded,
char *x_amz_signature,
char *x_amz_security_token,
char *x_amz_storage_class);