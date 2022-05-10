#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

template<class T>
void rand(const int size, T min, T max) {
	std::ofstream file;
	std::ostringstream oss;
	oss << size << '.' << min << '.' << max << '.' << "txt";
	
	file.open(oss.str());
	
	T elem;
	for (size_t i = 0; i < size; i++) {
		elem = min + static_cast<T>(rand()) % (max - min + 1);
		file << elem;
		file << std::endl;
	}
	file.close();
}
void rand_double(const int size, double min, double max);
int main()
{
	srand(time(NULL));
	
	rand(100, 30'000, 1'000'000);
	
	return 0;
}

void rand_double(const int size, double min, double max) {
	std::ofstream file;
	std::ostringstream oss;
	oss << size << '.' << min << '.' << max << '.' << "txt";

	file.open(oss.str());
	file << size;
	file << std::endl;
	double elem;
	for (size_t i = 0; i < size; i++) {
		auto r{ rand() };

		auto k{ static_cast<int>(r / (max - min + 1))};
		elem = min + r - k * (max - min + 1);
			
		file << elem;
		file << std::endl;
	}
	file.close();
}
