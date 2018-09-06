//mitroo_sylvester.cpp
#include "headers/mitroo_sylvester.h"
#include <string>
#include <iomanip>

#include <sstream>
#include <cmath>

#define OUTPUT 20



mitroo_sylvester::mitroo_sylvester(poluonumo *ena, poluonumo *duo, string h) {
	int i, j;

	f0 = ena;
	f1 = duo;
	hidden = h;

	if(!f0->array_exist()){
		f0->create_array();
	}
	if(!f1->array_exist()){
		f1->create_array();
	}		

	if (hidden == "x") {
		diastasi = f0->give_max_y() + f1->give_max_y();
	}
	else {
		diastasi = f0->give_max_x() + f1->give_max_x();
	}

	mitroo = new poluonumo**[diastasi];
	for (i = 0; i < diastasi; i++) {
		mitroo[i] = new poluonumo*[diastasi];
	}
	for (i = 0; i < diastasi; i++) {
		for (j = 0; j < diastasi; j++) {
			mitroo[i][j] = NULL;
		}
	}
}

mitroo_sylvester::~mitroo_sylvester() {
	int i, j;
	
	//prepei na diagrapso mono ta poluonuma ta arxika prin ginei to shift
	//giati einai ta idia me auta pou ginontai meta to shift
	//opote diagrafo auta pou mpikan arxika
	for (i = 0; i < diastasi; i++) {
		if (mitroo[i][0] == NULL) { //prospernao opoia grammi tou pinaka arxizei me NULL giati exei ginei shift pio prin
			continue;
		}
		else {
			for (j = 0; j < diastasi; j++) {
				delete mitroo[i][j];
			}
		}
	}
	for (i = 0; i < diastasi; i++) {
		delete []mitroo[i];
	}
	delete []mitroo;
	

}



void mitroo_sylvester::create_mitroo_sylvester() {
	if (hidden == "x") { //kruboume tin x
		create_mitroo_sylvester_for_hidden_x();
	}
	else { //kruboume tin y
		create_mitroo_sylvester_for_hidden_y();
	}
}

void mitroo_sylvester::create_mitroo_sylvester_for_hidden_x() {
	poluonumo * matrix_poluonumo;
	term * some_term;
	int i, j;
	double suntelestis;
	int stiles, grammes, current_stili;

	current_stili = 0;
	stiles = f0->give_max_x();
	grammes = f0->give_max_y();
	//cout<<"stiles:"<<stiles<<" grammes:"<<grammes<<endl;
	for (i = grammes; i >= 0; i--) { //diatrexoume ton pinaka kata grammes
		matrix_poluonumo = new poluonumo();
		for (j = 0; j <= stiles; j++) {
			suntelestis = f0->give_suntelesti_from_table(i, j);
			//if (suntelestis == 0) {//fabs
			if(fabs(suntelestis)<0.0001){
				continue;
			}
			some_term = new term(j, 0, suntelestis);
			//cout<<"term pou bazo:";
			//some_term->print_term();
			//cout<<endl;
			matrix_poluonumo->add_term(some_term);
		}
		//tora theloume na to dosoume sto katallilo keli tou pinaka matrix
		//to bazoume stin granmi tou bathmou tou f0(opou batmos to max_y giati krupsame to x)
		//kai stili to i pou einai ousiastika i dunami to y pou briskomaste (periptosi krupsame to x)
		//cout<<"sto keli:["<<0<<","<<current_stili<<"] bazo sto mitroo to:";
		//matrix_poluonumo->print_poluonumo();
		//cout<<endl;
		if (matrix_poluonumo->empty()) {
			add_poluonumo_to_mitroo(NULL, 0, current_stili);
			delete matrix_poluonumo; //TO PROSTHESA 24-10
		}
		else {
			add_poluonumo_to_mitroo(matrix_poluonumo, 0, current_stili);
		}
		current_stili++;
	}
	//theloume na kanoume to shifting gia tis epomenes d1-1 grammes arxizontas apo tin grammi 0
	for (i = 0; i < f1->give_max_y() - 1; i++) {
		for (j = 0; j < diastasi; j++) {
			matrix_poluonumo = mitroo[i][j];
			if (j + 1 == diastasi) { //tote bgainei ektos orios
				continue;
			}
			else {
				add_poluonumo_to_mitroo(matrix_poluonumo, i + 1, j + 1);
			}
		}
	}

	//gia to deutero poluonumo
	current_stili = 0;
	stiles = f1->give_max_x();
	grammes = f1->give_max_y();
	//cout<<"stiles:"<<stiles<<" grammes:"<<grammes<<endl;
	for (i = grammes; i >= 0; i--) { //diatrexoume ton pinaka kata stili
		matrix_poluonumo = new poluonumo();
		for (j = 0; j <= stiles; j++) {
			suntelestis = f1->give_suntelesti_from_table(i, j);
			//if (suntelestis == 0) {//fabs!!!!!
			if(fabs(suntelestis)<0.0001){
				continue;
			}
			some_term = new term(j, 0, suntelestis);
			//cout<<"term pou bazo:";
			//some_term->print_term();
			//cout<<endl;
			matrix_poluonumo->add_term(some_term);
		}
		//tora theloume na to dosoume sto katallilo keli tou pinaka matrix
		//to bazoume stin granmi tou bathmou tou f0(opou batmos to max_y giati krupsame to x)
		//kai stili to i pou einai ousiastika i dunami to y pou briskomaste (periptosi krupsame to x)
		//cout<<"sto keli:["<<f1->give_max_y()<<","<<current_stili<<"] bazo sto mitroo to:";
		//matrix_poluonumo->print_poluonumo();
		//cout<<endl;
		if (matrix_poluonumo->empty()) {
			add_poluonumo_to_mitroo(NULL, f1->give_max_y(), current_stili); //to eisagoume tin d1 grammi
			delete matrix_poluonumo; //TO PROSTHESA 24-10
		}
		else {
			add_poluonumo_to_mitroo(matrix_poluonumo, f1->give_max_y(), current_stili); //to eisagoume tin d1 grammi
		}
		current_stili++;
	}
	//theloume na kanoume to shifting gia tis epomenes grammes arxizontas apo tin grammi d1
	for (i = f1->give_max_y(); i < diastasi - 1; i++) {
		for (j = 0; j < diastasi; j++) {
			matrix_poluonumo = mitroo[i][j];
			if (j + 1 == diastasi) { //tote bgainei ektos oriou
				continue;
			}
			else {
				add_poluonumo_to_mitroo(matrix_poluonumo, i + 1, j + 1);
			}
		}
	}
}

