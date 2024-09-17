\name{getset.ff}
\alias{getset.ff}
\alias{get.ff}
\alias{set.ff}
\title{ Reading and writing vectors of values (low-level) }
\description{
  The three functions \command{get.ff}, \command{set.ff} and \command{getset.ff} provide the simplest interface to access an ff file: getting and setting vector of values identified by positive subscripts
}
\usage{
get.ff(x, i)
set.ff(x, i, value, add = FALSE)
getset.ff(x, i, value, add = FALSE)
}
\arguments{
  \item{x}{ an ff object }
  \item{i}{ an index position within the ff file }
  \item{value}{ the value to write to position i }
  \item{add}{ TRUE if the value should rather increment than overwrite at the index position }
}
\details{
  \command{getset.ff} combines the effects of \command{get.ff} and \command{set.ff} in a single operation: it retrieves the old value at position \code{i} before changing it.
  \command{getset.ff} will maintain \code{\link[bit]{na.count}}.
}
\value{
  \command{get.ff} returns a vector, \command{set.ff} returns the 'changed' ff object (like all assignment functions do) and \command{getset.ff} returns the value at the subscript positions.
  More precisely \code{getset.ff(x, i, value, add=FALSE)} returns the old values at the subscript positions \code{i} while \code{getset.ff(x, i, value, add=TRUE)} returns the incremented values at the subscript positions.
}
\author{ Jens Oehlschlägel }
\note{ \command{get.ff}, \command{set.ff} and \command{getset.ff} are low level functions that do not support \code{ramclass} and \code{ramattribs} and thus will not give the expected result with \code{factor} and \code{POSIXct} }
\seealso{ \code{\link{readwrite.ff}} for low-level access to contiguous chunks and \code{\link{[.ff}} for high-level access }
\examples{
 x <- ff(0, length=12)
 get.ff(x, 3L)
 set.ff(x, 3L, 1)
 x
 set.ff(x, 3L, 1, add=TRUE)
 x
 getset.ff(x, 3L, 1, add=TRUE)
 getset.ff(x, 3L, 1)
 x
 rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
