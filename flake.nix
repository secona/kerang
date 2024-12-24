{
  description = "Kerang";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: 
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
      };

      kerang = pkgs.mkDerivation {
        pname = "kerang";
        version = "0.0.0";

        src = ./.;

        nativeBuildInputs = [
          pkgs.cmake
          pkgs.gcc
        ];

        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
        ];

        doInstallCheck = false;
        buildInputs = [];
      };
    in {
      packages.default = kerang;

      devShells.default = pkgs.mkShell {
        buildInputs = [
          pkgs.cmake
          pkgs.gcc
          pkgs.gtest
        ];
      };
    });
}
