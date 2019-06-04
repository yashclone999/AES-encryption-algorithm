#include <iostream>
#include<math.h>
#include<vector>
using namespace std;

vector<vector<int> > xor_matrices ( vector<vector<int> >  state_matrix1, vector<vector<int> >  state_matrix2)
{
    vector<vector<int> > XOR (4, vector<int>(4,0)) ;
    for( int j = 0; j<4 ; j++)
        {
            for( int i = 0; i<4; i++)
            {
                XOR[i][j] = state_matrix1[i][j]^state_matrix2[i][j] ;

            }
        }
        return XOR ;
}


vector<vector<int> > sub_bytes(vector<vector<int> > state_matrix, vector<int> sbox)
{
    for( int j = 0; j<4 ; j++)
        {
            for( int i = 0; i<4; i++)
            {
                state_matrix[i][j] = sbox[state_matrix[i][j]] ;

            }
        }
        return state_matrix;
}

vector<vector<int> > shift_rows(vector<vector<int> > state_matrix)
{
    for(int i = 1; i<4;i++)//for 3 rows
        {
            vector<int> new_row(4,0) ;
            for(int k = 0; k<4; k++)//each element
            {
                new_row[k] = state_matrix[i][(k+i)%4];
            }
            state_matrix[i] = new_row ;
        }
        return state_matrix ;
}

vector<vector<int> > mix_column(vector<vector<int> > state_matrix, vector<vector<int> > M )
{
     for( int cl = 0; cl<4; cl++)
        {

        vector<int> temp_mix_col(4,0) ;
        for(int i=0;i<4;++i)
        {

                temp_mix_col[i]=0;
                for(int k=0;k<4;++k)
                    {
                        uint8_t product = 0;
                        uint8_t carry;
                        uint8_t temp_1 = M[i][k];
                        uint8_t temp_2 = state_matrix[k][cl];
                        while(temp_2 != 0)
                        {
                            if(temp_2%2 == 1)
                            {
                                product ^= temp_1;
                            }
                            carry = (temp_1 & 128);
                            temp_1 <<= 1;
                            if( carry == 128)
                            {
                                temp_1 ^= 283;
                            }
                            temp_2 >>= 1;

                        }
                        temp_mix_col[i] ^= (product);
                    }

        }
        for(int i = 0; i<4; i++)
            {
                state_matrix[i][cl] = temp_mix_col[i] ;
            }
        }

        return state_matrix ;
}

vector<vector<int> > xor_key(vector<vector<int> > state_matrix, vector<vector<int> > key )
{
    for(int i = 0; i<4;i++)
        {
            for(int k = 0; k<4; k++)//each element
            {
                state_matrix[i][k] = state_matrix[i][k]^key[i][k];

            }
        }
        return state_matrix ;
}

int main()
{
    vector<vector<int> > key_zero =
    {{83,79,77, 69},
    {32,49, 50,56},
    {32,66,73,84},
    {32, 75, 69, 89}};

    vector<vector<vector<int> >> key =
    {{{51,19,120,125},
    {10,94,43,46},
    {24,112,2,7},
    {3,98,103,98}},

    {{0, 19, 107, 22},
    {207, 145, 186, 148},
    {178, 194, 192, 199},
    {252, 158, 249,155}}};


    vector<int> sbox = { 99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118
    , 202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192
    , 183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21
    , 4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117
    , 9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132
    , 83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207
    , 208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168
    , 81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210
    , 205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115, 96
    , 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219, 224, 50
    , 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121, 231, 200, 55
    , 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8, 186, 120, 37
    , 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138, 112, 62, 181
    , 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158, 225, 248, 152, 17
    , 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223,140, 161, 137, 13
    , 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22};

    vector<vector<int> > state_matrix1 = {{34,145,103,206},{49, 51,23,41 }, {64,65,76,139}, {190,100,85,228}};
    vector<vector<int> > state_matrix2 = {{34,145,103,206},{49, 51,23,41 }, {64,65,76,139}, {190,100,85,245}};
    vector<vector<int> > M ={{2,3,1,1},{1,2,3,1},{1,1,2,3},{3,1,1,2}} ;

    //XOR state matrices with key zero
	state_matrix1 = xor_matrices(state_matrix1, key_zero);
	state_matrix2 = xor_matrices(state_matrix2, key_zero);

    vector<vector<int> > XOR (4, vector<int>(4,0)) ;

    //number of rounds 2
    for(int z = 0; z<2; z++)
    {

        //sub bytes
        state_matrix1 = sub_bytes(state_matrix1, sbox);
        state_matrix2 = sub_bytes(state_matrix2, sbox);
        //taking XOR of 2 state matrices
        XOR = xor_matrices(state_matrix1, state_matrix2);


        //shift rows
        state_matrix1 = shift_rows(state_matrix1);
        state_matrix2 = shift_rows(state_matrix2);
        //taking XOR of 2 state matrices
        XOR = xor_matrices(state_matrix1, state_matrix2);


        //mix column
        state_matrix1 = mix_column(state_matrix1, M);
        state_matrix2 = mix_column(state_matrix2, M);
        //taking XOR of 2 state matrices
        XOR = xor_matrices(state_matrix1, state_matrix2);


        //XOR with key
        state_matrix1 = xor_key(state_matrix1, key[z]);
        state_matrix2 = xor_key(state_matrix2, key[z]);
        //taking XOR of 2 state matrices
        XOR = xor_matrices(state_matrix1, state_matrix2);


    }

    //printing XOR of the latest state matrices
    for(int i = 0; i<4;i++)
                {

                    for(int k = 0; k<4; k++)
                    {
                        cout<<hex<<XOR[i][k]<<' ';
                    }
                    cout<<"\n\n" ;
                }









    return 0;
}
