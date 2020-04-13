\name{dimnames.ffdf}
\Rdversion{1.1}
\alias{dimnames.ffdf}
\alias{dimnames<-.ffdf}
\alias{names.ffdf}
\alias{names<-.ffdf}
\alias{row.names.ffdf}
\alias{row.names<-.ffdf}
\title{
  Getting and setting dimnames of ffdf
}
\description{
  Getting and setting dimnames, columnnames or rownames
}
\usage{
  \method{dimnames}{ffdf}(x)
  \method{dimnames}{ffdf}(x) <- value
  \method{names}{ffdf}(x)
  \method{names}{ffdf}(x) <- value
  \method{row.names}{ffdf}(x)
  \method{row.names}{ffdf}(x) <- value
}
\arguments{
  \item{x}{ a \code{\link{ffdf}} object }
  \item{value}{ a character vector, or, for dimnames a list with two character vectors }
}
\details{
  It is recommended not to assign row.names to a large ffdf object.
}
\value{
  The assignment function return the changed ffdf object. The other functions return the expected.
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{ffdf}}, \code{\link{dimnames.ff}}, \code{\link{rownames}}, \code{\link{colnames}}
}
\examples{
  ffd <- as.ffdf(data.frame(a=1:26, b=letters, stringsAsFactors = TRUE))
  dimnames(ffd)
  row.names(ffd) <- letters
  dimnames(ffd)
  ffd
  rm(ffd); gc()
}
