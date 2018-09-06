#include "headers/poluonumo.h"
#include <iomanip>
#include <sstream>
#include <cmath>

//#define OUTPUT 15


term::term(int x, int y, double n) {
	power_x = x;
	power_y = y;
	number = n;
	bathmos = power_x + power_y;
}

term::~term() {
	//cout<<"destroying a term"<<endl;
}

/*
void term::print_term() {
	stringstream buffer;

	buffer << "+(" << number << "*" << "x^" << power_x << "*" << "y^" << power_y << ")";
	cout << setw(OUTPUT)<<buffer.str();
}
*/

string  term::print_term() {//sigrisi number na gini me fabs
	stringstream buffer;

	buffer << "+(";
	if (number == 1) {
		if (power_x == 0 && power_y == 0) {
			buffer << number << ")";
		}
		else if (power_x == 0 && power_y != 0) {
			if (power_y == 1) {
				buffer << "y)";
			}
			else {
				buffer << "y^" << power_y << ")";
			}
		}
		else if (power_x != 0 && power_y == 0) {
			if (power_x == 1) {
				buffer << "x)";
			}
			else {
				buffer << "x^" << power_x << ")";
			}
		}
		else {
			if (power_x == 1 && power_y == 1) {
				buffer << "x*y)";
			}
			else if (power_x == 1 && power_y != 1) {
				buffer << "x*y^" << power_y << ")";
			}
			else if (power_x != 1 && power_y == 1) {
				buffer << "x^" << power_x << "*y)";
			}
			else {
				buffer << "x^" << power_x << "*" << "y^" << power_y << ")";
			}
		}
	}
	else if (number != 1) {
		if (power_x == 0 && power_y == 0) {
			buffer << number << ")";
		}
		else if (power_x == 0 && power_y != 0) {
			if (power_y == 1) {
				buffer << number << "*" << "y)";
			}
			else {
				buffer << number << "*" << "y^" << power_y << ")";
			}
		}
		else if (power_x != 0 && power_y == 0) {
			if (power_x == 1) {
				buffer << number << "*" << "x)";
			}
			else {
				buffer << number << "*" << "x^" << power_x << ")";
			}
		}
		else {
			if (power_x == 1 && power_y == 1) {
				buffer << number << "*" << "x*y)";
			}
			else if (power_x == 1 && power_y != 1) {
				buffer << number << "*" << "x*y^" << power_y << ")";
			}
			else if (power_x != 1 && power_y == 1) {
				buffer << number << "*" << "x^" << power_x << "*y)";
			}
			else {
				buffer << number << "*" << "x^" << power_x << "*" << "y^" << power_y << ")";
			}
		}
	}
	//cout << buffer.str();
	return buffer.str();
}

int term::give_bathmos_term() {
	return bathmos;
}

int term::give_power_x() {
	return power_x;
}

int term::give_power_y() {
	return power_y;
}

double term::give_number() {//double
	return number;
}
///////////////////////////////////////////////////////////////////////////////
poluonumo::poluonumo() {
	head = NULL;
	array = NULL;
	bathmos = 0;
	max_x = 0;
	max_y = 0;
	start=NULL;
	current=NULL;
	max_one_var=0; //gia to trito meros meta tin antikatastasi kapoias metablitis xrisimopoieitai auti
}

poluonumo::~poluonumo() {
	node *n;
	int i;
	head = start;
	while (head != NULL) {
		n = head->next;
		delete head->held_term;
		delete head;
		head = n;
	}
	if (array != NULL) {
		for (i = 0; i < max_y + 1; i++) {
			delete []array[i];
		}
		delete []array;
	}
	//cout<<"destroed ;)"<<endl;

}

poluonumo::poluonumo(const poluonumo &obj){
	node *n; 
	node *some; 
	node *born;
 
	bathmos=obj.bathmos; 
	max_x=obj.max_x; 
	max_y=obj.max_y;
 	head=NULL; 
	start=NULL; 
	current=NULL; 
	array=NULL;
	max_one_var=0; //gia to trito meros meta tin antikatastasi kapoias metablitis xrisimopoieitai auti
 
	some=obj.start; 
	while(some!=NULL){ 
		n=some->next; 
		born=new node; 
		born->held_term=new term(*(some->held_term)); 
		born->next=NULL; 
		if(head==NULL){ 
			start=born; 
			current=born; 
			head=born;
 		} 
		else{ 
			head->next=born; 
			head=born; 
		} 
		some = n; 
	}
	 
	if(obj.array!=NULL){ 
		this->create_array(); 
	} 
}


