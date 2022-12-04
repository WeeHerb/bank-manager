#include"GFMul.h"

namespace AES{
    int GFMul:: GFMuln(int n,int s){
        int result=0;

        if(n == 1)
            result = s;
        else if(n == 2)
            result = GFMul2(s);
        else if(n == 3)
            result = GFMul3(s);
        else if(n == 0x9)
            result = GFMul9(s);
        else if(n == 0xb)//11
            result = GFMul9(s)^GFMul2(s);
        else if(n == 0xd)//13
            result = GFMul9(s)^GFMul2(s)^GFMul2(s);
        else if(n == 0xe)//14
            result = GFMul9(s)^GFMul3(s)^GFMul2(s);

        return result;
    }
}