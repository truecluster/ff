\name{ffload}
\alias{ffload}
\title{
 Reload ffSaved Datasets
}
\description{
  Reload datasets written with the function \code{ffsave} or \code{ffsave.image} .
}
\usage{
ffload(file, list = character(0L), envir = parent.frame()
, rootpath = NULL, overwrite = FALSE)
}
\arguments{
  \item{file}{
  a character string giving the name (without extension) of the \code{.RData} and \code{.ffData} files to load
}
  \item{list}{
  An optional vector of names selecting those objects to be restored (default NULL restores all)
}
  \item{envir}{
  the environment where the data should be loaded.
}
  \item{rootpath}{
  an optional rootpath where to restore the ff files (default NULL restores in the original location)
}
  \item{overwrite}{
  logical indicating whether possibly existing ff files shall be overwritten
}
}
\details{
  \code{\link{ffinfo}} can be used to inspect the contents an ffsaved pair of \code{.RData} and \code{.ffData} files.
  Argument \code{list} can then be used to restore only part of the ffsave.
}
\value{
  A character vector with the names of the restored ff files
}
\note{
  The ff files are not platform-independent with regard to byte order.
  For large files and the zip64 format use \code{zip 3.0} and \code{unzip 6.0} from \url{https://infozip.sourceforge.net//}.
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{load}}, \code{\link{ffsave}}, \code{\link{ffinfo}}, \code{\link{ffdrop}}
}
\keyword{ IO }
\keyword{file}