void poluonumo::add_term(term *some_term) { //eisagogi orou stin lista poluonumou
	node *n = new node;
	if (max_x < some_term->give_power_x()) { //krataei to megisto power_x
		max_x = some_term->give_power_x();
	}
	if (max_y < some_term->give_power_y()) { //krataei to megisto power_y
		max_y = some_term->give_power_y();
	}
	if (bathmos < some_term->give_bathmos_term()) { //sugkrinei ton bathmo ton terms
		bathmos = some_term->give_bathmos_term(); //gia tin euresi tou bathmo tou poluonumou
	}
	n->held_term = some_term;
	n->next = NULL;
	if (head == NULL) {
		start = n;
		current = n; 
		head = n;
	}
	else {
		head->next = n;
		head = n;
	}

}

/*dimiourgei pinaka poluonumou apo tin lista poluonumou
gia pukni anaparastasi tou poluonumou*/
void poluonumo::create_array() {
	int i, j, grammi, stili;
	node *n;
	node *some;
	//desmeusi kai arxikopoihsi disdiastatou pinaka
	array = new double*[max_y + 1]; //grammes pinaka 				ME DOUBLE
	for (i = 0; i < max_y + 1; i++) {
		array[i] = new double[max_x + 1]; //stiles pinaka         ME DOUBLE
	}
	for (i = 0; i < max_y + 1; i++) {
		for (j = 0; j < max_x + 1; j++) {
			array[i][j] = 0;
		}
	}
	///////////////////////////////
	//eisagogi stoixeion tou apo tin lista poluonumou ston pinaka
	some = start;
	while (some != NULL) {
		n = some->next;
		grammi = some->held_term->give_power_y();
		stili = some->held_term->give_power_x();
		array[grammi][stili] = some->held_term->give_number();
		some = n;
	}
}


string  poluonumo::print_poluonumo() { //ektuponei to poluonumo me kanoniki morfi
	node *n;
	node *some;
	some = start;

	stringstream buffer;

	while (some != NULL) {
		n = some->next;
		buffer << some->held_term->print_term();
		some = n;
	}
	return buffer.str();
	//cout << endl;
	//cout<<endl<<"with bathmo:"<<bathmos<<" max_x:"<<max_x<<" max_y:"<<max_y<<endl;
}



bool poluonumo::check_array_for_existance(int x, int y) { //elegxei an ena stoixeio uparxei eidi ston pinaka
	if (array[x][y] != 0) {
		return true; //uparxei eidi stoixeio
	}
	else {
		return false; //den uparxei stoixeio
	}
}

bool poluonumo::check_list_for_existance(int x, int y) { //elegxei an ena stoixeio uparxei stin lista
	node *n;
	node *some;
	some = start;
	int test = 0;
	while (some != NULL) {
		n = some->next;
		if (some->held_term->give_power_x() == x && some->held_term->give_power_y() == y) {
			//cout<<"FOUND SAME!!"<<endl;
			return true;
		}
		some = n;
	}
	return false;
}

void poluonumo::print_array() { //ektuponei ton pinaka poluonumou
	int i, j;
	if(array==NULL){
		cout<<"O pinakas den exei dimiourgithei"<<endl;
	}
	else{
		for (i = 0; i < max_y + 1; i++) {
			for (j = 0; j < max_x + 1; j++) {
				cout << array[i][j] << " ";
			}
			cout << endl;
		}
		cout<<endl;
	}
}

int poluonumo::give_max_x() {
	return max_x;
}

int poluonumo::give_max_y() {
	return max_y;
}

term * poluonumo::give_term() { //dinei term tou poluonumou me tin seira (mou fenetai den to xrisimopoioume kapou)
//prin xrisimopoieithei auti i sunartisi, prepei na xrisimopoihthei i reset_current_term 
//gia na arxizei apo tin seira i lista
	term * data;
	if (current == NULL) {
		return NULL;
	}
	data = current->held_term;
	current = current->next;
	return data;
}

void poluonumo::reset_current_term() { //bazoume ton deikti current na deixnei stin arxi tis listas
	current = start;
}

double poluonumo::give_suntelesti_from_table(int grammi, int stili) {//double
	return array[grammi][stili];
}

