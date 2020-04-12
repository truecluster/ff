/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007-2012 Daniel Adler <dadler@uni-goettingen.de>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

/////////////////////////////////////////////////////////////////////////////*/


/*/////////////////////////////////////////////////////////////////////////////
//
// R ff - ANSI C API
//
/////////////////////////////////////////////////////////////////////////////*/

#include "ff.h"
#include "Array.hpp"
#include <climits>
#include <stdint.h>
// --- common interface --------------------------------------------------------

// TODO: ff driver properties get/set ffGet/SetProperty  e.g. ffGetProperty("pagesize")
int ff_getpagesize()
{
  return static_cast<int>( ff::FileMapping::getPageSize() );
}
// -> ffGetProperty("lasterror")
int  ff_geterror(FF handle)
{
  if (handle)
  {
    ff::ArrayBase* a = reinterpret_cast<ff::ArrayBase*>(handle);
    return a->getError();
  }
  return ff::E_NO_ERROR;
}

const char* ff_geterrstr(FF handle)
{
  if (handle)
  {
    ff::ArrayBase* a = reinterpret_cast<ff::ArrayBase*>(handle);
    return getErrorString(a->getError());
  }
  return getErrorString(ff::E_NO_ERROR);
}

void ff_delete(FF handle)
{
  ff::ArrayBase* a = reinterpret_cast<ff::ArrayBase*>(handle);
  delete a;
}

void ff_close(FF handle)
{
  ff::ArrayBase* a = reinterpret_cast<ff::ArrayBase*>(handle);
  a->close();
}
// read-only property
int ff_len(FF handle)
{
  ff::ArrayBase* a = reinterpret_cast<ff::ArrayBase*>(handle);
  return static_cast<int>( a->size() );
}

namespace ff {

// ----------------------------------------------------------------------------
// generic add

template<typename ImplT, typename T> inline T add(T a, T b) { return a+b; }


// ----------------------------------------------------------------------------
// cell template functions

template<typename T, class ImplT, typename IndexT>
T get(ImplT* impl, IndexT i)
{
  return impl->template get<T,IndexT>(i);
}

template<typename T, class ImplT, typename IndexT>
void set(ImplT* impl, IndexT i, T x)
{
    impl->template set<T,IndexT>(i,x);
}

template<typename T, class ImplT, typename IndexT>
T getset(ImplT* impl, IndexT i, T newval)
{
  T oldval = impl->template get<T,IndexT>(i);
  impl->template set<T,IndexT>(i, newval);
  return oldval;
}

template<typename T, class ImplT, typename IndexT>
void addset(ImplT* impl, IndexT i, T op2)
{
  impl->template set<T,IndexT>(i, add<ImplT,T>( impl->template get<T,IndexT>(i) , op2 ) );
}

/* Daniels original Code: add may overrun e.g. quad 
template<typename T, class ImplT, typename IndexT>
T addgetset(ImplT* impl, IndexT i, T op2)
{
  T newval = add<ImplT,T>( impl->template get<T,IndexT>(i) , op2 ); 
  impl->template set<T,IndexT>(i, newval);
return newval;
}
*/

/* this also returns newval, however AFTER making sure the addition is wrapped around 
   may it could be faster if not reading twice but putting cappaing in add, however, I don't know how to do this
 */
template<typename T, class ImplT, typename IndexT>
T addgetset(ImplT* impl, IndexT i, T op2)
{
  impl->template set<T,IndexT>(i, add<ImplT,T>( impl->template get<T,IndexT>(i) , op2 ));
  return impl->template get<T,IndexT>(i); 
}

// ----------------------------------------------------------------------------
// vector template functions

template<typename T, class ImplT, typename IndexT, typename SizeT>
void getV(ImplT* impl, IndexT i, SizeT s, T* p)
{
  for (IndexT end = i+s; i < end ; ++i ) *p++ = impl->template get<T,IndexT>(i);
}

template<typename T, class ImplT, typename IndexT, typename SizeT>
void setV(ImplT* impl, IndexT i, SizeT s, T* p)
{
  for (IndexT end = i+s; i < end ; ++i) impl->template set<T,IndexT>( i, *p++ );
}

template<typename T, class ImplT, typename IndexT, typename SizeT>
void getsetV(ImplT* impl, IndexT i, SizeT s, T* ret, T* value)
{
  for (IndexT end = i+s; i < end ; ++i) {
    *ret++ = impl->template get<T>(i);
    impl->template set<T,IndexT>(i, *value++ );
  }
}

template<typename T, class ImplT, typename IndexT, typename SizeT>
void addsetV(ImplT* impl, IndexT i, SizeT s, T* value)
{
  for (IndexT end = i+s; i < end ; ++i) {
    impl->template set<T,IndexT>( i, add<ImplT,T>( impl->template get<T,IndexT>(i), *value++) );
  }
}


/* Daniels original Code: add may overrun e.g. quad
template<typename T, class ImplT, typename IndexT, typename SizeT>
void addgetsetV(ImplT* impl, IndexT i, SizeT s, T* ret, T* value)
{
 for (IndexT end = i+s; i < end ; ++i) {
   T buf = add<ImplT,T>( impl->template get<T,IndexT>(i) , *value++ );
   impl->template set<T,IndexT>(i, buf);
   *ret++ = buf;
 }
}
*/

/* this also returns newval, however AFTER making sure the addition is wrapped around 
 may it could be faster if not reading twice but putting cappaing in add, however, I don't know how to do this
 and it is not much slower than before
*/
template<typename T, class ImplT, typename IndexT, typename SizeT>
void addgetsetV(ImplT* impl, IndexT i, SizeT s, T* ret, T* value)
{
 for (IndexT end = i+s; i < end ; ++i) {
   impl->template set<T,IndexT>(i, add<ImplT,T>( impl->template get<T,IndexT>(i) , *value++ ));
   *ret++ = impl->template get<T,IndexT>(i);
 }
}
 
 

// ----------------------------------------------------------------------------
// filters

namespace filters {

// pipe filter

struct pipe
{
  template<typename T> static inline T pack(T x) { return x; }
  template<typename T> static inline T unpack(T x) { return x; }
};

// cast_na filter

template<int BITS>
struct cast_na
{
  static inline int pack(int x)
  {
    return ( x == INT_MIN ) ? ( 1UL<<(BITS-1) ) : x;
  }
  static inline int unpack(int x)
  {
    return ( ( static_cast<unsigned int>(x) & ((1<<BITS)-1) ) == (1<<(BITS-1)) ) ? INT_MIN : x;
  }
};

}

// FFType - FF container type parametrized by policies

template<class ContainerT, class FilterT= filters::pipe>
class FFType : public ContainerT
{
public:
  typedef ContainerT                      container_type;
  typedef typename ContainerT::value_type value_type;
  typedef FilterT                         filter_type;

