\name{print.ff}
\alias{print.ff}
\alias{print.ffdf}
\alias{print.ff_vector}
\alias{print.ff_matrix}
\alias{str.ff}
\alias{str.ffdf}
\title{ Print and str methods }
\description{
  printing ff objects and compactly showing their structure
}
\usage{
\method{print}{ff}(x, \dots)
\method{print}{ff_vector}(x, maxlength = 16, \dots)
\method{print}{ff_matrix}(x, maxdim = c(16, 16), \dots)
\method{str}{ff}(object, nest.lev=0, \dots)
\method{str}{ffdf}(object, nest.lev=0, \dots)
}
\arguments{
  \item{x}{ a ff object }
  \item{object}{ a ff object }
  \item{nest.lev}{ current nesting level in the recursive calls to str }
  \item{maxlength}{ max number of elements to print from an \code{ff_vector} }
  \item{maxdim}{ max number of elements to print from each dimension from an \code{ff_array} }
  \item{\dots}{ further arguments to print }
}
\details{
  The print methods just print a few exmplary elements from the beginning and end of the dimensions.
}
\value{
  \code{invisible()}
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ff}}, \code{\link{print}}, \code{\link{str}} }
\examples{
  x <- ff(1:10000)
  x
  print(x, maxlength=30)
  dim(x) <- c(100,100)
  x
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
\keyword{ print }
