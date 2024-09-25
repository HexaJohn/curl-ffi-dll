#ifndef CONSOLE_H
#define CONSOLE_H


class CONSOLE {
public:
    CONSOLE();

    struct ExpandedPolicy create_policy(
        char* key,
        char* x_amz_credential,
        char* x_amz_algorithm,
        char* x_amz_date,
        char* encoded,
        char* x_amz_signature,
        char* x_amz_security_token,
        char* x_amz_storage_class);
    
    int run_segment(char* key,
        char* x_amz_credential,
        char* x_amz_algorithm,
        char* x_amz_date,
        char* encoded,
        char* x_amz_signature,
        char* x_amz_security_token,
        char* x_amz_storage_class,
        char* bucket_key,
        char* file_path);
};

#endif
