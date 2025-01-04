/*
# ff macros for looping over vmodes: addgetset, addgetset_vec, addgetset_vector, addgetset_array
# (c) 2007 Jens Oehlschägel
# Licence: GPL2
# Provided 'as is', use at your own risk
# Created: 2007-10-25
# Last changed: 2009-12-12
*/

/* { -- FF addgetset / readwrite / swap ------------------------------------------------------- */


/* { --- r_ff_double_getset_contiguous r_ff_double_get_contiguous r_ff_double_set_contiguous r_ff_double_addgetset_contiguous r_ff_double_addset_contiguous --- */

/* this is the preprocessed mother code realized by the macro expansions below */
#if 0
  SEXP r_ff_double_getset_contiguous(SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
  {
    SEXP ret_ = R_NilValue;
    int nreturn = asInteger(nreturn_);
    PROTECT( ret_ = allocVector(REALSXP, nreturn) );
    ff_double_getset_contiguous( R_ExternalPtrAddr(ff_), asInteger(index_) - 1, nreturn, REAL(ret_), REAL(value_));
    UNPROTECT(1);
    return ret_;
  }
#endif


/* define code fragments */
#define FF_CODE_GET_PROTECT \
  PROTECT( ret_ = allocVector(VMODE_RTYPE, nreturn) );
#define FF_CODE_GET_ASSIGN , VMODE_ACCESS(ret_)
#define FF_CODE_GET_UNPROTECT \
  UNPROTECT(1);
#define FF_CODE_SET_VALUEPAR_SEXP , SEXP value_
#define FF_CODE_SET_VALUEPAR_CEXP , VMODE_ACCESS(value_)

/* define macro renaming fragment to fragment_ argument */
#define R_FF_VMODE_GETSET( \
  FF_NAME_VMODE, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX \
, FF_CODE_GET_PROTECT_, FF_CODE_GET_ASSIGN_, FF_CODE_GET_UNPROTECT_ \
, FF_CODE_SET_VALUEPAR_SEXP_, FF_CODE_SET_VALUEPAR_CEXP_ \
) \
SEXP FF_GLUE_NAME(r_ff_, FF_NAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX)(SEXP ff_, SEXP index_, SEXP nreturn_ FF_CODE_SET_VALUEPAR_SEXP_) \
{ \
  SEXP ret_ = ff_; \
  int nreturn = asInteger(nreturn_); \
  FF_CODE_GET_PROTECT_ \
  FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX)( R_ExternalPtrAddr(ff_), asInteger(index_) - 1, nreturn FF_CODE_GET_ASSIGN_ FF_CODE_SET_VALUEPAR_CEXP_); \
  FF_CODE_GET_UNPROTECT_ \
  return ret_; \
} \


/* call macro for each clone */
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, set, _contiguous
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_VALUEPAR_CEXP
)

R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, /*set*/, _contiguous
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
,,
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, /*get*/, set, _contiguous
,,,
,FF_CODE_SET_VALUEPAR_SEXP,FF_CODE_SET_VALUEPAR_CEXP
)
//#if VMODE_FFMODE!=2
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, get, set, _contiguous
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_VALUEPAR_CEXP
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, /*get*/, set, _contiguous
,,,
,FF_CODE_SET_VALUEPAR_SEXP,FF_CODE_SET_VALUEPAR_CEXP
)
//#endif

#undef FF_CODE_GET_PROTECT
#undef FF_CODE_GET_ASSIGN
#undef FF_CODE_GET_UNPROTECT
#undef FF_CODE_SET_VALUEPAR_SEXP
#undef FF_CODE_SET_VALUEPAR_CEXP
#undef R_FF_VMODE_GETSET
/* } --- r_ff_double_getset_contiguous r_ff_double_get_contiguous r_ff_double_set_contiguous r_ff_double_addgetset_contiguous r_ff_double_addset_contiguous --- */



/* { --- r_ff_double_getset_vec r_ff_double_get_vec r_ff_double_set_vec r_ff_double_addreadwrite_vec r_ff_double_addset_vec --- */


/* define code fragments */
#define FF_CODE_GET_PROTECT \
  PROTECT( ret_ = allocVector(VMODE_RTYPE, nreturn) ); \
  VMODE_CTYPE *ret = VMODE_ACCESS(ret_);
#define FF_CODE_GET_ASSIGN \
  ret[i] =
#define FF_CODE_GET_UNPROTECT \
  UNPROTECT(1);
#define FF_CODE_SET_VALUEPAR_SEXP , SEXP value_
#define FF_CODE_SET_DECLARATION \
  int l=0, nvalue = LENGTH(value_); \
  VMODE_CTYPE *value = VMODE_ACCESS(value_);
#define FF_CODE_SET_VALUEPAR_CEXP , value[l]
#define FF_CODE_SET_VALUEINC_CEXP if (++l==nvalue) l=0; /* recycle values */

/* define macro renaming fragment to fragment_ argument */
#define R_FF_VMODE_GETSET( \
  FF_NAME_VMODE, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX \
, FF_CODE_GET_PROTECT_, FF_CODE_GET_ASSIGN_, FF_CODE_GET_UNPROTECT_ \
, FF_CODE_SET_VALUEPAR_SEXP_, FF_CODE_SET_DECLARATION_, FF_CODE_SET_VALUEPAR_CEXP_, FF_CODE_SET_VALUEINC_CEXP_ \
) \
SEXP FF_GLUE_NAME(r_ff_, FF_NAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX)(SEXP ff_, SEXP index_, SEXP nreturn_ FF_CODE_SET_VALUEPAR_SEXP_) \
{ \
  void *ff = R_ExternalPtrAddr(ff_); \
  int *index = INTEGER(index_); \
  int i, nreturn = asInteger(nreturn_); \
  \
  SEXP ret_ = ff_; \
  FF_CODE_GET_PROTECT_ \
  FF_CODE_SET_DECLARATION_ \
  \
  if (nreturn){ \
    /* simply loop */ \
    for (i=0;i<nreturn;i++){ \
      FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, index[i] - 1 FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
    } \
  } \
  \
  FF_CODE_GET_UNPROTECT_ \
  return ret_; \
} \


/* call macro for each clone */
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, set, _vec
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, /*set*/, _vec
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
,,,,
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, /*get*/, set, _vec
,,,
,FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
//#if VMODE_FFMODE!=2
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, get, set, _vec
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, /*get*/, set, _vec
,,,
,FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
//#endif

#undef FF_CODE_GET_PROTECT
#undef FF_CODE_GET_ASSIGN
#undef FF_CODE_GET_UNPROTECT
#undef FF_CODE_SET_VALUEPAR_SEXP
#undef FF_CODE_SET_DECLARATION
#undef FF_CODE_SET_VALUEPAR_CEXP
#undef FF_CODE_SET_VALUEINC_CEXP
#undef R_FF_VMODE_GETSET
/* } --- r_ff_double_getset_vec r_ff_double_get_vec r_ff_double_set_vec r_ff_double_addreadwrite_vec r_ff_double_addset_vec --- */



