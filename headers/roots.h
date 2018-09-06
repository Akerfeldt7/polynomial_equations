//roots.h

#ifndef ROOTS_H
#define ROOTS_H

#include <iostream>
#include <cmath>
#include <string.h>
#include "poluonumo.h"
#include "one_var_companion.h"

using namespace std;

class riza{
	private:
		double x;
		double y;
		int multiplicity; //h pollaplotita tis krummenis metablitis
		string hidden; //i pollaplotita tis krummenis metablitis
		bool idiodianusma;
	public:
		riza(double,double,int,string,bool);
		~riza();
		double give_x();
		double give_y();
		int give_multiplicity();
		void print_riza();
		void add_multiplicity(); //auksanei kata ena to multiplicity
		bool give_boolean();
		void make_boolean_true();
		//meros 3
		double give_idiotimi_with_multiplicity();
};

class list_of_roots{ //klassi i opoia exei tis telikes rizes (x,y)
	private:
		struct kombos{
			int id; //deixnei ton arithmo tou kombou//ksekinaei apo 1;
			double x;
			double y;
			kombos *next;
		};
		kombos *start;
		kombos *last;
		int plithos;
	public:
		list_of_roots();
		~list_of_roots();
		void add_to_lista(double,double);
		double give_x(int id);
		double give_y(int id);
		int give_plithos();
};


class roots{
	private:
		string hidden; //i krumeni metabliti
		int point; //deixnei se poio keli tou pinaka eimaste gia na eisagoume kainourgi riza kai kataepektasi poses exoun mpei//POLU SIMANTIKO
		int plithos_luseon; //einai oi megistes rizes pou xoraei o pinakas aneksartita apo to ean einai sostes i oxi
		riza **table_roots; //pinakas me deiktes se class riza
		int existance_of_multiplicity(double,double); //elegxei gia tin pollaplotita mias rizas
		//list_of_roots * all_rizes;
	public:
		roots(int,string); //to megisto plithos_luseon
		roots(const roots &obj); //copy_contructor
		~roots();
		void add_root(double,double,bool);
		void print_roots(poluonumo *f1,poluonumo *f2);
		int sunoliko_plithos_soston_luseon(); //epistrefei ton sunoliko arithmo ton soston luseon
		void print_change_roots(poluonumo *f1,poluonumo *f2,int t1,int t2,int t3,int t4); //gia otan exoume allaksei riza
		list_of_roots * fill_the_list_of_roots(poluonumo *f1,poluonumo *f2);
		
};


class lista{
	private:
		struct kombos{
			double timi;
			kombos *next;
		};
		kombos * start;
		kombos * last;
		int plithos;
		bool existance(double);
	public:
		lista();
		~lista();
		void add_to_lista(double);
		void print_lista();
		int give_plithos();
		void fill(list_of_roots *,double,string); //KAINOURGIA MEROS 3
};


		
	

#endif /* ROOTS_H */
