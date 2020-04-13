\name{write.table.ffdf}
\Rdversion{1.1}
\alias{write.table.ffdf}
\alias{write.csv.ffdf}
\alias{write.csv2.ffdf}
\alias{write.csv}
\alias{write.csv2}
\title{
  Exporting csv files from ff data.frames
}
\description{
  Function \code{write.table.ffdf} writes a \code{\link{ffdf}} object to a separated flat file, very much like (and using) \code{\link{write.table}}.
  It can also work with any convenience wrappers like \code{\link{write.csv}} and provides its own convenience wrapper (e.g. \code{write.csv.ffdf}) for R's usual wrappers.
}
\usage{
write.table.ffdf(x = NULL
, file, append = FALSE
, nrows = -1, first.rows = NULL, next.rows = NULL
, FUN = "write.table", ...
, transFUN = NULL
, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE
)
write.csv.ffdf(...)
write.csv2.ffdf(...)
write.csv(...)
write.csv2(...)
}
\arguments{
  \item{x}{
  a \code{\link{ffdf}} object which to export to the separated file
}
  \item{file}{
  either a character string naming a file or a connection
  open for writing.  \code{""} indicates output to the console.
}
  \item{append}{
  logical. Only relevant if \code{file} is a character
  string.  If \code{TRUE}, the output is appended to the
  file.  If \code{FALSE}, any existing file of the name is destroyed.
}
  \item{nrows}{
  integer: the maximum number of rows to write in (includes first.rows in case a 'first' chunk is read)
  Negative and other invalid values are ignored.
}
\item{first.rows}{
  the number of rows to write with the first chunk (default: next.rows)
}
  \item{next.rows}{
  integer: number of rows to write in further chunks, see details.
  By default calculated as \code{BATCHBYTES \%/\% sum(.rambytes[\link{vmode}(x)])}
}
  \item{FUN}{
  character: name of a function that is called for writing each chunk, see \code{\link{write.table}}, \code{\link{write.csv}}, etc.
}
  \item{\dots}{
  further arguments, passed to \code{FUN} in \code{write.table.ffdf}, or passed to \code{write.table.ffdf} in the convenience wrappers
}
  \item{transFUN}{
  NULL or a function that is called on each data.frame chunk before writing with \code{FUN} (for filtering, transformations etc.)
}
  \item{BATCHBYTES}{
  integer: bytes allowed for the size of the \code{\link{data.frame}} storing the result of reading one chunk. Default \code{getOption("ffbatchbytes")}.
}
  \item{VERBOSE}{
  logical: TRUE to verbose timings for each processed chunk (default FALSE)
}
}
\details{
  \code{write.table.ffdf} has been designed to export very large \code{\link{ffdf}} objects to separated flatfiles in chunks.
  The first chunk is potentially written with col.names. Further chunks are appended.
  \cr
  \code{write.table.ffdf} has been designed to behave as much like \code{\link{write.table}} as possible. However, note the following differences:
  \enumerate{
    \item by default \code{\link[=dimnames.ffdf]{row.names}} are only written if the \code{\link{ffdf}} has row.names.
  }
}
\value{
  \code{\link{invisible}}
}
\note{
  \code{\link{write.csv}} and \code{\link{write.csv2}} have been fixed in order to suppress \code{col.names} if \code{append=TRUE} is passed.
  Note also that \code{write.table.ffdf} passes \code{col.names=FALSE} for all chunks following the first chunk - but not so for \code{FUN="write.csv"} and \code{FUN="write.csv2"} .
}
\author{
  Jens Oehlschlägel, Christophe Dutang
}
\seealso{
  \code{\link{read.table.ffdf}}, \code{\link{write.table}}, \code{\link{ffdf}}
}
\examples{
   x <- data.frame(log=rep(c(FALSE, TRUE), length.out=26), int=1:26, dbl=1:26 + 0.1
, fac=factor(letters), ord=ordered(LETTERS), dct=Sys.time()+1:26
, dat=seq(as.Date("1910/1/1"), length.out=26, by=1), stringsAsFactors = TRUE)
   ffx <- as.ffdf(x)

   csvfile <- tempPathFile(path=getOption("fftempdir"), extension="csv")

   write.csv.ffdf(ffx, file=csvfile)
   write.csv.ffdf(ffx, file=csvfile, append=TRUE)

   ffy <- read.csv.ffdf(file=csvfile, header=TRUE
, colClasses=c(ord="ordered", dct="POSIXct", dat="Date"))

   rm(ffx, ffy); gc()
   unlink(csvfile)

 \dontrun{
  # Attention, this takes very long
  vmodes <- c(log="boolean", int="byte", dbl="single"
, fac="short", ord="short", dct="single", dat="single")

  message("create a ffdf with 7 columns and 78 mio rows")
  system.time({
    x <- data.frame(log=rep(c(FALSE, TRUE), length.out=26), int=1:26, dbl=1:26 + 0.1
, fac=factor(letters), ord=ordered(LETTERS), dct=Sys.time()+1:26
, dat=seq(as.Date("1910/1/1"), length.out=26, by=1), stringsAsFactors = TRUE)
    x <- do.call("rbind", rep(list(x), 10))
    x <- do.call("rbind", rep(list(x), 10))
    x <- do.call("rbind", rep(list(x), 10))
    x <- do.call("rbind", rep(list(x), 10))
    ffx <- as.ffdf(x, vmode = vmodes)
    for (i in 2:300){
      message(i, "\n")
      last <- nrow(ffx) + nrow(x)
      first <- last - nrow(x) + 1L
      nrow(ffx) <- last
      ffx[first:last,] <- x
    }
  })


  csvfile <- tempPathFile(path=getOption("fftempdir"), extension="csv")

  write.csv.ffdf(ffx, file=csvfile, VERBOSE=TRUE)
  ffy <- read.csv.ffdf(file=csvfile, header=TRUE
, colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
, asffdf_args=list(vmode = vmodes), VERBOSE=TRUE)

  rm(ffx, ffy); gc()
  unlink(csvfile)
 }
}
\keyword{IO}
\keyword{file}
\keyword{connection}
