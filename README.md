Compilation in clang stdenv in nix.
-----------------------------------

This small example project does not compile with with clang stdenv.

This has been reported in the context of Darwin
https://github.com/NixOS/nixpkgs/issues/150655

... but it seems to be a general issue with how clang and bazel interact
compiling c and c++ files. Hopefully this self-contained example helps
working out the issues.

This is the [shell.nix](./shell.nix) used in this example project, allowing
to choose between regular and clang stdenv.

```nix
{ pkgs ? import <nixpkgs> {} }:
let
  #used_stdenv = pkgs.stdenv;         # this works, using gcc
  used_stdenv = pkgs.clang13Stdenv;   # this is broken, using clang
in
used_stdenv.mkDerivation {
  name = "Testing c and c++ compilation";
  buildInputs = with pkgs;
    [
      bazel_4
    ];
}
```

Clone this repo and run with

```
nix-shell
bazel clean ; bazel build //... && bazel-bin/main
```

This results in this build

### With used_stdenv = pkgs.clang13Stdenv

```bash
$ bazel clean ; bazel build //... && bazel-bin/main
INFO: Starting clean (this may take a while). Consider using --async if the clean takes more than several minutes.
INFO: Analyzed 2 targets (15 packages loaded, 63 targets configured).
INFO: Found 2 targets...
ERROR: /home/testuser/src/my/bazel-with-clang/BUILD:13:10: Compiling main.cc failed: (Exit 1): clang failed: error executing command /nix/store/i973rwv7n9pq74iac8jlly9s3xlrr0bc-clang-wrapper-13.0.1/bin/clang -U_FORTIFY_SOURCE -fstack-protector -Wall -Wthread-safety -Wself-assign -Wunused-but-set-parameter -Wno-free-nonheap-object ... (remaining 25 argument(s) skipped)

Use --sandbox_debug to see verbose messages from the sandbox
main.cc:1:10: fatal error: 'iostream' file not found
#include <iostream>
         ^~~~~~~~~~
1 error generated.
INFO: Elapsed time: 0.216s, Critical Path: 0.03s
INFO: 12 processes: 11 internal, 1 linux-sandbox.
FAILED: Build did NOT complete successfully
```

### With used_stdenv = pkgs.stdenv

Compiling with the default stdenv (change the comments in `shell.nix`) works

```bash
$ bazel clean ; bazel build //... && bazel-bin/main
INFO: Starting clean (this may take a while). Consider using --async if the clean takes more than several minutes.
INFO: Analyzed 2 targets (15 packages loaded, 62 targets configured).
INFO: Found 2 targets...
INFO: Elapsed time: 0.903s, Critical Path: 0.16s
INFO: 12 processes: 6 internal, 6 linux-sandbox.
INFO: Build completed successfully, 12 total actions
in C   function foo() -> 42
in C++ function bar() -> 42

== SUCCESS ==
got values 42 and 42
```
