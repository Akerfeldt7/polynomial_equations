//solve.cpp

#include "headers/solve.h"



//Upologizei to k 
double upologismos_k(poluonumo_sylvester *p_syl) {
	double * table_1d;
	int diastasi_1d;
	int Ak;
	double smax = 0, smin = 0;

	Ak = p_syl->give_bathmo();
	diastasi_1d = (p_syl->give_diastasi()) * (p_syl->give_diastasi());
	table_1d = new double[diastasi_1d];
	table_1d = p_syl->transform_2d_to_1d(table_1d, diastasi_1d, Ak);
	
	int diastasi = p_syl->give_diastasi();

	Map<MatrixXd> m(table_1d, diastasi, diastasi);

	JacobiSVD<MatrixXd> svd(m, Eigen::ComputeFullU);
	JacobiSVD<MatrixXd>::SingularValuesType singular = svd.singularValues();

	//cout << "The singular values of A are:" << svd.singularValues() << endl;

	smin = singular(0);
	for (int i = 0; i < singular.rows(); i++) {
		//	cout << "Singular Value " << i << ":" << singular(i) << endl;
		if (smax < singular(i)) {
			smax = singular(i);
		}
		if (smin > singular(i)) {
			smin = singular(i);
		}
	}
	double k;
	//if (smin == 0) {
	if(fabs(smin)<0.0001){
		k = -1; //apeiro
	}
	else {
		k = smax / smin;
	}
	//cout<<"k:"<<k<<endl;
	delete []table_1d; //diagrafo to table_1d pou xrisimopoihthike gia ton upologismo tou k
	return k;
	//////////////////////////////////////////////////////////
}


//SOLVE STANDARD EIGEN PROBLEM//////////////////////////////////////////////////////////////

void solve_standard_eigen_problem(poluonumo **poluonuma, poluonumo_sylvester *p_syl, double k,bool change,int t1,int t2,int t3,int t4) {
//lunei to standard eigen problem dimiourgontas tin klassi pou afora auto to problima
//ektuponontas ta bimata kai ta apotelesmata
	standard_eigen_problem *std_problem;
	std_problem = new standard_eigen_problem(p_syl);
	roots *all_roots;
	list_of_roots *telikes_rizes;

	cout << "Equations" << endl;
	cout << "---------" << endl;

	cout << poluonuma[0]->print_poluonumo() << endl;
	cout << poluonuma[1]->print_poluonumo() << endl;
	
	if(change==true){
		if(p_syl->give_hidden()=="x"){
			cout<<"we had change the variable x at x=(t1z+t2z)/(t3z+t4)"<<endl;
		}
		else{
			cout<<"we had change the variable y at y=(t1z+t2z)/(t3z+t4)"<<endl;
		}
	}

	all_roots = std_problem->give_roots();

	int Ak = p_syl->give_bathmo();
	p_syl->print_mitroo_suntelesti(Ak);

	cout << endl << endl << "k ~= " << k << " > Bound: non-singular Md, standard eigenproblem" << endl << endl;

	cout << "Roots" << endl;
	cout << "-----" << endl << endl;
	if(change==true){ //allagameni metabliti
		all_roots->print_change_roots(poluonuma[0], poluonuma[1],t1,t2,t3,t4); //ektuponoume tis rizes pou brikame
	}
	else{	//kanonikes metablites
		all_roots->print_roots(poluonuma[0], poluonuma[1]); //ektuponoume tis rizes pou brikame
		telikes_rizes=all_roots->fill_the_list_of_roots(poluonuma[0], poluonuma[1]);
		
		cout<<"dokimastiko"<<endl;
		for(int i=0;i<telikes_rizes->give_plithos();i++){
			cout<<"x:"<<telikes_rizes->give_x(i+1)<<" ";
			cout<<"y:"<<telikes_rizes->give_y(i+1);
			cout<<endl;
		}
		delete telikes_rizes;	
	}
	
	/////////////////////
	delete all_roots;
	delete std_problem;
}


//////////////////////////////////////////////////////////////////



//SOLVE GENERALIZED EIGEN PROBLEM

