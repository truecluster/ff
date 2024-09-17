/*
# sorting module for ff
# (c) 2010 Jens Oehlschägel
# Licence: GPL2
# Provided 'as is', use at your own risk
# Created: 2010-01-01
# Last changed: 2010-06-06
*/

#include <R.h>
#include <Rinternals.h>

#include "config.h"
#include "ff.h"
#include "r_ff.h"

#define VERBOSE_LEVEL 0

#define key(A) (data[A])
#define equal(a,b) a==b
#define less(a,b) a<b
#define greater(a,b) a<b
#define exch(A,B) {t=A; A=B; B=t;}
#define exchi(A,B) {ti=A; A=B; B=ti;}
#define keyequal(A,B) (equal(key(A),key(B)))
#define keyless(A,B) (less(key(A),key(B)))
#define compexch(A,B) if (less(B,A)) exch(A,B)
#define keycompexch(A,B) if (keyless(B,A)) exch(A,B)

#define naequal(a,b) (ISNAN(a) ? ( ISNAN(b) ? TRUE : FALSE ) : ( ISNAN(b) ? FALSE : a==b ))
#define naless(a,b) (ISNAN(a) ? ( ISNAN(b) ? FALSE : !na_reverse ) : ( ISNAN(b) ? na_reverse : a<b ))
#define nakeyequal(A,B) (naequal(key(A),key(B)))
#define nakeyless(A,B) (naless(key(A),key(B)))
#define nacompexch(A,B) if (nakeyless(B,A)) exch(A,B)

#define intnaequal(a,b) (a==NA_INTEGER ? ( b==NA_INTEGER ? TRUE : FALSE ) : ( b==NA_INTEGER ? FALSE : a==b ))
#define intnaless(a,b) (a==NA_INTEGER ? ( b==NA_INTEGER ? FALSE : !na_reverse ) : ( b==NA_INTEGER ? na_reverse : a<b ))
#define intnakeyequal(A,B) (intnaequal(key(A),key(B)))
#define intnakeyless(A,B) (intnaless(key(A),key(B)))
#define intnacompexch(A,B) if (intnakeyless(B,A)) exch(A,B)

typedef int IndexT;
typedef double ValueT;

// xx TODO needs extension for 64bit integers  4^(i+1)+3*2^i+1
#define SHELLARRAYSIZE 16
static const IndexT incs[SHELLARRAYSIZE] = {1073790977, 268460033, 67121153, 16783361, 4197377,
           1050113, 262913, 65921, 16577, 4193, 1073, 281, 77,
           23, 8, 1};

#define INSERTIONSORT_LIMIT 32

/* --- Functions in this file ---

void ram_double_insitu(ValueT *data, IndexT *index, IndexT N)
void ram_integer_insitu(IndexT *data, IndexT *index, IndexT N)


void ram_integer_insertionsort_asc(IndexT *data, IndexT l, IndexT r)
void ram_integer_insertionsort_desc(IndexT *data, IndexT l, IndexT r)
void ram_integer_mergevalue_asc(IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
void ram_integer_mergevalue_desc(IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
void ram_integer_mergesort_asc_rec(IndexT *a, IndexT *b, IndexT l, IndexT r)
void ram_integer_mergesort_desc_rec(IndexT *a, IndexT *b, IndexT l, IndexT r)
IndexT ram_integer_mergesort(IndexT *index, IndexT *aux, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)

void ram_integer_insertionorder_asc(IndexT *data, IndexT *index, IndexT l, IndexT r)
void ram_integer_insertionorder_desc(IndexT *data, IndexT *index, IndexT l, IndexT r)
void ram_integer_mergeindex_asc(IndexT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
void ram_integer_mergeindex_desc(IndexT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
void ram_integer_mergeorder_asc_rec(IndexT *data, IndexT *a, IndexT *b, IndexT l, IndexT r)
void ram_integer_mergeorder_desc_rec(IndexT *data, IndexT *a, IndexT *b, IndexT l, IndexT r)
IndexT ram_integer_mergeorder(IndexT *data, IndexT *index, IndexT *aux, IndexT offset, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)

void ram_integer_shellsort_asc(IndexT *data, IndexT l, IndexT r)
void ram_integer_shellsort_desc(IndexT *data, IndexT l, IndexT r)
IndexT ram_integer_shellsort(IndexT *data, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)

void ram_integer_shellorder_asc(IndexT *data, IndexT *index, IndexT l, IndexT r)
void ram_integer_shellorder_desc(IndexT *data, IndexT *index, IndexT l, IndexT r)
void ram_integer_postorderstabilize(IndexT *data, IndexT *index, IndexT l, IndexT r, int has_na)
IndexT ram_integer_shellorder(IndexT *data, IndexT *index, IndexT offset, IndexT l, IndexT r
, int has_na, int na_last, int decreasing, int stabilize)

void ram_double_insertionsort_asc(ValueT *data, IndexT l, IndexT r)
void ram_double_insertionsort_desc(ValueT *data, IndexT l, IndexT r)
void ram_double_mergevalue_asc(ValueT *c, ValueT *a, IndexT N, ValueT *b, IndexT M)
void ram_double_mergevalue_desc(ValueT *c, ValueT *a, IndexT N, ValueT *b, IndexT M)
void ram_double_mergesort_asc_rec(ValueT *a, ValueT *b, IndexT l, IndexT r)
void ram_double_mergesort_desc_rec(ValueT *a, ValueT *b, IndexT l, IndexT r)
IndexT ram_double_mergesort(ValueT *index, ValueT *aux, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)

void ram_double_insertionorder_asc(ValueT *data, IndexT *index, IndexT l, IndexT r)
void ram_double_insertionorder_desc(ValueT *data, IndexT *index, IndexT l, IndexT r)
void ram_double_mergeindex_asc(ValueT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
void ram_double_mergeindex_desc(ValueT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
void ram_double_mergeorder_asc_rec(ValueT *data, IndexT *a, IndexT *b, IndexT l, IndexT r)
void ram_double_mergeorder_desc_rec(ValueT *data, IndexT *a, IndexT *b, IndexT l, IndexT r)
IndexT ram_double_mergeorder(ValueT *data, IndexT *index, IndexT *aux, IndexT offset, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)

void ram_double_shellsort_asc(ValueT *data, IndexT l, IndexT r)
void ram_double_shellsort_desc(ValueT *data, IndexT l, IndexT r)
IndexT ram_double_shellsort(ValueT *data, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)

void ram_double_shellorder_asc(ValueT *data, IndexT *index, IndexT l, IndexT r)
void ram_double_shellorder_desc(ValueT *data, IndexT *index, IndexT l, IndexT r)
void ram_double_postorderstabilize(ValueT *data, IndexT *index, IndexT l, IndexT r, int has_na)
IndexT ram_double_shellorder(ValueT *data, IndexT *index, IndexT offset, IndexT l, IndexT r
, int has_na, int na_last, int decreasing, int stabilize)

void ram_integer_keycount(IndexT *data, IndexT *count
, IndexT keyoffset, IndexT keylength, IndexT l, IndexT r
, int has_na)
void ram_integer_keyindexcount(IndexT *data, IndexT *index, IndexT *count
, IndexT offset, IndexT keyoffset, IndexT keylength, IndexT l, IndexT r
, int has_na)
void ram_integer_keycount2start(IndexT *count, IndexT keylength
, int has_na, int na_last, int decreasing)
IndexT ram_integer_keysort(IndexT *data, IndexT *count
, IndexT keyoffset, IndexT keylength, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)
IndexT ram_integer_keyorder(IndexT *data, IndexT *index, IndexT *auxindex, IndexT *count
, IndexT offset, IndexT keyoffset, IndexT keylength, IndexT l, IndexT r
, int has_na, int na_last, int decreasing)


void ram_integer_losort(IndexT *datain, IndexT *dataout, IndexT *count
  , IndexT l, IndexT r
  , int decreasing)
IndexT ram_integer_hisort(IndexT *datain, IndexT *dataout, IndexT *count
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing)
IndexT ram_integer_radixsort(IndexT *data, IndexT *dataaux, IndexT *count
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing)
void ram_integer_loorder(IndexT *data, IndexT *indexin, IndexT *indexout, IndexT *count
  , IndexT l, IndexT r
  , int decreasing)
IndexT ram_integer_hiorder(IndexT *data, IndexT *indexin, IndexT *indexout, IndexT *count
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing)
IndexT ram_integer_radixorder(IndexT *data, IndexT *index, IndexT *indexaux, IndexT *count
  , IndexT offset, IndexT l, IndexT r
  , int has_na, int na_last, int decreasing
)



SEXP r_ram_index_get(SEXP x_, SEXP index_)

SEXP r_ram_mergeorder(SEXP x_, SEXP index_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)
SEXP r_ram_mergesort(SEXP x_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)

SEXP r_ram_shellorder(SEXP x_, SEXP index_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_, SEXP stabilize_)
SEXP r_ram_shellsort(SEXP x_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)

SEXP r_ram_keyorder(SEXP x_, SEXP index_, SEXP keyrange_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)
SEXP r_ram_keysort(SEXP x_, SEXP keyrange_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)

SEXP r_ram_radixsort(SEXP x_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)
SEXP r_ram_radixorder(SEXP x_, SEXP index_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)


SEXP r_ff_double_ordermerge(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP auxff_, SEXP auxindex_
, SEXP left_, SEXP right_, SEXP method_, SEXP ordersize_, SEXP mergesize_
, SEXP orderindex_, SEXP has_na_, SEXP na_last_, SEXP decreasing_)
SEXP r_ff_double_sortmerge(SEXP ffmode_, SEXP ff_, SEXP auxff_
, SEXP left_, SEXP right_, SEXP method_, SEXP ordersize_, SEXP mergesize_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_)

SEXP r_ff_integer_ordermerge(SEXP ffmode_, SEXP ff_, SEXP index_, SEXP auxff_, SEXP auxindex_
, SEXP left_, SEXP right_, SEXP method_, SEXP keyrange_, SEXP ordersize_, SEXP mergesize_
, SEXP orderindex_, SEXP has_na_, SEXP na_last_, SEXP decreasing_)
SEXP r_ff_integer_sortmerge(SEXP ffmode_, SEXP ff_, SEXP auxff_
, SEXP left_, SEXP right_, SEXP method_, SEXP keyrange_, SEXP ordersize_, SEXP mergesize_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_
)


SEXP r_ff_integer_keysort(SEXP ffmode_, SEXP ffmode_, SEXP ff_
, SEXP left_, SEXP right_, SEXP keyrange_, SEXP ordersize_
, SEXP has_na_, SEXP na_last_, SEXP decreasing_
)


SEXP r_ff_index_chunkorder(SEXP index_, SEXP outindex_, SEXP indexsize_, SEXP method_, SEXP ordersize_)
SEXP r_ff_double_index_get(SEXP ffmode_, SEXP baseff_, SEXP returnff_, SEXP index_, SEXP auxindex_, SEXP offset_, SEXP left_, SEXP right_, SEXP method_, SEXP ordersize_)
SEXP r_ff_integer_index_get(SEXP ffmode_, SEXP baseff_, SEXP returnff_, SEXP index_, SEXP auxindex_, SEXP offset_, SEXP left_, SEXP right_, SEXP method_, SEXP ordersize_)

*/




/* xx TODO start point for multiple column sort

static int icmp(int x, int y, Rboolean nalast)
{
    if (x == y) return 0;
    if (x == NA_INTEGER)return nalast?1:-1;
    if (y == NA_INTEGER)return nalast?-1:1;
    if (x < y)    return -1;
    if (x > y)    return 1;
    return 0;
}

static int rcmp(double x, double y, Rboolean nalast)
{
    int nax = ISNAN(x), nay = ISNAN(y);
    if (nax && nay) return 0;
    if (nax)    return nalast?1:-1;
    if (nay)    return nalast?-1:1;
    if (x < y)    return -1;
    if (x > y)    return 1;
    return 0;
}

*/



/* { === begin pure C insitu apply order ================================================ */

void ram_double_insitu(ValueT *data, IndexT *index, IndexT N)
  {
    ValueT v;
    IndexT  i, j, k;
    for (i = 0; i < N; i++)
      if (index[i] != i){
          v = data[i]; k = i;
          do{
              j = k; data[j] = data[index[j]];
              k = index[j]; index[j] = j;
          }while (k != i);
          data[j] = v;
      }
  }


void ram_integer_insitu(IndexT *data, IndexT *index, IndexT N)
  {
    ValueT v;
    IndexT  i, j, k;
    for (i = 0; i < N; i++)
      if (index[i] != i){
          v = data[i]; k = i;
          do{
              j = k; data[j] = data[index[j]];
              k = index[j]; index[j] = j;
          }while (k != i);
          data[j] = v;
      }
  }




/* } === end pure C insitu apply order ================================================ */


/* xx some experimental check: more cache-friendly and faster but requires more RAM
  { === begin pure C stable mergeorder2 for doubles ================================================

// Sedgewick 6.3 Insertion sort with sentinel
//   sort index by data from left pos l to right pos r
void ram_double_insertionorder2_asc(ValueT *data, IndexT *index, IndexT l, IndexT r){
    IndexT i;
    ValueT t;
    IndexT ti;
    for (i=r;i>l;i--){
      if (less(data[i],data[i-1])){
        exch(data[i-1], data[i])
        exchi(index[i-1], index[i])
      }
    }
    for (i=l+2;i<=r;i++){
      IndexT j=i;
      ValueT v = data[i];
      IndexT vi = index[i];
      while (less(v,data[j-1])){
        data[j]=data[j-1];
        index[j]=index[j-1];
        j--;
      }
      data[j]=v;
      index[j]=vi;
    }
}
void ram_double_insertionorder2_desc(ValueT *data, IndexT *index, IndexT l, IndexT r){
    IndexT i;
    ValueT t;
    IndexT ti;
    for (i=l;i<r;i++){
      if (less(data[i],data[i+1])){
        exch(data[i+1], data[i])
        exchi(index[i+1], index[i])
      }
    }
    for (i=r-2;i>=l;i--){
      IndexT j=i;
      ValueT v = data[i];
      IndexT vi = index[i];
      while (less(v,data[j+1])){
        data[j]=data[j+1];
        index[j]=index[j+1];
        j++;
      }
      data[j]=v;
      index[j]=vi;
    }
}

// Sedgewick 8.1 Merging
//   stable merge c=a+b where N=len(a) and M=len(b)

void ram_double_mergeindex2_asc(ValueT *c, IndexT *ci, ValueT *a, IndexT *ai, IndexT N, ValueT *b, IndexT *bi, IndexT M){
  IndexT i,j,k;
  for (i=0,j=0,k=0;k<N+M;k++){
    if (i==N){
      for (;k<N+M;k++){
        c[k]=b[j];
        ci[k]=bi[j];
        j++;
      }
      break;
    }
    if (j==M){
      for (;k<N+M;k++){
        c[k]=a[i];
        ci[k]=ai[i];
        i++;
      }
      break;
    }
    if (less(b[j],a[i])){
      c[k] = b[j];
      ci[k] = bi[j];
      j++;
    }else{
      c[k] = a[i];
      ci[k] = ai[i];
      i++;
    }
  }
}
void ram_double_mergeindex2_desc(ValueT *c, IndexT *ci, ValueT *a, IndexT *ai, IndexT N, ValueT *b, IndexT *bi, IndexT M){
  IndexT i,j,k;
  for (i=N-1,j=M-1,k=N+M-1;k>=0;k--){
    if (i<0){
      for (;k>=0;k--){
        c[k]=b[j];
        ci[k]=bi[j];
        j--;
      }
      break;
    }
    if (j<0){
      for (;k>=0;k--){
        c[k]=a[i];
        ci[k]=ai[i];
        i--;
      }
      break;
    }
    if (less(a[i],b[j])){
      c[k] = a[i];
      ci[k] = ai[i];
      i--;
    }else{
      c[k] = b[j];
      ci[k] = bi[j];
      j--;
    }
  }
}


// Sedgewick 8.4 Mergesort with no copying
//   sorts b and leaves result in a

void ram_double_mergeorder2_asc_rec(ValueT *a, ValueT *b, IndexT *ai, IndexT *bi, IndexT l, IndexT r){
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_double_insertionorder2_asc(a, ai, l, r);
    return;
  }
  m = (l+r)/2;
  ram_double_mergeorder2_asc_rec(b, a, bi, ai, l, m);
  ram_double_mergeorder2_asc_rec(b, a, bi, ai, m+1, r);
  ram_double_mergeindex2_asc(a+l, ai+l, b+l, bi+l, m-l+1, b+m+1, bi+m+1, r-m);
}
void ram_double_mergeorder2_desc_rec(ValueT *a, ValueT *b, IndexT *ai, IndexT *bi, IndexT l, IndexT r){
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_double_insertionorder2_desc(a, ai, l, r);
    return;
  }
  m = (l+r)/2;
  ram_double_mergeorder2_desc_rec(b, a, bi, ai, l, m);
  ram_double_mergeorder2_desc_rec(b, a, bi, ai, m+1, r);
  ram_double_mergeindex2_desc(a+l, ai+l, b+l, bi+l, m-l+1, b+m+1, bi+m+1, r-m);
}



// mergsort interface:
//  - sort data
//  - handles NAs
//  - returns number of NAs
//

IndexT ram_double_mergeorder2(ValueT *data, ValueT *auxdata, IndexT *index, IndexT *auxindex, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
){
  IndexT i;
  IndexT l2,r2,nNA;
  r2 = r;
  if (has_na){
    l2 = l;
    if (na_last){
      for (i = l; i <= r; i++){
        if (ISNAN(data[i])){
          auxdata[r2] = data[i];
          auxindex[r2] = index[i];
          r2--;
        }else{
          auxdata[l2] = data[i];
          auxindex[l2] = index[i];
          l2++;
        }
      }
      nNA = r-r2;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++){
        data[i] = auxdata[i];
        index[i] = auxindex[i];
      }
      for (i=r;i>r2;i--,l2++){
        data[l2] = auxdata[i];
        index[l2] = auxindex[i];
      }
      for (i=r2+1;i<=r;i++){
        auxdata[i] = data[i];
        auxindex[i] = index[i];
      }
      if (decreasing)
        ram_double_mergeorder2_desc_rec(data, auxdata, index, auxindex, l, r2);
      else
        ram_double_mergeorder2_asc_rec(data, auxdata, index, auxindex, l, r2);
    }else{
      for (i = l; i <= r; i++){
        if (ISNAN(data[i])){
          auxdata[l2] = data[i];
          auxindex[l2] = index[i];
          l2++;
        }else{
          auxdata[r2] = data[i];
          auxindex[r2] = index[i];
          r2--;
        }
      }
      nNA = l2-l;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++){
        data[i] = auxdata[i];
        index[i] = auxindex[i];
      }
      for (i=r;i>r2;i--,l2++){
        data[l2] = auxdata[i];
        index[l2] = auxindex[i];
      }
      for (i=r2+1;i<=r;i++){
        auxdata[i] = data[i];
        auxindex[i] = index[i];
      }
      if (decreasing)
        ram_double_mergeorder2_desc_rec(data, auxdata, index, auxindex, r2+1, r);
      else
        ram_double_mergeorder2_asc_rec(data, auxdata, index, auxindex, r2+1, r);
    }
  }else{
    for (i = l; i <= r; i++){
      auxdata[i] = data[i];
      auxindex[i] = index[i];
    }
    if (decreasing)
      ram_double_mergeorder2_desc_rec(data, auxdata, index, auxindex, l, r);
    else
      ram_double_mergeorder2_asc_rec(data, auxdata, index, auxindex, l, r);
    nNA = 0;
  }
  return nNA;
}


 } === begin pure C stable mergeorder2 for doubles ================================================ */




/* { === begin pure C stable merge sort for doubles ================================================ */

/* Sedgewick 6.3 Insertion sort with sentinel
   sort index by data from left pos l to right pos r */
void ram_double_insertionsort_asc(ValueT *data, IndexT l, IndexT r){
    IndexT i;
    ValueT t;
    for (i=r;i>l;i--)
      compexch(data[i-1], data[i]);
    for (i=l+2;i<=r;i++){
      IndexT j=i;
      ValueT v = data[i];
      while (less(v,data[j-1])){
        data[j]=data[j-1]; j--;
      }
      data[j]=v;
    }
}
void ram_double_insertionsort_desc(ValueT *data, IndexT l, IndexT r){
    IndexT i;
    ValueT t;
    for (i=l;i<r;i++)
      compexch(data[i+1],data[i]);
    for (i=r-2;i>=l;i--){
      IndexT j=i;
      ValueT v = data[i];
      while (less(v,data[j+1])){
        data[j]=data[j+1]; j++;
      }
      data[j]=v;
    }
}

