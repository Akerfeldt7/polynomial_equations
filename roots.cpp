//roots.cpp

#include "headers/roots.h"


void routina_print(double *table,int plithos);
lista * koines_luseis(double *table,double *pinakas,int plithos_table,int plithos_pinaka);
lista * luseis_apo_to_ena(double *table,int plithos_table);



riza::riza(double x0,double y0,int m,string h,bool what){
	x=x0;
	y=y0;
	multiplicity=m;
	hidden=h;
	idiodianusma=what;
}

riza::~riza(){
	//cout<<"delete one riza"<<endl;
}

double riza::give_x(){
	return x;
}

double riza::give_y(){
	return y;
}

int riza::give_multiplicity(){
	return multiplicity;
}

void riza::add_multiplicity(){
	multiplicity++;
}

void riza::make_boolean_true(){
	idiodianusma=true;
}
	

void riza::print_riza(){
	if(hidden=="x"){
		if(multiplicity>1){
			cout<<"x="<<x<<" with multiplicity:"<<multiplicity<<endl;
		}
		else if(multiplicity==1 && idiodianusma==true){
			cout<<"x="<<x<<" "<<"y="<<y<<endl;
		}
	}
	else{
		if(multiplicity>1){
			cout<<"y="<<y<<" with multiplicity:"<<multiplicity<<endl;
		}
		else if(multiplicity==1 && idiodianusma==true){
			cout<<"x="<<x<<" "<<"y="<<y<<endl;
		}
	}
}

bool riza::give_boolean(){ //i boolean metabliti idiodianusma deixnei an to idiodianusma tha to laboume upopsin mas i oxi
	return idiodianusma;
}

double riza::give_idiotimi_with_multiplicity(){
	if(hidden=="x"){
		if(multiplicity>1){
			return x;
		}
	}
	else{
		if(multiplicity>1){
			return y;
		}
	}
}
	

/////////////////////////////////////////////////////////////////////////////////////////////


roots::roots(int p,string h){
	point=0;
	plithos_luseon=p;
	hidden=h;
	//all_rizes=NULL; //KAINOURGIO MEROS_3 TORAAAAAAAAAAAAAAAA
	table_roots=new riza*[plithos_luseon]; //dimiourgo pinakaki pou tha exei deiktes se rizes
	for(int i=0;i<plithos_luseon;i++){
		table_roots[i]=NULL;
	}
	
}

roots::roots(const roots &obj){ //copy constructor tis klassis roots //xrisimopoieitai gia tin apokrupsi ton apotelesmaton
//otan gurname ta apotelesmata apo tis 2 klasseis pou xreiasimopoiountai gia tin paragogi tous

	int i;
	double x0,y0;
	int m;
	bool what;
	
	riza *temp;
	hidden=obj.hidden;
	plithos_luseon=obj.plithos_luseon;
	point=obj.point;
	table_roots=new riza*[plithos_luseon];
	for(i=0;i<plithos_luseon;i++){
		table_roots[i]=NULL;
	}
	for(i=0;i<point;i++){
		x0=obj.table_roots[i]->give_x();
		y0=obj.table_roots[i]->give_y();
		m=obj.table_roots[i]->give_multiplicity();
		what=obj.table_roots[i]->give_boolean();
		temp=new riza(x0,y0,m,hidden,what);
		table_roots[i]=temp;
	}
}
		

roots::~roots(){ 
	for(int i=0;i<plithos_luseon;i++){
		if(table_roots[i]!=NULL){
			delete table_roots[i];
		}
	}
	delete []table_roots;
}

void roots::add_root(double x0,double y0,bool idiodianusma){ //bazei mia lusi sto pinakaki
	int elegxos_mul;
	if(point==plithos_luseon){
		cout<<"I cant put this root cause the limit is reached"<<endl;
	}
	else{
		//prin tin topothetisoume elegxoume tin pollaplotita tis
		elegxos_mul=existance_of_multiplicity(x0,y0);
		if( elegxos_mul!=-1 ){ //uparxei multiplicity stin riza stin thesi tou pinaka elegxos_mul
			table_roots[elegxos_mul]->add_multiplicity(); //opote auksanoume tin pollaplotita tis
			if(idiodianusma==true){ 
				table_roots[elegxos_mul]->make_boolean_true();
			}	
		}
		else{ //alios olokainourgia riza
			table_roots[point]=new riza(x0,y0,1,hidden,idiodianusma);
			point++;
		}
		//cout<<"I add riza "<<"x="<<x0<<" "<<"y="<<y0<<" with multiplicity:"<<m<<endl;
	}
}


