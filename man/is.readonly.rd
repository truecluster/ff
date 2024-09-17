\name{is.readonly}
\alias{is.readonly}
\alias{is.readonly.ff}
\title{ Get readonly status }
\description{
  Get readonly status of an ff object
}
\usage{
is.readonly(x, \dots)
\method{is.readonly}{ff}(x, \dots)
}
\arguments{
  \item{x}{ \code{x} }
  \item{\dots}{ \code{\dots} }
}
\details{
  ff objects can be created/opened with \code{readonly=TRUE}.
  After each opening of the ff file readonly status is stored in the \code{\link[=Extract.ff]{physical}} attributes and serves as the default for the next opening.
  Thus querying a closed ff object gives the last readonly status.
}
\value{
  logical scalar
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{open.ff}}, \code{\link[=Extract.ff]{physical}} }
\examples{
  x <- ff(1:12)
  is.readonly(x)
  close(x)
  open(x, readonly=TRUE)
  is.readonly(x)
  close(x)
  is.readonly(x)
  rm(x)
}
\keyword{ IO }
\keyword{ data }
