\name{length.hi}
\alias{length.hi}
\alias{poslength.hi}
\alias{maxindex.hi}
\title{ Hybrid Index, querying }
\description{
  Functions to query some index attributes
}
\usage{
\method{length}{hi}(x)
\method{maxindex}{hi}(x, \dots)
\method{poslength}{hi}(x, \dots)
}
\arguments{
  \item{x}{ an object of class \code{\link{hi}} }
  \item{\dots}{ further arguments (not used) }
}
\details{
  \command{length.hi} returns the number of the subsript elements in the index (even if they are negative).
  By contrast \code{\link[bit:maxindex.default]{poslength}} returns the number of selected elements (which for negative indices is \code{maxindex(x) - length(unique(x))}).
  \code{\link[bit:maxindex.default]{maxindex}} returns the highest possible index position.
}
\value{
  an integer scalar
}
\author{ Jens Oehlschlägel }
\note{ duplicated negative indices are removed }
\seealso{ \code{\link{hi}}, \code{\link{as.hi}}, \code{\link{length.ff}}, \code{\link{length}}, \code{\link[bit:maxindex.default]{poslength}}, \code{\link[bit:maxindex.default]{maxindex}} }
\examples{
  length(as.hi(-1, maxindex=12))
  poslength(as.hi(-1, maxindex=12))
  maxindex(as.hi(-1, maxindex=12))
  message("note that")
  length(as.hi(c(-1, -1), maxindex=12))
  length(as.hi(c(1,1), maxindex=12))
}
\keyword{ IO }
\keyword{ data }