/* { --- r_ff_double_getset_vector r_ff_double_get_vector r_ff_double_set_vector r_ff_double_addreadwrite_vector r_ff_double_addset_vector --- */

/* this is the preprocessed mother code realized by the macro expansions below */
#if 0
SEXP r_ff_double_getset_vector(SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  void *ff = R_ExternalPtrAddr(ff_);
  SEXP x = getListElement(index_, "x");
  SEXP dat = getListElement(x, "dat");
  SEXP class = getAttrib(dat, R_ClassSymbol);
  int first = asInteger(getListElement(x, "first"));
  int i, nreturn = asInteger(nreturn_);
  int l=0, nvalue = LENGTH(value_);                     /* dropped in r_ff_double_get_vector */
  double *value = REAL(value_);                         /* dropped in r_ff_double_get_vector */

  SEXP ret_ = R_NilValue;
  PROTECT( ret_ = allocVector(REALSXP, nreturn) );      /* dropped in r_ff_double_set_vector */
  double *ret = REAL(ret_);                             /* dropped in r_ff_double_set_vector */

  if (class==R_NilValue){ /* no class = not packed */

    int *index = INTEGER(dat);
    if (first<0){ /* negative subscripts */
      /* initialize */
      int iff=asInteger(getListElement(index_, "minindex")) - 1;
      int nff=asInteger(getListElement(index_, "maxindex"));
      int neg, ineg=LENGTH(dat); /* negative subscripts are also sorted ascending, thus we handle them from the last to first (abs ascending) */
      i=0;
      /* loop */
      while(ineg>0){
        neg = -index[--ineg] - 1;
        while(iff<neg){
          ret[i++] = ff_double_getset( ff, iff++, value[l]); if (++l==nvalue) l=0; /* recycle values */
        }
        iff++;
      }
      /* neg finalize */
      while(iff<nff){
        ret[i++] = ff_double_getset( ff, iff++, value[l]); if (++l==nvalue) l=0; /* recycle values */
      }
    }else{ /* positive subscripts */
      /* simply loop */
      for (i=0;i<nreturn;i++){
        ret[i] = ff_double_getset( ff, index[i] - 1, value[l]); if (++l==nvalue) l=0; /* recycle values */
      }
    }

  }else if(strcmp(CHAR(asChar(class)),"rle")==0){ /* rle class = packed */

    SEXP lengths = getListElement(dat, "lengths");
    int j, seqsize = LENGTH(lengths);
    int k, n, *seqlen = INTEGER(lengths);
    int v, *seqval = INTEGER(getListElement(dat, "values"));

    if (first<0){ /* negative subscripts */
      /* rle initialize: the subscripts before the first (=abs(last)) negative one */
      int iff=asInteger(getListElement(index_, "minindex")) - 1;
      int nff=asInteger(getListElement(index_, "maxindex"));
      int neg = -asInteger(getListElement(x, "last")) - 1; /* negative subscripts are also sorted ascending, thus we handle them from the last to first (abs ascending) */
      i=0;
      while(iff<neg){
        ret[i++] = ff_double_getset( ff, iff++, value[l]); if (++l==nvalue) l=0; /* recycle values */
      }
      iff++;
      /* rle loop */
      for (j=seqsize-1;j>=0;j--){
        v=seqval[j];
        n=seqlen[j];
        if (v==1){  /* with v=1 these negative subscripts have no gaps and we can skip at once */
          neg += n;
          iff += n;
        }else{      /* with v>1 we move abs neg upwards and handle the gaps */
          for (k=0;k<n;k++){
            neg += v;
            while(iff<neg){
              ret[i++] = ff_double_getset( ff, iff++, value[l]); if (++l==nvalue) l=0; /* recycle values */
            }
            iff++;
          }
        }
      }
      /* neg finalize: the subscripts after the last negative one */
      while(iff<nff){
        ret[i++] = ff_double_getset( ff, iff++, value[l]); if (++l==nvalue) l=0; /* recycle values */
      }
    }else{ /* positive subscripts */
      /* rle initialize */
      int iff = first - 1;
      i=0;
      ret[i++] = ff_double_getset( ff, iff, value[l]); if (++l==nvalue) l=0; /* recycle values */
      /* rle loop */
      for (j=0;j<seqsize;j++){
        v=seqval[j];
        n=seqlen[j];
        for (k=0;k<n;k++){
          iff += v;
          ret[i++] = ff_double_getset( ff, iff, value[l] ); if (++l==nvalue) l=0; /* recycle values */
        }
      }
    }

  }else{
    error("illegal class of $dat in seqpack object (must be integer vector or class rle)");
  }

  UNPROTECT(1);             /* dropped in r_ff_double_set_vector */
  return ret_;
}
#endif


