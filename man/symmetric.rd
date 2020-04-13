\name{symmetric}
\alias{symmetric}
\alias{symmetric.ff}
\alias{symmetric.default}
\alias{symmetric.dist}
\title{ Test for symmetric structure }
\description{
  Check if an object is inherently symmetric (its structure, not its data)
}
\usage{
symmetric(x, \dots)
\method{symmetric}{ff}(x, \dots)
\method{symmetric}{default}(x, \dots)
\method{symmetric}{dist}(x, \dots)
}
\arguments{
  \item{x}{ an ff or ram object }
  \item{\dots}{ further arguments (not used) }
}
\details{
  ff matrices can be declared symmetric at creation time. Compatibility function \command{symmetric.default} returns FALSE, \command{symmetric.dist} returns TRUE.
}
\value{
  TRUE or FALSE
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{symmetric}}, \code{\link{ff}} %, \code{\link{symm}}
        , \code{\link{dist}}, \code{\link{isSymmetric}} }
\examples{
  symmetric(matrix(1:16, 4, 4))
  symmetric(dist(rnorm(1:4)))
}
\keyword{ IO }
\keyword{ data }
