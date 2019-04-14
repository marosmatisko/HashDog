// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "md5.h"
#include <cuda.h>
#include <cuda_runtime_api.h>

using namespace std;
using namespace std::chrono;





int main(int argc, char** argv) {
	int main_index = 0;


	int nDevices;
	
	cudaGetDeviceCount(&nDevices);
	for (int i = 0; i < nDevices; i++) {
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);
		printf("Device Number: %d\n", i);
		printf("  Device name: %s\n", prop.name);
		printf("  Memory Clock Rate (KHz): %d\n",
			prop.memoryClockRate);
		printf("  Memory Bus Width (bits): %d\n",
			prop.memoryBusWidth);
		printf("  Peak Memory Bandwidth (GB/s): %f\n\n",
			2.0*prop.memoryClockRate*(prop.memoryBusWidth / 8) / 1.0e6);
	}

	if (argc != 3 || strlen(argv[1]) != 32 || strlen(argv[2]) > 1)
	{
		printf("\nIncorrect parameters, required input is HashDog.exe <hash> <password_length>");
		return 0;
	}

	if (nDevices > 0)
	{
		crack_md5(argv[1], atoi(argv[2]));

	}

	else
		printf("\nNo CUDA device found, quitting.");

	return 0;
	

}

