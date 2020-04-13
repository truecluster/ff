\name{as.vmode}
\alias{as.vmode}
\alias{as.vmode.default}
\alias{as.vmode.ff}
\alias{as.boolean}
\alias{as.boolean.default}
\alias{as.quad}
\alias{as.quad.default}
\alias{as.nibble}
\alias{as.nibble.default}
\alias{as.byte}
\alias{as.byte.default}
\alias{as.ubyte}
\alias{as.ubyte.default}
\alias{as.short}
\alias{as.short.default}
\alias{as.ushort}
\alias{as.ushort.default}
\title{ Coercing to virtual mode }
\description{
  \command{as.vmode} is a generic that converts some R ram object to the desired \code{\link{vmode}}.
}
\usage{
as.vmode(x, ...)
as.boolean(x, ...)
as.quad(x, ...)
as.nibble(x, ...)
as.byte(x, ...)
as.ubyte(x, ...)
as.short(x, ...)
as.ushort(x, ...)
\method{as.vmode}{default}(x, vmode, \dots)
\method{as.vmode}{ff}(x, \dots)
\method{as.boolean}{default}(x, ...)
\method{as.quad}{default}(x, ...)
\method{as.nibble}{default}(x, ...)
\method{as.byte}{default}(x, ...)
\method{as.ubyte}{default}(x, ...)
\method{as.short}{default}(x, ...)
\method{as.ushort}{default}(x, ...)
}
\arguments{
  \item{x}{ any object }
  \item{vmode}{ virtual mode }
  \item{\dots}{ The \code{\dots} don't have a function yet, they are only defined to keep the generic flexible. }
}
\details{
 Function \command{as.vmode} actually coerces to one of the usual \code{\link{storage.mode}s} (see \code{\link{.rammode}}) but flags them with an additional attribute 'vmode' if necessary.
 The coercion generics can also be called directly:
 \tabular{rl}{
  \code{as.boolean}    \tab  1 bit logical without NA \cr
  \code{as.logical}    \tab  2 bit logical with NA \cr
  \code{as.quad}       \tab  2 bit unsigned integer without NA \cr
  \code{as.nibble}     \tab  4 bit unsigned integer without NA \cr
  \code{as.byte}       \tab  8 bit signed integer with NA      \cr
  \code{as.ubyte}      \tab  8 bit unsigned integer without NA \cr
  \code{as.short}      \tab 16 bit signed integer with NA      \cr
  \code{as.ushort}     \tab 16 bit unsigned integer without NA \cr
  \code{as.integer}    \tab 32 bit signed integer with NA      \cr
  \code{as.single}     \tab 32 bit float \cr
  \code{as.double}     \tab 64 bit float \cr
  \code{as.complex}    \tab 2x64 bit float \cr
  \code{as.raw}        \tab 8 bit unsigned char \cr
  \code{as.character}  \tab character \cr
 }
}
\value{
  a vector of the desired vmode containing the input data
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{vmode}}, \code{\link{vector.vmode}} }
\examples{
  as.vmode(1:3,"double")
  as.vmode(1:3,"byte")
  as.double(1:3)
  as.byte(1:3)
}
\keyword{ IO }
\keyword{ data }
\keyword{ attribute }
