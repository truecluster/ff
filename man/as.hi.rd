\name{as.hi}
\alias{as.hi}
\alias{as.hi.NULL}
\alias{as.hi.hi}
\alias{as.hi.ri}
\alias{as.hi.bit}
\alias{as.hi.bitwhich}
\alias{as.hi.call}
\alias{as.hi.name}
\alias{as.hi.(}
\alias{as.hi.integer}
\alias{as.hi.which}
\alias{as.hi.double}
\alias{as.hi.logical}
\alias{as.hi.character}
\alias{as.hi.matrix}
\title{ Hybrid Index, coercion to }
\description{
  The generic \command{as.hi} and its methods are the main (internal) means for preprocessing index information into the hybrid index class \code{\link{hi}}.
  Usually \command{as.hi} is called transparently from \code{\link{[.ff}}. However, you can explicitely do the index-preprocessing,
  store the Hybrid Index \code{\link{hi}}, and use the \code{hi} for subscripting.
}
\usage{
as.hi(x, \dots)
\method{as.hi}{NULL}(x, \dots)
\method{as.hi}{hi}(x, \dots)
\method{as.hi}{ri}(x, maxindex = length(x), \dots)
\method{as.hi}{bit}(x, range = NULL, maxindex = length(x), vw = NULL
, dim = NULL, dimorder = NULL, pack = TRUE, \dots)
\method{as.hi}{bitwhich}(x, maxindex = length(x), pack = FALSE, \dots)
\method{as.hi}{call}(x, maxindex = NA, dim = NULL, dimorder = NULL, vw = NULL
, vw.convert = TRUE, pack = TRUE, envir = parent.frame(), \dots)
\method{as.hi}{name}(x, envir = parent.frame(), \dots)
%\method{as.hi}{(}(x, envir = parent.frame(), \dots)
\method{as.hi}{integer}(x, maxindex = NA, dim = NULL, dimorder = NULL
, symmetric = FALSE, fixdiag = NULL, vw = NULL, vw.convert = TRUE
, dimorder.convert  = TRUE, pack = TRUE, NAs = NULL, \dots)
\method{as.hi}{which}(x, \dots)
\method{as.hi}{double}(x, \dots)
\method{as.hi}{logical}(x, maxindex = NA, dim = NULL, vw = NULL, pack = TRUE, \dots)
\method{as.hi}{character}(x, names, vw = NULL, vw.convert = TRUE, \dots)
\method{as.hi}{matrix}(x, dim, dimorder = NULL, symmetric = FALSE, fixdiag = NULL
, vw = NULL, pack = TRUE, \dots)
}
\arguments{
  \item{x}{ an appropriate object of the class for which we dispatched }
  \item{envir}{ the environment in which to evaluate components of the index expression }
  \item{maxindex}{ maximum positive indexposition \code{maxindex}, is needed with negative indices, if vw or dim is given, maxindex is calculated automatically }
  \item{names}{ the \code{\link[=names.ff]{names}} of the indexed vector for character indexing }
  \item{dim}{ the \code{\link[=dim.ff]{dim}} of the indexed matrix to be stored within the \code{\link{hi}} object }
  \item{dimorder}{ the \code{\link{dimorder}} of the indexed matrix to be stored within the \code{\link{hi}} object, may convert interpretation of \code{x} }
  \item{symmetric}{ the \code{\link{symmetric}} of the indexed matrix to be stored within the \code{\link{hi}} object }
  \item{fixdiag}{ the \code{\link{fixdiag}} of the indexed matrix to be stored within the \code{\link{hi}} object }
  \item{vw}{ the virtual window \code{\link{vw}} of the indexed vector or matrix to be stored within the \code{\link{hi}} object, see details }
  \item{vw.convert}{ FALSE to prevent doubly virtual window conversion, this is needed for some internal calls that have done the virtual window conversion already, see details }
  \item{dimorder.convert}{ FALSE to prevent doubly dimorder conversion, this is needed for some internal calls that have done the dimorder conversion already, see details }
  \item{NAs}{ a vector of NA positions to be stored \code{\link[bit]{rlepack}ed}, not fully supported yet }
  \item{pack}{ FALSE to prevent \code{\link[bit]{rlepack}ing}, note that this is a hint rather than a guarantee, \code{\link[=as.hi]{as.hi.bit}} might ignore this }
  \item{range}{ NULL or a vector with two elements indicating first and last position to be converted from 'bit' to 'hi' }
  \item{\dots}{ further argument passed from generic to method or from wrapper method to \code{\link[=as.hi]{as.hi.integer}} }
}
\details{
  The generic dispatches appropriately, \code{\link[=as.hi]{as.hi.hi}} returns an \code{\link{hi}} object unchanged,
  \code{\link[=as.hi]{as.hi.call}} tries to \code{\link{hiparse}} instead of evaluate its input in order to save RAM.
  If parsing is successfull \code{\link[=as.hi]{as.hi.call}} will ignore its argument \code{pack} and always pack unless the subscript is too small to do so.
  If parsing fails it evaluates the index expression and dispatches again to one of the other methods.
  \code{\link[=as.hi]{as.hi.name}} and \code{\link[=as.hi]{as.hi.(}} are wrappers to \code{\link[=as.hi]{as.hi.call}}.
  \code{\link[=as.hi]{as.hi.integer}} is the workhorse for coercing evaluated expressions
  and \code{\link[=as.hi]{as.hi.which}} is a wrapper removing the \code{which} class attribute.
  \code{\link[=as.hi]{as.hi.double}}, \code{\link[=as.hi]{as.hi.logical}} and \code{\link[=as.hi]{as.hi.character}} are also wrappers to \code{\link[=as.hi]{as.hi.integer}},
  but note that \code{\link[=as.hi]{as.hi.logical}} is not memory efficient because it expands \emph{all} positions and then applies logical subscripting.
  \cr
  \code{\link[=as.hi]{as.hi.matrix}} calls \code{\link{arrayIndex2vectorIndex}} and then \code{\link[=as.hi]{as.hi.integer}} to interpret and preprocess matrix indices.
  \cr
  If the \code{dim} and \code{dimorder} parameter indicate a non-standard dimorder (\code{\link{dimorderStandard}}), the index information in \code{x} is converted from a standard dimorder interpretation to the requested \code{\link{dimorder}}.
  \cr
  If the \code{vw} parameter is used, the index information in \code{x} is interpreted relative to the virtual window but stored relative to the abolute origin.
  Back-coercion via \code{\link{as.integer.hi}} and friends will again return the index information relative to the virtual window, thus retaining symmetry and transparency of the viurtual window to the user.
  \cr
  You can use \code{\link[=length.hi]{length}} to query the index length (possibly length of negative subscripts),
  \code{\link[=length.hi]{poslength}} to query the number of selected elements (even with negative subscripts),
  and \code{\link[=length.hi]{maxindex}} to query the largest possible index position (within virtual window, if present)
  \cr
  Duplicated negative indices are removed and will not be recovered by \code{\link{as.integer.hi}}.
}
\value{
  an object of class \code{\link{hi}}
}
\author{ Jens Oehlschlägel }
\note{ Avoid changing the Hybrid Index representation, this might crash the \code{\link{[.ff}} subscripting. }
\seealso{ \code{\link{hi}} for the Hybrid Index class, \code{\link{hiparse}} for parsing details, \code{\link{as.integer.hi}} for back-coercion, \code{\link{[.ff}} for ff subscripting }
\examples{
  message("integer indexing with and without rel-packing")
  as.hi(1:12)
  as.hi(1:12, pack=FALSE)
  message("if index is double, the wrapper method just converts to integer")
  as.hi(as.double(1:12))
  message("if index is character, the wrapper method just converts to integer")
  as.hi(c("a","b","c"), names=letters)
  message("negative index must use maxindex (or vw)")
  as.hi(-(1:3), maxindex=12)
  message("logical index can use maxindex")
  as.hi(c(FALSE, FALSE, TRUE, TRUE))
  as.hi(c(FALSE, FALSE, TRUE, TRUE), maxindex=12)

  message("matrix index")
  x <- matrix(1:12, 6)
  as.hi(rbind(c(1,1), c(1,2), c(2,1)), dim=dim(x))

  message("first ten positions within virtual window")
  i <- as.hi(1:10, vw=c(10, 80, 10))
  i
  message("back-coerce relativ to virtual window")
  as.integer(i)
  message("back-coerce relativ to absolute origin")
  as.integer(i, vw.convert=FALSE)

  message("parsed index expressions save index RAM")
    as.hi(quote(1:1000000000))
\dontrun{
  message("compare to RAM requirement when the index experssion is evaluated")
    as.hi(1:1000000000)
}

message("example of parsable index expression")
  a <- seq(100, 200, 20)
  as.hi(substitute(c(1:5, 4:9, a)))
  hi(c(1,4, 100),c(5,9, 200), by=c(1,1,20))

message("two examples of index expression temporarily expanded to full length due to 
non-supported use of brackets '(' and mathematical operators '+' accepting token")
message("example1: accepted token but aborted parsing because length>16")
  as.hi(quote(1+(1:16)))
message("example1: rejected token and aborted parsing because length>16")
  as.hi(quote(1+(1:17)))
}
\keyword{ IO }
\keyword{ data }
