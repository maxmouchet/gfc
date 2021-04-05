#[repr(C)]
pub struct GFC {
    _private: [u8; 0],
}

extern "C" {
    fn gfc_init(range: u64, rounds: u64, seed: u64) -> *mut GFC;
    fn gfc_destroy(gfc: *mut GFC);
    fn gfc_decrypt(gfc: *const GFC, m: u64) -> u64;
    fn gfc_encrypt(gfc: *const GFC, m: u64) -> u64;
}

fn main() {
    let y = unsafe {
        let gfc = gfc_init(1000, 3, 42);
        let enc = gfc_encrypt(gfc, 10);
        let dec = gfc_decrypt(gfc, enc);
        gfc_destroy(gfc);
        (enc, dec)
    };
    println!("{:?}", y);
}