void mitroo_sylvester::create_mitroo_sylvester_for_hidden_y() {
	poluonumo * matrix_poluonumo;
	term * some_term;
	int i, j;//double o sintelestis
	double suntelestis;				
	int stiles, grammes, current_stili;

	current_stili = 0;
	stiles = f0->give_max_x();
	grammes = f0->give_max_y();
	//cout<<"stiles:"<<stiles<<" grammes:"<<grammes<<endl;
	for (i = stiles; i >= 0; i--) { //diatrexoume ton pinaka kata stili
		matrix_poluonumo = new poluonumo();
		for (j = 0; j <= grammes; j++) {
			suntelestis = f0->give_suntelesti_from_table(j, i);
			//if (suntelestis == 0) { 						//fabs
			if(fabs(suntelestis)<0.0001){
				continue;
			}
			some_term = new term(0, j, suntelestis);
			//cout<<"term pou bazo:";
			//some_term->print_term();
			//cout<<endl;
			matrix_poluonumo->add_term(some_term);
		}
		//tora theloume na to dosoume sto katallilo keli tou pinaka matrix
		//to bazoume stin granmi tou bathmou tou f0(opou batmos to max_x giati krupsame to y)
		//kai stili to i pou einai ousiastika i dunami to x pou briskomaste (periptosi krupsame to y)
		//cout<<"sto keli:["<<0<<","<<current_stili<<"] bazo sto mitroo to:";
		//matrix_poluonumo->print_poluonumo();
		//cout<<endl;
		if (matrix_poluonumo->empty()) {
			add_poluonumo_to_mitroo(NULL, 0, current_stili);
			delete matrix_poluonumo; //TO PROSTHESA 24-10
		}
		else {
			add_poluonumo_to_mitroo(matrix_poluonumo, 0, current_stili);
		}
		current_stili++;
	}
	//theloume na kanoume to shifting gia tis epomenes d1-1 grammes arxizontas apo tin grammi 0
	for (i = 0; i < f1->give_max_x() - 1; i++) {
		for (j = 0; j < diastasi; j++) {
			matrix_poluonumo = mitroo[i][j];
			if (j + 1 == diastasi) { //tote bgainei ektos orios
				continue;
			}
			else {
				add_poluonumo_to_mitroo(matrix_poluonumo, i + 1, j + 1);
			}
		}
	}


	//gia to deutero poluonumo
	current_stili = 0;
	stiles = f1->give_max_x();
	grammes = f1->give_max_y();
	//cout<<"stiles:"<<stiles<<" grammes:"<<grammes<<endl;
	for (i = stiles; i >= 0; i--) { //diatrexoume ton pinaka kata stili
		matrix_poluonumo = new poluonumo();
		for (j = 0; j <= grammes; j++) {
			suntelestis = f1->give_suntelesti_from_table(j, i);
			//if (suntelestis == 0) {									//fabs
			if(fabs(suntelestis)<0.0001){
				continue;
			}
			some_term = new term(0, j, suntelestis);
			//cout<<"term pou bazo:";
			//some_term->print_term();
			//cout<<endl;
			matrix_poluonumo->add_term(some_term);
		}
		//tora theloume na to dosoume sto katallilo keli tou pinaka matrix
		//to bazoume stin granmi tou bathmou tou f0(opou batmos to max_x giati krupsame to y)
		//kai stili to i pou einai ousiastika i dunami to x pou briskomaste (periptosi krupsame to y)
		//cout<<"sto keli:["<<f1->give_max_x()<<","<<current_stili<<"] bazo sto mitroo to:";
		//matrix_poluonumo->print_poluonumo();
		//cout<<endl;
		if (matrix_poluonumo->empty()) {
			add_poluonumo_to_mitroo(NULL, f1->give_max_x(), current_stili); //to eisagoume tin d1 grammi
			delete matrix_poluonumo; //TO PROSTHESA 24-10
		}
		else {
			add_poluonumo_to_mitroo(matrix_poluonumo, f1->give_max_x(), current_stili); //to eisagoume tin d1 grammi
		}
		current_stili++;
	}
	//theloume na kanoume to shifting gia tis epomenes grammes arxizontas apo tin grammi d1
	for (i = f1->give_max_x(); i < diastasi - 1; i++) {
		for (j = 0; j < diastasi; j++) {
			matrix_poluonumo = mitroo[i][j];
			if (j + 1 == diastasi) { //tote bgainei ektos oriou
				continue;
			}
			else {
				add_poluonumo_to_mitroo(matrix_poluonumo, i + 1, j + 1);
			}
		}
	}
}

