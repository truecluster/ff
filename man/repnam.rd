\name{repnam}
\Rdversion{1.1}
\alias{repnam}
\title{
  Replicate with names
}
\description{
  Function \code{repnam} replicates its \code{argument} to the desired \code{length}, either by simply \code{\link{rep}licating} or - if it has \code{\link{names}} - by replicating the \code{default} and matching the argument by its names.
}
\usage{
repnam(argument, names = NULL, len=length(names), default = list(NULL))
}
\arguments{
  \item{argument}{
  a named or non-named vector or list to be replicated
}
  \item{names}{
  NULL or a charcter vector of names to which the argument names are matched
}
  \item{len}{
  the desired length (required if names is not given)
}
  \item{default}{
  the desired default which is replicated in case names are used (the default \code{list(NULL)} is suitable for a list argument)
}
}
\value{ an object like argument or default having length len }
\author{
  Jens Oehlschlägel
}
\note{
  This is for internal use, e.g. to handle argument \code{colClasses} in \code{\link{read.table.ffdf}}
}
\seealso{
  \code{\link{rep}}, \code{\link{vector}}, \code{\link[bit]{repfromto}}
}
\examples{
 message("a list example")
 repnam(list(y=c(1,2), z=3), letters)
 repnam(list(c(1,2), 3), letters)

 message("a vector example")
 repnam(c(y=1, z=3), letters, default=NA)
 repnam(c(1, 3), letters, default=NA)

}
\keyword{ utilities }
