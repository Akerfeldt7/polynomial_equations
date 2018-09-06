//poluonumo_sylvester.cpp

#include "headers/poluonumo_sylvester.h"
#include <string>
#include <iomanip>

#include <sstream>

#define OUTPUT 15



poluonumo_sylvester::poluonumo_sylvester(mitroo_sylvester *m,poluonumo *p1,poluonumo *p2)
{
	//cout << "ime sti arxi tis poluonumo_silvester" << endl;
	f0=p1;
	f1=p2;
	diastasi=m->give_diastasi(); //diastasi mitroon
	hidden=m->give_hidden(); //i krummeni metabliti (kai metabliti tou poluonumou sylvester)
	bathmos_hidden(); //arxikopoiei ton bathmo_krimenis pou einai o bathmos tou poluonumou //to ebala edo arxika
	
	//////////////////////////////////////
	//dimiourgoume kai antigrafoume ton pinanaka tou mitroo_sylvester
	int i,j; 
	mitroo = new poluonumo**[diastasi]; 
	for(i=0;i<diastasi;i++) { 
		mitroo[i]=new poluonumo*[diastasi]; 
	} 
	for(i=0;i<diastasi;i++){ 
		for(j=0;j<diastasi;j++){ 
			mitroo[i][j] = NULL; 
		}	 
	} 
	for(i=0;i<diastasi;i++){ 
		for(j=0;j<diastasi;j++){
			mitroo[i][j]=m->give_poluonumo(i,j);  
		} 
	}
	//upenthimisi oti o sugkekrimenos pinakas mitroo exei se kathe tou thesi
	//diaforetiko deikti se poluonumo akoma kai gi auta pou exoun ginei shift
	//giati ta pairnei meso tis give_poluonumo pou kanei copy contructor
	//se antithesi me ton pinaka mitroo tou mitroo_sylvester

	///////////////////////////////////////////////

	for (int i = 0; i < diastasi; ++i)
	{
		for (int j = 0; j < diastasi; ++j)
		{
			if (mitroo[i][j] != NULL && hidden == "x")
			{
				if (bathmos_krimenis < mitroo[i][j]->give_max_x())
					bathmos_krimenis = mitroo[i][j]->give_max_x();
				if(!mitroo[i][j]->array_exist()){
					mitroo[i][j]->create_array();
				}

			}
			else if (mitroo[i][j] != NULL && hidden == "y")
			{
				if (bathmos_krimenis < mitroo[i][j]->give_max_y())
					bathmos_krimenis = mitroo[i][j]->give_max_y();
				if(!mitroo[i][j]->array_exist()){
					mitroo[i][j]->create_array();
				}
			}
		}
	}

//	cout << "brika tn bathmo tis krimenis :" << bathmos_krimenis << endl;

	poluonumo_mitrown = new double**[bathmos_krimenis + 1];							//DOUBLE SE OLA TA NEW!!!!!!!!!!!!!!!!!!!!!!!
	for (int i = 0; i < bathmos_krimenis + 1; ++i)
	{
		poluonumo_mitrown[i] = new double* [diastasi];

		for (int j = 0; j < diastasi; ++j)
		{
			poluonumo_mitrown[i][j] = new double[diastasi];
		}
	}

	for (int i = 0; i < bathmos_krimenis + 1; ++i)
	{
		for (int j = 0; j < diastasi; ++j)
		{
			for (int k = 0; k < diastasi; ++k)
			{
				poluonumo_mitrown[i][j][k] = 0;
			}
		}
	}
	
	if (hidden == "x")
	{

		for (int i = 0; i < diastasi; i++)
		{

			for (int j = 0; j < diastasi; j++)
			{
				//cout << "ime edw\n";
				if (mitroo[i][j] != NULL)
				{
					//cout << " mpika mesa\n" << mitroo[i][j]->give_max_x() << endl <<  mitroo[i][j]->give_max_y() << endl;
					//cout << "print array\t";
					//mitroo[i][j]->print_array();
					for (int k = 0; k <= mitroo[i][j]->give_max_x(); k++)//stili
					{

						for (int l = 0; l <= mitroo[i][j]->give_max_y(); l++)//grammi
						{
							//cout << mitroo[i][j]->give_suntelesti_from_table(l, k)<<"\tsto telefteo for\n";
							poluonumo_mitrown[k][i][j] = mitroo[i][j]->give_suntelesti_from_table(l, k);
							//cout << "\tpoluonumo_mitrown[" << k << "][" << i << "][" << j << "]: " << poluonumo_mitrown[k][i][j] << endl;
						}
					}
				}
				//else cout << "ine NULL\n";

			}
		}
	}
	else if (hidden == "y")
	{
		for (int i = 0; i < diastasi; i++)
		{
			for (int j = 0; j < diastasi; j++)
			{
				if (mitroo[i][j] != NULL)
				{
					for (int k = 0; k <= mitroo[i][j]->give_max_x(); k++) //stili
					{
						for (int l = 0; l <= mitroo[i][j]->give_max_y(); l++) //grammi
						{
							poluonumo_mitrown[l][i][j] = mitroo[i][j]->give_suntelesti_from_table(l, k);
						}
					}
				}
			}
		}
	}
}
										//to apokatw 8eli double
