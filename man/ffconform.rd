\name{ffconform}
\alias{ffconform}
\title{ Get most conforming argument }
\description{
  \command{ffconform} returns position of 'most' conformable ff argument or zero if the arguments are not conforming
}
\usage{
ffconform(\dots, vmode = NULL, fail = "stop")
}
\arguments{
  \item{\dots}{ two or more ff objects }
  \item{vmode}{ handing over target vmode here supresses searching for a common vmode, see \code{\link{maxffmode}} }
  \item{fail}{ the name of a function to call if not-conforming, default \code{\link{stop}} }
}
\details{
  A reference argument is defined to be the first argument with a \code{\link[=dim.ff]{dim}} attribute or the longest vector.
  The other arguements are then compared to the reference to check for conformity,
  which is violated if vmodes are not conforming
  or if the reference has not a multiple length of each other
  or if the dimensions do not match
  or if we have a dimorder conflict because not all arguments have the same \code{\link{dimorderStandard}}.
}
\value{
  the position of the most conforming argument or 0 (zero) if not conforming.
}
\author{ Jens Oehlschlägel }
\note{ xx Work in progress for package \pkg{R.ff} }
\seealso{ \code{\link{ffsuitable}}, \code{\link{maxffmode}}, \code{\link{ymismatch}}, \code{\link{stop}}, \code{\link{warning}}, \code{\link{dimorderStandard}} }
\examples{
  a <- ff(1:10)
  b <- clone(a)
  c <- ff(1:20)
  d <- ff(1:21)
  ffconform(a,b)
  ffconform(c,a)
  ffconform(a,c)
  ffconform(c,a,b)

  d1 <- ff(1:20, dim=c(2,10))
  d2 <- ff(1:20, dim=c(10,2))
  ffconform(c,d1)
  ffconform(c,d2)
  ffconform(d1,c)
  ffconform(d2,c)
  try(ffconform(d1,d2))
  ffconform(d1,d1)

  rm(a,b,c,d1,d2); gc()
}
\keyword{ IO }
\keyword{ data }
