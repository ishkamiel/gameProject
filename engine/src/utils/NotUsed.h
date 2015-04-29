#pragma once

/*
 * Macro to disable variable not used warnings
 * e.g.
 *  int VARIABLE_IS_NOT_USED i = 1;
 */
#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif