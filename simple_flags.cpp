#include "simple_flags.h"
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <list>
#include <iostream>
#include <string>

BEGIN_FLAGS_NAMESPACES
using std::vector;
using std::string;

template<typename T>
class OptionInfo {
public:
    std::string opt;
    std::string comment;
    T* optPtr;
};

template<typename T>
void registerFlag(const flag_string &opt, T* optPtr, std::string& comment) {}

#define Implement_Flags_Register(type)                                                            \
    static vector<OptionInfo<type>>& get_s_## type ##_Flags() {                                   \
        static vector<OptionInfo<type>> s_ ## type ##_Flags;                                      \
        return s_## type ## _Flags;                                                               \
    }                                                                                             \
    template<> void registerFlag<type>(const flag_string &opt, type* optPtr, const char* comment) \
    {                                                                                             \
        get_s_##type##_Flags().push_back(OptionInfo<type>{opt, comment, optPtr});                 \
    }

Implement_Flags_Register(flag_bool)
Implement_Flags_Register(flag_float)
Implement_Flags_Register(flag_int32)
Implement_Flags_Register(flag_uint32)
Implement_Flags_Register(flag_int64)
Implement_Flags_Register(flag_uint64)
Implement_Flags_Register(flag_double)
Implement_Flags_Register(flag_string)

Implement_Flags_Register(flag_stringlist)
Implement_Flags_Register(flag_boollist)
Implement_Flags_Register(flag_int32list)
Implement_Flags_Register(flag_uint32list)
Implement_Flags_Register(flag_int64list)
Implement_Flags_Register(flag_uint64list)
Implement_Flags_Register(flag_floatlist)
Implement_Flags_Register(flag_doublelist)

#define INSTANTIATE_Flags_Register(type) \
    template void registerFlag<type>(const flag_string &opt, type* optPtr, const char*);


INSTANTIATE_Flags_Register(flag_bool)
INSTANTIATE_Flags_Register(flag_float)
INSTANTIATE_Flags_Register(flag_int32)
INSTANTIATE_Flags_Register(flag_uint32)
INSTANTIATE_Flags_Register(flag_int64)
INSTANTIATE_Flags_Register(flag_uint64)
INSTANTIATE_Flags_Register(flag_double)
INSTANTIATE_Flags_Register(flag_string)

INSTANTIATE_Flags_Register(flag_stringlist)
INSTANTIATE_Flags_Register(flag_int32list)
INSTANTIATE_Flags_Register(flag_uint32list)
INSTANTIATE_Flags_Register(flag_int64list)
INSTANTIATE_Flags_Register(flag_uint64list)
INSTANTIATE_Flags_Register(flag_floatlist)
INSTANTIATE_Flags_Register(flag_doublelist)
INSTANTIATE_Flags_Register(flag_boollist)

//!
//! @brief is_true_key test wheather @code key can be treated as true
//! @param key a pointer to a valid C-string
//! @return if the the string pointed by @code key can be treated as true, it returns true or false.
//! @note @code key must point to a valid C-string or the behavior is undefined.
//! @see is_false_key
inline bool is_true_key(const char* key)
{
    const static char* true_keys[] = {
        "true" ,
        "True" ,
        "TRUE" ,
        "on" ,
        "On" ,
        "ON" ,
        "yes" ,
        "Yes" ,
        "YES"
    };
    for (size_t i = 0; i < sizeof(true_keys) / sizeof(char*); ++i)
    {
        if (0 == strcmp(true_keys[i], key))
        {
            return true;
        }
    }
    return false;
}

//!
//! @brief is_false_key test wheather @code key can be treated as false
//! @param key a pointer to a valid C-string
//! @return if the given param @code key can be treated as false, it returns true or false
//! @note @code key must point to a valid C-string or the behavior is undefined
//! @see is_true_key
inline bool is_false_key(const char* key)
{
    const static char* false_keys[] = {
        "false" ,
        "False" ,
        "FALSE" ,
        "off" ,
        "Off" ,
        "OFF" ,
        "no" ,
        "No" ,
        "NO"
    };

    for (size_t i = 0; i < sizeof(false_keys) / sizeof(char*); ++i)
    {
        if (0 == strcmp(false_keys[i], key))
        {
            return true;
        }
    }
    return false;
}

//!
//! @brief str_contains tests if a C-style string contains a given char
//! @param str a C-style string
//! @param c a char
inline bool str_contains(const char* str, char c)
{
    for (const char* s = str; *s != '\0'; ++s)
    {
        if (*s == c)
        {
            return true;
        }
    }
    return false;
}

