#include <iostream>
#include "simple_flags.h"
#include <assert.h>
using namespace std;

Define_bool(test_bool, false, "test bool")
Define_bool(test_bool1, false, "test bool2")
Define_bool_opt(--test-bool-x, Flag_test_bool_x, false, "test bool x")
Define_bool_opt(--test-bool-x2, Flag_test_bool_x2, false, "test bool x")
Define_int32(width, 0, "")
Define_int32(width2, 0, "")
Define_uint32(height, 0, "")
Define_uint32(height2, 0, "")
Define_int64(radius, 0, "")
Define_int64(radius2, 0, "")
Define_float(ratio, 0.0f, "")
Define_float(ratio2, 0.0f, "")
Define_double(pie, 0.0, "")
Define_double(pie2, 0.0, "")
Define_int32_opt(--width-x, Flag_width_x, 0, "")
Define_int32_opt(--width-x2, Flag_width_x2, 0, "")
Define_uint32_opt(--height-x, Flag_height_x, 0, "")
Define_uint32_opt(--height-x2, Flag_height_x2, 0, "")
Define_int64_opt(--radius-x, Flag_radius_x, 0, "")
Define_int64_opt(--radius-x2, Flag_radius_x2, 0, "")
Define_uint64_opt(--ratio-x, Flag_ratio_x, 0, "")
Define_uint64_opt(--ratio-x2, Flag_ratio_x2, 0, "")
Define_float_opt(--value, Flag_value, 0.0, "")
Define_double_opt(--cc, Flag_cc, 0.0, "")
Define_stringlist(names, "")
Define_floatlist(ages, "")
Define_doublelist(times, "")
Define_stringlist_opt(--names-x, Flag_names_x, "")
Define_floatlist_opt(--ages-x, Flag_age_x, "")
Define_doublelist_opt(--times-x, Flag_times_x, "")

int main(int argc, char *argv[])
{

    char* args[] = {
        "app",
        "-test_bool",
        "-test_bool1=ON",
        "--test-bool-x",
        "--test-bool-x2=ON",
        "-width",
        "88",
        "-width2=99",
        "-ratio", "789.9",
        "--ages-x", "1234", "2", "123"
    };

    std::cout << "parsed : " << Flags::parse_args(14, args) << std::endl;
    std::cout << "--help: " << Flag_help << std::endl;
    std::cout << Flag_test_bool << std::endl;
    std::cout << Flag_test_bool1 << std::endl;
    std::cout << Flag_test_bool_x << std::endl;
    std::cout << Flag_test_bool_x2 << std::endl;
    std::cout << Flag_width << std::endl;
    std::cout << Flag_width2 << std::endl;
    std::cout << Flag_ratio << std::endl;
    for (std::size_t i = 0; i < Flag_age_x.size(); ++i) {
        std::cout << Flag_age_x[i] << std::endl;
    }
    return 0;
}



//! Define_XXX

//! Boolean
//! -switch
//! -switch [ON|On|on|OFF|Off|off|TRUE|True|true|FALSE|False|false]
//! -switch-[ON|On|on|OFF|Off|off|TRUE|True|true|FALSE|False|false]
//! -switch=[ON|On|on|OFF|Off|off|TRUE|True|true|FALSE|False|false]

//! float
//! -key expression
//! -key=expression
//! -key-expression

//! string
//! -key expression
//! -key=expression
//! -key-expression

//! stringlist
//! -key expression1 expression2 ...
//! -key,expression1,expression2,expression3,...

//! reserved
//! --help

//! Flag_unknown_trash
//!

//! Define_XXX_ex
//! Boolean
//! --switch
//! --switch 

//! Self define opt, and flag
//! Define_XXX_opt(opt, flag, def, comment)
//! Define_bool_opt(--whole-time, FlagWholeTime, false, "Use the whole time?")
//! cout << FlagWholeTime << std::endl;
