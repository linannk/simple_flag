#include <iostream>
#include "simple_flags.h"
using namespace std;

Define_bool(c, false, "Use compatible cpu instruction mode")
Define_bool(O3, false, "Optimize level 3")
Define_bool(SSE, false, "Use SSE instruction")
Define_float(ratio, 0.0f, "Ratio")
Define_float(radius, 0.0f, "Radius")
Define_string(name, "", "name")
Define_stringlist(set, "set-set")
Define_stringlist(Wl, "Warning flag")
Define_bool_ex(mode, false, "Extra mode")
Define_bool_ex(no_defined, false, "")

int main(int argc, char *argv[])
{
    Flags::parse_args(argc, argv);
	cout << "--mode: " << Flag_mode << std::endl;
	cout << "--no_defined : " << Flag_no_defined << std::endl;
    return 0;
}



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