

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Check if OpenMP support has been compiled in
#' 
#' Prints a message to the console.
#' @return logical
#' @examples
#' has_openmp()
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
has_openmp <- function() {
  .Call(has_openmp_)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Calculate distance from origin of each point.
#' 
#' Calculation is done in parallel with OpenMP if available.
#' 
#' \describe{
#'   \item{\code{pdist_r}}{performs the calculation using R}
#'   \item{\code{pdist_c}}{performs the calculation using vanilla serial C code}
#'   \item{\code{pdist_openmp}}{performs the calculation using parallised code
#'    if OpenMP is available, otherwise uses serial C code}
#' }
#' 
#' @param x,y numeric vectors of the same length
#' @param nthreads number of threads to run. Default: 2. Note: this 
#'        number will only have an effect if code is actually compiled
#'        with OpenMP support.  See \code{\link{has_openmp}()}
#' @return distance from origin of each point
#' @examples
#' x <- c(1, 2)
#' y <- c(3, 4)
#' sqrt(x*x + y*y)
#' pdist_r(x, y)
#' pdist_c(x, y)
#' pdist_openmp(x, y)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pdist_openmp <- function(x, y, nthreads = 2) {
  .Call(pdist_openmp_, x, y, nthreads)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname pdist_openmp
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pdist_c <- function(x, y) {
  .Call(pdist_c_, x, y)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname pdist_openmp
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pdist_r <- function(x, y) {
  sqrt(x * x + y * y)
}


