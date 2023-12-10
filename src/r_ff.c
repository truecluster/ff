/*
# R-C layer of ff
# (c) 2007 Jens Oehlschägel (based on previous work by Daniel Adler)
# Licence: GPL2
# Provided 'as is', use at your own risk
# Created: 2007-08-24
# Last changed: 2007-11-29
*/

/* xx TODO add R_CheckUserInterrupt(); */

#include "r_ff.h"
#include "r_file_resize.h"

/* defining and making order methods */

/* { --- R FUNCTION REGISTRATION -------------------------------------------- */

R_CallMethodDef CallEntries[] =
{
 {"ffxtensions", (DL_FUNC) &r_ff_xtensions_available, 0},
 {"ffsymmxtensions", (DL_FUNC) &r_ff_symmxtensions_available, 0},
 {"getpagesize", (DL_FUNC) &r_ff_getpagesize, 0},
 {"geterror", (DL_FUNC) &r_ff_geterror, 1},
 {"geterrstr", (DL_FUNC) &r_ff_geterrstr, 1},
 {"ffmode_implemented",  (DL_FUNC) &r_ff_ffmode_implemented,   1},
 {"new", (DL_FUNC) &r_ff_new,  8}, // Martijn Schuemie for zero row ff
 {"is_open", (DL_FUNC) &r_ff_is_open,  1},
 {"open", (DL_FUNC) &r_ff_open,  4},
 {"close",(DL_FUNC) &r_ff_close, 1},
 {"delete",(DL_FUNC) &r_ff_delete, 1},
 {"maxlength",  (DL_FUNC) &r_ff_maxlength,   1},

/*
 {"getset",    (DL_FUNC) &r_ff__getset,    4},
 {"get",       (DL_FUNC) &r_ff__get,       3},
 {"set",       (DL_FUNC) &r_ff__set,       4},
 {"addgetset", (DL_FUNC) &r_ff__addgetset, 4},
 {"addset",    (DL_FUNC) &r_ff__addset,    4},
*/

 {"getset_contiguous",   (DL_FUNC) &r_ff__getset_contiguous,     5},
 {"get_contiguous",      (DL_FUNC) &r_ff__get_contiguous,        4},
 {"set_contiguous",      (DL_FUNC) &r_ff__set_contiguous,        5},
 {"addgetset_contiguous",(DL_FUNC) &r_ff__addgetset_contiguous,  5},
 {"addset_contiguous",   (DL_FUNC) &r_ff__addset_contiguous,     5},

 {"getset_vec",   (DL_FUNC) &r_ff__getset_vec, 5},
 {"get_vec",      (DL_FUNC) &r_ff__get_vec,    4},
 {"set_vec",      (DL_FUNC) &r_ff__set_vec,    5},
 {"addgetset_vec",(DL_FUNC) &r_ff__addgetset_vec, 5},
 {"addset_vec",   (DL_FUNC) &r_ff__addset_vec, 5},

 {"getset_vector",   (DL_FUNC) &r_ff__getset_vector, 5},
 {"get_vector",      (DL_FUNC) &r_ff__get_vector,    4},
 {"set_vector",      (DL_FUNC) &r_ff__set_vector,    5},
 {"addgetset_vector",(DL_FUNC) &r_ff__addgetset_vector, 5},
 {"addset_vector",   (DL_FUNC) &r_ff__addset_vector, 5},

 {"getset_array",    (DL_FUNC) &r_ff__getset_array,    10},
 {"get_array",       (DL_FUNC) &r_ff__get_array,        9},
 {"set_array",       (DL_FUNC) &r_ff__set_array,       10},
 {"addgetset_array", (DL_FUNC) &r_ff__addgetset_array, 10},
 {"addset_array",    (DL_FUNC) &r_ff__addset_array,    10},

#if FF_SYMMEXTENSIONS_AVAILABLE
 {"getset_symm",   (DL_FUNC) &r_ff__getset_symm, 7},
 {"get_symm",      (DL_FUNC) &r_ff__get_symm,    6},
 {"set_symm",      (DL_FUNC) &r_ff__set_symm,    7},
 {"addgetset_symm",(DL_FUNC) &r_ff__addgetset_symm, 7},
 {"addset_symm",   (DL_FUNC) &r_ff__addset_symm, 7},

 {"subget_symm", (DL_FUNC) &r_ram__get_symm, 6},
 {"subset_symm", (DL_FUNC) &r_ram__set_symm, 8},
#endif

 {"mergeorder", (DL_FUNC) &r_ram_mergeorder, 5},
 {"mergesort",  (DL_FUNC) &r_ram_mergesort, 4},
 {"shellorder", (DL_FUNC) &r_ram_shellorder, 6},
 {"shellsort",  (DL_FUNC) &r_ram_shellsort, 4},
 {"keyorder", (DL_FUNC) &r_ram_keyorder, 6},
 {"keysort",  (DL_FUNC) &r_ram_keysort, 5},
 {"radixorder",  (DL_FUNC) &r_ram_radixorder, 5},
 {"radixsort",  (DL_FUNC) &r_ram_radixsort, 4},
 {"ffsortmerge",  (DL_FUNC) &r_ff__sortmerge, 12},
 {"ffordermerge", (DL_FUNC) &r_ff__ordermerge, 15},
 {"ffkeysort",  (DL_FUNC) &r_ff_integer_keysort, 9},
 {"ffchunkorder", (DL_FUNC) &r_ff_index_chunkorder, 5},
 {"ffindexget", (DL_FUNC) &r_ff__index_get, 10},
 {"ffindexset", (DL_FUNC) &r_ff__index_set, 10},

/* additions by Daniel Adler (under ISC license) */
 {"r_file_resize", (DL_FUNC) &r_file_resize, 2 },

 {NULL, NULL, 0}
};


