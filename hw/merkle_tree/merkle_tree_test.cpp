#include <cstring>
#include <hls_stream.h>
#include <ap_int.h>
#include "merkle_tree.h"
#include <cstdint>

#define TEST_SIZE 262144

int main() {
    uint32_t input_data[TEST_SIZE];

    // Initialize input data
    memset(input_data, 0, TEST_SIZE);
    for (int i = 0; i < 5; ++i) {
        input_data[i] = i + 1;
    }

    hls::stream<ap_uint<512>> out_stream;
    int n_chunks = TEST_SIZE / 16;
    int n_rem_words = TEST_SIZE % 16;
    
    for (int i = 0; i < n_chunks; i++) {
        ap_uint<512> packet = 0;
        for (int j = 0; j < 16; j++) {
            ap_uint<32> word = input_data[i * 16 + j];
            packet.range((j + 1) * 32 - 1, j * 32) = word;
        }
        out_stream.write(packet);
    }

    if (n_rem_words) {
        ap_uint<512> packet = 0;
        for (int i = 0; i < n_rem_words; i++) {
            ap_uint<32> word = input_data[n_chunks * 16 + i];
            packet.range((i + 1) * 32 - 1, i * 32) = word;
        }
        out_stream.write(packet);
    }

    hls::stream<ap_uint<256>> res;

    merkle_tree(out_stream, res);

    ap_uint<256> res_int = res.read();

    uint32_t out_0 = (uint32_t)res_int.range(31, 0);
    uint32_t out_1 = (uint32_t)res_int.range(63, 32);
    uint32_t out_2 = (uint32_t)res_int.range(95, 64);
    uint32_t out_3 = (uint32_t)res_int.range(127, 96);
    uint32_t out_4 = (uint32_t)res_int.range(159, 128);
    uint32_t out_5 = (uint32_t)res_int.range(191, 160);
    uint32_t out_6 = (uint32_t)res_int.range(223, 192);
    uint32_t out_7 = (uint32_t)res_int.range(255, 224);

    std::cout << "Result0: " << out_0 << "\r\n";
    std::cout << "Result1: " << out_1 << "\r\n";
    std::cout << "Result2: " << out_2 << "\r\n";
    std::cout << "Result3: " << out_3 << "\r\n";
    std::cout << "Result4: " << out_4 << "\r\n";
    std::cout << "Result5: " << out_5 << "\r\n";
    std::cout << "Result6: " << out_6 << "\r\n";
    std::cout << "Result7: " << out_7 << "\r\n";

    return 0;
}