\name{vector2array}
\alias{vector2array}
\title{ Array: make array from vector }
\description{
  makes array from vector respecting \option{dim} and \option{dimorder}
}
\usage{
vector2array(x, dim, dimorder = NULL)
}
\arguments{
  \item{x}{ an input vector, recyled if needed }
  \item{dim}{ \code{\link{dim}} }
  \item{dimorder}{ \code{\link{dimorder}} }
}
\details{
FILLS vector into array of dim where fastest rotating is dim[dimorder[1]], next is dim[dimorder[2]] and so forth.
This is a generalization of converting vector to matrix(, byrow=TRUE).
NOTE that the result is a ram array always stored in STANDARD dimorder !!!
In this usage we sometimes term the dimorder 'bydim' because it does not change the physical layout of the result,
rather bydim refers to the dimorder in which to interpret the vector (not the result).
In \command{ff}, \command{update} and \command{clone} we have 'bydim' to contrast it from 'dimorder', the latter describing the layout of the file.
}
\value{
  a suitable \code{\link{array}}
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{array2vector}}, \code{\link{vectorIndex2arrayIndex}} }
\examples{
  vector2array(1:12, dim=c(3, 4))               # matrix(1:12, 3, 4)
  vector2array(1:12, dim=c(3, 4), dimorder=2:1) # matrix(1:12, 3, 4, byrow=TRUE)
}
\keyword{ array }
\keyword{ data }
