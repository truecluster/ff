\name{arrayIndex2vectorIndex}
\alias{arrayIndex2vectorIndex}
\title{ Array: make vector positions from array index }
\description{
  Make vector positions from a (non-symmetric) array index respecting \option{dim} and \option{dimorder}
}
\usage{
arrayIndex2vectorIndex(x, dim = NULL, dimorder = NULL, vw = NULL)
}
\arguments{
  \item{x}{ an n by m matrix with n m-dimensional array indices }
  \item{dim}{ NULL or \code{\link{dim}} }
  \item{dimorder}{ NULL or \code{\link{dimorder}} }
  \item{vw}{ NULL or integer vector[3] or integer matrix[3,m], see details }
}
\details{
  The fastest rotating dimension is dim[dimorder[1]], then dim[dimorder[2]], and so forth. \cr
  The parameters 'x' and 'dim' may refer to a subarray of a larger array, in this case, the array indices 'x' are interpreted as 'vw[1,] + x' within the larger array 'as.integer(colSums(vw))'.
}
\value{
  a vector of indices in \code{seq_len(prod(dim))} (or  \code{seq_len(prod(colSums(vw)))})
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{array2vector}}, \code{\link{vectorIndex2arrayIndex}} }
\examples{
  x <- matrix(1:12, 3, 4)
  x
  arrayIndex2vectorIndex(cbind(as.vector(row(x)), as.vector(col(x)))
  , dim=dim(x))
  arrayIndex2vectorIndex(cbind(as.vector(row(x)), as.vector(col(x)))
  , dim=dim(x), dimorder=2:1)
  matrix(1:30, 5, 6)
  arrayIndex2vectorIndex(cbind(as.vector(row(x)), as.vector(col(x)))
  , vw=rbind(c(0,1), c(3,4), c(2,1)))
  arrayIndex2vectorIndex(cbind(as.vector(row(x)), as.vector(col(x)))
  , vw=rbind(c(0,1), c(3,4), c(2,1)), dimorder=2:1)
}
\keyword{ array }
\keyword{ data }
