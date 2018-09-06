//helping_functions.cpp

#include "headers/helping_functions.h"

//kanei parsing sto string (poluonumo apo ton xristi) dimiourgontas ena antikeimeno klassis poluonumo
//delimeter einai ta + kai - ,to string DEN prepei na periexei kena
poluonumo * create_poluonumo(string input){	
	
	
	poluonumo *f0;
	string token;
	size_t pos = 0;
	int power_x, power_y; //statheros_oros;
	double statheros_oros;
	term *some_term;
	bool prosimo = true; //true gia +, false gia -;

	f0 = new poluonumo();
	
	if(input[0]=='-'){
		prosimo=false;
		input.erase(0,1);
	}
	
	while(((pos=input.find_first_of("+-"))!=string::npos)){
		token=input.substr(0,pos);
		//cout<<"token:"<<token<<endl;
		parse_term(token,prosimo,&power_x,&power_y,&statheros_oros);
		some_term=new term(power_x,power_y,statheros_oros);
		f0->add_term(some_term);
		if(input[pos]=='-'){ //elegxei to prosimo tou term [pos+1] to eixa
			prosimo=false;
		}
		else{
			prosimo=true;
		}
		input.erase(0,pos+1);
		//cout<<"input:"<<input<<endl;
	}
	parse_term(input,prosimo,&power_x,&power_y,&statheros_oros);
	some_term=new term(power_x,power_y,statheros_oros);
	f0->add_term(some_term);
	return f0;	
	
}


//kanei parsing enan orou tou poluonumou,epistrefontas tin dunami tou x,tin dunami tou y, kai ton stathero oro
//auta pou epistrefei ta xrisimopoiei i sunartisi pou ftiaxnei to poluonumo gia na ftiaksei to mononumo (term)
//kai na to prosthesei sto poluonumo
void parse_term(string s, bool prosimo, int *x, int *y, double *stath) { 
	size_t pos = 0;
	string power_x;
	string power_y;
	int megethos_ektheti = 0;

	//eidiki periptosi to token na ksekinaei me -
	if (s[0] == '-') {
		prosimo = false;
		s.erase(0, 1);
	}
	////////////////////////////////////////////////
	//euresi power_x
	if ((pos = s.find("x")) != string::npos) {
		//cout<<pos<<endl;
		if (s[pos + 1] != '^') {
			power_x = "1";
		}
		else {
			//power_x=s.substr(pos+2,1);
			megethos_ektheti = 0;
			while (isdigit(s[pos + 2 + megethos_ektheti])) {
				megethos_ektheti++;
			}
			power_x = s.substr(pos + 2, megethos_ektheti);
		}
	}
	else {
		power_x = "0";
	}
	///////////////////////////////
	//euresi power_y
	if ((pos = s.find("y")) != string::npos) {
		//cout<<pos<<endl;
		if (s[pos + 1] != '^') {
			power_y = "1";
		}
		else {
			//power_y=s.substr(pos+2,1);
			megethos_ektheti = 0;
			while (isdigit(s[pos + 2 + megethos_ektheti])) {
				megethos_ektheti++;
			}
			power_y = s.substr(pos + 2, megethos_ektheti);
		}
	}
	else {
		power_y = "0";
	}
	//////////////////////////////
	//euresi statherou orou
	int megethos_statherou_orou = 0;
	string statheros_oros;
	//while (isdigit(s[megethos_statherou_orou])) {//|| s[megethos_statherou_orou] =='.'
	while(isdigit(s[megethos_statherou_orou]) || s[megethos_statherou_orou]=='.'){
		megethos_statherou_orou++;
	}
	if (megethos_statherou_orou == 0) {
		if(prosimo){//prosimo +   //kainourgia if
			statheros_oros="1";
		}
		else{ //prosimo -
			statheros_oros = "-1";
		}
		//statheros_oros="1"; //upirxe apla auto
	}
	else {
		if (prosimo) { //prosimo +
			statheros_oros = s.substr(0, megethos_statherou_orou);
		}
		else { //prosimo -
			statheros_oros = "-" + s.substr(0, megethos_statherou_orou);
		}
	}
	////////////////////////////////////
	//ektuposeis
	//cout<<"power_x:"<<power_x<<endl;
	//cout<<"power_y:"<<power_y<<endl;
	//cout<<"statheros_oros:"<<statheros_oros<<endl;

	*x = atoi(power_x.c_str());
	*y = atoi(power_y.c_str());
	*stath = atof(statheros_oros.c_str());  //atof
}

