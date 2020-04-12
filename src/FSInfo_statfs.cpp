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

#include "config.h"
#ifdef FF_USE_STATFS

#include "FSInfo.hpp"

#ifdef HAVE_SYS_VFS_H
#include <sys/vfs.h>
#endif
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#ifdef HAVE_SYS_MOUNT_H
#include <sys/mount.h>
#endif
#ifdef HAVE_SYS_STATFS_H
#include <sys/statfs.h>
#endif
#ifdef HAVE_SYS_STATVFS_H
#include <sys/statvfs.h>
#endif

namespace ff {

void getFSInfo(const char* path, FSInfo& info)
{

//D.A. #if defined(__sun__)
//J.O. 16.9.2010
#if defined(__sun__) || defined(__sun) || defined(sun) || defined(__NetBSD__)
  struct statvfs sfs;
  statvfs(path, &sfs);
#else
  struct statfs sfs;
  statfs(path, &sfs);
#endif
  info.free_space = ((fsize_t)sfs.f_bsize) * ((fsize_t)sfs.f_bavail );
  info.block_size = sfs.f_bsize;
#ifdef HAVE_STRUCT_STATFS_F_IOSIZE
  info.optimal_size = sfs.f_iosize;
#else
  info.optimal_size = info.block_size;
#endif
}

}

#endif

