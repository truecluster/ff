\name{clone.ffdf}
\Rdversion{1.1}
\alias{clone.ffdf}
\title{
Cloning ffdf objects
}
\description{
clone physically duplicates ffdf objects
}
\usage{
\method{clone}{ffdf}(x, nrow=NULL, ...)
}
\arguments{
  \item{x}{an \code{\link{ffdf}} }
  \item{nrow}{ optionally the desired number of rows in the new object. Currently this works only together with \code{initdata=NULL} }
  \item{\dots}{ further arguments passed to \code{\link[=clone.ff]{clone}} (usually not usefull) }
}
\details{
  Creates a deep copy of an ffdf object by cloning all \code{\link[=Extract.ffdf]{physical}} components including the \code{\link[=dimnames.ffdf]{row.names}}
}
\value{
  An object of type \code{\link{ffdf}}
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link[=clone.ff]{clone}}, \code{\link{ffdf}}
}
\examples{
  x <- as.ffdf(data.frame(a=1:26, b=letters, stringsAsFactors = TRUE))

  message("Here we change the content of both x and y by reference")
  y <- x
  x$a[1] <- -1
  y$a[1]

  message("Here we change the content only of x because y is a deep copy")
  y <- clone(x)
  x$a[2] <- -2
  y$a[2]
  rm(x, y); gc()
}
\keyword{ IO }
\keyword{ data }
