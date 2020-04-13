\name{splitPathFile}
\Rdversion{1.1}
\alias{standardPathFile}
\alias{splitPathFile}
\alias{unsplitPathFile}
\alias{tempPathFile}
\alias{fftempfile}
\title{
  Analyze pathfile-strings
}
\description{
  \code{splitPathFile} splits a vector of pathfile-strings into path- and file-components without loss of information.
  \code{unsplitPathFile} restores the original pathfile-string vector.
  \code{standardPathFile} standardizes a vector of pathfile-strings: backslashes are replaced by slashes, except for the first two leading backslashes indicating a network share.
  \code{tempPathFile} returns  - similar to \code{\link{tempfile}} - a vector of filenames given path(s) and file-prefix(es) and an optional extension.
  \code{fftempfile} returns  - similar to \code{tempPathFile} - a vector of filenames following a vector of pathfile patterns that are intrepreted in a ff-specific way.
}
\usage{
splitPathFile(x)
unsplitPathFile(splitted)
standardPathFile(x)
tempPathFile(splitted=NULL, path=splitted$path, prefix=splitted$file, extension=NULL)
fftempfile(x)
}
\arguments{
  \item{x}{ a character vector of pathfile strings }
  \item{splitted}{ a return value from \code{splitPathFile} }
  \item{path}{ a character vector of path components }
  \item{prefix}{ a character vector of file components }
  \item{extension}{ optional extension like "csv" (or NULL) }
}
\details{
  \code{\link{dirname}} and \code{\link{basename}} remove trailing file separators and therefore cannot distinguish pathfile string that contains ONLY a path from a pathfile string that contains a path AND file.
  Therefore \code{\link{file.path}(dirname(pathfile), basename(pathfile))} cannot always restore the original pathfile string.
  \cr
  \code{splitPathFile} decomposes each pathfile string into three parts: a path BEFORE the last file separator, the file separator, the filename component AFTER the last file separator.
  If there is no file separator in the string, \code{splitPathFile} tries to guess whether the string is a path or a file component: ".", ".." and "~" are recognized as path components.
  No tilde expansion is done, see \code{\link{path.expand}}.
  Backslashes are converted to the current \code{\link{.Platform}$file.sep} using \code{splitPathFile} except for the first two leading backslashes indicating a network share.
  \cr
  \code{unsplitPathFile} restores the original pathfile-string vector up to translated backslashes.
  \cr
  \code{tempPathFile} internally uses \code{\link{tempfile}} to create its filenames, if an extension is given it repeats filename creation until none of them corresponds to an existing file.
  \cr
  \code{fftempfile} takes a path-prefix pattern as input, splits it,
  will replace an empty path by \code{getOption("fftempdir")} and will use \code{getOption("ffextension")} as extension.
}
\value{
A list with components
  \item{path}{ a character vector of path components }
  \item{fsep}{ a character vector of file separators or "" }
  \item{file}{ a character vector of file components }
}
\author{
  Jens Oehlschlägel
}
\note{
  There is no gurantee that the path and file components contain valid path- or file-names. Like \code{\link{basename}},  \code{splitPathFile} can return ".", ".." or even "", however, all these make sense as a prefix in tempPathFile.
}
\seealso{
  \code{\link{tempfile}}, \code{\link{dirname}}, \code{\link{basename}}, \code{\link{file.path}}
}
\examples{
  pathfile <- c("", ".", "/.", "./", "./.", "/"
  , "a", "a/", "/a", "a/a", "./a", "a/.", "c:/a/b/c", "c:/a/b/c/"
  , "..", "../", "/..", "../..", "//", "\\\\\\\\a\\\\", "\\\\\\\\a/"
  , "\\\\\\\\a/b", "\\\\\\\\a/b/", "~", "~/", "~/a", "~/a/")
  splitted <- splitPathFile(pathfile)
  restored <- unsplitPathFile(splitted)
  stopifnot(all(gsub("\\\\\\\\","/",restored)==gsub("\\\\\\\\","/",pathfile)))

  dirnam <- dirname(pathfile)
  basnam <- basename(pathfile)

  db  <- file.path(dirnam,basnam)
  ident = gsub("\\\\\\\\","/",db) == gsub("\\\\\\\\","/",pathfile)
  sum(!ident)

  do.call("data.frame", c(list(ident=ident, pathfile=pathfile
   , dirnam=dirnam, basnam=basnam), splitted))

  \dontrun{
    message("show the difference between tempfile and fftempfile")
    do.call("data.frame", c(list(ident=ident, pathfile=pathfile, dirnam=dirnam, basnam=basnam)
, splitted, list(filename=tempPathFile(splitted), fftempfile=fftempfile(pathfile))))

    message("for a single string splitPathFile is slower, 
for vectors of strings it scales much better than dirname+basename")

    system.time(for (i in 1:1000){
      d <- dirname(pathfile)
      b <- basename(pathfile)
    })
    system.time(for (i in 1:1000){
      s <- splitPathFile(pathfile)
    })

    len <- c(1,10,100,1000)
    timings <- matrix(0, 2, length(len), dimnames=list(c("dir.base.name", "splitPathFile"), len))
    for (j in seq(along=len)){
      l <- len[j]
      r <- 10000 / l
      x <- rep("\\\\\\\\a/b/", l)
      timings[1,j] <- system.time(for (i in 1:r){
          d <- dirname(x)
          b <- basename(x)
        })[3]
      timings[2,j] <- system.time(for (i in 1:r){
          s <- splitPathFile(x)
        })[3]
    }
    timings
  }
}
\keyword{file}
