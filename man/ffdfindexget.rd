\name{ffdfindexget}
\alias{ffdfindexget}
\alias{ffdfindexset}
\title{
  Reading and writing ffdf data.frame using ff subscripts
}
\description{
  Function \code{ffdfindexget} allows to extract rows from an ffdf data.frame according to positive integer suscripts stored in an ff vector.
  \cr
  Function \code{ffdfindexset} allows the inverse operation: assigning to rows of an ffdf data.frame according to positive integer suscripts stored in an ff vector.
  These functions allow more control than the method dispatch of \code{[} and  \code{[<-} if an ff integer subscript is used.
}
\usage{
  ffdfindexget(x, index, indexorder = NULL, autoindexorder = 3, FF_RETURN = NULL
  , BATCHSIZE = NULL, BATCHBYTES = getOption("ffmaxbytes"), VERBOSE = FALSE)
  ffdfindexset(x, index, value, indexorder = NULL, autoindexorder = 3
  , BATCHSIZE = NULL, BATCHBYTES = getOption("ffmaxbytes"), VERBOSE = FALSE)
}
\arguments{
  \item{x}{
  A \code{\link{ffdf}} data.frame containing the elements
}
  \item{index}{
  A \code{\link{ff}} integer vector with integer subscripts in the range from \code{1} to \code{length(x)}.
}
  \item{value}{
  A \code{\link{ffdf}} data.frame like \code{x} with the rows to be assigned
}
  \item{indexorder}{
  Optionally the return value of \code{\link{ffindexorder}}, see details
}
  \item{autoindexorder}{
  The minimum number of columns (which need chunked indexordering) for which we switch from on-the-fly ordering to stored \code{\link{ffindexorder}}
}
  \item{FF_RETURN}{
  Optionally an \code{\link{ffdf}} data.frame of the same type as x in which the returned values shall be stored, see details.
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
  Accessing rows of an ffdf data.frame identified by integer positions in an ff vector is a non-trivial task, because it could easily lead to random-access to disk files.
  We avoid random access by loading batches of the subscript values into RAM, order them ascending, and only then access the ff values on disk.
  Such ordering is don on-thy-fly for upto \code{autoindexorder-1} columns that need ordering.
  For \code{autoindexorder} o more columns we do the batched ordering upfront with \code{\link{ffindexorder}} and then re-use it in each call to \code{\link{ffindexget}} resp. \code{\link{ffindexset}}.
}
\value{
  Function \code{ffdfindexget} returns a ffdf data.frame with those rows selected by the ff \code{index} vector.
  \cr
  Function \code{ffdfindexset} returns \code{x} with those rows replaced that had been requested by \code{index} and \code{value}.
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{Extract.ff}}, \code{\link{ffindexget}}, \code{\link{ffindexorder}}
}
\examples{
message("ff integer subscripts with ffdf return/assign values")
x <- ff(factor(letters))
y <- ff(1:26)
d <- ffdf(x,y)
i <- ff(2:9)
di <- d[i,]
di
d[i,] <- di
message("ff integer subscripts: more control with ffindexget/ffindexset")
di <- ffdfindexget(d, i, FF_RETURN=di)
d <- ffdfindexset(d, i, di)
rm(x, y, d, i, di)
gc()
}
\keyword{ IO }
\keyword{ data }
