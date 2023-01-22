\name{ffsave}
\alias{ffsave}
\alias{ffsave.image}
\title{
Save R and ff objects
}
\description{
 \code{ffsave} writes an external representation of R and ff objects to an \code{ffarchive}.
 The objects can be read back from the file at a later date by using the function \code{\link{ffload}}.
}
\usage{
ffsave(...
, list = character(0L)
, file = stop("'file' must be specified")
, envir = parent.frame()
, rootpath = NULL
, add = FALSE
%, overwrite = FALSE
, move = FALSE
, compress = !move
, compression_level = 6
, precheck=TRUE
)
ffsave.image(file = stop("'file' must be specified"), safe = TRUE, ...)
}
\arguments{
  \item{\dots}{
  For \code{ffsave} the names of the objects to be saved (as symbols or character strings),
  for \code{ffsave.image} further arguments passed to \code{ffsave}
}
  \item{list}{
  A character vector containing the names of objects to be saved.
}
  \item{file}{
  A name for the the \code{ffarchive}, i.e. the two files \code{<file>.RData} and \code{<file>.ffData}
}
  \item{envir}{
  environment to search for objects to be saved.
}
  \item{add}{
  logical indicating whether the objects shall be added to the \code{ffarchive} (in this case \code{rootpath} is taken from an existing archive)
}
%  \item{overwrite}{
%  logical indicating whether an existing archive may be overwritten
%}
  \item{move}{
  logical indicating whether ff files shall be moved instead of copied into the \code{<file>.ffData}
}
  \item{compress}{
  logical specifying whether saving to a named file is to use compression.
}
  \item{compression_level}{
  compression level passed to \code{zip}, default 6
}
  \item{rootpath}{
  optional path component that all \emph{all} ff files share and that can be dropped/replaced when calling \code{\link{ffload}}
}
  \item{precheck}{
 logical: should the existence of the objects be checked before starting to save (and in particular before opening the file/connection)?
}
  \item{safe}{
 logical. If \code{TRUE}, a temporary file is used for creating the saved workspace. The temporary file is renamed to \code{<file>.ffData} if the save succeeds.
 This preserves an existing workspace \code{<file>.ffData} if the save fails,
 but at the cost of using extra disk space during the save.
}
}
\details{
  \code{ffsave} stores objects and ff files in an \code{ffarchive} named \code{<file>}:
  i.e. it saves all specified objects via \code{\link{save}} in a file named \code{<file>.RData}
  and saves all ff files related to these objects in a zipfile named \code{<file>.ffData} using an external \code{zip} utility.
  \cr
  By default files are stored relative to the \code{rootpath="\"} and will be restored relative to \code{"\"} (in its original location).
  By providing a partial path prefix via argument \code{rootpath} the files are stored relative to this \code{rootpath}.
  The \code{rootpath} is stored in the \code{<file>.RData} with the name \code{.ff.rootpath}.
  I.e. even if the ff objects were saved with argument \code{rootpath} to \code{ffsave},
  \code{\link{ffload}} by default restores in the original location.
  By using argument \code{rootpath} to \code{ffload} you can restore relative to a different \code{rootpath}
  (and using argument \code{rootpath} to \code{ffsave} gave you shorter relative paths)
  \cr
  By using argument \code{add} in \code{ffsave} you can add more objects to an existing \code{ffarchive}
  and by using argument \code{list} in \code{ffload} you can selectively restore objects.
  \cr
  The content of the \code{ffarchive} can be inspected using \code{\link{ffinfo}} before actually loading any of the objects.
  \cr
  The \code{ffarchive} can be deleted from disk using \code{\link{ffdrop}}.
}
\value{
  a character vector with messages returned from the \code{zip} utility (one for each ff file zipped)
}
\author{
  Jens Oehlschlägel
}
\note{
  The ff files are not platform-independent with regard to byte order.
  For large files and the zip64 format use \code{zip 3.0} and \code{unzip 6.0} from \url{https://infozip.sourceforge.net/}.
}
\seealso{
  \code{\link{ffinfo}} for inspecting the content of the \code{ffarchive} \cr
  \code{\link{ffload}} for loading all or some of the \code{ffarchive} \cr
  \code{\link{ffdrop}} for deleting one or more \code{ffarchives}
}
\examples{
  \dontrun{
  message("let's create some ff objects")
  n <- 8e3
  a <- ff(sample(n, n, TRUE), vmode="integer", length=n, filename="d:/tmp/a.ff")
  b <- ff(sample(255, n, TRUE), vmode="ubyte", length=n, filename="d:/tmp/b.ff")
  x <- ff(sample(255, n, TRUE), vmode="ubyte", length=n, filename="d:/tmp/x.ff")
  y <- ff(sample(255, n, TRUE), vmode="ubyte", length=n, filename="d:/tmp/y.ff")
  z <- ff(sample(255, n, TRUE), vmode="ubyte", length=n, filename="d:/tmp/z.ff")
  df <- ffdf(x=x, y=y, z=z)
  rm(x,y,z)

  message("save all of them")
  ffsave.image("d:/tmp/x")
  str(ffinfo("d:/tmp/x"))

  message("save some of them with shorter relative pathnames ...")
  ffsave(a, b, file="d:/tmp/y", rootpath="d:/tmp")
  str(ffinfo("d:/tmp/y"))

  message("... and add others later")
  ffsave(df, add=TRUE, file="d:/tmp/y", rootpath="d:/tmp")
  str(ffinfo("d:/tmp/y"))

  message("... and add others later")
  system.time(ffsave(a, file="d:/tmp/z", move=TRUE))
  ffinfo("d:/tmp/z")

  message("let's delete/close/remove all objects")
  close(a)  # no file anymore, since we moved a into the ffarchive
  delete(b, df)
  rm(df, a, b, n)
  message("prove it")
  ls()

  message("restore all but ff files in a different directory")
  system.time(ffload("d:/tmp/x", rootpath="d:/tmp2"))
  lapply(ls(), function(i)filename(get(i)))

  delete(a, b, df)
  rm(df, a, b)

  ffdrop(c("d:/tmp/x", "d:/tmp/y", "d:/tmp/z"))
  }
}
\keyword{ IO }
\keyword{file}
