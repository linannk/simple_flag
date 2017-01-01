#include <iostream>
#include "simple_flags.h"
using namespace std;

Define_bool(use_com, false, "Wheather to use com interface!!!")
Define_int32(age, -1, "input your age")
Define_float(radius, 0.0f, "radius")
Define_string(name, "default", "name")
Define_stringlist(set, "21312")

Define_bool_ex(no_undefine, false, "")

Define_bool_opt(--list-all-file, Flag_all, true, "")

int main(int argc, char *argv[])
{
    Flags::parse_args(argc, argv);
	cout << Flag_use_com << std::endl;
	cout << Flag_age << std::endl;
	cout << "Radius : " << Flag_radius << std::endl;
	cout << "Name : " << Flag_name << std::endl;
	cout << "list_all_file: " << Flag_all << std::endl;
	for (std::string& s : Flag_set) {
		std::cout << s << std::endl;
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
