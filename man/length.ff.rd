\name{length.ff}
\alias{length.ff}
\alias{length<-.ff}
\title{ Getting and setting length }
\description{
  Gets and sets length of ff objects.
}
\usage{
\method{length}{ff}(x)
\method{length}{ff}(x) <- value
}
\arguments{
  \item{x}{ object to query }
  \item{value}{ new object length }
}
\details{
  Changing the length of ff objects is only allowed if no \code{\link{vw}} is used.
  Changing the length of ff objects will remove any \code{\link{dim.ff}} and \code{\link{dimnames.ff}} attribute.
  Changing the length of ff objects will remove any \code{\link[bit]{na.count}} or \code{\link[bit:Metadata]{is.sorted}} attribute and warn about this.
  New elements are usually zero, but it may depend on OS and filesystem what they really are.
  If you want standard R behaviour: filling with NA ,you need to do this yourself.
  As an exception to this rule, ff objects with \code{\link{names.ff}} will be filled with NA's automatically,
  and the length of the names will be adjusted (filled with position numbers where needed, which can easily consume a lot of RAM,
  therefore removing 'names' will help to faster increase length without RAM problems).
}
\note{
  Special care needs to be taken with regard ff objects that represent factors.
  For ff factors based on UNSIGNED \code{\link{vmode}s}, new values of zero are silently interpreted as the first factor level.
  For ff factors based on SIGNED \code{\link{vmode}s}, new values of zero result in illegal factor levels.
  See \code{\link{nrow<-}}.
}
\value{
  Integer scalar
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{length}}, \code{\link{maxlength}}, \code{\link{file.resize}}, \code{\link[=dim.ff]{dim}}, \code{\link[=Extract.ff]{virtual}} }
\examples{
  x <- ff(1:12)
  maxlength(x)
  length(x)
  length(x) <- 10
  maxlength(x)
  length(x)
  length(x) <- 16
  maxlength(x)
  length(x)
  rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
\keyword{ attribute }
