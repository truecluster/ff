\name{is.open}
\alias{is.open}
\alias{is.open.ff}
\alias{is.open.ffdf}
\alias{is.open.ff_pointer}
\title{ Test if object is opened }
\description{
  Test whether an ff or ffdf object or a \code{ff_pointer} is opened.
}
\usage{
is.open(x, \dots)
\method{is.open}{ff}(x, \dots)
\method{is.open}{ffdf}(x, \dots)
\method{is.open}{ff_pointer}(x, \dots)
}
\arguments{
  \item{x}{ an \code{\link{ff}} or \code{\link{ffdf}} object }
  \item{\dots}{ further arguments (not used) }
}
\details{
  ff objects open automatically if accessed while closed.
  For ffdf objects we test all of their \code{\link[=Extract.ffdf]{physical}} components including their \code{\link[=row.names.ffdf]{row.names}} if they are \code{\link{is.ff}}
}
\value{
  TRUE or FALSE (or NA if not all components of an ffdf object are opened or closed)
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{is.readonly}}, \code{\link{open.ff}}, \code{\link{close.ff}} }
\examples{
  x <- ff(1:12)
  is.open(x)
  close(x)
  is.open(x)
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
