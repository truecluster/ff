\name{vector.vmode}
\alias{vector.vmode}
\alias{vector.vmode.default}
\alias{vector.vmode.ff}
\alias{boolean}
\alias{quad}
\alias{nibble}
\alias{byte}
\alias{ubyte}
\alias{short}
\alias{ushort}
\title{ Create vector of virtual mode }
\description{
  \command{vector.vmode} creates a vector of a given vmode and length
}
\usage{
vector.vmode(vmode = "logical", length = 0)
boolean(length = 0)
quad(length = 0)
nibble(length = 0)
byte(length = 0)
ubyte(length = 0)
short(length = 0)
ushort(length = 0)
}
\arguments{
  \item{vmode}{ virtual mode }
  \item{length}{ desired length }
}
\details{
 Function \command{vector.vmode} creates the vector in one of the usual \code{\link{storage.mode}s} (see \code{\link{.rammode}}) but flags them with an additional attribute 'vmode' if necessary.
 The creators can also be used directly:
 \tabular{rl}{
  \code{boolean}    \tab  1 bit logical without NA \cr
  \code{logical}    \tab  2 bit logical with NA \cr
  \code{quad}       \tab  2 bit unsigned integer without NA \cr
  \code{nibble}     \tab  4 bit unsigned integer without NA \cr
  \code{byte}       \tab  8 bit signed integer with NA      \cr
  \code{ubyte}      \tab  8 bit unsigned integer without NA \cr
  \code{short}      \tab 16 bit signed integer with NA      \cr
  \code{ushort}     \tab 16 bit unsigned integer without NA \cr
  \code{integer}    \tab 32 bit signed integer with NA       \cr
  \code{single}     \tab 32 bit float \cr
  \code{double}     \tab 64 bit float \cr
  \code{complex}    \tab 2x64 bit float \cr
  \code{raw}        \tab 8 bit unsigned char \cr
  \code{character}  \tab character \cr
 }
}
\value{
 a vector of the desired vmode initialized with 0
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{as.vmode}}, \code{\link{vector}} }
\examples{
  vector.vmode("byte",12)
  vector.vmode("double",12)
  byte(12)
  double(12)
}
\keyword{ IO }
\keyword{ data }
\keyword{ attribute }
