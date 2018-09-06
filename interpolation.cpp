//interpolation.cpp

#include "headers/interpolation.h"

double * metatropi_2d_to_1d(double ** table_2d,int,int);



//////////////////////////////////////////////////

lista_point::lista_point(){
	start=NULL;
	last=NULL;
	plithos=0;
}

lista_point::~lista_point(){
	kombos *current;
	kombos *for_delete;
	current=start;
	while(current!=NULL){
		for_delete=current;
		current=current->next;
		delete for_delete->timi;
		delete for_delete;
	}
}

void lista_point::add_to_lista(point *some){
	kombos *n;
	n=new kombos;
	//n->timi=new point;
	//n->timi->x=some->x;
	//n->timi->y=some->y;
	n->timi=some;
	n->next=NULL;
	if(start==NULL){
		start=n;
		last=n;
		n->id=1;
	}
	else{
		last->next=n;
		n->id=last->id+1;
		last=n;
	}
	plithos++;
}

void lista_point::print_lista(){
	kombos *current;
	current=start;
	cout<<"Points={";
	if(current==NULL){
		cout<<"no lista"<<endl;
	}
	while(current!=NULL){
		cout<<"["<<current->timi->x<<","<<current->timi->y<<"]";
		current=current->next;
		if(current!=NULL){
			cout<<",";
		}
	}
	cout<<"}"<<endl;
}

int lista_point::give_plithos(){
	return plithos;
}

double lista_point::give_x_from_kombo(int arithmos_kombou){
	kombos *current;
	current=start;
	if(arithmos_kombou<=0 || arithmos_kombou>plithos){
		cout<<"YOU HAD ASKING FOR WRONG KOMBO"<<endl;
		return 0; //pou einai lathasmeno
	}
	else{
		while(current!=NULL){
			if(current->id==arithmos_kombou){
				return current->timi->x;
			}
			current=current->next;
		}
	}		
			
}

double lista_point::give_y_from_kombo(int arithmos_kombou){
	kombos *current;
	current=start;
	if(arithmos_kombou<=0 || arithmos_kombou>plithos){
		cout<<"YOU HAD ASKING FOR WRONG KOMBO"<<endl;
		return 0; //pou einai lathasmeno
	}
	else{
		while(current!=NULL){
			if(current->id==arithmos_kombou){
				return current->timi->y;
			}
			current=current->next;
		}
	}		
}
	
/////////////////////////////////////////////////////


interpolation::interpolation(lista_point *some,int bathmos){ //contructor
	simeia=some;
	d=bathmos;
	rank=0;
	pol_f=NULL;

	k=(d+2)*(d+1)/2-1;
	//cout<<"k:"<<k<<endl;
	
	if(k==simeia->give_plithos()){
		well_constrained=true;
		cout<<"the system of equations is well-constrained"<<endl;
		construct();
	}
	else if(k>simeia->give_plithos()){
		well_constrained=false;
		cout<<"Overconstrained system,usually no solution"<<endl;
	}
	else{
		well_constrained=false;
		cout<<"Underdefined system,usually infinite solutions"<<endl;
		
	}
}


interpolation::~interpolation(){ //destructor
	delete simeia;
	if(pol_f!=NULL){
		delete pol_f;
	}

}