void roots::print_roots(poluonumo *f1,poluonumo *f2){ //EKTUPNEI TIS RIZES kanontas sugxronos tin antikatastasi sta poluonuma
	one_var_companion * c1,*c2; //MEROS 3
	double * luseis_1, *luseis_2; //MEROS 3
	lista * lista_koines_luseis=NULL; //MEROS 3
	double lusi1=0,lusi2=0;
	double elegxos=0.0; //gia to 10^(-5)
	double multiple_idiotimi;
	poluonumo * new_f1, *new_f2;
	elegxos=1.0/(pow(10,5));
	cout<<endl<<"PLITHOS KOINON PRAGMATIKON RIZON:"<<sunoliko_plithos_soston_luseon()<<endl;
	for(int i=0;i<plithos_luseon;i++){
		if(table_roots[i]!=NULL){ //an o pinakas exei mesa tou ligoteres luseis epeidi den exei gemisei logo multiplicity
			if(table_roots[i]->give_multiplicity()==1 &&table_roots[i]->give_boolean()==true){
				//cout<<"oi rizes pou tha elegksoume einai oi:"<<endl;
				//cout<<"x="<<table_roots[i]->give_x()<<" y="<<table_roots[i]->give_y()<<endl;
				lusi1=f1->antikatastasi(table_roots[i]->give_x(),table_roots[i]->give_y());
				lusi1=f2->antikatastasi(table_roots[i]->give_x(),table_roots[i]->give_y());
				if(fabs(lusi1)<elegxos && fabs(lusi2)<elegxos){
					cout<<"----------------------------"<<endl;
					table_roots[i]->print_riza();
					cout<<"H antikatastasi ton rizon sto poluonumo 1 bgazei lusi1:"<<lusi1<<endl;
					cout<<"H antikatastasi ton rizon sto poluonumo 2 bgazei lusi2:"<<lusi2<<endl;
					cout<<"----------------------------"<<endl<<endl;
				}
				else{ //i riza den midenizei kai ta duo poluonuma opote tin apopruptoume
					cout<<"WRONG SOLUTION"<<endl;
				}
			}
			else if( (table_roots[i]->give_multiplicity()>1) && (table_roots[i]->give_boolean()==true) ){ //riza me pollaplotita
				cout<<"----------------------------"<<endl;
				table_roots[i]->print_riza();
				//KAINOURGIO MEROS 3
				multiple_idiotimi=table_roots[i]->give_idiotimi_with_multiplicity(); //edo pairnoume tin riza pou exei multiplicity 
				new_f1=new poluonumo(*f1); //kanoume duplicate to f1 gia na tou antikatastisoume tin timi
				new_f1->antikatastasi_one_var(multiple_idiotimi,hidden); //ftiaxnoume to kainourgio poluonumo antikathistontas tin riza me to multiplicity
				new_f2=new poluonumo(*f2); //kanoume duplicate to f2 gia na tou antikatastisoume tin timi
				new_f2->antikatastasi_one_var(multiple_idiotimi,hidden); //ftiaxnoume to kainourgio poluonumo antikathistontas tin riza me to multiplicity
				//cout<<new_f1->print_poluonumo()<<endl; //auto edo ektuponei xrisimopoiontas tin lista kai den einai enimeromeni meta tin antikatastasi
				//new_f1->print_array();
				//cout<<new_f2->print_poluonumo()<<endl; //auto edo ektuponei xrisimopoiontas tin lista kai den einai enimeromeni meta tin antikatastasi
				//new_f2->print_array();
				if(hidden=="x"){
					c1=new one_var_companion(new_f1,"y"); //tou dinoume to poluonumo me tin metabliti tou
					c2=new one_var_companion(new_f2,"y"); //tou dinoume to poluonumo me tin metabliti tou
					luseis_1=c1->give_luseis(); //pairnoume tis luseis gia to proto
					luseis_2=c2->give_luseis(); //pairnoume tis luseis gia to deutero
					//routina_print(luseis_1,c1->give_plithos_luseon());
					//routina_print(luseis_2,c2->give_plithos_luseon());
					if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) || (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
						//tote oi luseis tha einai apo to ena poluonumo mono kai to allo tha einai to mideniko poluonumo
						//opote tha ikanopoieitai apo oles tis luseis
						if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2!=NULL) ){
							//oi luseis einai apo to luseis_2
							lista_koines_luseis=luseis_apo_to_ena(luseis_2,c2->give_plithos_luseon());
						}
						else if( (luseis_2==NULL && c2->give_plithos_luseon()==-1) && (luseis_1!=NULL) ){
							//oi luseis einai apo to luseis_1
							lista_koines_luseis=luseis_apo_to_ena(luseis_1,c1->give_plithos_luseon());
						}
						else if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
							//einai kai ta duo midenika poluonuma opote exoun apeires luseis
							cout<<"DUO MIDENIKA POLUONUMA-->APEIRES LUSEIS"<<endl;
						}
						else{
							//to ena einai to mideniko poluonumo kai to allo den exei luseis opote den tha exoun kamia lusi
							cout<<"MIDENIKO+ALUTO--->DEN EXOUN KOINES LUSEIS"<<endl;
						}
					}
					else{
						lista_koines_luseis=koines_luseis(luseis_1,luseis_2,c1->give_plithos_luseon(),c2->give_plithos_luseon()); //briskoume tis koines luseis
					}
					
				}
				else{
					c1=new one_var_companion(new_f1,"x"); //tou dinoume to poluonumo me tin metabliti tou
					c2=new one_var_companion(new_f2,"x"); //tou dinoume to poluonumo me tin metabliti tou
					luseis_1=c1->give_luseis(); //pairnoume tis luseis gia to proto
					luseis_2=c2->give_luseis(); //pairnoume tis luseis gia to deutero
					//routina_print(luseis_1,c1->give_plithos_luseon());
					//routina_print(luseis_2,c2->give_plithos_luseon());
					if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) || (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
						//tote oi luseis tha einai apo to ena poluonumo mono kai to allo tha einai to mideniko poluonumo
						//opote tha ikanopoieitai apo oles tis luseis
						if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2!=NULL) ){
							//oi luseis einai apo to luseis_2
							lista_koines_luseis=luseis_apo_to_ena(luseis_2,c2->give_plithos_luseon());
						}
						else if( (luseis_2==NULL && c2->give_plithos_luseon()==-1) && (luseis_1!=NULL) ){
							//oi luseis einai apo to luseis_1
							lista_koines_luseis=luseis_apo_to_ena(luseis_1,c1->give_plithos_luseon());
						}
						else if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
							//einai kai ta duo midenika poluonuma opote exoun apeires luseis
							cout<<"DUO MIDENIKA POLUONUMA-->APEIRES LUSEIS"<<endl;
						}
						else{
							//to ena einai to mideniko poluonumo kai to allo den exei luseis opote den tha exoun kamia lusi
							cout<<"MIDENIKO+ALUTO--->DEN EXOUN KOINES LUSEIS"<<endl;
						}
						
					}
					else{
						lista_koines_luseis=koines_luseis(luseis_1,luseis_2,c1->give_plithos_luseon(),c2->give_plithos_luseon()); //briskoume tis koines luseis
					}
				}
				//exoume tin lista me tis koines luseis!!! tora theloume na tis bazoume kapos
				if(lista_koines_luseis!=NULL){
					if(hidden=="x"){
						cout<<"y:";
					}
					else{
						cout<<"x:";
					}
					lista_koines_luseis->print_lista();
				}

				delete lista_koines_luseis;
				delete c1;
				delete c2;
				delete new_f1;
				delete new_f2;
				cout<<"----------------------------"<<endl<<endl;
			}
		}
	}
	/*
	cout<<"DOKIMASTIKOOOOOOOOOOOOOOOO"<<endl;
	lista * some_lista;
	double pinakas_1[]={0,2,0,1,4,5,1};
	double pinakas_2[]={5,0,4,1,16};
	some_lista=koines_luseis(pinakas_1,pinakas_2,7,5);
	some_lista->print_lista();
	*/
}

