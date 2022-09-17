#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <list>
#include <cstdlib>
#include <string>

using namespace std;

/*class Edge :pair<int, int> {
	private:
		size_t price;
	public:
		Edge(){};
		~Edge(){};
		
		Edge(size_t s, size_t f, size_t p);
		
		friend std::ostream& operator<< (std::ostream &out, const Edge& E);
		
};*/

/*class Matrix:map< int, map<int, int> >{
	private:
		static int high_limit;
		static list<int> higt_limit_path;
		int low_limit;
	public:
		Matrix(){low_limit = 0;};
		Matrix(const std::string& filename){ load(filename); };
		Matrix(const Matrix& M);
		
		int load(const std::string& filename);
		

		friend std::ostream& operator<< (std::ostream &out, const Matrix& matrix);
		friend void const print_str(std::ostream &out, const map<int, int>& str);
		find_high_limit();
};*/

class Path{
	private:
		size_t* points;
		size_t size;
	public:
		Path() : 
			points(NULL), size(0) {};
		Path(size_t N);
		Path(const Path& P);
		~Path();
		
		Path& operator=(const Path& P);
		
		size_t get_size() const { return size; };
		size_t get_next(size_t i) const { return points[i]; };
		
		void set_rib(const pair<size_t, size_t>& p);
		void alloc(size_t N);
		
		void find_reverse_cycle(set<pair<size_t, size_t> >& edges) const;

		friend std::ostream& operator<< (std::ostream& out, const Path& P);
};

class Komi {
	private:
		map< pair<size_t, size_t>, size_t> matrix;

		size_t high_limit;
		Path high_path;
		
		size_t low_limit;
		Path low_path;

		void push(pair<size_t, size_t> it, size_t p)
			{ matrix.insert_or_assign(it, p); };							//�������� �������� � �������(���� ���� ����, ��������)


		pair<pair<size_t, size_t>, size_t> find_min_map(map< pair<size_t, size_t>, size_t>& m) const;
		map< pair<size_t, size_t>, size_t>& create_matrix_str(map< pair<size_t, size_t>, size_t>& m, size_t str) const;
		map<pair<size_t, size_t>, size_t>& create_matrix_colum(map<pair<size_t, size_t>, size_t>& m, size_t colum) const;


	public:
		Komi();																//����������� �����������
		Komi(const std::string& filename);									//����������� � ��������� �����
		
		Komi(const Komi& K);												//����������� �����������
		Komi& operator=(const Komi& K);										// �������� ������������
		
		size_t load_matrix(const string& filename);							//�������� ������� �� �����
		
		friend std::ostream& operator<< (std::ostream &out, const Komi& K);	//����� ������� (� ����� ��� � �����)
		
		size_t size() const { return sqrt(matrix.size()); };				// ������ ������ �������
		size_t get_high_limit() { return high_limit; };
		size_t get_low_limit() { return low_limit; };

		void del_rib(const pair<size_t, size_t>& rib);						//������ �������� ����� rib = INT_MAX
		void del_str_and_colum(const pair<size_t, size_t>& rib);			//������� ������ � �������, � ������� ������ ����� rib, size  ����������� �� 1
		void early_cycle();													//������ del_rib ���� ������ ���������� � Path.find_reverse_cycle (�������� ����� ���������������� �����)

		void find_high_limit();												//���������� high_limit � ligh_path
		void find_low_limit_normaliz();
		void find_best_edges();
};














