#include "func.h"

/*Edge::Edge(size_t s, size_t f, size_t p){
	first = s;
	second = f;
	price = p;
}

std::ostream& operator<< (std::ostream &out, const Edge& E){
	out << "(" << E.first << "," << E.second << ")" << " = " << E.price << ";";
}


void const print_str(std::ostream &out, const map<int, int>& str){
	map <int, int>::const_iterator it = str.begin();
		for(;it != str.end(); it++){
			int s = (*it).second;
			if(s == INT_MAX) out << "-";
			else out << s;
			out << ";";
		};
};


int Matrix::load(const string& filename){
	ifstream fin(filename.c_str());
	if(!fin){ cout << "eof"; return 1; }; // файл не открылся
	string buff;
	getline(fin, buff);
	if(!fin){ cout << "null"; return 2; }; //файл пуст
	int N = atoi(buff.erase(0, 2).c_str());
	//cout << "N = " << N << endl;
	for(int i = 0; i < N; i++){
		map <int, int> str;
		for(int j = 0; j < N; j++){
			getline(fin, buff, ';');
			if (buff == "-"){
				pair<int,int> p(j, INT_MAX);
				str.insert(p);
			}
			else{
				str.insert(pair<int,int>(j, atoi(buff.c_str())));
			}
		}
		//print_str(cout, str); cout << endl;
		insert(pair<int, map<int,int> >(i, str));
	}
	return 0;
};

std::ostream& operator<< (std::ostream &out, const Matrix& matrix){
	int N = matrix.size();
	out << "N:" << N << ";";
	for(int i = 0; i < N ; i++){
		out << endl;
		print_str(out, matrix.at(i));
	}
};
*/
//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################

//пустой конструктор
Path::Path(size_t N) {
	size = N;
	points = NULL;
	if (N == 0) return;
	points = new size_t[N];
	for (size_t i = 0; i < N; i++) {
		points[i] = INT_MAX;
	}
};

//конструктор копий
Path::Path(const Path& P) {
	size = P.get_size();
	if (size == 0) return;
	points = new size_t[size];
	for (size_t i = 0; i < size; i++) {
		points[i] = P.points[i];// no next, just copy
	}
};

//дуструктор
Path::~Path()
{
	delete[] points;
};

//перевыделение памяти и очистка(в основном для пустого конструктора)
void Path::alloc(size_t N) {
	delete[] points;
	size = N;
	if (N == 0) return;
	points = new size_t[N];
	for (size_t i = 0; i < N; i++) {
		points[i] = INT_MAX;
	}
};

//оператор присваивания
Path& Path::operator=(const Path& P) {
	size_t size = P.get_size();
	delete[] points;
	if (size == 0) return *this;
	points = new size_t[size];
	for (size_t i = 0; i < size; i++) {
		points[i] = P.get_next(i);// no next, just copy
	}
	return *this;
};

void Path::set_rib(const pair<size_t,size_t>& p)
{
	points[p.first] = p.second;
};

//поиск обратных ребер
void Path::find_reverse_cycle(set<pair<size_t, size_t> >& edges) const {
	size_t j;
	edges.clear();
	for (size_t i = 0; i < size; i++) {
		j = 0;
		size_t next = get_next(i);
		while (next != INT_MAX) {
			edges.insert(pair<size_t, size_t>(next, i));
			next = get_next(next);
			j++;
			if (j > get_size() * 2) {//прерыватель бесконечного цикла
				edges.clear();
				return;
			}
		}
	}
};

std::ostream& operator<<(std::ostream& out, const Path& P)
{
	out << "size: " << P.size << endl << "counts: ";
	for (int i = 0; i < P.size; i++) {
		size_t p = P.points[i];
		if (p == INT_MAX) out << "-";
		else out << p;
		out << ", ";
	}
	out << ";\n";
	return out;
}

//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################
//############################################################################################################

Komi::Komi() {
	high_limit = INT_MAX;
	low_limit = 0;
}

Komi::Komi(const std::string& filename)
{
	high_limit = INT_MAX;
	low_limit = 0;
	load_matrix(filename);
}



Komi::Komi(const Komi& K){
	high_limit = K.high_limit;
	high_path = K.high_path;
	low_limit = K.low_limit;
	low_path = K.low_path;
	matrix = K.matrix;
};

