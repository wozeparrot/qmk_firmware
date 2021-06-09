{
  description = "qmk dev flake";

  inputs.nixpkgs.url = "github:nixos/nixpkgs/c0e881852006b132236cbf0301bd1939bb50867e";
  inputs.flake-utils.url = "github:numtide/flake-utils";
  inputs.poetry2nix.url = "github:nix-community/poetry2nix/11c0df8e348c0f169cd73a2e3d63f65c92baf666";

  outputs = inputs @ {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            (final: prev: {
              python3 = prev.python3.override {
                packageOverrides = self: super: {
                  tomlkit = super.tomlkit.overridePythonAttrs (old: rec {
                    version = "0.11.4";
                    src = super.fetchPypi {
                      inherit (old) pname;
                      inherit version;
                      sha256 = "sha256-MjWpAQ+uVDI+cnw6wG+3IHUv5mNbNCbjedrsYPvUSoM=";
                    };
                  });
                };
              };
            })
          ];
        };
        poetry2nix = import inputs.poetry2nix {
          inherit pkgs;
        };
      in {
        devShell = import ./shell.nix {
          inherit pkgs poetry2nix;
        };
      }
    );
}
