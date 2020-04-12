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

#ifndef FF_FILE_MAPPING_HPP
#define FF_FILE_MAPPING_HPP

/** abstraction to memory-mapped files (os-specific) */

#include "config.h"

#ifdef FF_USE_WIN32

#include "Win32FileMapping.hpp"

namespace ff {
typedef Win32FileMapping FileMapping;
typedef Win32FileSection FileSection;
}

#endif // FF_USE_WIN32

#ifdef FF_USE_MMAP

#include "MMapFileMapping.hpp"

namespace ff {
typedef MMapFileMapping FileMapping;
typedef MMapFileSection FileSection;
}

#endif // FF_USE_MMAP

#endif // FF_FILE_MAPPING_HPP