/* Sedgewick 8.1 Merging
   stable merge c=a+b where N=len(a) and M=len(b) */

void ram_double_mergevalue_asc(ValueT *c, ValueT *a, IndexT N, ValueT *b, IndexT M){
  IndexT i,j,k;
  for (i=0,j=0,k=0;k<N+M;k++){
    if (i==N){
      for (;k<N+M;k++)
        c[k]=b[j++];
      break;
    }
    if (j==M){
      for (;k<N+M;k++)
        c[k]=a[i++];
      break;
    }
    c[k] = (less(b[j],a[i])) ? b[j++] : a[i++];
  }
}
void ram_double_mergevalue_desc(ValueT *c, ValueT *a, IndexT N, ValueT *b, IndexT M){
  IndexT i,j,k;
  for (i=N-1,j=M-1,k=N+M-1;k>=0;k--){
    if (i<0){
      for (;k>=0;k--)
        c[k]=b[j--];
      break;
    }
    if (j<0){
      for (;k>=0;k--)
        c[k]=a[i--];
      break;
    }
    c[k] = (less(a[i],b[j])) ? a[i--] : b[j--];
  }
}


/* Sedgewick 8.4 Mergesort with no copying
   sorts b and leaves result in a */

void ram_double_mergesort_asc_rec(ValueT *a, ValueT *b, IndexT l, IndexT r){
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_double_insertionsort_asc(a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_double_mergesort_asc_rec(b, a, l, m);
  ram_double_mergesort_asc_rec(b, a, m+1, r);
  ram_double_mergevalue_asc(a+l, b+l, m-l+1, b+m+1, r-m);
}
void ram_double_mergesort_desc_rec(ValueT *a, ValueT *b, IndexT l, IndexT r){
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_double_insertionsort_desc(a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_double_mergesort_desc_rec(b, a, l, m);
  ram_double_mergesort_desc_rec(b, a, m+1, r);
  ram_double_mergevalue_desc(a+l, b+l, m-l+1, b+m+1, r-m);
}



/* mergsort interface:
  - sort data
  - handles NAs
  - returns number of NAs
*/

IndexT ram_double_mergesort(ValueT *index, ValueT *aux, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
){
  IndexT i;
  IndexT l2,r2,nNA;
  r2 = r;
  if (has_na){
    l2 = l;
    if (na_last){
      for (i = l; i <= r; i++){
        if (ISNAN(index[i]))
          aux[r2--] = index[i];
        else
          aux[l2++] = index[i];
      }
      nNA = r-r2;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_double_mergesort_desc_rec(index, aux, l, r2);
      else
        ram_double_mergesort_asc_rec(index, aux, l, r2);
    }else{
      for (i = l; i <= r; i++){
        if (ISNAN(index[i]))
          aux[l2++] = index[i];
        else
          aux[r2--] = index[i];
      }
      nNA = l2-l;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_double_mergesort_desc_rec(index, aux, r2+1, r);
      else
        ram_double_mergesort_asc_rec(index, aux, r2+1, r);
    }
  }else{
    for (i = l; i <= r; i++)
      aux[i] = index[i];
    if (decreasing)
      ram_double_mergesort_desc_rec(index, aux, l, r);
    else
      ram_double_mergesort_asc_rec(index, aux, l, r);
    nNA = 0;
  }
  return nNA;
}


/* } === begin pure C stable merge sort for doubles ================================================ */




/* { === begin pure C stable merge order for doubles ================================================ */


/* like Sedgewick 6.3 Insertion sort
   sort index by data from left pos l to right pos r */
void ram_double_insertionorder_asc(ValueT *data, IndexT *index, IndexT l, IndexT r){
    IndexT i;
    IndexT t;
    for (i=r;i>l;i--)
      keycompexch(index[i-1], index[i]);
    for (i=l+2;i<=r;i++){
      IndexT j=i;
      IndexT v = index[i];
      while (keyless(v,index[j-1])){
        index[j]=index[j-1]; j--;
      }
      index[j]=v;
    }
}
void ram_double_insertionorder_desc(ValueT *data, IndexT *index, IndexT l, IndexT r){
    IndexT i;
    IndexT t;
    for (i=l;i<r;i++)
      keycompexch(index[i+1],index[i]);
    for (i=r-2;i>=l;i--){
      IndexT j=i;
      IndexT v = index[i];
      while (keyless(v,index[j+1])){
        index[j]=index[j+1]; j++;
      }
      index[j]=v;
    }
}


/* like Sedgewick 8.1 Merging
   stable merge c=a+b where N=len(a) and M=len(b) */

void ram_double_mergeindex_asc(ValueT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M){
  IndexT i,j,k;
  for (i=0,j=0,k=0;k<N+M;k++){
    if (i==N){
      for (;k<N+M;k++)
        c[k]=b[j++];
      break;
    }
    if (j==M){
      for (;k<N+M;k++)
        c[k]=a[i++];
      break;
    }
    c[k] = (keyless(b[j],a[i])) ? b[j++] : a[i++];
  }
}
void ram_double_mergeindex_desc(ValueT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M){
  IndexT i,j,k;
  for (i=N-1,j=M-1,k=N+M-1;k>=0;k--){
    if (i<0){
      for (;k>=0;k--)
        c[k]=b[j--];
      break;
    }
    if (j<0){
      for (;k>=0;k--)
        c[k]=a[i--];
      break;
    }
    c[k] = (keyless(a[i],b[j])) ? a[i--] : b[j--];
  }
}

/* alternative parametrization without pointer arithmetic in case we can't use pointers
i = 0:(N-1) = 0:(m-l) => l:m
j = 0:(M-1) = 0:(r-m-1) => (m+1):r
k = 0:(N+M-1) = 0:(m-l+1+r-m-1) = 0:(r-l) => l:r

void ram_double_mergeindex_asc(ValueT *data, IndexT *c, IndexT *a, IndexT *b, IndexT l, IndexT m, IndexT r){
  IndexT i,j,k;
  for (i=l,j=m+1,k=l;k<=r;k++){
    if (i>m){
      for (;k<=r;k++)
        c[k]=b[j++];
      break;
    }
    if (j>r){
      for (;k<=r;k++)
        c[k]=a[i++];
      break;
    }
    c[k] = (keyless(b[j],a[i])) ? b[j++] : a[i++];
  }
}
*/



/* like Sedgewick 8.4 Mergesort with no copying
   sorts b and leaves result in a */

void ram_double_mergeorder_asc_rec(ValueT *data, IndexT *a, IndexT *b, IndexT l, IndexT r){
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_double_insertionorder_asc(data, a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_double_mergeorder_asc_rec(data, b, a, l, m);
  ram_double_mergeorder_asc_rec(data, b, a, m+1, r);
  /* alternative parametrization without pointer arithmetic
  ram_double_mergeindex_asc(data, a, b, b, l, m, r);
  */
  ram_double_mergeindex_asc(data, a+l, b+l, m-l+1, b+m+1, r-m);
}
void ram_double_mergeorder_desc_rec(ValueT *data, IndexT *a, IndexT *b, IndexT l, IndexT r){
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_double_insertionorder_desc(data, a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_double_mergeorder_desc_rec(data, b, a, l, m);
  ram_double_mergeorder_desc_rec(data, b, a, m+1, r);
  ram_double_mergeindex_desc(data, a+l, b+l, m-l+1, b+m+1, r-m);
}



/* mergorder interface:
  - does order index such that data is sorted
  - leaves aux in an undefined state
  - handles an offset, especially 1 to do R2C => order => C2R
  - handles NAs
  - returns number of NAs
*/

IndexT ram_double_mergeorder(ValueT *data, IndexT *index, IndexT *aux
, IndexT offset     // 0 for C subsripts, 1 to correct R2C and C2R
, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
){
  IndexT i;
  IndexT l2,r2,nNA;
  r2 = r;
  if (has_na){
    l2 = l;
    if (na_last){
      for (i = l; i <= r; i++){
        if (ISNAN(data[index[i]-=offset]))
          aux[r2--] = index[i];
        else
          aux[l2++] = index[i];
      }
      nNA = r-r2;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_double_mergeorder_desc_rec(data, index, aux, l, r2);
      else
        ram_double_mergeorder_asc_rec(data, index, aux, l, r2);
    }else{
      for (i = l; i <= r; i++){
        if (ISNAN(data[index[i]-=offset]))
          aux[l2++] = index[i];
        else
          aux[r2--] = index[i];
      }
      nNA = l2-l;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_double_mergeorder_desc_rec(data, index, aux, r2+1, r);
      else
        ram_double_mergeorder_asc_rec(data, index, aux, r2+1, r);
    }
  }else{
    if (offset){
      for (i = l; i <= r; i++){
        index[i] -= offset;
        aux[i] = index[i];
      }
    }else{
      for (i = l; i <= r; i++)
        aux[i] = index[i];
    }
    if (decreasing)
      ram_double_mergeorder_desc_rec(data, index, aux, l, r);
    else
      ram_double_mergeorder_asc_rec(data, index, aux, l, r);
    nNA = 0;
  }
  if (offset)
    for (i = l; i <= r; i++)
      index[i] += offset;
  return nNA;
}

/* } === end pure C stable merge order for doubles ================================================ */



/* { === begin pure C stable merge sort for integers ================================================ */

/* Sedgewick 6.3 Insertion sort
   sort index by data from left pos l to right pos r */
void ram_integer_insertionsort_asc(IndexT *data, IndexT l, IndexT r)
{
    IndexT i;
    IndexT t;
    for (i=r;i>l;i--)
      compexch(data[i-1], data[i]);
    for (i=l+2;i<=r;i++){
      IndexT j=i;
      IndexT v = data[i];
      while (less(v,data[j-1])){
        data[j]=data[j-1]; j--;
      }
	  data[j]=v;
    }
}
void ram_integer_insertionsort_desc(IndexT *data, IndexT l, IndexT r)
{
    IndexT i;
    IndexT t;
    for (i=l;i<r;i++)
      compexch(data[i+1],data[i]);
    for (i=r-2;i>=l;i--){
      IndexT j=i;
      IndexT v = data[i];
      while (less(v,data[j+1])){
        data[j]=data[j+1]; j++;
      }
	  data[j]=v;
    }
}

/* Sedgewick 8.1 Merging
   stable merge c=a+b where N=len(a) and M=len(b) */

void ram_integer_mergevalue_asc(IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
{
  IndexT i,j,k;
  for (i=0,j=0,k=0;k<N+M;k++){
    if (i==N){
      for (;k<N+M;k++)
        c[k]=b[j++];
      break;
    }
    if (j==M){
      for (;k<N+M;k++)
        c[k]=a[i++];
      break;
    }
    c[k] = (less(b[j],a[i])) ? b[j++] : a[i++];
  }
}
void ram_integer_mergevalue_desc(IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
{
  IndexT i,j,k;
  for (i=N-1,j=M-1,k=N+M-1;k>=0;k--){
    if (i<0){
      for (;k>=0;k--)
        c[k]=b[j--];
      break;
    }
    if (j<0){
      for (;k>=0;k--)
        c[k]=a[i--];
      break;
    }
    c[k] = (less(a[i],b[j])) ? a[i--] : b[j--];
  }
}


/* Sedgewick 8.4 Mergesort with no copying
   sorts b and leaves result in a */

void ram_integer_mergesort_asc_rec(IndexT *a, IndexT *b, IndexT l, IndexT r)
{
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_integer_insertionsort_asc(a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_integer_mergesort_asc_rec(b, a, l, m);
  ram_integer_mergesort_asc_rec(b, a, m+1, r);
  ram_integer_mergevalue_asc(a+l, b+l, m-l+1, b+m+1, r-m);
}
void ram_integer_mergesort_desc_rec(IndexT *a, IndexT *b, IndexT l, IndexT r)
{
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_integer_insertionsort_desc(a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_integer_mergesort_desc_rec(b, a, l, m);
  ram_integer_mergesort_desc_rec(b, a, m+1, r);
  ram_integer_mergevalue_desc(a+l, b+l, m-l+1, b+m+1, r-m);
}



/* mergsort interface:
  - sort data
  - handles NAs
  - returns number of NAs
*/

IndexT ram_integer_mergesort(IndexT *index, IndexT *aux, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
)
{
  IndexT i;
  IndexT l2,r2,nNA;
  r2 = r;
  if (has_na){
    l2 = l;
    if (na_last){
      for (i = l; i <= r; i++){
        if (index[i]==NA_INTEGER)
          aux[r2--] = index[i];
        else
          aux[l2++] = index[i];
      }
      nNA = r-r2;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_integer_mergesort_desc_rec(index, aux, l, r2);
      else
        ram_integer_mergesort_asc_rec(index, aux, l, r2);
    }else{
      for (i = l; i <= r; i++){
        if (index[i]==NA_INTEGER)
          aux[l2++] = index[i];
        else
          aux[r2--] = index[i];
      }
      nNA = l2-l;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_integer_mergesort_desc_rec(index, aux, r2+1, r);
      else
        ram_integer_mergesort_asc_rec(index, aux, r2+1, r);
    }
  }else{
    for (i = l; i <= r; i++)
      aux[i] = index[i];
    if (decreasing)
      ram_integer_mergesort_desc_rec(index, aux, l, r);
    else
      ram_integer_mergesort_asc_rec(index, aux, l, r);
    nNA = 0;
  }
  return nNA;
}


/* } === begin pure C stable merge sort for integers ================================================ */



/* { === begin pure C stable merge order for integers ================================================ */

/* like Sedgewick 6.3 Insertion sort
   sort index by data from left pos l to right pos r */
void ram_integer_insertionorder_asc(IndexT *data, IndexT *index, IndexT l, IndexT r)
{
    IndexT i;
    IndexT t;
    for (i=r;i>l;i--)
      keycompexch(index[i-1], index[i]);
    for (i=l+2;i<=r;i++){
      IndexT j=i;
      IndexT v = index[i];
      while (keyless(v,index[j-1])){
        index[j]=index[j-1]; j--;
        index[j]=v;
      }
    }
}
void ram_integer_insertionorder_desc(IndexT *data, IndexT *index, IndexT l, IndexT r)
{
    IndexT i;
    IndexT t;
    for (i=l;i<r;i++)
      keycompexch(index[i+1],index[i]);
    for (i=r-2;i>=l;i--){
      IndexT j=i;
      IndexT v = index[i];
      while (keyless(v,index[j+1])){
        index[j]=index[j+1]; j++;
        index[j]=v;
      }
    }
}


/* like Sedgewick 8.1 Merging
   stable merge c=a+b where N=len(a) and M=len(b) */

void ram_integer_mergeindex_asc(IndexT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
{
  IndexT i,j,k;
  for (i=0,j=0,k=0;k<N+M;k++){
    if (i==N){
      for (;k<N+M;k++)
        c[k]=b[j++];
      break;
    }
    if (j==M){
      for (;k<N+M;k++)
        c[k]=a[i++];
      break;
    }
    c[k] = (keyless(b[j],a[i])) ? b[j++] : a[i++];
  }
}

void ram_integer_mergeindex_desc(IndexT *data, IndexT *c, IndexT *a, IndexT N, IndexT *b, IndexT M)
{
  IndexT i,j,k;
  for (i=N-1,j=M-1,k=N+M-1;k>=0;k--){
    if (i<0){
      for (;k>=0;k--)
        c[k]=b[j--];
      break;
    }
    if (j<0){
      for (;k>=0;k--)
        c[k]=a[i--];
      break;
    }
    c[k] = (keyless(a[i],b[j])) ? a[i--] : b[j--];
  }
}


/* alternative parametrization without pointer arithmetic in case we can't use pointers
i = 0:(N-1) = 0:(m-l) => l:m
j = 0:(M-1) = 0:(r-m-1) => (m+1):r
k = 0:(N+M-1) = 0:(m-l+1+r-m-1) = 0:(r-l) => l:r

void ram_integer_mergeindex_asc(IndexT *data, IndexT *c, IndexT *a, IndexT *b, IndexT l, IndexT m, IndexT r){
  IndexT i,j,k;
  for (i=l,j=m+1,k=l;k<=r;k++){
    if (i>m){
      for (;k<=r;k++)
        c[k]=b[j++];
      break;
    }
    if (j>r){
      for (;k<=r;k++)
        c[k]=a[i++];
      break;
    }
    c[k] = (keyless(b[j],a[i])) ? b[j++] : a[i++];
  }
}
*/



/* like Sedgewick 8.4 Mergesort with no copying
   sorts b and leaves result in a */

void ram_integer_mergeorder_asc_rec(IndexT *data, IndexT *a, IndexT *b, IndexT l, IndexT r)
{
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_integer_insertionorder_asc(data, a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_integer_mergeorder_asc_rec(data, b, a, l, m);
  ram_integer_mergeorder_asc_rec(data, b, a, m+1, r);
  /* alternative parametrization without pointer arithmetic
  ram_integer_mergeindex_asc(data, a, b, b, l, m, r);
  */
  ram_integer_mergeindex_asc(data, a+l, b+l, m-l+1, b+m+1, r-m);
}
void ram_integer_mergeorder_desc_rec(IndexT *data, IndexT *a, IndexT *b, IndexT l, IndexT r)
{
  IndexT m;
  if (r-l <= INSERTIONSORT_LIMIT){
    ram_integer_insertionorder_desc(data, a, l, r);
    return;
  }
  m = (l+r)/2;
  ram_integer_mergeorder_desc_rec(data, b, a, l, m);
  ram_integer_mergeorder_desc_rec(data, b, a, m+1, r);
  ram_integer_mergeindex_desc(data, a+l, b+l, m-l+1, b+m+1, r-m);
}



/* mergorder interface:
  - does order index such that data is sorted
  - leaves aux in an undefined state
  - handles an offset, especially 1 to do R2C => order => C2R
  - handles NAs
  - returns number of NAs
*/

IndexT ram_integer_mergeorder(IndexT *data, IndexT *index, IndexT *aux
, IndexT offset     // 0 for C subsripts, 1 to correct R2C and C2R
, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
){
  IndexT i;
  IndexT l2,r2,nNA;
  if (has_na){
    r2 = r;
    l2 = l;
    if (na_last){
      for (i = l; i <= r; i++){
        if (data[index[i]-=offset]==NA_INTEGER)
          aux[r2--] = index[i];
        else
          aux[l2++] = index[i];
      }
      nNA = r-r2;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_integer_mergeorder_desc_rec(data, index, aux, l, r2);
      else
        ram_integer_mergeorder_asc_rec(data, index, aux, l, r2);
    }else{
      for (i = l; i <= r; i++){
        if (data[index[i]-=offset]==NA_INTEGER)
          aux[l2++] = index[i];
        else
          aux[r2--] = index[i];
      }
      nNA = l2-l;
      // reverse order in the right part which was written from right to left
      for (i=0;i<l2;i++)
        index[i] = aux[i];
      for (i=r;i>r2;i--,l2++)
        index[l2] = aux[i];
      for (i=r2+1;i<=r;i++)
        aux[i] = index[i];
      if (decreasing)
        ram_integer_mergeorder_desc_rec(data, index, aux, r2+1, r);
      else
        ram_integer_mergeorder_asc_rec(data, index, aux, r2+1, r);
    }
  }else{
    if (offset){
      for (i = l; i <= r; i++){
        index[i] -= offset;
        aux[i] = index[i];
      }
    }else{
      for (i = l; i <= r; i++)
        aux[i] = index[i];
    }
    if (decreasing)
      ram_integer_mergeorder_desc_rec(data, index, aux, l, r);
    else
      ram_integer_mergeorder_asc_rec(data, index, aux, l, r);
    nNA = 0;
  }
  if (offset)
    for (i = l; i <= r; i++)
      index[i] += offset;
  return nNA;
}


/* } === end pure C stable merge order for integers ================================================ */






/* { === begin pure C unstable shell sort/order/sortorder for integers ================================================ */

// sorts x inplace
void ram_integer_shellsort_asc(IndexT *data, IndexT l, IndexT r)
{
    IndexT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = data[i];
          j = i;
          while (j >= lh && less(v, data[j - h])){
            data[j] = data[j - h];
            j -= h;
          }
          data[j] = v;
      }
    }
}

void ram_integer_shellsort_desc(IndexT *data, IndexT l, IndexT r)
{
    IndexT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = data[i];
          j = i;
          while (j >= lh && less(data[j - h], v)){
            data[j] = data[j - h];
            j -= h;
          }
          data[j] = v;
      }
    }
}

// orders index inplace
void ram_integer_shellorder_asc(IndexT *data, IndexT *index, IndexT l, IndexT r)
{
    IndexT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = index[i];
          j = i;
          while (j >= lh && keyless(v, index[j - h])){
            index[j] = index[j-h];
            j -= h;
          }
          index[j] = v;
      }
    }
}


void ram_integer_shellorder_desc(IndexT *data, IndexT *index, IndexT l, IndexT r)
{
    IndexT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = index[i];
          j = i;
          while (j >= lh && keyless(index[j - h], v)){
            index[j] = index[j-h];
            j -= h;
          }
          index[j] = v;
      }
    }
}



/* puts index positions in ascending order for chunks of data with equal values
   ATTENTION: this only stabilizes if the index was ascending before instable ordering */
void ram_integer_postorderstabilize(IndexT *data, IndexT *index, IndexT l, IndexT r, int has_na)
{
    IndexT v;
    IndexT i, j, n=r-l+1;
    if (n>1){
      i = l;
      if (has_na){
        while(i<r){
          v = data[index[i++]];
          if (intnaequal(data[index[i]], v)){
            j = i-1;
            i++;
            while(i<=r && intnaequal(data[index[i]], v)){
              i++;
            }
            ram_integer_shellsort_asc(index, j, i-1);
          }
        }
      }else{
        while(i<r){
          v = data[index[i++]];
          if (equal(data[index[i]], v)){
            j = i-1;
            i++;
            while(i<=r && equal(data[index[i]], v)){
              i++;
            }
            ram_integer_shellsort_asc(index, j, i-1);
          }
        }
      }
    }
}






/* shellorder interface:
  - does order index such that data is sorted
  - handles an offset, especially 1 to do R2C => order => C2R
  - handles NAs
  - returns number of NAs
*/

IndexT ram_integer_shellorder(IndexT *data, IndexT *index
, IndexT offset     // 0 for C subsripts, 1 to correct R2C and C2R
, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
, int stabilize  // 0 for nothing, 1 to make sure equal values have increasing indices
)
{
  IndexT i;
  IndexT l2,r2,nNA;
  r2 = r;
  if (offset)
    for (i = l; i <= r; i++)
      index[i] -= offset;

  if (has_na){
    l2 = l;
    if (na_last){
      for (l2 = l; l2 <= r2; l2++)
        if (data[index[l2]]==NA_INTEGER){
          while(data[index[r2]]==NA_INTEGER && l2<r2)
            r2--;
          i = index[l2];
          index[l2] = index[r2];
          index[r2] = i;
          r2--;
        }
      if (l2==r2)
        l2++;
      nNA = r-r2;
      if (decreasing)
        ram_integer_shellorder_desc(data, index, l, r2);
      else
        ram_integer_shellorder_asc(data, index, l, r2);
    }else{
      for (l2 = l; l2 <= r2; r2--)
        if (data[index[r2]]==NA_INTEGER){
          while(data[index[l2]]==NA_INTEGER && l2<r2)
            l2++;
          i = index[r2];
          index[r2] = index[l2];
          index[l2] = i;
          l2++;
        }
      if (l2==r2)
        r2--;
      nNA = l2-l;
      if (decreasing)
        ram_integer_shellorder_desc(data, index, l2, r);
      else
        ram_integer_shellorder_asc(data, index, l2, r);
    }
  }else{
    if (decreasing)
      ram_integer_shellorder_desc(data, index, l, r);
    else
      ram_integer_shellorder_asc(data, index, l, r);
    nNA = 0;
  }
  if (stabilize)
    ram_integer_postorderstabilize(data, index, l, r, has_na);
  if (offset)
    for (i = l; i <= r; i++)
      index[i] += offset;
  return nNA;
}



/* shellsort interface:
  - does sort data
  - handles NAs
  - returns number of NAs
*/

IndexT ram_integer_shellsort(IndexT *data, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
)
{
  IndexT v;
  IndexT l2,r2,nNA;
  r2 = r;

  if (has_na){
    l2 = l;
    if (na_last){
      for (l2 = l; l2 <= r2; l2++)
        if (data[l2]==NA_INTEGER){
          while(data[r2]==NA_INTEGER && l2<r2)
            r2--;
          v = data[l2];
          data[l2] = data[r2];
          data[r2] = v;
          r2--;
        }
      if (l2==r2)
        l2++;
      nNA = r - r2;
      if (decreasing)
        ram_integer_shellsort_desc(data, l, r2);
      else
        ram_integer_shellsort_asc(data, l, r2);
    }else{
      for (l2 = l; l2 <= r2; r2--)
        if (data[r2]==NA_INTEGER){
          while(data[l2]==NA_INTEGER && l2<r2)
            l2++;
          v = data[r2];
          data[r2] = data[l2];
          data[l2] = v;
          l2++;
        }
      if (l2==r2)
        r2--;
      nNA = l2 - l;
      if (decreasing)
        ram_integer_shellsort_desc(data, l2, r);
      else
        ram_integer_shellsort_asc(data, l2, r);
    }
  }else{
    if (decreasing)
      ram_integer_shellsort_desc(data, l, r);
    else
      ram_integer_shellsort_asc(data, l, r);
    nNA = 0;
  }
  return nNA;
}


/* } === end pure C unstable shell sort/order/sortorder for integers ================================================ */



/* { === begin pure C unstable shell sort/order/sortorder for doubles ================================================ */

// sorts data inplace
void ram_double_shellsort_asc(ValueT *data, IndexT l, IndexT r)
{
    ValueT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = data[i];
          j = i;
          while (j >= lh && less(v, data[j - h])){
            data[j] = data[j - h];
            j -= h;
          }
          data[j] = v;
      }
    }
}

