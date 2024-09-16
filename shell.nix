with import <nixpkgs> { };
{ pkgs ? import <nixpkgs> { } }:

stdenv.mkDerivation {
  name = "cryptanalysislib";
  src = ./.;

  buildInputs = [
    cmake
    libtool
    autoconf
    automake
    autogen
    gnumake
    lldb
    clang_17
    clang-tools_17
    llvm_17
    llvmPackages_17.libcxx
    llvmPackages_17.openmp
    git
    gcc
    gtest
    gbenchmark
    openssl     # needed for libcoro
    boost       # needed for folly
    double-conversion # needed for folly
    fast-float  # needed for folly
    libevent    # needed for folly
    fmt         # needed for folly
    glog        # needed for folly
    lz4         # needed for folly
    zstd        # needed for folly
    snappy      # needed for folly
    liburing    # needed for folly
    libsodium   # needed for folly
    libaio      # needed for folly

  ] ++ (lib.optionals pkgs.stdenv.isLinux ([
    flamegraph
    gdb
    linuxKernel.packages.linux_6_6.perf
    pprof
    valgrind
    massif-visualizer
  ]));
}
