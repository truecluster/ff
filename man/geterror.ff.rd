\name{geterror.ff}
\alias{geterror.ff}
\alias{geterrstr.ff}
\title{ Get error and error string }
\description{
  Get last error code and error string that occured on an ff object.
}
\usage{
geterror.ff(x)
geterrstr.ff(x)
}
\arguments{
  \item{x}{ an ff object }
}
\value{
  \command{geterror.ff} returns an error integer code (no error = 0) and \command{geterrstr.ff} returns the error message (no error = "no error").
}
\author{ Jens Oehlschlägel, Daniel Adler (C++ back-end) }
\seealso{  \code{\link{ff}} }
\examples{
  x <- ff(1:12)
  geterror.ff(x)
  geterrstr.ff(x)
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
