#include "headers/gen_eig_prob.h"
#include "headers/poluonumo_sylvester.h"
#include <math.h>
#include "headers/roots.h"


#include <lapacke.h>

gen_eig_prob::gen_eig_prob(poluonumo_sylvester *p)
{

	plithos_luseon = 0;


	p_syl = p;

	d = p_syl->give_bathmo(); //auto einai to d
	m = p_syl->give_diastasi(); //auto einai to m
	diastasi_companion = d * m;


	if (p_syl->give_hidden() == "x") {
		hidden = "x";
		not_hidden = "y";
	}
	else
	{
		hidden = "y";
		not_hidden = "x";
	}
	if (d == 1)
	{
		construct_d1();
		solve();
		compute_roots();

	}
	else
	{
		make_L1();
		make_L0();
		solve();
		compute_roots();
	}
	make_Md();

}
gen_eig_prob::~gen_eig_prob()
{
	delete lisis;
}


void gen_eig_prob::construct_d1()
{

	double* M1;
	double* M0;

	int diastasi_1d = (m * m);
	M1 = new double[diastasi_1d];
	M0 = new double[diastasi_1d];

	M1 = p_syl->transform_2d_to_1d(M1, diastasi_1d, 1);
	M0 = p_syl->transform_2d_to_1d(M0, diastasi_1d, 0);

	Map<MatrixXd> m1(M1, m, m);
	Map<MatrixXd> m0(M0, m, m);

	//cout << m1 << endl;
	//cout << m0 << endl;
	L1 = m1;
	L0 = -1 * m0;

	cout << "\t\tL1 & L0 CONSTRUCTED" << endl;

	delete[] M1;
	delete[] M0;
}


void gen_eig_prob::solve()
{

	int N = L0.cols();

	MatrixXd V(N, N);
	MatrixXd lamda(N, 3);

	int LDm1 = L1.outerStride();
	int LDm0 = L0.outerStride();
	int LDV = V.outerStride();

	double * m1r = lamda.col(0).data();
	double * m1i = lamda.col(1).data();
	double * beta = lamda.col(2).data();

	LAPACKE_dggev(LAPACK_COL_MAJOR, 'N', 'V', N, L0.data(), LDm0, L1.data(), LDm1, m1r, m1i, beta, 0, LDV, V.data(), LDV);

	Lamda = lamda;
	W = V;

	cout << "\t\teigenValues & eigenVectors COMPUTED" << endl;


}



void gen_eig_prob::make_L1()
{
	double **L1_2d;
	double **Md;


	L1_2d = new double*[diastasi_companion]; //desmeusi tou disdiastatou pinaka L1
	for (int i = 0; i < diastasi_companion; i++)
		L1_2d[i] = new double[diastasi_companion];

	for (int i = 0; i < diastasi_companion; i++)// arxikopoioume tn proti grammi me 1000000..00
	{	if (i == 0)
		{
			L1_2d[0][i] = 1;
		}
		else
		{
			L1_2d[0][i] = 0;
		}
	}
	for (int i = 1; i < diastasi_companion; i++) { //arxikopoioume tis upoloipes grammes me midenika
		for (int j = 0; j < diastasi_companion; j++) {
			L1_2d[i][j] = 0;
		}
	}
	//kanume shift tn proti grami m*d-1 fores
	for (int i = 0; i < diastasi_companion - m; i++) {
		for (int j = 0; j < diastasi_companion; j++) {
			if (j + 1 == diastasi_companion) { //tote bgainei ektos oriou
				continue;
			}
			else {
				L1_2d[i + 1][j + 1] = L1_2d[i][j];
			}
		}
	}

	/* exume ena pinaka tis morfis 100..00
								   010..00
								   001..00
								   000..00
	den exume ftia3i akoma tn telefea grami
	*/

	Md = new double*[m];
	for (int i = 0; i < m; ++i)
		Md[i] = new double[m];


	Md = p_syl->get_mitroo(Md, d);
	int count = 0;
	int row = 0;
	int col = 0;

	for (int i = diastasi_companion - m; i < diastasi_companion; ++i)
	{
		for (int j = diastasi_companion - m; j < diastasi_companion; ++j)
		{
			row = count / m;
			col = count % m;

			L1_2d[i][j] = Md[row][col];
			count++;
		}
	}

	make_1d_L1(L1_2d);
	cout << "\tL1 & ";

	for (int i = 0; i < m; ++i)
		delete[] Md[i];
	delete[] Md;

	for (int i = 0; i < diastasi_companion; i++)
		delete[] L1_2d[i];
	delete[] L1_2d;


}

