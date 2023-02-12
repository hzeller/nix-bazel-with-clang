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
