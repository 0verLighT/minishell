{ pkgs ? import <nixpkgs> {} }:
(pkgs.mkShell.override { stdenv = pkgs.clangStdenv; }) {
  packages = [ 
    pkgs.doxygen
    pkgs.graphviz
    pkgs.meson
    pkgs.zlib
    pkgs.valgrind
  ];
  shellHook = ''echo nix-shell for minishell'';
}
