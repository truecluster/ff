\name{ff}
\alias{ff}
\alias{ff_pointer}
\title{ ff classes for representing (large) atomic data }
\description{
  The ff package provides atomic data structures that are stored on disk but behave (almost) as if they were in RAM by
  mapping only a section (pagesize) into main memory (the effective main memory consumption per ff object).
  Several access optimization techniques such as Hyrid Index Preprocessing (\code{\link{as.hi}}, \code{\link{update.ff}}) and Virtualization (\code{\link[=Extract.ff]{virtual}}, \code{\link{vt}}, \code{\link{vw}}) are implemented to achieve good performance even with large datasets.
  In addition to the basic access functions, the ff package also provides compatibility functions that facilitate writing code for ff and ram objects (\code{\link[=clone.ff]{clone}}, \code{\link{as.ff}}, \code{\link{as.ram}}) and very basic support for operating on ff objects (\code{\link{ffapply}}).
  While the (possibly packed) raw data is stored on a flat file, meta
  informations about the atomic data structure such as its dimension,
  virtual storage mode (\code{\link{vmode}}), factor level encoding,
  internal length etc.. are stored as an ordinary R object (external
  pointer plus attributes) and can be saved in the workspace.
  The raw flat file data encoding is always in native machine format for
  optimal performance and provides several packing schemes for different
  data types such as logical, raw, integer and double (in an extended version
  support for more tighly packed virtual data types is supported).
  flatfile data files can be shared among ff objects in the same R process or
  even from different R processes due to Memory-Mapping, although the
  caching effects have not been tested extensively.
  \cr
  Please do read and understand the limitations and warnings in \code{\link{LimWarn}} before you do anything serious with package ff.
}
\usage{
ff( initdata  = NULL
, length      = NULL
, levels      = NULL
, ordered     = NULL
, dim         = NULL
, dimorder    = NULL
, bydim       = NULL
, symmetric   = FALSE
, fixdiag     = NULL
, names       = NULL
, dimnames    = NULL
, ramclass    = NULL
, ramattribs  = NULL
, vmode       = NULL
, update      = NULL
, pattern     = NULL
, filename    = NULL
, overwrite   = FALSE
, readonly    = FALSE
, pagesize    = NULL  # getOption("ffpagesize")
, caching     = NULL  # getOption("ffcaching")
, finalizer   = NULL
, finonexit   = NULL  # getOption("fffinonexit")
, FF_RETURN   = TRUE
, BATCHSIZE   = .Machine$integer.max
, BATCHBYTES  = getOption("ffbatchbytes")
, VERBOSE     = FALSE
)
}
\arguments{
  \item{initdata}{ scalar or vector of the \code{\link{.vimplemented}} \code{\link{vmode}}s, recycled if needed, default 0, see also \code{\link{as.vmode}} and \code{\link{vector.vmode}} }
  \item{length}{ optional vector \code{\link{length}} of the object (default: derive from 'initdata' or 'dim'), see \code{\link{length.ff}} }
  \item{levels}{ optional character vector of levels if (in this case initdata must be composed of these) (default: derive from initdata) }
  \item{ordered}{ indicate whether the levels are ordered (TRUE) or non-ordered factor (FALSE, default) }
  \item{dim}{ optional array \code{\link{dim}}, see \code{\link{dim.ff}} and \code{\link{array}} }
  \item{dimorder}{ physical layout (default seq_along(dim)), see \code{\link{dimorder}} and \code{\link{aperm}} }
  \item{bydim}{ dimorder by which to interpret the 'initdata', generalization of the 'byrow' paramter in \code{\link{matrix}} }
  \item{symmetric}{ extended feature: TRUE creates symmetric matrix (default FALSE) %, see \code{\link{symm}}, \code{\link{ff_symm}}, \code{\link{ff_dist}}
       }
  \item{fixdiag}{ extended feature: non-NULL scalar requires fixed diagonal for symmetric matrix (default NULL is free diagonal) }
  \item{names}{ NOT taken from initdata, see \code{\link{names}} }
  \item{dimnames}{ NOT taken from initdata, see \code{\link{dimnames}} }
  \item{ramclass}{ class attribute attached when moving all or parts of this ff into ram, see \code{\link{ramclass}} }
  \item{ramattribs}{ additional attributes attached when moving all or parts of this ff into ram, see \code{\link{ramattribs}} }
  \item{vmode}{ virtual storage mode (default: derive from 'initdata'), see \code{\link{vmode}} and \code{\link{as.vmode}} }
  \item{update}{ set to FALSE to avoid updating with 'initdata' (default TRUE) (used by \code{\link{ffdf}}) }
  \item{pattern}{ root pattern with or without path for automatic ff filename creation (default NULL translates to "ff"), see also argument 'filename' }
  \item{filename}{ ff \code{\link{filename}} with or without path (default tmpfile with 'pattern' prefix); without path the file is created in \code{getOption("fftempdir")}, with path '.' the file is created in \code{\link{getwd}}. Note that files created in \code{getOption("fftempdir")} have default finalizer "delete" while other files have default finalizer "close". See also arguments 'pattern' and 'finalizer' and \code{\link[=Extract.ff]{physical}} }
  \item{overwrite}{ set to TRUE to allow overwriting existing files (default FALSE) }
  \item{readonly}{ set to TRUE to forbid writing to existing files }
  \item{pagesize}{ pagesize in bytes for the memory mapping (default from \code{getOptions("ffpagesize")} initialized by \code{\link{getdefaultpagesize}}), see also \code{\link[=Extract.ff]{physical}} }
  \item{caching}{ caching scheme for the backend, currently 'mmnoflush' or 'mmeachflush' (flush mmpages at each swap, default from \code{getOptions("ffcaching")} initialized with 'mmeachflush'), see also \code{\link[=Extract.ff]{physical}} }
  \item{finalizer}{ name of finalizer function called when ff object is \code{\link{remove}d} (default: ff files created in \code{getOptions("fftempdir")} are considered temporary and have default finalizer \code{\link[=delete.ff]{delete}}, files created in other locations have default finalizer \code{\link[=close.ff]{close}}); available finalizer generics are "close", "delete" and "deleteIfOpen", available methods are \code{\link{close.ff}}, \code{\link{delete.ff}} and \code{\link{deleteIfOpen.ff}}, see also argument 'finonexit' and \code{\link{finalizer}} }
  \item{finonexit}{ logical scalar determining whether  and \code{\link{finalize}} is also called when R is closed via \code{\link{q}}, (default TRUE from \code{getOptions("fffinonexit")}) }
  \item{FF_RETURN}{ logical scalar or ff object to be used. The default TRUE creates a new ff file. FALSE returns a ram object. Handing over an ff object here uses this or stops if not \code{\link{ffsuitable}} }
  \item{BATCHSIZE}{ integer scalar limiting the number of elements to be processed in \code{\link{update.ff}} when length(initdata)>1, default from \code{.Machine$integer.max} }
  \item{BATCHBYTES}{ integer scalar limiting the number of bytes to be processed in \code{\link{update.ff}} when length(initdata)>1, default from \code{getOption("ffbatchbytes")}, see also \code{\link{.rambytes}} }
  \item{VERBOSE}{ set to TRUE for verbosing in \code{\link{update.ff}} when length(initdata)>1, default FALSE }
}
\details{
 The atomic data is stored in \code{\link{filename}} as a native encoded raw flat file on disk, OS specific limitations of the file system apply.
 The number of elements per ff object is limited to the integer indexing, i.e. \code{\link{.Machine}$integer.max}.
 Atomic objects created with \command{ff} are \code{\link{is.open}}, a C++ object is ready to access the file via memory-mapping.
 Currently the C++ backend provides two caching schemes: 'mmnoflush' let the OS decide when to flash memory mapped pages
 and 'mmeachflush' will flush memory mapped pages at each page swap per ff file.
 These minimal memory ressources can be released by \code{\link[=close.ff]{close}ing} or \code{\link[=delete.ff]{delete}ing} the ff file.
 ff objects can be \code{\link{save}d} and \code{\link{load}ed} across R sessions. If the ff file still exists in the same location,
 it will be \code{\link[=open.ff]{open}ed} automatically at the first attempt to access its data. If the ff object is \code{\link{remove}d},
 at the next garbage collection (see \code{\link{gc}}) the ff object's \code{\link{finalizer}} is invoked.
 Raw data files can be made accessible as an ff object by explicitly given the filename and vmode but no size information (length or dim).
 The ff object will open the file and handle the data with respect to the given vmode.
 The \code{\link[=close.ff]{close}} finalizer will close the ff file, the \code{\link[=delete.ff]{delete}} finalizer will delete the ff file.
 The default finalizer \code{\link{deleteIfOpen}} will delete open files and do nothing for closed files. If the default finalizer is used,
 two actions are needed to protect the ff file against deletion: create the file outside the standard 'fftempdir' and close the ff object before removing it or before quitting R.
 When R is exited through \code{\link{q}}, the finalizer will be invoked depending on the 'fffinonexit' option, furthermore the 'fftempdir' is \code{\link{unlink}ed}. \cr
}
\value{
  If (\code{!FF_RETURN}) then a ram object like those generated by \code{\link{vector}}, \code{\link{matrix}}, \code{\link{array}} but with attributes 'vmode', 'physical' and 'virtual' accessible via \code{\link{vmode}}, \code{\link[=Extract.ff]{physical}} and \code{\link[=Extract.ff]{virtual}}  \cr
  If (\code{FF_RETURN}) an object of class 'ff' which is a a list with two components:
  \item{physical}{an external pointer of class '\code{ff_pointer}' which carries attributes with copy by reference semantics: changing a physical attribute of a copy changes the original }
  \item{virtual}{an empty list which carries attributes with copy by value semantics: changing a virtual attribute of a copy does not change the original }
}
\section{Physical object component}{
  The '\code{ff_pointer}' carries the following 'physical' or readonly attributes, which are accessible via \code{\link[=Extract.ff]{physical}}:
 \tabular{rl}{
  \code{vmode    } \tab see \code{\link{vmode}} \cr
  \code{maxlength} \tab see \code{\link{maxlength}} \cr
  \code{pattern  } \tab see parameter 'pattern' \cr
  \code{filename } \tab see \code{\link{filename}} \cr
  \code{pagesize } \tab see parameter 'pagesize' \cr
  \code{caching  } \tab see parameter 'caching' \cr
  \code{finalizer} \tab see parameter 'finalizer' \cr
  \code{finonexit} \tab see parameter 'finonexit' \cr
  \code{readonly } \tab see \code{\link{is.readonly}} \cr
  \code{class    } \tab The external pointer needs class 'ff_pointer' to allow method dispatch of finalizers  \cr
 }
}
\section{Virtual object component}{
  The 'virtual' component carries the following attributes (some of which might be NULL):
 \tabular{rl}{
  \code{Length    } \tab see \code{\link{length.ff}} \cr
  \code{Levels    } \tab see \code{\link{levels.ff}} \cr
  \code{Names     } \tab see \code{\link{names.ff}} \cr
  \code{VW        } \tab see \code{\link{vw.ff}} \cr
  \code{Dim       } \tab see \code{\link{dim.ff}} \cr
  \code{Dimorder  } \tab see \code{\link{dimorder}} \cr
  \code{Symmetric } \tab see \code{\link{symmetric.ff}} \cr
  \code{Fixdiag   } \tab see \code{\link{fixdiag.ff}} \cr
  \code{ramclass  } \tab see \code{\link{ramclass}} \cr
  \code{ramattribs} \tab see \code{\link{ramattribs}} \cr
 }
}
\section{Class}{
  You should not rely on the internal structure of ff objects or their ram versions. Instead use the accessor functions like \code{\link{vmode}}, \code{\link[=Extract.ff]{physical}} and \code{\link[=Extract.ff]{virtual}}.
  Still it would be wise to avoid attributes AND classes 'vmode', 'physical' and 'virtual' in any other packages.
  Note that the 'ff' object's class attribute also has copy-by-value semantics ('virtual').
  For the 'ff' object the following class attritibutes are known:
 \tabular{rl}{
  vector \tab \code{c("ff_vector","ff")} \cr
  matrix \tab \code{c("ff_matrix","ff_array","ff")} \cr
  array \tab \code{c("ff_array","ff")} \cr
  symmetric matrix \tab \code{c("ff_symm","ff")} \cr
  distance matrix \tab \code{c("ff_dist","ff_symm","ff")} \cr
  reserved for future use \tab \code{c("ff_mixed","ff")} \cr
 }
}
\section{Methods}{
 The following methods and functions are available for ff objects:
 \tabular{lrll}{
  \emph{ Type} \tab  \emph{ Name }  \tab \emph{ Assign }  \tab \emph{Comment}  \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Basic functions}  \cr
  function \tab  \code{\link{ff}}                         \tab \emph{ }  \tab constructor for ff and ram objects \cr
  generic  \tab  \code{\link[=update.ff]{update}}       \tab \emph{ }  \tab updates one ff object with the content of another \cr
  generic  \tab  \code{\link[=clone.ff]{clone}}                      \tab \emph{ }  \tab clones an ff object optionally changing some of its features \cr
  method   \tab  \code{\link[=print.ff]{print}}         \tab \emph{ }  \tab print ff \cr
  method   \tab  \code{\link[=str.ff]{str}}             \tab \emph{ }  \tab ff object structure \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Class test and coercion}  \cr
  function \tab  \code{\link{is.ff}}                      \tab \emph{ }  \tab check if inherits from ff \cr
  generic  \tab  \code{\link{as.ff}}                      \tab \emph{ }  \tab coerce to ff, if not yet \cr
  generic  \tab  \code{\link{as.ram}}                     \tab \emph{ }  \tab coerce to ram retaining some of the ff information \cr
  generic  \tab  \code{\link[=as.bit.ff]{as.bit}}          \tab \emph{ }  \tab coerce to \code{\link[bit]{bit}} \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Virtual storage mode} \cr
  generic  \tab  \code{\link{vmode}}                      \tab \code{<-} \tab get and set virtual mode (setting only for ram, not for ff objects) \cr
  generic  \tab  \code{\link{as.vmode}}                   \tab \emph{ }  \tab coerce to vmode (only for ram, not for ff objects) \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Physical attributes}  \cr
  function \tab  \code{\link[=Extract.ff]{physical}}                   \tab \code{<-} \tab set and get physical attributes \cr
  generic  \tab  \code{\link{filename}}                   \tab \emph{<-}  \tab get and set filename \cr
  generic  \tab  \code{\link{pattern}}                    \tab \emph{<-}  \tab get pattern and set filename path and prefix via pattern \cr
  generic  \tab  \code{\link{maxlength}}                  \tab \emph{ }  \tab get maxlength \cr
  generic  \tab  \code{\link[bit:Metadata]{is.sorted}}                  \tab \code{<-} \tab set and get if is marked as sorted \cr
  generic  \tab  \code{\link[bit]{na.count}}                   \tab \code{<-} \tab set and get NA count, if set to non-NA only swap methods can change and na.count is maintained automatically \cr
  generic  \tab  \code{\link{is.readonly}}                \tab \emph{ }   \tab get if is readonly \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }   \tab \bold{Virtual attributes} \cr
  function \tab  \code{\link[=Extract.ff]{virtual}}                    \tab \code{<-} \tab set and get virtual attributes \cr
  method   \tab  \code{\link[=length.ff]{length}}       \tab \code{<-} \tab set and get length \cr
  method   \tab  \code{\link[=dim.ff]{dim}}             \tab \code{<-} \tab set and get dim \cr
  generic  \tab  \code{\link{dimorder}}                   \tab \code{<-} \tab set and get the order of dimension interpretation \cr
  generic  \tab  \code{\link{vt}}                         \tab \code{}   \tab virtually transpose ff_array \cr
  method  \tab   \code{\link[=t.ff]{t}}                 \tab \code{}   \tab create transposed clone of ff_array \cr
  generic  \tab  \code{\link{vw}}                         \tab \code{<-} \tab set and get virtual windows \cr
  method   \tab  \code{\link[=names.ff]{names}}         \tab \code{<-} \tab set and get names \cr
  method   \tab  \code{\link[=dimnames.ff]{dimnames}}   \tab \code{<-} \tab set and get dimnames \cr
  generic  \tab  \code{\link{symmetric}}                  \tab \emph{ }   \tab get if is symmetric \cr
  generic  \tab  \code{\link{fixdiag}}                    \tab \code{<-} \tab set and get fixed diagonal of symmetric matrix \cr
  method   \tab  \code{\link{levels}}                     \tab \code{<-} \tab levels of factor  \cr
  generic  \tab  \code{\link{recodeLevels}}               \tab \code{ }  \tab recode a factor to different levels \cr
  generic  \tab  \code{\link{sortLevels}}                 \tab \code{ }  \tab sort the levels and recoce a factor \cr
  method   \tab  \code{\link{is.factor}}                  \tab \emph{ }  \tab if is factor \cr
  method   \tab  \code{\link{is.ordered}}                 \tab \emph{ }  \tab if is ordered (factor) \cr
  generic  \tab  \code{\link{ramclass}}                   \tab \code{}   \tab get ramclass \cr
  generic  \tab  \code{\link{ramattribs}}                 \tab \code{}   \tab get ramattribs \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Access functions}  \cr
  function \tab  \code{\link{get.ff}}                     \tab \emph{ }  \tab get single ff element (currently \code{\link[=Extract.ff]{[[}} is a shortcut) \cr
  function \tab  \code{\link{set.ff}}                     \tab \emph{ }  \tab set single ff element (currently \code{\link[=Extract.ff]{[[<-}} is a shortcut) \cr
  function \tab  \code{\link{getset.ff}}                  \tab \emph{ }  \tab set single ff element and get old value in one access operation \cr
  function \tab  \code{\link{read.ff}}                    \tab \emph{ }  \tab get vector of contiguous elements \cr
  function \tab  \code{\link{write.ff}}                   \tab \emph{ }  \tab set vector of contiguous elements  \cr
  function \tab  \code{\link{readwrite.ff}}               \tab \emph{ }  \tab set vector of contiguous elements and get old values in one access operation \cr
  method   \tab  \code{\link[=Extract.ff]{[}}                 \tab \emph{ }  \tab get vector of indexed elements, uses HIP, see \code{\link{hi}} \cr
  method   \tab  \code{\link[=Extract.ff]{[<-}}             \tab \emph{ }  \tab set vector of indexed elements, uses HIP, see \code{\link{hi}} \cr
  generic  \tab  \code{\link[=swap.ff]{swap}}           \tab \emph{ }  \tab set vector of indexed elements and get old values in one access operation \cr
  generic  \tab  \code{\link[=add.ff]{add}}             \tab \emph{ }  \tab (almost) unifies '+=' operation for ff and ram objects \cr
  generic  \tab  \code{\link[=bigsample.ff]{bigsample}} \tab \emph{ }  \tab sample from ff object \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Opening/Closing/Deleting}                                             \cr
  generic  \tab  \code{\link{is.open}}                    \tab \emph{ }  \tab check if ff is open \cr
  method   \tab  \code{\link[=open.ff]{open}}           \tab \emph{ }  \tab open ff object (is done automatically on access) \cr
  method   \tab  \code{\link[=close.ff]{close}}         \tab \emph{ }  \tab close ff object (releases C++ memory and protects against file deletion if  \code{\link{deleteIfOpen}}) finalizer is used \cr
  generic  \tab  \code{\link[=delete.ff]{delete}}       \tab \emph{ }  \tab deletes ff file (unconditionally) \cr
  generic  \tab  \code{\link{deleteIfOpen}}               \tab \emph{ }  \tab deletes ff file if ff object is open (finalization method) \cr
  generic  \tab  \code{\link{finalizer}}                  \tab \emph{<-} \tab get and set finalizer \cr
  generic  \tab  \code{\link{finalize}}                   \tab \emph{}   \tab force finalization \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Other}                                                     \cr
  function \tab  \code{\link{geterror.ff}}                \tab \emph{ }  \tab get error code \cr
  function \tab  \code{\link{geterrstr.ff}}               \tab \emph{ }  \tab get error message \cr
  }
}
\section{ff options}{
  Through \code{\link{options}} or \code{\link{getOption}} one can change and query global features of the ff package:
 \tabular{rll}{
  \emph{option}        \tab \emph{description}                           \tab \emph{default} \cr
  \code{fftempdir}     \tab default directory for creating ff files      \tab \code{\link{tempdir}} \cr
  \code{fffinalizer}   \tab name of default finalizer                    \tab \code{\link{deleteIfOpen}} \cr
  \code{fffinonexit}   \tab default for invoking finalizer on exit of R  \tab \code{TRUE} \cr
  \code{ffpagesize}    \tab default pagesize                             \tab \code{\link{getdefaultpagesize}} \cr
  \code{ffcaching}     \tab caching scheme for the C++ backend           \tab \code{'mmnoflush'} \cr
  \code{ffdrop}        \tab default for the \option{drop} parameter in the ff subscript methods  \tab TRUE \cr
  \code{ffbatchbytes}  \tab default for the byte limit in batched/chunked processing             \tab 16MB \cr
 }
}
\section{OS specific}{
 The following table gives an overview of file size limits for common file systems (see \url{https://en.wikipedia.org/wiki/Comparison_of_file_systems} for further details):
 \tabular{ll}{
  \strong{File System} \tab \strong{File size limit} \cr
  FAT16              \tab 2GB \cr
  FAT32              \tab 4GB \cr
  NTFS               \tab 16GB \cr
  ext2/3/4           \tab 16GB to 2TB \cr
  ReiserFS           \tab 4GB (up to version 3.4) / 8TB (from version 3.5) \cr
  XFS                \tab 8EB \cr
  JFS                \tab 4PB \cr
  HFS                \tab 2GB \cr
  HFS Plus           \tab 16GB \cr
  USF1               \tab 4GB to 256TB \cr
  USF2               \tab 512GB to 32PB \cr
  UDF                \tab 16EB \cr
  }
}
\section{Credits}{
 Package Version 1.0
 \tabular{ll}{
  Daniel Adler       \tab \email{dadler@uni-goettingen.de} \cr
                     \tab R package design, C++ generic file vectors, Memory-Mapping, 64-bit Multi-Indexing adapter and Documentation, Platform ports \cr
  Oleg Nenadic       \tab \email{onenadi@uni-goettingen.de} \cr
                     \tab Index sequence packing, Documentation \cr
  Walter Zucchini    \tab \email{wzucchi@uni-goettingen.de} \cr
                     \tab Array Indexing, Sampling, Documentation \cr
  Christian Gläser   \tab 	\email{christian_glaeser@gmx.de} \cr
                     \tab Wrapper for biglm package \cr
  }
 Package Version 2.0
 \tabular{ll}{
  Jens Oehlschlägel  \tab \email{Jens.Oehlschlaegel@truecluster.com} \cr
                     \tab R package redesign; Hybrid Index Preprocessing; transparent object creation and finalization; vmode design; virtualization and hybrid copying; arrays with dimorder and bydim; symmetric matrices; factors and POSIXct; virtual windows and transpose; new generics update, clone, swap, add, as.ff and as.ram; ffapply and collapsing functions. R-coding, C-coding and Rd-documentation. \cr
  Daniel Adler       \tab \email{dadler@uni-goettingen.de} \cr
                     \tab C++ generic file vectors, vmode implementation and low-level bit-packing/unpacking, arithmetic operations and NA handling, Memory-Mapping and backend caching. C++ coding and platform ports. R-code extensions for opening existing flat files readonly and shared. \cr
  }
}
\note{ Note that the standard finalizers are generic functions, their dispatch to the '\code{ff_pointer}' method happens at finalization time, their 'ff' methods exist for direct calling.
}
\section{Licence}{Package under GPL-2, included C++ code released by Daniel Adler under the less restrictive ISCL}
\seealso{ \code{\link{vector}}, \code{\link{matrix}}, \code{\link{array}}, \code{\link{as.ff}}, \code{\link{as.ram}} }
\examples{
  message("make sure you understand the following ff options 
    before you start using the ff package!!")
  oldoptions <- options(fffinalizer="deleteIfOpen", fffinonexit="TRUE", fftempdir=tempdir())
  message("an integer vector")
  ff(1:12)                  
  message("a double vector of length 12")
  ff(0, 12)
  message("a 2-bit logical vector of length 12 (vmode='boolean' has 1 bit)")
  ff(vmode="logical", length=12)
  message("an integer matrix 3x4 (standard colwise physical layout)")
  ff(1:12, dim=c(3,4))
  message("an integer matrix 3x4 (rowwise physical layout, but filled in standard colwise order)")
  ff(1:12, dim=c(3,4), dimorder=c(2,1))
  message("an integer matrix 3x4 (standard colwise physical layout, but filled in rowwise order
aka matrix(, byrow=TRUE))")
  ff(1:12, dim=c(3,4), bydim=c(2,1))
  gc()
  options(oldoptions)

  if (ffxtensions()){
     message("a 26-dimensional boolean array using 1-bit representation
      (file size 8 MB compared to 256 MB int in ram)")
     a <- ff(vmode="boolean", dim=rep(2, 26))
     dimnames(a) <- dummy.dimnames(a)
     rm(a); gc()
  }

  \dontrun{

     message("This 2GB biglm example can take long, you might want to change
       the size in order to define a size appropriate for your computer")
     require(biglm)

     b <- 1000
     n <- 100000
     k <- 3
     memory.size(max = TRUE)
     system.time(
     x <- ff(vmode="double", dim=c(b*n,k), dimnames=list(NULL, LETTERS[1:k]))
     )
     memory.size(max = TRUE)
     system.time(
     ffrowapply({
        l <- i2 - i1 + 1
        z <- rnorm(l)
        x[i1:i2,] <- z + matrix(rnorm(l*k), l, k)
     }, X=x, VERBOSE=TRUE, BATCHSIZE=n)
     )
     memory.size(max = TRUE)

     form <- A ~ B + C
     first <- TRUE
     system.time(
     ffrowapply({
        if (first){
          first <- FALSE
          fit <- biglm(form, as.data.frame(x[i1:i2,,drop=FALSE], stringsAsFactors = TRUE))
        }else
          fit <- update(fit, as.data.frame(x[i1:i2,,drop=FALSE], stringsAsFactors = TRUE))
     }, X=x, VERBOSE=TRUE, BATCHSIZE=n)
     )
     memory.size(max = TRUE)
     first
     fit
     summary(fit)
     rm(x); gc()
  }
}
\keyword{ IO }
\keyword{ array }
\keyword{ attribute }
\keyword{ classes }
\keyword{ package }
