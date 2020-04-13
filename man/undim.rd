\name{undim}
\alias{undim}
\title{ Undim }
\description{
  \command{undim} returns its input with the dim attribute removed
}
\usage{
undim(x)
}
\arguments{
  \item{x}{ an object }
}
\value{
  x without dim attribute
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{unclass<-}}, \code{\link{unclass}}, \code{\link{unname}}, \code{\link{dim}} }
\examples{
  x <- matrix(1:12, 3)
  x
  undim(x)
}
\keyword{ IO }
\keyword{ data }
