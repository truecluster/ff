\name{finalize}
\Rdversion{1.1}
\alias{finalize}
\alias{finalize.ff_pointer}
\alias{finalize.ff}
\alias{finalize.ffdf}
\title{
  Call finalizer
}
\description{
  This calls the currently assigned finalizer, either via R's finalization mechanism or manually.
}
\usage{
finalize(x, ...)
\method{finalize}{ff_pointer}(x, ...)
\method{finalize}{ff}(x, ...)
\method{finalize}{ffdf}(x, ...)
}
\arguments{
  \item{x}{ either an \code{\link{ff}} or \code{\link{ffdf}} object or an \code{ff_pointer}, see details }
  \item{\dots}{ currently ignored }
}
\details{
  The \code{finalize.ff_pointer} method is called from R after it had been passed to \code{\link{reg.finalizer}}. It will set the finalizer name to \code{NULL} and call the finalizer.
  \cr
  The \code{finalize} generic can be called manually on \code{\link{ff}} or \code{\link{ffdf}} objects. It will call the finalizer but not touch the finalizer name.
  \cr
  For more details see \code{\link{finalizer}}
}
\note{
  \code{finalize.ff_pointer} MUST NEVER be called manually - neither directly nor by calling the generic on an ff_pointer (could erroneously signal that there is no pending finalization lurking around)
}
\value{
  returns whatever the called finalizer returns, for ffdf a list with the finalization returns of each physical component is returned.
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{finalizer}}
}
\examples{
  x <- ff(1:12, pattern="./finalizerdemo")
  fnam <- filename(x)
  finalizer(x)
  is.open(x)
  file.exists(fnam)

  finalize(x)

  finalizer(x)
  is.open(x)
  file.exists(fnam)

  delete(x)
  finalizer(x)
  is.open(x)
  file.exists(fnam)

  rm(x)
  gc()
}
\keyword{ IO }