  template<typename InterfaceT, typename IndexT>
  inline InterfaceT get(IndexT index)
  {
    InterfaceT x = static_cast<InterfaceT>( container_type::get( static_cast<fsize_t>(index) ) );
    x = FilterT::unpack(x);
    return x;
  }

  template<typename InterfaceT, typename IndexT>
  inline void set(IndexT index, InterfaceT x)
  {
    x = filter_type::pack(x);
    container_type::set( static_cast<fsize_t>(index), static_cast<value_type>(x) );
  }
};

// type aliases

typedef signed   char  schar;
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

// R FF Types

using namespace filters; // cast_na

typedef FFType< BitArray<1,uint>                > BooleanImpl  ;
typedef FFType< BitArray<2,uint>                > QuadImpl     ;
typedef FFType< BitArray<2,uint>, cast_na<2>    > LogicalImpl  ;
typedef FFType< BitArray<4,uint>                > NibbleImpl   ;
typedef FFType< Array   <char  >, cast_na<8>    > ByteImpl     ;
typedef FFType< Array   <uchar >                > UByteImpl    ;
typedef FFType< Array   <short >, cast_na<16>   > ShortImpl    ;
typedef FFType< Array   <ushort>                > UShortImpl   ;
typedef FFType< Array   <int   >                > IntegerImpl  ;
typedef FFType< Array   <float >                > SingleImpl   ;
typedef FFType< Array   <double>                > DoubleImpl   ;
typedef FFType< Array   <uchar >                > RawImpl      ;

// add specialization


template<typename T> inline int clamp_na(int x)
{
  if ( ( x >= (1<<((sizeof(T)*8)-1)) ) || ( x < -((1<<((sizeof(T)*8)-1)) ) ) ) return INT_MIN;
    return x;
}

template<typename T> inline int clamp_na(int64_t x)
{
  if ( ( x >= (1LL<<((sizeof(T)*8)-1)) ) || ( x < -((1LL<<((sizeof(T)*8)-1)) ) ) ) return INT_MIN;
    return x;
}


template<> inline int add<LogicalImpl,int>(int a, int b)
{ return ( (a==INT_MIN) || (b==INT_MIN) ) ? INT_MIN : ( (a+b) & 1 ); }
// DISABLED BOOLEAN
// template<> inline int add<BooleanImpl,int>(int a, int b) { return a|b; }
template<> inline int add<ByteImpl,int>(int a, int b)
{ return ( (a==INT_MIN) || (b==INT_MIN) ) ? INT_MIN : clamp_na<char>(a+b); }
template<> inline int add<ShortImpl,int>(int a, int b)
{ return ( (a==INT_MIN) || (b==INT_MIN) ) ? INT_MIN : clamp_na<short>(a+b); }
template<> inline int add<IntegerImpl,int>(int a, int b)
{
  return ( (a==INT_MIN) || (b==INT_MIN) ) ? INT_MIN : (int) clamp_na<int>( ((int64_t)a) + ((int64_t)b ) );
}

}