int roots::sunoliko_plithos_soston_luseon(){ //to teliko sunoliko plithos ton rizon
	int multiple;
	int arithmos=0;
	for(int i=0;i<point;i++){
		multiple=table_roots[i]->give_multiplicity();
		if(multiple==1 &&table_roots[i]->give_boolean()==true){
			arithmos++;
		}
		else if(multiple>1 &&table_roots[i]->give_boolean()==true){
			arithmos=arithmos+multiple;
		}
	}
	return arithmos;
}		






int roots::existance_of_multiplicity(double x0,double y0){
	int i;
	double a;
	double epsilon=0.0001;
	if(hidden=="x"){
		for(i=0;i<point;i++){
			a=table_roots[i]->give_x();
			if(fabs(a-x0)<epsilon){
				return i;
			}
		}
	}
	else{
		for(i=0;i<point;i++){
			a=table_roots[i]->give_y();
			if(fabs(a-y0)<epsilon){
				return i;
			}
		}
	}
	return -1;
}


void roots::print_change_roots(poluonumo *f1,poluonumo *f2,int t1,int t2,int t3,int t4){ //ektuponei tis rizes gia ta poluonuma meta tin allazi metablitis apo y se z
//opou y=(t1z+t2)/(t3z+t4) (otan leme y ennooume tin ekastatote metabliti tou poluonumou sylvester) kai anagei tis rizes z stis y kai kanei tin antikastasi sta poluonuma
	double lusi1=0,lusi2=0;
	double elegxos=0.0; //gia to 10^(-5)
	double z;
	elegxos=1.0/(pow(10,5));
	cout<<endl<<"PLITHOS KOINON PRAGMATIKON RIZON:"<<sunoliko_plithos_soston_luseon()<<endl;
	for(int i=0;i<plithos_luseon;i++){
		if(table_roots[i]!=NULL){ //an o pinakas exei mesa tou ligoteres luseis epeidi den exei gemisei logo multiplicity
			if(table_roots[i]->give_multiplicity()==1 &&table_roots[i]->give_boolean()==true){
				if(hidden=="x"){
					if( fabs(t3*table_roots[i]->give_x()+t4)<0.0001){
						cout<<"----------------------------"<<endl;
						cout<<"O paranomastis (t3*z+t4) einai polu konta sto 0 gi auto aporiptoume tin lusi"<<endl;
						cout<<"----------------------------"<<endl;
						continue;
					}
					z=(t1*table_roots[i]->give_x()+t2)/(t3*table_roots[i]->give_x()+t4);
					//cout<<"oi rizes pou tha elegksoume einai oi:"<<endl;
					//cout<<"z="<<z<<" y="<<table_roots[i]->give_y()<<endl;
					lusi1=f1->antikatastasi(z,table_roots[i]->give_y());
					lusi1=f2->antikatastasi(z,table_roots[i]->give_y());
				}
				else{ //hidden=="y";
					if( fabs(t3*table_roots[i]->give_y()+t4)<0.0001){
						cout<<"----------------------------"<<endl;
						cout<<"O paranomastis (t3*z+t4) einai polu konta sto 0 gi auto aporiptoume tin lusi"<<endl;
						cout<<"----------------------------"<<endl;
						continue;
					}
					z=(t1*table_roots[i]->give_y()+t2)/(t3*table_roots[i]->give_y()+t4);
					//cout<<"oi rizes pou tha elegksoume einai oi:"<<endl;
					//cout<<"x="<<table_roots[i]->give_x()<<" z="<<z<<endl;
					lusi1=f1->antikatastasi(table_roots[i]->give_x(),z);
					lusi1=f2->antikatastasi(table_roots[i]->give_x(),z);
				}
				if(fabs(lusi1)<elegxos && fabs(lusi2)<elegxos){
					cout<<"----------------------------"<<endl;
					table_roots[i]->print_riza();
					cout<<"H antikatastasi ton rizon sto poluonumo 1 bgazei lusi1:"<<lusi1<<endl;
					cout<<"H antikatastasi ton rizon sto poluonumo 2 bgazei lusi2:"<<lusi2<<endl;
					cout<<"----------------------------"<<endl<<endl;
				}
				else{
					cout<<"WRONG SOLUTION"<<endl;
				}
			}
			else if( (table_roots[i]->give_multiplicity()>1) && (table_roots[i]->give_boolean()==true) ){
				cout<<"----------------------------"<<endl;
				table_roots[i]->print_riza();
				cout<<"opou i riza anagetai stin hidden=(t1*tade+t2)/(t3*tade+t4)"<<endl;
				cout<<"----------------------------"<<endl<<endl;
			}
		}
	}
}