void interpolation::construct(){
	double **matrix;
	int i,j;	

	matrix=new double*[k]; //k grammes
	for(i=0;i<k;i++){
		matrix[i]=new double[k+1]; //k+1 stiles
	}

	//arxikopoioume ton pinaka me tin proti stili na einai ola 1 kai ta upoloipa kelia me 0
	for(i=0;i<k;i++){
		for(j=0;j<k+1;j++){
			if(j==0){
				matrix[i][j]=1;
			}
			else{
				matrix[i][j]=0;
			}
		}
	}
	/////////////////////
	double x,y;
	int a,b,ab; //to ab einai to a+b pou arxizei apo 1
	for(i=0;i<k;i++){
		a=1;b=0;ab=1; //gia kathe grammi etsi arxikopoiountai auta //einai gia ta permutations 01|10|20|11|02|30|21|12|03|....kai loipa
		x=simeia->give_x_from_kombo(i+1); //i+1 giati to id tou proto kombou einai 1,to i tis for paei sumfona me grammes pinaka kai ksekinaei apo 0
		y=simeia->give_y_from_kombo(i+1); //i+1 giati to id tou proto kombou einai 1,to i tis for paei sumfona me grammes pinaka kai ksekinaei apo 0
		//cout<<"["<<x<<","<<y<<"]"<<endl;
		for(j=1;j<k+1;j++){ //ksekiname apo tin deuteri stili (i proti stili einai me 1 oles oi grammes)
			//cout<<a<<b<<endl;
			//kane tin douleia pou prepei	
			matrix[i][j]=pow(x,(double)a)*pow(y,(double)b); //EDO PROSOXI LIGO STIN PERIPTOSI 0^0!!!!!!! (den tin exo ksexorisei)
			if(b==ab){
				ab++;
				a=ab;
				b=0;
			}
			else{
				a--;
				b++;
			}
			
		}		
	}
	
	/*for(i=0;i<k;i++){ //routinia gia ektuposi
		for(j=0;j<k+1;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	*/	
	
	//prepei na ton 2d pinaka na ton xrisimopoihso prin ton diagrapso(an prepei na ton diagrapso edo pera)
	double *table_1d;
	table_1d=metatropi_2d_to_1d(matrix,k,k+1);

	Map<MatrixXd> temp_matrix(table_1d,k,k+1);
	
	interpolation_matrix=temp_matrix; //edo exoume ton companion se morfi tis Eigen	
	

	//cout<<"etoimos"<<endl;
	cout<<interpolation_matrix<<endl;
		
	upologismos_rank();
	if(rank<k){
		cout<<"rank is smaller than k, so the problem is infeaseble or the solution is numberically unstable!"<<endl;
	}
	else{	
		construct_poluonumo();
	}
	
	

	for(i=0;i<k;i++){ //diagrafoume ton disdiastato pinaka pou xrisimopoihsame
		delete []matrix[i];
	}
	delete []matrix;

	delete []table_1d; //diagrafoume ton monodiastato pinaka pou xrisimopoihsame

	
	

}

void interpolation::construct_poluonumo(){
	int i;
	int a,b,ab; //to ab einai to a+b pou arxizei apo 1
	int max_suntelestis;
	term *some_term;
	pol_f=new poluonumo();

	Eigen::FullPivLU<MatrixXd> lu(interpolation_matrix);
	cout<<lu.kernel()<<endl;
	MatrixXd vectors=lu.kernel();
	a=0;b=0;ab=0;
	max_suntelestis=vectors.rows()-1;
	if(fabs(vectors(max_suntelestis))<0.0001){ //KAINOURGIO 18-1
		max_suntelestis=-1;
	}
		
	for(i=0;i<vectors.rows();i++){
		if(max_suntelestis!=-1){ //KAINOURGIO 18-1 I SUNTHIKI MONO
			some_term=new term(a,b,vectors(i)/vectors(max_suntelestis)); //diairoume olous tous orous me ton suntelesti tou megaluterou orou
		}
		else{
			if(i==vectors.rows()-1){ //KAINOURGIO 18-1
				some_term=new term(a,b,0);
			}
			else{
				some_term=new term(a,b,vectors(i));
			}
		}
		pol_f->add_term(some_term);
		if(b==ab){
			ab++;
			a=ab;
			b=0;
		}
		else{
			a--;
			b++;
		}
		
	}
	//cout<<pol_f->print_poluonumo()<<endl; //etoimo to poluonumo mas!!!
	pol_f->create_array(); //dimiourgoume kai ton pinaka tou gia na einai komple!!

}

poluonumo * interpolation::give_poluonumo(){
	if(pol_f!=NULL){
		poluonumo *duplicate;
		duplicate=new poluonumo(*pol_f);
		return duplicate;
	}
	else{
		return NULL;
	}
}

void interpolation::upologismos_rank(){
	double threshhold=1e-7;
	JacobiSVD<MatrixXd> svd(interpolation_matrix, Eigen::ComputeFullU);
	JacobiSVD<MatrixXd>::SingularValuesType singular = svd.singularValues();

	//cout << "The singular values of A are:" << svd.singularValues() << endl;
	
	for (int i = 0; i < singular.rows(); i++) {
		//cout << "Singular Value " << i << ":" << singular(i) << endl;
		if( singular(i)>threshhold){
			rank++;
		}
	}
	
	//cout<<rank<<endl;
}



/*
	for(i=0;i<k;i++){ //routinia gia ektuposi
		for(j=0;j<k+1;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
*/


double * metatropi_2d_to_1d(double ** table_2d,int grammes,int stiles){ //boithitiki sunartisi,xrisimopoietai gia tin metatropi enos 2d-pinaka se 1d
	int point=0;
	int diastasi_1d=grammes*stiles;	
	double *table_1d;	
	table_1d=new double[diastasi_1d];	
	
	for(int j=0;j<stiles;j++){  
		for(int k=0 ;k<grammes;k++){
			table_1d[point]=table_2d[k][j]; //collumn-major layout
			point++;
		}
	}
	return table_1d;
}
































