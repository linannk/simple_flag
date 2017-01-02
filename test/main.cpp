#include <iostream>
#include "simple_flags.h"
using namespace std;

Define_stringlist(namse, "class names")

int main(int argc, char *argv[])
{
    Flags::parse_args(argc, argv);
    for (std::string s : Flag_namse) {
        cout << s << std::endl;
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