/* xx dito showing how to use iterators
  this simplifies code
  this is about 3% slower
  this could probably be made faster using preprocesor macros instead of function calls
*/
#if 0
SEXP r_ff_double_getset_vector_iteration(SEXP ff_, SEXP index_, SEXP nreturn_, SEXP value_)
{
  void *ff = R_ExternalPtrAddr(ff_);
  SEXP x = getListElement(index_, "x");
  SEXP dat = getListElement(x, "dat");
  SEXP class = getAttrib(dat, R_ClassSymbol);
  int first = asInteger(getListElement(x, "first"));
  int i=0, nreturn = asInteger(nreturn_);

  SEXP ret_ = R_NilValue;
  PROTECT( ret_ = allocVector(REALSXP, nreturn) );      /* dropped in r_ff_double_set_vector */
  double *ret = REAL(ret_);                             /* dropped in r_ff_double_set_vector */

  int l=0, nvalue = LENGTH(value_);                     /* dropped in r_ff_double_get_vector */
  double *value = REAL(value_);                         /* dropped in r_ff_double_get_vector */

  if (class==R_NilValue){ /* no class = not packed */

    int *index = INTEGER(dat);
    if (first<0){ /* negative subscripts */

      int  iff = asInteger(getListElement(index_, "minindex")) - 2;  /* we want to reach 0 (or generally minindex-1) AFTER the first iteration */
      int  nff = asInteger(getListElement(index_, "maxindex"));
      int ineg = LENGTH(dat) - 1;   /* negative subscripts are also sorted ascending, thus we handle them from the last to first (abs ascending) */
      int  neg = -index[ineg] - 1;  /* convert to positive and -1 due to R-Counting */
      while(next_positive_neg(
        &iff   /* MODIFIED: current POSITIVE value moving UP from 0:(N-1), I==N if done, initialize with -1 */
      , nff    /*           maximum POSITIVE value */
      , &neg   /* MODIFIED: current POSITIVE neg sequence value moving UP from -index[nindex-1]-1:-index[0]-1, initialize with -index[nindex-1]-1 */
      , &ineg  /* MODIFIED: current position of neg subscript in index moving down from (nindex-1):0, ineg==-1 if done, initialize with nindex-1 */
      , index  /* vector of negative subscripts (R-counting) */
      )){
        ret[i++] = ff_double_getset( ff, iff, value[l]); if (++l==nvalue) l=0; /* recycle values */
      }

    }else{ /* positive subscripts */
      /* simply loop */
      for (;i<nreturn;){
        ret[i++] = ff_double_getset( ff, index[i] - 1, value[l]); if (++l==nvalue) l=0; /* recycle values */
      }
    }

  }else if(strcmp(CHAR(asChar(class)),"rle")==0){ /* rle class = packed */

    SEXP lengths = getListElement(dat, "lengths");
    int j, seqsize = LENGTH(lengths);
    int k, n, *seqlen = INTEGER(lengths);
    int v, *seqval = INTEGER(getListElement(dat, "values"));

    if (first<0){ /* negative subscripts */
      /* rle initialize: the subscripts before the first (=abs(last)) negative one */
      int neg = -asInteger(getListElement(x, "last")) - 1; /* negative subscripts are also sorted ascending, thus we handle them from the last to first (abs ascending) */
      int iff =  asInteger(getListElement(index_, "minindex")) - 2; /* we want to reach 0 (or generally minindex-1) AFTER the first iteration */
      int nff =  asInteger(getListElement(index_, "maxindex"));
      j = seqsize;
      v = 0; /* switch to first=abs(last) sequence as soon as next neg is required */
      n = 0;
      k = 0;
      while(next_positive_negpacked(
        &iff      /* MODIFIED: current POSITIVE value moving UP from 0:(N-1), I==N if done, initialize with -1 */
      , nff       /*           maximum POSITIVE value */
      , &neg      /* MODIFIED: current POSITIVE neg sequence value moving UP from -Last-1:-First-1, initialize with -Last-1 */
      , &v        /* MODIFIED: current/last (POSITIVE) increment, initialize with 0 */
      , &j        /* MODIFIED: current sequence moving DOWN from (seqsize-1):0, j==-1 if done, initialize with seqsize */
      , &k        /* MODIFIED: current instance of increment moving DOWN from (*n):1, k==0 if done, initialize with 0 */
      , &n        /* MODIFIED: current/last number of instances, initialize with 0 */
      , seqlen    /* vector of numbers of instances */
      , seqval    /* vector of (POSITIVE) increments */
      , seqsize   /* number of sequences NOT NEEDED due to backcounting (but offered) */
      )){
        ret[i++] = ff_double_getset( ff, iff, value[l]); if (++l==nvalue) l=0; /* recycle values */
      }

    }else{ /* positive subscripts */
      int iff = first - 1;
      j = -1;               /* initializing artificial increment sequence: 0 = first real increment sequence */
      v = 0;                /* ... don't change cff */
      n = 1;                /* ... one element */
      k = 0;                /* ... before iteration 0, after 1 */
      while(next_packed(
        &iff      /* MODIFIED: current sequence value moving UP from First-1 to Last-1, initialize with First-1-v */
      , &v        /* MODIFIED: current/last increment, initialize with 0 */
      , &j        /* MODIFIED: current sequence (0..(seqsize-1), j==seqsize if done), initialize with -1 */
      , &k        /* MODIFIED: current instance of increment 0:(n-1), k==n if done, initialize with 0 */
      , &n        /* MODIFIED: current/last number of instances, initialize with 1 */
      , seqlen    /* vector of numbers of instances */
      , seqval    /* vector of increments */
      , seqsize   /* number of sequences */
      )){
        ret[i++] = ff_double_getset( ff, iff, value[l] ); if (++l==nvalue) l=0; /* recycle values */
      }

    }

  }else{
    error("illegal class of $dat in seqpack object (must be integer vector or class rle)");
  }

  UNPROTECT(1);             /* dropped in r_ff_double_set_vector */
  return ret_;
}
#endif



/* define code fragments */
#define FF_CODE_GET_PROTECT \
  PROTECT( ret_ = allocVector(VMODE_RTYPE, nreturn) ); \
  VMODE_CTYPE *ret = VMODE_ACCESS(ret_);
#define FF_CODE_GET_ASSIGN \
  ret[i] =
#define FF_CODE_GET_UNPROTECT \
  UNPROTECT(1);
#define FF_CODE_SET_VALUEPAR_SEXP , SEXP value_
#define FF_CODE_SET_DECLARATION \
  int l=0, nvalue = LENGTH(value_); \
  VMODE_CTYPE *value = VMODE_ACCESS(value_);
#define FF_CODE_SET_VALUEPAR_CEXP , value[l]
#define FF_CODE_SET_VALUEINC_CEXP if (++l==nvalue) l=0; /* recycle values */

/* define macro renaming fragment to fragment_ argument */
#define R_FF_VMODE_GETSET( \
  FF_NAME_VMODE, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX \
