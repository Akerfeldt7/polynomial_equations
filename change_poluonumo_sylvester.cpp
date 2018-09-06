//change_poluonumo_sylvester.cpp

#include "headers/change_poluonumo_sylvester.h"





void print_pinaka(double *,int);//pinakas,diastasi //ektuponei monodiastato pinaka
double * pollaplasiasmos_pinaka_with_arithmo(double *,int,double);//pinakas,diastasi,arithmos
double * prosthesi_pinaka_with_pinaka(double *,double *,int); //prosthetei duo pinakes,diastasi
double nea_metabliti_upologismos_k(double *mitroo,int diastasi_1d,int diastasi);
double * transform_int_to_double(int *,int); //metatrepsei enan pinaka int se double  //AUTO EDO DEN XREIAZETAI


void random_numbers(int *t1,int *t2,int *t3,int *t4){
	
	*t1=rand()%10+1; //generate a random number between 1-10
	*t2=rand()%10+1; //generate a random number between 1-10
	*t3=rand()%10+1; //generate a random number between 1-10
	*t4=rand()%10+1; //generate a random number between 1-10
	
}
	

double change_of_max_orou(poluonumo_sylvester *p_syl,int t1,int t2,int t3,int t4){ //max_oros poluonumou meta apo allagi metablitis,epistrefetai to kainourgio k
	int i,j;
	int bathmos; //o bathmos tou poluonumou
	int diastasi; //i diastasi ton mitroon tou poluonumou
	int diastasi_1d; //i diastasi pou tha dosoume stin Eigen (mitroo se monodiastato pinaka)
	double *table_1d; 																									  //DOUBLE !!!!!!!!!!!!!!!!!!
	double ***table_mitroa; //enas disdiastatos pinakas pou periexei se mia diagonio tou (oxi tin kuria) ta mitroa    DOUBLE !!!!!!!!!!!!!!!!!!
	
	double pollaplasiastis; //oi pollaplasiastes ton mitroon
	
	

	bathmos=p_syl->give_bathmo();
	diastasi=p_syl->give_diastasi();
	diastasi_1d=diastasi*diastasi;
	
	

	
	//random_numbers(seed,&t1,&t2,&t3,&t4);
	
	cout<<"----RANDOM NUMBERS----"<<endl;
	cout<<"t1:"<<t1<<endl;
	cout<<"t2:"<<t2<<endl;
	cout<<"t3:"<<t3<<endl;
	cout<<"t4:"<<t4<<endl;
	cout<<"----------------------"<<endl;
	
	//dimiourgoume ton pinaka table_mitroo
	//pou exei sta katallila kelia ta mitroa pou tha xrisimopoihsoume
	//gia tin dimiourgia tou max_mitroo
	table_mitroa=new double**[bathmos+1]; //grammes pinaka
	for(i=0;i<bathmos+1;i++){
		table_mitroa[i]=new double*[bathmos+1]; //stiles pinaka
	}
	int Ak=bathmos;
	for(i=0;i<bathmos+1;i++){
		for(j=0;j<bathmos+1;j++){
			if(i+j==bathmos){ //bazoume se autin tin thesei tou pinaka ton monodiastato pinaka mitroo
				table_1d=new double[diastasi_1d];
				table_1d=p_syl->transform_2d_to_1d(table_1d,diastasi_1d,Ak);
				table_mitroa[i][j]=table_1d;
				Ak=Ak-1;
			}
			else{
				table_mitroa[i][j]=NULL;
			}
		}
	}
	
		


	//metasximatizoume ton table_mitroa
	//pollaplasiazontas ta mitroa me katallilous pollaplasiastes
	//gia na exoume ston pinaka table_mitroa ta mitroa pou tha prosthesoume
	//gia tin dimiourgia tou max_mitroo
	for(i=0;i<bathmos+1;i++){ 
		for(j=0;j<bathmos+1;j++){
			if(table_mitroa[i][j]!=NULL){
				pollaplasiastis=pow(t1,j)*pow(t3,i);
				//cout<<"grammi:"<<i<<"stili:"<<j<<" pollaplasiastis:"<<pollaplasiastis<<endl;
				table_mitroa[i][j]=pollaplasiasmos_pinaka_with_arithmo(table_mitroa[i][j],diastasi_1d,pollaplasiastis);
				
			}
		}
	}


	//arxikopoihsi tou max_mitroo
	double *max_mitroo; 
	max_mitroo=new double[diastasi_1d];
	for(i=0;i<diastasi_1d;i++){
		max_mitroo[i]=0;
	}

	//prosthetoume ta mitroa apo ton table_mitroa sto max_mitroo
	for(i=0;i<bathmos+1;i++){ 
		for(j=0;j<bathmos+1;j++){
			if(table_mitroa[i][j]!=NULL){
				max_mitroo=prosthesi_pinaka_with_pinaka(max_mitroo,table_mitroa[i][j],diastasi_1d);
			}
		}
	}

	

	//print_pinaka(max_mitroo,diastasi_1d);

	Map<MatrixXd> max(max_mitroo,diastasi,diastasi);
	//cout<<"Max_mitroo pou kataskeuasame einai:"<<endl<<max<<endl;

	double new_k=nea_metabliti_upologismos_k(max_mitroo,diastasi_1d,diastasi);
	

	//OI DIAGRAFES TON PINAKON POU XRISIMOPOIHTHIKAN
	for(i=0;i<bathmos+1;i++){ 
		for(j=0;j<bathmos+1;j++){
			if(table_mitroa[i][j]!=NULL){
				delete []table_mitroa[i][j];
			}
		}
		delete []table_mitroa[i];
	}
	delete []table_mitroa;
	///////////////////////////////////////////////
	
	cout<<"NEW_K:"<<new_k<<endl;
	return new_k;
}




