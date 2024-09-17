\name{read.table.ffdf}
\Rdversion{1.1}
\alias{read.table.ffdf}
\alias{read.csv.ffdf}
\alias{read.csv2.ffdf}
\alias{read.delim.ffdf}
\alias{read.delim2.ffdf}
\title{
  Importing csv files into ff data.frames
}
\description{
  Function \code{read.table.ffdf} reads separated flat files into \code{\link{ffdf}} objects, very much like (and using) \code{\link{read.table}}.
  It can also work with any convenience wrappers like \code{\link{read.csv}} and provides its own convenience wrapper (e.g. \code{read.csv.ffdf}) for R's usual wrappers.
}
\usage{
read.table.ffdf(
  x = NULL
, file, fileEncoding = ""
, nrows = -1, first.rows = NULL, next.rows = NULL
, levels = NULL, appendLevels = TRUE
, FUN = "read.table", ...
, transFUN = NULL
, asffdf_args = list()
, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE
)
read.csv.ffdf(...)
read.csv2.ffdf(...)
read.delim.ffdf(...)
read.delim2.ffdf(...)
}
\arguments{
  \item{x}{
NULL or an optional \code{\link{ffdf}} object to which the read records are appended.
If this is provided, it defines crucial features that are otherwise determnined during the 'first' chunk of reading:
\code{\link[=vmode.ffdf]{vmode}s}, \code{\link[=dimnames.ffdf]{colnames}}, \code{colClasses}, sequence of predefined \code{\link[=levels.ff]{levels}}.
}
  \item{file}{
    the name of the file which the data are to be read from.
    Each row of the table appears as one line of the file.  If it does
    not contain an \emph{absolute} path, the file name is
    \emph{relative} to the current working directory,
    \code{\link{getwd}()}. Tilde-expansion is performed where supported.

    Alternatively, \code{file} can be a readable text-mode
    \code{\link{connection}} (which will be opened for reading if
    necessary, and if so \code{\link{close}}d (and hence destroyed) at
    the end of the function call).
}
  \item{fileEncoding}{
    character string: if non-empty declares the
    encoding used on a file (not a connection) so the character data can
    be re-encoded.  See \code{\link{file}}.
}
  \item{nrows}{
  integer: the maximum number of rows to read in (includes first.rows in case a 'first' chunk is read)
  Negative and other invalid values are ignored.
}
  \item{first.rows}{
  integer: number of rows to be read in the first chunk, see details. Default is the value given at \code{next.rows} or \code{1e3} otherwise.
  Ignored if \code{x} is given.
}
  \item{next.rows}{
  integer: number of rows to be read in further chunks, see details.
  By default calculated as \code{BATCHBYTES \%/\% sum(.rambytes[\link{vmode}(x)])}
}
  \item{levels}{
  NULL or an optional list, each element named with col.names of factor columns specifies the \code{\link[=levels.ff]{levels}}
  Ignored if \code{x} is given.
}
  \item{appendLevels}{
  logical.
  A vector of permissions to expand \code{\link[=levels.ff]{levels}} for factor columns.
  Recycled as necessary, or if the logical vector is named, unspecified values are taken to be \code{TRUE}.
  Ignored during processing of the 'first' chunk
}
  \item{FUN}{
  character: name of a function that is called for reading each chunk, see \code{\link{read.table}}, \code{\link{read.csv}}, etc.
}
  \item{\dots}{
  further arguments, passed to \code{FUN} in \code{read.table.ffdf}, or passed to \code{read.table.ffdf} in the convenience wrappers
}
  \item{transFUN}{
  NULL or a function that is called on each data.frame chunk after reading with \code{FUN} and before further processing (for filtering, transformations etc.)
}
  \item{asffdf_args}{
  further arguments passed to \code{\link{as.ffdf}} when converting the \code{\link{data.frame}} of the first chunk to \code{\link{ffdf}}.
  Ignored if \code{x} is given.
}
  \item{BATCHBYTES}{
  integer: bytes allowed for the size of the \code{\link{data.frame}} storing the result of reading one chunk. Default \code{getOption("ffbatchbytes")}.
}
  \item{VERBOSE}{
  logical: TRUE to verbose timings for each processed chunk (default FALSE)
}
}
\details{
  \code{read.table.ffdf} has been designed to read very large (many rows) separated flatfiles in row-chunks
  and store the result in a \code{\link{ffdf}} object on disk, but quickly accessible via \code{\link{ff}} techniques.
  \cr
  The first chunk is read with a default of 1000 rows, for subsequent chunks the number of rows is calculated to not require more RAM than \code{getOption("ffbatchbytes")}.
  The following could be indications to change the parameter \code{first.rows}:
  \enumerate{
    \item set \code{first.rows=-1} to read the complete file in one go (requires enough RAM)
    \item set \code{first.rows} to a smaller number if the pre-allocation of RAM for the first chunk with parameter \code{nrows} in \code{\link{read.table}} is too large, i.e. with many columns on machine with little RAM.
    \item set \code{first.rows} to a larger number if you expect better factor level ordering (factor levels are sorted in the first chunk, but not at subsequent chunks, however, factor level ordering can be fixed later, see below).
  }
  By default the \code{\link{ffdf}} object is created on the fly at the end of reading the 'first' chunk, see argument \code{first.rows}.
  The creation of the \code{\link{ffdf}} object is done via \code{\link{as.ffdf}} and can be finetuned by passing argument \code{asffdf_args}.
  Even more control is possible by passing in a \code{\link{ffdf}} object as argument \code{x} to which the read records are appended.
  \cr
  \code{read.table.ffdf} has been designed to behave as much like \code{\link{read.table}} as possible. Hoever, note the following differences:
  \enumerate{
    \item Arguments 'colClasses' and 'col.names' are now enforced also during 'next.rows' chunks.
          For example giving \code{colClasses=NA} will force that no colClasses are derived from the \code{first.rows} respective from the \code{\link{ffdf}} object in parameter \code{x}.
    \item colClass 'ordered' is allowed and will create an \code{\link{ordered}} factor
    \item character vector are not supported, character data must be read as one of the following colClasses: 'Date', 'POSIXct', 'factor, 'ordered'.
          By default character columns are read as factors.
          Accordingly arguments 'as.is' and 'stringsAsFactors' are not allowed.
    \item the sequence of \code{\link{levels.ff}} from chunked reading can depend on chunk size: by default new levels found on a chunk are appended to the levels found in previous chunks, no attempt is made to sort and recode the levels during chunked processing, levels can be sorted and recoded most efficiently \emph{after} all records have been read using \code{\link{sortLevels}}.
    \item the default for argument 'comment.char' is \code{""} even for those FUN that have a different default. However, explicit specification of 'comment.char' will have priority.
  }
}
\note{
    Note that using the 'skip' argument still requires to read the file from beginning in order to count the lines to be skipped.
    If you first read part of the file in order to understand its structure and then want to continue,
    a more efficient solution that using 'skip' is opening a \code{\link{file}} \code{\link{connection}} and pass that to argument 'file'.
    \code{read.table.ffdf} does the same in order to skip efficiently over previously read chunks.
}
\value{
  An \code{\link{ffdf}} object. If created during the 'first' chunk pass, it will have one \code{\link[=Extract.ffdf]{physical}} component per \code{\link[=Extract.ffdf]{virtual}} column.
}
\author{
  Jens Oehlschlägel, Christophe Dutang
}
\seealso{
  \code{\link{write.table.ffdf}}, \code{\link{read.table}}, \code{\link{ffdf}}
}
\examples{
 message("create some csv data on disk")
 x <- data.frame(
   log=rep(c(FALSE, TRUE), length.out=26)
 , int=1:26
 , dbl=1:26 + 0.1
 , fac=factor(letters)
 , ord=ordered(LETTERS)
 , dct=Sys.time()+1:26
 , dat=seq(as.Date("1910/1/1"), length.out=26, by=1)
 , stringsAsFactors = TRUE
 )
 x <- x[c(13:1, 13:1),]
 csvfile <- tempPathFile(path=getOption("fftempdir"), extension="csv")
 write.csv(x, file=csvfile, row.names=FALSE)
 
 cat("Simply read csv with header\n")
 y <- read.csv(file=csvfile, header=TRUE)
 y
 cat("Read csv with header\n")
 ffy <- read.csv.ffdf(file=csvfile, header=TRUE)
 ffy
 sapply(ffy[,], class)
 
 message("reading with colClasses (an ordered factor wont'work in read.csv)")
 try(read.csv(file=csvfile, header=TRUE, colClasses=c(ord="ordered")
 , stringsAsFactors = TRUE))
 # TODO could fix this with the following two commands (Gabor Grothendieck) 
 # but does not know what bad side-effects this could have
 #setOldClass("ordered")
 #setAs("character", "ordered", function(from) ordered(from))
 y <- read.csv(file=csvfile, header=TRUE, colClasses=c(dct="POSIXct", dat="Date")
 , stringsAsFactors = TRUE)
 ffy <- read.csv.ffdf(
   file=csvfile
 , header=TRUE
 , colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
 )
 rbind(
   ram_class = sapply(y, function(x)paste(class(x), collapse = ","))
 , ff_class = sapply(ffy[,], function(x)paste(class(x), collapse = ","))
 , ff_vmode = vmode(ffy)
 )
 
 message("NOTE that reading in chunks can change the sequence of levels and thus the coding")
 message("(Sorting levels during chunked reading can be too expensive)")
 levels(ffy$fac[])
 ffy <- read.csv.ffdf(
   file=csvfile
 , header=TRUE
 , colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
 , first.rows=6
 , next.rows=10
 , VERBOSE=TRUE
 )
 levels(ffy$fac[])
 
 
 message("If we don't know the levels we can sort then after reading")
 message("(Will rewrite all factor codes)")
 message("NOTE that you MUST assign the return value of sortLevels()")
 ffy <- sortLevels(ffy)
 levels(ffy$fac[])
 
 message("If we KNOW the levels we can fix levels upfront")
 ffy <- read.csv.ffdf(
   file=csvfile
 , header=TRUE
 , colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
 , first.rows=6
 , next.rows=10
 , levels=list(fac=letters, ord=LETTERS)
 )
 levels(ffy$fac[])
 
 message("Or we inspect a sufficiently large chunk of data and use those")
 table(ffy$fac[], exclude=NULL)
 ffy <- read.csv.ffdf(
   file=csvfile
 , header=TRUE
 , colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
 , nrows=13
 , VERBOSE=TRUE
 )
 message("append the rest to ffy")
 ffy <- read.csv.ffdf(
   x=ffy
 , file=csvfile
 , header=FALSE
 , skip=1 + nrow(ffy)
 , VERBOSE=TRUE
 )
 table(ffy$fac[], exclude=NULL)
 
 message("We can turn unexpected factor levels to NA, say we only allowed a:l")
 ffy <- read.csv.ffdf(
   file=csvfile
 , header=TRUE
 , colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
 , levels=list(fac=letters[1:12], ord=LETTERS[1:12])
 , appendLevels=FALSE
 )
 sapply(colnames(ffy), function(i)sum(is.na(ffy[[i]][])))

 message("let's store some columns more efficient")
 sum(.ffbytes[vmode(ffy)])
 ffy$log <- clone(ffy$log, vmode="boolean")
 ffy$fac <- clone(ffy$fac, vmode="byte")
 ffy$ord <- clone(ffy$ord, vmode="byte")
 sum(.ffbytes[vmode(ffy)])
 
 message("let's make a template with zero rows")
 ffx <- clone(ffy)  
 nrow(ffx) <- 0
   
 message("reading with template and colClasses")
 ffy <- read.csv.ffdf(
   x=ffx
 , file=csvfile
 , header=TRUE
 , colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
 , next.rows = 12
 , VERBOSE = TRUE
 )
 rbind(
   ff_class = sapply(ffy[,], function(x)paste(class(x), collapse = ","))
 , ff_vmode = vmode(ffy)
 )
 levels(ffx$fac[])
 levels(ffy$fac[])
 
 message("reading with template without colClasses")
 ffy <- read.csv.ffdf(
   x=ffx
   , file=csvfile
   , header=TRUE
   , next.rows = 12
   , VERBOSE = TRUE
 )
 rbind(
   ff_class = sapply(ffy[,], function(x)paste(class(x), collapse = ","))
 , ff_vmode = vmode(ffy)
 )
 levels(ffx$fac[])
 levels(ffy$fac[])
 

 message("We can fine-tune the creation of the ffdf")
 message("- let's create the ff files outside of fftempdir")
 message("- let's reduce required disk space and thus file.system cache RAM")
 message("By default we had record size 36.25")
 ffy <- read.csv.ffdf(
   file=csvfile
   , header=TRUE
   , colClasses=c(ord="ordered", dct="POSIXct", dat="Date")
   , asffdf_args=list(
     vmode = c(
         log="boolean"
       , int="byte"
       , dbl="single"
       , fac="nibble"  # no NAs
       , ord="nibble"  # no NAs
       , dct="single"
       , dat="single"
     )
     , col_args=list(pattern = "./csv")  # create in getwd() with prefix csv
   )
 )
 vmode(ffy)
 message("This recordsize is more than 50\% reduced")
 sum(.ffbytes[vmode(ffy)]) / 36.25
 
 message("Don't forget to wrap-up files that are not in fftempdir")
 delete(ffy); rm(ffy)
 message("It's a good habit to also wrap-up temporary stuff (or at least know how this is done)")
 rm(ffx); gc()

   
 fwffile <- tempfile()
 
 cat(file=fwffile, "123456", "987654", sep="\n")
 x <- read.fwf(fwffile, widths=c(1,2,3), stringsAsFactors = TRUE)    #> 1 23 456 \ 9 87 654
 y <- read.table.ffdf(file=fwffile, FUN="read.fwf", widths=c(1,2,3))
 stopifnot(identical(x, y[,]))
 x <- read.fwf(fwffile, widths=c(1,-2,3), stringsAsFactors = TRUE)   #> 1 456 \ 9 654
 y <- read.table.ffdf(file=fwffile, FUN="read.fwf", widths=c(1,-2,3))
 stopifnot(identical(x, y[,]))
 unlink(fwffile)
 
 cat(file=fwffile, "123", "987654", sep="\n")
 x <- read.fwf(fwffile, widths=c(1,0, 2,3), stringsAsFactors = TRUE)    #> 1 NA 23 NA \ 9 NA 87 654
 y <- read.table.ffdf(file=fwffile, FUN="read.fwf", widths=c(1,0, 2,3))
 stopifnot(identical(x, y[,]))
 unlink(fwffile)
 
 cat(file=fwffile, "123456", "987654", sep="\n")
 x <- read.fwf(fwffile, widths=list(c(1,0, 2,3), c(2,2,2))
 , stringsAsFactors = TRUE) #> 1 NA 23 456 98 76 54
 y <- read.table.ffdf(file=fwffile, FUN="read.fwf", widths=list(c(1,0, 2,3), c(2,2,2)))
 stopifnot(identical(x, y[,]))
 
 unlink(fwffile)

    \dontshow{
       x <- read.csv(file=csvfile, header=TRUE, stringsAsFactors = TRUE)

       y <- read.csv.ffdf(file=csvfile, header=TRUE)
       stopifnot(identical(x, y[,]))

       y <- read.csv.ffdf(file=csvfile, header=TRUE, nrows=13)
       stopifnot(identical(x[1:13,], y[,]))

       y <- read.csv.ffdf(file=csvfile, header=TRUE, first.rows=12)
       y <- sortLevels(y)
       stopifnot(identical(x, y[,]))

       y <- read.csv.ffdf(file=csvfile, header=TRUE, nrows=13, first.rows=12)
       y <- sortLevels(y)
       stopifnot(identical(x[1:13,], y[,]))

       y <- read.csv.ffdf(file=csvfile, header=TRUE, nrows=12, first.rows=12)
       y <- sortLevels(y)
       stopifnot(!identical(x[1:12,], y[,]))
       stopifnot(identical(as.character(as.matrix(x[1:12,])), as.character(as.matrix(y[,]))))

       y <- read.csv.ffdf(file=csvfile, header=TRUE, nrows=11, first.rows=12)
       y <- sortLevels(y)
       stopifnot(!identical(x[1:11,], y[,]))
       stopifnot(identical(as.character(as.matrix(x[1:11,])), as.character(as.matrix(y[,]))))

       y <- read.csv.ffdf(file=csvfile, header=TRUE, first.rows=-1)
       stopifnot(identical(x, y[,]))

       y <- read.csv.ffdf(file=csvfile, header=TRUE, nrows=13, first.rows=12, appendLevels=c(ord=FALSE))
       stopifnot(is.na(y$ord[13]) && !is.na(y$fac[13]))
    }

    unlink(csvfile)
}
\keyword{IO}
\keyword{file}
\keyword{connection}
