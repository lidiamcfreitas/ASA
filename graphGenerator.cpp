#include <iostream>
#include <stdint.h>

void generateConnectGraph(int n, int e){
    int u,v,i;
    printf("%d %d",n, n);
    printf("%d", 0);
    std::srand(std::time(0));
    for (i = 0; i < n - 1; i++){
        u = std::rand() % n;
        printf("%d %d\n", i, u);
    }
    for (i = 0; i < e; i++){
        v = std::rand() % n;
        u = std::rand() % n;
        printf("%d %d\n", u, v);
    }
}

int main(int argc, char *argv[]){
    generateConnectGraph(atoi(argv[1]), atoi(argv[2]));
}