double nea_metabliti_upologismos_k(double *mitroo,int diastasi_1d,int diastasi){ //upologistmos k gia poluonumo_sylvester meta apo allagi metablitis
	double smax=0,smin=0;
	double * temp;

	

	//temp=transform_int_to_double(mitroo,diastasi_1d);
	temp=mitroo; //epeidi to parapano tora pou ta kaname double ola den xreiazetai
	
	Map<MatrixXd> m(temp,diastasi,diastasi);

	//cout<<"max_mitroo:"<<endl<<m<<endl;
	
	JacobiSVD<MatrixXd> svd(m,Eigen::ComputeFullU);
	JacobiSVD<MatrixXd>::SingularValuesType singular=svd.singularValues();
	
	//cout<<"The singular values of A are:"<<svd.singularValues()<<endl;

	smin=singular(0);
	for(int i=0;i<singular.rows();i++){
		//cout<<"Singular Value "<<i<<":"<<singular(i)<<endl;
		if(smax<singular(i)){
			smax=singular(i);
		}
		if(smin>singular(i)){
			smin=singular(i);
		}
	}
	double k;
	if(smin==0){
		k=-1; //apeiro
	}
	else{ 
		k=smax/smin;
	}
	//cout<<"k:"<<k<<endl;
	delete []mitroo; //diagrafo to mitroo pou xrisimopoihthike gia ton upologismo tou k
	//delete []temp; //den xreiazetai afou to temp=mitroo
	return k;
	
}


//boithitikes sunartiseis/////////////////////////////////////////////////////////////////

void print_pinaka(double *table,int diastasi){ //ektuponei monodiastato pinaka
	for(int i=0;i<diastasi;i++){
		cout<<table[i]<<" ";
	}
	cout<<endl;
}

double * pollaplasiasmos_pinaka_with_arithmo(double *table,int diastasi,double arithmos){ //pollaplasiazei pinaka me arithmo
	for(int i=0;i<diastasi;i++){
		table[i]=arithmos*table[i];
	}
	return table;
}

double * prosthesi_pinaka_with_pinaka(double *table,double *pinakas,int diastasi){ //prosthetei duo pinakes
	for(int i=0;i<diastasi;i++){
		table[i]=table[i]+pinakas[i];
	}
	return table;
}

