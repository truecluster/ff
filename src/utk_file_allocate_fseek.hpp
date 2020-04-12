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

#ifndef UTK_FILE_ALLOCATE_FSEEK_HPP
#define UTK_FILE_ALLOCATE_FSEEK_HPP

#include "utk_config.hpp"
// D.A. #include <cstdio>
//{ J.O. 16.9.2010 interpreting B.R.
#if defined(__sun__) || defined(__sun) || defined(sun)
#include <stdio.h>
#else
#include <cstdio>
#endif
//} J.O. 16.9.2010
#include <stdint.h>

namespace utk
{
  typedef uint64_t fsize_t;
  int file_allocate_fseek(const char* path, fsize_t size);
}

#endif // UTK_FILE_ALLOCATE_FSEEK_HPP

