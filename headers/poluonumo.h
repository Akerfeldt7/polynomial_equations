#ifndef POLUONUMO_H
#define POLUONUMO_H

#include <iostream>

using namespace std;

/*struct roots{ //MEROS DEUTERO EINAI AUTO EDO //eftiaksa klassi roots
	double x;
	double y;
};
*/


class term {
private:
    int bathmos;
    int power_x;
    int power_y;
    double number;
public:
    term(int, int, double); //power_x,power_y,number
    ~term();
   string print_term();
    int give_bathmos_term();
    int give_power_x();
    int give_power_y();
    double give_number();
};


class poluonumo {
private:
    int bathmos; //bathmos poluonumou
    int max_x;  //megistos ekthetis tou x
    int max_y;  //megistos ekthetis tou y
    int max_one_var; //megistos ekthetis meta tin antikatastasi mias metablitis,gia to trito meros!!
    struct node {
        term * held_term;
        node *next;
    };
    node * head;
    node * start;
    node * current; //kainourgio
    double **array;  //2d-pinakas poluonumou,x stiles x^0 x^1.. x^k,y grammes paromoia me to x.
public:
    poluonumo();
    ~poluonumo();
	poluonumo(const poluonumo &obj);
    void add_term(term*);
    void create_array();
    string print_poluonumo();
    void print_array();
    bool check_array_for_existance(int, int); //elegxei an ena zeugari ektheton uparxei ston pinaka
    bool check_list_for_existance(int, int); //elegxei an ena zeugari ektheton uparxei stin lista
    int give_max_x();
    int give_max_y();
    term * give_term(); //prosoxi sta sxolia stin ulopoihsi sto arxeio .cpp
    void reset_current_term();  //mazi me give_term
    double give_suntelesti_from_table(int, int); //grammi,stilli...epistrefei ton suntelesti tou keliou pou zhteitai
    bool empty(); //epistrefei true an to poluonumo einai adeio
	int give_bathmos_poluonumo(); //epistrefei ton bathmo tou poluonumou
	bool array_exist(); //true an uparxei pinakas,false an den uparxei
	double antikatastasi(double,double); //meros 2 // kanei antikatastasi to (x0,y0) pou tou dinetai sto poluonumo kai epistrefei to apotelesma
	//int ** pollaplasiasmos_me_pinaka(int **,int); MH HLOPOIHMENO
	//MEROS 3
	void antikatastasi_one_var(double timi,string variable);
	int give_max_one_var();
	
   
};

 string metabliti_to_hide(poluonumo *ena, poluonumo *duo);

#endif /* POLUONUMO_H */