list_of_roots * roots::fill_the_list_of_roots(poluonumo *f1,poluonumo *f2){ //EKTUPNEI TIS RIZES kanontas sugxronos tin antikatastasi sta poluonuma
	one_var_companion * c1,*c2; //MEROS 3
	double * luseis_1, *luseis_2; //MEROS 3
	lista * lista_koines_luseis=NULL; //MEROS 3
	double lusi1=0,lusi2=0;
	double elegxos=0.0; //gia to 10^(-5)
	double multiple_idiotimi;
	poluonumo * new_f1, *new_f2;
	elegxos=1.0/(pow(10,5));
	list_of_roots *all_rizes=new list_of_roots();// KAINOURGIO MEROS 3 TORAAAAAAAA
	//cout<<endl<<"PLITHOS KOINON PRAGMATIKON RIZON:"<<sunoliko_plithos_soston_luseon()<<endl;
	for(int i=0;i<plithos_luseon;i++){
		if(table_roots[i]!=NULL){ //an o pinakas exei mesa tou ligoteres luseis epeidi den exei gemisei logo multiplicity
			if(table_roots[i]->give_multiplicity()==1 &&table_roots[i]->give_boolean()==true){
				//cout<<"oi rizes pou tha elegksoume einai oi:"<<endl;
				//cout<<"x="<<table_roots[i]->give_x()<<" y="<<table_roots[i]->give_y()<<endl;
				lusi1=f1->antikatastasi(table_roots[i]->give_x(),table_roots[i]->give_y());
				lusi1=f2->antikatastasi(table_roots[i]->give_x(),table_roots[i]->give_y());
				if(fabs(lusi1)<elegxos && fabs(lusi2)<elegxos){
					cout<<"----------------------------"<<endl;
					//table_roots[i]->print_riza();
					all_rizes->add_to_lista(table_roots[i]->give_x(),table_roots[i]->give_y());
					//cout<<"H antikatastasi ton rizon sto poluonumo 1 bgazei lusi1:"<<lusi1<<endl;
					//cout<<"H antikatastasi ton rizon sto poluonumo 2 bgazei lusi2:"<<lusi2<<endl;
					//cout<<"----------------------------"<<endl<<endl;
				}
				else{ //i riza den midenizei kai ta duo poluonuma opote tin apopruptoume
					//cout<<"WRONG SOLUTION"<<endl;
				}
			}
			else if( (table_roots[i]->give_multiplicity()>1) && (table_roots[i]->give_boolean()==true) ){ //riza me pollaplotita
				cout<<"----------------------------"<<endl;
				//table_roots[i]->print_riza();
				//KAINOURGIO MEROS 3
				multiple_idiotimi=table_roots[i]->give_idiotimi_with_multiplicity(); //edo pairnoume tin riza pou exei multiplicity 
				new_f1=new poluonumo(*f1); //kanoume duplicate to f1 gia na tou antikatastisoume tin timi
				new_f1->antikatastasi_one_var(multiple_idiotimi,hidden); //ftiaxnoume to kainourgio poluonumo antikathistontas tin riza me to multiplicity
				new_f2=new poluonumo(*f2); //kanoume duplicate to f2 gia na tou antikatastisoume tin timi
				new_f2->antikatastasi_one_var(multiple_idiotimi,hidden); //ftiaxnoume to kainourgio poluonumo antikathistontas tin riza me to multiplicity
				//cout<<new_f1->print_poluonumo()<<endl; //auto edo ektuponei xrisimopoiontas tin lista kai den einai enimeromeni meta tin antikatastasi
				//new_f1->print_array();
				//cout<<new_f2->print_poluonumo()<<endl; //auto edo ektuponei xrisimopoiontas tin lista kai den einai enimeromeni meta tin antikatastasi
				//new_f2->print_array();
				if(hidden=="x"){
					c1=new one_var_companion(new_f1,"y"); //tou dinoume to poluonumo me tin metabliti tou
					c2=new one_var_companion(new_f2,"y"); //tou dinoume to poluonumo me tin metabliti tou
					luseis_1=c1->give_luseis(); //pairnoume tis luseis gia to proto
					luseis_2=c2->give_luseis(); //pairnoume tis luseis gia to deutero
					//routina_print(luseis_1,c1->give_plithos_luseon());
					//routina_print(luseis_2,c2->give_plithos_luseon());
					if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) || (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
						//tote oi luseis tha einai apo to ena poluonumo mono kai to allo tha einai to mideniko poluonumo
						//opote tha ikanopoieitai apo oles tis luseis
						if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2!=NULL) ){
							//oi luseis einai apo to luseis_2
							lista_koines_luseis=luseis_apo_to_ena(luseis_2,c2->give_plithos_luseon());
						}
						else if( (luseis_2==NULL && c2->give_plithos_luseon()==-1) && (luseis_1!=NULL) ){
							//oi luseis einai apo to luseis_1
							lista_koines_luseis=luseis_apo_to_ena(luseis_1,c1->give_plithos_luseon());
						}
						else if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
							//einai kai ta duo midenika poluonuma opote exoun apeires luseis
							//cout<<"DUO MIDENIKA POLUONUMA-->APEIRES LUSEIS"<<endl;
						}
						else{
							//to ena einai to mideniko poluonumo kai to allo den exei luseis opote den tha exoun kamia lusi
							//cout<<"MIDENIKO+ALUTO--->DEN EXOUN KOINES LUSEIS"<<endl;
						}
					}
					else{
						lista_koines_luseis=koines_luseis(luseis_1,luseis_2,c1->give_plithos_luseon(),c2->give_plithos_luseon()); //briskoume tis koines luseis
					}
					
				}
				else{
					c1=new one_var_companion(new_f1,"x"); //tou dinoume to poluonumo me tin metabliti tou
					c2=new one_var_companion(new_f2,"x"); //tou dinoume to poluonumo me tin metabliti tou
					luseis_1=c1->give_luseis(); //pairnoume tis luseis gia to proto
					luseis_2=c2->give_luseis(); //pairnoume tis luseis gia to deutero
					//routina_print(luseis_1,c1->give_plithos_luseon());
					//routina_print(luseis_2,c2->give_plithos_luseon());
					if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) || (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
						//tote oi luseis tha einai apo to ena poluonumo mono kai to allo tha einai to mideniko poluonumo
						//opote tha ikanopoieitai apo oles tis luseis
						if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2!=NULL) ){
							//oi luseis einai apo to luseis_2
							lista_koines_luseis=luseis_apo_to_ena(luseis_2,c2->give_plithos_luseon());
						}
						else if( (luseis_2==NULL && c2->give_plithos_luseon()==-1) && (luseis_1!=NULL) ){
							//oi luseis einai apo to luseis_1
							lista_koines_luseis=luseis_apo_to_ena(luseis_1,c1->give_plithos_luseon());
						}
						else if( (luseis_1==NULL && c1->give_plithos_luseon()==-1) && (luseis_2==NULL && c2->give_plithos_luseon()==-1) ){
							//einai kai ta duo midenika poluonuma opote exoun apeires luseis
							//cout<<"DUO MIDENIKA POLUONUMA-->APEIRES LUSEIS"<<endl;
						}
						else{
							//to ena einai to mideniko poluonumo kai to allo den exei luseis opote den tha exoun kamia lusi
							//cout<<"MIDENIKO+ALUTO--->DEN EXOUN KOINES LUSEIS"<<endl;
						}
						
					}
					else{
						lista_koines_luseis=koines_luseis(luseis_1,luseis_2,c1->give_plithos_luseon(),c2->give_plithos_luseon()); //briskoume tis koines luseis
					}
				}
				//exoume tin lista me tis koines luseis!!! tora theloume na tis bazoume kapos
				if(lista_koines_luseis!=NULL){
					if(hidden=="x"){
						lista_koines_luseis->fill(all_rizes,table_roots[i]->give_x(),hidden);
						//cout<<"y:";
					}
					else{
						lista_koines_luseis->fill(all_rizes,table_roots[i]->give_y(),hidden);
						//cout<<"x:";
					}
					//lista_koines_luseis->print_lista();
				}

				delete lista_koines_luseis;
				delete c1;
				delete c2;
				delete new_f1;
				delete new_f2;
				cout<<"----------------------------"<<endl<<endl;
			}
		}
	}
	
	//cout<<"DOKIMASTIKOOOOOOOOOOOOOOOO"<<endl;
	/* //AUTO EDO DEN XREIAZETAI
	lista * some_lista;
	double pinakas_1[]={0,2,0,1,4,5,1};
	double pinakas_2[]={5,0,4,1,16};
	some_lista=koines_luseis(pinakas_1,pinakas_2,7,5);
	some_lista->print_lista();
	*/
	//AUTO EDO EINAI GIA TIN EKTUPOSI TON TELIKON RIZON
	/*for(int i=0;i<all_rizes->give_plithos();i++){
		cout<<"x:"<<all_rizes->give_x(i+1)<<" ";
		cout<<"y:"<<all_rizes->give_y(i+1);
		cout<<endl;
	}*/

	return all_rizes;
		
}


