#include<gtest/gtest.h>

#include "aes/aes.h"
const static char *aesKey = "1234567890abcdef";

void test(const std::string& expect){
    std::string actual(expect);
    auto& buff = actual;
    char *origin_data = buff.data();
    unsigned long long len = buff.size();
    AES::aes en(aesKey, origin_data,len);
    en.run_aes();

    AES::aes de(aesKey, buff.data(),len);
    de.de_aes();
    ASSERT_EQ(expect, actual);
}
TEST(Decrypt, AESAssert) {
    auto str = R"delimiter(
3
1
1
1
1
1
1
0
0
2
2
2
2
2
0
0
0
3
3
3
3
3
1
2

10000.000000
1671453960

-5000.000000
1671453966
2

10000.000000
1671453971

-1234.000000
1671453975
        )delimiter";
    std::string buff(str);
    if (buff.size() % 16 != 0) {
        buff.resize((buff.size() / 16 + 1) * 16);
    }
    for(int len = 16; len < buff.size() - 16; len+=16){
        for(int i = 0; i+len < buff.size(); i+=1){
            auto sub = buff.substr(i, len);
            std::cout << "Testcase: " << i  << "-" << i + len << " len " << len << std::endl;
            test(sub);
        }
    }
}