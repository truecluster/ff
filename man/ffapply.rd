\name{ffapply}
\alias{ffapply}
\alias{ffvecapply}
\alias{ffrowapply}
\alias{ffcolapply}
\title{ Apply for ff objects }
\description{
  The \code{ffapply} functions support convenient batched processing of ff objects
  such that each single batch or chunk will not exhaust RAM
  and such that batchs have sizes as similar as possible, see \code{\link[bit]{bbatch}}.
  Differing from R's standard \code{\link{apply}} which applies a \code{FUNction},
  the \code{ffapply} functions do apply an \code{EXPRession} and provide two indices \code{FROM="i1"} and \code{TO="i2"},
  which mark beginning and end of the batch and can be used in the applied expression.
  Note that the ffapply functions change the two indices in their parent frame, to avoid conflicts you can use different names through \code{FROM="i1"} and \code{TO="i2"}.
  For support of creating return values see details.
}
\usage{
ffvecapply(EXPR, X = NULL, N = NULL, VMODE = NULL, VBYTES = NULL, RETURN = FALSE
, CFUN = NULL, USE.NAMES = TRUE, FF_RETURN = TRUE, BREAK = ".break"
, FROM = "i1", TO = "i2"
, BATCHSIZE = .Machine$integer.max, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE)
ffrowapply(EXPR, X = NULL, N = NULL, NCOL = NULL, VMODE = NULL, VBYTES = NULL
, RETURN = FALSE, RETCOL = NCOL, CFUN = NULL, USE.NAMES = TRUE, FF_RETURN = TRUE
, FROM = "i1", TO = "i2"
, BATCHSIZE = .Machine$integer.max, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE)
ffcolapply(EXPR, X = NULL, N = NULL, NROW = NULL, VMODE = NULL, VBYTES = NULL
, RETURN = FALSE, RETROW = NROW, CFUN = NULL, USE.NAMES = TRUE, FF_RETURN = TRUE
, FROM = "i1", TO = "i2"
, BATCHSIZE = .Machine$integer.max, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE)
ffapply(EXPR = NULL, AFUN = NULL, MARGIN = NULL, X = NULL, N = NULL, DIM = NULL
, VMODE = NULL, VBYTES = NULL, RETURN = FALSE, CFUN = NULL, USE.NAMES = TRUE
, FF_RETURN = TRUE, IDIM = "idim"
, FROM = "i1", TO = "i2", BREAK = ".break"
, BATCHSIZE = .Machine$integer.max, BATCHBYTES = getOption("ffbatchbytes")
, VERBOSE = FALSE)
}
\arguments{
  \item{EXPR}{ the \code{\link{expression}} to be applied }
  \item{AFUN}{ \code{ffapply} only: alternatively to \code{EXPR} the name of a function to be applied, automatically converted to \code{EXPR} }
  \item{MARGIN}{ \code{ffapply} only: the margins along which to loop in \code{ffapply} }

  \item{X}{ an ff object from which several parameters can be derived, if they are not given directly: \code{N, NCOL, NROW, DIM, VMODE, VBYTES, FF_RETURN} }

  \item{N}{ the total number of elements in the loop, e.g. number of elements in \code{ffvecapply} or number of rows in \code{ffrowapply} }
  \item{NCOL}{ \code{ffrowapply} only: the number of columns needed to calculate batch sizes }
  \item{NROW}{ \code{ffcolapply} only: the number of rows needed to calculate batch sizes }
  \item{DIM}{ \code{ffapply} only: the dimension of the array needed to calculate batch sizes }

  \item{VMODE}{ the \code{\link{vmode}} needed to prepare the \code{RETURN} object and to derive \code{VBYTES} if they are not given directly }
  \item{VBYTES}{ the bytes per cell -- see \code{\link{.rambytes}} -- to calculate the RAM requirements per cell }
  \item{BATCHBYTES}{ the max number of bytes per batch, default \code{getOption("ffbatchbytes")} }
  \item{BATCHSIZE}{ an additional restriction on the number of loop elements, default=\code{.Machine$integer.max} }

  \item{FROM}{ the name of the index that marks the beginning of the batch, default 'i1', change if needed to avoid naming-conflicts in the calling frame }
  \item{TO}{ the name of the index that marks the end of the batch, default 'i2', change if needed to avoid naming-conflicts in the calling frame }
  \item{IDIM}{ \code{ffapply} only: the name of an R variable used for loop-switching, change if needed to avoid naming-conflicts in the calling frame }
  \item{BREAK}{ \code{ffapply} only: the name of an R object in the calling frame that triggers break out of the batch loop, if 1) it exists 2) is.logical and 3) is TRUE }

  \item{RETURN}{ \code{TRUE} to prepare a return value (default \code{FALSE}) }
  \item{CFUN}{ name of a collapsing function, see \code{\link{CFUN}} }
  \item{RETCOL}{ \code{NULL} gives return \code{vector[1:N]}, \code{RETCOL} gives return \code{matrix[1:N, 1:RETCOL]} }
  \item{RETROW}{ \code{NULL} gives return \code{vector[1:N]}, \code{RETROW} gives return \code{matrix[1:RETROW, 1:N]} }
  \item{FF_RETURN}{ \code{FALSE} to return a ram object, \code{TRUE} to return an ff object, or an ff object that is \code{\link{ffsuitable}} to absorb the return data }
  \item{USE.NAMES}{ \code{FALSE} to suppress attaching names or dimnames to the result }

  \item{VERBOSE}{ \code{TRUE} to verbose the batches }
}
\details{
  \command{ffvecapply} is the simplest ffapply method for \code{ff_vectors}. \command{ffrowapply} and \command{ffcolapply} is for \code{ff_matrix},
  and \command{ffapply} is the most general method for \code{ff_array}s and \code{ff_vector}s.
  \cr
  There are many ways to change the return value of the ffapply functions.
  In its simplest usage -- batched looping over an expression -- they don't return anything, see \code{\link{invisible}}.
  If you switch \code{RETURN=TRUE} in \command{ffvecapply} then it is assumed that all looped expressions together return one vector of length \code{N},
  and via parameter \code{FF_RETURN}, you can decide whether this vector is in ram or is an ff object (or even which ff object to use).
  \command{ffrowapply} and \command{ffcolapply} additionally have parameter \code{RETCOL} resp. \code{RETROW} which defaults to returning a matrix of the original size;
  in order to just return a vector of length \code{N} set this to \code{NULL}, or specify a number of columns/rows for the return matrix.
  It is assumed that the expression will return appropriate pieces for this return structure (see examples).
  If you specify \code{RETURN=TRUE} and a collapsing function name \code{CFUN}, then it is assumed that the batched expressions return aggregated information,
  which is first collected in a list, and finally the collapsing function is called on this list: \code{do.call(CFUN, list)}. If you want to return the unmodified list,
  you have to specify \code{CFUN="list"} for obvious reasons.
  \cr
  \code{ffapply} allows usages not completly unlike \code{\link{apply}}: you can specify the name of a function \code{AFUN} to be applied over \code{MARGIN}.
  However note that you must specify \code{RETURN=TRUE} in order to get a return value.
  Also note that currently ffapply assumes that your expression returns exactly one value per cell in \code{DIM[MARGINS]}.
  If you want to return something more complicated, you MUST specify a \code{CFUN="list"} and your return value will be a list with dim attribute \code{DIM[MARGINS]}.
  This means that for a function \code{AFUN} returning a scalar, \code{ffapply} behaves very similar to \code{\link{apply}}, see examples.
  Note also that \code{ffapply} might create a object named '.ffapply.dimexhausted' in its parent frame,
  and it uses a variable in the parent frame for loop-switching between dimensions, the default name 'idim' can be changed using the \code{IDIM} parameter.
  Finally you can break out of the implied loops by assigning \code{TRUE} to a variable with the name in \code{BREAK}.
}
\value{
  see details
}
\author{ Jens Oehlschlägel }
\note{ xx The complete generation of the return value is preliminary and the arguments related to defining the return value might still change, especially ffapply is work in progress }
\seealso{ \code{\link{apply}}, \code{\link{expression}}, \code{\link[bit]{bbatch}}, \code{\link[bit]{repfromto}}, \code{\link{ffsuitable}} }
\examples{
   message("ffvecapply examples")
   x <- ff(vmode="integer", length=100)
   message("loop evaluate expression without returning anything")
   ffvecapply(x[i1:i2] <- i1:i2, X=x, VERBOSE=TRUE)
   ffvecapply(x[i1:i2] <- i1:i2, X=x, BATCHSIZE=20, VERBOSE=TRUE)
   ffvecapply(x[i1:i2] <- i1:i2, X=x, BATCHSIZE=19, VERBOSE=TRUE)
   message("lets return the combined expressions as a new ff object")
   ffvecapply(i1:i2, N=length(x), VMODE="integer", RETURN=TRUE, BATCHSIZE=20)
   message("lets return the combined expressions as a new ram object")
   ffvecapply(i1:i2, N=length(x), VMODE="integer", RETURN=TRUE, FF_RETURN=FALSE, BATCHSIZE=20)
   message("lets return the combined expressions in existing ff object x")
   x[] <- 0L
   ffvecapply(i1:i2, N=length(x), VMODE="integer", RETURN=TRUE, FF_RETURN=x, BATCHSIZE=20)
   x
   message("aggregate and collapse")
   ffvecapply(summary(x[i1:i2]), X=x, RETURN=TRUE, CFUN="list", BATCHSIZE=20)
   ffvecapply(summary(x[i1:i2]), X=x, RETURN=TRUE, CFUN="crbind", BATCHSIZE=20)
   ffvecapply(summary(x[i1:i2]), X=x, RETURN=TRUE, CFUN="cmean", BATCHSIZE=20)

   message("how to do colSums with ffrowapply")
   x <- ff(1:1000, vmode="integer", dim=c(100, 10))
   ffrowapply(colSums(x[i1:i2,,drop=FALSE]), X=x, RETURN=TRUE, CFUN="list", BATCHSIZE=20)
   ffrowapply(colSums(x[i1:i2,,drop=FALSE]), X=x, RETURN=TRUE, CFUN="crbind", BATCHSIZE=20)
   ffrowapply(colSums(x[i1:i2,,drop=FALSE]), X=x, RETURN=TRUE, CFUN="csum", BATCHSIZE=20)

   message("further ffrowapply examples")
   x <- ff(1:1000, vmode="integer", dim=c(100, 10))
   message("loop evaluate expression without returning anything")
   ffrowapply(x[i1:i2, ] <- i1:i2, X=x, BATCHSIZE=20)
   message("lets return the combined expressions as a new ff object (x unchanged)")
   ffrowapply(2*x[i1:i2, ], X=x, RETURN=TRUE, BATCHSIZE=20)
   message("lets return a single row aggregate")
   ffrowapply(t(apply(x[i1:i2,,drop=FALSE], 1, mean)), X=x, RETURN=TRUE, RETCOL=NULL, BATCHSIZE=20)
   message("lets return a 6 column aggregates")
   y <- ffrowapply( t(apply(x[i1:i2,,drop=FALSE], 1, summary)), X=x
   , RETURN=TRUE, RETCOL=length(summary(0)), BATCHSIZE=20)
   colnames(y) <- names(summary(0))
   y
   message("determine column minima if a complete column does not fit into RAM")
   ffrowapply(apply(x[i1:i2,], 2, min), X=x, RETURN=TRUE, CFUN="pmin", BATCHSIZE=20)

   message("ffapply examples")
   x <- ff(1:720, dim=c(8,9,10))
   dimnames(x) <- dummy.dimnames(x)
   message("apply function with scalar return value")
   apply(X=x[], MARGIN=3:2, FUN=sum)
   apply(X=x[], MARGIN=2:3, FUN=sum)
   ffapply(X=x, MARGIN=3:2, AFUN="sum", RETURN=TRUE, BATCHSIZE=8)
   message("this is what CFUN is based on")
   ffapply(X=x, MARGIN=2:3, AFUN="sum", RETURN=TRUE, CFUN="list", BATCHSIZE=8)

   message("apply functions with vector or array return value currently have limited support")
   apply(X=x[], MARGIN=3:2, FUN=summary)
   message("you must use CFUN, the rest is up to you")
   y <- ffapply(X=x, MARGIN=3:2, AFUN="summary", RETURN=TRUE, CFUN="list", BATCHSIZE=8)
   y
   y[[1]]

   rm(x); gc()
}
\keyword{ array }
\keyword{ data }
