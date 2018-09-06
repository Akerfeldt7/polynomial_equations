//solve.h

#ifndef SOLVE_H
#define SOLVE_H

#include <iostream>
#include <ctime>
#include "poluonumo.h"
#include "poluonumo_sylvester.h"
#include "standard_eigen_problem.h"
#include "gen_eig_prob.h"
#include "roots.h"

#include "../Eigen/Dense"
#include "../Eigen/Eigenvalues"
#include "../Eigen/Core"
#include "../Eigen/SVD"



using namespace std;
using Eigen::MatrixXd;
using Eigen::MatrixXi;
using Eigen::JacobiSVD;
using Eigen::Map;

double upologismos_k(poluonumo_sylvester *p_syl);

void solve_standard_eigen_problem(poluonumo **,poluonumo_sylvester *,double k,bool,int,int,int,int);

void solve_gen_eig_problem(poluonumo **poluonuma, poluonumo_sylvester *p_syl, double k,bool,int,int,int,int);



int* gen_3_rand(int *arithmoi);

bool check_det(poluonumo_sylvester *p_syl);

long double give_det(poluonumo_sylvester *p_syl, int y);



#endif /* SOLVE_H */
