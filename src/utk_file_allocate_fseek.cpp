///////////////////////////////////////////////////////////////////////////////
//
// universal tool kit (utk)
// file allocation using fseeko (sparse files)
//
// Copyright (C) 2008 Daniel Adler <dadler@uni-goettingen.de>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#include "config.h"

#include "utk_file_allocate_fseek.hpp"

#ifdef __MINGW32__
#define fseeko fseeko64
#endif

#include <cerrno>

namespace utk
{
  int file_allocate_fseek(const char* path, fsize_t size)
  {
    // open new file for writing
    FILE* f = fopen(path,"w");
    if (!f) return errno;

    // return value
    int err;

    // seek to one-byte before end of file

    if (size == 0) {   // Martijn Schuemie for zero row ff
      err = fseeko(f, 0, SEEK_SET);   // Martijn Schuemie for zero row ff
    } else {
      err = fseeko(f, size-1, SEEK_SET);
      // write last byte
      if (!err)
      {
        unsigned char value = 0;
        unsigned int nwritten = fwrite(&value,1,1,f);
        if (nwritten != 1) err = 1;
      }
    }

    // close
    fclose(f);

    if (err) err = errno;

    return err;
  }
}

