\name{ffreturn}
\alias{ffreturn}
\title{ Return suitable ff object }
\description{
  \command{ffreturn} returns \code{FF_RETURN} if it is \code{\link{ffsuitable}} otherwise creates a suitable \code{\link{ffsuitable}} object
}
\usage{
ffreturn(FF_RETURN = NULL, FF_PROTO = NULL, FF_ATTR = NULL)
}
\arguments{
  \item{FF_RETURN}{ the object to be tested for suitability }
  \item{FF_PROTO}{ the prototype object which \code{FF_RETURN} should match }
  \item{FF_ATTR}{ a list of additional attributes dominating those from \code{FF_PROTO} }
}
\value{
  a suitable \code{\link{ffsuitable}} object
}
\author{ Jens Oehlschlägel }
\note{ xx Work in progress for package \pkg{R.ff} }
\seealso{ \code{\link{ffconform}}, \code{\link{ffsuitable}} }
\keyword{ IO }
\keyword{ data }
