\name{vw}
\alias{vw}
\alias{vw<-}
\alias{vw.ff}
\alias{vw.default}
\alias{vw<-.ff_vector}
\alias{vw<-.ff_array}
\title{ Getting and setting virtual windows }
\description{
  The virtual window \command{vw} function allows one to define a virtual window into an \code{ff_vector} or \code{ff_array}.
  The ff object will behave like a smaller array and it is mapped into the specified region of the complete array.
  This allows for example to execute recursive divide and conquer algorithms that work on parts of the full object,
  without the need to repeatedly create subfiles.
}
\usage{
vw(x, \dots)
vw(x, \dots) <- value
\method{vw}{ff}(x, \dots)
\method{vw}{default}(x, \dots)
\method{vw}{ff_vector}(x, \dots) <- value
\method{vw}{ff_array}(x, \dots) <- value
}
\arguments{
  \item{x}{ an \code{ff_vector} or \code{ff_array} }
  \item{\dots}{ further arguments (not used) }
  \item{value}{ a vector or matrix with an Offset, Window and Rest component, see details and examples }
}
\details{
  Each dimension of an ff array (or vector) is decomposed into three components, an invisible Offset, a visibe Window and an invisible Rest.
  For each dimension the sum of the vw components must match the dimension (or length).
  For an \code{ff_vector}, \code{vw} is simply a vector[1:3], for an array is is a \code{matrix[1:3,seq_along(dim(x))]}.
  \code{vw} is a \code{\link[=Extract.ff]{virtual}} attribute. \cr
}
\value{
  NULL or a vw specification, see details
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{length.ff}}, \code{\link{dim.ff}}, \code{\link[=Extract.ff]{virtual}} }
\examples{
  x <- ff(1:26, names=letters)
  y <- x
  vw(x) <- c(0, 13, 13)
  vw(y) <- c(13, 13, 0)
  x
  y
  x[1] <- -1
  y[1] <- -2
  vw(x) <- NULL
  x[]

  z <- ff(1:24, dim=c(4,6), dimnames=list(letters[1:4], LETTERS[1:6]))
  z
  vw(z) <- rbind(c(1,1), c(2,4), c(1,1))
  z

  rm(x,y,z); gc()
}
\keyword{ IO }
\keyword{ data }
\keyword{ array }
