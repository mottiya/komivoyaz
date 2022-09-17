#include "func.h"

void print_path(const Path& P){
	for(int i = 0; i < P.get_size(); i++){
		size_t N = P.get_next(i);
		if(N == INT_MAX) { cout << "-"; continue; };
		cout << N;
	}
};

void print_edges(const set<pair<size_t, size_t> >& e) {
	set<pair<size_t, size_t> >::const_iterator it = e.begin();
	for (; it != e.end(); it++) {
		cout << "(" << (*it).first << "," << (*it).second << ") ";
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	const string filename = "matrix_wt.txt";

	Komi K;
	Komi K1(filename);
	K.load_matrix(filename);
	cout << K << endl;
	K.find_high_limit();
	K.find_low_limit_normaliz();

	cout << K << endl << "high_limit = " << K.get_high_limit() << "low_limit = " << K.get_low_limit();

	return 0;
}
