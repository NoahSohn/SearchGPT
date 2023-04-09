{ pkgs }: {
	deps = [
		pkgs.nodejs-16_x
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}