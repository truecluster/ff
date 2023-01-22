\name{ffinfo}
\alias{ffinfo}
\title{
  Inspect content of ff saves
}
\description{
  Find out which objects and ff files are in a pair of files saved with \code{\link{ffsave}}
}
\usage{
ffinfo(file)
}
\arguments{
  \item{file}{
  a character string giving the name (without extension) of the \code{.RData} and \code{.ffData} files to load
}
}
\value{
  a list with components
  \item{RData}{a list, one element for each object (named like the object): a character vector with the names of the ff files }
  \item{ffData}{a list, one element for each path (names like the path): a character vector with the names of the ff files }
  \item{rootpath}{ the root path relative to which the files are stored in the .ffData zip }
}
\author{
  Jens Oehlschlägel
}
\note{
  For large files and the zip64 format use \code{zip 3.0} and \code{unzip 6.0} from \url{https://infozip.sourceforge.net/}.
}
\seealso{
  \code{\link{ffsave}}, \code{\link{ffload}}, \code{\link{ffdrop}}
}
\keyword{ IO }
\keyword{file}
