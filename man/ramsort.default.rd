\name{ramsort.default}
\alias{ramsort.default}
\alias{mergesort.default}
\alias{radixsort.default}
\alias{keysort.default}
\alias{shellsort.default}
\title{
Sorting: Sort R vector in-RAM and in-place
}
\description{
Function \code{ramsort} will sort the input vector in-place (without making a copy) and return the number of NAs found
}
\usage{
\method{ramsort}{default}(x, has.na = TRUE, na.last = TRUE, decreasing = FALSE
, optimize = c("time", "memory"), VERBOSE = FALSE, \dots)
\method{mergesort}{default}(x, has.na = TRUE, na.last = TRUE, decreasing = FALSE, \dots)
\method{radixsort}{default}(x, has.na = TRUE, na.last = TRUE, decreasing = FALSE, \dots)
\method{keysort}{default}(x, keyrange=range(x, na.rm=has.na), has.na = TRUE
, na.last = TRUE, decreasing = FALSE, \dots)
\method{shellsort}{default}(x, has.na = TRUE, na.last = TRUE, decreasing = FALSE, \dots)
}
\arguments{
  \item{x}{
an atomic R vector
}
  \item{keyrange}{
an integer vector with two values giving the smallest and largest possible value in x, note that you should give this explicitely for best performance, relying on the default needs one pass over the data to determine the range
}
  \item{has.na}{
boolean scalar telling ramsort whether the vector might contain \code{NA}s.
\emph{Note} that you risk a crash if there are unexpected \code{NA}s with \code{has.na=FALSE}
}
  \item{na.last}{
boolean scalar telling ramsort whether to sort \code{NA}s last or first.
\emph{Note} that 'boolean' means that there is no third option \code{NA} as in \code{\link{sort}}
}
  \item{decreasing}{
boolean scalar telling ramsort whether to sort increasing or decreasing
}
  \item{optimize}{
by default ramsort optimizes for 'time' which requires more RAM,
set to 'memory' to minimize RAM requirements and sacrifice speed
}
  \item{VERBOSE}{
  cat some info about chosen method
}
  \item{\dots}{
  ignored
}
}
\details{
Function \code{ramsort} is a front-end to a couple of single-threaded sorting algorithms
that have been carefully implemented to be fast with and without \code{NA}s.
\cr
The default is a mergesort algorithm without copying (Sedgewick 8.4) for integer and double data
which requires 2x the RAM of its input vector (character or complex data are not supported).
Mergesort is fast, stable with a reliable runtime.
\cr
For integer data longer than a certain length we improve on mergesort by using a faster LSD
radixsort algorithm (Sedgewick 10.5) that uses 2x the RAM of its input vector plus 65536+1 integers.
\cr
For booleans, logicals, integers at or below the resolution of smallint and for factors below a certain number of levels
we use a key-index sort instead of mergesort or radix sort
(note that R has a (slower) key-index sort in \code{\link{sort.list}} available with confusingly named \code{method='radix'}
but the standard \code{\link{sort}} does not leverage it for factors (2-11.1).
If you call \code{keysort} directly, you should provide a known 'keyrange' directly to obtain the full speed.
\cr
Finally the user can request a sort method that minimizes memory use at the price of longer computation time
with \code{optimize='memory'} -- currently a shellsort.
}
\value{
integer scalar with the number of NAs. This is always 0 with has.na=FALSE
}
\references{
Robert Sedgewick (1997). Algorithms in C, Third edition. Addison-Wesley.
}
\author{
Jens Oehlschlägel
}
\note{
This function is called for its side-effects and breaks the functional programming paradigm. Use with care.
}

\seealso{
  \code{\link{sort}}, \code{\link{ffsort}}, \code{\link{dfsort}}, \code{\link[bit]{ramorder}}
}
\examples{
   n <- 50
   x <- sample(c(NA, NA, 1:26), n, TRUE)
   sort(x)
   ramsort(x)
   x

   \dontrun{
      message("Note how the datatype influences sorting speed")
      n <- 5e6
      x <- sample(1:26, n, TRUE)

      y <- as.double(x)
      system.time(ramsort(y))

      y <- as.integer(x)
      system.time(ramsort(y))

      y <- as.short(x)
      system.time(ramsort(y))

      y <- as.factor(letters)[x]
      system.time(ramsort(y))
   }
}
\keyword{univar}
\keyword{manip}
\keyword{arith}
