AC_INIT(ff,2.0,dadler@uni-goettingen.de)
AC_CONFIG_HEADERS([src/ac_config.h])
AC_CHECK_HEADERS([sys/vfs.h])
AC_CHECK_HEADERS([sys/mman.h])
AC_CHECK_HEADERS([sys/file.h])
AC_CHECK_HEADERS([sys/stat.h])
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([sys/param.h])
AC_CHECK_HEADERS([sys/mount.h], AC_CHECK_MEMBERS([struct statfs.f_iosize],,,[#include <sys/mount.h>]) )
AC_CHECK_HEADERS([sys/statfs.h], AC_CHECK_MEMBERS([struct statfs.f_iosize],,,[#include <sys/statfs.h>]) )
AC_CHECK_HEADERS([sys/statvfs.h])
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_SYS_LARGEFILE
AC_FUNC_FSEEKO
AC_CHECK_FUNCS( fseeko )
AC_OUTPUT()