void mitroo_sylvester::add_poluonumo_to_mitroo(poluonumo * p, int grammi, int stili) {
	mitroo[grammi][stili] = p;
}


void mitroo_sylvester::print_mitroo_sylvester() { //me pinaka omorfa
	stringstream buffer;
	string test;

	int i, j;
	cout << "Sustima eksisoseon:" << endl;
	cout << "f0:";
	cout << f0->print_poluonumo();
	cout << endl << "f1:";
	cout << f1->print_poluonumo();
	cout << endl << "hidden:" << hidden << endl << endl;
	cout << "MITROO SYLVESTER" << endl;
	cout << "Dimension:" << diastasi << "x" << diastasi << endl << endl;
	
	cout << endl;
	for (i = 0; i < diastasi; i++) {
		for (j = 0; j < diastasi; j++) {
			if (mitroo[i][j] != NULL) {
				//cout << "sto keli:[" << i << "," << j << "]:";
				//cout<<setw(OUTPUT);
				cout << setw(OUTPUT) <<  mitroo[i][j]->print_poluonumo();
				//cout << setw(OUTPUT) << buffer.str() << " |";
			}
			else {
				cout << setw(OUTPUT) << "0";
				//cout << "sto keli:[" << i << "," << j << "]:0" << endl << endl;
			}

		}
		cout << endl;
		
	}
	cout << "////////////////////////////////////////////////" << endl;

} 

void mitroo_sylvester::print_simple_mitroo_sylvester() {  //me apla kelia (px keli[2,3]->3*y^2)
	stringstream buffer;
	string test;

	int i, j;
	cout << "Sustima eksisoseon:" << endl;
	cout << "f0:";
	cout << f0->print_poluonumo();
	cout << endl << "f1:";
	cout << f1->print_poluonumo();
	cout << endl << "hidden:" << hidden << endl << endl;
	cout << "MITROO SYLVESTER" << endl;
	cout << "Dimension:" << diastasi << "x" << diastasi << endl << endl;
	
	cout << endl;
	for (i = 0; i < diastasi; i++) {
		for (j = 0; j < diastasi; j++) {
			if (mitroo[i][j] != NULL) {
				cout << "sto keli:[" << i << "," << j << "]:";
				cout<<mitroo[i][j]->print_poluonumo();
				cout<<endl;
			}
			else{
				cout << "sto keli:[" << i << "," << j << "]:0" << endl << endl;
			}
		}
	}
}

int mitroo_sylvester::give_diastasi(){
	return diastasi;
}

string mitroo_sylvester::give_hidden(){
	return hidden;
}

poluonumo * mitroo_sylvester::give_poluonumo(int grammi,int stili){ //den tin exoume xrisimopoieisei kapou
//TIN XRISIMOPOIOUME GIA APOKRUPSI
	poluonumo *duplicate;
	if(mitroo[grammi][stili]==NULL){
		return NULL;
	}
	else{
		duplicate=new poluonumo(*mitroo[grammi][stili]);
		return duplicate;
	}
}





