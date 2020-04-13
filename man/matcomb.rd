\name{matcomb}
\alias{matcomb}
\title{ Array: make matrix indices from row and columns positions }
\description{
  create matrix indices from row and columns positions
}
\usage{
matcomb(r, c)
}
\arguments{
  \item{r}{ integer vector of row positions }
  \item{c}{ integer vector of column positions  }
}
\details{
  rows rotate faster than columns
}
\value{
  a k by 2 matrix of matrix indices where \code{ k = length(r) * length(c) }
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{row}}, \code{\link{col}} , \code{\link{expand.grid}} }
\examples{
  matcomb(1:3, 1:4)
  matcomb(2:3, 2:4)
}
\keyword{ array }
\keyword{ data }
