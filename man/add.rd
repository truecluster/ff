\name{add}
\alias{add}
\alias{add.ff}
\alias{add.default}
\title{ Incrementing an ff or ram object }
\description{
  Yet another assignment interface in order to allow to formulate \code{x[index,...,add=TRUE]<-value}
  in a way which works transparently, not only for ff, but also for ram objects: \code{add(x, value, index, ...)}.
}
\usage{
add(x, \dots)
\method{add}{ff}(x, value, \dots)
\method{add}{default}(x, value, \dots)
}
\arguments{
  \item{x}{ an ff or ram object }
  \item{value}{ the amount to increment, possibly recylcled }
  \item{\dots}{ further arguments -- especially index information -- passed to \code{\link{[<-}} or \code{\link[=Extract.ff]{[<-.ff}} }
}
\value{
  invisible()
}
\author{ Jens Oehlschlägel }
\note{
  Note that \code{add.default} changes the object in its parent frame and thus violates R's usual functional programming logic.
  Duplicated index positions should be avoided, because ff and ram objects behave differently:
  \preformatted{
  add.ff(x, 1, c(3,3))
  # will increment x at position 3 TWICE by 1, while
  add.default(x, 1, c(3,3))
  # will increment x at position 3 just ONCE by 1
  }
}
\seealso{ \code{\link{swap}}, \code{\link{[.ff}}, \code{\link{LimWarn}} }
\examples{
   message("incrementing parts of a vector")
   x <- ff(0, length=12)
   y <- rep(0, 12)
   add(x, 1, 1:6)
   add(y, 1, 1:6)
   x
   y

   message("incrementing parts of a matrix")
   x <- ff(0, dim=3:4)
   y <- array(0, dim=3:4)
   add(x, 1, 1:2, 1:2)
   add(y, 1, 1:2, 1:2)
   x
   y

   message("BEWARE that ff and ram methods differ in treatment of duplicated index positions")
   add(x, 1, c(3,3))
   add(y, 1, c(3,3))
   x
   y

   rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
