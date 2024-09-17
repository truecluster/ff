\name{close.ff}
\alias{close.ff}
\alias{close.ffdf}
\alias{close.ff_pointer}
\title{ Closing ff files }
\description{
  Close frees the Memory Mapping resources and closes the ff file without deleting the file data.
}
\usage{
\method{close}{ff}(con, \dots)
\method{close}{ffdf}(con, \dots)
\method{close}{ff_pointer}(con, \dots)
}
\arguments{
  \item{con}{ an open ff object }
  \item{\dots}{ \code{\dots} }
}
\details{
  The \code{ff_pointer} method is not intended for manual use, it is used at finalizer dispatch time.
  Closing ffdf objects will close all of their \code{\link[=Extract.ffdf]{physical}} components including their \code{\link[=row.names.ffdf]{row.names}} if they are \code{\link{is.ff}}
}
\value{
  TRUE if the file could be closed, FALSE if it was closed already (or NA if not all components of an ffdf returned FALSE or TRUE on closing)
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ff}}, \code{\link{open.ff}}, \code{\link{delete}}, \code{\link{deleteIfOpen}} }
\examples{
  x <- ff(1:12)
  close(x)
  x
  open(x)
  x
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
