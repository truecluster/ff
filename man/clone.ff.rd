\name{clone.ff}
\alias{clone.ff}
\title{ Cloning ff and ram objects }
\description{
  \command{clone} physically duplicates ff (and ram) objects and can additionally change some features, e.g. length.
}
\usage{
\method{clone}{ff}(x
, initdata = x
, length = NULL
, levels = NULL
, ordered = NULL
, dim = NULL
, dimorder = NULL
, bydim = NULL
, symmetric = NULL
, fixdiag = NULL
, names = NULL
, dimnames = NULL
, ramclass = NULL
, ramattribs = NULL
, vmode = NULL
, update  = NULL
, pattern = NULL
, filename = NULL
, overwrite = FALSE
, pagesize = NULL
, caching = NULL
, finalizer = NULL
, finonexit = NULL
, FF_RETURN = NULL
, BATCHSIZE = .Machine$integer.max
, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE
, \dots)
}
\arguments{
  \item{x}{ \code{x} }
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
  \item{names}{ see \code{\link{names}} }
  \item{dimnames}{ NOT taken from initdata, see \code{\link{dimnames}} }
  \item{ramclass}{ class attribute attached when moving all or parts of this ff into ram, see \code{\link{ramclass}} }
  \item{ramattribs}{ additional attributes attached when moving all or parts of this ff into ram, see \code{\link{ramattribs}} }
  \item{vmode}{ virtual storage mode (default: derive from 'initdata'), see \code{\link{vmode}} and \code{\link{as.vmode}} }
  \item{update}{ set to FALSE to avoid updating with 'initdata' (default TRUE) (used by \code{\link{ffdf}}) }
  \item{pattern}{ root pattern for automatic ff filename creation (default "ff"), see also \code{\link[=Extract.ff]{physical}} }
  \item{filename}{ ff \code{\link{filename}} (default tmpfile with 'pattern' prefix), see also \code{\link[=Extract.ff]{physical}} }
  \item{overwrite}{ set to TRUE to allow overwriting existing files (default FALSE) }
  \item{pagesize}{ pagesize in bytes for the memory mapping (default from getOptions("ffpagesize") initialized by \code{\link{getdefaultpagesize}}), see also \code{\link[=Extract.ff]{physical}} }
  \item{caching}{ caching scheme for the backend, currently 'mmnoflush' or 'mmeachflush' (flush mmpages at each swap, default from getOptions("ffcaching") initialized with 'memorymap'), see also \code{\link[=Extract.ff]{physical}} }
  \item{finalizer}{ name of finalizer function called when ff object is \code{\link{remove}d}, (default "deleteIfOpen" from getOptions("fffinalizer"))), standard finalizers are \code{\link{close.ff}}, \code{\link{delete.ff}} and \code{\link{deleteIfOpen.ff}}, see also \code{\link{reg.finalizer}} }
  \item{finonexit}{ logical scalar determining whether finalizer is also called when R is closed via \code{\link{q}}, (default TRUE from getOptions("fffinonexit")) }
  \item{FF_RETURN}{ logical scalar or ff object to be used. The default NULL creates a ff or ram clone, TRUE returns a ff clone, FALSE returns a ram clone. Handing over an ff object here uses this or stops if not \code{\link{ffsuitable}} }
  \item{BATCHSIZE}{ integer scalar limiting the number of elements to be processed in \code{\link{update.ff}} when length(initdata)>1, default from getOption("ffbatchsize") }
  \item{BATCHBYTES}{ integer scalar limiting the number of bytes to be processed in \code{\link{update.ff}} when length(initdata)>1, default from getOption("ffbatchbytes"), see also \code{\link{.rambytes}} }
  \item{VERBOSE}{ set to TRUE for verbosing in \code{\link{update.ff}} when length(initdata)>1, default FALSE }
  \item{\dots}{ further arguments to the generic }
}
\details{
  \command{clone} is generic. \command{clone.ff} is the workhorse behind \code{\link{as.ram}} and \code{\link{as.ff}}.
  For creating the desired object it calls \code{\link{ff}} which calls \code{\link{update}} for initialization.
}
\value{
  an ff or ram object
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ff}}, \code{\link{update}}, \code{\link{as.ram}}, \code{\link{as.ff}} }
\examples{
  x <- ff(letters, levels=letters)
  y <- clone(x, length=52)
  rm(x,y); gc()
}
\keyword{ IO }
\keyword{ data }