, FF_CODE_GET_PROTECT_, FF_CODE_GET_ASSIGN_, FF_CODE_GET_UNPROTECT_ \
, FF_CODE_SET_VALUEPAR_SEXP_, FF_CODE_SET_DECLARATION_, FF_CODE_SET_VALUEPAR_CEXP_, FF_CODE_SET_VALUEINC_CEXP_ \
) \
SEXP FF_GLUE_NAME(r_ff_, FF_NAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX)(SEXP ff_, SEXP index_, SEXP nreturn_ FF_CODE_SET_VALUEPAR_SEXP_) \
{ \
  void *ff = R_ExternalPtrAddr(ff_); \
  SEXP x = getListElement(index_, "x"); \
  SEXP dat = getListElement(x, "dat"); \
  SEXP class = getAttrib(dat, R_ClassSymbol); \
  int first = asInteger(getListElement(x, "first")); \
  int i, nreturn = asInteger(nreturn_); \
  \
  SEXP ret_ = ff_; \
  FF_CODE_GET_PROTECT_ \
  FF_CODE_SET_DECLARATION_ \
  \
  if (class==R_NilValue){ /* no class = not packed */ \
  \
    int *index = INTEGER(dat); \
    if (first<0){ /* negative subscripts */ \
      /* initialize */ \
      int iff=asInteger(getListElement(index_, "minindex")) - 1; \
      int nff=asInteger(getListElement(index_, "maxindex")); \
      int neg, ineg=LENGTH(dat); /* negative subscripts are also sorted ascending, thus we handle them from the last to first (abs ascending) */ \
      i=0; \
      /* loop */ \
      while(ineg>0){ \
        neg = -index[--ineg] - 1; \
        while(iff<neg){ \
          FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff++ FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
          i++; \
        } \
        iff++; \
      } \
      /* neg finalize */ \
      while(iff<nff){ \
        FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff++ FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
        i++; \
      } \
    }else{ /* positive subscripts */ \
      /* simply loop */ \
      for (i=0;i<nreturn;i++){ \
        FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, index[i] - 1 FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
      } \
    } \
  \
  }else if(strcmp(CHAR(asChar(class)),"rle")==0){ /* rle class = packed */ \
  \
    SEXP lengths = getListElement(dat, "lengths"); \
    int j, seqsize = LENGTH(lengths); \
    int k, n, *seqlen = INTEGER(lengths); \
    int v, *seqval = INTEGER(getListElement(dat, "values")); \
  \
    if (first<0){ /* negative subscripts */ \
      /* rle initialize: the subscripts before the first (=abs(last)) negative one */ \
      int iff=asInteger(getListElement(index_, "minindex")) - 1; \
      int nff=asInteger(getListElement(index_, "maxindex")); \
      int neg = -asInteger(getListElement(x, "last")) - 1; /* negative subscripts are also sorted ascending, thus we handle them from the last to first (abs ascending) */ \
      i=0; \
      while(iff<neg){ \
        FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff++ FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
        i++; \
      } \
      iff++; \
      /* rle loop */ \
      for (j=seqsize-1;j>=0;j--){ \
        v=seqval[j]; \
        n=seqlen[j]; \
        if (v==1){  /* with v=1 these negative subscripts have no gaps and we can skip at once */ \
          neg += n; \
          iff += n; \
        }else{      /* with v>1 we move abs neg upwards and handle the gaps */ \
          for (k=0;k<n;k++){ \
            neg += v; \
            while(iff<neg){ \
              FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff++ FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
              i++; \
            } \
            iff++; \
          } \
        } \
      } \
      /* neg finalize: the subscripts after the last negative one */ \
      while(iff<nff){ \
        FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff++ FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
        i++; \
      } \
    }else{ /* positive subscripts */ \
      /* rle initialize */ \
      int iff = first - 1; \
      i=0; \
      FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
      i++; \
      /* rle loop */ \
      for (j=0;j<seqsize;j++){ \
        v=seqval[j]; \
        n=seqlen[j]; \
        for (k=0;k<n;k++){ \
          iff += v; \
          FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff FF_CODE_SET_VALUEPAR_CEXP_ ); FF_CODE_SET_VALUEINC_CEXP_ \
          i++; \
        } \
      } \
    } \
  \
  }else{ \
    error("illegal class of $dat in seqpack object (must be integer vector or class rle)"); \
  } \
  \
  FF_CODE_GET_UNPROTECT_ \
  return ret_; \
} \


/* call macro for each clone */
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, set, _vector
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, /*set*/, _vector
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
,,,,
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, /*get*/, set, _vector
,,,
,FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
//#if VMODE_FFMODE!=2
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, get, set, _vector
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, /*get*/, set, _vector
,,,
,FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP, FF_CODE_SET_VALUEINC_CEXP
)
//#endif

#undef FF_CODE_GET_PROTECT
#undef FF_CODE_GET_ASSIGN
#undef FF_CODE_GET_UNPROTECT
#undef FF_CODE_SET_VALUEPAR_SEXP
#undef FF_CODE_SET_DECLARATION
#undef FF_CODE_SET_VALUEPAR_CEXP
#undef FF_CODE_SET_VALUEINC_CEXP
#undef R_FF_VMODE_GETSET
/* } --- r_ff_double_getset_vector r_ff_double_get_vector r_ff_double_set_vector r_ff_double_addreadwrite_vector r_ff_double_addset_vector --- */



/* { --- r_ff_double_getset_array r_ff_double_get_array r_ff_double_set_array r_ff_double_addreadwrite_array r_ff_double_addset_array --- */

