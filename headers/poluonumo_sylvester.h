//poluonumo_sylvester.h
#ifndef POLUONUMO_SYLVESTER_H
#define POLUONUMO_SYLVESTER_H

#include "mitroo_sylvester.h"


class poluonumo_sylvester{
	private:
		int bathmos_krimenis; //einai o bathmos tou poluonumou sylvester
		int diastasi; //diastasi ton mitroon pou periexei
		string hidden; //i metabliti tou poluonumou sylvester
		poluonumo *f0,*f1; //ta duo poluonuma pou dimiourgisan to polunuma sylvester
		poluonumo ***mitroo; //to mitroo_sylvester pou pou analuetai sto poluonumo sylvester
		double ***poluonumo_mitrown; //pinakas pou periexe ta mitroa tou poluonumou
		void bathmos_hidden(); //sunartisi pou kathorizei ton bathmo tou poluonumou sylvester (bathmos_krimenis)
		
	public:
		poluonumo_sylvester(mitroo_sylvester *,poluonumo *,poluonumo *); //contructor
		~poluonumo_sylvester(); //destructor
		void print_poluonumo_mitrown(); //ektuponei olokliro to poluonumo sylvester
		void print_mitroo_suntelesti(int); //ektuponei to mitroei suntelesti pou tou ziteitai
		int give_bathmo();
		////////////////////////////meros 2
		string give_hidden(); //epistrefei tin metabliti tou poluonumou-sylvester
		int give_diastasi(); //epistrefei tin metabliti int diastasi
		double * transform_2d_to_1d(double *,int,int); //metatrepei to 2d-mitroo se 1d 
		int * transform_2d_to_1d(int *,int,int); //idia me tin apo pano apla pairnei/gurizei pinaka int
		double ** give_mitroo(double **,int,int); //epistrefei to mitroo pou tou zitatai gemizontas to pinakaki pou tou dinoume
		double ** get_mitroo(double ** array, int Ak) ;
		poluonumo_sylvester(double ***,int,int,string); //contructor pou xreisimopoieitai meta apo tin allagi_metablitis
};









#endif /* POLUONUMO_SYLVESTER_H */