void ram_double_shellsort_desc(ValueT *data, IndexT l, IndexT r)
{
    ValueT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = data[i];
          j = i;
          while (j >= lh && less(data[j - h], v)){
            data[j] = data[j - h];
            j -= h;
          }
          data[j] = v;
      }
    }
}

// orders index inplace
void ram_double_shellorder_asc(ValueT *data, IndexT *index, IndexT l, IndexT r)
{
    IndexT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = index[i];
          j = i;
          while (j >= lh && keyless(v, index[j - h])){
            index[j] = index[j-h];
            j -= h;
          }
          index[j] = v;
      }
    }
}


void ram_double_shellorder_desc(ValueT *data, IndexT *index, IndexT l, IndexT r)
{
    IndexT v;
    IndexT i, j, h, lh, t, n=r-l+1;

    for (t = 0; incs[t] > n; t++);
    for (; t < SHELLARRAYSIZE; ++t){
      h = incs[t];
      lh = l+h;
      for (i = lh; i <= r; i++) {
          v = index[i];
          j = i;
          while (j >= lh && keyless(index[j - h], v)){
            index[j] = index[j-h];
            j -= h;
          }
          index[j] = v;
      }
    }
}




/* puts index positions in ascending order for chunks of data with equal values
   ATTENTION: this only stabilizes if the index was ascending before instable ordering */
void ram_double_postorderstabilize(ValueT *data, IndexT *index, IndexT l, IndexT r, int has_na)
{
    ValueT v;
    IndexT i, j, n=r-l+1;
    if (n>1){
      i = l;
      if (has_na){
        while(i<r){
          v = data[index[i++]];
          if (naequal(data[index[i]], v)){
            j = i-1;
            i++;
            while(i<=r && naequal(data[index[i]], v)){
              i++;
            }
            ram_integer_shellsort_asc(index, j, i-1);
          }
        }
      }else{
        while(i<r){
          v = data[index[i++]];
          if (equal(data[index[i]], v)){
            j = i-1;
            i++;
            while(i<=r && equal(data[index[i]], v)){
              i++;
            }
            ram_integer_shellsort_asc(index, j, i-1);
          }
        }
      }
    }
}



/* shellorder interface:
  - does order index such that data is sorted
  - handles an offset, especially 1 to do R2C => order => C2R
  - handles NAs
  - returns number of NAs
  - xxx stabilize does not work for NAs so far, here just for testing
*/

IndexT ram_double_shellorder(ValueT *data, IndexT *index
, IndexT offset     // 0 for C subsripts, 1 to correct R2C and C2R
, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
, int stabilize  // 0 for nothing, 1 to make sure equal values have increasing indices
)
{
  IndexT i;
  IndexT l2,r2,nNA;
  r2 = r;
  if (offset)
    for (i = l; i <= r; i++)
      index[i] -= offset;

  if (has_na){
    l2 = l;
    if (na_last){
      for (l2 = l; l2 <= r2; l2++)
        if (ISNAN(data[index[l2]])){
          while(ISNAN(data[index[r2]]) && l2<r2)
            r2--;
          i = index[l2];
          index[l2] = index[r2];
          index[r2] = i;
          r2--;
        }
      if (l2==r2)
        l2++;
      nNA = r-r2;
      if (decreasing)
        ram_double_shellorder_desc(data, index, l, r2);
      else
        ram_double_shellorder_asc(data, index, l, r2);
    }else{
      for (l2 = l; l2 <= r2; r2--)
        if (ISNAN(data[index[r2]])){
          while(ISNAN(data[index[l2]]) && l2<r2)
            l2++;
          i = index[r2];
          index[r2] = index[l2];
          index[l2] = i;
          l2++;
        }
      if (l2==r2)
        r2--;
      nNA = l2-l;
      if (decreasing)
        ram_double_shellorder_desc(data, index, l2, r);
      else
        ram_double_shellorder_asc(data, index, l2, r);
    }
  }else{
    if (decreasing)
      ram_double_shellorder_desc(data, index, l, r);
    else
      ram_double_shellorder_asc(data, index, l, r);
    nNA = 0;
  }
  if (stabilize)
    ram_double_postorderstabilize(data, index, l, r, has_na);
  if (offset)
    for (i = l; i <= r; i++)
      index[i] += offset;
  return nNA;
}


/* shellsort interface:
  - does sort data
  - handles NAs
  - returns number of NAs
*/

IndexT ram_double_shellsort(ValueT *data, IndexT l, IndexT r
, int has_na     // 0 for pure doubles, 1 if NA or NaN can be present
, int na_last    // 0 for NA NaN left, 1 for NA NaN right
, int decreasing // 0 for ascending, 1 for descending
)
{
  ValueT v;
  IndexT l2,r2,nNA;
  r2 = r;

  if (has_na){
    l2 = l;
    if (na_last){
      for (l2 = l; l2 <= r2; l2++)
        if (ISNAN(data[l2])){
          while(ISNAN(data[r2]) && l2<r2)
            r2--;
          v = data[l2];
          data[l2] = data[r2];
          data[r2] = v;
          r2--;
        }
      if (l2==r2)
        l2++;
      nNA = r - r2;
      if (decreasing)
        ram_double_shellsort_desc(data, l, r2);
      else
        ram_double_shellsort_asc(data, l, r2);
    }else{
      for (l2 = l; l2 <= r2; r2--)
        if (ISNAN(data[r2])){
          while(ISNAN(data[l2]) && l2<r2)
            l2++;
          v = data[r2];
          data[r2] = data[l2];
          data[l2] = v;
          l2++;
        }
      if (l2==r2)
        r2--;
      nNA = l2 - l;
      if (decreasing)
        ram_double_shellsort_desc(data, l2, r);
      else
        ram_double_shellsort_asc(data, l2, r);
    }
  }else{
    if (decreasing)
      ram_double_shellsort_desc(data, l, r);
    else
      ram_double_shellsort_asc(data, l, r);
    nNA = 0;
  }
  return nNA;
}

/* } === end pure C unstable shell sort/order/sortorder for doubles ================================================ */



/* { === end pure C unstable linear-time keysort and stable linear-time keyorder for integer ==================== */


// premise: data contains integers from offset+1..offset+M
// if it contains NAs, has_na needs to be TRUE (1)
// count has M+1 elements (NA count stored at position 0)
// we only consider values stored in data from l to r
void ram_integer_keycount(
    IndexT *data
  , IndexT *count
  , IndexT keyoffset
  , IndexT keylength
  , IndexT l, IndexT r
  , int has_na
)
{
  IndexT i;

  keylength++;
  for (i=0;i<=keylength;i++)count[i]=0;
  count -= keyoffset; // move the pointer such that the first elements will hit pos 0 of the real vector (save -keyoffset in each iteration)
  if (has_na){
    for (i=l;i<=r;i++)
      count[data[i]==NA_INTEGER ? keyoffset : data[i]]++;
  }else{
    for (i=l;i<=r;i++)count[data[i]]++;
  }
}

void ram_integer_keyindexcount(
    IndexT *data
  , IndexT *index
  , IndexT *count
  , IndexT offset
  , IndexT keyoffset, IndexT keylength
  , IndexT l, IndexT r
  , int has_na
)
{
  IndexT i;

  for (i=0;i<=keylength;i++)count[i]=0;
  count -= keyoffset; // move the pointer such that the first elements will hit pos 0 of the real vector (save -keyoffset in each iteration)
  data -= offset; // move the pointer such that the first elements will hit pos 0 of the real vector (save -offset in each iteration)
  if (has_na){
    for (i=l;i<=r;i++)
      count[data[index[i]]==NA_INTEGER ? keyoffset : data[index[i]]]++;
  }else{
    for (i=l;i<=r;i++)count[data[index[i]]]++;
  }
}


// premise: data contains integers from keyoffset+1..keyoffset+keylength
// if it contains NAs, has_na needs to be TRUE (1)
// count has keylength+2 elements (NA refers to position 0, position keylength+2 is unused)
// in count we expect the counts (after calling ram_integer_keycount) with NA in pos 0 and first in pos 1
// after this call we have the NAcount at keylength+1 or 0 (decreasing)
// after this call we have the NAfirstpos at keylength or 1 (decreasing)
// after this call we have the first position at 0 or 2 (decreasing)
void ram_integer_keycount2start(
    IndexT *count
  , IndexT keylength
  , int has_na, int na_last, int decreasing
)
{
  IndexT i;

  if (na_last){
    if (decreasing){
      // na_last and decreasing:
      // count of NA in 0, start of NA in 1, start of first element in 2..keylength+1
      count[keylength+1]=0;
      for (i=keylength;i>0;i--)count[i] += count[i+1];
      //count[1] properly set by last iteration;
      //count[0] already properly intitialized with NAcount
    }else{
      // na_last and increasing:
      // count of NA in keylength+1, start of NA in keylength, start of first element in 0..keylength-1
      count[keylength+1]=count[0];
      count[0] = 0;
      for (i=1;i<=keylength;i++)count[i] += count[i-1];
      //count[keylength] properly set by last iteration
    }
  }else{
    if (decreasing){
      // na_first and decreasing:
      // count of NA in 0, start of NA in 1, start of first element in 2..keylength+1
      count[keylength+1]=count[0];
      for (i=keylength;i>1;i--)count[i] += count[i+1];
      count[1]=0;
      //count[0] already properly intitialized with NAcount
    }else{
      // na_first and increasing:
      // count of NA in keylength+1, start of NA in keylength, start of first element in 0..keylength-1
      count[keylength+1]=count[0];
      //count[0] already properly intitialized with NAcount
      for (i=1;i<keylength;i++)count[i] += count[i-1];
      count[keylength]=0;
    }
  }
}




IndexT ram_integer_keysort(
    IndexT *data
  , IndexT *count
  , IndexT keyoffset // R index 1 correpsonds to keyoffset 0 !!!
  , IndexT keylength
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing
)
{
  IndexT i, v, lim;

  // count all keys including NAs
  ram_integer_keycount(
      data
    , count
    , keyoffset, keylength
    , l, r
    , has_na
  );

  // set NAs in data
  if (has_na){
    if (na_last){
      for (lim=r-count[0];r>lim;r--)
        data[r] = NA_INTEGER;
    }else{
      for (lim=l+count[0];l<lim;l++)
        data[l] = NA_INTEGER;
    }
  }

  // add sorted values to data
  if (decreasing){
    for (i=keylength;i>=1;i--){
      v = i + keyoffset;
      for (lim=l+count[i];l<lim;l++)
        data[l] = v;
    }
  }else{
    for (i=1;i<=keylength;i++){
      v = i + keyoffset;
      for (lim=l+count[i];l<lim;l++)
        data[l] = v;
    }
  }

  return count[0];
}



IndexT ram_integer_keyorder(
    IndexT *data
  , IndexT *index, IndexT *auxindex
  , IndexT *count
  , IndexT offset
  , IndexT keyoffset, IndexT keylength
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing
)
{
  IndexT i, NAcount, NApos;

  ram_integer_keyindexcount(
      data
    , index
    , count
    , offset
    , keyoffset, keylength
    , l, r
    , has_na
  );

  ram_integer_keycount2start(
      count
    , keylength
    , has_na, na_last, decreasing
  );

  // see the defintions in ram_integer_keycount2start
  if (decreasing){
    NApos = count[1];
    NAcount = count[0];
    count = count+1;
  }else{
    NApos = count[keylength];
    NAcount = count[keylength+1];
    count = count-1;
  }

  count -= keyoffset; // move the pointer such that the first elements will hit pos 0 of the real vector (save -keyoffset in each iteration)
  data -= offset; // move the pointer such that the first elements will hit pos 0 of the real vector (save -offset in each iteration)

  for (i=l;i<=r;i++){
    if (data[index[i]]==NA_INTEGER)
      auxindex[NApos++] = index[i];
    else
      auxindex[count[data[index[i]]]++] = index[i];
  }

  // xxx use memcpy here ??
  for (i=l;i<=r;i++)index[i]=auxindex[i];

  return NAcount;
}



// for integer radix sort
#define BITSWORD 16
#define NWORD 65536
#define LOPART(x)(x&0x0000FFFF)
// #define HIPART(x)(x<0 ? (x>>BITSWORD)&0x00007FFF: (x>>BITSWORD)|0x00008000)
#define HIPART(x)(((x>>BITSWORD)&0x0000FFFF)^(0x00008000))

/*  structure of count: 0..n where n=r-l+1
    after counting the frequencies of data 0:(NWORD-1) are stored in pos 1:NWORD and NAcount
    the start positions are stored beginning with l in pos 0:(NWORD-1) and NApos  which are then ++
    decreasing start positions are stored beginning with r in pos 0:(NWORD-1) and NApos  which are then --
*/

void ram_integer_losort(
    IndexT *datain
  , IndexT *dataout
  , IndexT *count
  , IndexT l, IndexT r
  , int decreasing
)
{
  IndexT i;
  for (i=0;i<=NWORD;i++)count[i]=0;
  for (i=l;i<=r;i++)count[LOPART(datain[i])+1]++;
  if (decreasing){
    count[0] = r;
    for (i=1;i<=NWORD;i++) count[i] = count[i-1] - count[i];
    for (i=r;i>=l;i--)dataout[count[LOPART(datain[i])]--] = datain[i];
  }else{
    count[0] = l;
    for (i=1;i<=NWORD;i++)count[i]+=count[i-1];
    for (i=l;i<=r;i++)dataout[count[LOPART(datain[i])]++] = datain[i];
  }
}




