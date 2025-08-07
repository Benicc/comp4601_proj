#include <iostream>
#include <vector>
#include <iomanip>


#include "sha3_256.h"
#include "Keccak-readable-and-compact.c"
#include <ap_int.h>

int main() {
    const int num_blocks = 16384;    // Same as Merkle tree leaves
    const int block_size = 64;
    const int hash_size = 32;
    // Create a buffer to hold one input block (all zeros)
    ap_uint<512> input_block_val = 0;
    for (int i = 0; i < 64; i++) {
        input_block_val.range(8*(i+1)-1, 8*i) = i % 16;
    }
    std::vector<unsigned char> input_block(block_size, input_block_val);

    // Prepare to store all output hashes
    std::vector<std::vector<unsigned char>> outputs(num_blocks, std::vector<unsigned char>(hash_size));

    for (int i = 0; i < num_blocks; ++i) {
        // Optionally, modify input_block to simulate different data
        // For example, set first byte = i % 256 to make each block unique:
        // input_block[0] = static_cast<unsigned char>(i % 256);

        sha3_opt_256(input_block.data(), outputs[i].data());
    }

    // Print the first hash
    std::cout << "First block hash: ";
    for (unsigned char b : outputs[0]) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    }
    std::cout << std::endl;

    // Print the last hash
    std::cout << "Last block hash: ";
    for (unsigned char b : outputs[num_blocks - 1]) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    }
    std::cout << std::endl;
    return 0;
}