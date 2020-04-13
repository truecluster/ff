\name{mismatch}
\alias{mismatch}
\alias{ymismatch}
\title{ Test for recycle mismatch }
\description{
  \command{mismatch} will return TRUE if the larger of nx,ny is not a multiple of the other and the other is >0 (see arithmetic.c).
  \command{ymismatch} will return TRUE if nx is not a multiple of ny and ny>0
}
\usage{
mismatch(nx, ny)
ymismatch(nx, ny)
}
\arguments{
  \item{nx}{ x length }
  \item{ny}{ y length }
}
\value{
  logical scalar
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ffconform}} }
\examples{
  ymismatch(4,0)
  ymismatch(4,2)
  ymismatch(4,3)
  ymismatch(2,4)
  mismatch(4,0)
  mismatch(4,2)
  mismatch(4,3)
  mismatch(2,4)
}
\keyword{ IO }
\keyword{ data }
