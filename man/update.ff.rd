\name{update.ff}
\alias{update.ff}
\alias{update.ffdf}
\title{ Update ff content from another object }
\description{
  \command{update} copies updates one ff object with the content of another object.
}
\usage{
\method{update}{ff}(object, from, delete = FALSE, bydim = NULL, fromdim = NULL
, BATCHSIZE = .Machine$integer.max, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE, \dots)
\method{update}{ffdf}(object, from, \dots)
}
\arguments{
  \item{object}{ an ff object to which to update }
  \item{from}{ an object from which to uodate  }
  \item{delete}{ NA for quick update with file-exchange, TRUE for quick update with deleting the 'from' object after the update, can speed up updating significantly }
  \item{bydim}{ how to interpret the content of the object, see \code{\link{ff}} }
  \item{fromdim}{ how to interpret the content of the 'from' object, see \code{\link{ff}} }
  \item{BATCHSIZE}{ \code{BATCHSIZE} }
  \item{BATCHBYTES}{ \code{BATCHBYTES} }
  \item{VERBOSE}{ \code{VERBOSE} }
  \item{\dots}{ further arguments }
}
\details{
  If the source object \code{is.ff} and not \code{delete=FALSE} then instead of slow copying we - if possible - try to swap and rename the files behind the ff objects.
  Quick update requires that the two ff objects are \code{\link{vectorCompatible}},
  that both don't use \code{\link{vw}},
  that they have identical \code{\link{maxlength}}
  and identical \code{\link{levels.ff}}.
}
\note{
  You don't have a guarantee that with \code{delete=TRUE} the 'from' object gets deleted or with \code{delete=NA} the 'from' objects carries the content of 'object'.
  Such expectations only turn true if really a quick update was possible.
}
\value{
  An ff object like the input 'object' updated with the content of the 'from' object.
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ff}}, \code{\link[=clone.ff]{clone}}, \code{\link{ffvecapply}}, \code{\link{vectorCompatible}}, \code{\link{filename}} }
\examples{
  x <- ff(1:100)
  y <- ff(-(1:100))
  message("You should make it a habit to re-assign the return value 
of update although this is not needed currently.")
  x <- update(x, from=y)
  x
  y
  x[] <- 1:100
  x <- update(x, from=y, delete=NA)
  x
  y
  x <- update(x, from=y, delete=TRUE)
  x
  y
  x
  rm(x,y); gc()

  \dontrun{
    message("timings")
    x <- ff(1:10000000)
    y <- ff(-(1:10000000))
    system.time(update(x, from=y))
    system.time(update(y, from=x, delete=NA))
    system.time(update(x, from=y, delete=TRUE))
    rm(x,y); gc()
  }

}
\keyword{ IO }
\keyword{ data }
