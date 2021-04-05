// build.rs

// TODO: Path relative to this file?
// TODO: Warning and optimization lags?
fn main() {
    cc::Build::new()
        .file("../src/gfc.c")
        .include("../include/")
        .compile("gfc");
    println!("cargo:rerun-if-changed=../src/gfc.c");
}