// R-FF C type interface definition macro

#define FF_DEF_TYPE2(NAME,TYPE,IMPL,INDEX,SIZE) \
FF   ff_##NAME##_new(const char* filepath, TYPE initval, INDEX size, int pagesize, int readonly, int autoflush \
, int createNew /* Martijn Schuemie for zero row ff */ \
) \
{ IMPL* p = new IMPL(); \
  InitParameters pars; \
  pars.path = filepath; \
  pars.size = static_cast<ff::fsize_t>(size); \
  pars.pagesize = static_cast<ff::msize_t>(pagesize); \
  pars.readonly = (readonly == 0 ) ? false : true; \
  pars.autoflush = (autoflush == 0) ? false : true; \
  pars.createNew = createNew; /* Martijn Schuemie for zero row ff */ \
  p->init(pars); \
  return reinterpret_cast<FF>(p); \
}\
\
TYPE ff_##NAME##_get(       FF handle, INDEX index          ) \
{ return get<TYPE,IMPL,INDEX>( reinterpret_cast<IMPL*>(handle), index ); } \
\
void ff_##NAME##_set(       FF handle, INDEX index, TYPE x) \
{ set<TYPE,IMPL,INDEX>( reinterpret_cast<IMPL*>(handle), index, x ); } \
\
TYPE ff_##NAME##_getset(    FF handle, INDEX index, TYPE x) \
{ return getset<TYPE,IMPL,INDEX>( reinterpret_cast<IMPL*>(handle), index, x ); } \
\
TYPE ff_##NAME##_addgetset( FF handle, INDEX index, TYPE x) \
{ return addgetset<TYPE,IMPL,INDEX>( reinterpret_cast<IMPL*>(handle), index, x); } \
\
void ff_##NAME##_addset(    FF handle, INDEX index, TYPE x) \
{ addset<TYPE,IMPL,INDEX>( reinterpret_cast<IMPL*>(handle), index, x); } \
\
void ff_##NAME##_get_contiguous(      FF handle, INDEX index, int size, TYPE* ret               ) \
{ getV<TYPE,IMPL,INDEX,SIZE>( reinterpret_cast<IMPL*>(handle), index, size, ret); } \
\
void ff_##NAME##_set_contiguous(      FF handle, INDEX index, int size, TYPE* value) \
{ setV<TYPE,IMPL,INDEX,SIZE>( reinterpret_cast<IMPL*>(handle), index, size, value); } \
\
void ff_##NAME##_getset_contiguous(   FF handle, INDEX index, int size, TYPE* ret, TYPE* value) \
{ getsetV<TYPE,IMPL,INDEX,SIZE>( reinterpret_cast<IMPL*>(handle), index, size, ret, value ); } \
\
void ff_##NAME##_addgetset_contiguous(FF handle, INDEX index, int size, TYPE* ret, TYPE* value) \
{ addgetsetV<TYPE,IMPL,INDEX,SIZE>( reinterpret_cast<IMPL*>(handle), index, size, ret, value); } \
\
void ff_##NAME##_addset_contiguous(   FF handle, INDEX index, int size, TYPE* value) \
{ addsetV<TYPE,IMPL,INDEX,SIZE>( reinterpret_cast<IMPL*>(handle), index, size, value); }


// front-end generator triggers int and double-index versions

#define FF_DEF_TYPE(NAME,TYPE,IMPL) \
  FF_DEF_TYPE2(NAME,TYPE,IMPL,int,int) \
  FF_DEF_TYPE2(NAME##_d,TYPE,IMPL,double,int)


using namespace ff;

// R-FF C type interface definitions

FF_DEF_TYPE(boolean,int,BooleanImpl)
FF_DEF_TYPE(quad,int,QuadImpl)
FF_DEF_TYPE(logical,int,LogicalImpl)
FF_DEF_TYPE(nibble,int,NibbleImpl)
FF_DEF_TYPE(byte,int,ByteImpl)
FF_DEF_TYPE(ubyte,int,UByteImpl)
FF_DEF_TYPE(short,int,ShortImpl)
FF_DEF_TYPE(ushort,int,UShortImpl)
FF_DEF_TYPE(integer,int,IntegerImpl)
FF_DEF_TYPE(single,double,SingleImpl)
FF_DEF_TYPE(double,double,DoubleImpl)
FF_DEF_TYPE(raw,unsigned char,RawImpl)