//!
//! @brief is_separated_with tests if a string starts with a given string
//! @param arg
//! @param opt
//! @param delimiters
inline const char* is_separated_with(const char* arg, const char* opt, const char* delimiters)
{
    const char* a = arg;
    const char* o = opt;
    for (;;)
    {
        if (*o == '\0' && str_contains(delimiters, *a))
        {
            return a + 1;
        }
        else if (*o != *a)
        {
            return NULL;
        }
        ++a;
        ++o;
    }
    return NULL;
}

inline bool parse_flag_bool(flag_bool* ptr, const char* str) {
    if (is_true_key(str)) {
        *ptr = true;
    }
    else if (is_false_key(str)) {
        *ptr = false;
    }
    else {
        *ptr = !*ptr;
        return false;
    }
    return true;
}

inline bool parse_flag_float(flag_float* ptr, const char* str) {
    char* endptr = nullptr;
    errno = 0;
    float value = strtof(str, &endptr);
    if (endptr == str || endptr == nullptr || errno != 0) {
        return false;
    }
    *ptr = value;
    return true;
}

inline bool parse_flag_double(flag_double* ptr, const char* str) {
    char* endptr = nullptr;
    errno = 0;
    double value = strtod(str, &endptr);
    if (endptr == str || endptr == nullptr || errno != 0) {
        return false;
    }
    *ptr = value;
    return true;
}

inline bool parse_flag_int32(flag_int32* ptr, const char* str) {
    char* endptr = nullptr;
    errno = 0;
    long value = strtol(str, &endptr, 10);
    if (endptr == str || endptr == nullptr || errno != 0) {
        return false;
    }
    *ptr = value;
    return true;
}

inline bool parse_flag_uint32(flag_uint32* ptr, const char* str) {
    char* endptr = nullptr;
    errno = 0;
    unsigned long value = strtoul(str, &endptr, 10);
    if (endptr == str || endptr == nullptr || errno != 0) {
        return false;
    }
    *ptr = value;
    return true;
}

inline bool parse_flag_int64(flag_int64* ptr, const char* str) {
    char* endptr = nullptr;
    errno = 0;
    long long value = strtoll(str, &endptr, 10);
    if (endptr == str || endptr == nullptr || errno != 0) {
        return false;
    }
    *ptr = value;
    return true;
}

inline bool parse_flag_uint64(flag_uint64* ptr, const char* str) {
    char* endptr = nullptr;
    errno = 0;
    unsigned long long value = strtoull(str, &endptr, 10);
    if (endptr == str || endptr == nullptr || errno != 0) {
        return false;
    }
    *ptr = value;
    return true;
}

inline bool parse_flag_string(flag_string* ptr, const char* str) {
    if (str[0] == '-')
    {
        return false;
    }
    *ptr = str;
    return true;
}

inline bool parse_flag_stringlist(flag_stringlist* ptr, const char* p) {
    if (p[0] == '-') {
        return false;
    }
    else {
        ptr->push_back(p);
        return true;
    }
}

inline void parse_split_flag_stringlist(flag_stringlist* ptr, const char* p)
{
    flag_string tmp;
    while (*p != '\0') {
        do {
            if (*p == ',') {
                ++p;
                break;
            }
            else {
                tmp.push_back(*p);
                ++p;
            }
        } while (*p != '\0');
        if (!tmp.empty()) {
            ptr->push_back(tmp);
            tmp.clear();
        }
    }
}

inline bool parse_flag_boollist(flag_boollist* ptr, const char* p) {
    if (is_true_key(p)) {
        ptr->push_back(true);
    }
    else if (is_false_key(p)) {
        ptr->push_back(false);
    }
    else {
        return false;
    }
    return true;
}

inline void parse_split_flag_boollist(flag_boollist* ptr, const char* p) {
    flag_string tmp;
    while (*p != '\0') {
        do {
            if (*p == ',') {
                ++p;
                break;
            }
            else {
                tmp.push_back(*p);
                ++p;
            }
        } while (*p != '\0');
        if (!tmp.empty()) {
            if (is_true_key(tmp.c_str())) {
                ptr->push_back(true);
            }
            else if (is_false_key(tmp.c_str())) {
                ptr->push_back(false);
            }
            else {
                std::cout << "Warning -- Flag parse: Invalid bool expression" << std::endl;
            }
            tmp.clear();
        }
    }
}

inline bool parse_flag_floatlist(flag_floatlist* ptr, const char* p) {
    char* endptr = nullptr;
    errno = 0;
    float value = strtof(p, &endptr);
    if (endptr != p && errno == 0 && endptr != nullptr) {
        ptr->push_back(value);
        return true;
    }
    return false;
}

inline void parse_split_flag_floatlist(flag_floatlist* ptr, const char* p) {
    char* endptr = nullptr;
    float value = 0.0f;
    while (*p != '\0') {
        errno = 0;
        endptr = nullptr;
        value = strtof(p, &endptr);
        if (errno != 0 || endptr == nullptr) {
            do {
                if (*p == ',') {
                    ++p;
                    break;
                }
                ++p;
            } while (*p != '\0');
        }
        else {
            ptr->push_back(value);
            p = endptr;
        }
    }
}

