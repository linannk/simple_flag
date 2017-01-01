#ifndef SIMPLE_FLAGS_H
#define SIMPLE_FLAGS_H
#include <stdint.h>
#include <vector>
#include <string>

#define FLAGS_NAMESPACE Flags
#define BEGIN_FLAGS_NAMESPACES namespace FLAGS_NAMESPACE {
#define END_FLAGS_NAMESPACES }

BEGIN_FLAGS_NAMESPACES
typedef std::string              flag_string;
typedef std::vector<flag_string> flag_stringlist;
typedef bool                     flag_bool;
typedef float                    flag_float;
typedef double                   flag_double;
typedef int16_t                  flag_int16;
typedef uint16_t                 flag_uint16;
typedef int32_t                  flag_int32;
typedef uint32_t                 flag_uint32;
typedef int64_t                  flag_int64;
typedef uint64_t                 flag_uint64;

int parse_args(int argc, char** argv);
void print_args_info();

template<typename T>
void registerFlag(const flag_string &opt, T* optPtr, const char* comment);

END_FLAGS_NAMESPACES
#define Declare_bool(opt) extern FLAGS_NAMESPACE::flag_bool Flag_ ## opt;
#define Declare_float(opt) extern FLAGS_NAMESPACE::flag_float Flag_ ## opt;
#define Declare_double(opt) extern FLAGS_NAMESPACE::flag_double Flag_ ## opt;
#define Declare_int32(opt) extern FLAGS_NAMESPACE::flag_int32 Flag_ ## opt;
#define Declare_uint32(opt) extern FLAGS_NAMESPACE::flag_uint32 Flag_ ## opt;
#define Declare_int64(opt) extern FLAGS_NAMESPACE::flag_int64 Flag_ ## opt;
#define Declare_uint64(opt) extern FLAGS_NAMESPACE::flag_uint64 Flag_ ## opt;
#define Declare_string(opt) extern FLAGS_NAMESPACE::flag_string Flag_ ## opt;
#define Declare_stringlist(opt) extern FLAGS_NAMESPACE::flag_stringlist Flag_ ## opt;

#define Declare_bool_opt(flag) extern FLAGS_NAMESPACE::flag_bool flag;
#define Declare_float_opt(flag) extern FLAGS_NAMESPACE::flag_float flag;
#define Declare_double_opt(flag) extern FLAGS_NAMESPACE::flag_double flag;
#define Declare_int32_opt(flag) extern FLAGS_NAMESPACE::flag_int32 flag;
#define Declare_uint32_opt(flag) extern FLAGS_NAMESPACE::flag_uint32 flag;
#define Declare_int64_opt(flag) extern FLAGS_NAMESPACE::flag_int64 flag;
#define Declare_uint64_opt(flag) extern FLAGS_NAMESPACE::flag_uint64 flag;
#define Declare_string_opt(flag) extern FLAGS_NAMESPACE::flag_string flag;
#define Declare_stringlist_opt(flag) extern FLAGS_NAMESPACE::flag_stringlist flag;

#define Flag_Connect_Str(x, y) x ## y
#define Flag_To_Str(x) #x

#define Define_ImplementerEx(type, opt, def, comment, opt_prefix, flag_prefix)                                         \
	FLAGS_NAMESPACE::type flag_prefix ## _ ## opt = def;                                                               \
	BEGIN_FLAGS_NAMESPACES	                                                                                           \
	class type ## _Flag_Register_ ## flag_prefix ## _ ## opt {                                                         \
	public:                                                                                                            \
		type ## _Flag_Register_ ## flag_prefix ## _ ## opt() {                                                         \
			registerFlag<type>(Flag_To_Str(opt_prefix ## opt), &flag_prefix ## _ ## opt, comment);                     \
		}	                                                                                                           \
	};                                                                                                                 \
	static type ## _Flag_Register_ ## flag_prefix ## _ ## opt s_flag_## flag_prefix ## _ ## opt ## _object;            \
	END_FLAGS_NAMESPACES

#define Define_ImplementerOpt(type, opt, flag, def, comment)                                 \
	FLAGS_NAMESPACE::type flag = def;                                                        \
	BEGIN_FLAGS_NAMESPACES                                                                   \
	class type ## _Flag_Register_ ## flag ## _ {                                             \
	public:                                                                                  \
		type ## _Flag_Register_ ## flag ## _() {                                             \
			registerFlag<type>(Flag_To_Str(opt), &flag, comment);                            \
		}                                                                                    \
	};                                                                                       \
	static type ## _Flag_Register_ ## flag ## _  type ## _Flag_Register_ ## flag ## _object; \
	END_FLAGS_NAMESPACES


#define Define_Implementer(type, opt, def, comment)                            \
    FLAGS_NAMESPACE::type Flag_ ## opt = def;                                  \
    BEGIN_FLAGS_NAMESPACES                                                     \
    class type ## _Flag_Register_ ## opt {                                     \
    public:                                                                    \
        type ## _Flag_Register_ ## opt() {                                     \
            registerFlag<type>(Flag_To_Str(- ## opt), &Flag_ ## opt, comment); \
        }                                                                      \
    };                                                                         \
	static type ## _Flag_Register_ ## opt s_flag_ ## opt ## _object;           \
    END_FLAGS_NAMESPACES

#define Define_bool(opt, def, comment) \
    Define_Implementer(flag_bool, opt, def, comment)

#define Define_float(opt, def, comment) \
    Define_Implementer(flag_float, opt, def, comment)