void R_init_ff(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}

void R_unload_ff(DllInfo *info)
{
}

/* } --- R FUNCTION REGISTRATION -------------------------------------------- */


/* { --- helper functions for getting and setting list elements by name ------------- */

SEXP getListElement(SEXP list, char *str)
{
  SEXP elmt = R_NilValue, names = getAttrib(list, R_NamesSymbol);
  int i;
  for (i = 0; i < length(list); i++)
    if(strcmp(CHAR(STRING_ELT(names, i)), str) == 0) {
      elmt = VECTOR_ELT(list, i);
      break;
    }
  return elmt;
}
Rboolean setListElement(SEXP list, char *str, SEXP elmt)
{
  SEXP names = getAttrib(list, R_NamesSymbol);
  int i;
  for (i = 0; i < length(list); i++)
    if(strcmp(CHAR(STRING_ELT(names, i)), str) == 0) {
      elmt = SET_VECTOR_ELT(list, i, elmt);
      return TRUE;
    }
  return FALSE;
}




/* } --- helper functions for getting and setting list elements by name ---------------- */


/* { --- helper functions for iterating (not consitently used because slower than direct coding) --- */
/* these functions change their arguments !! */
/* returns TRUE when next element is found */
/* yet only used for _symm functions and as a demo in r_ff_double_getset_vector_iterator */
/* xx macroing or inlining ?? */

/* next value in sequence */
Rboolean next_packed(
  int *i         /* MODIFIED: current sequence value moving UP from First-1 to Last-1, initialize with First-1-v */
, int *v         /* MODIFIED: current/last increment, initialize with 0 */
, int *j         /* MODIFIED: current sequence (0..(seqsize-1), j==seqsize if done), initialize with -1 */
, int *k         /* MODIFIED: current instance of increment 0:(n-1), k==n if done, initialize with 0 */
, int *n         /* MODIFIED: current/last number of instances, initialize with 1 */
, int* seqlen    /* vector of numbers of instances */
, int* seqval    /* vector of increments */
, int seqsize    /* number of sequences */
)
{
  //Rprintf(" IN i=%d v=%d j=%d k=%d n=%d seqsize=%d\n",*i,*v,*j,*k,*n,seqsize);
  if ((*k)++<(*n)){
    (*i) += (*v);
  }else{
    if (++(*j)<seqsize){
      (*v)=seqval[(*j)];
      (*n)=seqlen[(*j)];
      (*i) += (*v);
      (*k)=1; /* 0 has already been consumed by this iteration */
    }else{
      //Rprintf("END i=%d v=%d j=%d k=%d n=%d seqsize=%d\n",*i,*v,*j,*k,*n,seqsize);
      return FALSE;
    }
  }
  //Rprintf("OUT i=%d v=%d j=%d k=%d n=%d seqsize=%d\n",*i,*v,*j,*k,*n,seqsize);
  return TRUE;
}


