\name{Extract.ffdf}
\alias{Extract.ffdf}
\alias{[.ffdf}
\alias{[<-.ffdf}
\alias{[[.ffdf}
\alias{[[<-.ffdf}
\alias{$.ffdf}
\alias{$<-.ffdf}
\title{ Reading and writing data.frames (ffdf) }
\description{
  These are the main methods for reading and writing data from ffdf objects.
}
\usage{
\method{[}{ffdf}(x, i, j, drop = ncols == 1)
\method{[}{ffdf}(x, i, j) <- value
\method{[[}{ffdf}(x, i, j, exact = TRUE)
\method{[[}{ffdf}(x, i, j) <- value
\method{$}{ffdf}(x, i)
\method{$}{ffdf}(x, i) <- value
}
\arguments{
  \item{x}{ an ff object }
  \item{i}{ a row subscript or a matrix subscript or a list subscript }
  \item{j}{ a column subscript }
  \item{drop}{ logical. If TRUE the result is coerced to the lowest possible dimension. The default is to drop if only one column is left, but not to drop if only one row is left. }
  \item{value}{ A suitable replacement value: it will be repeated a whole number of times if necessary and it may be coerced: see the Coercion section.  If \code{NULL}, deletes the column if a single column is selected with \code{[[<-} or \code{$<-}. }
  \item{exact}{ logical: see \code{\link{[}}, and applies to column names. }
}
\details{
  The subscript methods \code{[}, \code{[[} and \code{$}, behave symmetrical to the assignment functions \code{[<-}, \code{[[<-} and \code{$<-}.
  What the former return is the assignment value to the latter.
  A notable exception is assigning \code{NULL} in \code{[[<-} and \code{$<-} which removes the \code{\link[=Extract.ffdf]{virtual}} column from the ffdf (and the \code{\link[=Extract]{physical}} component if it is no longer needed by any virtual column).
  Creating new columns via \code{[[<-} and \code{$<-} requires giving a name to the new column (character subscripting). \code{[<-} does not allow to create new columns, only to replace existing ones.
}
\section{Subscript expressions and return values}{
  \tabular{rllll}{
  \emph{allowed expression}    \tab -- \tab \emph{\code{example}}          \tab -- \tab \emph{\code{returnvalue}}                \cr
   row selection  \tab    \tab \code{x[i, ]} \tab    \tab \code{\link{data.frame}} or single row as list if \code{drop=TRUE}, like from data.frame \cr
   column selection  \tab    \tab \code{x[ ,i]} \tab    \tab \code{\link{data.frame}} or single column as vector unless \code{drop=TRUE}, like from data.frame  \cr
   matrix selection  \tab    \tab \code{x[cbind(i,j)]} \tab    \tab vector of the integer-matrix indexed cells (if the column types are compatible) \cr
   virtual selection \tab    \tab \code{x[i]}   \tab    \tab \code{\link{ffdf}}  with the selected columns only \cr
   physical selection \tab    \tab \code{x[[i]]} \tab    \tab the selected \code{\link{ff}}            \cr
   physical selection \tab    \tab \code{x$i} \tab    \tab the selected \code{\link{ff}}            \cr
  }
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ffdf}}, \code{\link[=[.data.frame]{Extract.data.frame}}, \code{\link{Extract.ff}}  }
\examples{
   d <- data.frame(a=letters, b=rev(letters), c=1:26, stringsAsFactors = TRUE)
   x <- as.ffdf(d)

   d[1,]
   x[1,]

   d[1:2,]
   x[1:2,]

   d[,1]
   x[,1]

   d[,1:2]
   x[,1:2]

   d[cbind(1:2,2:1)]
   x[cbind(1:2,2:1)]

   d[1]
   x[1]

   d[[1]]
   x[[1]]

   d$a
   x$a

   d$a[1:2]
   x$a[1:2]

   rm(x); gc()
}
\keyword{ IO }
\keyword{ data }
