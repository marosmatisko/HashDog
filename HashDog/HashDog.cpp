// HashDog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BruteForceGenerator.h"
#include "Md5Hash.h"
#include "Utility.h"
#include "Attacker.h"
#include "md5.h"
#include <cuda.h>
#include <cuda_runtime_api.h>

using namespace std;
using namespace std::chrono;

const short PASSWORD_LENGTH = 6;
const int HASH_SIZE = 129;


int main() {
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

	if (nDevices > 0)
	{
		crack_md5();
		
	}


	
	Attacker *black_hat = new Attacker(1);

	char* searched_string = new char[PASSWORD_LENGTH + 1];
	unsigned char* searched_digest = new unsigned char[HASH_SIZE];
	memcpy(searched_string, "A1p?.2", PASSWORD_LENGTH + 1);
	Md5Hash *md5_hash = new Md5Hash();
	md5_hash->hash_message(searched_string, searched_digest);

	//ATTACK with stopwatch! 
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	black_hat->perform_attack(PASSWORD_LENGTH, Attacker::attack_mode::brute_force, Attacker::attacked_hash::md5, searched_digest);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	black_hat->print_proof();

	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Hash computation time: " << duration << "us";
}