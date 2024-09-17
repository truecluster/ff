\name{is.sorted}
\alias{is.sorted.default}
\alias{is.sorted<-.default}
\title{ Getting and setting 'is.sorted' physical attribute }
\description{
  Functions to mark an ff or ram object as 'is.sorted' and query this. Responsibility to maintain this attribute is with the user.
}
\usage{
\method{is.sorted}{default}(x, \dots)
\method{is.sorted}{default}(x, \dots) <- value
}
\arguments{
  \item{x}{ an ff or ram object }
  \item{\dots}{ ignored }
  \item{value}{ NULL (to remove the 'is.sorted' attribute) or TRUE or FALSE }
}
\details{
  Sorting is slow, see \code{\link{sort}}.
  Checking whether an object is sorted can avoid unnessary sorting -- see \code{\link{is.unsorted}}, \code{\link[bit:intrle]{intisasc}} -- but still takes too much time with large objects stored on disk.
  Thus it makes sense to maintain an attribute, that tells us whether sorting can be skipped.
  Note that -- though you change it yourself -- \code{is.sorted} is a \code{\link[=Extract.ff]{physical}} attribute of an object,
  because it represents an attribute of the \emph{data}, which is shared between different \code{\link[=Extract.ff]{virtual}} views of the object.
}
\value{
  TRUE (if set to TRUE) or FALSE (if set to NULL or FALSE)
}
\note{
  \command{ff} will set \code{is.sorted(x) <- FALSE} if \code{\link[=clone.ff]{clone}} or \code{\link{length<-.ff}} have increased length.
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{is.ordered.ff}} for testing factor levels, \code{\link{is.unsorted}} for testing the data, \code{\link[bit:intrle]{intisasc}} for a quick version thereof, \code{\link[bit]{na.count}} for yet another \code{\link[=Extract.ff]{physical}} attribute }
\examples{
  x <- 1:12
  is.sorted(x) <- !( is.na(is.unsorted(x)) || is.unsorted(x))
  is.sorted(x)
  x[1] <- 100L
  message("don't forget to maintain once it's no longer TRUE")
  is.sorted(x) <- FALSE
  message("check whether as 'is.sorted' attribute is maintained")
  !is.null(physical(x)$is.sorted)
  message("remove the 'is.sorted' attribute")
  is.sorted(x) <- NULL
  message("NOTE that querying 'is.sorted' still returns FALSE")
  is.sorted(x)
}
\keyword{ IO }
\keyword{ data }
\keyword{ arith }
