\name{fforder}
\alias{fforder}
\title{
Sorting: order from ff vectors
}
\description{
Returns order with regard to one or more ff vectors
}
\usage{
fforder(...
, index = NULL
, use.index = NULL
, aux = NULL
, auxindex = NULL
, has.na = TRUE
, na.last = TRUE
, decreasing = FALSE
, BATCHBYTES = getOption("ffmaxbytes")
, VERBOSE = FALSE
)
}
\arguments{
  \item{\dots}{
  one of more ff vectors which define the order
}
  \item{index}{
  an optional ff integer vector used to store the order output
}
  \item{use.index}{
  A boolean flag telling fforder whether to use the positions in 'index' as input.
  If you do this, it is your responsibility to assure legal positions - otherwise you risk a crash.
}
  \item{aux}{
  An optional named list of ff vectors that can be used for temporary copying
  -- the names of the list identify the \code{\link{vmode}s} for which the respective ff vector is suitable.
}
  \item{auxindex}{
  An optional ff intger vector for temporary storage of integer positions.
}
  \item{has.na}{
boolean scalar telling fforder whether the vector might contain \code{NA}s.
\emph{Note} that you risk a crash if there are unexpected \code{NA}s with \code{has.na=FALSE}
}
  \item{na.last}{
boolean scalar telling fforder whether to order \code{NA}s last or first.
\emph{Note} that 'boolean' means that there is no third option \code{NA} as in \code{\link{order}}
}
  \item{decreasing}{
boolean scalar telling fforder whether to order increasing or decreasing
}
  \item{BATCHBYTES}{
  maximum number of RAM bytes fforder should try not to exceed
}
  \item{VERBOSE}{
  cat some info about the ordering
}
}
\details{
  fforder tries to order the vector in-RAM, if not possible it uses (a yet simple) out-of-memory algorithm.
  Like \code{\link[bit]{ramorder}} the in-RAM ordering method is choosen depending on context information.
}
\value{
  An ff vector with the positions that ore required to sort the input as specified
-- with an attribute \code{\link[bit]{na.count}} with as many values as columns in \dots
}
\author{
  Jens Oehlschlägel
}

\seealso{
  \code{\link[bit]{ramorder}}, \code{\link{ffsort}}, \code{\link{ffdforder}}, \code{\link{ffindexget}}
}
\examples{
   x <- ff(sample(1e5, 1e6, TRUE))
   y <- ff(sample(1e5, 1e6, TRUE))
   d <- ffdf(x, y)

   i <- fforder(y)
   y[i]
   i <- fforder(x, index=i)
   x[i]
   d[i,]

   i <- fforder(x, y)
   d[i,]

   i <- ffdforder(d)
   d[i,]

   rm(x, y, d, i)
   gc()
}
\keyword{univar}
\keyword{manip}
\keyword{arith}
\keyword{ IO }
\keyword{ data }