bool poluonumo::empty() { //elegxei an to poluonumo einai adeio
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

int poluonumo::give_bathmos_poluonumo()
{
	return bathmos;
}

bool poluonumo::array_exist(){ //elegxei an exei dimiourgithei array gia to poluonumo
	if(array==NULL){
		return false; //den exei dimiourgithei
	}
	else{
		return true; //exei dimiourgithei
	}
}



double poluonumo::antikatastasi(double x0,double y0){ //antikathistoume ta x kai ta y tou poluonumou me to (x0,y0)
	int i, j,grammi,stili;
	double lusi;
	node *n;
	node *some;
	
	if(array==NULL){ //an den exei dimiourgithei pinakaki poluonumou,dimiourgise to
		create_array();
	}	
	
	lusi=0;
	some = start;
	while (some != NULL) {
		n = some->next;
		grammi = some->held_term->give_power_y();
		stili = some->held_term->give_power_x();
		lusi=lusi+array[grammi][stili]*(pow(x0,(double)stili))*(pow(y0,(double)grammi)); //edo me to pow den ksero mipos se kapoia periptosi petaei sfalma
		some = n;
	}
	return lusi;	

}


//MEROS 3////////////////////////////////

//META APO AUTIN EDO TIN METATROPI DEN SUMBADIZOUN OI TIMES POU EXOUME STIN LISTA ME TIS TIMES POU EXOUME STON PINAKA
//PREPEI NA FTIAXTEI AUTI I SUMBATOTITA
void poluonumo::antikatastasi_one_var(double timi,string variable){ //variable einai i metabliti pou theloume na eksalipsoume	

	//pollaplasiasmos_arithmou_with_array(timi,variable);
	//eliminate_one_variable(variable);
	
	int i,j;
	
	if(array==NULL){
		cout<<"O pinakas den exei dimiourgithei"<<endl;
	}
	else{
		if(variable=="y"){
			for (i = 0; i < max_y + 1; i++) {
				for (j = 0; j < max_x + 1; j++) {
					if(timi==fabs(0) && i==0){ //gia na elegksoume tin periptosi 0^0
						continue;
					}
					else{
						array[i][j]=array[i][j]*pow(timi,double(i));
					}
				}
			}
		}
		else{
			for (i = 0; i < max_y + 1; i++) {
				for (j = 0; j < max_x + 1; j++) {
					if(timi==fabs(0) && j==0){ //gia na elegksoume tin periptosi 0^0
						continue;
					}
					else{
						array[i][j]=array[i][j]*pow(timi,double(j));
					}
				}
			}
		}
	}
	
	if(variable=="y"){ //prepei na prosthesoume ola ta stoixeia kathe stilis
		for(i=0;i<max_x+1;i++){ //pairnoume mia mia kathe stili
			for(j=1;j<max_y+1;j++){ //pairnoume edo tis grammes ektos apo tin proti
				array[0][i]=array[0][i]+array[j][i];
				array[j][i]=0; //midenizoume to stoixeio pou den itan stin proti grammi
			}
		}
	}
	else{
		for(i=0;i<max_y+1;i++){ //pairnoume mia mia tis grammes
			for(j=1;j<max_x+1;j++){ //pairnoume tis stile apo tin 1 kai meta
				array[i][0]=array[i][0]+array[i][j];
				array[i][j]=0;
			}
		}
	}

	//print_array();
	//diairoume olous tous suntelestes me tou megaluterou mi-midenikou orou!!!
	double max=1;
	if(variable=="y"){
		for(i=max_x;i>0;i--){
			if(array[0][i]!=0){
				max=array[0][i];
				max_one_var=i;
				break;
			}
		}
		for(i=0;i<max_x+1;i++){
			array[0][i]=array[0][i]/max;
		}
		
			
	}
	else{
		for(i=max_y;i>0;i--){
			if(array[i][0]!=0){
				max=array[i][0];
				max_one_var=i;
				break;
			}
		}
		for(i=0;i<max_y+1;i++){
			array[i][0]=array[i][0]/max;
		}
	}
	
	//print_array();
	//cout<<"MAX_ONE_VAR:"<<max_one_var<<endl<<endl;
	
}

int poluonumo::give_max_one_var(){
	return max_one_var;
}


		
/////////////////////////////////////////////////////////////////




string metabliti_to_hide(poluonumo *ena, poluonumo *duo) //epilegei poia metabliti prepei na krupsoume
{

	int x, x0, x1, y, y0, y1;

	x0 = ena->give_max_x();
	x1 = duo->give_max_x();

	y0 = ena->give_max_y();
	y1 = duo->give_max_y();


	x = x0 + x1;

	y = y0 + y1;

	if (x >= y)
		return "y";
	else
		return "x";


}
