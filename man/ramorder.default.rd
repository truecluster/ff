\name{ramorder.default}
\alias{ramorder.default}
\alias{mergeorder.default}
\alias{radixorder.default}
\alias{keyorder.default}
\alias{shellorder.default}
\title{
Sorting: order R vector in-RAM and in-place
}
\description{
Function \code{ramorder} will order the input vector in-place (without making a copy) and return the number of NAs found
}
\usage{
\method{ramorder}{default}(x, i, has.na = TRUE, na.last = TRUE, decreasing = FALSE
, stable = TRUE, optimize = c("time", "memory"), VERBOSE = FALSE, \dots)
\method{mergeorder}{default}(x, i, has.na = TRUE, na.last = TRUE, decreasing = FALSE, \dots)
\method{radixorder}{default}(x, i, has.na = TRUE, na.last = TRUE, decreasing = FALSE, \dots)
\method{keyorder}{default}(x, i, keyrange=range(x, na.rm=has.na), has.na = TRUE, na.last = TRUE
, decreasing = FALSE, \dots)
\method{shellorder}{default}(x, i, has.na = TRUE, na.last = TRUE, decreasing = FALSE, stabilize=FALSE, \dots)
}
\arguments{
  \item{x}{
an atomic R vector
}
  \item{i}{
 a integer vector with a permuation of positions in x (you risk a crash if you violate this)
}
  \item{keyrange}{
an integer vector with two values giving the smallest and largest possible value in x, note that you should give this explicitely for best performance, relying on the default needs one pass over the data to determine the range
}
  \item{has.na}{
boolean scalar telling ramorder whether the vector might contain \code{NA}s.
\emph{Note} that you risk a crash if there are unexpected \code{NA}s with \code{has.na=FALSE}
}
  \item{na.last}{
boolean scalar telling ramorder whether to order \code{NA}s last or first.
\emph{Note} that 'boolean' means that there is no third option \code{NA} as in \code{\link{order}}
}
  \item{decreasing}{
boolean scalar telling ramorder whether to order increasing or decreasing
}
  \item{stable}{
 set to false if stable ordering is not needed (may enlarge the set of ordering methods considered)
}
  \item{optimize}{
by default ramorder optimizes for 'time' which requires more RAM, set to 'memory'
to minimize RAM requirements and sacrifice speed
}
  \item{VERBOSE}{
  cat some info about chosen method
}
  \item{stabilize}{
  Set to \code{TRUE} for stabilizing the result of shellorder (for equal keys the order values will be sorted, this only works if \code{i=1:n})
to minimize RAM requirements and sacrifice speed
}
  \item{\dots}{
  ignored
}
}
\details{
Function \code{ramorder} is a front-end to a couple of single-threaded ordering algorithms
that have been carefully implemented to be fast with and without \code{NA}s.
\cr
The default is a mergeorder algorithm without copying (Sedgewick 8.4) for integer and double data
which requires 2x the RAM of its input vector (character or complex data are not supported).
Mergeorder is fast, stable with a reliable runtime.
\cr
For integer data longer than a certain length we improve on mergeorder by using a faster LSD
radixorder algorithm (Sedgewick 10.5) that uses 2x the RAM of its input vector plus 65536+1 integers.
\cr
For booleans, logicals, integers at or below the resolution of smallint and for factors below a certain number of levels
we use a key-index order instead of mergeorder or radix order
(note that R has a (slower) key-index order in \code{\link{sort.list}} available with confusingly named \code{method='radix'}
but the standard \code{\link{order}} does not leverage it for factors (2-11.1).
If you call \code{keyorder} directly, you should provide a known 'keyrange' directly to obtain the full speed.
\cr
Finally the user can request a order method that minimizes memory use at the price of longer computation time
with \code{optimize='memory'} -- currently a shellorder.
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
  \code{\link{order}}, \code{\link{fforder}}, \code{\link{dforder}}, \code{\link[bit]{ramsort}}
}
\examples{
   n <- 50
   x <- sample(c(NA, NA, 1:26), n, TRUE)
   order(x)
   i <- 1:n
   ramorder(x, i)
   i
   x[i]

   \dontrun{
      message("Note how the datatype influences sorting speed")
      n <- 1e7
      x <- sample(1:26, n, TRUE)

      y <- as.double(x)
      i <- 1:n
      system.time(ramorder(y, i))

      y <- as.integer(x)
      i <- 1:n
      system.time(ramorder(y, i))

      y <- as.short(x)
      i <- 1:n
      system.time(ramorder(y, i))

      y <- factor(letters)[x]
      i <- 1:n
      system.time(ramorder(y, i))
   }
}
\keyword{univar}
\keyword{manip}
\keyword{arith}
