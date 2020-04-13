\name{vectorIndex2arrayIndex}
\alias{vectorIndex2arrayIndex}
\title{ Array: make array from index vector positions }
\description{
  make array from index vector positions respecting \option{dim} and \option{dimorder}
}
\usage{
vectorIndex2arrayIndex(x, dim = NULL, dimorder = NULL, vw = NULL)
}
\arguments{
  \item{x}{ a vector of indices in \code{seq_len(prod(dim))} }
  \item{dim}{ NULL or \code{\link{dim}} }
  \item{dimorder}{ NULL or \code{\link{dimorder}} }
  \item{vw}{ NULL or integer matrix[2,m], see details }
}
\details{
  The fastest rotating dimension is dim[dimorder[1]], then dim[dimorder[2]], and so forth. \cr
  The parameters 'x' and 'dim' may refer to a subarray of a larger array, in this case, the array indices 'x' are interpreted as 'vw[1,] + x' within the larger array 'vw[1,] + x + vw[2,]'.
}
\value{
  an n by m matrix with n m-dimensional array indices
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{vector2array}}, \code{\link{arrayIndex2vectorIndex}} , \code{\link{symmIndex2vectorIndex}} }
\examples{
  matrix(1:12, 3, 4)
  vectorIndex2arrayIndex(1:12, dim=3:4)
  vectorIndex2arrayIndex(1:12, dim=3:4, dimorder=2:1)
  matrix(1:30, 5, 6)
  vectorIndex2arrayIndex(c(6L, 7L, 8L, 11L, 12L, 13L, 16L, 17L, 18L, 21L, 22L, 23L)
, vw=rbind(c(0,1), c(3,4), c(2,1)))
  vectorIndex2arrayIndex(c(2L, 8L, 14L, 3L, 9L, 15L, 4L, 10L, 16L, 5L, 11L, 17L)
, vw=rbind(c(0,1), c(3,4), c(2,1)), dimorder=2:1)

  \dontshow{
    # incomplete regression tests
    x <- matrix(1:12, 3, 4)
    i <- cbind(as.vector(row(x)), as.vector(col(x)))
    stopifnot(identical( array(arrayIndex2vectorIndex(i, dim=dim(x)), dim=dim(x)), x ))
    stopifnot(identical( vectorIndex2arrayIndex(arrayIndex2vectorIndex(i, dim=dim(x), dimorder=1:2), dim=dim(x)), i ))

    y <- vector2array(1:12, c(3,4), 2:1)
    i <- cbind(as.vector(row(y)), as.vector(col(y)))
    stopifnot(identical( array(arrayIndex2vectorIndex(i, dim=dim(y), dimorder=2:1), dim=dim(y)), y ))
    stopifnot(identical( vectorIndex2arrayIndex(arrayIndex2vectorIndex(i, dim=dim(y), dimorder=dimorder(y)), dim=dim(y), dimorder=dimorder(y)), i ))

    z <- vector2array(1:24, dim=4:2, dimorder=c(2,1,3))
    stopifnot(identical( arrayIndex2vectorIndex(vectorIndex2arrayIndex(z, dim=dim(z), dimorder=c(2,1,3)), dim=dim(z), dimorder=c(2,1,3)), as.vector(z) ))
  }
}
\keyword{ array }
\keyword{ data }
