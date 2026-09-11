# parallel-algs-research

This library is a practice project to experiment with linear algebra types and
operations. Eventually the algorithms will be parallelized.

### Usage:
Something should probably go here...

### TODO:
- no exceptions?
- row vs. col matrix storage (LAPACK/BLAS use col, 
- unit tests (google test, catch2)
- CI hist
- repo name
- .clang-format and .clang-tidy files -- LLVM Style
- CMakeLists.txt
- .gitignore
- github actions
- style guide

### Basic Project Outline:
1. Implement basic serial linalg ops (matvec, matmat, etc.)
2. Implement those with MPI
3. Implement basic linalg solvers/preconds (direct, lu, etc.)
4. Implement those with MPI
