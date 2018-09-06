//one_var_companion.cpp

#include "headers/one_var_companion.h"

double * transform_2d_to_1d(double ** ,int);


one_var_companion::one_var_companion(poluonumo * some,string s){

	f=some;
	var=s;
	plithos_luseon=0;
	luseis=NULL;
	/*if(var=="y"){
		dim=f->give_max_y(); //i diastasi isoutai me ton megisto bathmo tis metablitis
	}
	else{
		dim=f->give_max_x(); //i diastasi isoutai me ton megisto bathmos tis metablitis
	
	}*/
	dim=f->give_max_one_var();
	construct_companion();
	//solve_companion();
}

one_var_companion::~one_var_companion(){
	if(luseis!=NULL){
		delete []luseis;
	}
}


void one_var_companion::construct_companion(){
	int i,j;
	//cout<<"mpaino edo mesa me dim:"<<dim<<endl;
	if(dim==1){
		double * c;
		c=new double[1];
		c[0]=-(f->give_suntelesti_from_table(0,0)); //pairnei ton c0 tou poluonumou mono
		//cout<<c[0]<<endl; 
		Map<MatrixXd> temp_companion(c,1,1); //dinoume ton pinaka stin Eigen
		companion=temp_companion;
		delete []c;
		solve_companion();
	}
	else if(dim==0){
		//uparxoun 2 periptoseis:
		//1)eite o statheros tou oros einai 0 opote i luseis einai appeires
		//2)eite o statheros tou oros einai diaforetikos tou 0 opote den midenizetai
		//f->print_array();
		int number;
		number=f->give_suntelesti_from_table(0,0);
		if(number==0){ //edo isos thelei ssugkrisi me FABS
			//luseis=new double[1];
			//luseis[0]=0;
			plithos_luseon=-1; //diladi exei apeires luseis
		}
		else{
			cout<<"DEN EXEI LUSH TO POLUONUMO"<<endl;
		}
		//Se autin edo tin periptosi den kaloume solve_companion giati exoume brei tis luseis apo pio pano	
	}
	else{
		double ** disdiastatos_c; 
		disdiastatos_c=new double*[dim];
		for(i=0;i<dim;i++){
			disdiastatos_c[i]=new double[dim];
		}
	
		
		//gemizoume tin proti grammi tou pinaka
		for(i=0;i<dim;i++){
			if(i==1){
				disdiastatos_c[0][i]=1;
			}
			else{
				disdiastatos_c[0][i]=0;	
			}
		}
		
		//arxikopoioume tis upoloipes grammes me midenika
		for(i=1;i<dim;i++){
			for(j=0;j<dim;j++){
				disdiastatos_c[i][j]=0;
			}
		}
		
		//afou gemisoume ton pinaka theloume na kanoume shift mexri tin proteleutaia grammi
		for(i=0;i<dim-1;i++){
			for(j=0;j<dim;j++){
				if(j+1==dim){//bgainei ektos orion
					continue;
				}
				else{
					disdiastatos_c[i+1][j+1]=disdiastatos_c[i][j];
				}
			}
		}
		
		//os edo ftiaksame ton pinaka me mideika kai tous assous
		//tora theloume na ftiaksoume tin teleutaia grammi tou pinaka
		//pou tha einai oi statheroi oroi tou poluonumou ektos apo to megistobathmio
		
		for(i=0;i<dim;i++){
			if(var=="y"){
				disdiastatos_c[dim-1][i]=-(f->give_suntelesti_from_table(i,0)); //na prosekso to -0
			}
			else{
				disdiastatos_c[dim-1][i]=-(f->give_suntelesti_from_table(0,i)); //na prosekso to -0
			}
		}
		
		//debugging ektuposi
		/*for(i=0;i<dim;i++){
			for(j=0;j<dim;j++){
				cout<<disdiastatos_c[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
		*/
		////////////////////////////////////////////////////

		//tora prepei ton disdiastatos_c na ton metatrepsoume se 1d_pinaka collumn major kai na ton dosoume stin eigen
		double * table_1d;
		table_1d=transform_2d_to_1d(disdiastatos_c,dim);
		for(i=0;i<dim;i++){
			delete []disdiastatos_c[i];
		}
		delete []disdiastatos_c;
		Map<MatrixXd> temp_companion(table_1d,dim,dim); //dinoume ton pinaka stin Eigen
		companion=temp_companion;
		delete []table_1d;
		solve_companion();
	}

	//cout<<"ETOIMOS O COMPANION"<<endl;
	//cout<<companion<<endl;


}

void one_var_companion::solve_companion(){
	int i;	
	
	EigenSolver<MatrixXd> es(companion);
	//cout<<"poluonumo array:"<<endl;
	//f->print_array();
	//cout<<"The eignevalues of companion are:"<<endl<<es.eigenvalues()<<endl; //oi idiotimes einai oi luseis pou theloume
	//cout<<"The matrix of eigenvectors,V,is:"<<endl<<es.eigenvectors()<<endl;

	MatrixXcd idiotimes=es.eigenvalues();
	for(i=0;i<idiotimes.rows();i++){ //upologizo poses pragmatikes rizes uparxoun meso ton idiodiatimon
		if( (imag(idiotimes(i))==0)){
			plithos_luseon++;
		}
	}	
	//cout<<"plithos_luseon:"<<plithos_luseon<<endl;

	//gemizo enan pinaka me tis pragmatikes rizes
	luseis=new double[plithos_luseon];
	int point=0;
	for(i=0;i<idiotimes.rows();i++){ 
		if( (imag(idiotimes(i))==0)){
			luseis[point]=real(idiotimes(i));
			point++;
		}
	}	
	//////
	/*for(i=0;i<plithos_luseon;i++){ //gia ektuposi na to sbiso
		cout<<luseis[i]<<endl;
	}*/
	
	
}

int one_var_companion::give_plithos_luseon(){
	return plithos_luseon;
}

double * one_var_companion::give_luseis(){
	return luseis;
}



double * transform_2d_to_1d(double ** table_2d,int diastasi){ //boithitiki sunartisi,xrisimopoietai gia tin metatropi enos 2d-pinaka se 1d
	int point=0;
	int diastasi_1d=diastasi*diastasi;	
	double *table_1d;	
	table_1d=new double[diastasi_1d];	
	
	for(int j=0;j<diastasi;j++){  
		for(int k=0 ;k<diastasi;k++){
			table_1d[point]=table_2d[k][j]; //collumn-major layout
			point++;
		}
	}
	return table_1d;
}

	


