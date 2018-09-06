//mitroo_sylvester.h
#ifndef MITROO_SYLVESTER_H
#define MITROO_SYLVESTER_H

#include "poluonumo.h"


class mitroo_sylvester {
private:
	int diastasi; //diastasi tou mitroo sylvester
	poluonumo *f0, *f1; //poluonuma pou dimiourgoun to mitroo
	string hidden; //krummeni metabliti
	poluonumo ***mitroo; //2d-pinakas poluonumos (to mitroo sylvester)
	void add_poluonumo_to_mitroo(poluonumo *, int, int); //poluonumo,grammi,stili
	void create_mitroo_sylvester_for_hidden_y();
	void create_mitroo_sylvester_for_hidden_x();
public:
	mitroo_sylvester(poluonumo *, poluonumo *, string); //ta duo poluonuma kai tin krimmeni metabliti
	~mitroo_sylvester();
	void create_mitroo_sylvester(); //dimiourgei ton 2d-pinaka poluonumon(mitroo)
	void print_simple_mitroo_sylvester(); //ektuponei apla ton pinaka
	void print_mitroo_sylvester();  //ektuponei omorfa ton pinaka (san pinaka)
	int give_diastasi();
	string give_hidden();
	poluonumo *give_poluonumo(int,int); //dinoume grammi,stili kai mas epistrefei ena duplicate poluonumo
	
};

#endif /* MITROO_SYLVESTER_H */
