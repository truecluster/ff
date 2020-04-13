\name{vmode}
\alias{vmode}
\alias{vmode.default}
\alias{vmode.ff}
\alias{vmode<-}
\alias{vmode<-.default}
\alias{vmode<-.ff}
\alias{.vmode}
\alias{.vunsigned}
\alias{.vvalues}
\alias{.vimplemented}
\alias{.rammode}
\alias{.ffmode}
\alias{.vmin}
\alias{.vmax}
\alias{.vNA}
\alias{.rambytes}
\alias{.ffbytes}
\alias{.vcoerceable}
\alias{regtest.vmode}
\title{ Virtual storage mode }
\description{
  Function \command{vmode} returns virtual storage modes of 'ram' or 'ff' objects, the generic \command{vmode<-} sets the vmode of ram objects (vmode of ff objects cannot be changed).
}
\usage{
vmode(x, ...)
vmode(x) <- value
\method{vmode}{default}(x, \dots)
\method{vmode}{ff}(x, \dots)
\method{vmode}{default}(x) <- value
\method{vmode}{ff}(x) <- value
 regtest.vmode()
}
\arguments{
  \item{x}{ any object }
  \item{value}{ a vmode from .vmode }
  \item{\dots}{ The \code{\dots} don't have a function yet, they are only defined to keep the generic flexible. }
}
\details{
 \command{vmode} is generic with default and ff methods. The following meta data vectors can be queried by .vmode or .ffmode:
 \tabular{rl}{
  \code{.vmode}         \tab virtual mode \cr
  \code{.vunsigned}     \tab TRUE if unsigned vmode \cr
  \code{.vvalues}       \tab number of possible values (incl. NA) \cr
  \code{.vimplemented}  \tab TRUE if this vmode is available in ff (initialized \code{\link{.onLoad}} and stored in \code{\link{globalenv}} ) \cr
  \code{.rammode}       \tab storage mode of this vmode \cr
  \code{.ffmode}        \tab integer used to code the vmode in C-code \cr
  \code{.vvalues}       \tab number of possible integers incl. NA in this vmode (or NA for other vmodes) \cr
  \code{.vmin}          \tab min integer in this vmode (or NA for other vmodes) \cr
  \code{.vmax}          \tab max integer in this vmode (or NA for other vmodes) \cr
  \code{.vNA}           \tab NA or 0 if no NA for this vmode \cr
  \code{.rambytes}      \tab bytes needed in ram \cr
  \code{.ffbytes}       \tab bytes needed by ff on disk \cr
  \code{.vcoerceable}   \tab list of vectors with those vmodes that can absorb this vmode \cr
 }
 the following functions relate to vmode:
 \tabular{rl}{
  \code{\link{vector.vmode}}   \tab creating (ram) vector of some vmode \cr
  \code{\link{as.vmode}}       \tab generic for coercing to some vmode (dropping other attributes) \cr
  \code{vmode<-}               \tab generic for coercing to some vmode (keeping other attributes) \cr
  \code{\link{maxffmode}}      \tab determine lowest \code{.ffmode} that can absorb all input vmodes without information loss \cr
 }
 some of those call the vmode-specific functions:
 \tabular{lll}{
  \strong{creation}        \tab \strong{coercion}           \tab  \strong{vmode description} \cr
  \code{\link{boolean}}    \tab \code{\link{as.boolean}}    \tab  1 bit logical without NA \cr
  \code{\link{logical}}    \tab \code{\link{as.logical}}    \tab  2 bit logical with NA \cr
  \code{\link{quad}}       \tab \code{\link{as.quad}}       \tab  2 bit unsigned integer without NA \cr
  \code{\link{nibble}}     \tab \code{\link{as.nibble}}     \tab  4 bit unsigned integer without NA \cr
  \code{\link{byte}}       \tab \code{\link{as.byte}}       \tab  8 bit signed integer with NA      \cr
  \code{\link{ubyte}}      \tab \code{\link{as.ubyte}}      \tab  8 bit unsigned integer without NA \cr
  \code{\link{short}}      \tab \code{\link{as.short}}      \tab 16 bit signed integer with NA      \cr
  \code{\link{ushort}}     \tab \code{\link{as.ushort}}     \tab 16 bit unsigned integer without NA \cr
  \code{\link{integer}}    \tab \code{\link{as.integer}}    \tab 32 bit signed integer with NA      \cr
  \code{\link{single}}     \tab \code{\link{as.single}}     \tab 32 bit float \cr
  \code{\link{double}}     \tab \code{\link{as.double}}     \tab 64 bit float \cr
  \code{\link{complex}}    \tab \code{\link{as.complex}}    \tab 2x64 bit float \cr
  \code{\link{raw}}        \tab \code{\link{as.raw}}        \tab 8 bit unsigned char \cr
  \code{\link{character}}  \tab \code{\link{as.character}}  \tab character \cr
 }
}
\value{
  \code{vmode} returns a character scalar from \code{.vmode} or "NULL" for NULL \cr
  \code{rambytes} returns a vector of byte counts required by each of the vmodes
}
\note{ \command{regtest.vmode} checks correctness of some vmode features
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{ff}}, \code{\link{storage.mode}}, \code{\link{mode}} }
\examples{
 data.frame(.vmode=.vmode, .vimplemented=.vimplemented, .rammode=.rammode, .ffmode=.ffmode
, .vmin=.vmin, .vmax=.vmax, .vNA=.vNA, .rambytes=.rambytes, .ffbytes=.ffbytes)
  vmode(1)
  vmode(1L)
  .vcoerceable[["byte"]]
  .vcoerceable[["ubyte"]]
}
\keyword{ IO }
\keyword{ data }
\keyword{ attribute }