Komi& Komi::operator=(const Komi& K) {
	high_limit = K.high_limit;
	high_path = K.high_path;
	low_limit = K.low_limit;
	low_path = K.low_path;
	matrix = K.matrix;
	return *this;
};

size_t Komi::load_matrix(const string& filename) {
	ifstream fin(filename.c_str());
	if (!fin) { cout << "eof"; return 1; }; // файл не открылся
	string buff;
	getline(fin, buff);
	if (!fin) { cout << "null"; return 2; }; //файл пуст
	size_t N = atoi(buff.erase(0, 2).c_str());
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			getline(fin, buff, ';');
			if (buff == "-") {
				push({ i, j }, INT_MAX);
			}
			else {
				push({ i, j }, atoi(buff.c_str()));
			}
		}
	}
	return 0;
};

std::ostream& operator<< (std::ostream& out, const Komi& K) {
	size_t N = K.size();
	out << "N:" << N << ";";
	map< pair<size_t, size_t>, size_t>::const_iterator it = K.matrix.begin();
	for (;it != K.matrix.end();) {
		out << endl;
		for (size_t i = 0; i < N; i++) {
			if ((*it).second == INT_MAX) out << "-;";
			else out << (*it).second << ";";
			it++;
		}
	}
	return out;
};

map< pair<size_t, size_t>, size_t>& Komi::create_matrix_str(map< pair<size_t, size_t>, size_t>& m, size_t str) const {
	m.clear();
	for (size_t i = 0; i < size(); i++) {
		m.insert_or_assign({str, i}, matrix.at({str, i}));
	}
	return m;
};

map< pair<size_t, size_t>, size_t>& Komi::create_matrix_colum(map< pair<size_t, size_t>, size_t>& m, size_t colum) const {
	m.clear();
	for (size_t i = 0; i < size(); i++) {
		m.insert_or_assign({ i, colum }, matrix.at({ i, colum }));
	}
	return m;
};

pair<pair<size_t, size_t>, size_t> Komi::find_min_map(map< pair<size_t, size_t>, size_t>& m) const{
	map< pair<size_t, size_t>, size_t>::const_iterator it = m.begin();
	size_t min = (*it).second;
	size_t min_i = (*it).first.second;
	it++;
	for (; it != m.end(); it++) {
		if ((*it).second < min) {
			min = (*it).second;
			min_i = (*it).first.second;
		}
	}
	it--;
	return { { (*it).first.first, min_i}, min};
}

void Komi::del_rib(const pair<size_t, size_t>& rib){
	try {
		matrix.at(rib) = INT_MAX;
	}
	catch(out_of_range) {
		return;
	}
}

void Komi::del_str_and_colum(const pair<size_t, size_t>& rib){
	map< pair<size_t, size_t>, size_t>::iterator it = matrix.begin();
	for (; it != matrix.end(); ) {
		if (((*it).first.first == rib.first) ||
			((*it).first.second == rib.second)) {
			it = matrix.erase(it);
		}
		else it++;
	}
}

void Komi::early_cycle() {
	set<pair<size_t, size_t> > ribs;
	low_path.find_reverse_cycle(ribs);
	set<pair<size_t, size_t> >::iterator it = ribs.begin();
	for (; it != ribs.end(); it++) {
		del_rib(*it);
	}
};

void Komi::find_high_limit() {
	high_path.alloc(size());
	high_limit = 0;

	map< pair<size_t, size_t>, size_t> buff;
	create_matrix_str(buff, 0);
	pair<pair<size_t, size_t>, size_t> min_in_str;

	for (size_t i = 0; i < size() - 1; i++) {
		min_in_str = find_min_map(buff);
		high_limit += min_in_str.second;
		high_path.set_rib(min_in_str.first);

		create_matrix_str(buff, min_in_str.first.second);		//создание следующей строки
		set<pair<size_t, size_t> > ribs;						//удаление обратных ребер в буфере
		high_path.find_reverse_cycle(ribs);
		set<pair<size_t, size_t> >::iterator it = ribs.begin();
		for (; it != ribs.end(); it++) {
			buff.erase(*it);
		}
	}

	

	min_in_str = { { min_in_str.first.second, 0 }, matrix[{ min_in_str.first.second, 0 }]};
	high_limit += min_in_str.second;
	high_path.set_rib(min_in_str.first);
};