/* find next positive subscript not excluded by a packed negative subscript
   remember negative subscripts are sorted ascending, i.e. abs descending,
   since we need to traverse them abs ascending, we traverse them descending,
*/
Rboolean next_positive_negpacked(
  int *I         /* MODIFIED: current POSITIVE value moving UP from 0:(N-1), I==N if done, initialize with -1 */
, int N          /*           maximum POSITIVE value */
, int *i         /* MODIFIED: current POSITIVE neg sequence value moving UP from -Last-1:-First-1, initialize with -Last-1 */
, int *v         /* MODIFIED: current/last (POSITIVE) increment, initialize with 0 */
, int *j         /* MODIFIED: current sequence moving DOWN from (seqsize-1):0, j==-1 if done, initialize with seqsize */
, int *k         /* MODIFIED: current instance of increment moving DOWN from (*n):1, k==0 if done, initialize with 0 */
, int *n         /* MODIFIED: current/last number of instances, initialize with 0 */
, int* seqlen    /* vector of numbers of instances */
, int* seqval    /* vector of (POSITIVE) increments */
, int seqsize    /* number of sequences NOT NEEDED due to backcounting (but offered) */
)
{
  if ((*j)>=0){ /* neg subscripts not exhausted */
    if (++(*I)<(*i)){
      return TRUE;
    }else{
      /* find next value in (neg) packed sequence that leaves gap for positive subscripts */
      if ((*v)>1){
        if (--(*k) > 0){
          (*i) += (*v);
          (*I)++;
          return TRUE;
        }
      }else if ((*v)==1){ /* make sure that any (*v)==0 trick at loop-beginnings doesn't trick us :-) */
        (*i) += (*k); /* += (*k)*(*v), but since (*v)==1 */
      }
      while((*j)-- > 0){
        (*v) = seqval[(*j)];
        if ((*v)>1){
          (*n) = seqlen[(*j)];
          (*k) = (*n) - 1;
          (*I) = (*i) + 1;
          (*i) += (*v);
          return TRUE;
        }else{
          (*i) += seqlen[(*j)] * (*v);
        }
      }
      /* negative subscripts exhausted, realign (*I) with last suscript not available */
      (*I) = (*i);
    }
  }

  /* negative subscripts exhausted, is there any gap after the last neg. subscript and the end? */
  if (++(*I)<N)
    return TRUE;
  else
    (*I) = N + 1; /* security precaution: don't leave (*I) at a forbidden value */

  return FALSE;
}


