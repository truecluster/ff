\name{ffdf}
\Rdversion{1.1}
\alias{ffdf}
\title{
ff class for data.frames
}
\description{
Function 'ffdf' creates ff data.frames stored on disk very similar to 'data.frame'
}
\usage{
ffdf(...
, row.names = NULL
, ff_split = NULL
, ff_join = NULL
, ff_args = NULL
, update = TRUE
, BATCHSIZE = .Machine$integer.max
, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE)
}
\arguments{
  \item{\dots}{
\code{\link{ff}} vectors or matrices (optionally wrapped in \code{I()} that shall be bound together to an ffdf object
}
  \item{row.names}{
A \code{\link{character}} vector. Not recommended for large objects with many rows.
}
  \item{ff_split}{
A vector of character names or integer positions identifying input components to physically split into single ff_vectors.
If vector elements have names, these are used as root name for the new ff files.
}
  \item{ff_join}{
A list of vectors with character names or integer positions identifying input components to physically join in the same ff matrix.
If list elements have names, these are used to name the new ff files.
}
  \item{update}{
By default (TRUE) new ff files are updated with content of input ff objects. Setting to FALSE prevents this update.
}
  \item{ff_args}{
a list with further arguments passed to \code{\link{ff}} in case that new ff objects are created via 'ff_split' or 'ff_join'
}
\item{BATCHSIZE}{
  passed to \code{\link{update.ff}}
}
  \item{BATCHBYTES}{
  passed to \code{\link{update.ff}}
}
  \item{VERBOSE}{
  passed to \code{\link{update.ff}}
}
}
\details{
By default, creating an 'ffdf' object will NOT create new ff files, instead existing files are referenced.
This differs from \code{\link{data.frame}}, which always creates copies of the input objects,
most notably in \code{data.frame(matrix())}, where an input matrix is converted to single columns.
ffdf by contrast, will store an input matrix physically as the same matrix and virtually map it to columns.
Physically copying a large ff matrix to single ff vectors can be expensive.
More generally, ffdf objects have a \code{\link[=Extract.ffdf]{physical}} and a \code{\link[=Extract.ffdf]{virtual}} component,
which allows very flexible dataframe designs: a physically stored matrix can be virtually mapped to single columns,
a couple of physically stored vectors can be virtually mapped to a single matrix.
The means to configure these are \code{\link{I}} for the virtual representation and the 'ff_split' and 'ff_join'
arguments for the physical representation. An ff matrix wrapped into 'I()' will return the input matrix as a single object,
using 'ff_split' will store this matrix as single vectors - and thus create new ff files.
'ff_join' will copy a couple of input vectors into a unified new ff matrix with \code{dimorder=c(2,1)},
but virtually they will remain single columns. The returned ffdf object has also a \code{\link[=dimorder.ffdf]{dimorder}} attribute,
which indicates whether the ffdf object contains a matrix with non-standard dimorder \code{c(2,1)}, see \code{\link{dimorderStandard}}. \cr
Currently, \code{\link[=vw]{virtual windows}} are not supported for ffdf.
}
\section{Methods}{
 The following methods and functions are available for ffdf objects:
 \tabular{lrll}{
  \emph{ Type} \tab  \emph{ Name }  \tab \emph{ Assign }  \tab \emph{Comment}  \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Basic functions}  \cr
  function \tab  \code{\link{ffdf}}                       \tab \emph{ }  \tab constructor for ffdf objects \cr
  generic  \tab  \code{\link[=update.ffdf]{update}}       \tab \emph{ }  \tab updates one ffdf object with the content of another \cr
  generic  \tab  \code{\link[=clone.ffdf]{clone}}         \tab \emph{ }  \tab clones an ffdf object \cr
  method   \tab  \code{\link[=print.ffdf]{print}}         \tab \emph{ }  \tab print ffdf \cr
  method   \tab  \code{\link[=str.ffdf]{str}}             \tab \emph{ }  \tab ffdf object structure \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Class test and coercion}  \cr
  function \tab  \code{\link{is.ffdf}}                    \tab \emph{ }  \tab check if inherits from ff \cr
  generic  \tab  \code{\link{as.ffdf}}                    \tab \emph{ }  \tab coerce to ff, if not yet \cr
  generic  \tab  \code{\link[=as.data.frame.ffdf]{as.data.frame}}              \tab \emph{ }  \tab coerce to ram data.frame\cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Virtual storage mode} \cr
  generic  \tab  \code{\link[=vmode.ffdf]{vmode}}         \tab \code{ }  \tab get virtual modes for all (virtual) columns \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Physical attributes}  \cr
  function \tab  \code{\link[=Extract.ffdf]{physical}}   \tab \code{ }  \tab get physical attributes \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Virtual attributes} \cr
  function \tab  \code{\link[=Extract.ffdf]{virtual}}     \tab \code{ } \tab get virtual attributes \cr
  method   \tab  \code{\link[=length.ffdf]{length}}       \tab \code{ }  \tab get length \cr
  method   \tab  \code{\link[=dim.ffdf]{dim }}            \tab \code{<-} \tab get dim and set nrow \cr
  generic  \tab  \code{\link[=dimorder.ffdf]{dimorder}}   \tab \code{ }  \tab get the dimorder (non-standard if any component is non-standard) \cr
  method   \tab  \code{\link[=names.ffdf]{names}}         \tab \code{<-} \tab set and get names \cr
  method   \tab  \code{\link[=dimnames.ffdf]{row.names}}  \tab \code{<-} \tab set and get row.names \cr
  method   \tab  \code{\link[=dimnames.ffdf]{dimnames}}   \tab \code{<-} \tab set and get dimnames \cr
  method   \tab  \code{\link[=filename]{pattern}}         \tab \code{<-} \tab set pattern (rename/move files) \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Access functions}  \cr
  method   \tab  \code{\link[=[.ffdf]{[}}                 \tab \emph{<-} \tab set and get data.frame content (\code{[,]}) or get ffdf with less columns (\code{[]}) \cr
  method   \tab  \code{\link[=[[.ffdf]{[[}}               \tab \emph{<-} \tab set and get single column ff object \cr
  method   \tab  \code{\link[=$.ffdf]{$}}                 \tab \emph{<-} \tab set and get single column ff object \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Opening/Closing/Deleting}                                             \cr
  generic  \tab  \code{\link[=is.open.ffdf]{is.open}}     \tab \emph{ }  \tab tri-bool is.open status of the physical ff components \cr
  method   \tab  \code{\link[=open.ffdf]{open}}           \tab \emph{ }  \tab open all physical ff objects (is done automatically on access) \cr
  method   \tab  \code{\link[=close.ffdf]{close}}         \tab \emph{ }  \tab close all physical ff objects \cr
  method   \tab  \code{\link[=delete.ffdf]{delete}}       \tab \emph{ }  \tab deletes all physical ff files \cr
  method   \tab  \code{\link[=finalize.ffdf]{finalize}}   \tab \emph{ }  \tab call finalizer \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{processing}                                             \cr
  method   \tab  \code{\link[=chunk.ffdf]{chunk}}         \tab \emph{ }  \tab create chunked index \cr
  method   \tab  \code{\link[=sortLevels.ffdf]{sortLevels}} \tab \emph{ }  \tab sort and recode levels \cr
  \emph{ } \tab  \emph{ }                                 \tab \emph{ }  \tab \bold{Other}                                                     \cr
  }
}
\value{
A list with components
\item{physical}{the underlying ff vectors and matrices, to be accessed via \code{\link[=Extract.ffdf]{physical}}}
\item{virtual}{the virtual features of the ffdf including the virtual-to-physical mapping, to be accessed via \code{\link[=Extract.ffdf]{virtual}}}
\item{row.names}{the optional row.names, see argument row.names}
and class 'ffdf' (NOTE that ffdf dows not inherit from ff)
}
\author{
Jens Oehlschlägel
}
\note{
Note that in theory, accessing a chunk of rows from a matrix with \code{dimorder=c(2,1)} should be faster than accessing across a bunch of vectors.
However, at least under windows, the OS has difficulties filecaching parts from very large files, therefore - until we have partitioning - the recommended physical storage is in single vectors.
}
\seealso{
  \code{\link{data.frame}}, \code{\link{ff}}, for more example see \code{\link[=Extract.ffdf]{physical}}
}
\examples{
 m <- matrix(1:12, 3, 4, dimnames=list(c("r1","r2","r3"), c("m1","m2","m3","m4")))
 v <- 1:3
 ffm <- as.ff(m)
 ffv <- as.ff(v)

 d <- data.frame(m, v)
 ffd <- ffdf(ffm, v=ffv, row.names=row.names(ffm))
 all.equal(d, ffd[,])
 ffd
 physical(ffd)

 d <- data.frame(m, v)
 ffd <- ffdf(ffm, v=ffv, row.names=row.names(ffm), ff_split=1)
 all.equal(d, ffd[,])
 ffd
 physical(ffd)

 d <- data.frame(m, v)
 ffd <- ffdf(ffm, v=ffv, row.names=row.names(ffm), ff_join=list(newff=c(1,2)))
 all.equal(d, ffd[,])
 ffd
 physical(ffd)

 d <- data.frame(I(m), I(v))
 ffd <- ffdf(m=I(ffm), v=I(ffv), row.names=row.names(ffm))
 all.equal(d, ffd[,])
 ffd
 physical(ffd)

 rm(ffm,ffv,ffd); gc()
}
\keyword{ IO }
\keyword{ data }
