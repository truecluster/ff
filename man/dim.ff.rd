\name{dim.ff}
\alias{dim.ff}
\alias{dim.ffdf}
\alias{dim<-.ff}
\alias{dim<-.ffdf}
\alias{dimorder}
\alias{dimorder.default}
\alias{dimorder.ff_array}
\alias{dimorder.ffdf}
\alias{dimorder<-}
\alias{dimorder<-.ff_array}
\alias{dimorder<-.ffdf}
\title{ Getting and setting dim and dimorder }
\description{
  Assigning \code{dim} to an \code{ff_vector} changes it to an \code{ff_array}.
  Beyond that \code{dimorder} can be assigned to change from column-major order to row-major order or generalizations for higher order \code{ff_array}.
}
\usage{
  \method{dim}{ff}(x)
  \method{dim}{ffdf}(x)
  \method{dim}{ff}(x) <- value
  \method{dim}{ffdf}(x) <- value
   dimorder(x, \dots)
   dimorder(x, \dots) <- value
  \method{dimorder}{default}(x, \dots)
  \method{dimorder}{ff_array}(x, \dots)
  \method{dimorder}{ffdf}(x, \dots)
  \method{dimorder}{ff_array}(x, \dots) <- value
  \method{dimorder}{ffdf}(x, \dots) <- value  # just here to catch forbidden assignments
}
\arguments{
  \item{x}{ a ff object }
  \item{value}{ an appropriate integer vector }
  \item{\dots}{ further arguments (not used) }
}
\details{
   \command{dim} and \command{dimorder} are \code{\link[=Extract.ff]{virtual}} attributes. Thus two copies of an R ff object can point to the same file but interpret it differently.
   \command{dim} has the usual meaning, \command{dimorder} defines the dimension order of storage, i.e. \code{c(1,2)} corresponds to R's standard column-major order,
   \code{c(1,2)} corresponds to row-major order, and for higher dimensional arrays dimorder can also be used. Standard dimorder is \code{seq_along(dim(x))}. \cr
   For \code{\link{ffdf}} \code{dim} returns the number of rows and virtual columns. With \code{dim<-.ffdf} only the number of rows can be changed. For convenience you can assign \code{NA} to the number of columns. \cr
   For \code{\link{ffdf}} the dimorder returns non-standard dimorder if any of its columns contains a ff object with non-standard dimorder (see \code{\link{dimorderStandard}})
   An even higher level of virtualization is available using virtual windows, see \code{\link{vw}}.
}
\note{
  \code{x[]} returns a matrix like \code{x[,]} and thus respects dimorder, while \code{x[i:j]} returns a vector and simply returns elements in the stored order.
  Check the corresponding example twice, in order to make sure you understand that for non-standard dimorder \code{x[seq_along(x)]} is \emph{not the same} as \code{as.vector(x[])}.
}
\value{
  \command{names} returns a character vector (or NULL)
}
\author{ Jens Oehlschlägel }
\seealso{ \code{\link{dim}}, \code{\link[=dimnames.ff]{dimnames.ff_array}}, \code{\link{dimorderStandard}}, \code{\link{vw}}, \code{\link[=Extract.ff]{virtual}} }
\examples{
  x <- ff(1:12, dim=c(3,4), dimorder=c(2:1))
  y <- x
  dim(y) <- c(4,3)
  dimorder(y) <- c(1:2)
  x
  y
  x[]
  y[]
  x[,bydim=c(2,1)]
  y[,bydim=c(2,1)]

  message("NOTE that x[] like x[,] returns a matrix (respects dimorder),")
  message("while x[1:12] returns a vector IN STORAGE ORDER")
  message("check the following examples twice to make sure you understand this")
  x[,]
  x[]
  as.vector(x[])
  x[1:12]
  rm(x,y); gc()

  \dontshow{
    message("some regression test with regard to different dimorders")
    k <- 24
    d <- 3:5
    n <- prod(d)
    for (i in 1:k){
      a <- array(sample(n), dim=sample(d))
      x <- as.ff(a, dimorder=sample(seq_along(d)))
      if (!identical(a[1:n], x[1:n]))
        stop("error in caclulating access positions")
      if (!identical(a[1:dim(a)[1],,], x[1:dim(a)[1],,]))
        stop("error in caclulating access positions")
    }
    rm(x); gc()
  }
  \dontrun{
    message("some performance comparison between different dimorders")
    n <- 100
    m <- 100000
    a <- ff(1L,dim=c(n,m))
    b <- ff(1L,dim=c(n,m), dimorder=2:1)
    system.time(lapply(1:n, function(i)sum(a[i,])))
    system.time(lapply(1:n, function(i)sum(b[i,])))
    system.time(lapply(1:n, function(i){i<-(i-1)*(m/n)+1; sum(a[,i:(i+m/n-1)])}))
    system.time(lapply(1:n, function(i){i<-(i-1)*(m/n)+1; sum(b[,i:(i+m/n-1)])}))
    rm(a,b); gc()
  }
}
\keyword{ IO }
\keyword{ data }
