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

        int GFMul3(int s) {
            return GFMul2(s) ^ s;
        }

        int GFMul9(int s) {
            return GFMul3(GFMul3(s));
        }
        public:
        GFMul(){};
        int GFMuln(int n,int s);
    };
}