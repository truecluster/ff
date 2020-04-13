\name{fixdiag}
\alias{fixdiag}
\alias{fixdiag<-}
\alias{fixdiag.ff}
\alias{fixdiag.default}
\alias{fixdiag.dist}
\title{ Test for fixed diagonal }
\description{
  Check if an object has fixed diagonal
}
\usage{
fixdiag(x, \dots)
fixdiag(x, \dots) <- value
\method{fixdiag}{ff}(x, \dots)
\method{fixdiag}{default}(x, \dots)
\method{fixdiag}{dist}(x, \dots)
}
\arguments{
  \item{x}{ an ff or ram object }
  \item{value}{ assignement value }
  \item{\dots}{ further arguments (not used) }
}
\details{
  ff symmetric matrices can be declared to have fixed diagonal at creation time. Compatibility function \command{fixdiag.default} returns NULL, \command{fixdiag.dist} returns 0.
}
\value{
  NULL or the scalar representing the fixed diagonal
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{fixdiag}}, \code{\link{ff}} %, \code{\link{symm}}
        , \code{\link{dist}} }
\examples{
  fixdiag(matrix(1:16, 4, 4))
  fixdiag(dist(rnorm(1:4)))
}
\keyword{ IO }
\keyword{ data }
