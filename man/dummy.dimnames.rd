\name{dummy.dimnames}
\alias{dummy.dimnames}
\title{ Array: make dimnames }
\description{
  makes standard dimnames from letters and integers (for testing)
}
\usage{
dummy.dimnames(x)
}
\arguments{
  \item{x}{ an \code{\link{array}} }
}
\value{
  a list with character vectors suitable to be assigned as dimnames to x
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{dimnames}} }
\examples{
  dummy.dimnames(matrix(1:12, 3, 4))
}
\keyword{ array }
\keyword{ data }
