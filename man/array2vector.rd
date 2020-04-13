\name{array2vector}
\alias{array2vector}
\title{ Array: make vector from array }
\description{
  Makes a vector from an array respecting \option{dim} and \option{dimorder}
}
\usage{
array2vector(x, dim = NULL, dimorder = NULL)
}
\arguments{
  \item{x}{ an \code{\link{array}} }
  \item{dim}{ \code{\link{dim}} }
  \item{dimorder}{ \code{\link{dimorder}} }
}
\details{
 This is the inverse function of \code{\link{vector2array}}.
 It extracts the vector from the array by first moving through the fastest rotating dimension dim[dimorder[1]], then dim[dimorder[2]], and so forth
}
\value{
  a vector
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{vector2array}}, \code{\link{arrayIndex2vectorIndex}} }
\examples{
  array2vector(matrix(1:12, 3, 4))
  array2vector(matrix(1:12, 3, 4, byrow=TRUE), dimorder=2:1)
}
\keyword{ array }
\keyword{ data }