poluonumo * create_random_poluonumo(int bathmos) { //dimiourgei ena tuxaio poluonumo bathmou pou tou dinetai
	int power_x, power_y, statheros_oros;
	int arithmos_sunteleston = 1, suntelestes = 0;
	poluonumo *f0;
	term *some_term;

	f0 = new poluonumo();

	//arxikopoihsi randmom seed
	//srand(time(NULL));  //AUTO EDO TO EXO BALLEI STIN ARXI TIS MAIN

	//paragogi megistobathmiou orou
	power_x = rand() % (bathmos + 1);
	power_y = abs(bathmos - power_x);

	statheros_oros = rand() % 41 - 20;
	while (statheros_oros == 0) { //gia na min bgei o statheros_oros tou megistobathmiou orou 0
		statheros_oros = rand() % 41 - 20;
	}
	//cout<<"power_x:"<<power_x<<endl;
	//cout<<"power_y:"<<power_y<<endl;
	//cout<<"statheros_oros:"<<statheros_oros<<endl;
	some_term = new term(power_x, power_y, statheros_oros);
	f0->add_term(some_term);

	//tuxaia mononuma pou tha paraxthoune epipleon tou megistobathmiou
	suntelestes = rand() % 10; //generate 0-9
	//cout<<"tuxaioi suntelestes:"<<suntelestes<<endl;

	//paragogi tuxaion oron
	for (int i = 0; i < suntelestes; i++) {
		power_x = rand() % (bathmos + 1);
		if (power_x == bathmos) {
			power_y = 0;
		}
		else {
			power_y = rand() % (bathmos - power_x);
		}
		statheros_oros = rand() % 41 - 20;
		//cout<<"power_x:"<<power_x<<endl;
		//cout<<"power_y:"<<power_y<<endl;
		//cout<<"statheros_oros:"<<statheros_oros<<endl;
		if (!(f0->check_list_for_existance(power_x, power_y))) { //ean den uparxei to eidi to bazoume
			arithmos_sunteleston++;
			some_term = new term(power_x, power_y, statheros_oros); //dimiourgia term
			f0->add_term(some_term); //eisagogi tou sto poluonumo
		}
	}
	//cout<<"Arithmos sunteleston:"<<arithmos_sunteleston<<endl;
	return f0;
}



//palia sunartisi,parsarei me delimeter to keno
/*poluonumo * create_poluonumo(string input) {  //kanei parsing sto string (poluonumo apo ton xristi) dimiourgontas ena antikeimeno klassis poluonumo
	poluonumo *f0;
	string token;
	size_t pos = 0;
	int power_x, power_y, statheros_oros;
	term *some_term;
	bool prosimo = true; //true gia +, false gia -;

	f0 = new poluonumo();

	//if(input[0]=='-'){ //mou fenetai den xreiazetai auto giati elegxetai i periptosi
	//	prosimo=false;   //mesa stin parse_token
	//}

	while (((pos = input.find(" ")) != string::npos)) {
		token = input.substr(0, pos);
		//cout<<"token:"<<token<<endl;
		parse_term(token, prosimo, &power_x, &power_y, &statheros_oros);
		some_term = new term(power_x, power_y, statheros_oros);
		f0->add_term(some_term);
		if (input[pos + 1] == '-') { //elegxei to prosimo tou term
			prosimo = false;
		}
		else {
			prosimo = true;
		}
		input.erase(0, pos + 3);
	}
	return f0;
}*/