#define Define_double(opt, def, comment) \
    Define_Implementer(flag_double, opt, def, comment)

#define Define_int32(opt, def, comment) \
    Define_Implementer(flag_int32, opt, def, comment)

#define Define_uint32(opt, def, comment) \
    Define_Implementer(flag_uint32, opt, def, comment)

#define Define_int64(opt, def, comment) \
    Define_Implementer(flag_int64, opt, def, comment)

#define Define_uint64(opt, def, comment) \
    Define_Implementer(flag_uint64, opt, def, comment)

#define Define_string(opt, def, comment)                                        \
    FLAGS_NAMESPACE::flag_string Flag_ ## opt = def;                            \
    BEGIN_FLAGS_NAMESPACES                                                      \
    class flag_string ## _Flag_Register_ ## opt {                               \
    public:                                                                     \
        flag_string ## _Flag_Register_ ## opt() {                               \
            registerFlag(Flag_To_Str(- ## opt), &Flag_ ## opt, comment);        \
        }                                                                       \
    };                                                                          \
	static flag_string ## _Flag_Register_ ## opt s_flag_ ## opt ## _object;     \
    END_FLAGS_NAMESPACES

#define Define_stringlist(opt, comment)                                              \
    FLAGS_NAMESPACE::flag_stringlist Flag_ ## opt;                                   \
    BEGIN_FLAGS_NAMESPACES                                                           \
    class flag_stringlist ## _Flag_Register_ ## opt {                                \
    public:                                                                          \
        flag_stringlist ## _Flag_Register_ ## opt() {                                \
            registerFlag(Flag_To_Str(- ## opt), &Flag_ ## opt, comment);             \
        }                                                                            \
    };                                                                               \
	static flag_stringlist ## _Flag_Register_ ## opt s_flag_ ## opt ## _object;      \
    END_FLAGS_NAMESPACES


#define Define_bool_ex(opt, def, comment) \
	Define_ImplementerEx(flag_bool, opt, def, comment, --, Flag)

#define Define_float_ex(opt, def, comment) \
	Define_ImplementerEx(flag_float, opt, def, comment, --, Flag)

#define Define_double_ex(opt, def, comment) \
	Define_ImplementerEx(flag_double, opt, def, comment, --, Flag)

#define Define_int32_ex(opt, def, comment) \
	Define_ImplementerEx(flag_int32, opt, def, comment, --, Flag)

#define Define_uint32_ex(opt, def, comment) \
	Define_ImplementerEx(flag_uint32, opt, def, comment, --, Flag)

#define Define_int64_ex(opt, def, comment) \
	Define_ImplementerEx(flag_int64, opt, def, comment, --, Flag)

#define Define_uint64_ex(opt, def, comment) \
	Define_ImplementerEx(flag_uint64, opt, def, comment, --, Flag)

#define Define_string_ex(opt, def, comment) \
	Define_ImplementerEx(flag_string, opt, def, comment, --, Flag)

#define Define_stringlist_ex(opt, comment)                                           \
    FLAGS_NAMESPACE::flag_stringlist Flag_ ## opt;                                   \
    BEGIN_FLAGS_NAMESPACES                                                           \
    class flag_stringlist ## _Flag_Register_ ## opt {                                \
    public:                                                                          \
        flag_stringlist ## _Flag_Register_ ## opt() {                                \
            registerFlag(Flag_To_Str(-- ## opt), &Flag_ ## opt, comment);            \
        }                                                                            \
    };                                                                               \
	static flag_stringlist ## _Flag_Register_ ## opt s_flag_ ## opt ## _object;      \
    END_FLAGS_NAMESPACES

#define Define_bool_opt(opt, flag, def, comment) \
	Define_ImplementerOpt(flag_bool, opt, flag, def, comment)

#define Define_float_opt(opt, flag, def, comment) \
	Define_ImplementerOpt(flag_float, opt, flag, def, comment)

#define Define_double_opt(opt, flag, def, comment) \
	Define_ImplementerOpt(flag_double, opt, flag, def, comment)

#define Define_int32_opt(opt, flag, def, comment) \
	Define_ImplementerOpt(flag_int32, opt, flag, def, comment)

#define Define_uint32_opt(opt, flag, def, comment) \
	Define_ImplementerOpt(flag_uint32, opt, flag, def, comment)

#define Define_int64_opt(opt, flag, def, comment) \
	Define_ImplementerOpt(flag_uint64, opt, flag, def, comment)

#define Define_string_opt(opt, flag, def, comment) \
	Define_ImplementerOpt(flag_uint64, opt, flag, def, comment)

#define Define_stringlist_opt(opt, flag, comment)                                                                  \
	FLAGS_NAMESPACE::flag_stringlist flag;                                                                         \
	BEGIN_FLAGS_NAMESPACES                                                                                         \
	class flag_stringlist ## _Flag_Register_ ## _ ## flag ## _ {                                                   \
	public:                                                                                                        \
		flag_stringlist ## _Flag_Register_ ## _ ## flag ## _() {                                                   \
			registerFlag<type>(Flag_To_Str(opt), &flag, comment);                                                  \
		}                                                                                                          \
	};                                                                                                             \
	static flag_stringlist ## _Flag_Register_ ## flag ## _  flag_stringlist ## _Flag_Register_ ## flag ## _object; \
	END_FLAGS_NAMESPACES                                          

Declare_bool(help)
Declare_stringlist(unknown_trash)
#endif // SIMPLE_FLAGS_H

