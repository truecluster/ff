# Array utilities for ff
# (c) 2007 Jens Oehlschägel
# Licence: GPL2
# Provided 'as is', use at your own risk
# Created: 2007-08-24
# Last changed: 2007-10-25

# source("d:/mwp/eanalysis/ff/R/zzz.R")

# require(rhub)
# rhub_ff_4.0.3 <- check_for_cran(
#   path = "../ff_4.0.3.tar.gz"
# , email = "Jens.Oehlschlaegel@truecluster.com"
# , check_args = "--as-cran"
# , env_vars = c('_R_CHECK_FORCE_SUGGESTS_'= "false",'_R_CHECK_CRAN_INCOMING_USE_ASPELL_'= "true", '_R_CHECK_XREFS_MIND_SUSPECT_ANCHORS_'="true")
# , platform = c('macos-highsierra-release-cran','macos-highsierra-release')
# , show_status = FALSE
# )

# > require(rhub)
# > rhub_setup()
# > rhub_doctor()
# > rhub_check(platforms = c("linux", "macos", "windows", "ubuntu-clang", "ubuntu-gcc12"))
# ✔ Found git repository at /home/jo/SIK/truecluster/ff.
# ✔ Found GitHub PAT.                                 
# 
# ✔ Check started: linux, macos, windows, ubuntu-clang, ubuntu-gcc12 (brown-foxhound).
# See <https://github.com/truecluster/ff/actions> for live output!


.onLoad <- function(lib, pkg) {
  ##library.dynam("ff", pkg, lib) use useDynLib(ff, .registration = TRUE, .fixes = "C_") in NAMESPACE instead
  ##packageStartupMessage("Loading package ff", packageDescription("ff", lib, fields="Version"), "")
  
  # allow fftempdir to be set before package is loaded
  # and make tempdir name independent of platform (otherwise dirname(tempfile)!=getOption("fftempdir"))
  fftempdir <- getOption("fftempdir")
  if (is.null(fftempdir) || !dir.exists(dirname(fftempdir))){
    fftempdir <- standardPathFile(file.path(tempdir(), "ff"))
  }else{
    fftempdir <- standardPathFile(fftempdir)
  }
  fftempexists <- dir.exists(fftempdir)
  if (!fftempexists){
    dir.create(fftempdir)
  }
  options(fftempdir=fftempdir, fftempkeep=fftempexists)
  
  if (is.null(getOption("ffextension")))
    options(ffextension="ff")
  if (is.null(getOption("fffinonexit")))
    options(fffinonexit=TRUE)
  if (is.null(getOption("ffpagesize")))
    options(ffpagesize=getdefaultpagesize())
  if (is.null(getOption("ffcaching")))
    options(ffcaching="mmnoflush")
  if (is.null(getOption("ffdrop")))
    options(ffdrop=TRUE)
  if (is.null(getOption("ffbatchbytes"))){
    # some magic constant
    options(ffbatchbytes=16*1024^2)
  }
  if (is.null(getOption("ffmaxbytes"))){
    # some magic constant
    options(ffmaxbytes=0.5*1024^3)
  }
  # if we want an explicit list of ff objects, we should store them in an environment with hash=TRUE (much faster than a list)
  #assign(".fftemp", new.env(hash=TRUE), envir=globalenv())

  # assign(".vimplemented"
  # , c(
      # boolean   = .Call(C_ffmode_implemented, .ffmode["boolean"]  , PACKAGE="ff")
    # , logical   = .Call(C_ffmode_implemented, .ffmode["logical"]  , PACKAGE="ff")
    # , quad      = .Call(C_ffmode_implemented, .ffmode["quad"]     , PACKAGE="ff")
    # , nibble    = .Call(C_ffmode_implemented, .ffmode["nibble"]   , PACKAGE="ff")
    # , byte      = .Call(C_ffmode_implemented, .ffmode["byte"]     , PACKAGE="ff")
    # , ubyte     = .Call(C_ffmode_implemented, .ffmode["ubyte"]    , PACKAGE="ff")
    # , short     = .Call(C_ffmode_implemented, .ffmode["short"]    , PACKAGE="ff")
    # , ushort    = .Call(C_ffmode_implemented, .ffmode["ushort"]   , PACKAGE="ff")
    # , integer   = .Call(C_ffmode_implemented, .ffmode["integer"]  , PACKAGE="ff")
    # , single    = .Call(C_ffmode_implemented, .ffmode["single"]   , PACKAGE="ff")
    # , double    = .Call(C_ffmode_implemented, .ffmode["double"]   , PACKAGE="ff")
    # , complex   = .Call(C_ffmode_implemented, .ffmode["complex"]  , PACKAGE="ff")
    # , raw       = .Call(C_ffmode_implemented, .ffmode["raw"]      , PACKAGE="ff")
    # , character = .Call(C_ffmode_implemented, .ffmode["character"], PACKAGE="ff")
    # ), envir=globalenv()
  # )

  # list of possible coercions without information loss
  # assign(".vcoerceable"
  # , lapply(
      # list(
        # boolean   = 1:13
      # , logical   = c(2L, 5L, 7L, 9:12)
      # , quad      = 3:13
      # , nibble    = 4:13
      # , byte      = c(5L, 7L, 9:12)
      # , ubyte     = 6:13
      # , short     = c(7L, 9:12)
      # , ushort    = 8:12
      # , integer   = 9:12
      # , single    = 10:12
      # , double    = 11:12
      # , complex   = 12L
      # , raw       = 6:12
      # , character = 14L
      # )
      # , function(i)i[.vimplemented[i]]
    # )
    # , envir=globalenv()
  # )
	
  .vimplemented <<- c(
		boolean   = .Call(C_ffmode_implemented, .ffmode["boolean"]  , PACKAGE="ff")
	, logical   = .Call(C_ffmode_implemented, .ffmode["logical"]  , PACKAGE="ff")
	, quad      = .Call(C_ffmode_implemented, .ffmode["quad"]     , PACKAGE="ff")
	, nibble    = .Call(C_ffmode_implemented, .ffmode["nibble"]   , PACKAGE="ff")
	, byte      = .Call(C_ffmode_implemented, .ffmode["byte"]     , PACKAGE="ff")
	, ubyte     = .Call(C_ffmode_implemented, .ffmode["ubyte"]    , PACKAGE="ff")
	, short     = .Call(C_ffmode_implemented, .ffmode["short"]    , PACKAGE="ff")
	, ushort    = .Call(C_ffmode_implemented, .ffmode["ushort"]   , PACKAGE="ff")
	, integer   = .Call(C_ffmode_implemented, .ffmode["integer"]  , PACKAGE="ff")
	, single    = .Call(C_ffmode_implemented, .ffmode["single"]   , PACKAGE="ff")
	, double    = .Call(C_ffmode_implemented, .ffmode["double"]   , PACKAGE="ff")
	, complex   = .Call(C_ffmode_implemented, .ffmode["complex"]  , PACKAGE="ff")
	, raw       = .Call(C_ffmode_implemented, .ffmode["raw"]      , PACKAGE="ff")
	, character = .Call(C_ffmode_implemented, .ffmode["character"], PACKAGE="ff")
	)
	
  # list of possible coercions without information loss
  .vcoerceable <<- lapply(
      list(
        boolean   = 1:13
      , logical   = c(2L, 5L, 7L, 9:12)
      , quad      = 3:13
      , nibble    = 4:13
      , byte      = c(5L, 7L, 9:12)
      , ubyte     = 6:13
      , short     = c(7L, 9:12)
      , ushort    = 8:12
      , integer   = 9:12
      , single    = 10:12
      , double    = 11:12
      , complex   = 12L
      , raw       = 6:12
      , character = 14L
      )
      , function(i)i[.vimplemented[i]]
    )
	
}

