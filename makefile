OBJS=meros3_main.o poluonumo.o mitroo_sylvester.o poluonumo_sylvester.o helping_functions.o standard_eigen_problem.o solve.o roots.o  gen_eig_prob.o one_var_companion.o interpolation.o change_poluonumo_sylvester.o
SOURCE=meros3_main.cpp poluonumo.cpp mitroo_sylvester.cpp poluonumo_sylvester.cpp helping_functions.cpp standard_eigen_problem.cpp solve.cpp roots.cpp  gen_eig_prob.cpp one_var_companion.cpp interpolation.cpp change_poluonumo_sylvester.cpp
HEADER=poluonumo.h mitroo_sylvester.h poluonumo_sylvester.h standard_eigen_problem.h solve.h roots.h gen_eig_prob.h one_var_companion.h interpolation.h change_poluonumo_sylvester.h
OUT=run

all:$(OBJS)
	g++ -g $(OBJS) -llapacke -o $(OUT) 

meros3_main.o:meros3_main.cpp
	g++ -I Eigen -c meros3_main.cpp 

poluonumo.o:poluonumo.cpp
	g++ -c poluonumo.cpp

mitroo_sylvester.o:mitroo_sylvester.cpp
	g++ -c mitroo_sylvester.cpp

poluonumo_sylvester.o:poluonumo_sylvester.cpp
	g++ -c poluonumo_sylvester.cpp

helping_functions.o:helping_functions.cpp
	g++ -c helping_functions.cpp

standard_eigen_problem.o:standard_eigen_problem.cpp
	g++ -c standard_eigen_problem.cpp

solve.o:solve.cpp
	g++ -c solve.cpp 

roots.o:roots.cpp
	g++ -c roots.cpp

gen_eig_prob.o:gen_eig_prob.cpp
	g++ -c gen_eig_prob.cpp

one_var_companion.o:one_var_companion.cpp
	g++ -c one_var_companion.cpp

interpolation.o:interpolation.cpp
	g++ -c interpolation.cpp

change_poluonumo_sylvester.o:change_poluonumo_sylvester.cpp
	g++ -c change_poluonumo_sylvester.cpp

clean:
	rm -f $(OBJS) $(OUT)