/*double * transform_int_to_double(int *table,int diastasi){ //metatrepei enan pinaka int se pinaka doubles
	double *pinakas;
	pinakas=new double[diastasi];
	
	for(int i=0;i<diastasi;i++){
		pinakas[i]=table[i];
	}
	return pinakas;
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void algorithmos(poluonumo_sylvester * p_syl,double ***table_mitrown,int t1,int t2,int t3,int t4,int d,int diastasi,int mitroo);
void pollaplasiasmos_arithmou_me_pinaka(double ***,double ** table,double arithmos,int diastasi,int thesi);
void pollaplasiasmos_kai_prosthesi_arithmou_me_pinaka(double ***temporary_mitrown,double **table1,double **table2,double arithmos,int diastasi,int thesi);
void antigrafi_3d_pinakon(double ***table_mitrown,double ***temporary,int d,int diastasi);
void prosthesi_3d_pinakon(double ***poluonumo_mitrown,double *** table_mitrown,int d,int diastasi);

poluonumo_sylvester * erotima_4(poluonumo_sylvester *p_syl,int t1,int t2,int t3,int t4){ //sunartisi gia allagi_metablitis tou poluonumou_sylvester
	
	
	//tora prepei na dimiourgisoume 1 monodiastato pinaka d+1 megethous
	//pou tha bazoume mesa ta mitroa(2d int pinakes)
	//gia na baloume ta mitroa tou Poluonumou_sylvester
	int d=p_syl->give_bathmo(); //o bathmos tou poluonumou sylvester
	int diastasi=p_syl->give_diastasi(); //i diastasi ton mitroon
	double ***poluonumo_mitrown;

	poluonumo_mitrown=new double**[d+1];
	for(int i=0;i<d+1;i++)
	{
		poluonumo_mitrown[i]=new double*[diastasi];
		for(int j=0;j<diastasi;j++)
		{
			poluonumo_mitrown[i][j]=new double[diastasi];
		}
	}
	
	//arxikopoioume me 0 ola ta kelia
	for(int i=0;i<d+1;i++){
		for(int j=0;j<diastasi;j++){
			for(int k=0;k<diastasi;k++){
				poluonumo_mitrown[i][j][k]=0;
			}
		}
	}
	
	/////////////////////////////////////////////////////////
	//tora xreiazomaste 1 3d-pinakaki d+1,diastasi,diastasi megethous pou tha ta xrisimopoihsoume gia tous pollaplasiasmous
	//kai meta tha to prosthetoume sto apo pano
	

	double ***table_mitrown;
	table_mitrown=new double**[d+1];
	for(int i=0;i<d+1;i++)
	{
		table_mitrown[i]=new double*[diastasi];
		for(int j=0;j<diastasi;j++)
		{
			table_mitrown[i][j]=new double[diastasi];
		}
	}
	
	//arxikopoioume me 0 ola ta kelia
	for(int i=0;i<d+1;i++){
		for(int j=0;j<diastasi;j++){
			for(int k=0;k<diastasi;k++){
				table_mitrown[i][j][k]=0;
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////

	//o parakato algorithmos pou ftiaxnei ta mitroa tha trexei d+1 fores (diladi gia kathe mitroo tou poluonumou_sylvester)
	for(int i=0;i<d+1;i++){
		algorithmos(p_syl,table_mitrown,t1,t2,t3,t4,d,diastasi,i);
		prosthesi_3d_pinakon(poluonumo_mitrown,table_mitrown,d,diastasi); // prostheto to table_mitrown sto poluoonumo_mitrown

		for(int z=0;z<d+1;z++){ //kai meta ksanamidenizo to table_mitrown
			for(int j=0;j<diastasi;j++){
				for(int k=0;k<diastasi;k++){
					table_mitrown[z][j][k]=0;
				}
			}
		}
	}
	/////////////
	
	/*cout<<"TO KAINOURGIO POLUONUMO MITROWN"<<endl;
	for(int i=0;i<d+1;i++){
		for(int j=0;j<diastasi;j++){
			for(int k=0;k<diastasi;k++){
				cout<<poluonumo_mitrown[i][j][k]<<" ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}*/

	//diagrafi tou table_mitrown pou den to xreiazomaste pleon
	for(int i=0;i<d+1;i++){
		for(int j=0;j<diastasi;j++){
			delete []table_mitrown[i][j];
		}
		delete []table_mitrown[i];
	}
	delete []table_mitrown;

	//DINOUME AUTON TON TRISDIASTO PINAKA
	//STIN KLASSI POLUONUMO_SYLVESTER
	//GIA KATASKEUI KAINOURGIOU POLUONUMOU_SYLVESTER!!!!
	
	poluonumo_sylvester *new_p_syl;
	new_p_syl=new poluonumo_sylvester(poluonumo_mitrown,d,diastasi,p_syl->give_hidden());

	//Dimiourgisame to kainourgio poluonumo_sylvester opote tora o pinakas den mas xreiazetai
	for(int i=0;i<d+1;i++){
		for(int j=0;j<diastasi;j++){
			delete []poluonumo_mitrown[i][j];
		}
		delete []poluonumo_mitrown[i];
	}
	delete []poluonumo_mitrown;

	return new_p_syl;
	

		
}

