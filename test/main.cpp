#include <iostream>
#include "simple_flags.h"
#include <assert.h>
using namespace std;

Define_bool(enabe_special, true, "Enable special version")
Define_int32(width, 14, "Input width")
Define_int32(height, 123, "Input height")
Define_int32(length, 999, "Input length")
Define_string(name, "", "name")
Define_string(password, "", "password")
Define_stringlist(d, "Directories")

int main(int argc, char *argv[])
{
    Flags::parse_args(argc, argv);

    std::cout << Flag_enabe_special << std::endl;
    std::cout << Flag_width << std::endl;
    std::cout << Flag_height << std::endl;
    std::cout << Flag_length << std::endl;
    std::cout << Flag_d.size() << std::endl;
    std::cout << Flag_name << std::endl;
    std::cout << Flag_password << std::endl;

    for (std::size_t i = 0; i < Flag_d.size(); ++i) {
        std::cout << Flag_d[i] << std::endl;
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
