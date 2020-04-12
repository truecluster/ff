///////////////////////////////////////////////////////////////////////////////
//
// universal tool kit (utk)
// configuration header
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

#ifndef UTK_CONFIG_HPP
#define UTK_CONFIG_HPP

#include "utk_platform_macros.hpp"

#if !defined UTK__Flavour_Windows
# ifndef AC_CONFIG_H_INCLUDED
#  include "ac_config.h"
#  define AC_CONFIG_H_INCLUDED
# endif
#endif

#ifdef UTK__Flavour_Windows
#define UTK__USE_TIMER_WINDOWS_HIRES
#endif

#ifdef UTK__OS_Linux
#define UTK__USE_LARGE_FILE_SUPPORT
#endif

#endif // UTK_CONFIG_HPP

