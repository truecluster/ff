\name{as.ff}
\alias{as.ff}
\alias{as.ff.default}
\alias{as.ff.ff}
\alias{as.ram}
\alias{as.ram.default}
\alias{as.ram.ff}
\title{ Coercing ram to ff and ff to ram objects }
\description{
   Coercing ram to ff and ff to ram objects while optionally modifying object features.
}
\usage{
  as.ff(x, ...)
  as.ram(x, ...)
  \method{as.ff}{default}(x, filename = NULL, overwrite = FALSE, ...)
  \method{as.ff}{ff}(x, filename = NULL, overwrite = FALSE, ...)
  \method{as.ram}{default}(x, ...)
  \method{as.ram}{ff}(x, ...)
}
\arguments{
  \item{x}{ any object to be coerced }
  \item{filename}{ path and filename }
  \item{overwrite}{ TRUE to overwrite the old filename }
  \item{\dots}{ \code{\dots} }
}
\details{
  If \command{as.ff.ff} is called on an 'ff' object or \command{as.ram.default} is called on a non-ff object AND no changes are required, the input object 'x' is returned unchanged.
  Otherwise the workhorse \code{\link{clone.ff}} is called.
  If no change of features are requested, the filename attached to the object remains unchanged, otherwise a new filename is requested (or can be set by the user).
}
\note{
   If you use \code{ram <- as.ram(ff)} for caching, please note that you must \command{\link{close.ff}} before you can write back \code{as.ff(ram, overwrite=TRUE)} (see examples).
}
\value{
  A ram or ff object.
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{as.ff.bit}}, \code{\link{ff}}, \code{\link[=clone.ff]{clone}} %, \code{\link{as.symm}}
         , \code{\link{as.vmode}}, \code{\link{vmode}}, \code{\link{as.hi}} }
\examples{
   message("create ff")
   myintff <- ff(1:12)
   message("coerce (=clone) integer ff to double ff")
   mydoubleff <- as.ff(myintff, vmode="double")
   message("cache (=clone) integer ff to integer ram AND close original ff")
   myintram <- as.ram(myintff) # filename is retained
   close(myintff)
   message("modify ram cache and write back (=clone) to ff")
   myintram[1] <- -1L
   myintff <- as.ff(myintram, overwrite=TRUE)
   message("coerce (=clone) integer ram to double ram")
   mydoubleram <- as.ram(myintram, vmode="double")
   message("coerce (inplace) integer ram to double ram")
   myintram <- as.ram(myintram, vmode="double")
   message("more classic: coerce (inplace) double ram to integer ram")
   vmode(myintram) <- "integer"
   rm(myintff, myintram, mydoubleff, mydoubleram); gc()
}
\keyword{ IO }
\keyword{ data }
