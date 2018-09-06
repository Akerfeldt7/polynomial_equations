//interpolation.h
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <iostream>
#include <cmath>
#include "poluonumo.h"

using namespace std;

#include "../Eigen/Dense"
#include "../Eigen/Eigenvalues"
#include "../Eigen/Core"
#include "../Eigen/SVD"

using Eigen::MatrixXd;
using Eigen::MatrixXcd;  //den eimai sigouros to xrisimopoio gia to eigensolvers
using Eigen::JacobiSVD;
using Eigen::Map;
using Eigen::EigenSolver;

/*class point{
	private:
		double x;
		double y;
	public:
		point(double,double);
		~point();
};*/

struct point{
	double x;
	double y;
};

class lista_point{
	private:
		struct kombos{
			int id;
			point *timi;
			kombos *next;
		};
		kombos * start;
		kombos * last;
		int plithos;
	public:
		lista_point();
		~lista_point();
		void add_to_lista(point*);
		void print_lista();
		int give_plithos();
		double give_x_from_kombo(int arithmos_kombou);
		double give_y_from_kombo(int arithmos_kombou);
};



class interpolation{
	private:
		int k; //bgainei apo ton bathmo kai einai k grammes,k+1 stiles
		int d; //o bathmos tou poluonumou
		bool well_constrained; //deixnei an mporoume na kataskeuasoume ton interpolation i oxi
		int rank; //to rank tou interpolation
		lista_point *simeia; //i lista me ta simeia pou dosame
		MatrixXd interpolation_matrix;
		void construct(); //kataskeuazei ton pinaka
		void upologismos_rank();
		void construct_poluonumo();
		poluonumo * pol_f;
	public:
		interpolation(lista_point *,int);
		~interpolation();
		poluonumo * give_poluonumo();
		
};











#endif /* INTERPOLATION_H */
