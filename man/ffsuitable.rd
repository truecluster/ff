\name{ffsuitable}
\alias{ffsuitable}
\alias{ffsuitable_attribs}
\title{ Test ff object for suitability }
\description{
  \command{ffsuitable} tests whether \code{FF_RETURN} is an \code{\link{ff}} object like \code{FF_PROTO} and having attributes \code{FF_ATTR}.
}
\usage{
ffsuitable(FF_RETURN, FF_PROTO = NULL, FF_ATTR = list()
, strict.dimorder = TRUE, fail = "warning")
ffsuitable_attribs(x)
}
\arguments{
  \item{x}{ an object from which to extract attributes for comparison }
  \item{FF_RETURN}{ the object to be tested for suitability }
  \item{FF_PROTO}{ the prototype object which \code{FF_RETURN} should match }
  \item{FF_ATTR}{ a list of additional attributes dominating those from \code{FF_PROTO} }
  \item{strict.dimorder}{ if TRUE ffsuitability requires that the dimorders are standard (ascending) }
  \item{fail}{ name of a function to be called if not ffsuitable (default \code{\link{warning}}) }
}
\value{
  TRUE if \code{FF_RETURN} object is suitable, FALSE otherwise
}
\author{ Jens Oehlschlägel }
\note{ xx Work in progress for package \pkg{R.ff} }
\seealso{ \code{\link{ffconform}}, \code{\link{ffreturn}} }
\keyword{ IO }
\keyword{ data }
