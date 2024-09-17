\name{as.ff.bit}
\Rdversion{1.1}
\alias{as.ff.bit}
\alias{as.bit.ff}
\title{
  Conversion between bit and ff boolean
}
\description{
  Function \code{as.ff.bit} converts a \code{\link[bit]{bit}} vector to a boolean \code{\link{ff}} vector.
  Function \code{as.bit.ff} converts a boolean \code{\link{ff}} vector to a \code{\link{ff}} vector.
}
\usage{
\method{as.ff}{bit}(x, filename = NULL, overwrite = FALSE, \dots)
\method{as.bit}{ff}(x, \dots)
}
\arguments{
  \item{x}{ the source of conversion }
  \item{filename}{ optionally a desired filename }
  \item{overwrite}{ logical indicating whether we allow overwriting the target file }
  \item{\dots}{ further arguments passed to ff in case \code{as.ff.bit}, ignored in case of \code{as.bit.ff} }
}
\details{
  The data are copied bot bit-wise but integerwise, therefore these conversions are very fast.
  \code{as.bit.ff}  will attach the ff filename to the bit vector, and \code{as.ff.bit} will - if attached - use THIS filename and SILENTLY overwrite this file.
}
\note{
  NAs are mapped to TRUE in 'bit' and to FALSE in 'ff' booleans. Might be aligned in a future release. Don't use bit if you have NAs - or map NAs explicitely.
}
\value{
  A vector of the converted type
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link[bit]{bit}}, \code{\link{ff}}, \code{\link{as.ff}}, \code{\link{as.hi.bit}}
}
\examples{
  l <- as.boolean(sample(c(FALSE,TRUE), 1000, TRUE))

  b <- as.bit(l)
  stopifnot(identical(l,b[]))
  b
  f <- as.ff(b)
  stopifnot(identical(l,f[]))
  f
  b2 <- as.bit(f)
  stopifnot(identical(l,b2[]))
  b2
  f2 <- as.ff(b2)
  stopifnot(identical(filename(f),filename(f2)))
  stopifnot(identical(l,f2[]))
  f
  rm(f,f2); gc()
}
\keyword{ classes }
\keyword{ logic }
\keyword{ IO }
\keyword{ data }
