\name{pagesize}
\alias{pagesize}
\alias{pagesize.ff}
\title{ Pagesize of ff object }
\description{
  Returns current pagesize of ff object
}
\usage{
pagesize(x, \dots)
\method{pagesize}{ff}(x, \dots)
}
\arguments{
  \item{x}{ an \code{\link{ff}} object }
  \item{\dots}{ further arguments (not used) }
}
\value{
  integer number of bytes
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{getpagesize}} }
\examples{
  x <- ff(1:12)
  pagesize(x)
}
\keyword{ IO }
\keyword{ data }
