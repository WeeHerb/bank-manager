#pragma once

namespace AES{
    class GFMul{
        public:
        explicit GFMul(){};
        int GFMuln(int a,int b) {
            int p = 0;
            int hi_bit_set;
            for (int counter = 0; counter < 8; counter++) {
                if ((b & int(1)) != 0) {
                    p ^= a;
                }
                hi_bit_set = (int) (a & int(0x80));
                a <<= 1;
                if (hi_bit_set != 0) {
                    a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */
                }
                b >>= 1;
            }
            return p;
        }
    };
}