\name{ffsort}
\alias{ffsort}
\title{
Sorting of ff vectors
}
\description{
Sorting: sort an ff vector -- optionally in-place
}
\usage{
ffsort(x
, aux = NULL
, has.na = TRUE
, na.last = TRUE
, decreasing = FALSE
, inplace = FALSE
, decorate = FALSE
, BATCHBYTES = getOption("ffmaxbytes")
, VERBOSE = FALSE
)
}
\arguments{
  \item{x}{
    an ff vector
}
  \item{aux}{
    NULL or an ff vector of the same type for temporary storage
}
  \item{has.na}{
boolean scalar telling ffsort whether the vector might contain \code{NA}s.
\emph{Note} that you risk a crash if there are unexpected \code{NA}s with \code{has.na=FALSE}
}
  \item{na.last}{
boolean scalar telling ffsort whether to sort \code{NA}s last or first.
\emph{Note} that 'boolean' means that there is no third option \code{NA} as in \code{\link{sort}}
}
  \item{decreasing}{
boolean scalar telling ffsort whether to sort increasing or decreasing
}
  \item{inplace}{
boolean scalar telling ffsort whether to sort the original ff vector (\code{TRUE})
or to create a sorted copy (\code{FALSE}, the default)
}
  \item{decorate}{
boolean scalar telling ffsort whether to decorate the returned ff vector with \code{\link[bit:Metadata]{is.sorted}}
and \code{\link[bit]{na.count}} attributes.
}
  \item{BATCHBYTES}{
  maximum number of RAM bytes ffsort should try not to exceed
}
  \item{VERBOSE}{
  cat some info about the sorting
}
}
\details{
  ffsort tries to sort the vector in-RAM respecting the BATCHBYTES limit.
  If a fast sort it not possible, it uses a slower in-place sort (shellsort).
  If in-RAM is not possible, it uses (a yet simple) out-of-memory algorithm.
  Like \code{\link[bit]{ramsort}} the in-RAM sorting method is choosen depending on context information.
  If a key-index sort can be used, ffsort completely avoids merging disk based subsorts.
  If argument \code{decorate=TRUE} is used, then \code{na.count(x)} will return the number of NAs
  and \code{is.sorted(x)} will return TRUE if the sort was done with \code{na.last=TRUE} and \code{decreasing=FALSE}.
}
\note{
  the ff vector may not have a names attribute
}
\value{
  An ff vector -- optionally decorated with \code{\link[bit:Metadata]{is.sorted}} and \code{\link[bit]{na.count}}, see argument 'decorate'
}
\author{
  Jens Oehlschlägel
}

\seealso{
  \code{\link[bit]{ramsort}}, \code{\link{fforder}}, \code{\link{ffdfsort}}
}
\examples{
   n <- 1e6
   x <- ff(c(NA, 999999:1), vmode="double", length=n)
   x <- ffsort(x)
   x
   is.sorted(x)
   na.count(x)
   x <- ffsort(x, decorate=TRUE)
   is.sorted(x)
   na.count(x)
   x <- ffsort(x, BATCHBYTES=n, VERBOSE=TRUE)
}
\keyword{univar}
\keyword{manip}
\keyword{arith}
\keyword{ IO }
\keyword{ data }
