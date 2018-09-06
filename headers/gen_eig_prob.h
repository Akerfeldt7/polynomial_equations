#ifndef GEN_EIG_PROB__H
#define GEN_EIG_PROB__H

#include "poluonumo_sylvester.h"

#include "roots.h"




#include "../Eigen/Dense"
#include "../Eigen/Eigenvalues"
#include "../Eigen/Core"
#include "../Eigen/SVD"


using Eigen::MatrixXd;
using Eigen::MatrixXcd;  
using Eigen::JacobiSVD;
using Eigen::Map;
using Eigen::EigenSolver;



class gen_eig_prob {
private:

	string hidden;
	string not_hidden;


	int plithos_luseon;

	poluonumo_sylvester * p_syl; //to poluonumo_sylvester
	int d; //o bathmos tou poluonumou Sylvester
	int m; //diastasi ton mitroon tou poluonumou Sylvester
	int diastasi_companion;// i diastasi tou companio

	MatrixXd L1;// o L1
	MatrixXd L0;// o L0

	MatrixXd Md;

	MatrixXd W; // to eigenVectors
	MatrixXd Lamda;// to eigenValues

	void construct_d1();// ftiaxni ta L1 L0 an einai d==1

	void solve();// briski ta eigenValues (kai ta bazi sto Lamda) kai ta eigenVector (ta bazi st W)

	void make_L0();//ftiaxni to L0
	void make_1d_L0(double ** source);//metatrepi ton ton 2d L0 p exi ftiaxti me to make_L0 se 1d colum-major

	void make_L1();//ftiaxni ton L1
	void make_1d_L1(double ** source);// metatrepi ton ton 2d L1 p exi ftiaxti me to make_L1 se 1d colum-major
	void compute_roots();//pernei to W kai to Lamda k briski tis lisis ka ta bazi stn roots
	void print();// ektiponi to W k to Lamda
	void make_Md(); //kane tn Md se MatrixXd k tn bazi st Md;
	roots *lisis; //oi klasi me tis (pithanes) rizes pou exoume brei
public:
	gen_eig_prob(poluonumo_sylvester *p);
	~gen_eig_prob();
	void print_Md();
	roots *give_lisis();
	

};

#endif
