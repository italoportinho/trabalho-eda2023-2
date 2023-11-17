// Copyright (C) 2023 - Italo Portinho
// Para compilar(windows): g++ main.cpp -o main
#include <cstdio>
#include "./redblack/redblack.hpp"

int main() {
    ArvoreRedBlack* minha_arvore = new ArvoreRedBlack { .raiz = 0};
    Insert(minha_arvore, 11);
    Insert(minha_arvore, 2);
    Insert(minha_arvore, 14);
    Insert(minha_arvore, 15);
    Insert(minha_arvore, 8);
    Insert(minha_arvore, 7);
    Insert(minha_arvore, 4);
    Insert(minha_arvore, 1);
    Insert(minha_arvore, 5);
    em_ordem(minha_arvore->raiz);
    printf("RAIZ == %d", minha_arvore->raiz->dado);
}
