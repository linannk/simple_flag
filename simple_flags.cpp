#include "simple_flags.h"
#include <string.h>
#include <assert.h>
#include <list>
#include <iostream>

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

Implement_Flags_Register(bool)
Implement_Flags_Register(flag_float)
Implement_Flags_Register(flag_int32)
Implement_Flags_Register(flag_uint32)
Implement_Flags_Register(flag_int64)
Implement_Flags_Register(flag_uint64)
Implement_Flags_Register(flag_double)
Implement_Flags_Register(flag_string)
Implement_Flags_Register(flag_stringlist)

#define INSTANTIATE_Flags_Register(type) \
    template void registerFlag<type>(const flag_string &opt, type* optPtr, const char*);


INSTANTIATE_Flags_Register(bool)
INSTANTIATE_Flags_Register(flag_float)
INSTANTIATE_Flags_Register(flag_int32)
INSTANTIATE_Flags_Register(flag_uint32)
INSTANTIATE_Flags_Register(flag_int64)
INSTANTIATE_Flags_Register(flag_uint64)
INSTANTIATE_Flags_Register(flag_double)
INSTANTIATE_Flags_Register(flag_string)
INSTANTIATE_Flags_Register(flag_stringlist)

inline bool is_false_key(const char* key)
{
    const char* true_keys[] = {
        "true" ,
        "True" ,
        "TRUE" ,
        "on" ,
        "On" ,
        "ON"
    };
    for (int i = 0; i < sizeof(true_keys) / sizeof(char*); ++i)
    {
        if (0 == strcmp(true_keys[i], key))
        {
            return true;
        }
    }
    return false;
}

inline bool is_true_key(const char* key)
{
    const char* false_keys[] = {
        "false" ,
        "False" ,
        "FALSE" ,
        "off" ,
        "Off" ,
        "OFF"
    };

    for (int i = 0; i < sizeof(false_keys) / sizeof(char*); ++i)
    {
        if (0 == strcmp(false_keys[i], key))
        {
            return true;
        }
    }
    return false;
}

inline bool str_contains(const char* str, char c)
{
	assert(str != NULL);
	const char* s = str;
	while (*s != '\0') {
		if (*s == c) {
			return true;
		}
		++s;
	}
	return false;
}

inline const char* is_separated_with(const char* arg, const char* opt, const char* delimiters)
{
	assert(arg != NULL && opt != NULL && delimiters != NULL);
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

//bool parse_flag_bool(flag_bool* ptr, const char* str) {
//	return false;
//}

bool parse_flag_float(flag_float* ptr, const char* str) {
	*ptr = (float)atof(str);
	return true;
}

bool parse_flag_double(flag_double* ptr, const char* str) {
	*ptr = atof(str);
	return true;
}

bool parse_flag_int16(flag_int16* ptr, const char* str) {
	*ptr = (flag_int16)atoi(str);
	return true;
}

bool parse_flag_int32(flag_int32* ptr, const char* str) {
	*ptr = (flag_int32)atoi(str);
	return true;
}

bool parse_flag_uint32(flag_uint32* ptr, const char* str) {
	*ptr = (flag_uint32)atoi(str);
	return true;
}

bool parse_flag_int64(flag_int64* ptr, const char* str) {
	*ptr = (flag_int64)atoi(str);
	return true;
}

bool parse_flag_uint64(flag_uint64* ptr, const char* str) {
	*ptr = (flag_uint64)atoi(str);
	return true;
}

bool parse_flag_string(flag_string* ptr, const char* str) {
	assert(ptr != NULL && str != NULL);
	*ptr = str;
	return true;
}


int parse_args(int argc, char** argv)
{

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
				else { \
					std::cout << "Warning -- Falg parse : not a valid expression: " << argv[i] << std::endl; \
				} \
			} \
			break; \
		} \
		else if (const char* p = is_separated_with(argv[i], iter->opt.c_str(), "-=")) \
		{ \
			if (!parse_ ## type(iter->optPtr, p)) \
			{ \
				std::cout << "Warning -- Flag parse : not a valid expression: " << argv[i] << std::endl; \
			} \
			else { ++iRet; ++i; } \
			break; \
		} \
	}} while(0)

    int iRet = 0;
	int j = 0;
	int i = 1;
	std::size_t pos = 0;
    while (i < argc) {
		std::cout << "argv : " << argv[i] << std::endl;
		j = i;
        if (0 == strcmp("--help", argv[i]))
        {
			++i;
            Flag_help = true;
        }
		CHECK_ARGC;

		//! bool is special
		for (auto iter = get_s_bool_Flags().begin(); iter != get_s_bool_Flags().end(); ++iter) {
			std::cout << "opt : " << iter->opt << std::endl;
			if (iter->opt == argv[i]) {
				++iRet; ++i;
				if (i < argc) {
					if (is_true_key(argv[i])) {
						*(iter->optPtr) = true;
						++i;
					}
					else if (is_false_key(argv[i])) {
						*(iter->optPtr) = false;
						++i;
					}
					else {
						*(iter->optPtr) = !*(iter->optPtr);
					}
				}
				else {
					*(iter->optPtr) = !*(iter->optPtr);
				}
			}
			else if (const char* p = is_separated_with(argv[i], iter->opt.c_str(), "-=")) {
				++iRet; ++i;
				if (is_true_key(p)) {
					*(iter->optPtr) = true;
				}
				else if (is_false_key(p)) {
					*(iter->optPtr) = false;
				}
				else {
					*(iter->optPtr) = !*(iter->optPtr);
					std::cout << "Warning -- Flags parse : not a valid bool equation!" << std::endl;
				}
			}
		}
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

		//! stringlist is special
		for (auto iter = get_s_flag_stringlist_Flags().begin(); iter != get_s_flag_stringlist_Flags().end(); ++iter)
		{
			if (iter->opt == argv[i])
			{
				++iRet;
				++i;
				for (; i < argc; ++i) {
					if (argv[i][0] == '-') {
						break;
					}
					else {
						iter->optPtr->push_back(argv[i]);
					}
				}
				break;
			}
			else if (const char* p = is_separated_with(argv[i], iter->opt.c_str(), ",")) {
				++iRet;
				++i;
				while (*p != 0) {
					Flags::flag_string tmp;
					while (*p != 0) {
						tmp.push_back(*p++);
						if (*p == ',') {
							++p;
							break;
						}
					}
					if (!tmp.empty()) {
						iter->optPtr->push_back(tmp);
					}
				}
				break;
			}
		}

		if (j == i)
		{
			Flag_unknown_trash.push_back(argv[i]);
			++i;
		}
    }
    return iRet;
}

void print_args_info()
{
    for (std::size_t i = 0; i < get_s_bool_Flags().size(); ++i)
    {
        std::cout << get_s_bool_Flags()[i].comment << std::endl;
    }
}

END_FLAGS_NAMESPACES

bool Flag_help = false;
FLAGS_NAMESPACE::flag_stringlist Flag_unknown_trash;
