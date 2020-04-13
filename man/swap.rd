\name{swap}
\alias{swap}
\alias{swap.ff}
\alias{swap.ff_array}
\alias{swap.default}
\title{ Reading and writing in one operation (high-level) }
\description{
  The generic \command{swap} combines \code{x[i]} and \code{x[i] <- value} in a single operation.
}
\usage{
swap(x, value, \dots)
\method{swap}{ff}(x, value, i, add = FALSE, pack = FALSE, \dots)
\method{swap}{ff_array}(x, value, \dots, bydim = NULL, drop = getOption("ffdrop"), add = FALSE, pack = FALSE)
\method{swap}{default}(x, value, \dots, add = FALSE)
}
\arguments{
  \item{x}{ a ff or ram object }
  \item{value}{ the new values to write, possibly recycled, see \code{\link{[.ff}} }
  \item{i}{ index information, see \code{\link{[.ff}} }
  \item{\dots}{ missing OR up to length(dim(x)) index expressions OR (ff only) \code{\link{hi}} objects }
  \item{drop}{ logical scalar indicating whether array dimensions shall be dropped }
  \item{bydim}{ how to interpret vector to array data, see \code{\link{[.ff}} }
  \item{add}{ TRUE if the values should rather increment than overwrite at the target positions, see \code{\link{readwrite.ff}} }
  \item{pack}{ FALSE to prevent rle-packing in hybrid index preprocessing, see \code{\link{as.hi}} }
}
\details{
  \preformatted{
  y <- swap(x, value, i, add=FALSE, ...)

  is a shorter and more efficient version of

  y <- x[i, add=FALSE, ...]
  x[i, add=FALSE, ...] <- value

  and

  y <- swap(x, value, i, add=TRUE, ...)

  is a shorter and more efficient version of

  y <- x[i, add=TRUE, ...]
  y <- y + value
  x[i, add=FALSE, ...] <- y
  }
}
\value{
  Values at the target positions.
  More precisely \code{swap(x, value, i, add=FALSE)} returns the old values at the position \code{i} while \code{swap(x, value, i, add=TRUE)} returns the incremented values of \code{x}.
}
\author{ Jens Oehlschlägel }
\note{
  Note that \code{swap.default} changes the object in its parent frame and thus violates R's usual functional programming logic.
  When using \code{add=TRUE}, duplicated index positions should be avoided, because ff and ram objects behave differently:
  \preformatted{
  swap.ff(x, 1, c(3,3), add=TRUE)
  # will increment x at position 3 TWICE by 1, while
  swap.default(x, 1, c(3,3), add=TRUE)
  # will increment x at position 3 just ONCE by 1
  }
}
\seealso{ \code{\link{[.ff}}, \code{\link{add}}, \code{\link{readwrite.ff}}, \code{\link{getset.ff}}, \code{\link{LimWarn}} }
\examples{
  x <- ff("a", levels=letters, length=52)
  y <- swap(x, "b", sample(length(x), 26))
  x
  y
  rm(x,y); gc()
}
\keyword{ IO }
\keyword{ data }
\keyword{ array }
