\name{na.count}
\alias{na.count.ff}
\alias{na.count.default}
\alias{na.count<-.ff}
\alias{na.count<-.default}
\title{ Getting and setting 'na.count' physical attribute }
\description{
  The 'na.count' physical attribute gives the current number of NAs if properly initialized and properly maintained, see details.
}
\usage{
\method{na.count}{ff}(x, \dots)
\method{na.count}{default}(x, \dots)
\method{na.count}{ff}(x, \dots) <- value
\method{na.count}{default}(x, \dots) <- value
}
\arguments{
  \item{x}{ an ff or ram object }
  \item{\dots}{ further arguments (not used) }
  \item{value}{ NULL (to remove the 'na.count' attribute) or TRUE to activate or an integer value }
}
\details{
  The 'na.count' feature is activated by assigning the current number of NAs to \code{na.count(x) <- currentNA} and deactivated by assigning NULL.
  The 'na.count' feature is maintained by the, \code{\link{getset.ff}}, \code{\link{readwrite.ff}} and \code{\link{swap}},
  other ff methods for writing -- \code{\link{set.ff}}, \code{\link{[[<-.ff}}, \code{\link{write.ff}}, \code{\link[=Extract.ff]{[<-.ff}} -- will stop if 'na.count' is activated.
  The functions \command{na.count} and \command{na.count<-} are generic.
  For ram objects, the default method for \command{na.count} calculates the number of NAs on the fly, thus no maintenance restrictions apply.
}
\value{
  NA (if set to NULL or NA) or an integer value otherwise
}
\author{ Jens Oehlschlägel, Daniel Adler (C++ back-end) }
\seealso{ \code{\link{getset.ff}}, \code{\link{readwrite.ff}} and \code{\link{swap}} for methods that support maintenance of 'na.count', \code{\link{NA}}, \code{\link[bit:Metadata]{is.sorted}} for yet another \code{\link[=Extract.ff]{physical}} attribute }
\examples{
  message("--- ff examples ---")
  x <- ff(1:12)
  na.count(x)
  message("activate the 'na.count' physical attribute and set the current na.count manually")
  na.count(x) <- 0L
  message("add one NA with a method that maintains na.count")
  swap(x, NA, 1)
  na.count(x)
  message("remove the 'na.count' physical attribute (and stop automatic maintenance)")
  na.count(x) <- NULL
  message("activate the 'na.count' physical attribute and have ff automatically 
calculate the current na.count")
  na.count(x) <- TRUE
  na.count(x)
  message("--- ram examples ---")
  x <- 1:12
  na.count(x)
  x[1] <- NA
  message("activate the 'na.count' physical attribute and have R automatically 
calculate the current na.count")
  na.count(x) <- TRUE
  na.count(x)
  message("remove the 'na.count' physical attribute (and stop automatic maintenance)")
  na.count(x) <- NULL
  na.count(x)
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
