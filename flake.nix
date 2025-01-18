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

      kerang = pkgs.stdenv.mkDerivation {
        pname = "kerang";
        version = "0.0.0";

        src = ./.;

        nativeBuildInputs = with pkgs; [ cmake cmocka ];

        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
        ];

        buildPhase = ''
          make kerang
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp kerang $out/bin/
        '';
      };
    in {
      packages.default = kerang;

      devShells.default = pkgs.mkShell {
        inputsFrom = [kerang];
        buildInputs = with pkgs; [ clang-tools ];
      };
    });
}
