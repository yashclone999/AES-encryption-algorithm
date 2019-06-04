#include <iostream>
#include <vector>

using namespace std;



vector<int> last_row( vector<int > sbox, vector<vector<int> > key)
{
    vector<int> last_row(4, 0);
    for(int i =0; i<4; i++)
    {
        last_row[i] = key[3][(i+1)%4] ;
    }

    for(int i =0; i<4; i++)
    {
        last_row[i] = sbox[last_row[i]] ;
    }

    return last_row ;
}
int main()
{

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
    std::vector<std::vector<int> > initial_key = {{89, 97, 115,104 },{32,84,104,97},{107, 117, 114, 5},{5,5,5,5}};


    std::vector<std::vector<int> > round_const = { {1, 0, 0, 0},
				{2, 0, 0, 0},
				{4, 0, 0, 0},
				{8, 0, 0, 0},
				{16,0, 0, 0},
				{32,0, 0, 0},
				{64,0, 0, 0},
				{128,0, 0, 0},
				{27,0, 0, 0},
				{54,0, 0, 0}};

    vector<int> lastrow(4, 0);
    vector<int> temp(4, 0);

    for( int i = 0; i<10; i++)
    {
        //Implements rearrangement of last column and substitution
        lastrow = last_row(sbox, initial_key);

        //XOR with round constant
        for(int j = 0; j<4; j++)
        {
            temp[j] = lastrow[j]^round_const[i][j] ;
        }

        //XOR with the corresponding column of the previous key
        for( int j = 0; j<4; j++)
        {
            for(int k = 0; k<4; k++)
            {
                temp[k] = initial_key[j][k]^temp[k] ;
            }
            initial_key[j] = temp ;
        }

        //Printing round key
        for( int i = 0; i<4; i++)
        {
        for(int j = 0; j<4; j++)
        {
            cout<<hex<<initial_key[j][i]<<' ' ;
        }
        cout<<"\n\n" ;
        }
    }



    return 0;
}
