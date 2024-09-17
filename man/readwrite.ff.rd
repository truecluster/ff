\name{readwrite.ff}
\alias{read.ff}
\alias{write.ff}
\alias{readwrite.ff}
\title{ Reading and writing vectors (low-level) }
\description{
  Simpe low-level interface for reading and writing vectors from ff files.
}
\usage{
read.ff(x, i, n)
write.ff(x, i, value, add = FALSE)
readwrite.ff(x, i, value, add = FALSE)
}
\arguments{
  \item{x}{ an ff object }
  \item{i}{ a start position in the ff file }
  \item{n}{ number of elements to read }
  \item{value}{ vector of elements to write }
  \item{add}{ TRUE if the values should rather increment than overwrite at the target positions }
}
\details{
  \command{readwrite.ff} combines the effects of \command{read.ff} and \command{write.ff} in a single operation: it retrieves the old values starting from position \code{i} before changing them.
  \command{getset.ff} will maintain \code{\link[bit]{na.count}}.
}
\value{
  \command{read.ff} returns a vector of values, \command{write.ff} returns the 'changed' ff object (like all assignment functions do) and \command{readwrite.ff} returns the values at the target position.
  More precisely \code{readwrite.ff(x, i, value, add=FALSE)} returns the old values at the position \code{i} while \code{readwrite.ff(x, i, value, add=TRUE)} returns the incremented values of \code{x}.
}
\author{ Jens Oehlschlägel }
\note{ \command{read.ff}, \command{write.ff} and \command{readwrite.ff} are low level functions that do not support \code{ramclass} and \code{ramattribs} and thus will not give the expected result with \code{factor} and \code{POSIXct} }
\seealso{ \code{\link{getset.ff}} for low-level scalar access and \code{\link{[.ff}} for high-level access }
\examples{
  x <- ff(0, length=12)
  read.ff(x, 3, 6)
  write.ff(x, 3, rep(1, 6))
  x
  write.ff(x, 3, rep(1, 6), add=TRUE)
  x
  readwrite.ff(x, 3, rep(1, 6), add=TRUE)
  readwrite.ff(x, 3, rep(1, 6))
  x
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
