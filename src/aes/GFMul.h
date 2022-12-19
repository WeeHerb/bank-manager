#pragma once

namespace AES{
    class GFMul{
        private:
        int GFMul2(int s) {
            int result = s << 1;
            int a7 = result & 0x00000100;

            if(a7 != 0) {
                result = result & 0x000000ff;
                result = result ^ 0x1b;
            }

            return result;
        }

        int GFMul4(int s){
            return GFMul2(GFMul2(s));
        }

        int GFMul8(int s){
            return GFMul2(GFMul4(s));
        }

        int GFMul3(int s) {
            return GFMul2(s) ^ s;
        }

        int GFMul12(int s){
            return GFMul8(s) ^ GFMul4(s);
        }




        public:
        explicit GFMul(){};
        //int GFMuln(int n,int s);
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