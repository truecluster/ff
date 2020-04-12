/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007,2008 Daniel Adler <dadler@uni-goettingen.de>

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


#ifndef FF_ARRAY_HPP
#define FF_ARRAY_HPP

#include "FileMapping.hpp"

#include <algorithm> // std::min
// D.A. #include <cstdio>
//{ J.O. 16.9.2010 interpreting B.R.
#if defined(__sun__) || defined(__sun) || defined(sun)
#include <stdio.h>
#else
#include <cstdio>
#endif
//} J.O. 16.9.2010

namespace ff {

  /** ff init parameters structure */
  struct InitParameters
  {
    const char* path;
    fsize_t     size;
    msize_t     pagesize;
    bool        readonly;
    bool        autoflush;
    bool        createNew;  // Martijn Schuemie for zero row ff
  };

  /** ArrayBase class (common interface) */
  class ArrayBase
  {
  public:
    /** constructor */
    ArrayBase(msize_t size=0)
        : _fileMapping(0)
        , _fileSection(0)
        , _sectionSize(size)
    {
    }
    /** virtual destructor */
    virtual ~ArrayBase()
    {
        close();
    }
    /** get last error code */
    Error getError() const
    {
      return _fileMapping->getError();
    }
    /** explicitly close */
    void close()
    {
      if (_fileSection) {
        delete _fileSection;
        _fileSection = 0;
      }
      if (_fileMapping) {
        delete _fileMapping;
        _fileMapping = 0;
      }
    }
    /** get size */
    virtual fsize_t size() const = 0;
  protected:
    FileMapping* _fileMapping;
    FileSection* _fileSection;
    msize_t      _sectionSize;

  };


  /** one-dimensional Array container type for a given valuetype ValueT */
  template<typename ValueT>
  class Array : public ArrayBase
  {
  public:

    typedef ValueT            value_type;
    typedef fsize_t           size_type;

    enum { bits = sizeof(value_type)*8 };

    static const inline int get_bits() { return sizeof(value_type)*8; }

    /** constructor */
    Array()
      : ArrayBase(0)
    {
    }
    Array(
      const char* path
    , fsize_t size=0
    , msize_t pagesize=FileMapping::getPageSize()
    , bool    readonly=false
    , bool    autoflush=false
    )
    : ArrayBase(size)
    {
      InitParameters p;

      p.path = path;
      p.size = size;
      p.pagesize = pagesize;
      p.readonly = readonly;
      p.autoflush = autoflush;

      init(p);
    }

    void init(InitParameters& par)
    {
      close();

      _sectionSize = par.pagesize;

      _fileMapping = new FileMapping(par.path, par.size*sizeof(value_type), par.readonly, par.autoflush
, par.createNew  // Martijn Schuemie for zero row ff
);   

      if ( _fileMapping->getError() == E_NO_ERROR )
      {
        msize_t size = static_cast<msize_t>( std::min( _fileMapping->size(), static_cast<fsize_t>(_sectionSize) ) );
        _fileSection = _fileMapping->mapSection( 0, size );
      }
    }

    /** get pointer for element_index offset */
    inline value_type* getPointer(foff_t element_index)
    {
      foff_t byteIndex = element_index * sizeof(value_type);

      if ( !_fileSection->checkOffsetInSection(byteIndex) ) {

        fsize_t offset = byteIndex / _sectionSize * _sectionSize;
        msize_t size   = static_cast<msize_t>( std::min( _fileMapping->size() - offset, static_cast<fsize_t>(_sectionSize) ) );

        _fileSection->reset( offset, size );
      }

      return (value_type*) _fileSection->getPointer(byteIndex);
    }

    /** set value at element_index */
    inline void set(foff_t element_index, value_type v)
    {
      * getPointer(element_index) = v;
    }

    /** get value at element index */
    inline value_type get(foff_t element_index)
    {
      return * getPointer(element_index);
    }

    /** get size of array (in terms of element units) */
    virtual fsize_t size() const
    {
      if (_fileMapping)
        return _fileMapping->size() / sizeof(value_type);
      return 0;
    }
  };


  template<int BITS, typename T=unsigned int>
  class BitArray : public Array<T>
  {
  public:

    typedef Array<T> super_t;
    enum { bits = BITS };

    inline static const int get_bits() { return bits; }

    BitArray(
      const char* path
    , fsize_t size=0
    , msize_t pagesize=FileMapping::getPageSize()
    , bool    readonly=false
    , bool    autoflush=false)
    : Array<T>(path, ( ( (size*BITS) + (sizeof(T)*8-1) ) / 8 ) / sizeof(T), pagesize, readonly, autoflush)
    , mSize(size)
    {
    }

    BitArray()
    : mSize(0)
    {
    }

    /** init */
    void init(InitParameters& p)
    {
      mSize = p.size;
      p.size = ( ( (p.size*BITS) + (sizeof(T)*8-1) ) / 8 ) / sizeof(T);
      super_t::init(p);
    }

    /** get value at bit_index */
    inline T get(foff_t index)
    {
      foff_t element_index;

      int bitindex = split_index(index, element_index);

      T bitset = Array<T>::get( element_index );
      bitset >>= bitindex;
      T mask   = (1<<BITS)-1;
      return bitset & mask;
    }

    /** set value at bit_index */
    inline void set(foff_t index, T value)
    {
      foff_t element_index;

      int bitindex = split_index(index, element_index);

      T bitset = Array<T>::get( element_index );

      T mask   = (1<<BITS)-1;
      value  &= mask;
      mask  <<= bitindex;
      value <<= bitindex;

      bitset = ( bitset & ~mask ) | value;

      Array<T>::set( element_index, bitset );
    }

  private:
    /** split bit_index into element index and bit offset */
    int split_index(foff_t index, foff_t& element_index)
    {
      foff_t bit_index = index * BITS;
      element_index = bit_index / ( sizeof(T)*8 );
      foff_t bit_pos   = bit_index - ( element_index * (sizeof(T)*8) );
      return static_cast<int>(bit_pos);
    }

    fsize_t mSize;
  };

}

#endif // FF_ARRAY_HPP

