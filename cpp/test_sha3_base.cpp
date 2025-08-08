#include "Keccak-readable-and-compact.c"
#include <ap_int.h>
#include <vector>

int main() {
    const int num_blocks = 16384;    // Same as Merkle tree leaves
    const int block_size = 64;
    const int hash_size = 32;
    // Create a buffer to hold one input block (all zeros)

    std::vector<unsigned char> big_input(num_blocks * block_size);

    for (int i = 0; i < (num_blocks * block_size); ++i) {
        big_input[i] = static_cast<unsigned char>(i % 16);
    }

    unsigned char * fips_output = new unsigned char[32];

 
    FIPS202_SHA3_256(big_input.data(), block_size * num_blocks, fips_output);
   


    printf("SUCCESS!!!!\n");
    printf("HASH OUTPUT: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", fips_output[i]);
    }
    printf("\n");
    
    return 0;
}