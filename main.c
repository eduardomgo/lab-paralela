#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char** argv) {
    int meu_ranque, num_procs, origem, destino, etiq=0;
    int flag = 0;
    char mensagem[100];
    MPI_Status estado;
    MPI_Request pedido;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD,&num_procs);

    if (meu_ranque != 0) {
        sprintf(mensagem, "Processo %d está vivo!", meu_ranque);
        destino = 0;
        MPI_Isend(mensagem, strlen(mensagem)+1, MPI_CHAR, destino, etiq, MPI_COMM_WORLD, &pedido);
    }
    else {
        for (origem=1; origem < num_procs; origem++) {
            MPI_Irecv(mensagem, 100, MPI_CHAR, MPI_ANY_SOURCE, etiq, MPI_COMM_WORLD, &pedido);
            while(flag == 0){
                MPI_Test(&pedido, &flag, &estado);
            }
            printf("%s\n", mensagem);
        }
    }
    MPI_Finalize( ); 
}