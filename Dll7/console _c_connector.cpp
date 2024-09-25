#include "pch.h"

#include <cstdlib>
#include "dll7.h"
#include "console.h"


extern "C" {

    static CONSOLE* CONSOLE_instance = NULL;

    void lazyCONSOLE() {
        if (CONSOLE_instance == NULL) {
            CONSOLE_instance = new CONSOLE();
        }
    }

    void CONSOLE_init(const char* name) {
        lazyCONSOLE();
        // CONSOLE_instance->init(name);
    }

    int CONSOLE_test(char* key,
        char* x_amz_credential,
        char* x_amz_algorithm,
        char* x_amz_date,
        char* encoded,
        char* x_amz_signature,
        char* x_amz_security_token,
        char* x_amz_storage_class,
        char* bucket_key,
        char* file_path)
    {
        return CONSOLE_instance->run_segment(
            key,
            x_amz_credential,
            x_amz_algorithm,
            x_amz_date,
            encoded,
            x_amz_signature,
            x_amz_security_token,
            x_amz_storage_class,
            bucket_key,
            file_path);

    }
}
