//standard_eigen_problem.h
#ifndef STANDARD_EIGEN_PROBLEM_H
#define STANDARD_EIGEN_PROBLEM_H

#include "poluonumo_sylvester.h"
#include "roots.h"


#include "../Eigen/Dense"
#include "../Eigen/Eigenvalues"
#include "../Eigen/Core"
#include "../Eigen/SVD"

using Eigen::MatrixXd;
using Eigen::MatrixXcd;  //den eimai sigouros to xrisimopoio gia to eigensolvers
using Eigen::JacobiSVD;
using Eigen::Map;
using Eigen::EigenSolver;



class standard_eigen_problem{
	private:
		string hidden; //krumeni metabliti
		string another; //i alli metabliti
		roots *all_rizes; 
		int plithos_luseon;
		poluonumo_sylvester * p_syl; //to poluonumo_sylvester
		int d; //o bathmos tou poluonumou Sylvester
		int diastasi; //diastasi ton mitroon tou poluonumou Sylvester
		int diastasi_companion; //i diastasi tou pinaka Companion
		MatrixXd companion;  //o pinakas Companion
		void construct_companion();  //gia d=1
		//void compute_roots(); //gia d=1
		void construct_big_companion(); //gia d>=2
		void compute_big_roots(); //gia d>=2 //to xrisimopoio gia ola ta d
	public:
		standard_eigen_problem(poluonumo_sylvester *);
		~standard_eigen_problem();
		int give_plithos_luseon();
		roots *give_roots(); //dimiourgei klono ton rizon kai epistrefei ton klono (gia na uparxei apokrupsi)
};






#endif /* STANDARD_EIGEN_PROBLEM_H */