/* find next positive subscript not excluded by a non-packed negative subscript
   remember negative subscripts are sorted ascending, i.e. abs descending,
   since we need to traverse them abs ascending, we traverse them descending,
*/
Rboolean next_positive_neg(
  int *I         /* MODIFIED: current POSITIVE value moving UP from 0:(N-1), I==N if done, initialize with -1 */
, int N          /*           maximum POSITIVE value */
, int *neg       /* MODIFIED: current POSITIVE neg sequence value moving UP from -index[nindex-1]-1:-index[0]-1, initialize with -index[nindex-1]-1 */
, int *ineg      /* MODIFIED: current position of neg subscript in index moving down from (nindex-1):0, ineg==-1 if done, initialize with nindex-1 */
, int* index     /* vector of negative subscripts (R-counting) */
)
{
  //Rprintf("  IN I=%d N=%d neg=%d ineg=%d\n",*I,N,*neg,*ineg);
  if ((*ineg)>=0){ /* neg subscripts not exhausted */
    if (++(*I)<(*neg)){
      //Rprintf("OUT1 I=%d N=%d neg=%d ineg=%d\n",*I,N,*neg,*ineg);
      return TRUE;
    }else{
      /* find next value in (neg) non-packed sequence that leaves gap for positive subscripts */
      while((*ineg)-- > 0){
        (*neg) = -index[(*ineg)] - 1; /* index is negative in R-Counting */
        if (++(*I)<(*neg)){
          //Rprintf("OUT2 I=%d N=%d neg=%d ineg=%d\n",*I,N,*neg,*ineg);
          return TRUE;
        }
      }
      /* negative subscripts exhausted, (*I) realigned with last suscript not available */
    }
  }

  /* negative subscripts exhausted, is there any gap after the last neg. subscript and the end? */
  if (++(*I)<N){
    //Rprintf("OUT3 I=%d N=%d neg=%d ineg=%d\n",*I,N,*neg,*ineg);
    return TRUE;
  }else{
    (*I) = N + 1; /* security precaution: don't leave (*I) at a forbidden value */
  }
  //Rprintf(" END I=%d N=%d neg=%d ineg=%d\n",*I,N,*neg,*ineg);
  return FALSE;
}



/* } --- helper functions for iterating ---------------------------------------------- */



/* { --- UTILITIES ---------------------------------------------------------- */


SEXP r_ff_xtensions_available(void)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(LGLSXP,1) );
  LOGICAL(ret_)[0] = FF_XTENSIONS_AVAILABLE;
  UNPROTECT(1);
  return ret_;
}

SEXP r_ff_symmxtensions_available(void)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(LGLSXP,1) );
  LOGICAL(ret_)[0] = FF_SYMMXTENSIONS_AVAILABLE;
  UNPROTECT(1);
  return ret_;
}



SEXP r_ff_getpagesize(void)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );
  INTEGER(ret_)[0] = ff_getpagesize();
  UNPROTECT(1);
  return ret_;
}



/* } --- UTILITIES ---------------------------------------------------------- */



/* --- FF ----------------------------------------------------------------- */


SEXP r_ff_geterror(SEXP ff_)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP,1) );
  INTEGER(ret_)[0] = ff_geterror( R_ExternalPtrAddr(ff_) );
  UNPROTECT(1);
  return ret_;
}

SEXP r_ff_geterrstr(SEXP ff_)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(STRSXP,1) );
  SET_STRING_ELT(ret_, 0, mkChar(ff_geterrstr( R_ExternalPtrAddr(ff_) )));
  UNPROTECT(1);
  return ret_;
}

/* this is for .vimplemented in vmode.R */
SEXP r_ff_ffmode_implemented(SEXP ffmode)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(LGLSXP,1) );

  switch (asInteger(ffmode)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: LOGICAL(ret_)[0] = TRUE; break;
#endif
#if VMODE_COMPILE_RAW
  case 13: LOGICAL(ret_)[0] = TRUE; break;
#endif
  default: LOGICAL(ret_)[0] = FALSE;
  }

  UNPROTECT(1);
  return ret_;
}


