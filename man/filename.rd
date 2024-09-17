\name{filename}
\alias{filename}
\alias{filename.default}
\alias{filename.ff_pointer}
\alias{filename.ffdf}
\alias{filename<-}
\alias{filename<-.ff}
\alias{pattern}
\alias{pattern<-}
\alias{pattern.ff}
\alias{pattern<-.ff}
\alias{pattern<-.ffdf}
\title{ Get or set filename }
\description{
  Get or set filename from ram or \code{\link{ff}} object via the \code{filename} and \code{filename<-} generics
  or rename all files behind a \code{\link{ffdf}} using the \code{pattern<-} generic.
}
\usage{
filename(x, \dots)
filename(x, \dots) <- value
\method{filename}{default}(x, \dots)
\method{filename}{ff_pointer}(x, \dots)
\method{filename}{ffdf}(x, \dots)
\method{filename}{ff}(x, \dots) <- value
pattern(x, \dots)
pattern(x, \dots) <- value
\method{pattern}{ff}(x, \dots)
\method{pattern}{ff}(x, \dots) <- value
\method{pattern}{ffdf}(x, \dots) <- value
}
\arguments{
  \item{x}{ a ram or ff  object, or for pattern assignment only - a ffdf object }
  \item{value}{ a new filename }
  \item{\dots}{ dummy to keep R CMD CHECK quiet }
}
\value{
  \code{filename} and \code{pattern} return a character filename or pattern.
  For \code{\link{ffdf}} returns a list with one filename element for each \code{\link[=Extract.ffdf]{physical}} component.
  The assignment functions return the changed object, which will keep the change even without re-assigning the return-value
}
\details{
  Assigning a \code{filename<-} means renaming the corresponding file on disk - even for ram objects. If that fails, the assignment fails.
  If a file is moved in or out of \code{getOption("fftempdir")} the \code{\link{finalizer}}  is changed accordingly to 'delete' in \code{getOption("fftempdir")} and 'close' otherwise.
  \cr
  A \code{pattern} is an incomplete filename (optional path and optional filename-prefix) that is turned to filenames by
  adding a random string using and optionally an extension from optionally an extension from \code{getOption("ffextension")} (see \code{\link{fftempfile}}).
  \code{filename<-} exhibits R's standard behaviour of considering "filename" and "./filename" both to be located in \code{\link{getwd}}.
  By constrast \code{pattern<-} will create "filename" without path in \code{getOption("fftempdir")} and only "./filename" in \code{\link{getwd}}.
}
\author{ Jens Oehlschlägel }
\seealso{  \code{\link{fftempfile}}, \code{\link{finalizer}}, \code{\link{ff}}, \code{\link{as.ff}}, \code{\link{as.ram}}, \code{\link{update.ff}},  \code{\link{file.move}}}
\examples{
  \dontrun{
  message("Neither giving pattern nor filename gives a random filename 
with extension ffextension in fftempdir")
  x <- ff(1:12)
  finalizer(x)
  filename(x)
  message("Giving a pattern with just a prefix moves to a random filename 
beginning with the prefix in fftempdir")
  pattern(x) <- "myprefix_"
  filename(x)
  message("Giving a pattern with a path and prefix moves to a random filename 
beginning with prefix in path (use . for getwd) ")
  pattern(x) <- "./myprefix"
  filename(x)
  message("Giving a filename moves to exactly this filename and extension 
in the R-expected place) ")
  if (!file.exists("./myfilename.myextension")){
    filename(x) <- "./myfilename.myextension"
    filename(x)
  }

  message("NOTE that the finalizer has changed from 'delete' to 'close': 
now WE are responsible for deleting the file - NOT the finalizer")
  finalizer(x)
  delete(x)
  rm(x)
  }
}
\keyword{ IO }
\keyword{ data }
