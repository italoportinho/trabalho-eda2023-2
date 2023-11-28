// Copyright (C) 2023 - Italo Portinho
// Para compilar(windows): g++ main.cpp -o main

#include <cstdio>
#include <cstdlib>
#include <map>
#include <ctime>

int main() {
    std::map<int, int> map_tree{};
    int chave = 0;

    /************************************************************************/
    /********************** Operações no std::map ***************************/
    /************************************************************************/

    std::clock_t map_start = std::clock();
    int map_deletes = 0;
    for (int i = 0; i < 100000; i++) {
        chave = rand();
        map_tree[chave] = chave;
        if (i > 100 && i % 100 == 0) {
            map_tree.extract(rand());
            map_deletes++;
        }
    }
    std::clock_t map_end = std::clock();
    std::clock_t map_search_start = std::clock();
    int map_search_hits = 0;
    for (int i = 0; i < 100000; i++) {
        chave = rand();
        if (map_tree.find(chave) != map_tree.end())
            map_search_hits++;
    }
    std::clock_t map_search_end = std::clock();


    /************************************************************************/
    /********************** Resultados std::map *****************************/
    /************************************************************************/
    double map_time_ms = 1000.0*(map_end - map_start)/CLOCKS_PER_SEC;
    printf("\nMAP_ms == %f , ", map_time_ms);
    printf("deletes_MAP == %d , ", map_deletes);
    printf("MAP_search_hits == %d , ", map_search_hits);
    double map_search_ms = 1000.0*(map_search_end - map_search_start)/CLOCKS_PER_SEC;
    printf("MAP_search_ms == %f \n", map_search_ms);
}
