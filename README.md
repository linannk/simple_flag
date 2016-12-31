# Overview
This is a simple project
It helps to create application with rich CLI

# Guide
!.Add simple_flags.h and simple_flags.cpp to you project or wherever you access its interface.
2.Define your cli options, Use Define_* macro or Define_*_ex maxro
3.use Flag_xxx use access your option
## Examples:
^^^C++
#include <simple_flags.h>
Define_bool(use_compatable_mode, false, "Use compatable mode, Use SSE CPU instruction")
int main(int argc, char** argv) {
	Falgs::parse_args(argc, argv);
	
	//! Flag_use_compatable_mode
	return 0;
	}
C++^^^


