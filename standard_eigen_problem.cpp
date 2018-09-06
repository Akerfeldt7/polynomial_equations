//standard_eigen_problem.cpp

#include "headers/standard_eigen_problem.h"

double** topothetisi(double **c,MatrixXd pinakas,int diastasi_companion,int diastasi,int arithmos_mitroou);
double * metatropi_2d_to_1d(double ** table_2d,int diastasi_companion);






standard_eigen_problem::standard_eigen_problem(poluonumo_sylvester *p){
	all_rizes=NULL;
	plithos_luseon=0;
	p_syl=p;
	if(p_syl->give_hidden()=="x"){
		hidden="x";
		another="y";
	}
	else{
		hidden="y";
		another="x";
	}

	d=p_syl->give_bathmo(); //auto einai to d
	diastasi=p_syl->give_diastasi(); //auto einai to m
	diastasi_companion=d*diastasi; //i diastasi tou companion
	if(d==1){
		//contruct companion
		construct_companion();
	}
	else{
		//contruct big companion
		construct_big_companion();
	}
}

standard_eigen_problem::~standard_eigen_problem(){  //destructor
	delete all_rizes;
}



void standard_eigen_problem::construct_companion(){ //Gia d=1
	double * first;
	double * second;

	int diastasi_1d=(diastasi*diastasi);
	first=new double[diastasi_1d];
	second=new double[diastasi_1d];
	
	first=p_syl->transform_2d_to_1d(first,diastasi_1d,1);
	second=p_syl->transform_2d_to_1d(second,diastasi_1d,0);
	
	//diastasi=p_syl->give_diastasi(); to exo ballei ston contructor
	Map<MatrixXd> m1(first,diastasi,diastasi);
	Map<MatrixXd> m0(second,diastasi,diastasi);

	//cout<<m1<<endl;
	//cout<<m0<<endl;

	
	m1=m1.inverse();
	m1=-1*m1;
	companion=m1*m0;
	
	//double *p=&c(0); //get the address storing the data for c
	//companion(c,diastasi,diastasi); //a read-only accesor for c
	
	

	delete []first;
	delete []second;
	
	
	//cout<<companion<<endl;

	compute_big_roots(); //MPOREI NA EINAI LATHOS kai na thelei to apo pano
	
	
}



void standard_eigen_problem::construct_big_companion(){ //d>=2
	int i=0,j=0;
	//int diastasi_companion;
	double **c; //autos tha einai o companion pou tha metasximatisoume stin morfi matrixXd

	int diastasi_companion=diastasi*d; //m*d opou m=dim(Mi) kai d=bathmos pol.Syl
	
	c=new double*[diastasi_companion]; //desmeusi tou disdiastatou pinaka c
	for(i=0;i<diastasi_companion;i++){
		c[i]=new double[diastasi_companion];
	}
	
	////////////////////////////////////////////////////////////////////////////////
	//tora theloume na ton gemisoume auton ton pinaka
	//tha ton gemisoume grammi grammi mexri tin teleutaia grammi pros to paron
	//tha gemisoume tin proti grammi bazontas stis theseis
	//0-(m-1)-->0 ,m-->1, (m+1)-(diastasi_companion-1)--->0
	for(i=0;i<diastasi_companion;i++){//gemizoume tin proti grammi 
		if(i==diastasi){		
			c[0][i]=1;
		}
		else{
			c[0][i]=0;
		}
	}
	for(i=1;i<diastasi_companion;i++){ //arxikopoioume tis upoloipes grammes me midenika
		for(j=0;j<diastasi_companion;j++){
			c[i][j]=0;
		}
	}		
	
	//afou gemisoume tin proti grammi kai genika ton pinaka,apla kanoume shift mexri tin grammi diastasi_companion-diastasi
	for(i=0;i<diastasi_companion-diastasi;i++){
		for(j=0;j<diastasi_companion;j++){
			if (j+1==diastasi_companion){ //tote bgainei ektos oriou
				continue;
			}
			else{
				c[i+1][j+1]=c[i][j];
			}
		}
	}

	//os edo ftiaksame ton pinaka me ta midenika kai tous assous
	//tora theloume na ftiaksoume tis teleutaies grammes tou pinaka
	//pou tha einai apo stoixeia ton mitroon
	//////////////////////////////////////////////////////////////////

	//ta ginomena pinakon einai oses fores einai to d
	//katarxas tha xreiastoume to mitroo tou megistobathmiou orou
	double *pinakas_meg_orou;
	int diastasi_1d=diastasi*diastasi;
	pinakas_meg_orou=new double[diastasi_1d];
	pinakas_meg_orou=p_syl->transform_2d_to_1d(pinakas_meg_orou,diastasi_1d,d);
	Map<MatrixXd> m_megalo(pinakas_meg_orou,diastasi,diastasi);
	//cout<<"M_MEGALO---->"<<endl<<m_megalo<<endl;
	m_megalo=m_megalo.inverse();
	m_megalo=-1*m_megalo;
	//cout<<"meta apo prakseis M_MEGALO---->"<<endl<<m_megalo<<endl;

	//tora prepei na pairnoume apo to 0 mexri kai to d-1 
	//kai na ta pollaplasiazoume me to megalo kai na bazoume tis times ston c stis katalliles theseis
	double *pinakas;
	pinakas=new double[diastasi_1d];
	for(i=0;i<d;i++){
		pinakas=p_syl->transform_2d_to_1d(pinakas,diastasi_1d,i);
		Map<MatrixXd> m(pinakas,diastasi,diastasi);
		//cout<<"pollaplasiazo ton M_MEGALO me ton m"<<i<<":"<<endl<<m<<endl;
		m=m_megalo*m;
		//tora auton ton pinaka prepei ta stoixeia tou na ta bazoume stis katalliles theseis tou c
		//cout<<"kai pairno ton:"<<endl<<m<<endl;
		c=topothetisi(c,m,diastasi_companion,diastasi,i); //opou i o arithmos mitroou
	}
	
	//cout<<"AUTOS EINAI O ETOIMOS"<<endl; //o disdiastatos pinakas c
	/*for(i=0;i<diastasi_companion;i++){ //ektuposi tou
		for(j=0;j<diastasi_companion;j++){
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}*/
	
	//tora prepei na ton kanoume monodiastato gia na ton parei i EIGEN
	double *table_1d;
	table_1d=metatropi_2d_to_1d(c,diastasi_companion);
	
	Map<MatrixXd> temp_companion(table_1d,diastasi_companion,diastasi_companion);
	
	companion=temp_companion; //edo exoume ton companion se morfi tis Eigen
	
	//diagrafi ton pinakon pou xrisimopoihsa gia na kataskeuaso ton companion
	delete []table_1d; 
	delete []pinakas_meg_orou;
	delete []pinakas;
	for(i=0;i<diastasi_companion;i++){
		delete []c[i];
	}
	delete []c;	
	
	compute_big_roots();
	
			
}