void algorithmos(poluonumo_sylvester * p_syl,double ***table_mitrown,int t1,int t2,int t3,int t4,int d,int diastasi,int mitroo){ 
//ulopoiei ton algorithmo pou afora tis prakseis pou xreiazontai gia tin kataskeui tou kainourgiou poluonumou_sylvester
	
	int i,j,k;
	double **temp;
	
	
	table_mitrown[0]=p_syl->give_mitroo(table_mitrown[0],mitroo,diastasi); //stin proti thesi tou 3d-pinaka bazoume prepei na mpei to Mitroo pou tha kanoume douleia

	//pinakas termporary_mitrown//////////////////
	double ***temporary_mitrown;
	temporary_mitrown=new double**[d+1];
	for(int i=0;i<d+1;i++)
	{
		temporary_mitrown[i]=new double*[diastasi];
		for(int j=0;j<diastasi;j++)
		{
			temporary_mitrown[i][j]=new double[diastasi];
		}
	}
	//arxikopoioume me 0 ola ta kelia
	for(int i=0;i<d+1;i++){
		for(int j=0;j<diastasi;j++){
			for(int k=0;k<diastasi;k++){
				temporary_mitrown[i][j][k]=0;
			}
		}
	}
	//////////////////////////////////////////////////



	//tora apo edo kai pera prepei na arxisoume ton pollaplasiasmo tou pinaka me tous suntelestes

	for(i=0;i<mitroo;i++){
		for(j=0;j<d+1;j++){
			//pollaplasiasmos t2 me pinaka
			//to bazoume panta stin thesi tou pinaka pou pollaplasiasame
			pollaplasiasmos_arithmou_me_pinaka(temporary_mitrown,table_mitrown[j],t2,diastasi,j); //j einai i thesi tou megalou pinaka pou prepei na balloume
		}
		for(j=0;j<d+1;j++){
			//pollaplasiasmos t1 me pinaka
			//prepei na to prosthesoume me ton pinaka pou brisketai mia thesi meta
			//kai na to balloume ekei pera kai auto giati to t1 einai oros tou z (t1z+t2)
			if(j+1==d+1){
				continue;
			}
			pollaplasiasmos_kai_prosthesi_arithmou_me_pinaka(temporary_mitrown,table_mitrown[j],temporary_mitrown[j+1],t1,diastasi,j+1);
		}
		//antigrafo ta dedomena tou temporary sto table_mitrown kai meta sbino to temporary
		antigrafi_3d_pinakon(table_mitrown,temporary_mitrown,d,diastasi);
	}

	//arxikopoioume me 0 ola ta kelia tou temporary mitrown ksana
	for(int i=0;i<d+1;i++){
		for(int j=0;j<diastasi;j++){
			for(int k=0;k<diastasi;k++){
				temporary_mitrown[i][j][k]=0;
			}
		}
	}

	////////////////////////////////
	for(i=0;i<d-mitroo;i++){
		for(j=0;j<d+1;j++){
			//pollaplasiasmos t4 me pinaka
			//to bazoume panta stin thesi tou pinaka pou pollaplasiasame
			pollaplasiasmos_arithmou_me_pinaka(temporary_mitrown,table_mitrown[j],t4,diastasi,j); //j einai i thesi tou megalou pinaka pou prepei na balloume
		}
		for(j=0;j<d+1;j++){
			//pollaplasiasmos t3 me pinaka
			//prepei na to prosthesoume me ton pinaka pou brisketai mia thesi meta
			//kai na to balloume ekei pera kai auto giati to t3 einai oros tou z (t3z+t4)
			if(j+1==d+1){
				continue;
			}
			pollaplasiasmos_kai_prosthesi_arithmou_me_pinaka(temporary_mitrown,table_mitrown[j],temporary_mitrown[j+1],t3,diastasi,j+1);
		}
		antigrafi_3d_pinakon(table_mitrown,temporary_mitrown,d,diastasi);	
	}
	
	//diagrafi temporary_mitrown pou den xreiazomaste allo
	for(i=0;i<d+1;i++){
		for(j=0;j<diastasi;j++){
			delete []temporary_mitrown[i][j];
		}
		delete []temporary_mitrown[i];
	}
	delete []temporary_mitrown;

	
	/* //gia ektuposi einai auto edo////////////
	for(i=0;i<d+1;i++){
		for(j=0;j<diastasi;j++){
			for(k=0;k<diastasi;k++){
				cout<<table_mitrown[i][j][k]<<" ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}*/
	////////////////////////////////
}
	
	


