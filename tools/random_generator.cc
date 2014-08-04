#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int RandomUniform(int n) {
  int top = ((((RAND_MAX - n) + 1) / n) * n - 1) + n;  
  int r;  
  do {  
    r = rand();  
  } while (r > top);  
  return (r % n);  
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	if (argc != 4) {
		cout << "usage: ./random_generator [size] [range] [std/ofstream]" << endl;
		exit(1);
	}
	int size = strtol(argv[1], NULL, 10), range = strtol(argv[2], NULL, 10);
	if (strcmp(argv[3], "std") == 0) {
		for (int i = 0; i < size; ++i)
			cout << RandomUniform(range) << " ";
	} else {
		ofstream of("random.txt");
		for (int i = 0; i < size; ++i)
			of << RandomUniform(range) << " ";
	}
	return 0;
}
