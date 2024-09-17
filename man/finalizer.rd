\name{finalizer}
\Rdversion{1.1}
\alias{finalizer}
\alias{finalizer<-}
\alias{finalizer.ff}
\alias{finalizer<-.ff}
\title{
  Get and set finalizer (name)
}
\description{
  The generic \code{finalizer} allows to get the current finalizer. The generic \code{finalizer<-} allows to set the current finalizer or to change an existing finalizer (but not to remove a finalizer).
}
\usage{
finalizer(x, ...)
finalizer(x, ...) <- value
\method{finalizer}{ff}(x, ...)
\method{finalizer}{ff}(x, ...) <- value
}
\arguments{
  \item{x}{an \code{\link{ff}} object}
  \item{value}{the name of the new finalizer}
  \item{\dots}{ignored}
}
\details{
  If an \code{\link{ff}}  object is created a finalizer is assigned, it has the task to free ressources no longer needed, for example remove the ff file or free the C++ RAM associated with an open ff file.
  The assigned finalizer depends on the location of the ff file:
  if the file is created in \code{getOption(fftempdir)} it is considered considered temporary and has default finalizer \code{\link[=delete.ff]{delete}},
  files created in other locations have default finalizer \code{\link[=close.ff]{close}}.
  The user can override this either by setting \code{options("fffinalizer")} or by using argument \code{finalizer} when creating single \code{ff} objects.
  Available finalizer generics are "close", "delete" and "deleteIfOpen", available methods are \code{\link{close.ff}}, \code{\link{delete.ff}} and \code{\link{deleteIfOpen.ff}}.
  \cr
  In order to be able to change the finalizer before finalization, the finalizer is NOT directly passed to R's finalization mechanism \code{\link{reg.finalizer}} (an active finalizer can never be changed other than be executed).
  Instead the NAME of the desired finalizer is stored in the ff object and \code{\link{finalize.ff_pointer}} is passed to \code{reg.finalizer}.
  \code{finalize.ff_pointer} will at finalization-time determine the desired finalizer and call it.
  \cr
  There are two possible triggers for execution \code{finalize.ff_pointer}:
  \enumerate{
    \item the garbage collection \code{\link{gc}} following removal \code{\link{rm}} of the ff object
    \item closing R if \code{finonexit} was \code{TRUE} at ff creation-time, determined by \code{options("fffinonexit")} and ff argument \code{finonexit}
  }
  Furthermore there are two possible triggers for calling the finalizer
  \enumerate{
    \item an explicit call to \code{\link{finalize}}
    \item an explicit call to one of the finalizers \code{\link[=close.ff]{close}}, \code{\link{delete}} and \code{\link{deleteIfOpen}}
  }
  The user can define custom finalizers by creating a generic function like \code{\link{delete}}, a ff_pointer method like \code{\link{delete.ff_pointer}} and a ff method for manual calls like \code{\link{delete.ff}}. The user then is responsible to take care of two things
  \enumerate{
    \item adequate freeing of ressources
    \item proper maintenance of the finalizer name in the ff object via \code{\link[=Extract.ff]{physical}$finalizer}
  }
  \code{is.null(finalizer(ff))} indicates NO active finalizer, i.e. no pending execution of \code{finalize.ff_pointer} lurking around after call of \code{reg.finalizer}.
  This requires that
  \enumerate{
    \item the \code{ff_pointer} method sets the finalizer name to \code{NULL}
    \item the \code{ff} may change a non-NULL finalizer name to a different name but not change it to NULL
  }
}
\value{
  \code{finalizer} returns the name of the active finalizer or \code{NULL} if no finalizer is active. \cr
  \code{finalizer<-} returns the changed ff object (reassignment of this return value not needed to keep the change).
  If there was no pending call to \code{\link{finalize.ff_pointer}} (\code{is.null(finalizer(ff))}), \code{finalizer<-} will create one by calling \code{reg.finalizer} with the current setting of \code{\link[=Extract.ff]{physical}$finonexit}.
}
\note{
  You can not assign NULL to an active finalizer using \code{finalizer<-} because this would not stop R's finalization mechanism and would carry the risk of assiging MULTIPLE finalization tasks.
}
\author{
  Jens Oehlschlägel
}
\seealso{
  \code{\link{ff}}, \code{\link{finalize}}, \code{\link{reg.finalizer}}
}
\examples{
  x <- ff(1:12, pattern="./finalizerdemo")
  fnam <- filename(x)
  finalizer(x)
  finalizer(x) <- "delete"
  finalizer(x)
  rm(x)
  file.exists(fnam)
  gc()
  file.exists(fnam)
}
\keyword{ IO }
