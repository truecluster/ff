\name{dimnames.ff}
\alias{dimnames.ff}
\alias{dimnames.ff_array}
\alias{dimnames<-.ff_array}
\title{ Getting and setting dimnames }
\description{
  For \code{ff_array}s you can set dimnames.
}
\usage{
  \method{dimnames}{ff_array}(x)
  \method{dimnames}{ff_array}(x) <- value
}
\arguments{
  \item{x}{ a ff array (or matrix) }
  \item{value}{ a list with length(dim(x)) elements (either NULL of character vector of length of dimension }
}
\details{
  if \code{\link{vw}} is set, \command{dimnames.ff_array} returns the appropriate part of the names, but you can't set \command{dimnames} while \command{vw} is set.
  \command{dimnames} returns NULL for \code{ff_vectors} and setting \code{dimnames} for \code{ff_vector} is not allowed, but setting \code{\link[=names.ff]{names}} is.
}
\value{
  \command{dimnames} returns a list, see \code{\link{dimnames}}
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{dimnames}}, \code{\link{dim.ff}} , \code{\link{names.ff}} , \code{\link{vw}}, \code{\link[=Extract.ff]{virtual}} }
\examples{
  x <- ff(1:12, dim=c(3,4), dimnames=list(letters[1:3], LETTERS[1:4]))
  dimnames(x)
  dimnames(x) <- list(LETTERS[1:3], letters[1:4])
  dimnames(x)
  dimnames(x) <- NULL
  dimnames(x)
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
