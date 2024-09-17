\name{ffindexorder}
\alias{ffindexorder}
\alias{ffindexordersize}
\title{
  Sorting: chunked ordering of integer suscript positions
}
\description{
  Function \code{ffindexorder} will calculate chunkwise the order positions to sort all positions in a chunk ascending.
  \cr
  Function \code{ffindexordersize} does the calculation of the chunksize for \code{ffindexorder}.
}
\usage{
ffindexordersize(length, vmode, BATCHBYTES = getOption("ffmaxbytes"))
ffindexorder(index, BATCHSIZE, FF_RETURN = NULL, VERBOSE = FALSE)
}
\arguments{
  \item{index}{
  A \code{\link{ff}} integer vector with integer subscripts.
}
  \item{BATCHSIZE}{
  Limit for the chunksize (see details)
}
  \item{BATCHBYTES}{
  Limit for the number of bytes per batch
}
  \item{FF_RETURN}{
  Optionally an \code{\link{ff}} integer vector in which the chunkwise order positions are stored.
}
  \item{VERBOSE}{
  Logical scalar for activating verbosing.
}
  \item{length}{
  Number of elements in the index
}
  \item{vmode}{
  The \code{\link{vmode}} of the ff vector to which the index shall be applied with \code{\link{ffindexget}} or \code{\link{ffindexset}}
}
}
\details{
  Accessing integer positions in an ff vector is a non-trivial task, because it could easily lead to random-access to a disk file.
  We avoid random access by loading batches of the subscript values into RAM, order them ascending, and only then access the ff values on disk.
  Such an ordering can be done on-the-fly by \code{\link{ffindexget}} or it can be created upfront with \code{ffindexorder}, stored and re-used,
  similar to storing and using hybrid index information with \code{\link{as.hi}}.
}
\value{
  Function \code{ffindexorder} returns an ff integer vector with an attribute \code{BATCHSIZE} (the chunksize finally used, not the one given with argument \code{BATCHSIZE}).
  \cr
  Function \code{ffindexordersize} returns a balanced batchsize as returned from \code{\link[bit]{bbatch}}.
}
\author{
  Jens Oehlschlägel
}
\seealso{
   \code{\link{ffindexget}},  \code{\link{as.hi}},  \code{\link[bit]{bbatch}}
}
\examples{
     x <- ff(sample(40))
     message("fforder requires sorting")
     i <- fforder(x)
     message("applying this order i is done by ffindexget")
     x[i]
     message("applying this order i requires random access, 
       therefore ffindexget does chunkwise sorting")
     ffindexget(x, i)
     message("if we want to apply the order i multiple times,
       we can do the chunkwise sorting once and store it")
     s <- ffindexordersize(length(i), vmode(i), BATCHBYTES = 100)
     o <- ffindexorder(i, s$b)
     message("this is how the stored chunkwise sorting is used")
     ffindexget(x, i, o)
     message("")
     rm(x,i,s,o)
     gc()
}
\keyword{ IO }
\keyword{ data }
