\name{symmIndex2vectorIndex}
\alias{symmIndex2vectorIndex}
\title{ Array: make vector positions from symmetric array index }
\description{
  make vector positions from (non-symmetric) array index respecting \option{dim} and \option{fixdiag}
}
\usage{
symmIndex2vectorIndex(x, dim, fixdiag = NULL)
}
\arguments{
  \item{x}{ a matrix[,1:2] with matrix subscripts }
  \item{dim}{ the dimensions of the symmetric matrix }
  \item{fixdiag}{ NULL assumes free diagonal, any value assumes fixed diagonal }
}
\details{
  With \option{fixdiag = NULL}
}
\value{
  a vector of indices in \code{seq_len(prod(dim(x)))}
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{arrayIndex2vectorIndex}} }
\examples{
  symmIndex2vectorIndex(rbind(
   c(1,1)
  ,c(1,10)
  ,c(10,1)
  ,c(10,10)
  ), dim=c(10,10))
  symmIndex2vectorIndex(rbind(
   c(1,1)
  ,c(1,10)
  ,c(10,1)
  ,c(10,10)
  ), dim=c(10,10), fixdiag=1)
}
\keyword{ array }
\keyword{ data }
