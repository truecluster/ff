\name{maxffmode}
\alias{maxffmode}
\title{ Lossless vmode coercability }
\description{
  \command{maxffmode} returns the lowest \code{\link{vmode}} that can absorb all input vmodes without data loss
}
\usage{
maxffmode(...)
}
\arguments{
  \item{\dots}{ one or more vectors of vmodes }
}
\value{
  the smallest \code{\link{.ffmode}} which can absorb the input vmodes without data loss
}
\note{
  The output can be larger than any of the inputs (if the highest input vmode is an integer type without NA and any other input requires NA).
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{.vcoerceable}}, \code{\link{.ffmode}}, \code{\link{ffconform}} }
\examples{
   maxffmode(c("quad","logical"), "ushort")
}
\keyword{ IO }
\keyword{ data }