////////////////////////////////////////////////
lista::lista(){
	start=NULL;
	last=NULL;
	plithos=0;
	//cout<<"dimiourgisa mia lista"<<endl;
}

lista::~lista(){
	kombos *current;
	kombos *for_delete;
	current=start;
	while(current!=NULL){
		for_delete=current;
		current=current->next;
		delete for_delete;
	}
}

void lista::add_to_lista(double some){
	if(!existance(some)){
		kombos *n;
		n=new kombos;
		n->timi=some;
		n->next=NULL;	
		if(start==NULL){
			start=n;
			last=n;
		}
		else{
			last->next=n;
			last=n;
		}
		plithos++;
	}
	else{
		//cout<<"to exo ksanaballei"<<endl;
	}
}

void lista::print_lista(){
	kombos *current;
	current=start;
	cout<<"[";
	if(current==NULL){
		cout<<"Den exoun koini lusi";
	}
	while(current!=NULL){
		cout<<current->timi;
		current=current->next;
		if(current!=NULL){
			cout<<",";
		}
	}
	cout<<"]"<<endl;
}

bool lista::existance(double some){
	kombos *current;
	current=start;
	while(current!=NULL){
		if(current->timi==some){
			return true;
		}
		current=current->next;
	}
	return false;
}

int lista::give_plithos(){
	return plithos;
}

