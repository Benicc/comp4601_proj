#include "data_mover.h"

void data_mover(volatile uint32_t *input, int size, hls::stream<ap_uint<512>> &out, hls::stream<ap_uint<256>> &res,
    uint32_t *result_mem) {
#pragma HLS INTERFACE m_axi     port=input offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi     port=result_mem offset=slave bundle=gmem
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE axis port=res
#pragma HLS INTERFACE s_axilite port=return bundle=control
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=size bundle=control
#pragma HLS INTERFACE s_axilite port=result_mem bundle=control

    int n_chunks = size / 16;

    //pack integers words into a packet
    //these words fill the 512 bit width
    for (int i = 0; i < n_chunks; i++) {
        ap_uint<512> packet = 0;
        for (int j = 0; j < 16; j++) {
            ap_uint<32> word = input[i * 16 + j];
            packet.range((j + 1) * 32 - 1, j * 32) = word;
        }
        out.write(packet);
    }

    ap_uint<256> val = res.read();

    for (int i = 0; i < 8; i++) {
        result_mem[i] = val.range((i + 1) * 32 - 1, i * 32);
    }
}