.onAttach <- function(libname, pkgname){
  packageStartupMessage("Attaching package ff")
  packageStartupMessage('- getOption("fftempdir")=="',getOption("fftempdir"),'"\n',sep='')
  packageStartupMessage('- getOption("ffextension")=="',getOption("ffextension"),'"\n',sep='')
  packageStartupMessage('- getOption("ffdrop")==',getOption("ffdrop"),'\n',sep='')
  packageStartupMessage('- getOption("fffinonexit")==',getOption("fffinonexit"),'\n',sep='')
  packageStartupMessage('- getOption("ffpagesize")==',getOption("ffpagesize"),'\n',sep='')
  packageStartupMessage('- getOption("ffcaching")=="',getOption("ffcaching"),'"  -- consider "ffeachflush" if your system stalls on large writes\n',sep='')
  packageStartupMessage('- getOption("ffbatchbytes")==',getOption("ffbatchbytes"),' -- consider a different value for tuning your system\n',sep='')
  packageStartupMessage('- getOption("ffmaxbytes")==',getOption("ffmaxbytes"),' -- consider a different value for tuning your system\n',sep='')
  # if (getRversion()<="2.10.0"){
    # packageStartupMessage('fixing [.AsIs in base namespace because if the NextMethod("[") returns a different class, [.AsIs was reverting this')
    #assignInNamespace(
    #  "[.AsIs"
    #, function (x, i, ...){
    #    ret <- NextMethod("[")
    #    oldClass(ret) <- c("AsIs", oldClass(ret))
    #    ret
    #  }
    #, "base"
    #)
    # assignInNamespace(
      # "[.AsIs"
    # , function (x, i, ...)I(NextMethod("["))
    # , "base"
    # )
  # }
}

.onDetach <- function(libpath) {
   packageStartupMessage("Detaching package ff")
  # if (getRversion()<="2.10.0"){
    # packageStartupMessage('restoring [.AsIs')
    # assignInNamespace(
      # "[.AsIs"
    # , function (x, i, ...){
        # ret <- NextMethod("[")
        # oldClass(ret) <- c("AsIs", oldClass(x))
        # ret
      # }
    # , "base"
    # )
  # }
}

.onUnload <- function(libpath){
   packageStartupMessage("Unloading package ff")
   #remove(list=".fftemp", envir=globalenv())
   #gc()
   fftempdir <- getOption("fftempdir")
   fftempkeep <- getOption("fftempkeep", default = FALSE)
   library.dynam.unload("ff", libpath)
   if (!fftempkeep && unlink(fftempdir, recursive = TRUE)){
     packageStartupMessage("Error in unlinking fftempdir")
   }else{
     if (fftempdir == standardPathFile(file.path(tempdir(), "ff")))
       fftempdir <- NULL
     options(
       fftempdir=fftempdir
     , fftempkeep=NULL
     , ffextension=NULL
     , fffinonexit=NULL
     , ffpagesize=NULL
     , ffcaching=NULL
     , ffdrop=NULL
     , ffbatchbytes=NULL
     , ffmaxbytes=NULL
     )
   }
}