poluonumo_sylvester::poluonumo_sylvester(double ***table,int d,int megethos_mitrown,string s){ //contructor pou xreisimopoieitai meta apo tin allagi_metablitis
	int i,j,k;		
	bathmos_krimenis=d;
	diastasi=megethos_mitrown;
	hidden=s;
	f0=NULL;
	f1=NULL;
	mitroo=NULL;

	poluonumo_mitrown = new double**[bathmos_krimenis + 1];		//double sta new!!!!!
	for (int i = 0; i < bathmos_krimenis + 1; ++i)
	{
		poluonumo_mitrown[i] = new double* [diastasi];

		for (int j = 0; j < diastasi; ++j)
		{
			poluonumo_mitrown[i][j] = new double[diastasi];
		}
	}

	for (int i = 0; i < bathmos_krimenis + 1; ++i)
	{
		for (int j = 0; j < diastasi; ++j)
		{
			for (int k = 0; k < diastasi; ++k)
			{
				poluonumo_mitrown[i][j][k]=table[i][j][k];
			}
		}
	}
}

	
	

poluonumo_sylvester::~poluonumo_sylvester(){ 
	int i,j;
	for(i=0;i<bathmos_krimenis+1;i++){
		for(j=0;j<diastasi;j++){
			delete []poluonumo_mitrown[i][j];
		}
		delete []poluonumo_mitrown[i];
	}
	delete []poluonumo_mitrown;
	
	if(mitroo!=NULL){
		//kainourgio gia tin diagrafi tou mitroo meta tin apokripsi
		for (i = 0; i < diastasi; i++) {
			for (j = 0; j < diastasi; j++) {
				delete mitroo[i][j];
			}
		}
		for (i = 0; i < diastasi; i++) {
			delete []mitroo[i];
		}
		delete []mitroo;
	}
	/////////////////////////////
}
		

void poluonumo_sylvester::bathmos_hidden()
{
	int x0, x1, y0, y1;
	//int bathmos_krimenis = 0;
	if  (hidden == "x")
	{
		x0 = f0->give_max_x();
		x1 = f1->give_max_x();
		if (x0 >= x1)
			//return x0 ;
			bathmos_krimenis=x0;
		else
			//return x1 ;
			bathmos_krimenis=x1;
	}
	else
	{
		y0 = f0->give_max_y();
		y1 = f1->give_max_y();
		if (y0 >= y1)
			//return y0 ;
			bathmos_krimenis=y0;
		else
			//return y1 ;
			bathmos_krimenis=y1;
	}
}

void poluonumo_sylvester::print_poluonumo_mitrown() //ektuponei olo to poluonumo
{

	//int bathmos_krimenis;

	//bathmos_krimenis = bathmos_hidden();
cout<< "POLYONYMO MITROWN\n";
//cout << bathmos_krimenis << " " << diastasi << endl;
//	cout << "ime stn arxi tis print_poluonumo_mitrown" << endl;
cout<<endl<<"Degree of expression Sylvester:"<<bathmos_krimenis<<endl;
cout<<"Dimmension of matrix:"<<diastasi<<"X"<<diastasi<<endl;

//	cout << "brika ton bathmo tis krimenis: " << bathmos_krimenis << " k diastasi:" << diastasi << endl;
	
		for (int i = 0; i < bathmos_krimenis + 1; ++i)
		{
			cout << endl << endl;
			for (int j = 0; j < diastasi; ++j)
			{

				if (j == (diastasi / 2))
					cout << setw(5) << hidden << "^" << i << "*";
				else
					cout << setw(5) << "\t";

				for (int k = 0; k < diastasi; ++k)
				{
					cout << setw(5) << poluonumo_mitrown[i][j][k];
				}
				if (j == (diastasi / 2))
					cout << setw(5) << "\t+";

				cout << endl;
			}
		}
	
	//cout << setw(5) << poluonumo_mitrown[0][0][0];

}

