AC_INIT(ff,2.0,dadler@uni-goettingen.de)
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi
CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
CXX=`"${R_HOME}/bin/R" CMD config CXX`
if test -z "$CXX"; then
  AC_MSG_ERROR([No C++ compiler is available])
fi
CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXXFLAGS`
AC_LANG(C++)
AC_PROG_CC([cc cl gcc])
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