void lista::fill(list_of_roots * all_rizes,double some_timi,string hidden){ //KAINOURGIOOOO MEROS_3 TORAAAAAAAA
	kombos *current;
	current=start;
	if(current==NULL){
		//cout<<"den exoun koini lusi"<<endl;
	}
	while(current!=NULL){
		if(hidden=="x"){
			all_rizes->add_to_lista(some_timi,current->timi);	
		}
		else{
			all_rizes->add_to_lista(current->timi,some_timi);
		}
		current=current->next;
	}	
}
	





/////////////////////////////



void routina_print(double *table,int plithos){
	int i;
	for(i=0;i<plithos;i++){ 
		cout<<table[i]<<endl;
	}
}

lista * koines_luseis(double *table,double *pinakas,int plithos_table,int plithos_pinaka){
	lista * some;
	int i,j;
	double diafora;
	double elegxos=0.0;
	elegxos=1.0/(pow(10,5));
	some=new lista();
	for(i=0;i<plithos_table;i++){
		for(j=0;j<plithos_pinaka;j++){
			diafora=table[i]-pinakas[j];
			if(fabs(diafora)<elegxos){ 
				//koino stoixeio
				//balto kapou
				some->add_to_lista(table[i]);
				break; //pame sto epomeno
			}
		}
	}
	//cout<<"LISTA"<<endl;
	//some->print_lista();
	return some;
}

