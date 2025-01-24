let
  pkgs = import <nixpkgs> { };
in
pkgs.mkShell {
  packages = with pkgs;  [
    arduino-cli
      # pkgs.texlive.withPackages (ps: [ps.enumitem])
  ];
}