void gen_eig_prob::make_L0()
{
	double **L0_2d;
	double **Md;
	int bathmos = 0;


	L0_2d = new double*[diastasi_companion]; //desmeusi tou disdiastatou pinaka L0_2d
	for (int i = 0; i < diastasi_companion; i++)
		L0_2d[i] = new double[diastasi_companion];

	for (int i = 0; i < diastasi_companion; i++)// arxikopoioume tn proti grammi me 000-10000..00
	{	if (i == m)
		{
			L0_2d[0][i] = -1;
		}
		else
		{
			L0_2d[0][i] = 0;
		}
	}
	for (int i = 1; i < diastasi_companion; i++) { //arxikopoioume tis upoloipes grammes me midenika
		for (int j = 0; j < diastasi_companion; j++) {
			L0_2d[i][j] = 0;
		}
	}
	//kanume shift tn proti grami m*d-1 fores
	for (int i = 0; i < diastasi_companion - m; i++) {
		for (int j = 0; j < diastasi_companion; j++) {
			if (j + 1 == diastasi_companion) { //tote bgainei ektos oriou
				continue;
			}
			else {
				L0_2d[i + 1][j + 1] = L0_2d[i][j];
			}
		}
	}

	Md = new double*[m];
	for (int i = 0; i < m; ++i)
	{
		Md[i] = new double[m];
	}
	for (int fora = 1; fora <= d; ++fora)
	{


		Md = p_syl->get_mitroo(Md, fora - 1);

		int count = 0;
		int row = 0;
		int col = 0;


		for (int i = diastasi_companion - m; i < diastasi_companion; ++i)//row
		{
			for (int j = ((fora - 1) * m); j < (fora * m); ++j) //col
			{
				row = count / m;
				col = count % m;

				L0_2d[i][j] = Md[row][col];
				count++;
			}
		}

	}

	make_1d_L0(L0_2d);
	cout << "L0 CONSTRUCTED" << endl;

	for (int i = 0; i < m; ++i)
		delete[] Md[i];
	delete[] Md;
	for (int i = 0; i < diastasi_companion; i++)
		delete[] L0_2d[i];
	delete[] L0_2d;

}

void gen_eig_prob::make_1d_L1(double ** source)
{
	double * temp;
	int count = 0;

	temp = new double[diastasi_companion * diastasi_companion];

	for (int i = 0; i < diastasi_companion; ++i)
	{
		for (int j = 0; j < diastasi_companion; ++j)
		{
			temp[count] = source[j][i];
			count++;
		}
	}

	Map<MatrixXd> m1(temp, diastasi_companion, diastasi_companion);

	L1 = m1;
	delete[] temp;


}

void gen_eig_prob::make_1d_L0(double ** source)
{
	double * temp;
	int count = 0;

	temp = new double[diastasi_companion * diastasi_companion];

	for (int i = 0; i < diastasi_companion; ++i)
	{
		for (int j = 0; j < diastasi_companion; ++j)
		{
			temp[count] = source[j][i];
			count++;
		}
	}

	Map<MatrixXd> m1(temp, diastasi_companion, diastasi_companion);

	L0 = -1 * m1;
	delete[]temp;


}

void gen_eig_prob::print()
{
	cout << "to LAMDA einai\n";
	cout << Lamda << endl << endl << endl;

	cout << "to W einai\n";
	cout << W << endl << endl;
}



void gen_eig_prob::compute_roots()
{
	int count_roots = 0;
	double x, y;

	//print();
	
	//kanoume tin kanonikopoihsi 
	for(int i=0;i<m;i++){
		for(int j=0;j<W.cols();j++){
			if( fabs(W(m-1,j))<10e-7){
				W(i,j)=0;
				continue;
			}
			W(i,j)=W(i,j)/W(m-1,j);
		}
	}
	//print();
	//////////////////////////////////////////


	for (int i = 0; i < Lamda.rows(); ++i)
	{
		if (fabs(Lamda(i, 1)) < 10e-7)
		{
			if ((fabs(Lamda(i, 2)) > 10e-7)) 
			{
				count_roots++;
			}
		}
	}


	this->lisis = new roots(count_roots, this->hidden.data());

	for (int i = 0; i < this->Lamda.rows();i++) 
	{
		if ( (fabs(Lamda(i, 1)) < 10e-7) && (fabs(Lamda(i, 2)) > 10e-7))
		{
			if(hidden=="y"){
				if(W(m-1,i)==1 || W(m-1,i)==-1){
					x=W(m-2,i);
					y=((Lamda(i, 0)) / (Lamda(i, 2)));
					this->lisis->add_root(x,y,true);
				}
				else{
					x=W(m-2,i);
					y=((Lamda(i, 0)) / (Lamda(i, 2)));
					this->lisis->add_root(x,y,false);
				}
			}
			else{
				if(W(m-1,i)==1 || W(m-1,i)==-1){
					x=((Lamda(i, 0)) / (Lamda(i, 2)));
					y=W(m-2,i);
					this->lisis->add_root(x,y,true);
				}
				else{
					x=((Lamda(i, 0)) / (Lamda(i, 2)));
					y=W(m-2,i);
					this->lisis->add_root(x,y,false);
				}
			}
		}
	}
	cout << "\t\tROOTS COMPUTED!!" << endl;


}




void gen_eig_prob::make_Md()
{
	double* md;
	md = new double[m * m];
	md = p_syl->transform_2d_to_1d(md, m * m, d);
	Map<MatrixXd> m1(md, m, m);
	Md = m1;
	delete []md;

}
void gen_eig_prob::print_Md()
{
	cout << Md << endl;
}

roots *gen_eig_prob::give_lisis(){
	roots* duplicate;
	duplicate=new roots(*lisis);
	return duplicate;
}