void standard_eigen_problem::compute_big_roots(){ //gia d>=2
	int i,j;
	

	EigenSolver<MatrixXd> es(companion);
	//cout<<"The eignevalues of companion are:"<<endl<<es.eigenvalues()<<endl;
	//cout<<"The matrix of eigenvectors,V,is:"<<endl<<es.eigenvectors()<<endl;	

	//ftiaxno ta idiodianusmata etsi opos mas boleuoun kanonikopoiontas ta
	MatrixXcd test=es.eigenvectors();
	for(i=0;i<diastasi;i++){ //gia tis grammes 0-(diastasi-1) opou diastasi einai i diastasi ton mitroon tou poluonumou
		for(j=0;j<diastasi_companion;j++){ //oles tis stiles tou companion
			test(i,j)=test(i,j)/test(diastasi-1,j);
		}
	}
	//cout<<"The matrix of eigenvectors,V,with (...,1) is:"<<endl<<test<<endl;
	MatrixXcd krumeni_root=es.eigenvalues();

	
	///////////////////////////////////////////////////

	
	for(i=0;i<krumeni_root.rows();i++){ //upologizo poses pragmatikes rizes uparxoun meso ton idiodiatimon
		if( (imag(krumeni_root(i))==0)){
			plithos_luseon++;
		}
	}

	

	//cout<<"plithos_luseon:"<<plithos_luseon<<endl;

	
	all_rizes=new roots(plithos_luseon,hidden); //dimiourgo to antikeimeno roots pou tha exei tis luseis 
	if(hidden=="x"){
		for(i=0;i<diastasi_companion;i++){ //gemizo ton pinaka_luseon
			if( (imag(krumeni_root(i))==0) && (real(test(diastasi-1,i))==1)){
				all_rizes->add_root(real(krumeni_root(i)),real(test(diastasi-2,i)),true); 
			}
			else if( (imag(krumeni_root(i))==0) && (real(test(diastasi-1,i))!=1)){
				all_rizes->add_root(real(krumeni_root(i)),real(test(diastasi-2,i)),false); //den mas kanei to idiodianusma
			}
		}
	}
	else{
		for(i=0;i<diastasi_companion;i++){ //gemizo ton pinaka_luseon
			if( (imag(krumeni_root(i))==0) && (real(test(diastasi-1,i))==1)){
				all_rizes->add_root(real(test(diastasi-2,i)),real(krumeni_root(i)),true);
			}
			else if( (imag(krumeni_root(i))==0) && (real(test(diastasi-1,i))!=1)){
				all_rizes->add_root(real(test(diastasi-2,i)),real(krumeni_root(i)),false); //den mas kanei to idiodianusma
			}
		}
	}

	
	
}
	



roots *standard_eigen_problem::give_roots(){ 
	roots *duplicate;
	duplicate=new roots(*all_rizes); //dimiourgoume antigrafo ton rizon gia na steiloume ekso apo tin klassi
	return duplicate;
}

int standard_eigen_problem::give_plithos_luseon(){
	return plithos_luseon;
}





double ** topothetisi(double **c,MatrixXd pinakas,int diastasi_companion,int diastasi,int arithmos_mitroou){ //boithitiki sunartisi,xrisimopoieitai stin kataskeui tou companion gia d>=2
	int i,j;
	//tha topothetoume apo tin grammi diastasi_companion-diastasi
	//tora i stili pou tha arxizoume eksartatai
	//tha arxizoume apo stili--> arithmo_mitroo*diastasi
	int grammi=diastasi_companion-diastasi;
	int stili=arithmos_mitroou*diastasi;
	for(i=0;i<diastasi;i++){
		for(j=0;j<diastasi;j++){
			c[grammi][stili]=pinakas(i,j);
			stili++;
		}
		stili=arithmos_mitroou*diastasi;
		grammi++;
	}
	return c;
}

double * metatropi_2d_to_1d(double ** table_2d,int diastasi_companion){ //boithitiki sunartisi,xrisimopoietai gia tin metatropi enos 2d-pinaka se 1d
	int point=0;
	int diastasi_1d=diastasi_companion*diastasi_companion;	
	double *table_1d;	
	table_1d=new double[diastasi_1d];	
	
	for(int j=0;j<diastasi_companion;j++){  
		for(int k=0 ;k<diastasi_companion;k++){
			table_1d[point]=table_2d[k][j]; //collumn-major layout
			point++;
		}
	}
	return table_1d;
}


















