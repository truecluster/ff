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

#include "Error.hpp"

namespace ff {

  /* J.O.: changed from const char */
  const char* getErrorString(Error error)
  {
    switch(error) {
    case E_NO_ERROR:          return "no error";
    case E_INVALID:           return "invalid";
    case E_NO_DISKSPACE:      return "no diskspace";
    case E_UNABLE_TO_OPEN:    return "unable to open";
    case E_NOT_EXISTING:      return "not existing";
    case E_WRITE_ERROR:       return "write error";
    case E_FILE_IS_READONLY:  return "file is read-only";
    default:                  return "unknown error";
    }
  }

}