SEXP r_ff_new(SEXP name, SEXP ffmode, SEXP initval, SEXP len, SEXP pagesize, SEXP ro, SEXP autoflush
, SEXP createNew  // Martijn Schuemie for zero row ff
)
{
  SEXP ff_ = R_NilValue;
  void* ff = (void*) 0; /* assignment keeps the compiler quiet */

  switch (asInteger(ffmode)) { /* for ffmode see vmode.R */
#if VMODE_COMPILE_BOOLEAN
  case 1: ff = (void*) ff_boolean_new( CHAR(STRING_ELT(name,0)), asLogical(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ff = (void*) ff_logical_new( CHAR(STRING_ELT(name,0)), asLogical(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ff = (void*) ff_quad_new( CHAR(STRING_ELT(name,0)), asInteger(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ff = (void*) ff_nibble_new( CHAR(STRING_ELT(name,0)), asInteger(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ff = (void*) ff_byte_new( CHAR(STRING_ELT(name,0)), asInteger(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ff = (void*) ff_ubyte_new( CHAR(STRING_ELT(name,0)), asInteger(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ff = (void*) ff_short_new( CHAR(STRING_ELT(name,0)), asInteger(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ff = (void*) ff_ushort_new( CHAR(STRING_ELT(name,0)), asInteger(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ff = (void*) ff_integer_new( CHAR(STRING_ELT(name,0)), asInteger(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ff = (void*) ff_single_new( CHAR(STRING_ELT(name,0)), asReal(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ff = (void*) ff_double_new( CHAR(STRING_ELT(name,0)), asReal(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ff = (void*) ff_raw_new( CHAR(STRING_ELT(name,0)), asRaw(initval), asInteger(len), asInteger(pagesize), asLogical(ro), asLogical(autoflush)
, asInteger(createNew)  // Martijn Schuemie for zero row ff
); break;
#endif
  default: error("unknown ffmode");
  }

  if ( !ff ) {
    error("r_ff_new nil pointer creating ff");
    return R_NilValue;
  }
  if (ff_geterror( ff )) {
    error("r_ff_new %s", ff_geterrstr( ff ));
    ff_close(ff);
    return R_NilValue;
  }

  PROTECT( ff_ = R_MakeExternalPtr(ff, R_NilValue, R_NilValue) );
  UNPROTECT(1);

  return ff_;
}

SEXP r_ff_is_open(SEXP ff_)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(LGLSXP,1) );
  void* ff = (void*) R_ExternalPtrAddr(ff_);
  if (ff)
    LOGICAL(ret_)[0] = TRUE;
  else
    LOGICAL(ret_)[0] = FALSE;
  UNPROTECT(1);
  return ret_;
}

SEXP r_ff_open(SEXP ff_, SEXP ffmode, SEXP ro, SEXP autoflush)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(LGLSXP,1) );

  void* ff = (void*) 0; /* assignment keeps the compiler quiet */

  switch (asInteger(ffmode)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ff = (void*) ff_boolean_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ff = (void*) ff_logical_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ff = (void*) ff_quad_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ff = (void*) ff_nibble_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ff = (void*) ff_byte_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ff = (void*) ff_ubyte_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ff = (void*) ff_short_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ff = (void*) ff_ushort_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ff = (void*) ff_integer_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_SINGLE
  case 10: ff = (void*) ff_single_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ff = (void*) ff_double_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
#if VMODE_COMPILE_RAW
  case 13: ff = (void*) ff_raw_new( /* for ffmode see vmode.R */
    CHAR(asChar(getAttrib(ff_, install("filename"))))
  , 0 /* to be ignored in this call */
  , 0 // Martijn Schuemie for zero row ff
  , asInteger(getAttrib(ff_, install("pagesize")))
  , asLogical(ro)
  , asLogical(autoflush)
  , 0  // Martijn Schuemie for zero row ff
  ); break;
#endif
  default: error("unknown ffmode");
  }

  if ( !ff )
    error("r_ff_open nil pointer reopening ff");
  if (ff_geterror( ff ))
    error("r_ff_open %s", ff_geterrstr( ff ));

  R_SetExternalPtrAddr(ff_, ff);

  SEXP ro_; 
  PROTECT( ro_ = allocVector(LGLSXP,1) );
  LOGICAL(ro_)[0] = LOGICAL(ro)[0];
  setAttrib(ff_, install("readonly"), ro_);

  LOGICAL(ret_)[0] = TRUE;
  UNPROTECT(2);
  return ret_;
}

/* currently not used */
SEXP r_ff_close(SEXP ff_)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(LGLSXP,1) );
  void* ff = (void*) R_ExternalPtrAddr(ff_);
  if (ff){
    ff_close( ff );
    R_ClearExternalPtr(ff_);
    LOGICAL(ret_)[0] = TRUE;
  }else{
    LOGICAL(ret_)[0] = FALSE;
  }
  UNPROTECT(1);
  return ret_;
}

SEXP r_ff_delete(SEXP ff_)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(LGLSXP,1) );
  void* ff = (void*) R_ExternalPtrAddr(ff_);
  if (ff){
    ff_delete( ff );
    R_ClearExternalPtr(ff_);
    LOGICAL(ret_)[0] = TRUE;
  }else{
    LOGICAL(ret_)[0] = FALSE;
  }
  UNPROTECT(1);
  return ret_;
}

/* currently not used */
SEXP r_ff_maxlength(SEXP ff_)
{
  SEXP ret_;
  int l;
  PROTECT( ret_ = allocVector(INTSXP, 1) );
  l = ff_len( R_ExternalPtrAddr(ff_) );
  INTEGER(ret_)[0] = l;
  UNPROTECT(1);
  return ret_;
}






/* { -- VMODE MACRO section  ------------------------------------------------------- */

/*
  In addition to the different access functions {ff (single addgetset), ff contiguous, ff vector, ff array, ff symm, ram symm}
  we now do a lot of code duplication for performance reasons:
  we duplicate for the 5 access methods: getset, get, set, addgetset, addset  (this is necessary in order to avoid costly 'if's during looping)
  we duplicate for the 13 vmodes, because of the latter we need an additional layer of switch functions, e.g. r_ff__getset switching to r_ff_double_getset, r_ff_integer_getset etc..
  Duplicating for 13 vmodes and the switch layer might be avoidable !?
*/

/* macros that help to pass arguments with commas */

#define MACRO_HOWMANY_1(X1)       X1
#define MACRO_HOWMANY_2(X1,X2)    X1,X2
#define MACRO_HOWMANY_WHAT(X) MACRO_HOWMANY_##X

/* Example passing macro arguments with commas
#define FUNC(C) \
printf(C);

#define FUNB(HOWMANY,WHAT) \
FUNC(MACRO_HOWMANY_WHAT(HOWMANY(WHAT))) \
#define FUNA(HOWMANY,WHAT) \
int main(){ \
  int j=13; \
  FUNB(HOWMANY,MACRO_HOWMANY_WHAT(HOWMANY(WHAT))) \
  return 1; \
} \

// all the following works
#define D MACRO_HOWMANY_WHAT(2("abc%d",j))
FUNA(2,D)
#define D MACRO_HOWMANY_WHAT(1("abc"))
FUNA(1,D)
#define D "abc"
FUNA(1,D)
*/

/* trick to glue expanded macro arguments */
#define FF_GLUE_NAME(FF_GLUE_PREFIX, FF_GLUE_VMODE, FF_GLUE_ADD, FF_GLUE_GET, FF_GLUE_SET, FF_GLUE_POSTFIX) FF_GLUE_PREFIX##FF_GLUE_VMODE##_##FF_GLUE_ADD##FF_GLUE_GET##FF_GLUE_SET##FF_GLUE_POSTFIX

/* make the switch functions that switch methods conditional on vmode */
#include "r_ff_methodswitch.h"
#if FF_SYMMXTENSIONS_AVAILABLE
  #include "x_r_ff_methodswitch.h"
#endif

/* defining and making vmode methods */
#include "r_ff_makevmodes.h"

#undef FF_GLUE_NAME


#undef MACRO_HOWMANY_1
#undef MACRO_HOWMANY_2
#undef MACRO_HOWMANY_WHAT
/* } -- VMODE MACRO section  ------------------------------------------------------- */

/* wrap-up from r_ff.h */
#undef VMODE_COMPILE_BOOLEAN
#undef VMODE_COMPILE_LOGICAL
#undef VMODE_COMPILE_QUAD
#undef VMODE_COMPILE_NIBBLE
#undef VMODE_COMPILE_BYTE
#undef VMODE_COMPILE_UBYTE
#undef VMODE_COMPILE_SHORT
#undef VMODE_COMPILE_USHORT
#undef VMODE_COMPILE_INTEGER
#undef VMODE_COMPILE_SINGLE
#undef VMODE_COMPILE_DOUBLE
#undef VMODE_COMPILE_RAW
