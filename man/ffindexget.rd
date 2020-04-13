\name{ffindexget}
\alias{ffindexget}
\alias{ffindexset}
\title{
  Reading and writing ff vectors using ff subscripts
}
\description{
  Function \code{ffindexget} allows to extract elements from an ff vector according to positive integer suscripts stored in an ff vector.
  \cr
  Function \code{ffindexset} allows the inverse operation: assigning to elements of an ff vector according to positive integer suscripts stored in an ff vector.
  These functions allow more control than the method dispatch of \code{[} and  \code{[<-} if an ff integer subscript is used.
}
\usage{
ffindexget(x, index, indexorder = NULL, FF_RETURN = NULL
, BATCHSIZE = NULL, BATCHBYTES = getOption("ffmaxbytes"), VERBOSE = FALSE)
ffindexset(x, index, value, indexorder = NULL
, BATCHSIZE = NULL, BATCHBYTES = getOption("ffmaxbytes"), VERBOSE = FALSE)
}
\arguments{
  \item{x}{
  A \code{\link{ff}} vector containing the elements
}
  \item{index}{
  A \code{\link{ff}} integer vector with integer subscripts in the range from \code{1} to \code{length(x)}.
}
  \item{value}{
  An \code{\link{ff}} vector of the same \code{\link{vmode}} as x containing the values to be assigned
}
  \item{indexorder}{
  Optionally the return value of \code{\link{ffindexorder}}, see details
}
  \item{FF_RETURN}{
  Optionally an \code{\link{ff}} vector of the same \code{\link{vmode}} as x in which the returned values shall be stored, see details.
}
  \item{BATCHSIZE}{
  Optinal limit for the batchsize (see details)
}
  \item{BATCHBYTES}{
  Limit for the number of bytes per batch
}
  \item{VERBOSE}{
  Logical scalar for verbosing
}
}
\details{
  Accessing integer positions in an ff vector is a non-trivial task, because it could easily lead to random-access to a disk file.
  We avoid random access by loading batches of the subscript values into RAM, order them ascending, and only then access the ff values on disk.
  Since ordering is expensive, it may pay to do the batched ordering once upfront and then re-use it with  \code{\link{ffindexorder}},
  similar to storing and using hybrid index information with \code{\link{as.hi}}.
}
\value{
  Function \code{ffindexget} returns an ff vector with the extracted elements.
  \cr
  Function \code{ffindexset} returns the ff vector in which we have updated values.
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{Extract.ff}}, \code{\link{ffdfindexget}}, \code{\link{ffindexorder}}
}
\examples{
message("ff integer subscripts with ff return/assign values")
x <- ff(factor(letters))
i <- ff(2:9)
xi <- x[i]
xi
xi[] <- NA
xi
x[i] <- xi
x
message("ff integer subscripts: more control with ffindexget/ffindexset")
xi <- ffindexget(x, i, FF_RETURN=xi)
x <- ffindexset(x, i, xi)
rm(x, i, xi)
gc()
}
\keyword{ IO }
\keyword{ data }
