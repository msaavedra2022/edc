

#include <sdsl/wavelet_trees.hpp>
#include <iostream>

using namespace sdsl;
using namespace std;

//(x, y)
vector<pair<int, int>> grid_original = {
    {1, 1},
    {1, 4},
    {1, 14},
    {2,i*d 2},
    {2, 12},
    {3, 3},
    {3, 6},
    {4, 10},
    {7, 12},
    {8, 2},
    {8, 9},
    {8, 14},
    {9, 7},
    {9, 11},
    {10, 5},
    {10, 8}
};


bit_vector build_b(vector<pair<int, int>>& grid_original){
    vector<bool> b = {};
    int i = 1;
    b.push_back(1);
    for (pair<int, int>  p : grid_original) {
        if (p.first == i) {
            b.push_back(0);
        }else if(i+1 != p.first) {
            unsigned int j = i;
            while (j != p.first) {
                b.push_back(1);
                j++;
            }
            b.push_back(0);
            i = p.first;
            
        }else{
            b.push_back(1);
            b.push_back(0);
            i = p.first;
        }
    }

    //transformar vector a bit_vector
    bit_vector result = bit_vector(b.size());
    for (int i = 0; i < b.size(); i++) {
        result[i] = b[i];
    }
    return result;
}


vector<unsigned int> build_grid(vector<pair<int, int> >& grid_original) {
    vector<unsigned int > grid_nueva = {};

    //ordenar array en caso de que esté desordenado
    sort(grid_original.begin(), grid_original.end());

    for (int i = 0; i < grid_original.size(); i++){
        // en wavelet tree se trabaja desde 0 a n-1 en vez de 1 a n como en grid original
        grid_nueva.push_back(grid_original[i].second -1);
    }

    return grid_nueva;
}


//(x1, x2), (y1, y2)
tuple<tuple<int, int>, tuple<int, int>> getRange(bit_vector& b, int x1, int x2, int y1, int y2) {
    rank_support_v<1> rank = rank_support_v<>(&b);
    select_support_mcl<1> select = select_support_mcl<>(&b);

    // + 1 en select porque considera el 0 como el primer elemento
    int x_1 = (select(x1)+1) - (x1 - 1);
    int x_2 = (select(x2 + 1)+1) - (x2 + 1);

    return make_tuple(make_tuple(x_1, x_2), make_tuple(y1, y2));
}


//tranformar puntos de wavelet tree a puntos de grid original
//(x, y) desde 1 a n
pair<int, int> mapPoint(bit_vector& b, pair<int, int> puntos) {
    rank_support_v<1> rank = rank_support_v<1>(&b);
    select_support_mcl<0> select = select_support_mcl<0>(&b);

    int pos = select(puntos.second);
    // cout << "pos = " << pos << endl;

    int ones = rank(pos);
    // cout << "ones = " << ones << endl;
    int x =ones;

    //print result
    // cout << "(" << puntos.first << ", " << puntos.second << ") -> (" <<puntos.first << ", " << x << ")" << endl;

    return make_pair(puntos.first, x);

}

int main(int argc, char* argv[])
{
    vector<pair<int, int>> grid_original = {
        {1, 1},
        {1, 4},
        {1, 14},
        {2, 2},
        {2, 12},
        {3, 3},
        {3, 6},
        {4, 10},
        {7, 12},
        {8, 2},
        {8, 9},
        {8, 14},
        {9, 7},
        {9, 11},
        {10, 5},
        {10, 8}
    };

    cout << "B: " ;
    bit_vector b = build_b(grid_original);
    //print b de 4 en 4
    for (int i = 1; i <= b.size(); i++) {
        cout << b[i-1];
        if (i % 4 == 0) {
            cout << " ";
        }
    }
    cout << endl << endl;
    vector<unsigned int> grid_nueva = build_grid(grid_original);

    // crear y usar int_vector buffer
    int_vector_buffer<> v("cadenaDeNumeros.bin", ios::out);

    //// en wavelet tree se trabaja desde 0 a n-1 en vez de 1 a n
    for (int i = 0; i < grid_nueva.size(); i++) {
        v[i] = grid_nueva[i];
    }

    //crear wavelet tree
    wm_int<> wm(v, v.size());

    //obtener rango de [4, 9] y [8, 12] rangos de 1 a n
    tuple<tuple<int, int>, tuple<int, int>> rango = getRange(b, 4, 9, 8, 12);

    cout <<  "Rango[x1, x2] , [y1, y2] -> [4, 9] y [8, 12]: se transforma en: [" << get<0>(get<0>(rango)) << ", " << get<1>(get<0>(rango)) << "] y [" << get<0>(get<1>(rango)) << ", " << get<1>(get<1>(rango)) << "]" << endl << endl;

    // cono en wavelet tree se trabaja desde 0 a n-1 en vez de 1 a n se le resta 1 a los rangos
    int_vector<>::size_type x1 = get<0>(get<0>(rango)) - 1;
    int_vector<>::size_type x2 = get<1>(get<0>(rango)) - 1;
    int_vector<>::size_type y1 = get<0>(get<1>(rango)) - 1;
    int_vector<>::size_type y2 = get<1>(get<1>(rango)) - 1;

    //obtener el rango de [4, 9] y [8, 12]
    auto result = wm.range_search_2d(x1, x2, y1, y2);


    //representar puntos en grid original
    cout << "Puntos encontrados en grid original: " << endl;
    for (auto it = result.second.begin(); it != result.second.end(); ++it) {
        // +1 porque en wavelet tree se trabaja desde 0 a n-1 en vez de 1 a n ya que mapPoint recibe puntos de 1 a n
        //second es x y first es y para el wavelet tree pero para mapPoint se necesita (x, y)
        pair<int, int> puntos = mapPoint(b, make_pair(it->second + 1, it->first + 1));


        cout << "(" << it->second + 1 << ", " << it->first + 1 << ") -> (" << puntos.first << ", " << puntos.second << ")" << endl;
    }

    auto aa = mapPoint(b, make_pair(9, 11));

    
}