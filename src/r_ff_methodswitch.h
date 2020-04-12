/*
# R-C layer of ff: vmode method switch
# (c) 2007 Jens Oehlschägel
# Licence: GPL2
# Provided 'as is', use at your own risk
# Created: 2007-08-24
# Last changed: 2009-12-12
*/

/* All combinations of
   - getset, get set addgetset addset
   - (single), contiguous, vec, vector, array
   - boolean, logical, quad, nibble, byte, ubyte, short, ushort, integer, single, double, complex
*/


/* { --- r_ff__getset --- replaced by r_ff__getset_vec

SEXP r_ff__getset(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_getset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_getset( ff_, index_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}
SEXP r_ff__get(SEXP ffmode_, SEXP ff_, SEXP index_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_get( ff_, index_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_get( ff_, index_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}
SEXP r_ff__set(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_set( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_set( ff_, index_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}
SEXP r_ff__addgetset(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_addgetset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addgetset( ff_, index_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}
SEXP r_ff__addset(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_addset( ff_, index_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addset( ff_, index_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

   } --- r_ff__getset --- */


/* { --- r_ff__getset_contiguous --- */

SEXP r_ff__getset_contiguous(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_getset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_getset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_getset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_getset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__get_contiguous(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_get_contiguous( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_get_contiguous(  ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_get_contiguous(  ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_get_contiguous(  ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_get_contiguous( ff_, index_, nreturn_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__set_contiguous(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_set_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_set_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_set_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_set_contiguous( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addgetset_contiguous(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_addgetset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_addgetset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_addgetset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addgetset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addset_contiguous(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ = r_ff_single_addset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ = r_ff_double_addset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ = r_ff_double_addset_contiguous(  ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addset_contiguous( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

/* } --- r_ff__getset_contiguous --- */




/* { --- r_ff__getset_vec --- */

SEXP r_ff__getset_vec(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_getset_vec( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__get_vec(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_get_vec( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_get_vec( ff_, index_, nreturn_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__set_vec(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_set_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_set_vec( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addgetset_vec(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addgetset_vec( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addset_vec(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addset_vec( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

/* } --- r_ff__getset_vec --- */


/* { --- r_ff__getset_vector --- */

SEXP r_ff__getset_vector(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_getset_vector( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__get_vector(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_get_vector( ff_, index_, nreturn_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_get_vector( ff_, index_, nreturn_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__set_vector(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_set_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_set_vector( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addgetset_vector(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addgetset_vector( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addset_vector(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addset_vector( ff_, index_, nreturn_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

/* } --- r_ff__getset_vector --- */



/* { --- r_ff__getset_array --- */

SEXP r_ff__getset_array(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP indexdim_, SEXP ffdim_, SEXP ndim_, SEXP nreturn_, SEXP cumindexdim_, SEXP cumffdim_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_getset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__get_array(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP indexdim_, SEXP ffdim_, SEXP ndim_, SEXP nreturn_, SEXP cumindexdim_, SEXP cumffdim_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_get_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__set_array(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP indexdim_, SEXP ffdim_, SEXP ndim_, SEXP nreturn_, SEXP cumindexdim_, SEXP cumffdim_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_set_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addgetset_array(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP indexdim_, SEXP ffdim_, SEXP ndim_, SEXP nreturn_, SEXP cumindexdim_, SEXP cumffdim_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addgetset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

SEXP r_ff__addset_array(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP indexdim_, SEXP ffdim_, SEXP ndim_, SEXP nreturn_, SEXP cumindexdim_, SEXP cumffdim_, SEXP value_)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ret_ = r_ff_boolean_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ret_ = r_ff_logical_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ret_ = r_ff_quad_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ret_ = r_ff_nibble_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ret_ = r_ff_byte_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ret_ = r_ff_ubyte_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ret_ = r_ff_short_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ret_ = r_ff_ushort_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ret_ = r_ff_integer_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ret_ =  r_ff_single_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ret_ =  r_ff_double_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: ret_ =  r_ff_double_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ret_ = r_ff_raw_addset_array( ff_, index_, indexdim_, ffdim_, ndim_, nreturn_, cumindexdim_, cumffdim_, value_); break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }
  return ret_;
}

/* } --- r_ff__getset_array --- */


/* { --- r_ff__sortmerge --- */


SEXP r_ff__sortmerge(
  SEXP ffmode_
, SEXP ff_            /* ff data vector */
, SEXP auxff_         /* auxilliary data vector */
, SEXP left_         /* first R position to be ordered */
, SEXP right_        /* last R position to be ordered */
, SEXP method_       /* 0=mergesort 1=shellsort 2=keysort (the latter not for doubles) */
, SEXP keyrange_      /* NULL, or - for method==2 - vector with 2 elements, 1st is keystart, 2nd is keylength */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
, SEXP mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_ = R_NilValue;

  switch (asInteger(ffmode_)) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 13:
    ret_ = r_ff_integer_sortmerge(
      ffmode_        /* ff data vector */
    , ff_            /* ff data vector */
    , auxff_         /* auxilliary data vector */
    , left_         /* first R position to be ordered */
    , right_        /* last R position to be ordered */
    , method_       /* 0=mergesort 1=shellsort 2=keysort (the latter not for doubles) */
    , keyrange_      /* NULL, or - for method==2 - vector with 2 elements, 1st is keystart, 2nd is keylength */
    , ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
    , mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
    , has_na_       /* logical scalar */
    , na_last_      /* logical scalar */
    , decreasing_   /* logical scalar */
    ); break;
  case 10:
  case 11:
    ret_ =  r_ff_double_sortmerge(
      ffmode_        /* ff data vector */
    , ff_            /* ff data vector */
    , auxff_         /* auxilliary data vector */
    , left_         /* first R position to be ordered */
    , right_        /* last R position to be ordered */
    , method_       /* 0=mergesort 1=shellsort 2=keysort (the latter not for doubles) */
    , ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
    , mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
    , has_na_       /* logical scalar */
    , na_last_      /* logical scalar */
    , decreasing_   /* logical scalar */
    ); break;
  default: error("illegal .ffmode[vmode(ffobj)] for mergeorder (desc) function");
  }

  return ret_;
}


/* } --- r_ff__sortmerge --- */



/* { --- r_ff__ordermerge --- */

SEXP r_ff__ordermerge(
  SEXP ffmode_
, SEXP ff_            /* ff data vector */
, SEXP index_        /* NULL or ff index vector, xx TODO we can speed up by implementing true internal sorting, internally we currently do always ordering */
, SEXP auxff_         /* auxilliary data vector */
, SEXP auxindex_     /* NULL or auxilliary index vector (needed if index_ given) */
, SEXP left_         /* first R position to be ordered */
, SEXP right_        /* last R position to be ordered */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=keyorder (the latter not for doubles) */
, SEXP keyrange_      /* NULL, or - for method==2 - vector with 2 elements, 1st is keystart, 2nd is keylength */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
, SEXP mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
, SEXP orderindex_   /* logical scalar: shall we reorder index_? (otherwise we simpy write it) */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_ = R_NilValue;

  switch (asInteger(ffmode_)) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 13:
    ret_ = r_ff_integer_ordermerge(
      ffmode_        /* ff data vector */
    , ff_            /* ff data vector */
    , index_        /* NULL or ff index vector, xx TODO we can speed up by implementing true internal sorting, internally we currently do always ordering */
    , auxff_         /* auxilliary data vector */
    , auxindex_     /* NULL or auxilliary index vector (needed if index_ given) */
    , left_         /* first R position to be ordered */
    , right_        /* last R position to be ordered */
    , method_       /* 0=mergeorder 1=shellorder 2=keyorder (the latter not for doubles) */
    , keyrange_      /* NULL, or - for method==2 - vector with 2 elements, 1st is keystart, 2nd is keylength */
    , ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
    , mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
    , orderindex_   /* logical scalar: shall we reorder index_? (otherwise we simpy write it) */
    , has_na_       /* logical scalar */
    , na_last_      /* logical scalar */
    , decreasing_   /* logical scalar */
    ); break;
  case 10:
  case 11:
    ret_ =  r_ff_double_ordermerge(
      ffmode_        /* ff data vector */
    , ff_            /* ff data vector */
    , index_        /* NULL or ff index vector, xx TODO we can speed up by implementing true internal sorting, internally we currently do always ordering */
    , auxff_         /* auxilliary data vector */
    , auxindex_     /* NULL or auxilliary index vector (needed if index_ given) */
    , left_         /* first R position to be ordered */
    , right_        /* last R position to be ordered */
    , method_       /* 0=mergeorder 1=shellorder 2=keyorder (the latter not for doubles) */
    , ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
    , mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
    , orderindex_   /* logical scalar: shall we reorder index_? (otherwise we simpy write it) */
    , has_na_       /* logical scalar */
    , na_last_      /* logical scalar */
    , decreasing_   /* logical scalar */
    ); break;
  default: error("illegal .ffmode[vmode(ffobj)] for mergeorder (desc) function");
  }

  return ret_;
}


/* } --- r_ff__ordermerge --- */



/* { --- r_ff__index_get r_ff__index_set --- */


SEXP r_ff__index_get(SEXP ffmode_
, SEXP baseff_         /* ff input data vector */
, SEXP returnff_        /* ff output data vector */
, SEXP index_        /* ff index data vector */
, SEXP auxindex_     /* NULL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
, SEXP offset_       /* e.g. 1 for R2C */
, SEXP left_         /* left position from where index to e applied */
, SEXP right_        /* right position from where index to e applied */
, SEXP method_       /* 0=mergeorder 1=shellorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 13:
    ret_ =  r_ff_integer_index_get(
      ffmode_
    , baseff_         /* ff input data vector */
    , returnff_        /* ff output data vector */
    , index_        /* ff index data vector */
    , auxindex_     /* NULL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
    , offset_       /* e.g. 1 for R2C */
    , left_         /* left position from where index to e applied */
    , right_        /* right position from where index to e applied */
    , method_       /* 0=mergeorder 1=shellorder */
    , ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
    ); break;
   case 10:
   case 11:
    ret_ =  r_ff_double_index_get(
      ffmode_
    , baseff_         /* ff input data vector */
    , returnff_        /* ff output data vector */
    , index_        /* ff index data vector */
    , auxindex_     /* NULL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
    , offset_       /* e.g. 1 for R2C */
    , left_         /* left position from where index to e applied */
    , right_        /* right position from where index to e applied */
    , method_       /* 0=mergeorder 1=shellorder */
    , ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
    ); break;
  default: error("illegal .ffmode[vmode(ffobj)] for index_get function");
  }
  return ret_;
}

SEXP r_ff__index_set(SEXP ffmode_
, SEXP baseff_         /* ff input data vector */
, SEXP valueff_        /* ff output data vector */
, SEXP index_        /* ff index data vector */
, SEXP auxindex_     /* NULL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
, SEXP offset_       /* e.g. 1 for R2C */
, SEXP left_         /* left position from where index to e applied */
, SEXP right_        /* right position from where index to e applied */
, SEXP method_       /* 0=mergeorder 1=shellorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
)
{
  SEXP ret_ = R_NilValue;
  switch (asInteger(ffmode_)) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 13:
    ret_ =  r_ff_integer_index_set(
      ffmode_
    , baseff_         /* ff input data vector */
    , valueff_        /* ff output data vector */
    , index_        /* ff index data vector */
    , auxindex_     /* NULL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
    , offset_       /* e.g. 1 for R2C */
    , left_         /* left position from where index to e applied */
    , right_        /* right position from where index to e applied */
    , method_       /* 0=mergeorder 1=shellorder */
    , ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
    ); break;
   case 10:
   case 11:
    ret_ =  r_ff_double_index_set(
      ffmode_
    , baseff_         /* ff input data vector */
    , valueff_        /* ff output data vector */
    , index_        /* ff index data vector */
    , auxindex_     /* NULL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
    , offset_       /* e.g. 1 for R2C */
    , left_         /* left position from where index to e applied */
    , right_        /* right position from where index to e applied */
    , method_       /* 0=mergeorder 1=shellorder */
    , ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
    ); break;
  default: error("illegal .ffmode[vmode(ffobj)] for index_set function");
  }
  return ret_;
}

/* } --- r_ff__index_get r_ff__index_set --- */

