\name{dimorderCompatible}
\alias{dimorderStandard}
\alias{vectorStandard}
\alias{dimorderCompatible}
\alias{vectorCompatible}
\title{ Test for dimorder compatibility }
\description{
  \command{dimorderStandard} returns TRUE if the dimorder is standard (ascending),
  \command{vectorStandard} returns TRUE if the dimorder-bydim combination is compatible with a standard elementwise vector interpretation,
  \command{dimorderCompatible} returns TRUE if two dimorders have a compatible  elementwise vector interpretation
  and \command{vectorCompatible} returns TRUE if dimorder-bydim combinations have a compatible  elementwise vector interpretation.
}
\usage{
dimorderStandard(dimorder)
vectorStandard(dimorder, bydim = NULL)
dimorderCompatible(dim, dim2, dimorder, dimorder2)
vectorCompatible(dim, dim2, dimorder=NULL, dimorder2=NULL, bydim = NULL, bydim2 = NULL)
}
\arguments{
  \item{dim}{ a \code{\link{dim}} }
  \item{dim2}{ a dim }
  \item{dimorder}{ a \code{\link{dimorder}} }
  \item{dimorder2}{ a dimorder }
  \item{bydim}{ a bydim order, see \code{\link{[.ff}} }
  \item{bydim2}{ a bydim order, see argument \code{fromdim} in \code{\link{update.ff}} }
}
\value{
  TRUE if compatibility has been detected, FALSE otherwise
}
\author{ Jens Oehlschlägel }
\note{ does not yet gurantee to detect all compatible configurations, but the most important ones }
\seealso{ \code{\link{dimorder}}, \code{\link{ffconform}} }
\keyword{ IO }
\keyword{ data }
