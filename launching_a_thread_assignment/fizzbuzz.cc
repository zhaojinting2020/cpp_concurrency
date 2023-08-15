#include <iostream>
#include <thread>
#include <string>

using namespace std;

const int nplayers{4};
const int max_number{30};
string player_names[] = {"Abdul", "Bart", "Claudia", "Divya"};

void speak() {
	for (int n = 1; n <= max_number; ++n) {
		string player = player_names[(n-1)%nplayers];
		
		cout << player << " says ";
	
		if (n % 3 == 0 && n % 5 == 0) {
			cout << "fizzbuzz!";
		}
		else if (n % 3 == 0) {
			cout << "fizz!";
		}
		else if (n % 5 == 0) {
			cout << "buzz!";
		}
		else {
			cout << n;
		}
		cout << endl;
	}
}

int main() {
	// speak();
	thread game{speak};
	game.join();
}