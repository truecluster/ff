\name{ffdfsort}
\alias{dfsort}
\alias{dforder}
\alias{ramdfsort}
\alias{ramdforder}
\alias{ffdfsort}
\alias{ffdforder}
\title{
Sorting: convenience wrappers for data.frames
}
\description{
These functions allow convenient sorting and ordering of collections of (ff) vectors organized in (ffdf) data.frames
}
\usage{
dforder(x, ...)
dfsort(x, ...)
ramdforder(x, ...)
ramdfsort(x, ...)
ffdforder(x, ...)
ffdfsort(x, ...)
}
\arguments{
  \item{x}{
  a \code{\link{data.frame}} (for \code{dforder, dfsort, ramorder, ramsort}) or an \code{\link{ffdf}} object (for \code{ffdforder, ffdfsort})
}
  \item{\dots}{
  further arguments passed to \code{\link{sort}}, \code{\link[bit]{ramsort}} or \code{\link{ffsort}} (for objects with one column)
  or passed to \code{\link{order}}, \code{\link[bit]{ramorder}} or \code{\link{fforder}} (for objects with mulitple columns)
}
}
\value{
 the order functions return an (ff) vector of integer order positions, the sort functions return a sorted clone of the (ffdf) input data.frame
}
\author{
  Jens Oehlschlägel
}

\seealso{
    \code{\link{sort}}, \code{\link[bit]{ramsort}} or \code{\link{ffsort}} \cr
    \code{\link{order}}, \code{\link[bit]{ramorder}} or \code{\link{fforder}}
}
\examples{
   x <- ff(sample(1e5, 1e6, TRUE))
   y <- ff(sample(1e5, 1e6, TRUE))
   z <- ff(sample(1e5, 1e6, TRUE))
   d <- ffdf(x, y, z)
   d2 <- ffdfsort(d)
   d2
   d
   d2 <- d[1:2]
   i <- ffdforder(d2)
   d[i,]
   rm(x, y, z, i, d, d2)
   gc()
}
\keyword{univar}
\keyword{manip}
\keyword{arith}
\keyword{ IO }
\keyword{ data }
