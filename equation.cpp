#include"pch.h"
#include"equation.hpp"


namespace decl {
		std::vector<Function> func_table;
}

using namespace decl;

Function::Function() {
	this->equation = "";
	this->name = "";
	this->var_ptr = nullptr;
}

Function::Function(const std::string equation, const std::string name,  Variable *var)
{
	this->equation = equation;
	this->name = name;
	this->var_ptr = var;
}

double declaration_func() {
	//считаем что метку  дескриптором fnctional уже встретили
	//обрабатываем: name '=' expression;
	Token t = ts.get();
	if (t.kind != name)throw  std::exception("expeceted name of function!!!\n");
	ts.putback(t);
	return define_func();
}

double define_func()
{
	//считаем что метку  дескриптором name уже встретили
	Token t = ts.get();//name
	std::string str;
	Token t2 = ts.get();// '=' 
	double d;
	switch (t2.kind) {

	case '=': {

		std::string str;
		Variable * my_var;
		while (std::cin >> str);
		for (auto i : str)
			std::cin.putback(i);
		my_var = this_var(str);
		 d = expression();
		func_table.push_back({ str , t.name ,my_var });
	     }
	}
	
    return d;
}

Variable * this_var(std::string str) {

	std::string var, express;
	Variable * temp;
	express = "undefined variable ";
	Token t = ts.get();
	while (true) {
		if (t.kind == name) {
			express += t.name;
			if(!is_declarated(t.name))throw std::exception(express.c_str());
			for (auto i : var_table)
				if ((i.name == t.name) && !i.is_constant) {
					temp = &i;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    for (auto i : str)
		            std::cin.putback(i);
                    return temp;
				}
		}
	}
	
	return nullptr;
}



double get_value_func(size_t pos) {
   
	//TODO :: insert your code here
}

bool is_declarated_func(std::string str) {
	for (auto i : func_table)
		if (i.name == str)return true;
	return false;
}

double read_equation(const std::string str) {
	
	for (auto i : str)std::cin.putback(i);//запишем последовательность в поток
	double d = expression();// и наконец посчитаем ее
	return d;
}