# [Project Name] C++ Style Guide

Adapted from the [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html),
trimmed to what's relevant for this project.

---

## 1. Golden Rule

If you're editing existing code, match the style already there, even if it's
not exactly what this guide says. Consistency within a file matters more than
any individual rule. Open a PR to fix the style itself rather than drifting.

## 2. Language Standard

- **C++17.** No compiler-specific extensions.
- No RTTI/exceptions restriction — *unlike LLVM.* LLVM bans these for compiler
  binary-size reasons that don't apply to this project.
  - **Default:**use exceptions for unrecoverable
    error conditions (e.g. dimension mismatch in matrix multiply, singular
    matrix in a solve). Use `assert` for programmer-error conditions that
    should never happen in correct code (see §7).
  - RTTI (`dynamic_cast`) — avoid by default, same as LLVM, since a
    numerical library shouldn't need deep polymorphic class hierarchies. If a
    real use case comes up, add it deliberately, don't reach for it out of
    habit.

## 3. Formatting — enforced by tooling, not by hand

- Run `clang-format` (LLVM style, or our `.clang-format` once we commit one)
  before every commit. Don't hand-format; don't argue about braces.
- Run `clang-tidy` in CI. If it flags something you disagree with, fix the
  `.clang-tidy` config, don't just ignore the warning.
- 80-column line width.
- Spaces, not tabs. No trailing whitespace.

## 4. Naming Conventions

**Default — simpler than LLVM's, closer to common C++ practice:**

| Kind | Convention | Example |
|---|---|---|
| Types (classes, structs, enums) | `PascalCase` | `Matrix`, `SolverStatus` |
| Functions / methods | `camelCase` | `multiply()`, `isSquare()` |
| Variables (local, params) | `camelCase` | `rowCount`, `tolerance` |
| Private/protected member variables | `camelCase_` (trailing underscore) | `numRows_`, `data_` |
| Constants / `constexpr` | `kPascalCase` | `kDefaultTolerance` |
| Namespaces | `lower_snake_case` | `linalg`, `linalg::mpi` |
| Template parameters | `PascalCase` | `template <typename ScalarType>` |

Avoid abbreviations unless they're standard in the field (`lhs`/`rhs` for
matrix operands is fine; `mtx` for "matrix" is not — write it out).

## 5. Comments & Documentation

- Every file gets a short header comment: what this file contains.
- Every public class and function gets a Doxygen comment (`///`), even a
  one-liner. This matters more here than in most projects since a
  collaborator new to linalg needs to know *what a function assumes*, not
  just what it's named.
- Comment on **why**, not **what** — the code already says what it does.
- For non-obvious math (e.g. "why this pivoting strategy," "why this
  communication pattern"), a comment with a one-line justification or a
  reference is worth more than a paragraph of prose.

```cpp
/// Multiplies this matrix by \p vec, returning the result.
///
/// \p vec.size() must equal numCols(); throws std::invalid_argument
/// otherwise.
Vector<T> multiply(const Vector<T>& vec) const;
```

## 6. `#include` Order

1. This file's own header (if a `.cpp` implementing an `.h`)
2. Other project headers (`linalg/...`)
3. Third-party library headers (MPI, LAPACK, etc.)
4. Standard library headers

Each group sorted alphabetically, separated by a blank line.

## 7. Error Handling & Assertions

- `assert()` for conditions that indicate a **bug in our own code** — should
  never fire in correct, correctly-used code. Always include a message.
  ```cpp
  assert(rows_ > 0 && "Matrix must have positive row count");
  ```
- Exceptions for conditions that indicate **bad input or a runtime failure**
  the caller could hit legitimately (bad dimensions, singular matrix, MPI
  failure) — see §2.
- Never silently ignore an error condition. If a function can fail, its
  return type or its documented exceptions should say so.

## 8. General Practices (kept from LLVM)

- Prefer `static_cast`/`const_cast`/`reinterpret_cast` over C-style casts.
- Never `using namespace std;` in a header. Fine in a `.cpp` file for our own
  project namespace only.
- Use range-based `for` loops over manual iterator loops wherever possible.
- Prefer early exits/`continue` over deep nesting.
- No `else` after a `return`/`break`/`continue`.
- Preincrement (`++i`) over postincrement (`i++`) unless you specifically
  need the old value.
- Header guards: use `#pragma once` (simpler than LLVM's manual guard
  convention, universally supported by our target compilers).
- Every header should compile on its own (include everything it uses;
  don't rely on include order from other files).

## 9. Things LLVM's Guide Covers That This Project Dropping

- Preferring LLVM's own container library (`SmallVector`, etc.) over the STL
  — we just use `std::` / whatever numerical library we adopt in Phase 4.
- Library-layering / linker-ordering rules — matters at LLVM's multi-hundred-
  library scale, not ours.
- `raw_ostream` — LLVM-specific I/O class; we use `<iostream>`/`<format>`.
- Default-label-in-switch and virtual-method-anchor rules — compiler/ABI
  concerns specific to LLVM's build.

---

*Questions or disagreements with a default in this doc — especially §2 and
§4 — should turn into a PR editing this file, not silent divergence.*