void solve_gen_eig_problem(poluonumo **poluonuma, poluonumo_sylvester *p_syl, double k,bool change,int t1,int t2,int t3,int t4)
//lunei to genikeumeno problima dimiourgontas tin klassi pou afora auto to problima
//ektuponontas ta bimata kai ta apotelesmata
{
	gen_eig_prob *gen_problem;
	gen_problem = new gen_eig_prob(p_syl);
	roots *r;
	list_of_roots *telikes_rizes;
	//gen_problem->compute_roots();
	cout << "Equations" << endl;
	cout << "---------" << endl;
	
	cout << poluonuma[0]->print_poluonumo() << endl;
	cout << poluonuma[1]->print_poluonumo() << endl;

	if(change==true){
		if(p_syl->give_hidden()=="x"){
			cout<<"we had change the variable x at x=(t1z+t2z)/(t3z+t4)"<<endl;
		}
		else{
			cout<<"we had change the variable y at y=(t1z+t2z)/(t3z+t4)"<<endl;
		}
	}


	cout << endl << "Md is:" << endl << endl;
	gen_problem->print_Md();

	if (k == -1) {
		cout << endl << endl << "k inifinity > Bound: ill-conditioned Md, generalized eigenproblem" << endl << endl;
	}
	else {
		cout << endl << endl << "k ~= " << k << " > Bound: ill-conditioned Md, generalized eigenproblem" << endl << endl;
	}

	r=gen_problem->give_lisis();
	cout << "Roots" << endl;
	cout << "-----" << endl << endl;
	if(change==true){ //allagameni metabliti
		//gen_problem->lisis->print_change_roots(poluonuma[0], poluonuma[1],t1,t2,t3,t4);
		r->print_change_roots(poluonuma[0], poluonuma[1],t1,t2,t3,t4);
		
	}
	else{ //kanonikes metablites
		//gen_problem->lisis->print_roots(poluonuma[0], poluonuma[1]);
		r->print_roots(poluonuma[0], poluonuma[1]);
		telikes_rizes=r->fill_the_list_of_roots(poluonuma[0], poluonuma[1]);
		
		cout<<"dokimastiko"<<endl;
		for(int i=0;i<telikes_rizes->give_plithos();i++){
			cout<<"x:"<<telikes_rizes->give_x(i+1)<<" ";
			cout<<"y:"<<telikes_rizes->give_y(i+1);
			cout<<endl;
		}
		delete telikes_rizes;
	}
	///////////////
	
	/////////////////////
	delete r;
	delete gen_problem;
}
/////////////////////////////////////////////////////////////////////////////////////

//BONUS EROTIMA UPOLOGISMOS TOU ORIZOUSAS/////////////////////////////////////////////////////////

bool check_det(poluonumo_sylvester *p_syl) //elegxei tin orizousa pou epistrafike
{
	int* num;
	long double det = 0;

	num = new int[3];

	num = gen_3_rand(num);
	det = give_det(p_syl, num[0]);
	if (det == 0)
	{
		cout << "Determinant of M(" << num[0] << ") = 0. Checking with y = " << num[1] << endl << endl;
		det = give_det(p_syl, num[1]);
		if (det == 0)
		{
			cout << "Determinant of M(" << num[0] << ") = M(" << num[1] << ") = 0.  Checking with y = " << num[2] << endl << endl;
			det = give_det(p_syl, num[2]);
			if (det == 0)
			{
				cout << "Determinant of M(" << num[0] << ") = M(" << num[1] << ") = M(" << num[2] << ") = 0. Please do not continue computing, you may not find solution!!!" << endl << endl;
				delete[] num;
				return 0;
			}
			else
			{
				delete[] num;
				return 1;
			}
		}
		else
		{
			delete[] num;
			return 1;
		}
	}
	else
	{
		cout << "Determinant of M(" << num[0] << ") = " << det << " you may continue computing." << endl << endl;
		delete[] num;
		return 1;
	}

}

long double give_det(poluonumo_sylvester *p_syl, int y) //upologizei tin orizousa
{
	int m = p_syl->give_diastasi(); //auto einai to m
	int d = p_syl->give_bathmo();

	double *md;

	MatrixXd sum(m, m);

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			sum(i, j) = 0;
		}
	}

	md = new double[m * m];

	for (int i = 0; i < d + 1; ++i)
	{

		md = p_syl->transform_2d_to_1d(md, (m * m), i);

		Map<MatrixXd> Md (md, m, m);
		//cout << "Md" << i << endl << Md << endl;
		sum = sum + ((pow(y, i)) * Md);
		//cout << "sum" << endl << sum << endl << endl;
	}

	delete[] md;
	//cout << endl << sum << endl;
	//cout << "det = " << sum.determinant() << endl;
	return (sum.determinant());
}


int* gen_3_rand(int *arithmoi) //paragei 3 tuxaious diaforetikous arithmous
{
	arithmoi[0] = rand() % 50 + 1;
	do
	{
		arithmoi[1] = rand() % 50 + 1;
	} while (arithmoi[1] == arithmoi[0]);

	do
	{
		arithmoi[2] = rand() % 50 + 1;

	} while ((arithmoi[2] == arithmoi[0]) || (arithmoi[2] == arithmoi[1]));

	return arithmoi;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////























