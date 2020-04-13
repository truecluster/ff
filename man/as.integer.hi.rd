\name{as.integer.hi}
\alias{as.which.hi}
\alias{as.bitwhich.hi}
\alias{as.bit.hi}
\alias{as.integer.hi}
\alias{as.logical.hi}
\alias{as.character.hi}
\alias{as.matrix.hi}
\title{ Hybrid Index, coercing from }
\description{
  Functions that (back-)convert an \code{\link{hi}} object to the respective subscripting information.
}
\usage{
\method{as.which}{hi}(x, \dots)
\method{as.bitwhich}{hi}(x, \dots)
\method{as.bit}{hi}(x, \dots)
\method{as.integer}{hi}(x, vw.convert = TRUE, \dots)
\method{as.logical}{hi}(x, maxindex = NULL, \dots)
\method{as.character}{hi}(x, names, vw.convert = TRUE, \dots)
\method{as.matrix}{hi}(x, dim = x$dim, dimorder = x$dimorder
, vw = x$vw, symmetric = x$symmetric, fixdiag = x$fixdiag, \dots)
}
\arguments{
  \item{x}{ an object of class \code{\link{hi}} }
  \item{maxindex}{ the \code{\link{length}} of the subscripted object (needed for logical output) }
  \item{names}{ the \code{\link{names}} vector of the subscripted object }
  \item{dim}{ the \code{\link{dim}} of the subscripted object }
  \item{dimorder}{ the \code{\link{dimorder}} of the subscripted object }
  \item{vw}{ the virtual window \code{\link{vw}} of the subscripted object }
  \item{vw.convert}{ \code{vw.convert} }
  \item{symmetric}{ TRUE if the subscripted matrix is \code{\link{symmetric}} }
  \item{fixdiag}{ TRUE if the subscripted matrix has \code{\link{fixdiag}} }
  \item{\dots}{ further arguments passed }
}
\value{
  \command{as.integer.hi} returns an integer vector, see \code{\link{as.hi.integer}}.
  \command{as.logical.hi} returns an logical vector, see \code{\link{as.hi.logical}}.
  \command{as.character.hi} returns a character vector, see \code{\link{as.hi.character}}.
  \command{as.matrix.hi} returns a matrix index, see \code{\link{as.hi.matrix}}.
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{hi}}, \code{\link{as.hi}} }
\examples{
  x <- 1:6
  names(x) <- letters[1:6]
  as.integer(as.hi(c(1:3)))
  as.logical(as.hi(c(TRUE,TRUE,TRUE,FALSE,FALSE,FALSE)))
  as.character(as.hi(letters[1:3], names=names(x)), names=names(x))
  x <- matrix(1:12, 6)
  as.matrix(as.hi(rbind(c(1,1), c(1,2), c(2,1)), dim=dim(x)), dim=dim(x))
}
\keyword{ IO }
\keyword{ data }
