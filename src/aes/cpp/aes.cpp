#include"aes.h"
#include"GFMul.h"
#include<cstring>
#include<iostream>

namespace AES{
    aes:: aes(char *key,char *str){
        this->key=key;
        this->str=str;
        this->len=strlen(this->str);
    }
    
    int aes:: get_int_from_char(char c){
        int result = (int) c;
	    return result & 0x000000ff;
    }
    int aes:: get_word_from_str(char *str_get){
        int one = get_int_from_char(str_get[0]);
        one = one << 24;
        int two = get_int_from_char(str_get[1]);
        two = two << 16;
        int three = get_int_from_char(str_get[2]);
        three = three << 8;
        int four = get_int_from_char(str_get[3]);
        return one | two | three | four;
    }
    void aes:: split_int_to_array(int num, int array[4]) {
        int one = num >> 24;
        array[0] = one & 0x000000ff;
        int two = num >> 16;
        array[1] = two & 0x000000ff;
        int three = num >> 8;
        array[2] = three & 0x000000ff;
        array[3] = num & 0x000000ff;
    }
    void aes:: left_loop4int(int array[4], int step) {
        int temp[4];
        for(int i = 0; i < 4; i++)
            temp[i] = array[i];

        int index = step % 4 == 0 ? 0 : step % 4;
        for(int i = 0; i < 4; i++){
            array[i] = temp[index];
            index++;
            index = index % 4;
        }
    }
    int aes:: get_num_from_sbox(int index) {
        auto get_left4bit = [index]()->int{
            int left = index & 0x000000f0;
	        return left >> 4;
        };
        auto get_right4bit = [index]()->int{
            return index & 0x0000000f;
        };
        int row = get_left4bit();
        int col = get_right4bit();
        return S[row][col];
    }
    int aes:: T(int num, int round) {
        int num_array[4];
    
        const int Rcon[10] = { 0x01000000, 0x02000000,
        0x04000000, 0x08000000,
        0x10000000, 0x20000000,
        0x40000000, (int)0x80000000,
        0x1b000000, 0x36000000 };
        split_int_to_array(num, num_array);

        //for(int i=0;i<4;i++) std:: cout<<"split:"<<num_array[i]<<std:: endl;

        left_loop4int(num_array, 1);//字循环

        //for(int i=0;i<4;i++) std:: cout<<"left_loop:"<<num_array[i]<<std:: endl;

        //字节代换
        for(int i = 0; i < 4; i++)
            num_array[i] = get_num_from_sbox(num_array[i]);

        //for(int i=0;i<4;i++) std:: cout<<"get_num:"<<num_array[i]<<std:: endl;

        auto merge_array_to_int = [num_array]()->int{
           // std:: cout<<num_array[0]<<" "<<num_array[1]<<" "<<num_array[2]<<" "<<num_array[3]<<std:: endl;
            int one = num_array[0] << 24;
            int two = num_array[1] << 16;
            int three = num_array[2] << 8;
            int four = num_array[3];
            //std:: cout<<num_array[0]<<" "<<num_array[1]<<" "<<num_array[2]<<" "<<num_array[3]<<std:: endl;
            //std:: cout<<" one "<<one<<" two "<<two<<" three "<<three<<" four "<<four<<std:: endl;
            return one | two | three | four;
        };

        int result = merge_array_to_int();

        // std:: cout<<"result: "<<result<<std:: endl;
        // int out=result ^ Rcon[round];
        // std:: cout<<"T: "<<out<<std:: endl;

        return result ^ Rcon[round];
    }
    void aes:: extend_key(char *key){

        //std:: cout<<"aes key : "<<key<<std:: endl;
        //ok
        for(int i = 0; i < 4; i++)
            w[i] = get_word_from_str(key + i * 4);

        for(int i = 4, j = 0; i < 44; i++) {
            if( i % 4 == 0) {
                w[i] = w[i - 4] ^ T(w[i - 1], j);
                j++;//下一轮
            }else {
                w[i] = w[i - 4] ^ w[i - 1];
            }
        }

        // std:: cout<<std:: endl;
        // for(int i=0;i<44;i++) std:: cout<<"w: "<<w[i]<<std::endl;
        // std:: cout<<std:: endl;

    }

