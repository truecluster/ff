/*
# R-C layer of ff
# (c) 2007 Jens Oehlschägel
# Licence: GPL2
# Provided 'as is', use at your own risk
# Created: 2007-08-24
# Last changed: 2007-11-29
*/

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include "config.h"
#include "ff.h"

#define VMODE_COMPILE_LOGICAL 1
#define VMODE_COMPILE_INTEGER 1
#define VMODE_COMPILE_DOUBLE 1
#define VMODE_COMPILE_RAW 1
#define VMODE_COMPILE_COMPLEX 0

#if FF_XTENSIONS_AVAILABLE
  #define VMODE_COMPILE_BOOLEAN 1
  #define VMODE_COMPILE_QUAD 1
  #define VMODE_COMPILE_NIBBLE 1
  #define VMODE_COMPILE_BYTE 1
  #define VMODE_COMPILE_UBYTE 1
  #define VMODE_COMPILE_SHORT 1
  #define VMODE_COMPILE_USHORT 1
  #define VMODE_COMPILE_SINGLE 1
#else
  #define VMODE_COMPILE_BOOLEAN 0
  #define VMODE_COMPILE_QUAD 0
  #define VMODE_COMPILE_NIBBLE 0
  #define VMODE_COMPILE_BYTE 0
  #define VMODE_COMPILE_UBYTE 0
  #define VMODE_COMPILE_SHORT 0
  #define VMODE_COMPILE_USHORT 0
  #define VMODE_COMPILE_SINGLE 0
#endif

#define asRaw(x) RAW(x)[0]

/* { --- forward declarations ------------------------------------------------ */

/* non-exported helper functions */


SEXP     getListElement(SEXP list, char *str);
Rboolean setListElement(SEXP list, char *str, SEXP elmt);

Rboolean     next_packed(int *i, int *v, int *j, int *k, int *n, int* seqlen, int* seqval, int seqsize);
Rboolean next_positive_negpacked(
          int *I, int N, int *i, int *v, int *j, int *k, int *n, int* seqlen, int* seqval, int seqsize);
Rboolean next_positive_neg(
          int *I, int N, int *neg, int *ineg, int* index);

/* utility functions */


SEXP r_ff_xtensions_available(void);
SEXP r_ff_symmxtensions_available(void);
SEXP r_ff_getpagesize(void);
SEXP r_ff_int_check_ascending(SEXP x);
SEXP r_ff_int_check_descending(SEXP x);
SEXP r_ff_int_rle(SEXP x);


/* ff functions */

SEXP r_ff_geterror(SEXP ff_);
SEXP r_ff_geterrstr(SEXP ff_);

SEXP r_ff_ffmode_implemented(SEXP ffmode);

SEXP r_ff_new(SEXP name, SEXP ffmode, SEXP initval, SEXP len, SEXP pagesize, SEXP ro, SEXP autoflush
, SEXP createNew  // Martijn Schuemie for zero row ff
);
SEXP r_ff_open(SEXP ff_, SEXP ffmode, SEXP ro, SEXP autoflush);
SEXP r_ff_is_open(SEXP ff_);
SEXP r_ff_close(SEXP ff_);
SEXP r_ff_delete(SEXP ff_);

SEXP r_ff_maxlength(SEXP ff_); /* not used because maxlength stored in physical attributes */

#include "r_ff_methoddeclaration.h"
#if FF_SYMMXTENSIONS_AVAILABLE
  #include "x_r_ff_methoddeclaration.h"
#endif

/* } --- forward declarations ------------------------------------------------ */
