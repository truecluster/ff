\name{length.ffdf}
\Rdversion{1.1}
\alias{length.ffdf}
\title{
Getting length of a ffdf dataframe
}
\description{
Getting "length" (number of columns) of a ffdf dataframe
}
\usage{
\method{length}{ffdf}(x)
}
\arguments{
  \item{x}{an \code{\link{ffdf}} object}
}
\value{ integer number of columns}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{dim.ffdf}}, \code{\link{length.ff}}, \code{\link{ffdf}}
}
\examples{
  length(as.ffdf(data.frame(a=1:26, b=letters, stringsAsFactors = TRUE)))
  gc()
}
\keyword{ IO }
\keyword{ data }
