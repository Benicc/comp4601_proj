#include <hls_stream.h>
#include <ap_int.h>

void dummy_hash(
    hls::stream<ap_uint<512>> &in,
    hls::stream<ap_uint<256>> &out
) {
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<256> dummy_result = 0;


    ap_uint<512> data = in.read();
    // dummy_result ^= data.range(255, 0);
    dummy_result.range(31, 0) = 12;


    // Write ONE final 256-bit dummy hash
    out.write(dummy_result);
}