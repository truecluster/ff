\name{maxlength}
\alias{maxlength}
\alias{maxlength.ff}
\alias{maxlength.default}
\title{ Get physical length of an ff or ram object }
\description{
  \command{maxlength} returns the physical length of an ff or ram object
}
\usage{
maxlength(x, \dots)
\method{maxlength}{ff}(x, \dots)
\method{maxlength}{default}(x, \dots)
}
\arguments{
  \item{x}{ ff or ram object }
  \item{\dots}{ additional arguments (not used) }
}
\value{
  integer scalar
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{length.ff}}, \code{\link[bit:maxindex.default]{maxindex}} }
\examples{
  x <- ff(1:12)
  length(x) <- 10
  length(x)
  maxlength(x)
  x
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
