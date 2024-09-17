\name{vt}
\alias{vt}
\alias{vt.ff}
\alias{vt.default}
\alias{t.ff}
\title{ Virtual transpose }
\description{
  The \command{vt} generic does a matrix  or array transpose by modifying \code{\link[=Extract.ff]{virtual}} attributes
  rather than by physically copying matrix elements.
}
\usage{
vt(x, \dots)
\method{vt}{ff}(x, \dots)
\method{vt}{default}(x, \dots)
\method{t}{ff}(x)
}
\arguments{
  \item{x}{ an ff or ram object }
  \item{\dots}{ further arguments (not used) }
}
\details{
  The \code{vt.ff} method does transpose through reversing \code{\link{dim.ff}} and \code{\link{dimorder}}.
  The \code{vt.default} method is a wrapper to the standard transpose \code{\link{t}}. \cr
  The \code{t.ff} method creates a transposed \code{\link[=clone.ff]{clone}}. \cr
  If \code{x} has a virtual window \code{\link{vw}} defined, \code{vt.ff} returns an ff object with a transposed virtual window,
  the \code{t.ff} method return a transposed clone of the virtual window content only.
}
\value{
  an object that behaves like a transposed matrix
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{dim.ff}}, \code{\link{vw}}, \code{\link[=Extract.ff]{virtual}} }
\examples{
  x <- ff(1:20, dim=c(4,5))
  x
  vt(x)
  y <- t(x)
  y
  vw(x) <- cbind(c(1,3,0),c(1,4,0))
  x
  vt(x)
  y <- t(x)
  y
  rm(x,y); gc()
}
\keyword{ IO }
\keyword{ data }
\keyword{ array }
