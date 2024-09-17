\name{LimWarn}
\alias{LimWarn}
\title{ ff Limitations and Warnings }
\description{
  This help page lists the currently known limitations of package ff,
  as well as differences between ff and ram methods.
}
\section{Automatic file removal}{
  Remind that not giving parameter \code{ff(filename=)} will result in a temporary file in \code{fftempdir} with 'delete' finalizer,
  while giving parameter \code{ff(filename=)} will result in a permanent file with 'close' finalizer.
  Do avoid setting \code{setwd(getOption("fftempdir"))}!
  Make sure you really understand the implications of automatic unlinking of getOption("fftempdir") \code{\link{.onUnload}},
  of finalizer choice and of finalizing behaviour at the end of R sessions as defaulted in getOption("fffinonexit").
  \bold{Otherwise you might experience 'unexpected' losses of files and data.}
}
\section{Size of objects}{
  ff objects can have length zero and are limited to \code{.Machine$integer.max} elements. We have not yet ported the R code to support 64bit double indices (in essence 52 bits integer) although the C++ back-end has been prepared for this.
  Furthermore filesize limitations of the OS apply, see \code{\link{ff}}.
}
\section{Side effects}{
  In contrast to standard R expressions, ff expressions violate the functional programming logic and are called for their side effects.
  This is also true for ram compatibility functions \code{\link{swap.default}}, and \code{\link{add.default}}.
}
\section{Hybrid copying semantics}{
  If you modify a copy of an ff object, changes of data (\code{\link[=Extract.ff]{[<-}}) and of \code{\link[=Extract.ff]{physical}} attributes
  will be shared, but changes in \code{\link[=Extract.ff]{virtual}} and class attributes will not.
}
\section{Limits of compatibility between ff and ram objects}{
  If it's not too big, you can move an ff object completely into R's RAM through \code{\link{as.ram}}.
  However, you should watch out for three limitations:
  \enumerate{
    \item Ram objects don't have hybrid copying semantics; changes to a copy of a ram object will never change the original ram object
    \item Assigning values to a ram object can easily upgrade to a higher \code{\link{storage.mode}}. This will create conflicts with the
          \code{\link{vmode}} of the ram object, which goes undetected until you try to write back to disk through \code{\link{as.ff}}.
    \item Writing back to disk with \code{\link{as.ff}} under the same filename requires that the original ff object has been deleted
          (or at least closed if you specify parameter \code{overwrite=TRUE}).
  }
}
\section{Index expressions}{
  ff index expressions do not allow zeros and NAs, see see \code{\link{[.ff}} and see \code{\link{as.hi}}
}
\section{Availablility of bydim parameter}{
  Parameter \code{bydim} is only available in ff access methods, see \code{\link{[.ff}}
}
\section{Availablility of add parameter}{
  Parameter \code{add} is only available in ff access methods, see \code{\link{[.ff}}
}
\section{Compatibility of swap and add}{
  If index expressions contain duplicated positions, the ff and ram methods for \code{\link{swap}}
  and \code{\link{add}} will behave differently, see \code{\link{swap}}.
}
\section{Definition of [[ and [[<-}{
  You should consider the behaviour of \code{\link{[[.ff}} and 
  \code{\link{[[<-.ff}} as undefined and not use them in programming.
  Currently they are shortcuts to \code{\link{get.ff}} and \code{\link{set.ff}}, 
  which unlike \code{\link[=Extract.ff]{[.ff}} and \code{\link[=Extract.ff]{[<-.ff}}
  do not support \code{\link{factor}} and \code{\link{POSIXct}}, 
  nor \code{\link{dimorder}} or virtual windows \code{\link{vw}}.
  In contrast to the standard methods, \code{\link{[[.ff}} and 
  \code{\link{[[<-.ff}} only accepts positive integer index positions.
  The definition of \code{\link{[[.ff}} and \code{\link{[[<-.ff}} may be 
  changed in the future.
}
\section{Multiple vector interpretation in arrays }{
  R objects have always standard \code{\link{dimorder} seq_along(dim)}.
  In case of non-standard dimorder (see \code{\link{dimorderStandard}})
  the vector sequence of array elements in R and in the ff file differs.
  To access array elements in file order, you can use \code{\link{getset.ff}}, \code{\link{readwrite.ff}}
  or copy the ff object and set \code{dim(ff)<-NULL} to get a vector view into the ff object
  (using \code{[} dispatches the vector method \code{\link{[.ff}}).
  To access the array elements in R standard dimorder you simply use \code{[} which dispatches
  to \code{\link{[.ff_array}}. Note that in this case \code{\link{as.hi}} will unpack the complete index, see next section.
}
\section{RAM expansion of index expressions}{
  Some index expressions do not consume RAM due to the \code{\link{hi}} representation.
  For example \code{1:n} will almost consume no RAM however large n.
  However, some index expressions are expanded and require to \code{\link[bit:maxindex.default]{maxindex}(i) * .rambytes["integer"]} bytes,
  either because the sorted sequence of index positions cannot be rle-packed efficiently
  or because \code{\link{hiparse}} cannot yet parse such expression and falls back to evaluating/expanding the index expression.
  If the index positions are not sorted, the index will be expanded and a second vector is needed to store the information for re-ordering,
  thus the index requires \code{2 * \link[=Extract.ff]{maxindex}(i) * .rambytes["integer"]} bytes.
}
\section{RAM expansion when recycling assigment values}{
  Some assignment expressions do not consume RAM for recycling. For example \code{x[1:n] <- 1:k}
  will not consume RAM however large is n compared to k, when x has standard \code{\link{dimorder}}.
  However, if \code{length(value)>1}, assignment expressions with non-ascending index positions trigger recycling the value R-side to the full index length.
  This will happen if \code{\link{dimorder}} does not match parameter \code{bydim} or if the index is not sorted in ascending order.
}
\section{Byteorder imcompatibility}{
  Note that ff files cannot been transferred between systems with different byteorder.
}
\keyword{ IO }
\keyword{ data }
\keyword{ package }
