\name{as.ffdf}
\Rdversion{1.1}
\alias{as.ffdf}
\alias{as.ffdf.ff_vector}
\alias{as.ffdf.ff_matrix}
\alias{as.ffdf.data.frame}
\alias{as.data.frame.ffdf}
\title{
Coercing to ffdf and data.frame
}
\description{
  Functions for coercing to ffdf and data.frame
}
\usage{
as.ffdf(x, ...)
\method{as.ffdf}{ff_vector}(x, ...)
\method{as.ffdf}{ff_matrix}(x, ...)
\method{as.ffdf}{data.frame}(x, vmode=NULL, col_args = list(), ...)
\method{as.data.frame}{ffdf}(x, ...)
}
\arguments{
  \item{x}{ the object to be coerced }
  \item{vmode}{ optional specification of the \code{\link{vmode}s} of columns of the \code{\link{data.frame}}. Either a character vector of vmodes (named with column names of the data.frame or recycled if not named)
                or a list named with vmodes where each element identifies those columns of the data.frame that should get the vmode encoded in the name of the element }
  \item{col_args}{ further arguments; passed to \code{\link{ff}}  }
  \item{\dots}{ further arguments; passed to \code{\link{ffdf}} for .ff_vector, .ff_matrix and .data.frame methods, ignored for .ffdf identity method }
}
\value{
  'as.ffdf' returns an object of class \code{\link{ffdf}}, 'as.data.frame' returns an object of class \code{\link{data.frame}}
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{is.ffdf}}, \code{\link{ffdf}}, \code{\link{data.frame}}
}
\examples{
  d <- data.frame(x=1:26, y=letters, z=Sys.time()+1:26, stringsAsFactors = TRUE)
  ffd <- as.ffdf(d)
  stopifnot(identical(d, as.data.frame(ffd)))
  rm(ffd); gc()
}
\keyword{ IO }
\keyword{ data }
