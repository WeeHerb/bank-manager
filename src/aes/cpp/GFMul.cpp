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
            result = GFMul8(s)^s;
        else if(n == 0xb)//11
            result = GFMul8(s)^s^GFMul2(s);
        else if(n == 0xd)//13
            result = GFMul12(s)^s;
        else if(n == 0xe)//14
            result = GFMul12(s)^GFMul2(s);
        else if(n == 0xc)//12
            result = GFMul12(s);
        else if(n == 0x8)
            result = GFMul8(s);
        else if(n == 4)
            result = GFMul4(s);

        return result;
    }
}