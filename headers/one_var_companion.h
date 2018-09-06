//one_var_companion.h
#ifndef ONE_VAR_COMPANION_H
#define ONE_VAR_COMPANION_H

#include "poluonumo.h"


#include "../Eigen/Dense"
#include "../Eigen/Eigenvalues"
#include "../Eigen/Core"
#include "../Eigen/SVD"

using Eigen::MatrixXd;
using Eigen::MatrixXcd;  //den eimai sigouros to xrisimopoio gia to eigensolvers
using Eigen::JacobiSVD;
using Eigen::Map;
using Eigen::EigenSolver;


class one_var_companion{
	private:
		string var; //i metabliti tou poluonumou pou ftiaxnoume ton companion
		MatrixXd companion;
		int dim; //diastasi tou companion
		poluonumo *f;
		void construct_companion(); //kataskeuazei ton companion
		void solve_companion();   //lunei ton companion
		double *luseis;
		int plithos_luseon;
	public:
		one_var_companion(poluonumo *,string);
		~one_var_companion();
		int give_plithos_luseon();
		double * give_luseis();
};


#endif /* ONE_VAR_COMPANION_H */
