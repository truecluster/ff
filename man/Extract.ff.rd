\name{Extract.ff}
\alias{Extract.ff}
\alias{[.ff}
\alias{[<-.ff}
\alias{[.ff_array}
\alias{[<-.ff_array}
\alias{[[.ff}
\alias{[[<-.ff}
\title{ Reading and writing vectors and arrays (high-level) }
\description{
  These are the main methods for reading and writing data from ff files.
}
\usage{
\method{[}{ff}(x, i, pack = FALSE)
\method{[}{ff}(x, i, add = FALSE, pack = FALSE) <- value
\method{[}{ff_array}(x, \dots, bydim = NULL, drop = getOption("ffdrop"), pack = FALSE)
\method{[}{ff_array}(x, \dots, bydim = NULL, add = FALSE, pack = FALSE) <- value
\method{[[}{ff}(x, i)
\method{[[}{ff}(x, i, add = FALSE) <- value
}
\arguments{
  \item{x}{ an ff object }
  \item{i}{ missing OR a single index expression OR a \code{\link{hi}} object }
  \item{\dots}{ missing OR up to length(dim(x)) index expressions OR \code{\link{hi}} objects }
  \item{drop}{ logical scalar indicating whether array dimensions shall be dropped }
  \item{bydim}{ the dimorder which shall be used in interpreting vector to/from array data }
  \item{pack}{ FALSE to prevent rle-packing in hybrid index preprocessing, see \code{\link{as.hi}} }
  \item{value}{ the values to be assigned, possibly recycled }
  \item{add}{ TRUE if the values should rather increment than overwrite at the target positions, see \code{\link{readwrite.ff}} }
}
\details{
  The single square bracket operators \command{[} and \command{[<-} are the workhorses for accessing the content of an ff object.
  They support \code{ff_vector} and \code{ff_array} access (\code{\link{dim.ff}}), they respect virtual windows (\code{\link{vw}}),
  \code{\link{names.ff}} and \code{\link{dimnames.ff}} and retain \code{\link{ramclass}} and \code{\link{ramattribs}}
  and thus support \code{\link{POSIXct}} and \code{\link{factor}}, see \code{\link{levels.ff}}.
  \cr
  The functionality of \command{[} and \command{[<-} cn be combined into one efficient operation, see \code{\link{swap}}.
  \cr
  The double square bracket operator \command{[[} is a shortcut for \code{\link{get.ff}}
  resp. \code{\link{set.ff}}, however, you should not rely on this for the future, see \code{\link{LimWarn}}. For programming please prefer \command{[}.
}
\section{Index expressions}{
  \code{x <- ff(1:12, dim=c(3,4), dimnames=list(letters[1:3], NULL))}
  \tabular{rll}{
  \emph{allowed expression}    \tab -- \tab \emph{\code{example}}                \cr
   positive integers           \tab    \tab \code{x[ 1 ,1]}                      \cr
   negative integers           \tab    \tab \code{x[ -(2:12) ]}                  \cr
   logical                     \tab    \tab \code{x[ c(TRUE, FALSE, FALSE) ,1]}  \cr
   character                   \tab    \tab \code{x[ "a" ,1]}                    \cr
   integer matrices            \tab    \tab \code{x[ rbind(c(1,1)) ]}            \cr
   hybrid index                \tab    \tab \code{x[ hi ,1]}                     \cr
  \emph{disallowed expression} \tab -- \tab \emph{\code{example}}                \cr
   zeros                       \tab    \tab \code{x[ 0 ]}                        \cr
   NAs                         \tab    \tab \code{x[ NA ]}                       \cr
  }
}
\section{Dimorder and bydim}{
  Arrays in R have always standard \code{\link{dimorder} seq_along(dim(x))} while ff allows to store an array in a different dimorder.
  Using nonstandard dimorder (see \code{\link{dimorderStandard}}) can speed up certain access operations: while matrix \code{dimorder=c(1,2)} -- column-major order --
  allows fast extraction of columns, \code{dimorder=c(2,1)} allows fast extraction of rows.
  \cr
  While the dimorder -- being an attribute of an \code{ff_array} -- controls how the vector in an ff file is interpreted,
  the \code{bydim} argument to the extractor functions controls, how assigment vector values
  in \command{[<-} are translated to the array and how the array is translated to a vector in \command{[} subscripting.
  Note that \code{bydim=c(2,1)} corresponds to \code{matrix(..., byrow=TRUE)}.
}
\section{Multiple vector interpretation in arrays }{
  In case of non-standard dimorder (see \code{\link{dimorderStandard}})
  the vector sequence of array elements in R and in the ff file differs.
  To access array elements in file order, you can use \code{\link{getset.ff}}, \code{\link{readwrite.ff}}
  or copy the ff object and set \code{dim(ff)<-NULL} to get a vector view into the ff object
  (using \code{[} dispatches the vector method \code{\link{[.ff}}).
  To access the array elements in R standard dimorder you simply use \code{[} which dispatches
  to \code{\link{[.ff_array}}. Note that in this case \code{\link{as.hi}} will unpack the complete index, see next section.
}
\section{RAM expansion of index expressions}{
  Some index expressions do not consume RAM due to the \code{\link{hi}} representation,
  for example \code{1:n} will almost consume no RAM hoewever large n.
  However, some index expressions are expanded and require to \code{\link[=Extract.ff]{maxindex}(i) * .rambytes["integer"]} bytes,
  either because the sorted sequence of index positions cannot be rle-packed efficiently
  or because \code{\link{hiparse}} cannot yet parse such expression and falls back to evaluating/expanding the index expression.
  If the index positions are not sorted, the index will be expanded and a second vector is needed to store the information for re-ordering,
  thus the index requires \code{2 * \link[=Extract.ff]{maxindex}(i) * .rambytes["integer"]} bytes.
}
\section{RAM expansion when recycling assigment values}{
  Some assignment expressions do not consume RAM for recycling, for example \code{x[1:n] <- 1:k}
  will not consume RAM hoewever large n compared to k, when x has standard \code{\link{dimorder}}.
  However, if \code{length(value)>1}, assignment expressions with non-ascending index positions trigger recycling the value R-side to the full index length.
  This will happen if \code{\link{dimorder}} does not match parameter \code{bydim} or if the index is not sorted ascending.
}
\value{
  The read operators \command{[} and \command{[[} return data from the ff object,
  possibly decorated with \code{\link[=names.ff]{names}}, \code{\link[=dim.ff]{dim}},
  \code{\link[=dimnames.ff]{dimnames}} and further attributes and classes (see \code{\link{ramclass}}, \code{\link{ramattribs}})
  \cr
  The write operators \command{[<-} and \command{[[<-} return the 'modified' ff object (like all assignment operators do).
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{ff}}, \code{\link{swap}}, \code{\link{add}}, \code{\link{readwrite.ff}}, \code{\link{LimWarn}} }
\examples{
   message("look at different dimorders")
   x <- ff(1:12, dim=c(3,4), dimorder=c(1,2))
   x[]
   as.vector(x[])
   x[1:12]
   x <- ff(1:12, dim=c(3,4), dimorder=c(2,1))
   x[]
   as.vector(x[])
   message("Beware (might be changed)")
   x[1:12]

   message("look at different bydim")
   matrix(1:12, nrow=3, ncol=4, byrow=FALSE)
   x <- ff(1:12, dim=c(3,4), bydim=c(1,2))
   x
   matrix(1:12, nrow=3, ncol=4, byrow=TRUE)
   x <- ff(1:12, dim=c(3,4), bydim=c(2,1))
   x
   x[,, bydim=c(2,1)]
   as.vector(x[,, bydim=c(2,1)])
   message("even consistent interpretation of vectors in assignments")
   x[,, bydim=c(1,2)] <- x[,, bydim=c(1,2)]
   x
   x[,, bydim=c(2,1)] <- x[,, bydim=c(2,1)]
   x
   rm(x); gc()

  \dontrun{
   message("some performance implications of different dimorders")
   n <- 100
   m <- 100000
   a <- ff(1L,dim=c(n,m))
   b <- ff(1L,dim=c(n,m), dimorder=2:1)
   system.time(lapply(1:n, function(i)sum(a[i,])))
   system.time(lapply(1:n, function(i)sum(b[i,])))
   system.time(lapply(1:n, function(i){i<-(i-1)*(m/n)+1; sum(a[,i:(i+m/n-1)])}))
   system.time(lapply(1:n, function(i){i<-(i-1)*(m/n)+1; sum(b[,i:(i+m/n-1)])}))

   n <- 100
   a <- ff(1L,dim=c(n,n,n,n))
   b <- ff(1L,dim=c(n,n,n,n), dimorder=4:1)
   system.time(lapply(1:n, function(i)sum(a[i,,,])))
   system.time(lapply(1:n, function(i)sum(a[,i,,])))
   system.time(lapply(1:n, function(i)sum(a[,,i,])))
   system.time(lapply(1:n, function(i)sum(a[,,,i])))
   system.time(lapply(1:n, function(i)sum(b[i,,,])))
   system.time(lapply(1:n, function(i)sum(b[,i,,])))
   system.time(lapply(1:n, function(i)sum(b[,,i,])))
   system.time(lapply(1:n, function(i)sum(b[,,,i])))

   n <- 100
   m <- 100000
   a <- ff(1L,dim=c(n,m))
   b <- ff(1L,dim=c(n,m), dimorder=2:1)
   system.time(ffrowapply(sum(a[i1:i2,]), a, RETURN=TRUE, CFUN="csum", BATCHBYTES=16104816\%/\%20))
   system.time(ffcolapply(sum(a[,i1:i2]), a, RETURN=TRUE, CFUN="csum", BATCHBYTES=16104816\%/\%20))
   system.time(ffrowapply(sum(b[i1:i2,]), b, RETURN=TRUE, CFUN="csum", BATCHBYTES=16104816\%/\%20))
   system.time(ffcolapply(sum(b[,i1:i2]), b, RETURN=TRUE, CFUN="csum", BATCHBYTES=16104816\%/\%20))

   rm(a,b); gc()
  }
}
\keyword{ IO }
\keyword{ data }
\keyword{ array }
