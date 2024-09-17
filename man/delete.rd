\name{delete}
\alias{delete}
\alias{delete.ff}
\alias{delete.ffdf}
\alias{delete.ff_pointer}
\alias{delete.default}
\alias{deleteIfOpen}
\alias{deleteIfOpen.ff}
\alias{deleteIfOpen.ff_pointer}
\title{ Deleting the file behind an ff object }
\description{
  The generic \command{delete} deletes the content of an object without removing the object itself.
  The generic \command{deleteIfOpen} does the same, but only if \code{\link{is.open}} returns TRUE.
}
\usage{
delete(x, \dots)
deleteIfOpen(x, \dots)
\method{delete}{ff}(x, \dots)
\method{delete}{ffdf}(x, \dots)
\method{delete}{ff_pointer}(x, \dots)
\method{delete}{default}(x, \dots)
\method{deleteIfOpen}{ff}(x, \dots)
\method{deleteIfOpen}{ff_pointer}(x, \dots)
}
\arguments{
  \item{x}{ an ff or ram object }
  \item{\dots}{ further arguments (not used) }
}
\details{
  The proper sequence to fully delete an ff object is: \code{delete(x);rm(x)}, where \command{delete.ff} frees the Memory Mapping resources and deletes the ff file,
  leaving intact the R-side object including its \code{\link{class}}, \code{\link[=Extract.ff]{physical}} and \code{\link[=Extract.ff]{virtual}} attributes.
  The default method is a compatibility function doing something similar with ram objects: by assiging an empty list to the name of the ram object to the parent frame
  we destroy the content of the object, leaving an empty stub that prevents raising an error if the parent frame calls the \code{delete(x);rm(x)} sequence. \cr
  The \command{deleteIfOpen} does the same as \command{delete} but protects closed ff objects from deletion, it is mainly intended for use through a finalizer, as are the \code{ff_pointer} methods.
}
\value{
  \command{delete} returns TRUE if the/all ff files could be removed and FALSE otherwise. \cr
  \command{deleteIfOpen} returns TRUE if the/all ff files could be removed, FALSE if not and NA if the ff object was open.
}
\author{ Jens Oehlschlägel }
\note{
  Deletion of ff files can be triggerd automatically via three routes:
  \enumerate{
    \item if an ff object with a 'delete' finalizer is removed
    \item if an ff object was created with \code{fffinonexit=TRUE} the finalizer is also called when R shuts down.
    \item if an ff object was created in \code{getOption("fftempdir")}, it will be unlinked together with the fftempdir \code{\link[base:ns-hooks]{.onUnload}}
  }
  Thus in order to retain an ff file, one has to create it elsewhere than in fftempdir with a finalizer that does not destroy the file (by default files outside fftempdir get a 'close' finalizer') i.e. one of the following:
  \enumerate{
    \item name the file AND use \code{fffinalizer="close"}
    \item name the file AND use \code{fffinalizer="deleteIfOpen"} AND close the ff object before leaving R
    \item name the file AND use \code{fffinalizer="delete"} AND use \code{fffinonexit=FALSE}
  }
}
\seealso{ \code{\link{ff}}, \code{\link{close.ff}}, \code{\link{open.ff}}, \code{\link{reg.finalizer}} }
\examples{
  message('create the ff file outside getOption("fftempir"), 
    it will have default finalizer "close", so you need to delete it explicitely')
  x <- ff(1:12, pattern="./ffexample")
  delete(x)
  rm(x)
}
\keyword{ IO }
\keyword{ data }
