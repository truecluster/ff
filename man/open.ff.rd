\name{open.ff}
\alias{open.ff}
\alias{open.ffdf}
\title{ Opening an ff file }
\description{
  \command{open.ff} opens an ff file, optionally marking it readonly and optionally specifying a caching scheme.
}
\usage{
 \method{open}{ff}(con, readonly = FALSE, pagesize = NULL, caching = NULL, assert = FALSE, \dots)
 \method{open}{ffdf}(con, readonly = FALSE, pagesize = NULL, caching = NULL, assert = FALSE, \dots)
}
\arguments{
  \item{con}{ an \code{\link{ff}} or \code{\link{ffdf}} object }
  \item{readonly}{ \code{readonly} }
  \item{pagesize}{ number of bytes to use as pagesize or NULL to take the pagesize stored in the \code{\link[=Extract.ff]{physical}} attribute of the ff object, see \code{\link{getalignedpagesize}} }
  \item{caching}{ one of 'mmnoflush' or 'mmeachflush', see \code{\link{ff}} }
  \item{assert}{ setting this to TRUE will give a message if the ff was not open already }
  \item{\dots}{ further arguments (not used) }
}
\details{
  ff objects will be opened automatically when accessing their content and the file is still closed.
  Opening ffdf objects will open all of their \code{\link[=Extract.ffdf]{physical}} components including their \code{\link[=row.names.ffdf]{row.names}} if they are \code{\link{is.ff}}
}
\value{
  TRUE if object could be opened, FALSE if it was opened already (or NA if not all components of an ffdf returned FALSE or TRUE on opening)
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ff}}, \code{\link{close.ff}}, \code{\link{delete}}, \code{\link{deleteIfOpen}}, \code{\link{getalignedpagesize}} }
\examples{
  x <- ff(1:12)
  close(x)
  is.open(x)
  open(x)
  is.open(x)
  close(x)
  is.open(x)
  x[]
  is.open(x)
  y <- x
  close(y)
  is.open(x)
  rm(x,y); gc()
}
\keyword{ IO }
\keyword{ data }