void pollaplasiasmos_arithmou_me_pinaka(double ***temporary_mitrown,double ** table,double arithmos,int diastasi,int thesi){
	double **temp;
	int i,j,k;
	
	for(i=0;i<diastasi;i++){
		for(j=0;j<diastasi;j++){
			temporary_mitrown[thesi][i][j]=table[i][j]*arithmos;
		}
	}

}

void pollaplasiasmos_kai_prosthesi_arithmou_me_pinaka(double ***temporary_mitrown,double **table1,double** table2,double arithmos,int diastasi,int thesi){
	int i,j;
	double **temp;
	
	temp=new double *[diastasi];
	for(i=0;i<diastasi;i++){
		temp[i]=new double[diastasi];
	}

	for(i=0;i<diastasi;i++){
		for(j=0;j<diastasi;j++){
			temp[i][j]=arithmos*table1[i][j];
		}
	}
	
	for(i=0;i<diastasi;i++){
		for(j=0;j<diastasi;j++){
			temporary_mitrown[thesi][i][j]=temp[i][j]+table2[i][j];
		}
	}
	
	//delete ton temp pou den mas xreiazetai allo
	for(i=0;i<diastasi;i++){
			delete []temp[i];
	}
	delete []temp;
}
	



void antigrafi_3d_pinakon(double ***table_mitrown,double ***temporary,int d,int diastasi){
	int i,j,k;
	
	for(i=0;i<d+1;i++){
		for(j=0;j<diastasi;j++){
			for(k=0;k<diastasi;k++){
				table_mitrown[i][j][k]=temporary[i][j][k];
			}
		}
	}
}


void prosthesi_3d_pinakon(double ***poluonumo_mitrown,double *** table_mitrown,int d,int diastasi){
	int i,j,k;

	for(i=0;i<d+1;i++){
		for(j=0;j<diastasi;j++){
			for(k=0;k<diastasi;k++){
				poluonumo_mitrown[i][j][k]=poluonumo_mitrown[i][j][k]+table_mitrown[i][j][k];
			}
		}
	}
}
