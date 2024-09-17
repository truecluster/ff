\name{names.ff}
\alias{names.ff}
\alias{names<-.ff}
\alias{names.ff_array}
\alias{names<-.ff_array}
\title{ Getting and setting names }
\description{
  For \code{ff_vector}s you can set names, though this is not recommended for large objects.
}
\usage{
  \method{names}{ff}(x)
  \method{names}{ff}(x) <- value
  \method{names}{ff_array}(x)
  \method{names}{ff_array}(x) <- value
}
\arguments{
  \item{x}{ a ff vector }
  \item{value}{ a character vector }
}
\details{
  If \code{\link{vw}} is set, \command{names.ff} returns the appropriate part of the names, but you can't set names while \command{vw} is set.
  \command{names.ff_array}
  returns NULL and setting names for
  \code{ff_array}s is not allowed,
  but setting \code{\link[=dimnames.ff]{dimnames}} is.
}
\value{
  \command{names} returns a character vector (or NULL)
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{names}}, \code{\link[=dimnames.ff]{dimnames.ff_array}}, \code{\link{vw}}, \code{\link[=Extract.ff]{virtual}} }
\examples{
  x <- ff(1:26, names=letters)
  names(x)
  names(x) <- LETTERS
  names(x)
  names(x) <- NULL
  names(x)
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
