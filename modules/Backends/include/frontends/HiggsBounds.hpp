/* 
 * Frontend for HiggsBounds backend
 * 
 * Last modified:
 * Christopher Rogan 2014-08-29
 */

/* Specify the path to the shared library along with a backend name. */

#define LIBPATH      "Backends/lib/libHB.so"
#ifdef BACKENDRENAME
  #define BACKENDNAME BACKENDRENAME
#else
  #define BACKENDNAME HiggsBounds
#endif
#define VERSION 4.1
#define SAFE_VERSION 4_1

/* The following macro loads the library (using dlmopen) in LIBPATH 
 * when this header file is included somewhere. */

LOAD_LIBRARY

/* Next we use macros BE_VARIABLE and BE_FUNCTION to load pointers 
 * (using dlsym) to the variables and functions within the library.
 *  
 * The macros also set up a minimal interface providing 'get/set'
 * functions for the library variables and function pointers 
 * for the library functions.
 *  
 * These functions are then wrapped in functors that the core can connect 
 * to the modules via the rollcall system */
 
/* Syntax for BE_FUNCTION:
 * BE_FUNCTION([choose function name], [type], [arguement types], "[exact symbol name]", "[choose capability name]")
 * 
 * The last argument (capability name) is optional. 
 * If left out (as done below) it will default to "[backend name]_[function name]_capability"
 * (e.g. "LibFirst_initialize_capability")  */

BE_FUNCTION(initialize_HiggsBounds_int, void, (int&, int&, int&), "initialize_higgsbounds_int_", "initialize_HiggsBounds_int")
BE_FUNCTION(run_HiggsBounds_classic, void, (double&, int&, double&, int&), "run_higgsbounds_classic_", "run_HiggsBounds_classic")
BE_FUNCTION(HiggsBounds_input_SLHA, void, (const char&), "higgsbounds_input_slha_", "HiggsBounds_input_SLHA")
BE_FUNCTION(finish_HiggsBounds, void, (), "finish_higgsbounds_", "finish_HiggsBounds")
BE_FUNCTION(HiggsBounds_set_mass_uncertainties, void, (double*, double*), "higgsbounds_set_mass_uncertainties_", "HiggsBounds_set_mass_uncertainties")

// LEP chisq extension specific
BE_FUNCTION(initialize_HiggsBounds_chisqtables, void, (), "initialize_higgsbounds_chisqtables_", "initialize_HiggsBounds_chisqtables")
BE_FUNCTION(HB_calc_stats, void, (double&, double&, double&, int&), "hb_calc_stats_", "HB_calc_stats")
BE_FUNCTION(finish_HiggsBounds_chisqtables, void, (), "finish_higgsbounds_chisqtables_","finish_HiggsBounds_chisqtables")

BE_INI_FUNCTION{}
DONE

// Undefine macros to avoid conflict with other backends
#include "backend_undefs.hpp"
