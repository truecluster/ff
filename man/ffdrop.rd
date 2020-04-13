\name{ffdrop}
\alias{ffdrop}
\title{
  Delete an ffarchive
}
\description{
  Delete the \code{<file>.Rdata} and \code{<file>.ffData} files behind an \code{ffarchive}
}
\usage{
ffdrop(file)
}
\arguments{
  \item{file}{
  vector of archive filenames (without extensions)
}
}
\value{
  A list with components
  \item{RData}{vector with results of \code{\link{file.remove}} on RData files }
  \item{ffData}{Description of 'comp2'}
}
\author{
  Jens Oehlschlägel
}
\note{
  This deletes file on disk without warning
}
\seealso{
  \code{\link{ffsave}}, \code{\link{ffinfo}}, \code{\link{ffload}}
}
\keyword{ IO }
\keyword{file}
