\name{unclass_-}
\alias{unclass<-}
\title{ Unclassed assignement }
\description{
  With \command{unclass<-} you can circumvent class dispatch on the assignment operator
}
\usage{
unclass(x) <- value
}
\arguments{
  \item{x}{ some object }
  \item{value}{ the value to be assigned }
}
\value{
  the modified object
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{unclass}}, \code{\link{undim}} }
\examples{
  x <- factor(letters)
  unclass(x)[1:3] <- 1L
  x
}
\keyword{ IO }
\keyword{ data }
