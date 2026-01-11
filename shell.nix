{ pkgs ? import <nixpkgs> {} }:
(pkgs.mkShell.override { stdenv = pkgs.clangStdenv; }) {
  packages = with pkgs; [
    doxygen
    graphviz
    meson
    ninja
  ]
  ++ lib.optionals stdenv.isLinux [
    valgrind
    gdb
  ];
  shellHook = ''echo nix-shell for minishell'';
}