/* this is the preprocessed mother code realized by the macro expansions below */
#if 0
SEXP r_ff_double_getset_array(SEXP ff_, SEXP index_, SEXP indexdim_, SEXP ffdim_, SEXP ndim_, SEXP nreturn_, SEXP cumindexdim_, SEXP cumffdim_, SEXP value_)
{
  void *ff = R_ExternalPtrAddr(ff_);

  int ndim = asInteger(ndim_);
  int *indexdim = INTEGER(indexdim_);
  int *ffdim = INTEGER(ffdim_);
  int *cumindexdim = INTEGER(cumindexdim_);
  int *cumffdim = INTEGER(cumffdim_);

  SEXP ret_ = ff_;
  int nreturn = asInteger(nreturn_);                  /* drop in r_ff_double_set_array */
  PROTECT( ret_ = allocVector(REALSXP, nreturn) );    /* drop in r_ff_double_set_array */
  double *ret=REAL(ret_);                             /* drop in r_ff_double_set_array */

  int nvalue = LENGTH(value_);                    /* drop in r_ff_double_get_array */
  double *value = REAL(value_);                   /* drop in r_ff_double_get_array */

  /* the calculated index positions on the R and ff side */
  int iR, iff;

  /* Caches that save us doing redundant multiplications on the ff side.
     On the R side the same kind of caching could be done, but only when Rdimensionorder equals ffdimensionorder
  */
  int dif, newFF, sumFF=0;
  int *lastFF = (int *) R_alloc(ndim, sizeof(int));
  int *partFF = (int *) R_alloc(ndim, sizeof(int));

  /* for each dimension store whether packed or not */
  Rboolean *packed = (Rboolean *) R_alloc(ndim, sizeof(Rboolean));
  /* for each dimension store whether we have negative suscripting or not */
  Rboolean *isneg = (Rboolean *) R_alloc(ndim, sizeof(Rboolean));

  /* one dimension counter and ndim x counters for each dim in indexdim */
  int d;
  int *i = (int *) R_alloc(ndim, sizeof(int));

  /* ndim x valid index positions: start values and actual values */
  int *seqfirst = (int *) R_alloc(ndim, sizeof(int));
  int *subscript = (int *) R_alloc(ndim, sizeof(int));

  /* ndim x negative subscripts (optional): start values and actual values */
  int *negfirst = (int *) R_alloc(ndim, sizeof(int));
  int *neg = (int *) R_alloc(ndim, sizeof(int));

  /* case of packed */
  int *seqsize = (int *) R_alloc(ndim, sizeof(int));    /* ndim x length of index for unpacked / length of pseqlen for packed */
  int **pseqval = (int **) R_alloc(ndim, sizeof(int*)); /* ndim x index values for for unpacked / rle values for packed */
  int **pseqlen = (int **) R_alloc(ndim, sizeof(int*)); /* ndim x                               / rle lengths for packed */
  int *seqval = (int *) R_alloc(ndim, sizeof(int));     /* ndim x cache to store the actual rle value */
  int *seqlen = (int *) R_alloc(ndim, sizeof(int));     /* ndim x cache to store the actual rle length */
  int *j0 = (int *) R_alloc(ndim, sizeof(int));         /* ndim x position relative to seqsize (start values) */
  int *k0 = (int *) R_alloc(ndim, sizeof(int));         /* ndim x position relative to seqlen (start values) */
  int *j = (int *) R_alloc(ndim, sizeof(int));          /* ndim x position relative to seqsize (actual values) */
  int *k = (int *) R_alloc(ndim, sizeof(int));          /* ndim x position relative to seqlen (actual values) */

  /* just caches */
  SEXP x,dat,class;

  /* initialize */
  for (d=0;d<ndim;d++){
      x = getListElement(VECTOR_ELT(index_, d), "x");
      dat = getListElement(x, "dat");
      class = getAttrib(dat, R_ClassSymbol);

      i[d] = 0;                                                     /* for(i[d]=0;i[d]<indexdim[d];i[d]++) */
      isneg[d] = asInteger(getListElement(x, "first")) < 0;
      if (class==R_NilValue){
        packed[d] = FALSE;
        seqsize[d] = LENGTH(dat);
        pseqval[d] = INTEGER(dat);
        if (isneg[d]){
          /* find the first non-neg subscript and the abs first (~last) non-used neg */
          seqfirst[d] = 0;
          j0[d] = seqsize[d] - 1;     /* remember we walk negative indices from last to first */
          negfirst[d] = -pseqval[d][j0[d]] - 1;
          while(seqfirst[d]==negfirst[d]){
            seqfirst[d]++;
            if (j0[d] > 0){
              j0[d]--;
              negfirst[d] = -pseqval[d][j0[d]] - 1;
            }else{
              negfirst[d] = ffdim[d]; /* one behind the last possible index position */
            }
          }
          subscript[d] = seqfirst[d];
          neg[d] = negfirst[d];
          j[d] = j0[d];                                                 /* for(j[d]=j0[d];j[d]>=0;j[d]--) */
        }else{
          seqfirst[d] = pseqval[d][0] - 1;
          subscript[d] = seqfirst[d];
        }
      }else if(strcmp(CHAR(asChar(class)),"rle")==0){
        if (asInteger(getListElement(VECTOR_ELT(index_, d), "length")) < 2){
          UNPROTECT(1);
          error("less than two indices must not be RLE packed\n");
        }
        packed[d] = TRUE;
        seqsize[d] = LENGTH(getListElement(dat, "lengths"));
        pseqval[d] = INTEGER(getListElement(dat, "values"));
        pseqlen[d] = INTEGER(getListElement(dat, "lengths"));
        if (isneg[d]){
          seqfirst[d] = 0;
          negfirst[d] = -asInteger(getListElement(x, "last")) - 1; /* remember we walk negative indices from last to first */
          j0[d] = seqsize[d] - 1;
          seqval[d] = pseqval[d][j0[d]];
          seqlen[d] = pseqlen[d][j0[d]];
          if(negfirst[d]==0){
            while(seqval[d]==1){
              seqfirst[d] += seqlen[d]; /* this actually is += seqlen[d] * seqval[d], but since seqval[d]=1 ... */
              negfirst[d] -= seqlen[d]; /* this actually is -= seqlen[d] * seqval[d], but since seqval[d]=1 ... */
              if (j0[d] > 0){
                j0[d]--;
                seqval[d] = pseqval[d][j0[d]];
                seqlen[d] = pseqlen[d][j0[d]];
              }else{
                seqval[d] = 0;
                seqlen[d] = 0;
                negfirst[d] = ffdim[d];
              }
            }
            seqfirst[d]++;
            negfirst[d] += seqval[d];   /* now we have seqfirst[d] < negfirst[d] */
            k0[d]=1;                    /* the first of these seqval has been used now */
          }else{
            k0[d]=0;
          }
          subscript[d] = seqfirst[d];
          j[d] = j0[d];                                                 /* for(j[d]=j0[d];j[d]<seqsize[d];j[d]++) */
          k[d] = k0[d];                                                 /* for(k[d]=k0[d];k[d]<seqlen[d];k[d]++) */
          neg[d] = negfirst[d];
        }else{
          seqval[d] = pseqval[d][0];
          seqlen[d] = pseqlen[d][0];
          seqfirst[d] = asInteger(getListElement(x, "first")) - 1;
          j0[d] = 0;                                                 /* for(j[d]=0;j[d]<seqsize[d];j[d]++) */
          k0[d] = 0;                                                 /* for(k[d]=0;k[d]<seqlen[d];k[d]++) */
          subscript[d] = seqfirst[d];
          j[d] = j0[d];                                                 /* for(j[d]=j0[d];j[d]<seqsize[d];j[d]++) */
          k[d] = k0[d];                                                 /* for(k[d]=k0[d];k[d]<seqlen[d];k[d]++) */
        }
      }else{
        error("illegal class");
      }

      if (d==0){
        partFF[d]=0;
      }else{
        lastFF[d]=subscript[d] * cumffdim[d];
        partFF[d]=lastFF[d];
        sumFF += partFF[d];
      }

  }

  /* debug the initialization
  for (int d2=0;d2<ndim;d2++){
    Rprintf("d=%d packed[d]=%d isneg[d]=%d ffdim[d]=%d indexdim[d]=%d i[d]=%d seqfirst[d]=%d subscript[d]=%d\n", d2, packed[d2], isneg[d2], ffdim[d2], indexdim[d2], i[d2], seqfirst[d2], subscript[d2]);
    Rprintf("seqsize[d]=%d\n", seqsize[d2]);
    if (packed[d2])
      Rprintf("j0[d]=%d j[d]=%d seqval[d]=%d seqlen[d]=%d\n",j0[d2], j[d2], seqval[d2], seqlen[d2]);
    if (packed[d2] || isneg[d2])
      Rprintf("k0[d]=%d k[d]=%d\n",k0[d2], k[d2]);
    if (isneg[d2])
      Rprintf("negfirst=%d neg[d]=%d\n", negfirst[d2], neg[d2]);
  }
  */

  /* loop */
  Rboolean goon = TRUE;
  while(goon){
    int d2;
    /* handle found value */
    iff = sumFF + subscript[0] * cumffdim[0];
    iR=0;for (d2=0;d2<ndim;d2++)iR += i[d2]*cumindexdim[d2];
    ret[iR] = ff_double_getset( ff, iff, value[iR%nvalue] ); /* recycle values */

    /* start next search at first dimension */
    d = 0;

    /* search */
    while(1){
      /* explore next element */
      i[d]++;
      if (i[d]<indexdim[d]){
        /* find next value in same dimension */
        if (packed[d]){
          if (isneg[d]){
            subscript[d]++;
            if (subscript[d]==neg[d]){
              if (seqval[d] != 1 && ++(k[d])<seqlen[d]){
                neg += seqval[d];
                subscript[d]++;
              }else{
                if (seqval[d]==1){
                  subscript[d] += seqlen[d]; /* this actually is += seqlen[d] * seqval[d], but since seqval[d]=1 ... */
                  neg[d]       -= seqlen[d]; /* this actually is -= seqlen[d] * seqval[d], but since seqval[d]=1 ... */
                }
                while(TRUE){
                  if (j[d] > 0){
                    j[d]--;
                    seqval[d] = pseqval[d][j[d]];
                    seqlen[d] = pseqlen[d][j[d]];
                    if (seqval[d]==1){
                      subscript[d] += seqlen[d]; /* this actually is += seqlen[d] * seqval[d], but since seqval[d]=1 ... */
                      neg[d]       -= seqlen[d]; /* this actually is -= seqlen[d] * seqval[d], but since seqval[d]=1 ... */
                    }else{
                      neg += seqval[d];
                      subscript[d]++;
                      k[d]=1;
                      break;
                    }
                  }else{
                    seqval[d] = 0;
                    seqlen[d] = 0;
                    neg[d] = ffdim[d];
                    subscript[d]++;
                    break;
                  }
                }
              }
            }
          }else{
            if (k[d]<seqlen[d]){
              k[d]++;
            }else{
              j[d]++;
              k[d] = 1; /* was erroneously zero, but first value will have been used in the line after this ifelse statement */
              seqval[d] = pseqval[d][j[d]];
              seqlen[d] = pseqlen[d][j[d]];
            }
            subscript[d] += seqval[d];
          }
        }else{
          if (isneg[d]){
            subscript[d]++;
            while(subscript[d]==neg[d]){
              subscript[d]++;
              if (j[d] > 0){
                j[d]--;
                neg[d] = -pseqval[d][j[d]] - 1;
              }else{
                neg[d] = ffdim[d]; /* one behind the last possible index position */
              }
            }
          }else{
            subscript[d] = pseqval[d][i[d]] - 1;
          }
        }
        if (d>0){
          newFF = subscript[d] * cumffdim[d];
          dif = newFF - lastFF[d];
          partFF[d] = partFF[d] + dif;
          sumFF = sumFF + dif;
          lastFF[d] = newFF;
        }
        break;
      }else{
        /* reset dimension and switch to next dimension ... or exit */
        i[d] = 0;
        subscript[d] = seqfirst[d];
        if (packed[d]){
          j[d] = j0[d]; /* ==0 unless isneg[d] */
          k[d] = k0[d]; /* ==0 unless isneg[d] */
          seqlen[d] = pseqlen[d][j0[d]];
          seqval[d] = pseqval[d][j0[d]];
          if (isneg[d]){
            neg[d] = negfirst[d];
          }
        }else{
          if (isneg[d]){
            neg[d] = negfirst[d];
            j[d] = j0[d];
          }
        }
        if (d>0){
          newFF = subscript[d] * cumffdim[d];
          dif = newFF - lastFF[d];
          partFF[d] = partFF[d] + dif;
          sumFF = sumFF + dif;
          lastFF[d] = newFF;
        }
        d++;
        if (d==ndim){
          goon = FALSE;
          break;
        }
      }
    }
  }

  UNPROTECT(1);
  return ret_;
}
#endif



