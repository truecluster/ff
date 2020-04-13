\name{vmode.ffdf}
\Rdversion{1.1}
\alias{vmode.ffdf}
\title{
Virtual storage mode of ffdf
}
\description{
Function vmode returns the virtual storage mode of each ffdf column
}
\usage{
\method{vmode}{ffdf}(x, ...)
}
\arguments{
  \item{x}{\code{\link{ffdf}}}
  \item{\dots}{ignored}
}
\value{
  a character vector with one element for each column
}
\author{
  Jens Oehlschlägel
}
\seealso{ \code{\link{vmode}}, \code{\link{ffdf}} }
\examples{
  vmode(as.ffdf(data.frame(a=as.double(1:26), b=letters, stringsAsFactors = TRUE)))
  gc()
}
\keyword{ IO }
\keyword{ data }
