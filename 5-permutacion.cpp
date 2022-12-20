#include <sdsl/bit_vectors.hpp>
#include <iostream>

using namespace std;
using namespace sdsl;

class Permutacion{
    private:
        int_vector<> perm;
        bit_vector sampled;
        int_vector<> rev_links;
        rank_support_v<> rank;

    public:
        Permutacion(sdsl::int_vector<> perm, sdsl::bit_vector sampled, sdsl::int_vector<> rev_links){
            this->perm = perm;
            this->sampled = sampled;
            this->rev_links = rev_links;
            this->rank = rank_support_v<>(&this->sampled);
        }

        unsigned int read(unsigned int index){
            if(index >= perm.size()) return -1;
            return perm[index-1];
        }

        unsigned int readInverso(unsigned int value){
            if(value > sampled.size()) return -1;
            

            unsigned int index = value;
            bool atajo = false;
            while (perm[index-1] != value){
                index = perm[index-1];
                if (sampled[index-1] == 1 && !atajo){
                    atajo = true;
                    index = rev_links[rank(index-1)];
                }
            }
            return index;
        }

};


int main()
{

    int_vector<> perm = {1, 4, 9, 2, 7, 5, 3, 6, 8};
    bit_vector sampled = {0, 0, 1, 0, 1, 0, 0, 1, 0};
    int_vector<> rev_links = {5, 8, 3};


    Permutacion p = Permutacion(perm, sampled, rev_links);

    //print all readInverso
    for (int i = 0; i < perm.size(); i++) {
        cout << "read Inverso de " << perm[i] << " es " << p.readInverso(perm[i]) << endl;
    }
    return 0;
}