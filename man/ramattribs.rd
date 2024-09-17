\name{ramattribs}
\alias{ramclass}
\alias{ramclass.ff}
\alias{ramclass.default}
\alias{ramclass_excludes}
\alias{ramattribs}
\alias{ramattribs.ff}
\alias{ramattribs.default}
\alias{ramattribs_excludes}
\title{ Get ramclass and ramattribs }
\description{
  Functions \command{ramclass} and \command{ramattribs} return the respective virtual attributes, that determine which class (and attributes) an ff object receives when subscripted (or coerced) to ram.
}
\usage{
ramclass(x, \dots)
\method{ramclass}{ff}(x, \dots)
\method{ramclass}{default}(x, \dots)
ramattribs(x, \dots)
\method{ramattribs}{ff}(x, \dots)
\method{ramattribs}{default}(x, \dots)
}
\arguments{
  \item{x}{ \code{x} }
  \item{\dots}{ further arguments (not used) }
}
\details{
 \command{ramclass} and \command{ramattribs} provide a general mechanism to store atomic classes in ff objects,
  for example \code{\link{factor}} -- see \code{\link{levels.ff}} -- and \code{\link[base:DateTimeClasses]{POSIXct}}, see the example.
}
\value{
  \command{ramclass} returns a character vector with classnames and \command{ramattribs} returns a list with names elemens just like \code{\link{attributes}}.
  The vectors \code{ramclass_excludes} and \code{ramattribs_excludes} name those attributes, which are not exported from ff to ram objects when using \code{\link{as.ram}}.
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ff}}, \code{\link[=Extract.ff]{virtual}}, \code{\link{as.ram}}, \code{\link{levels.ff}}, \code{\link{attributes}}, \code{\link{DateTimeClasses}} }
\examples{
  x <- ff(as.POSIXct(as.POSIXlt(Sys.time(), "GMT")), length=12)
  x
  ramclass(x)
  ramattribs(x)
  class(x[])
  attributes(x[])
  virtual(x)$ramattribs$tzone = NULL
  attributes(x[])
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
\keyword{ attribute }
\keyword{ classes }