/* define code fragments */
#define FF_CODE_GET_PROTECT \
  int nreturn = asInteger(nreturn_); \
  PROTECT( ret_ = allocVector(VMODE_RTYPE, nreturn) ); \
  VMODE_CTYPE *ret = VMODE_ACCESS(ret_);
#define FF_CODE_GET_ASSIGN ret[iR] =
#define FF_CODE_GET_UNPROTECT \
  UNPROTECT(1);
#define FF_CODE_SET_VALUEPAR_SEXP , SEXP value_
#define FF_CODE_SET_DECLARATION \
  int nvalue = LENGTH(value_); \
  VMODE_CTYPE *value = VMODE_ACCESS(value_);
#define FF_CODE_SET_VALUEPAR_CEXP , value[iR%nvalue] /* recycle values */

/* define macro renaming fragment to fragment_ argument */
#define R_FF_VMODE_GETSET( \
  FF_NAME_VMODE, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX \
, FF_CODE_GET_PROTECT_, FF_CODE_GET_ASSIGN_, FF_CODE_GET_UNPROTECT_ \
, FF_CODE_SET_VALUEPAR_SEXP_, FF_CODE_SET_DECLARATION_, FF_CODE_SET_VALUEPAR_CEXP_ \
) \
SEXP FF_GLUE_NAME(r_ff_, FF_NAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, FF_NAME_POSTFIX)(SEXP ff_, SEXP index_, SEXP indexdim_, SEXP ffdim_, SEXP ndim_, SEXP nreturn_, SEXP cumindexdim_, SEXP cumffdim_ FF_CODE_SET_VALUEPAR_SEXP_) \
{ \
  void *ff = R_ExternalPtrAddr(ff_); \
  \
  int ndim = asInteger(ndim_); \
  int *indexdim = INTEGER(indexdim_); \
  int *ffdim = INTEGER(ffdim_); \
  int *cumindexdim = INTEGER(cumindexdim_); \
  int *cumffdim = INTEGER(cumffdim_); \
  \
  SEXP ret_ = ff_; \
  FF_CODE_GET_PROTECT_ \
  FF_CODE_SET_DECLARATION_ \
  \
  /* the calculated index positions on the R and ff side */ \
  int iR, iff; \
  \
  /* Caches that save us doing redundant multiplications on the ff side. \
     On the R side the same kind of caching could be done, but only when Rdimensionorder equals ffdimensionorder \
  */ \
  int dif, newFF, sumFF=0; \
  int *lastFF = (int *) R_alloc(ndim, sizeof(int)); \
  int *partFF = (int *) R_alloc(ndim, sizeof(int)); \
  \
  /* for each dimension store whether packed or not */ \
  Rboolean *packed = (Rboolean *) R_alloc(ndim, sizeof(Rboolean)); \
  /* for each dimension store whether we have negative suscripting or not */ \
  Rboolean *isneg = (Rboolean *) R_alloc(ndim, sizeof(Rboolean)); \
  \
  /* one dimension counter and ndim x counters for each dim in indexdim */ \
  int d; \
  int *i = (int *) R_alloc(ndim, sizeof(int)); \
  \
  /* ndim x valid index positions: start values and actual values */ \
  int *seqfirst = (int *) R_alloc(ndim, sizeof(int)); \
  int *subscript = (int *) R_alloc(ndim, sizeof(int)); \
  \
  /* ndim x negative subscripts (optional): start values and actual values */ \
  int *negfirst = (int *) R_alloc(ndim, sizeof(int)); \
  int *neg = (int *) R_alloc(ndim, sizeof(int)); \
  \
  /* case of packed */ \
  int *seqsize = (int *) R_alloc(ndim, sizeof(int));    /* ndim x length of index for unpacked / length of pseqlen for packed */ \
  int **pseqval = (int **) R_alloc(ndim, sizeof(int*)); /* ndim x index values for for unpacked / rle values for packed */ \
  int **pseqlen = (int **) R_alloc(ndim, sizeof(int*)); /* ndim x                               / rle lengths for packed */ \
  int *seqval = (int *) R_alloc(ndim, sizeof(int));     /* ndim x cache to store the actual rle value */ \
  int *seqlen = (int *) R_alloc(ndim, sizeof(int));     /* ndim x cache to store the actual rle length */ \
  int *j0 = (int *) R_alloc(ndim, sizeof(int));         /* ndim x position relative to seqsize (start values) */ \
  int *k0 = (int *) R_alloc(ndim, sizeof(int));         /* ndim x position relative to seqlen (start values) */ \
  int *j = (int *) R_alloc(ndim, sizeof(int));          /* ndim x position relative to seqsize (actual values) */ \
  int *k = (int *) R_alloc(ndim, sizeof(int));          /* ndim x position relative to seqlen (actual values) */ \
  \
  /* just caches */ \
  SEXP x,dat,class; \
  \
  /* initialize */ \
  for (d=0;d<ndim;d++){ \
      x = getListElement(VECTOR_ELT(index_, d), "x"); \
      dat = getListElement(x, "dat"); \
      class = getAttrib(dat, R_ClassSymbol); \
      i[d] = 0;                                                     /* for(i[d]=0;i[d]<indexdim[d];i[d]++) */ \
      isneg[d] = asInteger(getListElement(x, "first")) < 0; \
      if (class==R_NilValue){ \
        packed[d] = FALSE; \
        seqsize[d] = LENGTH(dat); \
        pseqval[d] = INTEGER(dat); \
        if (isneg[d]){ \
          /* find the first non-neg subscript and the abs first (~last) non-used neg */ \
          seqfirst[d] = 0; \
          j0[d] = seqsize[d] - 1;     /* remember we walk negative indices from last to first */ \
          negfirst[d] = -pseqval[d][j0[d]] - 1; \
          while(seqfirst[d]==negfirst[d]){ \
            seqfirst[d]++; \
            if (j0[d] > 0){ \
              j0[d]--; \
              negfirst[d] = -pseqval[d][j0[d]] - 1; \
            }else{ \
              negfirst[d] = ffdim[d]; /* one behind the last possible index position */ \
            } \
          } \
          subscript[d] = seqfirst[d]; \
          neg[d] = negfirst[d]; \
          j[d] = j0[d]; /* for(j[d]=j0[d];j[d]>=0;j[d]--) */ \
        }else{ \
          seqfirst[d] = pseqval[d][0] - 1; \
          subscript[d] = seqfirst[d]; \
        } \
      }else if(strcmp(CHAR(asChar(class)),"rle")==0){ \
        if (asInteger(getListElement(VECTOR_ELT(index_, d), "length")) < 2){ \
          FF_CODE_GET_UNPROTECT_ \
          error("less than two indices must not be RLE packed\n"); \
        } \
        packed[d] = TRUE; \
        seqsize[d] = LENGTH(getListElement(dat, "lengths")); \
        pseqval[d] = INTEGER(getListElement(dat, "values")); \
        pseqlen[d] = INTEGER(getListElement(dat, "lengths")); \
        if (isneg[d]){ \
          seqfirst[d] = 0; \
          negfirst[d] = -asInteger(getListElement(x, "last")) - 1; /* remember we walk negative indices from last to first */ \
          j0[d] = seqsize[d] - 1; \
          seqval[d] = pseqval[d][j0[d]]; \
          seqlen[d] = pseqlen[d][j0[d]]; \
          if(negfirst[d]==0){ \
            while(seqval[d]==1){ \
              seqfirst[d] += seqlen[d]; /* this actually is += seqlen[d] * seqval[d], but since seqval[d]=1 ... */ \
              negfirst[d] -= seqlen[d]; /* this actually is -= seqlen[d] * seqval[d], but since seqval[d]=1 ... */ \
              if (j0[d] > 0){ \
                j0[d]--; \
                seqval[d] = pseqval[d][j0[d]]; \
                seqlen[d] = pseqlen[d][j0[d]]; \
              }else{ \
                seqval[d] = 0; \
                seqlen[d] = 0; \
                negfirst[d] = ffdim[d]; \
              } \
            } \
            seqfirst[d]++; \
            negfirst[d] += seqval[d];   /* now we have seqfirst[d] < negfirst[d] */ \
            k0[d]=1;                    /* the first of these seqval has been used now */ \
          }else{ \
            k0[d]=0; \
          } \
          subscript[d] = seqfirst[d]; \
          j[d] = j0[d];                                                 /* for(j[d]=j0[d];j[d]<seqsize[d];j[d]++) */ \
          k[d] = k0[d];                                                 /* for(k[d]=k0[d];k[d]<seqlen[d];k[d]++) */ \
          neg[d] = negfirst[d]; \
        }else{ \
          seqval[d] = pseqval[d][0]; \
          seqlen[d] = pseqlen[d][0]; \
          seqfirst[d] = asInteger(getListElement(x, "first")) - 1; \
          j0[d] = 0;                                                 /* for(j[d]=0;j[d]<seqsize[d];j[d]++) */ \
          k0[d] = 0;                                                 /* for(k[d]=0;k[d]<seqlen[d];k[d]++) */ \
          subscript[d] = seqfirst[d]; \
          j[d] = j0[d];                                                 /* for(j[d]=j0[d];j[d]<seqsize[d];j[d]++) */ \
          k[d] = k0[d];                                                 /* for(k[d]=k0[d];k[d]<seqlen[d];k[d]++) */ \
        } \
      }else{ \
        error("illegal class"); \
      } \
  \
      if (d==0){ \
        lastFF[d]=0; \
        partFF[d]=0; \
      }else{ \
        lastFF[d]=subscript[d] * cumffdim[d]; \
        partFF[d]=lastFF[d]; \
        sumFF += partFF[d]; \
      } \
  \
  } \
  \
  /* debug the initialization \
  for (int d2=0;d2<ndim;d2++){ \
    Rprintf("d=%d packed[d]=%d isneg[d]=%d ffdim[d]=%d indexdim[d]=%d i[d]=%d seqfirst[d]=%d subscript[d]=%d\n", d2, packed[d2], isneg[d2], ffdim[d2], indexdim[d2], i[d2], seqfirst[d2], subscript[d2]); \
    Rprintf("seqsize[d]=%d\n", seqsize[d2]); \
    if (packed[d2]) \
      Rprintf("j0[d]=%d j[d]=%d seqval[d]=%d seqlen[d]=%d\n",j0[d2], j[d2], seqval[d2], seqlen[d2]); \
    if (packed[d2] || isneg[d2]) \
      Rprintf("k0[d]=%d k[d]=%d\n",k0[d2], k[d2]); \
    if (isneg[d2]) \
      Rprintf("negfirst=%d neg[d]=%d\n", negfirst[d2], neg[d2]); \
  } \
  */ \
  \
  /* loop */ \
  Rboolean goon = TRUE; \
  while(goon){ \
  \
    int d2;\
    /* handle found value */ \
    iff = sumFF + subscript[0] * cumffdim[0]; \
    iR=0;for (d2=0;d2<ndim;d2++)iR += i[d2]*cumindexdim[d2]; \
    /*Rprintf("d=%d sumFF=%d iFF=%d iR=%d\n", d, sumFF, iff, iR);*/ \
    /*for (int d2=0;d2<ndim;d2++)Rprintf("d2=%d i=%d subscript=%d partFF=%d cumffdim=%d cumindexdim=%d\n",d2, i[d2], subscript[d2], partFF[d2], cumffdim[d2], cumindexdim[d2]);*/\
    FF_CODE_GET_ASSIGN_ FF_GLUE_NAME(ff_, FF_FFNAME_VMODE, FF_NAME_ADD, FF_NAME_GET, FF_NAME_SET, )( ff, iff FF_CODE_SET_VALUEPAR_CEXP_ ); \
  \
    /* start next search at first dimension */ \
    d = 0; \
  \
    /* search */ \
    while(1){ \
      /* explore next element */ \
      i[d]++; \
      if (i[d]<indexdim[d]){ \
        /* find next value in same dimension */ \
        if (packed[d]){ \
          if (isneg[d]){ \
            subscript[d]++; \
            if (subscript[d]==neg[d]){ \
              if (seqval[d] != 1 && ++(k[d])<seqlen[d]){ \
                neg += seqval[d]; \
                subscript[d]++; \
              }else{ \
                if (seqval[d]==1){ \
                  subscript[d] += seqlen[d]; /* this actually is += seqlen[d] * seqval[d], but since seqval[d]=1 ... */ \
                  neg[d]       -= seqlen[d]; /* this actually is -= seqlen[d] * seqval[d], but since seqval[d]=1 ... */ \
                } \
                while(TRUE){ \
                  if (j[d] > 0){ \
                    j[d]--; \
                    seqval[d] = pseqval[d][j[d]]; \
                    seqlen[d] = pseqlen[d][j[d]]; \
                    if (seqval[d]==1){ \
                      subscript[d] += seqlen[d]; /* this actually is += seqlen[d] * seqval[d], but since seqval[d]=1 ... */ \
                      neg[d]       -= seqlen[d]; /* this actually is -= seqlen[d] * seqval[d], but since seqval[d]=1 ... */ \
                    }else{ \
                      neg += seqval[d]; \
                      subscript[d]++; \
                      k[d]=1; \
                      break; \
                    } \
                  }else{ \
                    seqval[d] = 0; \
                    seqlen[d] = 0; \
                    neg[d] = ffdim[d]; \
                    subscript[d]++; \
                    break; \
                  } \
                } \
              } \
            } \
          }else{ \
            if (k[d]<seqlen[d]){ \
              k[d]++; \
            }else{ \
              j[d]++; \
              k[d] = 1; /* was erroneously zero, but first value will have been used in the line after this ifelse statement */ \
              seqval[d] = pseqval[d][j[d]]; \
              seqlen[d] = pseqlen[d][j[d]]; \
            } \
            subscript[d] += seqval[d]; \
          } \
        }else{ \
          if (isneg[d]){ \
            subscript[d]++; \
            while(subscript[d]==neg[d]){ \
              subscript[d]++; \
              if (j[d] > 0){ \
                j[d]--; \
                neg[d] = -pseqval[d][j[d]] - 1; \
              }else{ \
                neg[d] = ffdim[d]; /* one behind the last possible index position */ \
              } \
            } \
          }else{ \
            subscript[d] = pseqval[d][i[d]] - 1; \
          } \
        } \
        if (d>0){ \
          newFF = subscript[d] * cumffdim[d]; \
          dif = newFF - lastFF[d]; \
          partFF[d] = partFF[d] + dif; \
          sumFF = sumFF + dif; \
          lastFF[d] = newFF; \
        } \
        break; \
      }else{ \
        /* reset dimension and switch to next dimension ... or exit */ \
        i[d] = 0; \
        subscript[d] = seqfirst[d]; \
        if (packed[d]){ \
          j[d] = j0[d]; /* ==0 unless isneg[d] */ \
          k[d] = k0[d]; /* ==0 unless isneg[d] */ \
          seqlen[d] = pseqlen[d][j0[d]]; \
          seqval[d] = pseqval[d][j0[d]]; \
          if (isneg[d]){ \
            neg[d] = negfirst[d]; \
          } \
        }else{ \
          if (isneg[d]){ \
            neg[d] = negfirst[d]; \
            j[d] = j0[d]; \
          } \
        } \
        if (d>0){ \
          newFF = subscript[d] * cumffdim[d]; \
          dif = newFF - lastFF[d]; \
          partFF[d] = partFF[d] + dif; \
          sumFF = sumFF + dif; \
          lastFF[d] = newFF; \
        } \
        d++; \
        if (d==ndim){ \
          goon = FALSE; \
          break; \
        } \
      } \
    } \
  } \
  \
  FF_CODE_GET_UNPROTECT_ \
  return ret_; \
} \


