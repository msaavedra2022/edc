#include <sdsl/bit_vectors.hpp>
#include <iostream>

using namespace std;
using namespace sdsl;


class SecuenciaUnaria{
    bit_vector bitmap;
    public:
    SecuenciaUnaria(int_vector<> input){
        int j = 0;
        for(int i = 0; i < input.size(); i++){
            for(int k = 0; k < input[i]; k++){
                bitmap[j++] = 1;
            }
            bitmap[j++] = 0;
        }
    }

};