IndexT ram_integer_hisort(
    IndexT *datain
  , IndexT *dataout
  , IndexT *count
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing
)
{
  IndexT i, NApos, NAcount=0;

  for (i=0;i<=NWORD;i++)count[i]=0;
  if (has_na){
    for (i=l;i<=r;i++){
      if (datain[i]==NA_INTEGER)
        NAcount++;
      else
        count[HIPART(datain[i])+1]++;
    }
  }else{
    for (i=l;i<=r;i++)
      count[HIPART(datain[i])+1]++;
  }

  if (has_na && NAcount){
    if (na_last){
      if (decreasing){
        NApos=r;
        count[0] = r-NAcount;
      }else{
        NApos=r-NAcount+1;
        count[0] = l;
      }
    }else{
      if (decreasing){
        NApos=l+NAcount-1;
        count[0] = r;
      }else{
        NApos=l;
        count[0] = l+NAcount;
      }
    }
    if (decreasing){
      for (i=1;i<=NWORD;i++)count[i] = count[i-1] - count[i];
      for (i=r;i>=l;i--){
        if (datain[i]==NA_INTEGER)
          dataout[NApos--]=datain[i];
        else
          dataout[count[HIPART(datain[i])]--] = datain[i];
      }
    }else{
      for (i=1;i<=NWORD;i++)count[i]+=count[i-1];
      for (i=l;i<=r;i++){
        if (datain[i]==NA_INTEGER)
          dataout[NApos++]=datain[i];
        else
          dataout[count[HIPART(datain[i])]++] = datain[i];
      }
    }
  }else{
    if (decreasing){
      count[0] = r;
      for (i=1;i<=NWORD;i++)count[i] = count[i-1] - count[i];
      for (i=r;i>=l;i--)dataout[count[HIPART(datain[i])]--] = datain[i];
    }else{
      count[0] = l;
      for (i=1;i<=NWORD;i++)count[i]+=count[i-1];
      for (i=l;i<=r;i++)dataout[count[HIPART(datain[i])]++] = datain[i];
    }
  }
  return NAcount;
}


IndexT ram_integer_radixsort(
    IndexT *data
  , IndexT *dataaux
  , IndexT *count
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing
)
{
  IndexT NAcount=0;
  ram_integer_losort(
      data
    , dataaux
    , count
    , l, r
    , decreasing
  );
  NAcount = ram_integer_hisort(
      dataaux
    , data
    , count
    , l, r
    , has_na, na_last, decreasing
  );
  return NAcount;
}




void ram_integer_loorder(
    IndexT *data
  , IndexT *indexin
  , IndexT *indexout
  , IndexT *count
  , IndexT l, IndexT r
  , int decreasing
)
{
  IndexT i;
  for (i=0;i<=NWORD;i++)count[i]=0;
  for (i=l;i<=r;i++)count[LOPART(data[indexin[i]])+1]++;
  if (decreasing){
    count[0] = r;
    for (i=1;i<=NWORD;i++) count[i] = count[i-1] - count[i];
    for (i=r;i>=l;i--)indexout[count[LOPART(data[indexin[i]])]--] = indexin[i];
  }else{
    count[0] = l;
    for (i=1;i<=NWORD;i++)count[i]+=count[i-1];
    for (i=l;i<=r;i++)indexout[count[LOPART(data[indexin[i]])]++] = indexin[i];
  }
}


IndexT ram_integer_hiorder(
    IndexT *data
  , IndexT *indexin
  , IndexT *indexout
  , IndexT *count
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing
)
{
  IndexT i, NApos, NAcount=0;

  for (i=0;i<=NWORD;i++)count[i]=0;
  if (has_na){
    for (i=l;i<=r;i++){
      if (data[indexin[i]]==NA_INTEGER)
        NAcount++;
      else
        count[HIPART(data[indexin[i]])+1]++;
    }
  }else{
    for (i=l;i<=r;i++)
      count[HIPART(data[indexin[i]])+1]++;
  }

  if (has_na && NAcount){
    if (na_last){
      if (decreasing){
        NApos=r;
        count[0] = r-NAcount;
      }else{
        NApos=r-NAcount+1;
        count[0] = l;
      }
    }else{
      if (decreasing){
        NApos=l+NAcount-1;
        count[0] = r;
      }else{
        NApos=l;
        count[0] = l+NAcount;
      }
    }
    if (decreasing){
      for (i=1;i<=NWORD;i++)count[i] = count[i-1] - count[i];
      for (i=r;i>=l;i--){
        if (data[indexin[i]]==NA_INTEGER)
          indexout[NApos--]=indexin[i];
        else
          indexout[count[HIPART(data[indexin[i]])]--]=indexin[i];
      }
    }else{
      for (i=1;i<=NWORD;i++)count[i]+=count[i-1];
      for (i=l;i<=r;i++){
        if (data[indexin[i]]==NA_INTEGER)
          indexout[NApos++]=indexin[i];
        else
          indexout[count[HIPART(data[indexin[i]])]++]=indexin[i];
      }
    }
  }else{
    if (decreasing){
      count[0] = r;
      for (i=1;i<=NWORD;i++)count[i] = count[i-1] - count[i];
      for (i=r;i>=l;i--)indexout[count[HIPART(data[indexin[i]])]--]=indexin[i];
    }else{
      count[0] = l;
      for (i=1;i<=NWORD;i++)count[i]+=count[i-1];
      for (i=l;i<=r;i++)indexout[count[HIPART(data[indexin[i]])]++]=indexin[i];
    }
  }
  return NAcount;
}


/* note, R_qsort_int_I is slightly faster, but not stable, not guaranteed to be O(n*log(n)) and does not handle NAs */
IndexT ram_integer_radixorder(
    IndexT *data
  , IndexT *index
  , IndexT *indexaux
  , IndexT *count
  , IndexT offset
  , IndexT l, IndexT r
  , int has_na, int na_last, int decreasing
)
{
  IndexT i, NAcount=0;

  if (offset)
    for (i = l; i <= r; i++)
      index[i] -= offset;

  ram_integer_loorder(
      data
    , index
    , indexaux
    , count
    , l, r
    , decreasing
  );
  NAcount = ram_integer_hiorder(
      data
    , indexaux
    , index
    , count
    , l, r
    , has_na, na_last, decreasing
  );

  if (offset)
    for (i = l; i <= r; i++)
      index[i] += offset;

  return NAcount;
}


/* { === end pure C unstable linear-time keysort and stable linear-time keyorder for integer ==================== */


SEXP r_ram_mergeorder(
  SEXP x_            /* data vector */
, SEXP index_        /* index vector, must be provided initialized with valid positions in R counting */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{

  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);

  int *index;
  index = INTEGER(index_);

  IndexT *auxindex;
  auxindex = (IndexT *) R_alloc(n, sizeof(IndexT));

  switch (TYPEOF(x_)){
    case LGLSXP:
    case INTSXP:
    {
      int *y;
      y = INTEGER(x_);
      INTEGER(ret_)[0] = ram_integer_mergeorder(y, index, auxindex, 1, 0, n-1, has_na, na_last, decreasing);
      break;
    }
    case REALSXP:
    {
      double *x;
      x = REAL(x_);
      INTEGER(ret_)[0] = ram_double_mergeorder(x, index, auxindex, 1, 0, n-1, has_na, na_last, decreasing);
      /* xx some experimental check: more cache-friendly and faster but requires more RAM
      double *auxdata;
      auxdata = (double *) R_alloc(n, sizeof(double));
      INTEGER(ret_)[0] = ram_double_mergeorder2(x, auxdata, index, auxindex, 0, n-1, has_na, na_last, decreasing);
      */
      break;
    }
    default:
      error("unimplemented type in mergeorder");
  }

  UNPROTECT(1);
  return ret_;
}





// in-ram merge sort
SEXP r_ram_mergesort(
  SEXP x_            /* data vector */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{

  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);


  switch (TYPEOF(x_)){
    case LGLSXP:
    case INTSXP:
    {
      int *y;
      y = INTEGER(x_);
      IndexT *indexaux;
      indexaux = (IndexT *) R_alloc(n, sizeof(IndexT));
      INTEGER(ret_)[0] = ram_integer_mergesort(y, indexaux, 0, n-1, has_na, na_last, decreasing);
      break;
    }
    case REALSXP:
    {
      double *x;
      x = REAL(x_);
      ValueT *valueaux;
      valueaux = (ValueT *) R_alloc(n, sizeof(ValueT));
      INTEGER(ret_)[0] = ram_double_mergesort(x, valueaux, 0, n-1, has_na, na_last, decreasing);
      break;
    }
    default:
      error("unimplemented type in mergesort");
  }

  UNPROTECT(1);
  return ret_;
}



// in-ram merge order
SEXP r_ram_shellorder(
  SEXP x_            /* data vector */
, SEXP index_        /* index vector, must be provided initialized with valid positions in R counting */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
, SEXP stabilize_    /* logical scalar */
)
{

  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);
  Rboolean stabilize = asLogical(stabilize_);

  int *index;
  index = INTEGER(index_);

  switch (TYPEOF(x_)){
    case LGLSXP:
    case INTSXP:
    {
      int *y;
      y = INTEGER(x_);
      INTEGER(ret_)[0] = ram_integer_shellorder(y, index, 1, 0, n-1, has_na, na_last, decreasing, stabilize);
      break;
    }
    case REALSXP:
    {
      double *x;
      x = REAL(x_);
      INTEGER(ret_)[0] = ram_double_shellorder(x, index, 1, 0, n-1, has_na, na_last, decreasing, stabilize);
      break;
    }
    default:
      error("unimplemented type in shellorder");
  }

  UNPROTECT(1);
  return ret_;
}


// in-ram merge sort
SEXP r_ram_shellsort(
  SEXP x_            /* data vector */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{

  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);

  switch (TYPEOF(x_)){
    case LGLSXP:
    case INTSXP:
    {
      int *y;
      y = INTEGER(x_);
      INTEGER(ret_)[0] = ram_integer_shellsort(y, 0, n-1, has_na, na_last, decreasing);
      break;
    }
    case REALSXP:
    {
      double *x;
      x = REAL(x_);
      INTEGER(ret_)[0] = ram_double_shellsort(x, 0, n-1, has_na, na_last, decreasing);
      break;
    }
    default:
      error("unimplemented type in shellsort");
  }

  UNPROTECT(1);
  return ret_;
}





// in-ram key order
SEXP r_ram_keyorder(
  SEXP x_            /* data vector */
, SEXP index_        /* index vector, must be provided initialized with valid positions in R counting */
, SEXP keyrange_       /* integer[2] */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  IndexT *x = INTEGER(x_);
  IndexT *index = INTEGER(index_);

  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);

  IndexT keyoffset = INTEGER(keyrange_)[0] - 1; // note that minvalue 1 is mapped to offset 0
  IndexT keylength = INTEGER(keyrange_)[1] - INTEGER(keyrange_)[0] + 1;

  IndexT *count;
  IndexT *auxindex;

  count   = (IndexT *) R_alloc(keylength+2, sizeof(IndexT));
  auxindex = (IndexT *) R_alloc(n, sizeof(IndexT));

  INTEGER(ret_)[0] = ram_integer_keyorder(
    x
  , index, auxindex
  , count
  , 1 // offset
  , keyoffset, keylength
  , 0, n-1
  , has_na, na_last, decreasing
  );

  UNPROTECT(1);
  return ret_;
}



// in-ram key sort
SEXP r_ram_keysort(
  SEXP x_            /* data vector */
, SEXP keyrange_       /* integer[2] */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{

  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  IndexT *x = INTEGER(x_);

  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);

  IndexT keyoffset = INTEGER(keyrange_)[0] - 1; // note that minvalue 1 is mapped to offset 0
  IndexT keylength = INTEGER(keyrange_)[1] - INTEGER(keyrange_)[0] + 1;

  IndexT *count;
  count   = (IndexT *) R_alloc(keylength+2, sizeof(IndexT));

  INTEGER(ret_)[0] = ram_integer_keysort(
    x
  , count
  , keyoffset, keylength
  , 0, n-1
  , has_na, na_last, decreasing
  );

  UNPROTECT(1);
  return ret_;
}



SEXP r_ram_radixsort(
  SEXP x_            /* data vector */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{

  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  IndexT *x = INTEGER(x_);

  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);

  IndexT *xaux, *count;

  xaux   = (IndexT *) R_alloc(n, sizeof(IndexT));
  count  = (IndexT *) R_alloc(NWORD+1, sizeof(IndexT));

  INTEGER(ret_)[0] = ram_integer_radixsort(
    x
  , xaux
  , count
  , 0, n-1
  , has_na, na_last, decreasing
  );

  UNPROTECT(1);
  return ret_;
}


SEXP r_ram_radixorder(
  SEXP x_            /* data vector */
, SEXP index_        /* integer vector */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{

  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  int n = LENGTH(x_);
  IndexT *x = INTEGER(x_);
  IndexT *index = INTEGER(index_);

  Rboolean has_na     = asLogical(has_na_);
  Rboolean na_last    = asLogical(na_last_);
  Rboolean decreasing = asLogical(decreasing_);

  IndexT *auxindex, *count;

  auxindex  = (IndexT *) R_alloc(n, sizeof(IndexT));
  count     = (IndexT *) R_alloc(NWORD+1, sizeof(IndexT));

  INTEGER(ret_)[0] = ram_integer_radixorder(
    x
  , index
  , auxindex
  , count
  , 1
  , 0, n-1
  , has_na, na_last, decreasing
  );

  UNPROTECT(1);
  return ret_;
}





SEXP r_ff_double_ordermerge(
  SEXP ffmode_
, SEXP ff_            /* ff data vector */
, SEXP index_        /* NULL or ff index vector, xx TODO we can speed up by implementing true internal sorting, internally we currently do always ordering */
, SEXP auxff_        /* auxilliary data vector */
, SEXP auxindex_     /* NULL or auxilliary index vector (needed if index_ given) */
, SEXP left_         /* first R position to be ordered */
, SEXP right_        /* last R position to be ordered */
, SEXP method_       /* 0=mergeorder 1=shellorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
, SEXP mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
, SEXP orderindex_   /* logical scalar: shall we reorder index_? (otherwise we simpy write it) */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  void *fromvalue;
  void *fromindex;
  void *tovalue;
  void *toindex;
  fromvalue = R_ExternalPtrAddr(ff_);
  fromindex = R_ExternalPtrAddr(index_);
  tovalue = R_ExternalPtrAddr(auxff_);
  toindex = R_ExternalPtrAddr(auxindex_);
  Rboolean orderindex = asLogical(orderindex_);
  Rboolean decreasing = asLogical(decreasing_);
  Rboolean has_na = asLogical(has_na_);
  Rboolean na_last = asLogical(na_last_);
  Rboolean na_reverse = decreasing ? !na_last : na_last;
  IndexT left      = asInteger(left_) - 1;
  IndexT right     = asInteger(right_) - 1;
  IndexT ordersize = asInteger(ordersize_);
  IndexT mergesize = asInteger(mergesize_);
  IndexT method    = asInteger(method_);
  IndexT mergesize2 = 2*mergesize;
  IndexT nNA = 0;

  ValueT *valuebuffer;
  IndexT *indexbuffer;
  IndexT *auxindexbuffer;

  ValueT *valuebuffer1;
  IndexT *indexbuffer1;
  ValueT *valuebuffer2;
  IndexT *indexbuffer2;

  // we use R_Calloc because then we can free big RAM after the ordering pass and have more for the file system cache
  valuebuffer = (ValueT *) R_Calloc(ordersize, ValueT);
  indexbuffer = (IndexT *) R_Calloc(ordersize, IndexT);
  if (method!=1 || orderindex)
    auxindexbuffer = (IndexT *) R_Calloc(ordersize, IndexT);
  else
    auxindexbuffer = 0; // keep compiler quiet

  IndexT l,r,i,n,N,offset;
  IndexT l1,l2,r1,r2,n1,n2,m1,m2;
  IndexT i1,i2;
  IndexT L1,L2,R1,R2;
  IndexT T=right-left+1;
  IndexT merges = 0;

  /* define function pointers and assign */
  void (*ff_vmode_get_contiguous)( void *handle, int index, int size, ValueT *ret );
  void (*ff_vmode_set_contiguous)( void *, int, int, ValueT * );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_SINGLE
  case 10: ff_vmode_get_contiguous =  ff_single_get_contiguous;
           ff_vmode_set_contiguous =  ff_single_set_contiguous; break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ff_vmode_get_contiguous =  ff_double_get_contiguous;
           ff_vmode_set_contiguous =  ff_double_set_contiguous; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }

  // ValueT (*ff_vmode_get)( void *, int );
  void (*ff_vmode_set)( void *, int, ValueT );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_SINGLE
  case 10: //ff_vmode_get =  ff_single_get;
           ff_vmode_set =  ff_single_set; break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: //ff_vmode_get =  ff_double_get;
           ff_vmode_set =  ff_double_set; break;
#endif
#if VMODE_COMPILE_COMPLEX
  case 12: //ff_vmode_get =  ff_double_get;
           ff_vmode_set =  ff_double_set; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }


  N = ordersize;
  while (N<T){
    merges+=1;
    N=N+N;
  }

