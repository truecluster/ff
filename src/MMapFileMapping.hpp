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

#ifndef FF_MMAP_FILE_MAPPING_HPP
#define FF_MMAP_FILE_MAPPING_HPP

#include "types.hpp"
#include "Error.hpp"

/** unix implementation of memory-mapped files */

namespace ff {

  // forward declarations
  class MMapFileMapping;
  class MMapFileSection;

  /** file mapping class */
  class MMapFileMapping
  {
  public:

    /** open file mapping on file given by native platform path */
    MMapFileMapping(const char* path, fsize_t size, bool readonly,bool autoflush
, bool createNew)  // Martijn Schuemie for zero row ff
;

    /** destructor */
    ~MMapFileMapping();

    /** map section from file into memory */
    MMapFileSection* mapSection(foff_t offset, msize_t size, void* baseaddr=0);

    /** remap section to new offset and size */
    void             remapSection(MMapFileSection& section, foff_t offset, msize_t size, void* baseaddr=0);

    /** get file size */
    fsize_t   size() const { return _size; }

    /** get error status */
    Error getError() const { return _error; }

    /** get system page size */
    static msize_t getPageSize();

  private:
    int     _fd;
    fsize_t _size;
    Error   _error;
    bool    _readonly;
    bool    _autoflush;
    bool    _createNew;  // Martijn Schuemie for zero row ff
  };

  /** file that supports mapping of sections */
  class MMapFileSection
  {
  public:

    MMapFileSection(int fd, foff_t offset, msize_t size, void* addr, bool readonly, bool autoflush
, bool createNew  // Martijn Schuemie for zero row ff
);
    ~MMapFileSection();

    /** reset file section to offset offs and size s */
    void   reset(foff_t off, msize_t s, void* baseaddr=0);

    /** check if range at offset offs with length size is completely in section */
    inline bool checkRangeInSection(foff_t offs, msize_t size) const
    {
      return ( (_offset <= offs) && ( static_cast<foff_t>(offs+size) < _end ) );
    }

    /** check if byte at offset off is contained in section */
    inline bool  checkOffsetInSection(foff_t offs) const
    {
      return ( (_offset <= offs) && ( offs < _end ) );

    }

    /** obtain address pointer of offset offs */
    inline void*  getPointer(foff_t offset)
    {
      foff_t disp = offset - _offset;
      return (void*) ( ( (unsigned char*)_addr ) + disp );
    }

    /** flush (possibly syncronized) back data to persistent storage and unmap */
    void flush();

  private:
    int        _fd;
    bool       _readonly;
    bool       _autoflush;
    bool       _createNew;  // Martijn Schuemie for zero row ff
    foff_t     _offset;
    foff_t     _end;
    msize_t    _size;
    void*      _addr;
  };

}

#endif

