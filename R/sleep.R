

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Sleep inside a forloop in C in serial or in parallel
#' 
#' @param N number of 0.1 second sleeps
#' @param nthreads number of threads
#' @return None
#' @examples
#' system.time(sleep_c(2))
#' system.time(sleep_openmp(2, nthreads = 3))
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sleep_c <- function(N = 2) {
  .Call(sleep_c_, N)
  invisible()
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname sleep_c
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sleep_openmp <- function(N = 2, nthreads = 2) {
  .Call(sleep_openmp_, N, nthreads)
  invisible()
}