#if VERBOSE_LEVEL>0
  Rprintf("order pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("ordermerge,from,to,type,L1,l1,r1,R1,L2,l2,r2,R2\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d,,,,,,,,,\n", l, r); R_FlushConsole();
#endif

    // read the value chunk
    ff_vmode_get_contiguous( fromvalue, l, n, valuebuffer);

    // initialize the local index 0:(n-1)
    for (i = 0; i<n; i++){
      indexbuffer[i]=i;
    }

    // order the chunk
    if (method!=1 || orderindex)
      nNA += ram_double_mergeorder(valuebuffer, indexbuffer, auxindexbuffer, 0, 0, n-1, has_na, na_last, decreasing);
    else
      nNA += ram_double_shellorder(valuebuffer, indexbuffer, 0, 0, n-1, has_na, na_last, decreasing, 0); // xx shall we stabilize?

    // write the value chunk
    if (merges%2)
      for (i = 0; i<n; i++){
        ff_vmode_set( tovalue, l+i, valuebuffer[indexbuffer[i]]);
      }
    else
      for (i = 0; i<n; i++){
        ff_vmode_set( fromvalue, l+i, valuebuffer[indexbuffer[i]]);
      }

    if (index_!=R_NilValue){
      if (orderindex){
        ff_integer_get_contiguous( fromindex, l-left, n, auxindexbuffer);
        for (i = 0; i<n; i++){
          indexbuffer[i] = auxindexbuffer[indexbuffer[i]];
        }
      }else{
        offset = l + 1;
        for (i = 0; i<n; i++){
          indexbuffer[i] = offset + indexbuffer[i];  // C2R positions
        }
      }
      if (merges%2){
        ff_integer_set_contiguous( toindex, l-left, n, indexbuffer);
      }else{
        ff_integer_set_contiguous( fromindex, l-left, n, indexbuffer);
      }
    }


  }

  // this was large RAM, let's free here, then we have it for the filesystem cache
  R_Free(valuebuffer);
  R_Free(indexbuffer);
  if (method!=1 || orderindex)
    R_Free(auxindexbuffer);


  N = ordersize;
  if (n<T){

    valuebuffer1 = (ValueT *) R_Calloc(mergesize, ValueT);
    valuebuffer2 = (ValueT *) R_Calloc(mergesize, ValueT);
    valuebuffer = (ValueT *) R_Calloc(mergesize2, ValueT);

    if (index_==R_NilValue){

      while(N<T){
#if VERBOSE_LEVEL>0
        Rprintf("merge pass #%d\n", merges); R_FlushConsole();
#endif
        if (merges%2){
          fromvalue = R_ExternalPtrAddr(auxff_);
          tovalue = R_ExternalPtrAddr(ff_);
        }else{
          tovalue = R_ExternalPtrAddr(auxff_);
          fromvalue = R_ExternalPtrAddr(ff_);
        }
        n = N;
        N = 2*n;
        L1 = left;
        L2 = left+n;
        R2=-1;
        while (R2<right){
          R1 = L1 + n - 1;
          R2 = R1 + n;
          if (R2>right){
            if (L2>right){
              // the last pair only has one chunk, no need to merge, but let's not forget to copy from from to to
              R1 = right;
              for (l1 = L1; l1<=R1; l1+=mergesize2){
                r1 = l1 + mergesize2 - 1;
                if (r1>R1)
                  r1 = R1;
                n1 = r1 - l1 + 1;
#if VERBOSE_LEVEL>1
                Rprintf("%d,%d,%d,SKIP,%d,%d,%d,%d,,,,\n", merges,n, N, L1, l1, r1, R1); R_FlushConsole();
#endif
                ff_vmode_get_contiguous( fromvalue, l1, n1, valuebuffer);
                ff_vmode_set_contiguous( tovalue, l1, n1, valuebuffer);
              }
              break;
            }else{
              R2 = right;
            }
          }

          l  = L1;
          l1 = L1;
          l2 = L2;
          n1 = 0;
          n2 = 0;
          i1 = 0;
          i2 = 0;
          while(1){
            // move everything to the left in the in-buffers
            if (i1<n1){
              n1 = n1 - i1;
              memmove(valuebuffer1, valuebuffer1+i1, n1*sizeof(ValueT));
              m1 = mergesize - n1;
            }else{
              n1 = 0;
              m1 = mergesize;
            }
            if (i2<n2){
              n2 = n2 - i2;
              memmove(valuebuffer2, valuebuffer2+i2, n2*sizeof(ValueT));
              m2 = mergesize - n2;
            }else{
              n2 = 0;
              m2 = mergesize;
            }

            // calculating the read positions
            r1 = l1 + m1 - 1;
            r2 = l2 + m2 - 1;
            if (r1>R1){
              r1 = R1;
              m1 = r1 - l1 + 1;
            }
            if (r2>R2){
              r2 = R2;
              m2 = r2 - l2 + 1;
            }

            // filling the in-buffers
#if VERBOSE_LEVEL>1
            Rprintf("%d,%d,%d,MERGE,%d,%d,%d,%d,%d,%d,%d,%d\n", merges, n, N, L1, l1, r1, R1, L2, l2, r2, R2); R_FlushConsole();
#endif
            if (m1>0){
              ff_vmode_get_contiguous( fromvalue, l1, m1, valuebuffer1+n1);
            }
            if (m2>0){
              ff_vmode_get_contiguous( fromvalue, l2, m2, valuebuffer2+n2);
            }
            l1 += m1;
            l2 += m2;
            n1 += m1;
            n2 += m2;

            // doing the merge
            if (nNA){
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (naless(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }else{
                  if (naless(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }
              }
            }else{ // not has_na
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (less(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }else{
                  if (less(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }
              }
            }


            // flushing the out-buffers
            ff_vmode_set_contiguous( tovalue, l, i, valuebuffer);

            l += i;
            if (l > R2)
              break;
          }

          L1 += N;
          L2 += N;
        }
        merges -= 1;
      }

    }else{

      indexbuffer1 = (IndexT *) R_Calloc(mergesize, IndexT);
      indexbuffer2 = (IndexT *) R_Calloc(mergesize, IndexT);
      indexbuffer = (IndexT *) R_Calloc(mergesize2, IndexT);

      while(N<T){
#if VERBOSE_LEVEL>0
        Rprintf("merge pass #%d\n", merges); R_FlushConsole();
#endif
        if (merges%2){
          fromindex = R_ExternalPtrAddr(auxindex_);
          fromvalue = R_ExternalPtrAddr(auxff_);
          toindex = R_ExternalPtrAddr(index_);
          tovalue = R_ExternalPtrAddr(ff_);
        }else{
          toindex = R_ExternalPtrAddr(auxindex_);
          tovalue = R_ExternalPtrAddr(auxff_);
          fromindex = R_ExternalPtrAddr(index_);
          fromvalue = R_ExternalPtrAddr(ff_);
        }
        n = N;
        N = 2*n;
        L1 = left;
        L2 = left+n;
        R2=-1;
        while (R2<right){
          R1 = L1 + n - 1;
          R2 = R1 + n;
          if (R2>right){
            if (L2>right){
              // the last pair only has one chunk, no need to merge, but let's not forget to copy from from to to
              R1 = right;
              for (l1 = L1; l1<=R1; l1+=mergesize2){
                r1 = l1 + mergesize2 - 1;
                if (r1>R1)
                  r1 = R1;
                n1 = r1 - l1 + 1;
#if VERBOSE_LEVEL>1
                Rprintf("%d,%d,%d,SKIP,%d,%d,%d,%d,,,,\n", merges,n, N, L1, l1, r1, R1); R_FlushConsole();
#endif
                ff_vmode_get_contiguous( fromvalue, l1, n1, valuebuffer);
                ff_integer_get_contiguous( fromindex, l1-left, n1, indexbuffer);
                ff_vmode_set_contiguous( tovalue, l1, n1, valuebuffer);
                ff_integer_set_contiguous( toindex, l1-left, n1, indexbuffer);
              }
              break;
            }else{
              R2 = right;
            }
          }

          l  = L1;
          l1 = L1;
          l2 = L2;
          n1 = 0;
          n2 = 0;
          i1 = 0;
          i2 = 0;
          while(1){
            // move everything to the left in the in-buffers
            if (i1<n1){
              n1 = n1 - i1;
              memmove(valuebuffer1, valuebuffer1+i1, n1*sizeof(ValueT));
              memmove(indexbuffer1, indexbuffer1+i1, n1*sizeof(IndexT));
              m1 = mergesize - n1;
            }else{
              n1 = 0;
              m1 = mergesize;
            }
            if (i2<n2){
              n2 = n2 - i2;
              memmove(valuebuffer2, valuebuffer2+i2, n2*sizeof(ValueT));
              memmove(indexbuffer2, indexbuffer2+i2, n2*sizeof(IndexT));
              m2 = mergesize - n2;
            }else{
              n2 = 0;
              m2 = mergesize;
            }

            // calculating the read positions
            r1 = l1 + m1 - 1;
            r2 = l2 + m2 - 1;
            if (r1>R1){
              r1 = R1;
              m1 = r1 - l1 + 1;
            }
            if (r2>R2){
              r2 = R2;
              m2 = r2 - l2 + 1;
            }

            // filling the in-buffers
#if VERBOSE_LEVEL>1
            Rprintf("%d,%d,%d,MERGE,%d,%d,%d,%d,%d,%d,%d,%d\n", merges, n, N, L1, l1, r1, R1, L2, l2, r2, R2); R_FlushConsole();
#endif
            if (m1>0){
              ff_vmode_get_contiguous( fromvalue, l1, m1, valuebuffer1+n1);
            }
            if (m2>0){
              ff_vmode_get_contiguous( fromvalue, l2, m2, valuebuffer2+n2);
            }
            if (m1>0)
              ff_integer_get_contiguous( fromindex, l1-left, m1, indexbuffer1+n1);
            if (m2>0)
              ff_integer_get_contiguous( fromindex, l2-left, m2, indexbuffer2+n2);
            l1 += m1;
            l2 += m2;
            n1 += m1;
            n2 += m2;

            // doing the merge
            if (nNA){
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                      indexbuffer[i] = indexbuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                      indexbuffer[i] = indexbuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (naless(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }else{
                  if (naless(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }
              }
            }else{  // not has_na
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                      indexbuffer[i] = indexbuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                      indexbuffer[i] = indexbuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (less(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }else{
                  if (less(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }
              }
            }


            // flushing the out-buffers
            ff_vmode_set_contiguous( tovalue, l, i, valuebuffer);
            ff_integer_set_contiguous( toindex, l-left, i, indexbuffer);

            l += i;
            if (l > R2)
              break;
          }

          L1 += N;
          L2 += N;
        }
        merges -= 1;
      }

      R_Free(indexbuffer1);
      R_Free(indexbuffer2);
      R_Free(indexbuffer);
    }

    R_Free(valuebuffer1);
    R_Free(valuebuffer2);
    R_Free(valuebuffer);
  }

  INTEGER(ret_)[0] = nNA;
  UNPROTECT(1);
  return ret_;
}



SEXP r_ff_double_sortmerge(
  SEXP ffmode_
, SEXP ff_            /* ff data vector */
, SEXP auxff_         /* auxilliary data vector */
, SEXP left_         /* first R position to be ordered */
, SEXP right_        /* last R position to be ordered */
, SEXP method_       /* 0=mergesort 1=shellsort */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
, SEXP mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  void *fromvalue;
  void *tovalue;
  fromvalue = R_ExternalPtrAddr(ff_);
  tovalue = R_ExternalPtrAddr(auxff_);
  Rboolean decreasing = asLogical(decreasing_);
  Rboolean has_na = asLogical(has_na_);
  Rboolean na_last = asLogical(na_last_);
  Rboolean na_reverse = decreasing ? !na_last : na_last;
  IndexT left      = asInteger(left_) - 1;
  IndexT right     = asInteger(right_) - 1;
  IndexT ordersize = asInteger(ordersize_);
  IndexT mergesize = asInteger(mergesize_);
  IndexT method    = asInteger(method_);
  IndexT mergesize2 = 2*mergesize;
  IndexT nNA=0;

  ValueT *valuebuffer;
  ValueT *auxvaluebuffer;

  ValueT *valuebuffer1;
  ValueT *valuebuffer2;

  void (*ff_vmode_get_contiguous)( void *handle, int index, int size, ValueT *ret );
  void (*ff_vmode_set_contiguous)( void *, int, int, ValueT * );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_SINGLE
  case 10: ff_vmode_get_contiguous =  ff_single_get_contiguous;
           ff_vmode_set_contiguous =  ff_single_set_contiguous; break;
#endif
#if VMODE_COMPILE_DOUBLE
  case 11: ff_vmode_get_contiguous =  ff_double_get_contiguous;
           ff_vmode_set_contiguous =  ff_double_set_contiguous; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }

  // we use R_Calloc because then we can free big RAM after the ordering pass and have more for the file system cache
  valuebuffer = (ValueT *) R_Calloc(ordersize, ValueT);
  if (method!=1)
    auxvaluebuffer = (ValueT *) R_Calloc(ordersize, ValueT);
  else
    auxvaluebuffer = 0; // keep compiler quiet

  IndexT l,r,i,n,N;
  IndexT l1,l2,r1,r2,n1,n2,m1,m2;
  IndexT i1,i2;
  IndexT L1,L2,R1,R2;
  IndexT T=right-left+1;
  IndexT merges = 0;

  N = ordersize;
  while (N<T){
    merges+=1;
    N=N+N;
  }

#if VERBOSE_LEVEL>0
  Rprintf("sort pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("sortmerge,from,to,type,L1,l1,r1,R1,L2,l2,r2,R2\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d,,,,,,,,,\n", l, r); R_FlushConsole();
#endif

    // read the value chunk
    ff_vmode_get_contiguous( fromvalue, l, n, valuebuffer);

    if (method!=1)
      nNA += ram_double_mergesort(valuebuffer, auxvaluebuffer, 0, n-1, has_na, na_last, decreasing);
    else
      nNA += ram_double_shellsort(valuebuffer, 0, n-1, has_na, na_last, decreasing);

    if (merges%2){
      ff_vmode_set_contiguous( tovalue, l, n, valuebuffer);
    }else{
      ff_vmode_set_contiguous( fromvalue, l, n, valuebuffer);
    }

  }

  // this was large RAM, let's free here, then we have it for the filesystem cache
  R_Free(valuebuffer);
  if (method!=1)
    R_Free(auxvaluebuffer);

  N = ordersize;
  if (n<T){

  valuebuffer1 = (ValueT *) R_Calloc(mergesize, ValueT);
  valuebuffer2 = (ValueT *) R_Calloc(mergesize, ValueT);
  valuebuffer = (ValueT *) R_Calloc(mergesize2, ValueT);

    while(N<T){
#if VERBOSE_LEVEL>0
      Rprintf("merge pass #%d\n", merges); R_FlushConsole();
#endif
      if (merges%2){
        fromvalue = R_ExternalPtrAddr(auxff_);
        tovalue = R_ExternalPtrAddr(ff_);
      }else{
        tovalue = R_ExternalPtrAddr(auxff_);
        fromvalue = R_ExternalPtrAddr(ff_);
      }
      n = N;
      N = 2*n;
      L1 = left;
      L2 = left+n;
      R2=-1;
      while (R2<right){
        R1 = L1 + n - 1;
        R2 = R1 + n;
        if (R2>right){
          if (L2>right){
            // the last pair only has one chunk, no need to merge, but let's not forget to copy from from to to
            R1 = right;
            for (l1 = L1; l1<=R1; l1+=mergesize2){
              r1 = l1 + mergesize2 - 1;
              if (r1>R1)
                r1 = R1;
              n1 = r1 - l1 + 1;
#if VERBOSE_LEVEL>1
              Rprintf("%d,%d,%d,SKIP,%d,%d,%d,%d,,,,\n", merges,n, N, L1, l1, r1, R1); R_FlushConsole();
#endif
              ff_vmode_get_contiguous( fromvalue, l1, n1, valuebuffer);
              ff_vmode_set_contiguous( tovalue, l1, n1, valuebuffer);
            }
            break;
          }else{
            R2 = right;
          }
        }

        l  = L1;
        l1 = L1;
        l2 = L2;
        n1 = 0;
        n2 = 0;
        i1 = 0;
        i2 = 0;
        while(1){
          // move everything to the left in the in-buffers
          if (i1<n1){
            n1 = n1 - i1;
            memmove(valuebuffer1, valuebuffer1+i1, n1*sizeof(ValueT));
            m1 = mergesize - n1;
          }else{
            n1 = 0;
            m1 = mergesize;
          }
          if (i2<n2){
            n2 = n2 - i2;
            memmove(valuebuffer2, valuebuffer2+i2, n2*sizeof(ValueT));
            m2 = mergesize - n2;
          }else{
            n2 = 0;
            m2 = mergesize;
          }

          // calculating the read positions
          r1 = l1 + m1 - 1;
          r2 = l2 + m2 - 1;
          if (r1>R1){
            r1 = R1;
            m1 = r1 - l1 + 1;
          }
          if (r2>R2){
            r2 = R2;
            m2 = r2 - l2 + 1;
          }

          // filling the in-buffers
#if VERBOSE_LEVEL>1
          Rprintf("%d,%d,%d,MERGE,%d,%d,%d,%d,%d,%d,%d,%d\n", merges, n, N, L1, l1, r1, R1, L2, l2, r2, R2); R_FlushConsole();
#endif
          if (m1>0){
            ff_vmode_get_contiguous( fromvalue, l1, m1, valuebuffer1+n1);
          }
          if (m2>0){
            ff_vmode_get_contiguous( fromvalue, l2, m2, valuebuffer2+n2);
          }
          l1 += m1;
          l2 += m2;
          n1 += m1;
          n2 += m2;

          // doing the merge
          for(i=0, i1=0, i2=0; ; i++){
            if (i1==n1){
              if (l1>R1){
                // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                for(;i2<n2;i2++,i++){
                  valuebuffer[i] = valuebuffer2[i2];
                }
              }
              break;
            }
            if (i2==n2){
              if (l2>R2){
                // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                for(;i1<n1;i1++,i++){
                  valuebuffer[i] = valuebuffer1[i1];
                }
              }
              break;
            }

            if (nNA){
              if (decreasing){
                if (naless(valuebuffer1[i1], valuebuffer2[i2])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }else{
                if (naless(valuebuffer2[i2], valuebuffer1[i1])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }
            }else{
              if (decreasing){
                if (less(valuebuffer1[i1], valuebuffer2[i2])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }else{
                if (less(valuebuffer2[i2], valuebuffer1[i1])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }
            }

          }

          // flushing the out-buffers
          ff_vmode_set_contiguous( tovalue, l, i, valuebuffer);

          l += i;
          if (l > R2)
            break;
        }

        L1 += N;
        L2 += N;
      }
      merges -= 1;
    }


    R_Free(valuebuffer1);
    R_Free(valuebuffer2);
    R_Free(valuebuffer);
  }

  INTEGER(ret_)[0] = nNA;
  UNPROTECT(1);
  return ret_;
}




SEXP r_ff_integer_ordermerge(
  SEXP ffmode_
, SEXP ff_           /* ff data vector */
, SEXP index_        /* NULL or ff index vector, xx TODO we can speed up by implementing true internal sorting, internally we currently do always ordering */
, SEXP auxff_        /* auxilliary data vector */
, SEXP auxindex_     /* NULL or auxilliary index vector (needed if index_ given) */
, SEXP left_         /* first R position to be ordered */
, SEXP right_        /* last R position to be ordered */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=radixorder 3=keyorder (only 0 or 1 for doubles) */
, SEXP keyrange_     /* NULL, or - for method==2 - vector with 2 elements firstkey+lastkey */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
, SEXP mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
, SEXP orderindex_   /* logical scalar: shall we reorder index_? (otherwise we simpy write it) */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  void *fromvalue;
  void *fromindex;
  void *tovalue;
  void *toindex;
  fromvalue = R_ExternalPtrAddr(ff_);
  fromindex = R_ExternalPtrAddr(index_);
  tovalue = R_ExternalPtrAddr(auxff_);
  toindex = R_ExternalPtrAddr(auxindex_);
  Rboolean orderindex = asLogical(orderindex_);
  Rboolean decreasing = asLogical(decreasing_);
  Rboolean has_na = asLogical(has_na_);
  Rboolean na_last = asLogical(na_last_);
  Rboolean na_reverse = decreasing ? !na_last : na_last;
  IndexT left      = asInteger(left_) - 1;
  IndexT right     = asInteger(right_) - 1;
  IndexT ordersize = asInteger(ordersize_);
  IndexT mergesize = asInteger(mergesize_);
  IndexT method    = asInteger(method_);
  IndexT keyoffset=0, keylength=0;  /* keep compiler quiet */

  IndexT mergesize2 = 2*mergesize;
  IndexT nNA = 0;

  IndexT *valuebuffer;
  IndexT *indexbuffer;
  IndexT *auxindexbuffer;

  IndexT *count;

  IndexT *valuebuffer1;
  IndexT *indexbuffer1;
  IndexT *valuebuffer2;
  IndexT *indexbuffer2;

  void (*ff_vmode_get_contiguous)( void *handle, int index, int size, IndexT *ret );
  void (*ff_vmode_set_contiguous)( void *, int, int, IndexT * );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ff_vmode_get_contiguous = ff_boolean_get_contiguous;
          ff_vmode_set_contiguous = ff_boolean_set_contiguous; break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ff_vmode_get_contiguous = ff_logical_get_contiguous;
          ff_vmode_set_contiguous = ff_logical_set_contiguous; break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ff_vmode_get_contiguous = ff_quad_get_contiguous;
          ff_vmode_set_contiguous = ff_quad_set_contiguous; break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ff_vmode_get_contiguous = ff_nibble_get_contiguous;
          ff_vmode_set_contiguous = ff_nibble_set_contiguous; break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ff_vmode_get_contiguous = ff_byte_get_contiguous;
          ff_vmode_set_contiguous = ff_byte_set_contiguous; break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ff_vmode_get_contiguous = ff_ubyte_get_contiguous;
          ff_vmode_set_contiguous = ff_ubyte_set_contiguous; break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ff_vmode_get_contiguous = ff_short_get_contiguous;
          ff_vmode_set_contiguous = ff_short_set_contiguous; break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ff_vmode_get_contiguous = ff_ushort_get_contiguous;
          ff_vmode_set_contiguous = ff_ushort_set_contiguous; break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ff_vmode_get_contiguous = ff_integer_get_contiguous;
          ff_vmode_set_contiguous = ff_integer_set_contiguous; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }


  //IndexT (*ff_vmode_get)( void *, int );
  void (*ff_vmode_set)( void *, int, IndexT );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: //ff_vmode_get = ff_boolean_get;
          ff_vmode_set = ff_boolean_set; break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: //ff_vmode_get = ff_logical_get;
          ff_vmode_set = ff_logical_set; break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: //ff_vmode_get = ff_quad_get;
          ff_vmode_set = ff_quad_set; break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: //ff_vmode_get = ff_nibble_get;
          ff_vmode_set = ff_nibble_set; break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: //ff_vmode_get = ff_byte_get;
          ff_vmode_set = ff_byte_set; break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: //ff_vmode_get = ff_ubyte_get;
          ff_vmode_set = ff_ubyte_set; break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: //ff_vmode_get = ff_short_get;
          ff_vmode_set = ff_short_set; break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: //ff_vmode_get = ff_ushort_get;
          ff_vmode_set = ff_ushort_set; break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: //ff_vmode_get = ff_integer_get;
          ff_vmode_set = ff_integer_set; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }


  if (method==3){
    keyoffset = INTEGER(keyrange_)[0] - 1; // note that minvalue 1 is mapped to offset 0
    keylength = INTEGER(keyrange_)[1] - INTEGER(keyrange_)[0] + 1;
  }

  // we use R_Calloc because then we can free big RAM after the ordering pass and have more for the file system cache
  valuebuffer = (IndexT *) R_Calloc(ordersize, IndexT);
  indexbuffer = (IndexT *) R_Calloc(ordersize, IndexT);
  if (method!=1 || orderindex){
    auxindexbuffer = (IndexT *) R_Calloc(ordersize, IndexT);
    if (method>1){
      if (method==2){
        count = (IndexT *) R_Calloc(NWORD+1, IndexT);
      }else
        count = (IndexT *) R_Calloc(keylength+2, IndexT);
    }else{ // keep compiler quiet
      count = 0;
    }
  }else{  // keep compiler quiet
    auxindexbuffer = 0;
    count = 0;
  }


  IndexT l,r,i,n,N,offset;
  IndexT l1,l2,r1,r2,n1,n2,m1,m2;
  IndexT i1,i2;
  IndexT L1,L2,R1,R2;
  IndexT T=right-left+1;
  IndexT merges = 0;

  N = ordersize;
  while (N<T){
    merges+=1;
    N=N+N;
  }

#if VERBOSE_LEVEL>0
  Rprintf("order pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("ordermerge,from,to,type,L1,l1,r1,R1,L2,l2,r2,R2\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d,,,,,,,,,\n", l, r); R_FlushConsole();
#endif

    // read the value chunk
    ff_vmode_get_contiguous( fromvalue, l, n, valuebuffer);

    // initialize the local index 0:(n-1)
    for (i = 0; i<n; i++){
      indexbuffer[i]=i;
    }


    // order the chunk
    if (method!=1 || orderindex){
      switch (method){
        case 3:{
          nNA += ram_integer_keyorder(valuebuffer, indexbuffer, auxindexbuffer, count, 0, keyoffset, keylength, 0, n-1, has_na, na_last, decreasing);
          break; }
        case 2: {
          nNA += ram_integer_radixorder(valuebuffer, indexbuffer, auxindexbuffer, count, 0, 0, n-1, has_na, na_last, decreasing);
          break; }
        default:
          nNA += ram_integer_mergeorder(valuebuffer, indexbuffer, auxindexbuffer, 0, 0, n-1, has_na, na_last, decreasing);
      }

    }else{
      nNA += ram_integer_shellorder(valuebuffer, indexbuffer, 0, 0, n-1, has_na, na_last, decreasing, 1); // last 1 = we stabilize
    }

    // write the value chunk
    if (merges%2)
      for (i = 0; i<n; i++){
        ff_vmode_set( tovalue, l+i, valuebuffer[indexbuffer[i]]);
      }
    else
      for (i = 0; i<n; i++){
        ff_vmode_set( fromvalue, l+i, valuebuffer[indexbuffer[i]]);
      }

    if (index_!=R_NilValue){
      if (orderindex){
        ff_integer_get_contiguous( fromindex, l-left, n, auxindexbuffer);
        for (i = 0; i<n; i++){
          indexbuffer[i] = auxindexbuffer[indexbuffer[i]];
        }
      }else{
        offset = l + 1;
        for (i = 0; i<n; i++){
          indexbuffer[i] = offset + indexbuffer[i];  // C2R positions
        }
      }
      if (merges%2){
        ff_integer_set_contiguous( toindex, l-left, n, indexbuffer);
      }else{
        ff_integer_set_contiguous( fromindex, l-left, n, indexbuffer);
      }
    }

  }


  // this was large RAM, let's free here, then we have it for the filesystem cache
  R_Free(valuebuffer);
  R_Free(indexbuffer);
  if (method!=1 || orderindex){
    R_Free(auxindexbuffer);
    if (method>1){
      R_Free(count);
    }
  }

  N = ordersize;
  if (n<T){

    valuebuffer1 = (IndexT *) R_Calloc(mergesize, IndexT);
    valuebuffer2 = (IndexT *) R_Calloc(mergesize, IndexT);
    valuebuffer = (IndexT *) R_Calloc(mergesize2, IndexT);

    if (index_==R_NilValue){

      while(N<T){
#if VERBOSE_LEVEL>0
        Rprintf("merge pass #%d\n", merges); R_FlushConsole();
#endif
        if (merges%2){
          fromvalue = R_ExternalPtrAddr(auxff_);
          tovalue = R_ExternalPtrAddr(ff_);
        }else{
          tovalue = R_ExternalPtrAddr(auxff_);
          fromvalue = R_ExternalPtrAddr(ff_);
        }
        n = N;
        N = 2*n;
        L1 = left;
        L2 = left+n;
        R2=-1;
        while (R2<right){
          R1 = L1 + n - 1;
          R2 = R1 + n;
          if (R2>right){
            if (L2>right){
              // the last pair only has one chunk, no need to merge, but let's not forget to copy from from to to
              R1 = right;
              for (l1 = L1; l1<=R1; l1+=mergesize2){
                r1 = l1 + mergesize2 - 1;
                if (r1>R1)
                  r1 = R1;
                n1 = r1 - l1 + 1;
#if VERBOSE_LEVEL>1
                Rprintf("%d,%d,%d,SKIP,%d,%d,%d,%d,,,,\n", merges,n, N, L1, l1, r1, R1); R_FlushConsole();
#endif
                ff_vmode_get_contiguous( fromvalue, l1, n1, valuebuffer);
                ff_vmode_set_contiguous( tovalue, l1, n1, valuebuffer);
              }
              break;
            }else{
              R2 = right;
            }
          }

          l  = L1;
          l1 = L1;
          l2 = L2;
          n1 = 0;
          n2 = 0;
          i1 = 0;
          i2 = 0;
          while(1){
            // move everything to the left in the in-buffers
            if (i1<n1){
              n1 = n1 - i1;
              memmove(valuebuffer1, valuebuffer1+i1, n1*sizeof(IndexT));
              m1 = mergesize - n1;
            }else{
              n1 = 0;
              m1 = mergesize;
            }
            if (i2<n2){
              n2 = n2 - i2;
              memmove(valuebuffer2, valuebuffer2+i2, n2*sizeof(IndexT));
              m2 = mergesize - n2;
            }else{
              n2 = 0;
              m2 = mergesize;
            }

            // calculating the read positions
            r1 = l1 + m1 - 1;
            r2 = l2 + m2 - 1;
            if (r1>R1){
              r1 = R1;
              m1 = r1 - l1 + 1;
            }
            if (r2>R2){
              r2 = R2;
              m2 = r2 - l2 + 1;
            }

            // filling the in-buffers
#if VERBOSE_LEVEL>1
            Rprintf("%d,%d,%d,MERGE,%d,%d,%d,%d,%d,%d,%d,%d\n", merges, n, N, L1, l1, r1, R1, L2, l2, r2, R2); R_FlushConsole();
#endif
            if (m1>0){
              ff_vmode_get_contiguous( fromvalue, l1, m1, valuebuffer1+n1);
            }
            if (m2>0){
              ff_vmode_get_contiguous( fromvalue, l2, m2, valuebuffer2+n2);
            }
            l1 += m1;
            l2 += m2;
            n1 += m1;
            n2 += m2;

            // doing the merge
            if (nNA){
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (intnaless(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }else{
                  if (intnaless(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }
              }
            }else{ // not has_na
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (less(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }else{
                  if (less(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    i1++;
                  }
                }
              }
            }


            // flushing the out-buffers
            ff_vmode_set_contiguous( tovalue, l, i, valuebuffer);

            l += i;
            if (l > R2)
              break;
          }

          L1 += N;
          L2 += N;
        }
        merges -= 1;
      }

    }else{

      indexbuffer1 = (IndexT *) R_Calloc(mergesize, IndexT);
      indexbuffer2 = (IndexT *) R_Calloc(mergesize, IndexT);
      indexbuffer = (IndexT *) R_Calloc(mergesize2, IndexT);

      while(N<T){
#if VERBOSE_LEVEL>0
        Rprintf("merge pass #%d\n", merges); R_FlushConsole();
#endif
        if (merges%2){
          fromindex = R_ExternalPtrAddr(auxindex_);
          fromvalue = R_ExternalPtrAddr(auxff_);
          toindex = R_ExternalPtrAddr(index_);
          tovalue = R_ExternalPtrAddr(ff_);
        }else{
          toindex = R_ExternalPtrAddr(auxindex_);
          tovalue = R_ExternalPtrAddr(auxff_);
          fromindex = R_ExternalPtrAddr(index_);
          fromvalue = R_ExternalPtrAddr(ff_);
        }
        n = N;
        N = 2*n;
        L1 = left;
        L2 = left+n;
        R2=-1;
        while (R2<right){
          R1 = L1 + n - 1;
          R2 = R1 + n;
          if (R2>right){
            if (L2>right){
              // the last pair only has one chunk, no need to merge, but let's not forget to copy from from to to
              R1 = right;
              for (l1 = L1; l1<=R1; l1+=mergesize2){
                r1 = l1 + mergesize2 - 1;
                if (r1>R1)
                  r1 = R1;
                n1 = r1 - l1 + 1;
#if VERBOSE_LEVEL>1
                Rprintf("%d,%d,%d,SKIP,%d,%d,%d,%d,,,,\n", merges,n, N, L1, l1, r1, R1); R_FlushConsole();
#endif
                ff_vmode_get_contiguous( fromvalue, l1, n1, valuebuffer);
                ff_integer_get_contiguous( fromindex, l1-left, n1, indexbuffer);
                ff_vmode_set_contiguous( tovalue, l1, n1, valuebuffer);
                ff_integer_set_contiguous( toindex, l1-left, n1, indexbuffer);
              }
              break;
            }else{
              R2 = right;
            }
          }

          l  = L1;
          l1 = L1;
          l2 = L2;
          n1 = 0;
          n2 = 0;
          i1 = 0;
          i2 = 0;
          while(1){
            // move everything to the left in the in-buffers
            if (i1<n1){
              n1 = n1 - i1;
              memmove(valuebuffer1, valuebuffer1+i1, n1*sizeof(IndexT));
              memmove(indexbuffer1, indexbuffer1+i1, n1*sizeof(IndexT));
              m1 = mergesize - n1;
            }else{
              n1 = 0;
              m1 = mergesize;
            }
            if (i2<n2){
              n2 = n2 - i2;
              memmove(valuebuffer2, valuebuffer2+i2, n2*sizeof(IndexT));
              memmove(indexbuffer2, indexbuffer2+i2, n2*sizeof(IndexT));
              m2 = mergesize - n2;
            }else{
              n2 = 0;
              m2 = mergesize;
            }

            // calculating the read positions
            r1 = l1 + m1 - 1;
            r2 = l2 + m2 - 1;
            if (r1>R1){
              r1 = R1;
              m1 = r1 - l1 + 1;
            }
            if (r2>R2){
              r2 = R2;
              m2 = r2 - l2 + 1;
            }

            // filling the in-buffers
#if VERBOSE_LEVEL>1
            Rprintf("%d,%d,%d,MERGE,%d,%d,%d,%d,%d,%d,%d,%d\n", merges, n, N, L1, l1, r1, R1, L2, l2, r2, R2); R_FlushConsole();
#endif
            if (m1>0){
              ff_vmode_get_contiguous( fromvalue, l1, m1, valuebuffer1+n1);
            }
            if (m2>0){
              ff_vmode_get_contiguous( fromvalue, l2, m2, valuebuffer2+n2);
            }
            if (m1>0)
              ff_integer_get_contiguous( fromindex, l1-left, m1, indexbuffer1+n1);
            if (m2>0)
              ff_integer_get_contiguous( fromindex, l2-left, m2, indexbuffer2+n2);
            l1 += m1;
            l2 += m2;
            n1 += m1;
            n2 += m2;

            // doing the merge
            if (nNA){
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                      indexbuffer[i] = indexbuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                      indexbuffer[i] = indexbuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (intnaless(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }else{
                  if (intnaless(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }
              }
            }else{  // not has_na
              for(i=0, i1=0, i2=0; ; i++){
                if (i1==n1){
                  if (l1>R1){
                    // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                    for(;i2<n2;i2++,i++){
                      valuebuffer[i] = valuebuffer2[i2];
                      indexbuffer[i] = indexbuffer2[i2];
                    }
                  }
                  break;
                }
                if (i2==n2){
                  if (l2>R2){
                    // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                    for(;i1<n1;i1++,i++){
                      valuebuffer[i] = valuebuffer1[i1];
                      indexbuffer[i] = indexbuffer1[i1];
                    }
                  }
                  break;
                }
                if (decreasing){
                  if (less(valuebuffer1[i1], valuebuffer2[i2])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }else{
                  if (less(valuebuffer2[i2], valuebuffer1[i1])){
                    valuebuffer[i] = valuebuffer2[i2];
                    indexbuffer[i] = indexbuffer2[i2];
                    i2++;
                  }else{
                    valuebuffer[i] = valuebuffer1[i1];
                    indexbuffer[i] = indexbuffer1[i1];
                    i1++;
                  }
                }
              }
            }


            // flushing the out-buffers
            ff_vmode_set_contiguous( tovalue, l, i, valuebuffer);
            ff_integer_set_contiguous( toindex, l-left, i, indexbuffer);

            l += i;
            if (l > R2)
              break;
          }

          L1 += N;
          L2 += N;
        }
        merges -= 1;
      }

      R_Free(indexbuffer1);
      R_Free(indexbuffer2);
      R_Free(indexbuffer);
    }

    R_Free(valuebuffer1);
    R_Free(valuebuffer2);
    R_Free(valuebuffer);
  }

  INTEGER(ret_)[0] = nNA;
  UNPROTECT(1);
  return ret_;
}



SEXP r_ff_integer_sortmerge(
  SEXP ffmode_
, SEXP ff_            /* ff data vector */
, SEXP auxff_         /* auxilliary data vector */
, SEXP left_         /* first R position to be ordered */
, SEXP right_        /* last R position to be ordered */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=radixorder 3=keyorder (only 0 or 1 for doubles) */
, SEXP keyrange_       /* NULL, or - for method==2 - vector with 2 elements firstkey+lastkey */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
, SEXP mergesize_    /* int no of elements to be merged in RAM (xx let's try if one block is sufficient) */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  void *fromvalue;
  void *tovalue;
  fromvalue = R_ExternalPtrAddr(ff_);
  tovalue = R_ExternalPtrAddr(auxff_);
  Rboolean decreasing = asLogical(decreasing_);
  Rboolean has_na = asLogical(has_na_);
  Rboolean na_last = asLogical(na_last_);
  Rboolean na_reverse = decreasing ? !na_last : na_last;
  IndexT left      = asInteger(left_) - 1;
  IndexT right     = asInteger(right_) - 1;
  IndexT ordersize = asInteger(ordersize_);
  IndexT mergesize = asInteger(mergesize_);
  IndexT method    = asInteger(method_);
  IndexT keyoffset=0, keylength=0; /* keep compiler quiet */
  IndexT mergesize2 = 2*mergesize;
  IndexT nNA=0;

  IndexT *valuebuffer;
  IndexT *auxvaluebuffer;

  IndexT *count;

  IndexT *valuebuffer1;
  IndexT *valuebuffer2;

  void (*ff_vmode_get_contiguous)( void *handle, int index, int size, IndexT *ret );
  void (*ff_vmode_set_contiguous)( void *, int, int, IndexT * );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ff_vmode_get_contiguous = ff_boolean_get_contiguous;
          ff_vmode_set_contiguous = ff_boolean_set_contiguous; break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ff_vmode_get_contiguous = ff_logical_get_contiguous;
          ff_vmode_set_contiguous = ff_logical_set_contiguous; break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ff_vmode_get_contiguous = ff_quad_get_contiguous;
          ff_vmode_set_contiguous = ff_quad_set_contiguous; break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ff_vmode_get_contiguous = ff_nibble_get_contiguous;
          ff_vmode_set_contiguous = ff_nibble_set_contiguous; break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ff_vmode_get_contiguous = ff_byte_get_contiguous;
          ff_vmode_set_contiguous = ff_byte_set_contiguous; break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ff_vmode_get_contiguous = ff_ubyte_get_contiguous;
          ff_vmode_set_contiguous = ff_ubyte_set_contiguous; break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ff_vmode_get_contiguous = ff_short_get_contiguous;
          ff_vmode_set_contiguous = ff_short_set_contiguous; break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ff_vmode_get_contiguous = ff_ushort_get_contiguous;
          ff_vmode_set_contiguous = ff_ushort_set_contiguous; break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ff_vmode_get_contiguous = ff_integer_get_contiguous;
          ff_vmode_set_contiguous = ff_integer_set_contiguous; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }


  if (method==3){
    keyoffset = INTEGER(keyrange_)[0] - 1; // note that minvalue 1 is mapped to offset 0
    keylength = INTEGER(keyrange_)[1] - INTEGER(keyrange_)[0] + 1;
  }

  // we use R_Calloc because then we can free big RAM after the ordering pass and have more for the file system cache
  valuebuffer = (IndexT *) R_Calloc(ordersize, IndexT);
  if (method!=1){
    auxvaluebuffer = (IndexT *) R_Calloc(ordersize, IndexT);
    if (method>1){
      if (method==2){
        count = (IndexT *) R_Calloc(NWORD+1, IndexT);
      }else
        count = (IndexT *) R_Calloc(keylength+2, IndexT);
    }else{ // keep compiler quiet
      count = 0;
    }
  }else{ // keep compiler quiet
    auxvaluebuffer = 0;
    count = 0;
  }



  IndexT l,r,i,n,N;
  IndexT l1,l2,r1,r2,n1,n2,m1,m2;
  IndexT i1,i2;
  IndexT L1,L2,R1,R2;
  IndexT T=right-left+1;
  IndexT merges = 0;

  N = ordersize;
  while (N<T){
    merges+=1;
    N=N+N;
  }

#if VERBOSE_LEVEL>0
  Rprintf("sort pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("sortmerge,from,to,type,L1,l1,r1,R1,L2,l2,r2,R2\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d,,,,,,,,,\n", l, r); R_FlushConsole();
#endif

    // read the value chunk
    ff_vmode_get_contiguous( fromvalue, l, n, valuebuffer);

    if (method!=1){
      if(method==3)
        nNA += ram_integer_keysort(valuebuffer, count, keyoffset, keylength, 0, n-1, has_na, na_last, decreasing);
      else if(method==2)
        nNA += ram_integer_radixsort(valuebuffer, auxvaluebuffer, count, 0, n-1, has_na, na_last, decreasing);
      else
        nNA += ram_integer_mergesort(valuebuffer, auxvaluebuffer, 0, n-1, has_na, na_last, decreasing);
    }else{
      nNA += ram_integer_shellsort(valuebuffer, 0, n-1, has_na, na_last, decreasing);
    }

    if (merges%2){
      ff_vmode_set_contiguous( tovalue, l, n, valuebuffer);
    }else{
      ff_vmode_set_contiguous( fromvalue, l, n, valuebuffer);
    }

  }

  // this was large RAM, let's free here, then we have it for the filesystem cache
  R_Free(valuebuffer);
  if (method!=1){
    R_Free(auxvaluebuffer);
    if (method>1){
      R_Free(count);
    }
  }

  N = ordersize;
  if (n<T){

  valuebuffer1 = (IndexT *) R_Calloc(mergesize, IndexT);
  valuebuffer2 = (IndexT *) R_Calloc(mergesize, IndexT);
  valuebuffer = (IndexT *) R_Calloc(mergesize2, IndexT);

    while(N<T){
#if VERBOSE_LEVEL>0
      Rprintf("merge pass #%d\n", merges); R_FlushConsole();
#endif
      if (merges%2){
        fromvalue = R_ExternalPtrAddr(auxff_);
        tovalue = R_ExternalPtrAddr(ff_);
      }else{
        tovalue = R_ExternalPtrAddr(auxff_);
        fromvalue = R_ExternalPtrAddr(ff_);
      }
      n = N;
      N = 2*n;
      L1 = left;
      L2 = left+n;
      R2=-1;
      while (R2<right){
        R1 = L1 + n - 1;
        R2 = R1 + n;
        if (R2>right){
          if (L2>right){
            // the last pair only has one chunk, no need to merge, but let's not forget to copy from from to to
            R1 = right;
            for (l1 = L1; l1<=R1; l1+=mergesize2){
              r1 = l1 + mergesize2 - 1;
              if (r1>R1)
                r1 = R1;
              n1 = r1 - l1 + 1;
#if VERBOSE_LEVEL>1
              Rprintf("%d,%d,%d,SKIP,%d,%d,%d,%d,,,,\n", merges,n, N, L1, l1, r1, R1); R_FlushConsole();
#endif
              ff_vmode_get_contiguous( fromvalue, l1, n1, valuebuffer);
              ff_vmode_set_contiguous( tovalue, l1, n1, valuebuffer);
            }
            break;
          }else{
            R2 = right;
          }
        }

        l  = L1;
        l1 = L1;
        l2 = L2;
        n1 = 0;
        n2 = 0;
        i1 = 0;
        i2 = 0;
        while(1){
          // move everything to the left in the in-buffers
          if (i1<n1){
            n1 = n1 - i1;
            memmove(valuebuffer1, valuebuffer1+i1, n1*sizeof(IndexT));
            m1 = mergesize - n1;
          }else{
            n1 = 0;
            m1 = mergesize;
          }
          if (i2<n2){
            n2 = n2 - i2;
            memmove(valuebuffer2, valuebuffer2+i2, n2*sizeof(IndexT));
            m2 = mergesize - n2;
          }else{
            n2 = 0;
            m2 = mergesize;
          }

          // calculating the read positions
          r1 = l1 + m1 - 1;
          r2 = l2 + m2 - 1;
          if (r1>R1){
            r1 = R1;
            m1 = r1 - l1 + 1;
          }
          if (r2>R2){
            r2 = R2;
            m2 = r2 - l2 + 1;
          }

          // filling the in-buffers
#if VERBOSE_LEVEL>1
          Rprintf("%d,%d,%d,MERGE,%d,%d,%d,%d,%d,%d,%d,%d\n", merges, n, N, L1, l1, r1, R1, L2, l2, r2, R2); R_FlushConsole();
#endif
          if (m1>0){
            ff_vmode_get_contiguous( fromvalue, l1, m1, valuebuffer1+n1);
          }
          if (m2>0){
            ff_vmode_get_contiguous( fromvalue, l2, m2, valuebuffer2+n2);
          }
          l1 += m1;
          l2 += m2;
          n1 += m1;
          n2 += m2;

          // doing the merge
          for(i=0, i1=0, i2=0; ; i++){
            if (i1==n1){
              if (l1>R1){
                // chunk 1 is exhausted, we can flush in-buffer2 without comparison
                for(;i2<n2;i2++,i++){
                  valuebuffer[i] = valuebuffer2[i2];
                }
              }
              break;
            }
            if (i2==n2){
              if (l2>R2){
                // chunk 2 is exhausted, we can flush in-buffer1 without comparison
                for(;i1<n1;i1++,i++){
                  valuebuffer[i] = valuebuffer1[i1];
                }
              }
              break;
            }

            if (nNA){
              if (decreasing){
                if (intnaless(valuebuffer1[i1], valuebuffer2[i2])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }else{
                if (intnaless(valuebuffer2[i2], valuebuffer1[i1])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }
            }else{
              if (decreasing){
                if (less(valuebuffer1[i1], valuebuffer2[i2])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }else{
                if (less(valuebuffer2[i2], valuebuffer1[i1])){
                  valuebuffer[i] = valuebuffer2[i2];
                  i2++;
                }else{
                  valuebuffer[i] = valuebuffer1[i1];
                  i1++;
                }
              }
            }

          }

          // flushing the out-buffers
          ff_vmode_set_contiguous( tovalue, l, i, valuebuffer);

          l += i;
          if (l > R2)
            break;
        }

        L1 += N;
        L2 += N;
      }
      merges -= 1;
    }


    R_Free(valuebuffer1);
    R_Free(valuebuffer2);
    R_Free(valuebuffer);
  }

  INTEGER(ret_)[0] = nNA;
  UNPROTECT(1);
  return ret_;
}



SEXP r_ff_integer_keysort(
  SEXP ffmode_
, SEXP ff_            /* ff data vector */
, SEXP left_         /* first R position to be ordered */
, SEXP right_        /* last R position to be ordered */
, SEXP keyrange_       /* NULL, or - for method==2 - vector with 2 elements firstkey,lastkey */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (as large as possible) */
, SEXP has_na_       /* logical scalar */
, SEXP na_last_      /* logical scalar */
, SEXP decreasing_   /* logical scalar */
)
{
  SEXP ret_;
  PROTECT( ret_ = allocVector(INTSXP, 1) );

  void *fromvalue;
  fromvalue = R_ExternalPtrAddr(ff_);
  Rboolean decreasing = asLogical(decreasing_);
  Rboolean has_na = asLogical(has_na_);
  Rboolean na_last = asLogical(na_last_);
  IndexT left      = asInteger(left_) - 1;
  IndexT right     = asInteger(right_) - 1;
  IndexT ordersize = asInteger(ordersize_);
  IndexT keyoffset = INTEGER(keyrange_)[0] - 1; // note that minvalue 1 is mapped to offset 0
  IndexT keylength = INTEGER(keyrange_)[1] - INTEGER(keyrange_)[0] + 1;
  IndexT nNA;

  IndexT *valuebuffer;

  IndexT *count;
  IndexT *allcount;

  // we use R_Calloc because then we can free big RAM after the ordering pass and have more for the file system cache
  valuebuffer = (IndexT *) R_Calloc(ordersize, IndexT);

  count = (IndexT *) R_Calloc(keylength+2, IndexT);
  allcount = (IndexT *) R_Calloc(keylength+2, IndexT);

  IndexT l,r,i,k,v,n;

  void (*ff_vmode_get_contiguous)( void *handle, int index, int size, IndexT *ret );
  void (*ff_vmode_set_contiguous)( void *, int, int, IndexT * );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ff_vmode_get_contiguous = ff_boolean_get_contiguous;
          ff_vmode_set_contiguous = ff_boolean_set_contiguous; break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ff_vmode_get_contiguous = ff_logical_get_contiguous;
          ff_vmode_set_contiguous = ff_logical_set_contiguous; break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ff_vmode_get_contiguous = ff_quad_get_contiguous;
          ff_vmode_set_contiguous = ff_quad_set_contiguous; break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ff_vmode_get_contiguous = ff_nibble_get_contiguous;
          ff_vmode_set_contiguous = ff_nibble_set_contiguous; break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ff_vmode_get_contiguous = ff_byte_get_contiguous;
          ff_vmode_set_contiguous = ff_byte_set_contiguous; break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ff_vmode_get_contiguous = ff_ubyte_get_contiguous;
          ff_vmode_set_contiguous = ff_ubyte_set_contiguous; break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ff_vmode_get_contiguous = ff_short_get_contiguous;
          ff_vmode_set_contiguous = ff_short_set_contiguous; break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ff_vmode_get_contiguous = ff_ushort_get_contiguous;
          ff_vmode_set_contiguous = ff_ushort_set_contiguous; break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ff_vmode_get_contiguous = ff_integer_get_contiguous;
          ff_vmode_set_contiguous = ff_integer_set_contiguous; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }


#if VERBOSE_LEVEL>0
  Rprintf("sort pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("ffkeysort,from,to,type,L1,l1,r1,R1,L2,l2,r2,R2\n"); R_FlushConsole();
#endif
#endif

  for (i=0; i<=keylength;i++)
    allcount[i]=0;

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d,,,,,,,,,\n", l, r); R_FlushConsole();
#endif

    // read the value chunk
    ff_vmode_get_contiguous( fromvalue, l, n, valuebuffer);

    // count each key
    ram_integer_keycount(valuebuffer, count, keyoffset, keylength, 0, n-1, has_na);

    // cumulate the counts for each key
    for (i=0; i<=keylength;i++)
      allcount[i] += count[i];
  }


  // this was large RAM, let's free here, then we have it for the filesystem cache
  R_Free(count);


  nNA = allcount[0];

  l = left; r = left+ordersize-1;
  i=0; n=ordersize;
  if (r>right){
    r = right;
    n = r-l+1;
  }
  if (na_last){
    if (decreasing){
      k=keylength; v=keyoffset+keylength;
      while(1){
        while(allcount[k]){
          //Rprintf("left=%d l=%d r=%d right=%d i=%d n=%d k=%d allcount[k]=%d\n", left, l, r, right, i, n, k, allcount[k]);  R_FlushConsole();
          allcount[k]--;
          valuebuffer[i++]=v;
          if (i==n){
            // write the value chunk
            ff_vmode_set_contiguous( fromvalue, l, n, valuebuffer);
            i=0;l+=ordersize;r+=ordersize;
            if (r>right){
              r = right;
              n = r-l+1;
            }
          }
        }
        if (k>1){
          k--;v--;
        }else{
          if (k==1){
            k = 0; v = NA_INTEGER;
          }else
            break;
        }
      }
    }else{
      k=1; v=keyoffset+1;
      while(1){
        while(allcount[k]){
          //Rprintf("left=%d l=%d r=%d right=%d i=%d n=%d k=%d allcount[k]=%d\n", left, l, r, right, i, n, k, allcount[k]);  R_FlushConsole();
          allcount[k]--;
          valuebuffer[i++]=v;
          if (i==n){
            // write the value chunk
            ff_vmode_set_contiguous( fromvalue, l, n, valuebuffer);
            i=0;l+=ordersize;r+=ordersize;
            if (r>right){
              r = right;
              n = r-l+1;
            }
          }
        }
        if (k==0)
          break;
        else if (k<keylength){
          k++;v++;
        }else{
          v = NA_INTEGER;
          k=0;
        }
      }
    }
  }else{
    v = NA_INTEGER;
    k = 0;
    if (decreasing){
      while(1){
        while(allcount[k]){
          //Rprintf("left=%d l=%d r=%d right=%d i=%d n=%d k=%d allcount[k]=%d\n", left, l, r, right, i, n, k, allcount[k]);  R_FlushConsole();
          allcount[k]--;
          valuebuffer[i++]=v;
          if (i==n){
            // write the value chunk
            ff_vmode_set_contiguous( fromvalue, l, n, valuebuffer);
            i=0;l+=ordersize;r+=ordersize;
            if (r>right){
              r = right;
              n = r-l+1;
            }
          }
        }
        if (k>1){
          k--;v--;
        }else{
          if (k==1)
            break;
          else{
            k = keylength; v = keyoffset + keylength;
          }
        }
      }
    }else{
      while(1){
        while(allcount[k]){
          //Rprintf("left=%d l=%d r=%d right=%d i=%d n=%d k=%d allcount[k]=%d\n", left, l, r, right, i, n, k, allcount[k]);  R_FlushConsole();
          allcount[k]--;
          valuebuffer[i++]=v;
          if (i==n){
            // write the value chunk
            ff_vmode_set_contiguous( fromvalue, l, n, valuebuffer);
            i=0;l+=ordersize;r+=ordersize;
            if (r>right){
              r = right;
              n = r-l+1;
            }
          }
        }
        if (k==0){
          k=1; v = keyoffset + 1;
        }else if (k<keylength){
          k++;v++;
        }else
            break;
      }
    }
  }

  R_Free(valuebuffer);
  R_Free(allcount);

  INTEGER(ret_)[0] = nNA;
  UNPROTECT(1);
  return ret_;
}






// chunkwise order auxindex_ without sorting index_
// both ffs must have same length (no virtual windows)
SEXP r_ff_index_chunkorder(
  SEXP index_        /* ff index vector */
, SEXP indexorder_     /* ff output positions */
, SEXP indexsize_    /* number of elements in both, x_ and index_ */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=radixorder 4=quickorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (same size as in index_get) */
)
{
  SEXP ret_ = R_NilValue;

  IndexT method    = asInteger(method_);

  void *index = R_ExternalPtrAddr(index_);
  void *indexorder = R_ExternalPtrAddr(indexorder_);

  IndexT indexsize = asInteger(indexsize_);
  IndexT ordersize = asInteger(ordersize_);

  IndexT *valuebuffer;
  IndexT *indexbuffer;
  IndexT *auxindexbuffer = 0; // keep compiler quiet
  IndexT *count = 0; // keep compiler quiet

  valuebuffer    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  indexbuffer    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  switch (method){
    case 0:{
      auxindexbuffer    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
      break;
      }
    case 2:{
      auxindexbuffer    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
      count    = (IndexT *) R_alloc(NWORD+1, sizeof(IndexT));
      break;
      }
  }

  IndexT l,r,i,n;

#if VERBOSE_LEVEL>0
  Rprintf("chunkorder pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("chunkorder,from,to,type,L1,l1,r1,R1,L2,l2,r2,R2\n"); R_FlushConsole();
#endif
#endif

  r = ordersize;
  for (l = 0; l<indexsize; l+=ordersize, r+=ordersize){
    if (r>indexsize)
      r=indexsize;
    n = r-l;

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d\n", l, r-1); R_FlushConsole();
#endif

    ff_integer_get_contiguous( index, l, n, valuebuffer);
    for (i=0;i<n;i++){
      indexbuffer[i] = i;
    }
    switch(method){
      case 0:{
        ram_integer_mergeorder(valuebuffer, indexbuffer, auxindexbuffer, 0, 0, n-1, FALSE, FALSE, FALSE);
        break;}
      case 1:{
        ram_integer_shellorder(valuebuffer, indexbuffer, 0, 0, n-1, FALSE, FALSE, FALSE, FALSE); // don't need stabilization here
        break;
        }
      case 2:{
        ram_integer_radixorder(valuebuffer, indexbuffer, auxindexbuffer, count, 0, 0, n-1, FALSE, FALSE, FALSE);
        break;
        }
      case 4:{
        R_qsort_int_I (valuebuffer, indexbuffer, 1, n);
        break;
        }
    }

    ff_integer_set_contiguous( indexorder, l, n, indexbuffer); // NOT C2R !!
  }

  return ret_;
}


/* write baseff ordered by index to returnff
   assumption
   left .. right is same for baseff returnff and index (same virtual window)
   xx this is too complicated => lets deprecate the virtual window feature
*/
SEXP r_ff_double_index_get(
  SEXP ffmode_
, SEXP baseff_         /* ff input data vector */
, SEXP returnff_        /* ff output data vector */
, SEXP index_        /* ff index data vector */
, SEXP auxindex_     /* LOGICAL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
, SEXP offset_       /* e.g. 1 for R2C */
, SEXP left_         /* left position of the index to be applied, xx if this is used, it is added to offset, i.e. we assume that the index counting starts at left */
, SEXP right_        /* right position of teh index to be applied */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=radixorder 4=quickorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
)
{
  SEXP ret_ = R_NilValue;

  IndexT method    = asInteger(method_);

  IndexT left = asInteger(left_) - 1;  //R2C
  IndexT right = asInteger(right_) - 1;  //R2C
  IndexT ordersize = asInteger(ordersize_);
  IndexT offset = asInteger(offset_) + left; // beware

  void *from = R_ExternalPtrAddr(baseff_);
  void *to = R_ExternalPtrAddr(returnff_);
  void *index = R_ExternalPtrAddr(index_);
  void *auxindex = 0;

  ValueT *valuebuffer;
  IndexT *indexbuffer;
  IndexT *auxindexbuffer = 0; // keep compiler quiet
  IndexT *auxindexbuffer2 = 0; // keep compiler quiet
  IndexT *count = 0; // keep compiler quiet

  //void (*ff_vmode_get_contiguous)( void *handle, int index, int size, ValueT *ret );
  void (*ff_vmode_set_contiguous)( void *, int, int, ValueT * );
   switch (asInteger(ffmode_)) {
 #if VMODE_COMPILE_SINGLE
   case 10: //ff_vmode_get_contiguous =  ff_single_get_contiguous;
            ff_vmode_set_contiguous =  ff_single_set_contiguous; break;
 #endif
 #if VMODE_COMPILE_DOUBLE
   case 11: //ff_vmode_get_contiguous =  ff_double_get_contiguous;
            ff_vmode_set_contiguous =  ff_double_set_contiguous; break;
 #endif
   default: error("unknown .ffmode[vmode(ffobj)]");
   }

  ValueT (*ff_vmode_get)( void *, int );
  //void (*ff_vmode_set)( void *, int, ValueT );
   switch (asInteger(ffmode_)) {
 #if VMODE_COMPILE_SINGLE
   case 10: ff_vmode_get =  ff_single_get;
            //ff_vmode_set =  ff_single_set; 
            break;
 #endif
 #if VMODE_COMPILE_DOUBLE
   case 11: ff_vmode_get =  ff_double_get;
            //ff_vmode_set =  ff_double_set; 
            break;
 #endif
   default: error("unknown .ffmode[vmode(ffobj)]");
   }


  Rboolean lauxindex;
  if (auxindex_==R_NilValue)
    lauxindex = NA_LOGICAL; /* we order on-the-fly */
  else if (isLogical(auxindex_)){
    lauxindex = asLogical(auxindex_);
    if (lauxindex!=NA_LOGICAL && lauxindex)
      error("auxindex==TRUE not allowed");
  }else{
    lauxindex = TRUE;
  }

  valuebuffer = (ValueT *) R_alloc(ordersize, sizeof(ValueT));
  indexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));

  if (lauxindex==NA_LOGICAL){
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
    switch (method){
      case 0:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        break;
        }
      case 2:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        count    = (IndexT *) R_alloc(NWORD+1, sizeof(IndexT));
        break;
        }
    }
  }else if(lauxindex){
    auxindex = R_ExternalPtrAddr(auxindex_);
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  }

  IndexT l,r,i,j,n;

#if VERBOSE_LEVEL>0
  Rprintf("index_get pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("index_get,from,to\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d\n", l, r); R_FlushConsole();
#endif

    ff_integer_get_contiguous( index, l, n, indexbuffer);
    if (lauxindex==NA_LOGICAL){ // chunkorder index positions on-the-fly
      for (i=0;i<n;i++){
        auxindexbuffer[i] = i;
      }

      switch(method){
        case 0:{
          ram_integer_mergeorder(indexbuffer, auxindexbuffer, auxindexbuffer2, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;}
        case 1:{
          ram_integer_shellorder(indexbuffer, auxindexbuffer, 0, 0, n-1, FALSE, FALSE, FALSE, FALSE); // don't need stabilization here
          break;
          }
        case 2:{
          ram_integer_radixorder(indexbuffer, auxindexbuffer, auxindexbuffer2, count, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;
          }
        case 4:{
          R_qsort_int_I (indexbuffer, auxindexbuffer, 1, n);
          break;
          }
      }

    }else if (lauxindex){ // read chunkorder of index from auxindex
      ff_integer_get_contiguous( auxindex, l, n, auxindexbuffer);
    }

    if (method==4 && lauxindex==NA_LOGICAL){
      // with quicksort indexbuffer is already sorted, therefore we do not use the code below with indexbuffer[j]
      if (offset){
        for (i=0;i<n;i++){
          valuebuffer[auxindexbuffer[i]] = ff_vmode_get(from, indexbuffer[i] - offset);//-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          valuebuffer[auxindexbuffer[i]] = ff_vmode_get(from, indexbuffer[i]);//-1==R2C
        }
      }
    }else if (lauxindex==NA_LOGICAL || lauxindex){ // we have auxindex
      if (offset){
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          valuebuffer[j] = ff_vmode_get(from, indexbuffer[j] - offset);//-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          valuebuffer[j] = ff_vmode_get(from, indexbuffer[j]);//-1==R2C
        }
      }
    }else{  // do not use chunkorder (just for testing, don't use this for production, can take applying index more time than order creation needed)
      if (offset){
        for (i=0;i<n;i++){
          valuebuffer[i] = ff_vmode_get(from, indexbuffer[i] - offset);//-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          valuebuffer[i] = ff_vmode_get(from, indexbuffer[i]);//-1==R2C
        }
      }
    }

    ff_vmode_set_contiguous( to, l, n, valuebuffer);
  }

  return ret_;
}


SEXP r_ff_integer_index_get(
  SEXP ffmode_
, SEXP baseff_         /* ff input data vector */
, SEXP returnff_        /* ff output data vector */
, SEXP index_        /* ff index data vector */
, SEXP auxindex_     /* LOGICAL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
, SEXP offset_       /* e.g. 1 for R2C */
, SEXP left_         /* left position of the index to be applied, xx if this is used, it is added to offset, i.e. we assume that the index counting starts at left */
, SEXP right_        /* right position of teh index to be applied */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=radixorder 4=quickorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
)
{
  SEXP ret_ = R_NilValue;

  IndexT method    = asInteger(method_);

  IndexT left = asInteger(left_) - 1;  //R2C
  IndexT right = asInteger(right_) - 1;  //R2C
  IndexT ordersize = asInteger(ordersize_);
  IndexT offset = asInteger(offset_) + left; // beware

  void *from = R_ExternalPtrAddr(baseff_);
  void *to = R_ExternalPtrAddr(returnff_);
  void *index = R_ExternalPtrAddr(index_);
  void *auxindex = 0;

  IndexT *valuebuffer;
  IndexT *indexbuffer;
  IndexT *auxindexbuffer = 0; // keep compiler quiet
  IndexT *auxindexbuffer2 = 0; // keep compiler quiet
  IndexT *count = 0; // keep compiler quiet

  //void (*ff_vmode_get_contiguous)( void *handle, int index, int size, IndexT *ret );
  void (*ff_vmode_set_contiguous)( void *, int, int, IndexT * );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: //ff_vmode_get_contiguous = ff_boolean_get_contiguous;
          ff_vmode_set_contiguous = ff_boolean_set_contiguous; break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: //ff_vmode_get_contiguous = ff_logical_get_contiguous;
          ff_vmode_set_contiguous = ff_logical_set_contiguous; break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: //ff_vmode_get_contiguous = ff_quad_get_contiguous;
          ff_vmode_set_contiguous = ff_quad_set_contiguous; break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: //ff_vmode_get_contiguous = ff_nibble_get_contiguous;
          ff_vmode_set_contiguous = ff_nibble_set_contiguous; break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: //ff_vmode_get_contiguous = ff_byte_get_contiguous;
          ff_vmode_set_contiguous = ff_byte_set_contiguous; break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: //ff_vmode_get_contiguous = ff_ubyte_get_contiguous;
          ff_vmode_set_contiguous = ff_ubyte_set_contiguous; break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: //ff_vmode_get_contiguous = ff_short_get_contiguous;
          ff_vmode_set_contiguous = ff_short_set_contiguous; break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: //ff_vmode_get_contiguous = ff_ushort_get_contiguous;
          ff_vmode_set_contiguous = ff_ushort_set_contiguous; break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: //ff_vmode_get_contiguous = ff_integer_get_contiguous;
          ff_vmode_set_contiguous = ff_integer_set_contiguous; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }

  IndexT (*ff_vmode_get)( void *, int );
  // void (*ff_vmode_set)( void *, int, IndexT );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ff_vmode_get = ff_boolean_get;
          //ff_vmode_set = ff_boolean_set; 
          break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ff_vmode_get = ff_logical_get;
          //ff_vmode_set = ff_logical_set; 
          break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ff_vmode_get = ff_quad_get;
          //ff_vmode_set = ff_quad_set; 
          break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ff_vmode_get = ff_nibble_get;
          //ff_vmode_set = ff_nibble_set; 
          break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ff_vmode_get = ff_byte_get;
          //ff_vmode_set = ff_byte_set; 
          break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ff_vmode_get = ff_ubyte_get;
          //ff_vmode_set = ff_ubyte_set; 
          break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ff_vmode_get = ff_short_get;
          //ff_vmode_set = ff_short_set; 
          break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ff_vmode_get = ff_ushort_get;
          //ff_vmode_set = ff_ushort_set; 
          break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ff_vmode_get = ff_integer_get;
          //ff_vmode_set = ff_integer_set; 
          break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }

  Rboolean lauxindex;
  if (auxindex_==R_NilValue)
    lauxindex = NA_LOGICAL; /* we order on-the-fly */
  else if (isLogical(auxindex_)){
    lauxindex = asLogical(auxindex_);
    if (lauxindex!=NA_LOGICAL && lauxindex)
      error("auxindex==TRUE not allowed");
  }else{
    lauxindex = TRUE;
  }

  valuebuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  indexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));

  if (lauxindex==NA_LOGICAL){
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
    switch (method){
      case 0:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        break;
        }
      case 2:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        count    = (IndexT *) R_alloc(NWORD+1, sizeof(IndexT));
        break;
        }
    }
  }else if(lauxindex){
    auxindex = R_ExternalPtrAddr(auxindex_);
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  }

  IndexT l,r,i,j,n;

#if VERBOSE_LEVEL>0
  Rprintf("index_get pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("index_get,from,to\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d\n", l, r); R_FlushConsole();
#endif

    ff_integer_get_contiguous( index, l, n, indexbuffer);
    if (lauxindex==NA_LOGICAL){ // chunkorder index positions on-the-fly
      for (i=0;i<n;i++){
        auxindexbuffer[i] = i;
      }

      switch(method){
        case 0:{
          ram_integer_mergeorder(indexbuffer, auxindexbuffer, auxindexbuffer2, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;}
        case 1:{
          ram_integer_shellorder(indexbuffer, auxindexbuffer, 0, 0, n-1, FALSE, FALSE, FALSE, FALSE); // don't need stabilization here
          break;
          }
        case 2:{
          ram_integer_radixorder(indexbuffer, auxindexbuffer, auxindexbuffer2, count, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;
          }
        case 4:{
          R_qsort_int_I (indexbuffer, auxindexbuffer, 1, n);
          break;
          }
      }

    }else if (lauxindex){ // read chunkorder of index from auxindex
      ff_integer_get_contiguous( auxindex, l, n, auxindexbuffer);
    }

    if (method==4 && lauxindex==NA_LOGICAL){
      // with quicksort indexbuffer is already sorted, therefore we do not use the code below with indexbuffer[j]
      if (offset){
        for (i=0;i<n;i++){
          valuebuffer[auxindexbuffer[i]] = ff_vmode_get(from, indexbuffer[i] - offset);//-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          valuebuffer[auxindexbuffer[i]] = ff_vmode_get(from, indexbuffer[i]);//-1==R2C
        }
      }
    }else if (lauxindex==NA_LOGICAL || lauxindex){ // we have auxindex
      if (offset){
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          valuebuffer[j] = ff_vmode_get(from, indexbuffer[j] - offset);//-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          valuebuffer[j] = ff_vmode_get(from, indexbuffer[j]);//-1==R2C
        }
      }
    }else{  // do not use chunkorder (just for testing, don't use this for production, can take applying index more time than order creation needed)
      if (offset){
        for (i=0;i<n;i++){
          valuebuffer[i] = ff_vmode_get(from, indexbuffer[i] - offset);//-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          valuebuffer[i] = ff_vmode_get(from, indexbuffer[i]);//-1==R2C
        }
      }
    }

    ff_vmode_set_contiguous( to, l, n, valuebuffer);
  }

  return ret_;
}






/* update baseff ordered by index from valueff
   assumption
   left .. right is same for baseff valueff and index (same virtual window)
   xx this is too complicated => lets deprecate the virtual window feature
*/
SEXP r_ff_double_index_set(
  SEXP ffmode_
, SEXP baseff_         /* ff input data vector */
, SEXP valueff_        /* ff data vector with update values */
, SEXP index_        /* ff index data vector */
, SEXP auxindex_     /* LOGICAL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
, SEXP offset_       /* e.g. 1 for R2C */
, SEXP left_         /* left position of the index to be applied, xx if this is used, it is added to offset, i.e. we assume that the index counting starts at left */
, SEXP right_        /* right position of teh index to be applied */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=radixorder 4=quickorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
)
{
  SEXP ret_ = R_NilValue;

  IndexT method    = asInteger(method_);

  IndexT left = asInteger(left_) - 1;  //R2C
  IndexT right = asInteger(right_) - 1;  //R2C
  IndexT ordersize = asInteger(ordersize_);
  IndexT offset = asInteger(offset_) + left; // beware

  void *from = R_ExternalPtrAddr(baseff_);
  void *to = R_ExternalPtrAddr(valueff_);
  void *index = R_ExternalPtrAddr(index_);
  void *auxindex = 0;

  ValueT *valuebuffer;
  IndexT *indexbuffer;
  IndexT *auxindexbuffer = 0; // keep compiler quiet
  IndexT *auxindexbuffer2 = 0; // keep compiler quiet
  IndexT *count = 0; // keep compiler quiet

  void (*ff_vmode_get_contiguous)( void *handle, int index, int size, ValueT *ret );
  //void (*ff_vmode_set_contiguous)( void *, int, int, ValueT * );
   switch (asInteger(ffmode_)) {
 #if VMODE_COMPILE_SINGLE
   case 10: ff_vmode_get_contiguous =  ff_single_get_contiguous;
            //ff_vmode_set_contiguous =  ff_single_set_contiguous; 
            break;
 #endif
 #if VMODE_COMPILE_DOUBLE
   case 11: ff_vmode_get_contiguous =  ff_double_get_contiguous;
            //ff_vmode_set_contiguous =  ff_double_set_contiguous; 
            break;
 #endif
   default: error("unknown .ffmode[vmode(ffobj)]");
   }

  //ValueT (*ff_vmode_get)( void *, int );
  void (*ff_vmode_set)( void *, int, ValueT );
   switch (asInteger(ffmode_)) {
 #if VMODE_COMPILE_SINGLE
   case 10: //ff_vmode_get =  ff_single_get;
            ff_vmode_set =  ff_single_set; break;
 #endif
 #if VMODE_COMPILE_DOUBLE
   case 11: //ff_vmode_get =  ff_double_get;
            ff_vmode_set =  ff_double_set; break;
 #endif
   default: error("unknown .ffmode[vmode(ffobj)]");
   }


  Rboolean lauxindex;
  if (auxindex_==R_NilValue)
    lauxindex = NA_LOGICAL; /* we order on-the-fly */
  else if (isLogical(auxindex_)){
    lauxindex = asLogical(auxindex_);
    if (lauxindex!=NA_LOGICAL && lauxindex)
      error("auxindex==TRUE not allowed");
  }else{
    lauxindex = TRUE;
  }

  valuebuffer = (ValueT *) R_alloc(ordersize, sizeof(ValueT));
  indexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));

  if (lauxindex==NA_LOGICAL){
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
    switch (method){
      case 0:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        break;
        }
      case 2:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        count    = (IndexT *) R_alloc(NWORD+1, sizeof(IndexT));
        break;
        }
    }
  }else if(lauxindex){
    auxindex = R_ExternalPtrAddr(auxindex_);
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  }

  IndexT l,r,i,j,n;

#if VERBOSE_LEVEL>0
  Rprintf("index_set pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("index_set,from,to\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d\n", l, r); R_FlushConsole();
#endif

    ff_vmode_get_contiguous( to, l, n, valuebuffer);
    ff_integer_get_contiguous( index, l, n, indexbuffer);

    if (lauxindex==NA_LOGICAL){ // chunkorder index positions on-the-fly
      for (i=0;i<n;i++){
        auxindexbuffer[i] = i;
      }

      switch(method){
        case 0:{
          ram_integer_mergeorder(indexbuffer, auxindexbuffer, auxindexbuffer2, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;}
        case 1:{
          ram_integer_shellorder(indexbuffer, auxindexbuffer, 0, 0, n-1, FALSE, FALSE, FALSE, FALSE); // don't need stabilization here
          break;
          }
        case 2:{
          ram_integer_radixorder(indexbuffer, auxindexbuffer, auxindexbuffer2, count, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;
          }
        case 4:{
          R_qsort_int_I (indexbuffer, auxindexbuffer, 1, n);
          break;
          }
      }

    }else if (lauxindex){ // read chunkorder of index from auxindex
      ff_integer_get_contiguous( auxindex, l, n, auxindexbuffer);
    }

    if (method==4 && lauxindex==NA_LOGICAL){
      // with quicksort indexbuffer is already sorted, therefore we do not use the code below with indexbuffer[j]
      if (offset){
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i] - offset, valuebuffer[auxindexbuffer[i]]);  //-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i], valuebuffer[auxindexbuffer[i]]);  //-1==R2C
        }
      }
    }else if (lauxindex==NA_LOGICAL || lauxindex){ // we have auxindex
      if (offset){
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          ff_vmode_set( from, indexbuffer[j] - offset, valuebuffer[j]);  //-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          ff_vmode_set( from, indexbuffer[j], valuebuffer[j]);  //-1==R2C
        }
      }
    }else{  // do not use chunkorder (just for testing, don't use this for production, can take applying index more time than order creation needed)
      if (offset){
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i] - offset, valuebuffer[i]);  //-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i], valuebuffer[i]);  //-1==R2C
        }
      }
    }

  }

  return ret_;
}