inline bool parse_flag_doublelist(flag_doublelist* ptr, const char* p) {
    char* endptr = NULL;
    errno = 0;
    double value = strtod(p, &endptr);
    if (endptr != p && errno == 0) {
        ptr->push_back(value);
        return true;
    }
    return false;
}

inline void parse_split_flag_doublelist(flag_doublelist* ptr, const char* p) {
    char* endptr = NULL;
    double value = 0.0;
    std::string tmp;
    while (*p != '\0') {
        do {
            if (*p == ',') {
                ++p;
                break;
            }
            else {
                tmp.push_back(*p);
                ++p;
            }
        } while (*p != '\0');
        if (!tmp.empty()) {
            errno = 0;
            value = strtod(p, &endptr);
            if (errno != 0 || endptr == p || endptr == NULL) {
                std::cout << "Warning -- Flag parse: Invalid float expression" << std::endl;
            }
            else {
                ptr->push_back(value);
            }
            tmp.clear();
        }
    }
}

inline bool parse_flag_int32list(flag_int32list* ptr, const char* p) {
    char* endptr = NULL;
    errno = 0;
    long value = strtol(p, &endptr, 10);
    if (endptr != p && errno == 0 && endptr != NULL) {
        ptr->push_back(value);
        return true;
    }
    return false;
}

inline void parse_split_flag_int32list(flag_int32list* ptr, const char* p) {
    char* endptr = NULL;
    long value = 0;
    std::string tmp;
    while (*p != '\0') {
        do {
            if (*p == ',') {
                ++p;
                break;
            }
            else {
                tmp.push_back(*p);
                ++p;
            }
        } while (*p != '\0');
        if (!tmp.empty()) {
            errno = 0;
            value = strtol(p, &endptr, 10);
            if (errno != 0 || endptr == p) {
                std::cout << "Warning -- Flag parse: Invalid float expression" << std::endl;
            }
            else {
                ptr->push_back(value);
            }
            tmp.clear();
        }
    }
}

inline bool parse_flag_uint32list(flag_uint32list* ptr, const char* p) {
    char* endptr = NULL;
    errno = 0;
    unsigned long value = strtoul(p, &endptr, 10);
    if (endptr != p && errno == 0 && endptr != NULL) {
        ptr->push_back(value);
        return true;
    }
    return false;
}

inline void parse_split_flag_uint32list(flag_uint32list* ptr, const char* p) {
    char* endptr = NULL;
    unsigned long value = 0;
    std::string tmp;
    while (*p != '\0') {
        do {
            if (*p == ',') {
                ++p;
                break;
            }
            else {
                tmp.push_back(*p);
                ++p;
            }
        } while (*p != '\0');
        if (!tmp.empty()) {
            errno = 0;
            value = strtoul(p, &endptr, 10);
            if (errno != 0 || endptr == p || endptr == NULL) {
                std::cout << "Warning -- Flag parse: Invalid float expression" << std::endl;
            }
            else {
                ptr->push_back(value);
            }
            tmp.clear();
        }
    }
}

inline bool parse_flag_uint64list(flag_uint64list* ptr, const char* p) {
    char* endptr = NULL;
    errno = 0;
    unsigned long long value = strtoull(p, &endptr, 10);
    if (endptr != p && errno == 0 && endptr != NULL) {
        ptr->push_back(value);
        return true;
    }
    return false;
}

inline void parse_split_flag_uint64list(flag_uint64list* ptr, const char* p) {
    char* endptr = NULL;
    unsigned long long value = 0;
    std::string tmp;
    while (*p != '\0') {
        do {
            if (*p == ',') {
                ++p;
                break;
            }
            else {
                tmp.push_back(*p);
                ++p;
            }
        } while (*p != '\0');
        if (!tmp.empty()) {
            errno = 0;
            value = strtoull(p, &endptr, 10);
            if (errno != 0 || endptr == p && endptr != NULL) {
                std::cout << "Warning -- Flag parse: Invalid float expression" << std::endl;
            }
            else {
                ptr->push_back(value);
            }
            tmp.clear();
        }
    }
}

inline bool parse_flag_int64list(flag_int64list* ptr, const char* p) {
    char* endptr = NULL;
    errno = 0;
    unsigned long long value = strtoull(p, &endptr, 10);
    if (endptr != p && errno == 0 && endptr != NULL) {
        ptr->push_back(value);
        return true;
    }
    return false;
}