void poluonumo_sylvester::print_mitroo_suntelesti(int Ak) //ektuponei mono to mitroo_suntelesti pou zziteitai
{
	if(Ak>bathmos_krimenis){
		cout<<"You ask for bigger companion-matrix than the degree of the expression_Sylvester"<<endl;
	}	
	else{
		cout << endl << endl;
		cout<<endl<<"Degree of expression Sylvester:"<<bathmos_krimenis<<endl;
		cout<<"Dimmension of matrix:"<<diastasi<<"X"<<diastasi<<endl;
		cout<<"Companion-matrix:"<<Ak<<endl;
		for (int j = 0; j < diastasi; ++j)
		{
			for (int k = 0; k < diastasi; ++k)
			{
				cout << setw(5) << poluonumo_mitrown[Ak][j][k];
			}
			cout << endl;
		}
	}
	
}

int poluonumo_sylvester::give_bathmo(){
	return bathmos_krimenis;
}
	
/////////////////////////////////////////meros_2////////////////////////////////////////////////////////////////
string poluonumo_sylvester::give_hidden(){ //epistrefei poia einai i krummeni metabliti
	return hidden;
}

int poluonumo_sylvester::give_diastasi(){ //epistrefei tin diastasi ton mitrown
	return diastasi;
}

double * poluonumo_sylvester::transform_2d_to_1d(double * table_1d,int diastasi_1d,int Ak){  //epistrefei se monodiastato pinaka double collumn major to mitroo pou zitatai
	int point=0;
	if(Ak>bathmos_krimenis){
		cout<<"You ask for bigger companion-matrix than the degree of the expression_Sylvester"<<endl;
		return NULL;
	}	
	if(diastasi_1d!=diastasi*diastasi){
		cout<<"Wrong dimension of 1d-table"<<endl;
		return NULL;
	}
	for(int j=0;j<diastasi;j++){  
		for(int k=0 ;k<diastasi;k++){
			table_1d[point]=poluonumo_mitrown[Ak][k][j]; //collumn-major layout
			point++;
		}
	}
	return table_1d;
}
//AUTI EDO I SUNARTISI XRISIMOPOIEITAI MESA STIN CHANGE_POLUNUMO_SYLVESTER KAI PLEON EXO TIN ENTUPOSI OTI DEN THA XREIAZETAI MOLIS GINOUN KAI OI ALLAGES SE AUTO TO ARXEIO
//double sta int *
int * poluonumo_sylvester::transform_2d_to_1d(int * table_1d,int diastasi_1d,int Ak){  //epistrefei se monodiastato pinaka int collumn major to mitroo pou zitatai
	int point=0;
	if(Ak>bathmos_krimenis){
		cout<<"You ask for bigger companion-matrix than the degree of the expression_Sylvester"<<endl;
		return NULL;
	}	
	if(diastasi_1d!=diastasi*diastasi){
		cout<<"Wrong dimension of 1d-table"<<endl;
		return NULL;
	}
	for(int j=0;j<diastasi;j++){  
		for(int k=0 ;k<diastasi;k++){
			table_1d[point]=poluonumo_mitrown[Ak][k][j]; //collumn-major layout
			point++;
		}
	}
	return table_1d;
}
//double ta int** //AUTI EDO I SUNARTISI XRISIMOPOIEITAI MESA STIN CHANGE_POLUNUMO_SYLVESTER KAI PLEON EXO TIN ENTUPOSI OTI DEN THA XREIAZETAI MOLIS GINOUN KAI OI ALLAGES SE AUTO TO ARXEIO
double ** poluonumo_sylvester::give_mitroo(double ** table,int Ak,int megethos){ //epistrefei se disdiastato pinaka int to mitroo pou zitatai
	if(Ak>bathmos_krimenis){
		cout<<"You ask for bigger companion-matrix than the degree of the expression_Sylvester"<<endl;
		return NULL;
	}
	
	if(diastasi!=megethos){
		cout<<"Wrong dimension of 1d-table"<<endl;
		return NULL;
	}	
	
	for(int j=0;j<diastasi;j++){
		for(int k=0;k<diastasi;k++){
			table[j][k]=poluonumo_mitrown[Ak][j][k];
		}
	}
	return table;
}

double ** poluonumo_sylvester::get_mitroo(double ** array, int Ak) //epistrefei se disdiastato pinaka double to mitroo pou zitatai
{
	if (Ak > bathmos_krimenis)
	{
		cout << "You ask for bigger companion-matrix than the degree of the expression_Sylvester" << endl;
		return NULL;
	}

	for (int i = 0; i < diastasi; ++i)
	{
		for (int j = 0; j < diastasi; ++j)
		{
			array[i][j] = poluonumo_mitrown[Ak][i][j];
		}
	}

	return array;
}
























	
	
	

