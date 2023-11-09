#include <mpi.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char*argv[]) {
     // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int P;
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    // Get the rank of the process
    int i;
    MPI_Comm_rank(MPI_COMM_WORLD, &i);

    // Get the name of the machine
    char machine_name[256]; // Adjust the size as needed
    int name_len;
    MPI_Get_processor_name(machine_name, &name_len);

    // Print off a message with the machine name, rank, and size of the communicator
    std::cout << "I am process " << i << " out of " << P << ". I am running on " << machine_name << "." << std::endl;

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
