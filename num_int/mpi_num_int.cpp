#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <mpi.h>

#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

  
int main (int argc, char* argv[]) {
  
  if (argc < 6) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity>"<<std::endl;
    return -1;
  }
  
  int functionid = atoi(argv[1]);
  float a = atof(argv[2]);
  float b = atof(argv[3]);
  int n = atoi(argv[4]);
  int intensity = atoi(argv[5]);

  MPI_Init(&argc, &argv);

  int P, i;
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  MPI_Comm_rank(MPI_COMM_WORLD, &i);

  float local_sum = 0.0;
  float global_sum = 0.0;

  float h = (b-a)/n;
  auto start = std::chrono::high_resolution_clock::now();
  int local_n = n/P;
  int start_index = i*local_n;
  int end_index = start_index + local_n;
  if (i == P-1) {
    end_index = n;
  }

  for(int j = start_index; j < end_index; j++) {
    float x = a + (j + 0.5)*h;
    switch(functionid) {
      case 1:
        local_sum += f1(x, intensity);
        break;
      case 2:
        local_sum += f2(x, intensity);
        break;
      case 3:
        local_sum += f3(x, intensity);
        break;
      case 4:
        local_sum += f4(x, intensity);
        break;
      default:
        std::cerr<<"Invalid functionid. Must be between 1 and 4."<<std::endl;
        return -1;
    }
  }

  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  if (i == 0) {
    std::cout<<global_sum*h<<std::endl;
    std::cerr<<elapsed.count()<<std::endl;
  }

  MPI_Finalize();

  return 0;
}
