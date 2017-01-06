#include <iostream>
#include "simple_flags.h"
#include <assert.h>
using namespace std;

//Define_stringlist(namse, "class names")
//Define_bool(model, false, "")

Define_bool(use_model, false, "")
Define_float(radius, 0.0f, "")
Define_double(pie, 0.0, "")
Define_int32(height, 0, "")
Define_uint32(age, 0, "")
Define_int64(time, 0, "")
Define_uint64(lenght, 0, "")
Define_string(name, "", "")
Define_stringlist(set, "")

int main(int argc, char *argv[])
{
    Flags::parse_args(argc, argv);
    std::cout << Flag_use_model << std::endl;
    std::cout << Flag_name << std::endl;
    std::cout << Flag_radius << std::endl;
    std::cout << Flag_pie << std::endl;
    std::cout << Flag_height << std::endl;
    std::cout << Flag_age << std::endl;
    std::cout << Flag_time << std::endl;
    std::cout << Flag_set.size() << std::endl;
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