SEXP r_ff_integer_index_set(
  SEXP ffmode_
, SEXP baseff_         /* ff input data vector */
, SEXP valueff_        /* ff output data vector */
, SEXP index_        /* ff index data vector */
, SEXP auxindex_     /* LOGICAL or ff chunkwise order of index positions as returned by r_ff_index_chunkorder, if NULL _index positions are ordered on-the-fly */
, SEXP offset_       /* e.g. 1 for R2C */
, SEXP left_         /* left position of the index to be applied, xx if this is used, it is added to offset, i.e. we assume that the index counting starts at left */
, SEXP right_        /* right position of teh index to be applied */
, SEXP method_       /* 0=mergeorder 1=shellorder 2=radixorder 4=quickorder */
, SEXP ordersize_    /* int no of elements to be ordered in RAM (must be same as in r_ff_index_chunkorder) */
)
{
  SEXP ret_ = R_NilValue;

  IndexT method    = asInteger(method_);

  IndexT left = asInteger(left_) - 1;  //R2C
  IndexT right = asInteger(right_) - 1;  //R2C
  IndexT ordersize = asInteger(ordersize_);
  IndexT offset = asInteger(offset_) + left; // beware

  void *from = R_ExternalPtrAddr(baseff_);
  void *to = R_ExternalPtrAddr(valueff_);
  void *index = R_ExternalPtrAddr(index_);
  void *auxindex = 0;

  IndexT *valuebuffer;
  IndexT *indexbuffer;
  IndexT *auxindexbuffer = 0; // keep compiler quiet
  IndexT *auxindexbuffer2 = 0; // keep compiler quiet
  IndexT *count = 0; // keep compiler quiet

  void (*ff_vmode_get_contiguous)( void *handle, int index, int size, IndexT *ret );
  //void (*ff_vmode_set_contiguous)( void *, int, int, IndexT * );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: ff_vmode_get_contiguous = ff_boolean_get_contiguous;
          //ff_vmode_set_contiguous = ff_boolean_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: ff_vmode_get_contiguous = ff_logical_get_contiguous;
          //ff_vmode_set_contiguous = ff_logical_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: ff_vmode_get_contiguous = ff_quad_get_contiguous;
          //ff_vmode_set_contiguous = ff_quad_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: ff_vmode_get_contiguous = ff_nibble_get_contiguous;
          //ff_vmode_set_contiguous = ff_nibble_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: ff_vmode_get_contiguous = ff_byte_get_contiguous;
          //ff_vmode_set_contiguous = ff_byte_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: ff_vmode_get_contiguous = ff_ubyte_get_contiguous;
          //ff_vmode_set_contiguous = ff_ubyte_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: ff_vmode_get_contiguous = ff_short_get_contiguous;
          //ff_vmode_set_contiguous = ff_short_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: ff_vmode_get_contiguous = ff_ushort_get_contiguous;
          //ff_vmode_set_contiguous = ff_ushort_set_contiguous; 
          break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: ff_vmode_get_contiguous = ff_integer_get_contiguous;
          //ff_vmode_set_contiguous = ff_integer_set_contiguous; 
          break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }

  //IndexT (*ff_vmode_get)( void *, int );
  void (*ff_vmode_set)( void *, int, IndexT );
  switch (asInteger(ffmode_)) {
#if VMODE_COMPILE_BOOLEAN
  case 1: //ff_vmode_get = ff_boolean_get;
          ff_vmode_set = ff_boolean_set; break;
#endif
#if VMODE_COMPILE_LOGICAL
  case 2: //ff_vmode_get = ff_logical_get;
          ff_vmode_set = ff_logical_set; break;
#endif
#if VMODE_COMPILE_QUAD
  case 3: //ff_vmode_get = ff_quad_get;
          ff_vmode_set = ff_quad_set; break;
#endif
#if VMODE_COMPILE_NIBBLE
  case 4: //ff_vmode_get = ff_nibble_get;
          ff_vmode_set = ff_nibble_set; break;
#endif
#if VMODE_COMPILE_BYTE
  case 5: //ff_vmode_get = ff_byte_get;
          ff_vmode_set = ff_byte_set; break;
#endif
#if VMODE_COMPILE_UBYTE
  case 6: //ff_vmode_get = ff_ubyte_get;
          ff_vmode_set = ff_ubyte_set; break;
#endif
#if VMODE_COMPILE_SHORT
  case 7: //ff_vmode_get = ff_short_get;
          ff_vmode_set = ff_short_set; break;
#endif
#if VMODE_COMPILE_USHORT
  case 8: //ff_vmode_get = ff_ushort_get;
          ff_vmode_set = ff_ushort_set; break;
#endif
#if VMODE_COMPILE_INTEGER
  case 9: //ff_vmode_get = ff_integer_get;
          ff_vmode_set = ff_integer_set; break;
#endif
  default: error("unknown .ffmode[vmode(ffobj)]");
  }

  Rboolean lauxindex;
  if (auxindex_==R_NilValue)
    lauxindex = NA_LOGICAL; /* we order on-the-fly */
  else if (isLogical(auxindex_)){
    lauxindex = asLogical(auxindex_);
    if (lauxindex!=NA_LOGICAL && lauxindex)
      error("auxindex==TRUE not allowed");
  }else{
    lauxindex = TRUE;
  }

  valuebuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  indexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));

  if (lauxindex==NA_LOGICAL){
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
    switch (method){
      case 0:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        break;
        }
      case 2:{
        auxindexbuffer2    = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
        count    = (IndexT *) R_alloc(NWORD+1, sizeof(IndexT));
        break;
        }
    }
  }else if(lauxindex){
    auxindex = R_ExternalPtrAddr(auxindex_);
    auxindexbuffer = (IndexT *) R_alloc(ordersize, sizeof(IndexT));
  }

  IndexT l,r,i,j,n;