lista * luseis_apo_to_ena(double *table,int plithos_table){
	int i;
	lista * some;
	some=new lista();
	for(i=0;i<plithos_table;i++){
		some->add_to_lista(table[i]);
	}
	return some;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//KLASSI LIST_OF_ROOTS
list_of_roots::list_of_roots(){
	start=NULL;
	last=NULL;
	plithos=0;
}

list_of_roots::~list_of_roots(){
	kombos *current;
	kombos *for_delete;
	current=start;
	while(current!=NULL){
		for_delete=current;
		current=current->next;
		delete for_delete;
	}
}

void list_of_roots::add_to_lista(double some_x,double some_y){
	kombos *n;
	n=new kombos;
	n->x=some_x;
	n->y=some_y;
	n->id=plithos+1;
	n->next=NULL;	
	if(start==NULL){
		start=n;
		last=n;
	}
	else{
		last->next=n;
		last=n;
	}
	plithos++;
}

double list_of_roots::give_x(int some_id){
	kombos *current;
	
	current=start;
	while(current!=NULL){
		if(current->id==some_id){
			return current->x;
		}
		current=current->next;
	}
}

double list_of_roots::give_y(int some_id){
	kombos *current;
	
	current=start;
	while(current!=NULL){
		if(current->id==some_id){
			return current->y;
		}
		current=current->next;
	}
}

int list_of_roots::give_plithos(){
	return plithos;
}




	

				
			












	
