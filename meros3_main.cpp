#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cctype>
#include <cstdlib>
#include <ctime>


#include "headers/poluonumo.h"
#include "headers/mitroo_sylvester.h"
#include "headers/poluonumo_sylvester.h"
#include "headers/helping_functions.h"
#include "headers/solve.h"
#include "headers/change_poluonumo_sylvester.h"

#include "headers/one_var_companion.h"  //den xreiazetai auto na to sbiso! to exo gia testaki

#include "headers/interpolation.h"


using namespace std;



int main(int argc, char const *argv[])
{
	srand( time( 0 ) );
	int d1, d2, k_sintelestis, flag_to_delete = 0;
	poluonumo **poluonuma;
	ifstream input;
	string line,  poly_1, poly_2;

	string path;

	mitroo_sylvester *m_syl;
	poluonumo_sylvester *p_syl;

	poluonuma = new poluonumo*[2];

	int B = 7;

	if ((argc <= 2) || (argc > 10) )
	{
		cout << "WRONG ARGS!!\nPlease give:\n\t1) -generate -d1 [X] -d2 [Y] -solve B\n\t2)-read -console\n\t3)-read -i [input file] -d1 [X] -d2 [Y] -solve B" << endl;
		delete []poluonuma;
		return -1;
	}
	else
	{
		if ((strcmp(argv[1], "-generate") == 0) && ((argc == 8) || (argc == 7)))
		{
			if ((strcmp(argv[2], "-d1") == 0) && (strcmp(argv[4], "-d2") == 0) && (strcmp(argv[6], "-solve") == 0) && (argc == 7))
			{
				flag_to_delete = 1;
				cout << "doulebi\n";
				d1 = atoi(argv[3]);
				d2 = atoi(argv[5]);
				cout << d1 << " " << d2 << endl;
				poluonuma[0] = create_random_poluonumo(d1);
				poluonuma[1] = create_random_poluonumo(d2);

				cout << poluonuma[0]->print_poluonumo() << endl;
				cout << poluonuma[1]->print_poluonumo() << endl;
			}
			else if ((strcmp(argv[2], "-d1") == 0) && (strcmp(argv[4], "-d2") == 0) && (strcmp(argv[6], "-solve") == 0) && (argc == 8))
			{
				flag_to_delete = 1;
				cout << "doulebi\n";
				d1 = atoi(argv[3]);
				d2 = atoi(argv[5]);
				cout << d1 << " " << d2 << endl;
				poluonuma[0] = create_random_poluonumo(d1);
				poluonuma[1] = create_random_poluonumo(d2);

				cout << poluonuma[0]->print_poluonumo() << endl;
				cout << poluonuma[1]->print_poluonumo() << endl;
				B = atoi(argv[7]);
			}
			else
			{
				cout << "WRONG ARGS!!\nPlease give:\n\t1) -generate -d1 [X] -d2 [Y] -solve B\n\t2)-read -console\n\t3)-read -i [input file] -d1 [X] -d2 [Y] -solve B" << endl;
				delete []poluonuma;
				return -1;
			}
		}
		else if (strcmp(argv[1], "-read") == 0)
		{
			if ((strcmp(argv[2], "-console") == 0) && (argc == 3))
			{
				cout << "grapse to poluonumo 1\n";
				cin >> poly_1;
				cout << poly_1 << endl;

				cout << "grapse to poluonumo 2\n";
				cin >> poly_2 ;
				cout << poly_2 << endl;


				poluonuma[0] = create_poluonumo(poly_1);

				poluonuma[1] = create_poluonumo(poly_2);
			}
			else if ((strcmp(argv[2], "-i") == 0) && ((argc == 10) || (argc == 9)))
			{
				if ((strcmp(argv[4], "-d1") == 0) && (strcmp(argv[6], "-d2") == 0) && (strcmp(argv[8], "-solve") == 0) && (argc == 10) )
				{
					int temp = 0;
					int bathmos1 = 0, bathmos2 = 0;

					bathmos1 = atoi(argv[5]);
					bathmos2 = atoi(argv[7]);

					path = argv[3];
					input.open(path.c_str());
					B = atoi(argv[9]);

					if (input.is_open())
					{
						int temp = 1;
						while (getline(input, line))
						{
							if (temp == 3)
							{
								cout << "More than 3 lines in file ERROR\n";
								delete []poluonuma;
								return -1;
							}
							else
							{
								poluonuma[temp - 1] = create_poluonumo(line);
								temp++;
							}
						}
						if (bathmos1 != poluonuma[0]->give_bathmos_poluonumo() || bathmos2 != poluonuma[1]->give_bathmos_poluonumo())
						{
							cout << "NOT maching bathmoi from file and args!\n";
							input.close();
							delete []poluonuma;
							return -1;
						}
						input.close();
					}
				}
				else if ((strcmp(argv[4], "-d1") == 0) && (strcmp(argv[6], "-d2") == 0) && (strcmp(argv[8], "-solve") == 0) && (argc == 9))
				{
					int temp = 0;
					int bathmos1 = 0, bathmos2 = 0;

					bathmos1 = atoi(argv[5]);
					bathmos2 = atoi(argv[7]);

					path = argv[3];
					input.open(path.c_str());


					if (input.is_open())
					{
						int temp = 1;
						while (getline(input, line))
						{
							if (temp == 3)
							{
								cout << "More than 3 lines in file ERROR\n";
								delete []poluonuma;
								return -1;
							}
							else
							{
								poluonuma[temp - 1] = create_poluonumo(line);
								temp++;
							}
						}
						if (bathmos1 != poluonuma[0]->give_bathmos_poluonumo() || bathmos2 != poluonuma[1]->give_bathmos_poluonumo())
						{
							cout << "NOT maching bathmoi from file and args!\n";
							input.close();
							delete []poluonuma;
							return -1;
						}
						input.close();
					}
					else
					{
						cout << "Can not open file!\n";
						delete []poluonuma;
						return -1;
					}
				}
				else
				{
					cout << "WRONG ARGS!!\nPlease give:\n\t1) -generate -d1 [X] -d2 [Y] -solve B\n\t2)-read -console\n\t3)-read -i [input file] -d1 [X] -d2 [Y] -solve B" << endl;
					delete []poluonuma;
					return -1;
				}
			}
			else
			{
				cout << "WRONG ARGS!!\nPlease give:\n\t1) -generate -d1 [X] -d2 [Y] -solve B\n\t2)-read -console\n\t3)-read -i [input file] -d1 [X] -d2 [Y] -solve B" << endl;
				delete []poluonuma;
				return -1;
			}
		}
		else
		{
			cout << "WRONG ARGS!!\nPlease give:\n\t1) -generate -d1 [X] -d2 [Y] -solve B\n\t2)-read -console\n\t3)-read -i [input file] -d1 [X] -d2 [Y] -solve B" << endl;
			delete []poluonuma;
			return -1;
		}
	}


	m_syl = new mitroo_sylvester(poluonuma[0], poluonuma[1], metabliti_to_hide(poluonuma[0], poluonuma[1]));

	m_syl->create_mitroo_sylvester();

	//m_syl->print_mitroo_sylvester();


	p_syl = new poluonumo_sylvester(m_syl, poluonuma[0], poluonuma[1]);


////////////////////////////////////////////////meros deutero
	cout << endl << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "+-------------------+---------------------------+----------------------" << endl;
	cout << "+-------------------| STRATING TO COMPUTE ROOTS |---------------------+" << endl;
	cout << "+-------------------+---------------------------+---------------------+" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << endl;
	double sugkrisi = pow(10, B);
	double k;

	k = upologismos_k(p_syl);
	if (check_det(p_syl))// edw tsekaro tn orizousa an epistrepsi 0 tote k oi 3 orizouses ine 0;
	{

		cout << "k:" << k << endl << endl;
		if (k < sugkrisi && k != -1) {
			cout << "                        +--------------------+                        " << endl;
			cout << "                        |  STANDARD PROBLEM  |                        " << endl;
			cout << "                        +--------------------+                        " << endl;

			solve_standard_eigen_problem(poluonuma, p_syl, k,false,0,0,0,0);
		}
		else {
			cout << "                        +-----------------------+                     " << endl;
			cout << "                        |  GENERALIZED PROBLEM  |                     " << endl;
			cout << "                        +-----------------------+                     " << endl;
			solve_gen_eig_problem(poluonuma, p_syl, k,false,0,0,0,0);
		}
	}
	cout << endl << endl;

	/*//testaki gia tin antikatastasi mias metablitis na to sbiso////////////////////////
	cout<<"DEBUGGING"<<endl;
	poluonumo * new_f1;
	new_f1=new poluonumo(*poluonuma[0]); 
	new_f1->antikatastasi_one_var(1.5,"y");
	new_f1->print_array();
	cout<<"testaki one_var_companion"<<endl;
	one_var_companion *testing;
	testing=new one_var_companion(new_f1,"x");
	*/
	////////////////////////////////////////////////////////

	//////////////INTERPOLATION////////////////////////


	lista_point * some_lista;
	point * some_point;
	
	some_lista=new lista_point();

	some_point=new point;
	//some_point->x=-1;
	//some_point->y=0;
	some_point->x=-5;
	some_point->y=1;
	some_lista->add_to_lista(some_point);
	
	some_point=new point;
	//some_point->x=1;
	//some_point->y=0;
	some_point->x=-5;
	some_point->y=0;
	some_lista->add_to_lista(some_point);
	
	some_point=new point;
	//some_point->x=3;
	//some_point->y=-1;
	some_point->x=2;
	some_point->y=-2;
	some_lista->add_to_lista(some_point);

	some_point=new point;
	//some_point->x=4;
	//some_point->y=-1;
	some_point->x=-5;
	some_point->y=-2;
	some_lista->add_to_lista(some_point);

	some_point=new point;
	//some_point->x=1;
	//some_point->y=-3;
	some_point->x=4;
	some_point->y=4;
	some_lista->add_to_lista(some_point);
	
	some_lista->print_lista();
	
	interpolation * interpolation_matrix;
	interpolation_matrix=new interpolation(some_lista,2);

	poluonumo * pol_f;
	pol_f=interpolation_matrix->give_poluonumo();
	if(pol_f!=NULL){
		cout<<pol_f->print_poluonumo()<<endl; //to poluonumo mas
		pol_f->print_array(); //o pinakas tou poluonumou mas
		//delete pol_f;
	}
	delete interpolation_matrix;

	//DEUTERO
	some_lista=new lista_point();

	some_point=new point;
	//some_point->x=-1;
	//some_point->y=0;
	some_point->x=-3;
	some_point->y=-4;
	some_lista->add_to_lista(some_point);
	
	some_point=new point;
	//some_point->x=1;
	//some_point->y=0;
	some_point->x=0;
	some_point->y=4;
	some_lista->add_to_lista(some_point);
	
	some_point=new point;
	//some_point->x=3;
	//some_point->y=-1;
	some_point->x=-5;
	some_point->y=0;
	some_lista->add_to_lista(some_point);

	some_point=new point;
	//some_point->x=4;
	//some_point->y=-1;
	some_point->x=1;
	some_point->y=-5;
	some_lista->add_to_lista(some_point);

	some_point=new point;
	//some_point->x=1;
	//some_point->y=-3;
	some_point->x=-4;
	some_point->y=3;
	some_lista->add_to_lista(some_point);
	
	some_lista->print_lista();
	
	//interpolation * interpolation_matrix;
	interpolation_matrix=new interpolation(some_lista,2);

	poluonumo * pol_f1;
	pol_f1=interpolation_matrix->give_poluonumo();
	if(pol_f1!=NULL){
		cout<<pol_f1->print_poluonumo()<<endl; //to poluonumo mas
		pol_f1->print_array(); //o pinakas tou poluonumou mas
		//delete pol_f1;
	}
	delete interpolation_matrix;

	poluonuma[0]=pol_f;
	poluonuma[1]=pol_f1;

	m_syl = new mitroo_sylvester(poluonuma[0], poluonuma[1], metabliti_to_hide(poluonuma[0], poluonuma[1]));

	m_syl->create_mitroo_sylvester();

	//m_syl->print_mitroo_sylvester();


	p_syl = new poluonumo_sylvester(m_syl, poluonuma[0], poluonuma[1]);


	cout << endl << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "+-------------------+---------------------------+----------------------" << endl;
	cout << "+-------------------| STRATING TO COMPUTE ROOTS |---------------------+" << endl;
	cout << "+-------------------+---------------------------+---------------------+" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << endl;
	sugkrisi = pow(10, B);

	k = upologismos_k(p_syl);
	if (check_det(p_syl))// edw tsekaro tn orizousa an epistrepsi 0 tote k oi 3 orizouses ine 0;
	{

		cout << "k:" << k << endl << endl;
		if (k < sugkrisi && k != -1) {
			cout << "                        +--------------------+                        " << endl;
			cout << "                        |  STANDARD PROBLEM  |                        " << endl;
			cout << "                        +--------------------+                        " << endl;

			solve_standard_eigen_problem(poluonuma, p_syl, k,false,0,0,0,0);
		}
		else {
			cout << "                        +-----------------------+                     " << endl;
			cout << "                        |  GENERALIZED PROBLEM  |                     " << endl;
			cout << "                        +-----------------------+                     " << endl;
			solve_gen_eig_problem(poluonuma, p_syl, k,false,0,0,0,0);
		}
	}
	cout << endl << endl;
//*/
	////////////////////telos////////////////////////////////

	string answer;

	cout << endl << "Do you want to recompute with change of variable? Y/N" << endl;
	cin >> answer;
	if ((strcmp(answer.data(), "Y") == 0) || (strcmp(answer.data(), "y") == 0))
	{
		//erotima 4=allagi poluonumou_sylvester//////////////
		int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
		double new_k = 0;
		poluonumo_sylvester *new_p_syl = NULL;

		poluonumo **new_poluonuma;
		new_poluonuma = new poluonumo*[2];



		for (int i = 0; i < 3; i++) { //i diadikasia tha ginei 3 fores
			random_numbers(&t1, &t2, &t3, &t4); //paragoume 4 tuxaious arithmous
			cout << "t1:" << t1 << "t2:" << t2 << "t3:" << t3 << "t4:" << t4 << endl;
			new_k = change_of_max_orou(p_syl, t1, t2, t3, t4); //ftiaxnoume ton max oro tou poluonumou_sylvester meta tin allagi metablitis
			if (new_k < k || (k==-1 && new_k!=-1) ) { //kai elegxoume an to k einai mikrotero apo to prototupo poluonumi_sylvester
				new_p_syl = erotima_4(p_syl, t1, t2, t3, t4); //ean einai to paragoume to kainourgio poluonumo_sylvester
				break;
			}
		}


		if (new_p_syl != NULL) {
			new_p_syl->print_poluonumo_mitrown();
			cout << "new_k=" << new_k << endl;
			if (new_k < sugkrisi && new_k != -1) {
				cout << "                        +--------------------+                        " << endl;
				cout << "                        |  STANDARD PROBLEM  |                        " << endl;
				cout << "                        +--------------------+                        " << endl;
				solve_standard_eigen_problem(poluonuma, new_p_syl, new_k,true,t1,t2,t3,t4);
			}
			else {
				cout << "                        +-----------------------+                     " << endl;
				cout << "                        |  GENERALIZED PROBLEM  |                     " << endl;
				cout << "                        +-----------------------+                     " << endl;
				solve_gen_eig_problem(poluonuma, new_p_syl, new_k,true,t1,t2,t3,t4);
			}

			delete new_p_syl;
			delete[] new_poluonuma;
		}

	}
	else if ((strcmp(answer.data(), "N") == 0) || (strcmp(answer.data(), "n") == 0))
	{

	}
	else
	{
		cout << "Wrong answer. terminating!" << endl;
	}
	

	//diagrafes (uparxoun apo to meros proto)
	delete poluonuma[0];
	delete poluonuma[1];
	delete [] poluonuma;
	delete m_syl;
	delete p_syl;
	return 0;
	/////////////////////

}