#if VERBOSE_LEVEL>0
  Rprintf("index_set pass\n"); R_FlushConsole();
#if VERBOSE_LEVEL>1
  Rprintf("index_set,from,to\n"); R_FlushConsole();
#endif
#endif

  for (l = left, r = left+ordersize-1, n=ordersize; l<=right; l+=ordersize, r+=ordersize){
    if (r>right){
      r = right;
      n = r-l+1;
    }

#if VERBOSE_LEVEL>1
      Rprintf("0,%d,%d\n", l, r); R_FlushConsole();
#endif

    ff_vmode_get_contiguous( to, l, n, valuebuffer);
    ff_integer_get_contiguous( index, l, n, indexbuffer);
    if (lauxindex==NA_LOGICAL){ // chunkorder index positions on-the-fly
      for (i=0;i<n;i++){
        auxindexbuffer[i] = i;
      }

      switch(method){
        case 0:{
          ram_integer_mergeorder(indexbuffer, auxindexbuffer, auxindexbuffer2, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;}
        case 1:{
          ram_integer_shellorder(indexbuffer, auxindexbuffer, 0, 0, n-1, FALSE, FALSE, FALSE, FALSE); // don't need stabilization here
          break;
          }
        case 2:{
          ram_integer_radixorder(indexbuffer, auxindexbuffer, auxindexbuffer2, count, 0, 0, n-1, FALSE, FALSE, FALSE);
          break;
          }
        case 4:{
          R_qsort_int_I (indexbuffer, auxindexbuffer, 1, n);
          break;
          }
      }

    }else if (lauxindex){ // read chunkorder of index from auxindex
      ff_integer_get_contiguous( auxindex, l, n, auxindexbuffer);
    }

    if (method==4 && lauxindex==NA_LOGICAL){
      // with quicksort indexbuffer is already sorted, therefore we do not use the code below with indexbuffer[j]
      if (offset){
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i] - offset, valuebuffer[auxindexbuffer[i]]);  //-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i], valuebuffer[auxindexbuffer[i]]);  //-1==R2C
        }
      }
    }else if (lauxindex==NA_LOGICAL || lauxindex){ // we have auxindex
      if (offset){
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          ff_vmode_set( from, indexbuffer[j] - offset, valuebuffer[j]);  //-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          j = auxindexbuffer[i]; // NOT R2C
          ff_vmode_set( from, indexbuffer[j], valuebuffer[j]);  //-1==R2C
        }
      }
    }else{  // do not use chunkorder (just for testing, don't use this for production, can take applying index more time than order creation needed)
      if (offset){
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i] - offset, valuebuffer[i]);  //-1==R2C
        }
      }else{
        for (i=0;i<n;i++){
          ff_vmode_set( from, indexbuffer[i], valuebuffer[i]);  //-1==R2C
        }
      }
    }

  }

  return ret_;
}