    void aes:: convert_to_int_array(char *con_str,int pa[4][4]){
        int k = 0;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++) {
                pa[j][i] = get_int_from_char(con_str[k]);
                k++;
            }
        }
    }

    void aes:: add_round_key(int array[4][4], int round){
        int warray[4];
        for(int i = 0; i < 4; i++) {

            //std:: cout<<w[round*4+i]<<std:: endl;

            split_int_to_array(w[ round * 4 + i], warray);

            // std:: cout<<"\n";
            // for(int j=0;j<4;j++) std:: cout<<"j: "<<i<<" wa: "<<warray[j]<<" ";
            // std:: cout<<"\n";

            for(int j = 0; j < 4; j++) {
                array[j][i] = array[j][i] ^ warray[j];
            }
        }
        // for(int i=0;i<4;i++){
        //     for(int j=0;j<4;j++){
        //         std:: cout<<array[i][j]<<" ";
        //     }std:: cout<<std:: endl;
        // }
    }

    void aes:: sub_bytes(int array[4][4]){
        for(int i = 0; i < 4; i++)
		    for(int j = 0; j < 4; j++)
			    array[i][j] = get_num_from_sbox(array[i][j]);
    }

    void aes:: shift_rows(int array[4][4]){
        int rowTwo[4], rowThree[4], rowFour[4];
        for(int i = 0; i < 4; i++) {
            rowTwo[i] = array[1][i];
            rowThree[i] = array[2][i];
            rowFour[i] = array[3][i];
        }
        left_loop4int(rowTwo, 1);
        left_loop4int(rowThree, 2);
        left_loop4int(rowFour, 3);
        for(int i = 0; i < 4; i++) {
            array[1][i] = rowTwo[i];
            array[2][i] = rowThree[i];
            array[3][i] = rowFour[i];
        }
    }

    void aes:: mix_columns(int array[4][4]){
        GFMul gf;
        const int colM[4][4] = { 2, 3, 1, 1,
        1, 2, 3, 1,
        1, 1, 2, 3,
        3, 1, 1, 2 };
        int tempArray[4][4];

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                tempArray[i][j] = array[i][j];
            }
        }
        
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                array[i][j] = gf.GFMuln(colM[i][0],tempArray[0][j]) ^ gf.GFMuln(colM[i][1],tempArray[1][j]) 
                    ^ gf.GFMuln(colM[i][2],tempArray[2][j]) ^ gf.GFMuln(colM[i][3], tempArray[3][j]);
            }
        }
    }

    void aes:: convert_array_to_str(int array[4][4], char *str){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
			    *str++ = (char)array[j][i];
            }
        }
    }
    void aes:: run_aes(){
        // std:: cout<<"I am run_aes\n";
        // std:: cout<<"len : "<<this->len<<std:: endl;
        // std:: cout<<"this is str:"<<this->str<<std:: endl;
        extend_key(this->key);//ok
        int p_array[4][4];
        for(int i=0;i<this->len;i+=16){
            convert_to_int_array(this->str + i, p_array);

            add_round_key(p_array, 0);

            for(int j=1;j<=9;j++){
                sub_bytes(p_array);

                shift_rows(p_array);

                mix_columns(p_array);

                // std::cout<<"i: "<<j<<std:: endl;
                // for(int i=0;i<4;i++){
                //     for(int j=0;j<4;j++){
                //         std:: cout<<p_array[i][j]<<" ";
                //     }
                //     std:: cout<<std:: endl;
                // }

                add_round_key(p_array, j);

            }
            sub_bytes(p_array);

            shift_rows(p_array);

            add_round_key(p_array,10);

            convert_array_to_str(p_array,this->str+i);
        }
    }


    int aes:: get_num_from_s1box(int index){
        auto get_left4bit = [index]()->int{
            int left = index & 0x000000f0;
	        return left >> 4;
        };
        auto get_right4bit = [index]()->int{
            return index & 0x0000000f;
        };
        int row = get_left4bit();
        int col = get_right4bit();
        return S2[row][col];
    }

    void aes:: de_sub_bytes(int array[4][4]){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                array[i][j] = get_num_from_s1box(array[i][j]);
            }
        }
    }

    void aes:: right_loop4int(int array[4], int step) {
        int temp[4];
        for(int i = 0; i < 4; i++)
            temp[i] = array[i];

        int index = step % 4 == 0 ? 0 : step % 4;
        index = 3 - index;
        for(int i = 3; i >= 0; i--) {
            array[i] = temp[index];
            index--;
            index = index == -1 ? 3 : index;
        }
    }

    void aes:: de_shift_rows(int array[4][4]){
        int rowTwo[4], rowThree[4], rowFour[4];
        for(int i = 0; i < 4; i++) {
            rowTwo[i] = array[1][i];
            rowThree[i] = array[2][i];
            rowFour[i] = array[3][i];
        }

        right_loop4int(rowTwo, 1);
        right_loop4int(rowThree, 2);
        right_loop4int(rowFour, 3);

        for(int i = 0; i < 4; i++) {
            array[1][i] = rowTwo[i];
            array[2][i] = rowThree[i];
            array[3][i] = rowFour[i];
        }
    }

    void aes:: de_mix_columns(int array[4][4]){
        int tempArray[4][4];
        GFMul gf;
        const int deColM[4][4] = { 0xe, 0xb, 0xd, 0x9,
        0x9, 0xe, 0xb, 0xd,
        0xd, 0x9, 0xe, 0xb,
        0xb, 0xd, 0x9, 0xe };

        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                tempArray[i][j] = array[i][j];

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                array[i][j] = gf.GFMuln(deColM[i][0],tempArray[0][j]) ^ gf.GFMuln(deColM[i][1],tempArray[1][j]) 
                    ^ gf.GFMuln(deColM[i][2],tempArray[2][j]) ^ gf.GFMuln(deColM[i][3], tempArray[3][j]);
            }
        }
    }

    void aes:: get_array_from4w(int i, int array[4][4]){
        int index = i * 4;
        int colOne[4], colTwo[4], colThree[4], colFour[4];
        split_int_to_array(w[index], colOne);
        split_int_to_array(w[index + 1], colTwo);
        split_int_to_array(w[index + 2], colThree);
        split_int_to_array(w[index + 3], colFour);

        for(int i = 0; i < 4; i++) {
            array[i][0] = colOne[i];
            array[i][1] = colTwo[i];
            array[i][2] = colThree[i];
            array[i][3] = colFour[i];
        }
    }

    void aes:: add_round_to_warray(int a_array[4][4],int b_array[4][4]) {
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                a_array[i][j] = a_array[i][j] ^ b_array[i][j];
            }
        }  
        // for(int i=0;i<4;i++){
        //     for(int j=0;j<4;j++){
        //         std::cout<<a_array[i][j]<<" ";
        //     }
        //     std:: cout<<"\n";
        // }std:: cout<<"\n";
    }

    void aes:: de_aes(){
        //std:: cout<<"I am de_aes, now str is:"<<this->str<<std:: endl;
        extend_key(this->key);
        int c_array[4][4];
        for(int i=0;i<this->len;i+=16){
            convert_to_int_array(this->str + i, c_array);

            add_round_key(c_array, 10);

            int w_array[4][4];
            for(int j=9;j>=1;j--){
                de_sub_bytes(c_array);

                de_shift_rows(c_array);

                de_mix_columns(c_array);
                get_array_from4w(j, w_array);
			    de_mix_columns(w_array);

                add_round_to_warray(c_array, w_array);
            }
            de_sub_bytes(c_array);

            de_shift_rows(c_array);

            add_round_key(c_array, 0);

            convert_array_to_str(c_array,this->str+i);
        }
        //std:: cout<<"de_aes is finished ans :"<<this->str<<std:: endl;
    }
}