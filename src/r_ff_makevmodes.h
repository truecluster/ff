/*
# R-C layer of ff: defining vmodes and making all vmode methods
# (c) 2007 Jens Oehlschägel
# Licence: GPL2
# Provided 'as is', use at your own risk
# Created: 2007-08-24
# Last changed: 2007-11-29
*/

/* --- make logical type functions --- */
#if VMODE_COMPILE_BOOLEAN
  #define VMODE_NAME    boolean
  #define VMODE_FFNAME  boolean
  #define VMODE_FFMODE  1
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int     // Rboolean gives an compiler error
  #define VMODE_RTYPE   LGLSXP
  #define VMODE_ACCESS  LOGICAL
  #define VMODE_COERCE  asLogical
  #define VMODE_INIT    FALSE
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif

/* --- make logical type functions --- */
#if VMODE_COMPILE_LOGICAL
  #define VMODE_NAME    logical
  #define VMODE_FFNAME  logical
  #define VMODE_FFMODE  2
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int     // Rboolean gives an compiler error
  #define VMODE_RTYPE   LGLSXP
  #define VMODE_ACCESS  LOGICAL
  #define VMODE_COERCE  asLogical
  #define VMODE_INIT    FALSE
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif


/* --- make quad type functions --- */
#if VMODE_COMPILE_QUAD
  #define VMODE_NAME    quad
  #define VMODE_FFNAME  quad
  #define VMODE_FFMODE  3
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int
  #define VMODE_RTYPE   INTSXP
  #define VMODE_ACCESS  INTEGER
  #define VMODE_COERCE  asInteger
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif


/* --- make nibble type functions --- */
#if VMODE_COMPILE_NIBBLE
  #define VMODE_NAME    nibble
  #define VMODE_FFNAME  nibble
  #define VMODE_FFMODE  4
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int
  #define VMODE_RTYPE   INTSXP
  #define VMODE_ACCESS  INTEGER
  #define VMODE_COERCE  asInteger
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif


/* --- make byte type functions --- */
#if VMODE_COMPILE_BYTE
  #define VMODE_NAME    byte
  #define VMODE_FFNAME  byte
  #define VMODE_FFMODE  5
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int
  #define VMODE_RTYPE   INTSXP
  #define VMODE_ACCESS  INTEGER
  #define VMODE_COERCE  asInteger
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif


/* --- make ubyte type functions --- */
#if VMODE_COMPILE_UBYTE
  #define VMODE_NAME    ubyte
  #define VMODE_FFNAME  ubyte
  #define VMODE_FFMODE  6
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int
  #define VMODE_RTYPE   INTSXP
  #define VMODE_ACCESS  INTEGER
  #define VMODE_COERCE  asInteger
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif


/* --- make short type functions --- */
#if VMODE_COMPILE_SHORT
  #define VMODE_NAME    short
  #define VMODE_FFNAME  short
  #define VMODE_FFMODE  7
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int
  #define VMODE_RTYPE   INTSXP
  #define VMODE_ACCESS  INTEGER
  #define VMODE_COERCE  asInteger
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif


/* --- make ushort type functions --- */
#if VMODE_COMPILE_USHORT
  #define VMODE_NAME    ushort
  #define VMODE_FFNAME  ushort
  #define VMODE_FFMODE  8
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int
  #define VMODE_RTYPE   INTSXP
  #define VMODE_ACCESS  INTEGER
  #define VMODE_COERCE  asInteger
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif



/* --- make integer type functions --- */
#if VMODE_COMPILE_INTEGER
  #define VMODE_NAME    integer
  #define VMODE_FFNAME  integer
  #define VMODE_FFMODE  9
  #define VMODE_CPPTYPE int
  #define VMODE_CTYPE   int
  #define VMODE_RTYPE   INTSXP
  #define VMODE_ACCESS  INTEGER
  #define VMODE_COERCE  asInteger
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif

/* --- make single type functions --- */
#if VMODE_COMPILE_SINGLE
  #define VMODE_NAME    single
  #define VMODE_FFNAME  single
  #define VMODE_FFMODE  10
  #define VMODE_CPPTYPE float
  #define VMODE_CTYPE   double
  #define VMODE_RTYPE   REALSXP
  #define VMODE_ACCESS  REAL
  #define VMODE_COERCE  asReal
  #define VMODE_INIT    0.0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif

/* --- make double type functions --- */
#if VMODE_COMPILE_DOUBLE
  #define VMODE_NAME    double
  #define VMODE_FFNAME  double
  #define VMODE_FFMODE  11         /* this code communicated from R to C for switching data types in r_ff_new and r_ff_open, see ffmode() in vmode.R */
  #define VMODE_CPPTYPE double
  #define VMODE_CTYPE   double
  #define VMODE_RTYPE   REALSXP
  #define VMODE_ACCESS  REAL
  #define VMODE_COERCE  asReal
  #define VMODE_INIT    0.0       /* might help calling ff_<VMODE>_new from r_ff_open when initial value is not available */
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif

/* --- make double type functions --- */
/* easy on C++ side but more difficult on R/C side (Rcomplex is a struct) */
#if VMODE_COMPILE_COMPLEX
  #define VMODE_NAME    complex
  #define VMODE_FFNAME  complex
  #define VMODE_FFMODE  12
  #define VMODE_CTYPE   Rcomplex    // xx struct
  #define VMODE_RTYPE   CPLXSXP
  #define VMODE_ACCESS  COMPLEX
  #define VMODE_COERCE  asComplex
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif

/* --- make raw type functions --- */
#if VMODE_COMPILE_RAW
  #define VMODE_NAME    raw
  #define VMODE_FFNAME  raw
  #define VMODE_FFMODE  13
  #define VMODE_CPPTYPE unsigned char
  #define VMODE_CTYPE   unsigned char /* Rbyte */
  #define VMODE_RTYPE   RAWSXP
  #define VMODE_ACCESS  RAW
  #define VMODE_COERCE  asRaw
  #define VMODE_INIT    0
  #include "r_ff_addgetset.h"
  #if FF_SYMMXTENSIONS_AVAILABLE
    #include "x_r_ff_addgetset.h"
  #endif
  #undef VMODE_NAME
  #undef VMODE_FFNAME
  #undef VMODE_FFMODE
  #undef VMODE_CPPTYPE
  #undef VMODE_CTYPE
  #undef VMODE_RTYPE
  #undef VMODE_ACCESS
  #undef VMODE_COERCE
  #undef VMODE_INIT
#endif



