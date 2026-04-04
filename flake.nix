{
  description = "Flake minishell";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
          nativeBuildInputs = with pkgs; [
            doxygen
            graphviz
            meson
            ninja
            clang-tools
            pkg-config
            readline
            lldb_22
          ] ++ pkgs.lib.optionals pkgs.stdenv.isLinux [
            valgrind
            gdb
          ];

          shellHook = ''cc --version'';
        };
      }
    );
}