inline void parse_split_flag_int64list(flag_int64list* ptr, const char* p) {
    char* endptr = NULL;
    long long value = 0;
    std::string tmp;
    while (*p != '\0') {
        do {
            if (*p == ',') {
                ++p;
                break;
            }
            else {
                tmp.push_back(*p);
                ++p;
            }
        } while (*p != '\0');
        if (!tmp.empty()) {
            errno = 0;
            value = strtoll(p, &endptr, 10);
            if (errno != 0 || endptr == p || endptr == NULL) {
                std::cout << "Warning -- Flag parse: Invalid float expression" << std::endl;
            }
            else {
                ptr->push_back(value);
            }
            tmp.clear();
        }
    }
}

#define CHECK_ARGC if (i >= argc) break
#define PARSE_COMMON_TYPE(type) do { \
    for (auto iter = get_s_ ## type ## _Flags().begin(); iter != get_s_ ## type ## _Flags().end(); ++iter) \
    { \
        if (iter->opt == argv[i]) { \
            ++iRet; ++i;\
            if (i < argc) { \
                if (parse_ ## type(iter->optPtr, argv[i])) { \
                    ++i; \
                } \
            } \
            break; \
        } \
        else if (const char* p = is_separated_with(argv[i], iter->opt.c_str(), "-=")) \
        { \
            ++iRet; \
            if (!parse_ ## type(iter->optPtr, p)) \
            { \
                std::cout << "Warning -- Flag parse : not a valid expression: " << argv[i] << std::endl; \
            } \
            else { ++i; } \
        	break; \
        } \
    }} while(0)

#define PARSE_BOOL_TYPE(type) do { \
    for (auto iter = get_s_ ## type ## _Flags().begin(); iter != get_s_ ## type ## _Flags().end(); ++iter) \
    { \
        if (iter->opt == argv[i]) { \
            ++iRet; ++i;\
            if (i < argc) { \
                if (parse_ ## type(iter->optPtr, argv[i])) { \
                    ++i; \
                } \
            } \
            else { *iter->optPtr = !*iter->optPtr; } \
            break; \
        } \
        else if (const char* p = is_separated_with(argv[i], iter->opt.c_str(), "-=")) \
        { \
            ++iRet; \
            if (!parse_ ## type(iter->optPtr, p)) \
            { \
                std::cout << "Warning -- Flag parse : not a valid expression: " << argv[i] << std::endl; \
            } \
            else { ++i; } \
            break; \
        } \
    }} while(0)

#define PARSE_LIST_TYPE(type) do { \
    for (auto iter = get_s_ ## type ## _Flags().begin(); iter != get_s_ ## type ## _Flags().end(); ++iter) {\
        if (iter->opt == argv[i]) { \
            ++iRet; ++i; \
            for (; i < argc; ++i) { \
                if (!parse_ ## type(iter->optPtr, argv[i])) { \
                    break; \
                } \
            } \
            break; \
        } \
        else if (const char* p = is_separated_with(argv[i], iter->opt.c_str(), ",")) { \
            ++iRet; ++i; \
            parse_split_ ## type(iter->optPtr, p);\
        } \
    }} while(0)

int parse_args(int argc, char** argv)
{
    return InitAppCmdLine(argc, argv, 0);
}

int InitAppCmdLine(int argc, char ** argv, int flags)
{
    int iRet = 0;
    for (int i = 0, j = 0; i < argc; j = i)
    {
        PARSE_BOOL_TYPE(flag_bool);
        CHECK_ARGC;

        PARSE_COMMON_TYPE(flag_float);
        CHECK_ARGC;

        PARSE_COMMON_TYPE(flag_double);
        CHECK_ARGC;

        PARSE_COMMON_TYPE(flag_string);
        CHECK_ARGC;

        PARSE_COMMON_TYPE(flag_int32);
        CHECK_ARGC;

        PARSE_COMMON_TYPE(flag_uint32);
        CHECK_ARGC;

        PARSE_COMMON_TYPE(flag_int64);
        CHECK_ARGC;

        PARSE_COMMON_TYPE(flag_uint64);
        CHECK_ARGC;

        PARSE_LIST_TYPE(flag_stringlist);
        CHECK_ARGC;

        PARSE_LIST_TYPE(flag_floatlist);
        CHECK_ARGC;

        PARSE_LIST_TYPE(flag_doublelist);
        CHECK_ARGC;

        PARSE_LIST_TYPE(flag_int32list);
        CHECK_ARGC;

        PARSE_LIST_TYPE(flag_int64list);
        CHECK_ARGC;

        PARSE_LIST_TYPE(flag_uint32list);
        CHECK_ARGC;

        PARSE_LIST_TYPE(flag_uint64list);
        CHECK_ARGC;

        if (i == j)
        {
            Flag_trash.push_back(argv[i++]);
        }
    }
    return iRet;
}

int DumpHelpInfo()
{
    return 0;
}

END_FLAGS_NAMESPACES

Define_bool_opt(--help, Flag_help, false, "Dump application command line help information")
FLAGS_NAMESPACE::flag_stringlist Flag_trash;
