\name{ffxtensions}
\alias{ffxtensions}
\alias{ffsymmxtensions}
\title{ Test for availability of ff extensions }
\description{
  checks if this version of package ff supports ff extensions.
}
\usage{
 ffxtensions()
 ffsymmxtensions()
}
\value{
  logical scalar
}
\details{
  ff extensions are needed for certain bitcompressed vmodes and ff symm extensions for symmetric matrices.
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{vmode}}%, \code{\link{symm}}
}
\examples{
  ffxtensions()
  ffsymmxtensions()
}
\keyword{ IO }
\keyword{ data }
