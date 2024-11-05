
<!-- README.md is generated from README.Rmd. Please edit that file -->

# simpleopenmp

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
[![CRAN](https://www.r-pkg.org/badges/version/simpleopenmp)](https://CRAN.R-project.org/package=simpleopenmp)
[![R-CMD-check](https://github.com/coolbutuseless/simpleopenmp/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/coolbutuseless/simpleopenmp/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

`simpleopenmp` is a demonstration package showing how
[OpenMP](https://www.openmp.org/) could be used within an R package to
speed up C calculations.

OpenMP itself provides tools for performing C code in parallel using
directives supported by many compilers.

## Installation

You can install the latest development version from
[GitHub](https://github.com/coolbutuseless/simpleopenmp) with:

``` r
# install.package('remotes')
remotes::install_github('coolbutuseless/simpleopenmp')
```

## Simple benchmark

The following benchmarking was performed on macOS M2 mac mini with 10
cores.

The benchmark shows:

- Serial C version is faster than R
- OpenMP with `nthreads = 1` is the same as the serial C version
- OpenMP with `nthreads = 2` is approx 1.5x faster than the serial C
  version.
- `nthreads = 4` and `8` are about the same speed - about 2.5x faster
  than the serial C version.

``` r
# was the package compiled with openmp support?
has_openmp()
#> OpenMP enabled. Num threads = 1
#> [1] TRUE
```

``` r
library(simpleopenmp)

set.seed(1)
x <- runif(1e6)
y <- runif(1e6)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sanity check all results are equal
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
res_r      <- pdist_r(x, y)
res_c     <- pdist_c(x, y)
res_openmp <- pdist_openmp(x, y)

stopifnot(isTRUE(all.equal(res_r, res_c)))
stopifnot(isTRUE(all.equal(res_r, res_openmp)))

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Simple benchmark
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bench::mark(
  pdist_r(x, y),
  pdist_c(x, y),
  pdist_openmp(x, y, nthreads = 1),
  pdist_openmp(x, y, nthreads = 2),
  pdist_openmp(x, y, nthreads = 4),
  pdist_openmp(x, y, nthreads = 8),
  relative = TRUE
)[, 1:5] |> knitr::kable()
```

| expression                       |       min |    median |   itr/sec | mem_alloc |
|:---------------------------------|----------:|----------:|----------:|----------:|
| pdist_r(x, y)                    | 34.107639 | 11.611371 |  1.000000 |         2 |
| pdist_c(x, y)                    |  3.872677 |  2.640598 |  4.597156 |         1 |
| pdist_openmp(x, y, nthreads = 1) |  3.884152 |  2.698892 |  4.479240 |         1 |
| pdist_openmp(x, y, nthreads = 2) |  1.894535 |  1.655774 |  7.351177 |         1 |
| pdist_openmp(x, y, nthreads = 4) |  1.000000 |  1.124378 | 11.642349 |         1 |
| pdist_openmp(x, y, nthreads = 8) |  1.424043 |  1.000000 | 12.011554 |         1 |

## Status by Platform

### macOS

- By default macOS does not include the necessary OpenMP libraries.
- If you follow the instructions from
  [mac.r-project.org](https://mac.r-project.org/openmp/) it is possible
  to download and install the header and dynamic library.
- If openmp not found, then the C code should silently/gracefully
  degrade to running the code serially.
- This setup has been tested on my macOS M2 machine with `*.h` files
  located in `/usr/local/include/` and the library located at
  `/usr/local/lib/libomp.dylib`

### Linux

- This works under the machines provided by github codespaces.
- Any feedback or notes from Linux users is most welcome!

### Windows

- Currently untested as I do not have access to a windows machine with
  openmp
- Any feedback or notes from Windows users is most welcome!

# Issues

If you can help with any of these issues please see matching issue on
[github](https://githu.com/coolbutuseless/simpleopenmp/issues)

- `cleanup` script doesn’t seem to run when doing package build within
  RStudio
- Untested on windows
- Untested on windows
- I’m unsure of when `configure.win` is required. This file is included
  in this package but is completely empty
- compilation complaints
  - `omp_sched_monotonic = 0x80000000` and other places cause a warning
    related to `-Wpedantic` because
    `ISO C restricts enumerator values to range of 'int' (2147483648 is too large)`
  - `extern void *llvm_omp_target_dynamic_shared_alloc()` causes a
    warning due to `-Wstrict-prototypes` because
    `a function declaration without a prototype is deprecated in all versions of C`

## macOS: Compilation setup and detecting OpenMP

On windows and linux, I think R should automatically link in OpenMP and
set the appropriate `$SHLIB_OPENMP_CFLAGS` flag.

For macOS, bespoke installation and detection of OpenMP is required
using the details specified on
[mac.r-project.org](https://mac.r-project.org/openmp/).

The `configure` script in this package is heavily based upon the work of
[Jeroen Ooms](https://github.com/jeroen) and [Gabor
Csardi](https://github.com/gaborcsardi).

- `configure` standard shell script run by`R CMD INSTALL` before
  anything else
  - Bourne Shell script. Must be marked as executable.
- `configure.win` is needed .. ?? When? Always? Can it be empty?
- `src/Makevars.in` is the template which gets turned into `Makevars` by
  the `configure` script
- `clean` run by the R build process after the package has been
  compiled, but before the tarball is built. (Must be an executable
  script)

Notes:

- You may need to install `checkbashisms` script as `R CMD CHECK`
  requires this for checking the `configure` and `clean` scripts
  - On macOS install [homebrew](https://brew.sh/) and run
    `brew install checkbashisms`

## References:

- [OpenMP on Mac](https://mac.r-project.org/openmp/)
- <https://www.devgem.io/posts/building-an-openmp-project-with-cmake-on-mac-with-apple-m2-pro>
- [Writing R Exensions -
  OpenMP](https://cran.r-project.org/doc/manuals/r-release/R-exts.html#OpenMP-support)
- Stackoverflow;
  - <https://stackoverflow.com/questions/68263165/installing-r-on-osx-big-sur-edit-and-apple-m1-for-use-with-rcpp-and-openmp>
