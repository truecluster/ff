\name{Forbidden_ffdf}
\Rdversion{1.1}
\alias{physical<-.ffdf}
\alias{virtual<-.ffdf}
\alias{length<-.ffdf}
\alias{vmode<-.ffdf}
\alias{vw<-.ffdf}
\alias{vw.ffdf}
\title{
  Forbidden ffdf functions
}
\description{
  Methods implemented just to prevent using them (because something inppropriate could be find by inheritance)
}
\usage{
\method{physical}{ffdf}(x) <- value
\method{virtual}{ffdf}(x) <- value
\method{length}{ffdf}(x) <- value
\method{vmode}{ffdf}(x, ...) <- value
\method{vw}{ffdf}(x, ...) <- value
\method{vw}{ffdf}(x, ...)
}
\arguments{
  \item{x}{an ffdf object}
}
\keyword{ internal }