/* call macro for each clone */
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, set, _array
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, get, /*set*/, _array
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
,,,
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, /*add*/, /*get*/, set, _array
,,,
,FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP
)
//#if VMODE_FFMODE!=2
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, get, set, _array
, FF_CODE_GET_PROTECT, FF_CODE_GET_ASSIGN, FF_CODE_GET_UNPROTECT
, FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP
)
R_FF_VMODE_GETSET( VMODE_NAME, VMODE_FFNAME, add, /*get*/, set, _array
,,,
,FF_CODE_SET_VALUEPAR_SEXP, FF_CODE_SET_DECLARATION, FF_CODE_SET_VALUEPAR_CEXP
)
//#endif

#undef FF_CODE_GET_PROTECT
#undef FF_CODE_GET_ASSIGN
#undef FF_CODE_GET_UNPROTECT
#undef FF_CODE_SET_VALUEPAR_SEXP
#undef FF_CODE_SET_DECLARATION
#undef FF_CODE_SET_VALUEPAR_CEXP
#undef R_FF_VMODE_GETSET
/* } --- r_ff_double_getset_array r_ff_double_get_array r_ff_double_set_array r_ff_double_addreadwrite_array r_ff_double_addset_array --- */


/* } -- FF addgetset / readwrite / swap ------------------------------------------------------- */




