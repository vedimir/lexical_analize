#include"pch.h"
#include"equation.hpp"


//bool is_const_var(std::string str) { //DEPRECATED
//	std::vector<std::string>const_var_table = {"pi" , "e"};
//	for (auto i : const_var_table)
//		if (str == i)return true;
//	return false;
//}

namespace decl {
	std::vector<Variable> var_table;

	Token_Stream ts;
}
using namespace decl;

//const char extract( std::string str) {
//	if (str.empty)return '\0';
//	char temp = str.front();
//	str.erase(str.cbegin());
//	return temp;
//}
bool is_functional(std::string str) {
	double(*pf)(double);
	std::vector<std::pair<std::string , double(*)(double)>>functional_talbe = {
		{"sin", pf = std::sin} , {"cos", pf = std::cos} , {"ln", pf = std::log} ,
	{"lg", pf = std::log10} , {"tg", pf = std::tan} , {"ctg", pf = std::tan} ,
	{"arcsin", pf = std::asin} ,{"arccos", pf = std::acos},{"arctg", pf = std::atan} ,
	{"arcctg", pf = std::atan} };
	
	for (auto i : functional_talbe) 
		if (i.first == str)return true;
		return false;
}

bool is_array(std::string str) {
	for (auto i : var_table)
		if ((i.name == str) && i.is_array)return true;
	return false;
}

void define_is_array(std::string name)
{
	for (auto & i : var_table)
		if ((i.name == name) && i.is_array) {
			i.value.clear();
			i.is_array = true;
		}
		else if (i.name == name) {
			i.is_array = true;
		}
	return;
}

bool is_variable_expr(std::string str) {
	std::vector<std::string>variable_expr_table = {"+=" ,"-=" , "="};
	for (auto i : variable_expr_table)
		if (str == i)return true;
	return false;
}

void sys_handle(Token t) {
	if (t.name == quit)
		exit(0);
	if (t.name == help)
		print_help();
}

bool is_system_key(std::string str)
{
	std::vector<std::string>system_key_table = {"exit" , "help"};
	for (auto i : system_key_table)
		if (i == str)return true;
	return false;
}

void print_help() {
	std::cout << "THIS IS EXTENDED CALCULATOR\nDEVELOPED BY BJARNE STROUSTRUP AND DS-71\n\n\n"\
		"SET COMMAND TO THIS CALCULATOR :\n"\
		"expression - set symbols , for exam : 2+4*2 / 3*(2-1);\n"\
		"WARNING : EACH REPRESENT-SELF TOKEN UNITS MUST HAVE  SPACE-SYMBOLS\n\n"\
		"help - print to set comands and syntaxis command\n"\
		"exit - quit to the windows\n" \
		"let - definition somebody variable , using characters||digits but not specialy symbols\n"\
		"; - print value expression\n\n"\
		"TERMS INITIALIZATION OF VARIABLE :\n"\
		"let 'name' = expression;  - initial new variable with name 'name'\n"\
		"let const 'name' = expression;  - initial new constant variable with name 'name'\n"\
		"'name'; - read value into the variable with name 'name'\n"\
		"'name'  '=' expression; -  re-initial old variable new value. old value is deleted\n"\
		"'name' '+=' expression; -re-initial old variable new value , with saving old value along new value\n"\
		"'name' '{' begin : end : step'}'; create a new table vairable 'all in one'\n"\
		"'name''['position']';display element of table vairable \n"\
		"'name' '-=' expression; -re-initial old variable new value , with saving old value along new value\n";
}


//Variable::Variable(std::string name, double value , bool is_cnst)
//{
//	 this->name = name;
//	this->value = value;
//	this->is_constant = is_cnst;
//}

Variable::Variable()
{
	this->is_array = false;
	this->is_constant = false;
	this->name = std::string();
	this->value = std::vector<double>();
}

Variable::Variable(const std::string str, const double d, const bool is_cnst) {
    this->name = str;
	this->value.push_back(d);
	this->is_constant = is_cnst;
}


Variable::Variable(const Variable & v)
{
	this->is_constant = v.is_constant;
	this->name = v.name;
	this->value = v.value;
}

double get_value(std::string name , size_t pos) {

	if (is_declarated(name))
	for (const Variable& v : var_table) {
		if (v.name == name)return v.value.at(pos);//возврат всегда первого значения
	}
	std::string str = "not find variable ";
	str += name;
	throw std::exception( str.c_str());
}



double  set_value(std::string name, double value , double old_value) {

	std::string str1 = "try change const variable ";
	str1 + name;
	if (is_declarated(name)) {
		for (Variable& v : var_table)
			if ((v.name == name) && !v.is_constant) {
				if(!v.is_array)v.value.pop_back();//для изменения старого значения удалим его
				v.value.push_back(value + old_value);//и заменим на новое
				return v.value.front();//возврат всегда первого значения
			}
			else if(v.is_constant && (v.name == name))throw  std::exception(str1.c_str());
	}
	std::string str = "not find variable ";
	str += name;
	throw std::exception(str.c_str());
}

bool is_declarated(std::string var) {

	for (Variable& v : var_table) 
		if (v.name == var)return true;
			
	return false;
}

double define_name(Variable var) {
	std::string str = "re-implementation is ";
	str += var.name;
	//bool bl = false;
	if(is_declarated(var.name))throw std::exception(str.c_str());
	//if (is_const_var(var.name) || var.is_constant) bl = true;
	//if (var.is_constant) bl = true;
	//var.is_constant = bl;
	var_table.push_back(Variable(var));//непосредственно добавление новой переменной в память
	return var.value.front();//возврат всегда первого значения
}



Token::Token() {
	value = double();
	kind = char();
	this->name = std::string();
}
Token::Token(char ch) {
	value = double();
	kind = char(ch);
	this->name = std::string();
}
Token::Token(std::string str)
{
	kind = char();
	this->value = double();
	this->name = str;
}
Token::Token(char ch , double d) {
	value = double(d);
	kind = char(ch);
	this->name = std::string();
}
Token::Token(char ch, std::string str)
{
	kind = ch;
	this->value = double();
	this->name = str;
}

Token_Stream::Token_Stream()
{
}

void Token_Stream::putback(Token t)
{
	buffer_t.push_front(t);
}

Token Token_Stream::get()
{  
	

	if (!buffer_t.empty()) {
	
		Token temp = buffer_t.front();
		buffer_t.pop_front();
		return temp;
	}

	char symbol;
	
	std::cin >> symbol;
	switch (symbol) {
	case print:
	case'*':
	case'/':
	case'=':
	case'%':
	case'[':
    case']':
	case':':
	case'+':
	case'-':
	case'^':
	case'(':
	case'{':
	case')':
	case'}':
	case'!':
		return Token(symbol);
	case'.':
	case'0':
	case'1':
	case'2':
	case'3':
	case'4':
	case'5':
	case'6':
	case'7':
	case'8':
	case'9':
            std::cin.putback(symbol);
            double val;
		    std::cin >> val;

		return Token(number, val);
	default: 
		if (!isdigit(symbol)) {

			std::string s;
			s += symbol;
			while ((std::cin.get(symbol) && isalnum(symbol))&& !is_functional(s)) s += symbol;
			//while (std::cin.get(symbol)&&(isalpha(symbol) || isdigit(symbol))) s += symbol;
			std::cin.putback(symbol);
			if (s == declkey)return Token(let);
			if (s == function)return Token(fnctional);
			if (s == cnst)return Token(const_var);
			if (is_system_key(s))return Token(system_key, s);
			if (is_functional(s))return Token(functional, s);
			//необходимо доработать даную ветку до работопособного состояния
			//if (is_variable_expr(s))return Token(variable_expr, s);//это пока не работает из-за "+" в первой позиции case
			return Token(name, s);// все что не попадает под категорию ключевого слова будет переменной
		}
		else
		throw std::exception(" isalpha(symbol) Wrong Token\n");
	}
}

void Token_Stream::ignore(char c)
{

	if (!buffer_t.empty() && (c == buffer_t.front().kind)) {

		buffer_t.clear();
		return;
	}
	buffer_t.clear();

	char ch = 0;
	while (std::cin >> ch)
		if (ch == c)return;

}

//bool Token_Stream::empty()
//{
//	if (((buffer.kind == ' ') || (buffer.kind == '\0')) 
//		&& !std::cin.rdbuf()->in_avail()-1)return true;
//	std::string temp;
//	bool bl{true};// по умолчанию поток пуст
//	std::getline(std::cin, temp);
//	for (auto v : temp) {
//		if (v!=' ') {
//			bl = false;//не пусто
//			break;
//		}
//		else
//		bl =  true;// пусто
//	}
//	if (!bl) {//для не пустой строки
//		for (unsigned i{}; i < temp.length(); ++i) //в случае символьной строки положить все символы назад в поток
//			std::cin.putback(temp[temp.length() - (i + 1)]);
//		
//		return bl;//вернуть признак непустого потока
//	}
//	else if (!temp.empty() && bl) return bl;
//	if (!full && temp.empty())//нет символов в потоке 
//		return true;
//	return false;
//
//}


//void Token_Stream::reset(Token t)//чтобы была возможность выборочно утанавливать лексему
//{
//	if((t.kind == '\0') && (t.name == "") && (t.value == 0))
//	full = false;
//	full = true;
//	buffer = t;
//}

double primary() {
	Token t = ts.get();
	switch (t.kind) {

	case'(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') throw std::exception(" ( Wrong Token\n");
		return d;
	}
	case'{':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}')throw std::exception(" { Wrong Token\n");
		return d;
	}
	case number:
		return t.value;
	case'-':
		return -primary();
	case'+':
		return primary();
	case name: 
		if (is_declarated(t.name)) {
			ts.putback(t);//не забудем вернуть лексему следущей продукции грамматике
			return Name();
		}
		if (is_declarated_func(t.name)) {
			ts.putback(t);//не забудем вернуть лексему следущей продукции грамматике
			return get_value_func();
		}
	case functional:
		ts.putback(t);
		return Get_func();
	//case name:
	//{
	//	
	//	if (is_declarated(t.name)) {
	//		Token t2;
	//		
	//		if (std::cin.rdbuf()->in_avail() - 1) {//нет лексемы - нет проблемы -> лексема - проблема
	//			 t2 = ts.get();
	//			 switch (t2.kind) {
	//			 case'=': {
	//				 double d = expression();//здесь проблема , тогда нельзя ts.putback
	//				 //когда есть ; то надо его оставить
	//				 set_value(t.name, d);
	//				 //if ts.get == ; ...
	//				 //ts.reset({';',"" , 0}); - например так. не выжу смысла идти дальше пока не ясна грамматика
	//				 //надо доработать грамматику ,чтобы корректно работала , утсранить недочеты.
	//				 ts.putback(t2);
	//				 break;
	//			 }
	//			 case ';':
	//				 ts.putback(t2);
	//				 return get_value(t.name);//для возврата конкретно значения переменной
	//			 case '\n':
	//				 ts.putback(t2);
	//				 return get_value(t.name);
	//				 break;
	//			 default:
	//				 throw std::exception("undefined token in bind with variable\n");
	//			 }
	//		}
	//		else {
	//			ts.putback(t);
	//			return get_value(t.name);//для участия в составных выражениях
	//		}
	//	}
	//		
	//	else {
	//		std::string str = "undefined varialbe ";
	//	    str += t.name;
	//		throw std::exception(str.c_str());
	//	}
	//	break;
	//}
	default:
		throw std::exception("Neds primary expresion\n"); 
	}
}

double Get_func() {
	Token t = ts.get();
	Token t2 = ts.get();
	if (t2.kind != '(')throw std::exception("waiting token '(' !!!\n");
	double d = expression();
	t2 = ts.get();
	if (t2.kind != ')')throw std::exception("waiting token ')' !!!\n");
	return RETURN_FUNCTION(t.name , d);//t.name == ""//why?
}

double RETURN_FUNCTION(std::string function , double expr)
{
	double(*pf)(double);
	std::vector<std::pair<std::string, double(*)(double)>>functional_talbe = {
		{"sin", pf = std::sin} , {"cos", pf = std::cos} , {"ln", pf = std::log} ,
	{"lg", pf = std::log10} , {"tg", pf = std::tan} , {"ctg", pf = std::tan} ,
	{"arcsin", pf = std::asin} ,{"arccos", pf = std::acos},{"arctg", pf = std::atan} ,
	{"arcctg", pf = std::atan} };

	for (auto i : functional_talbe)
		if (i.first == function) {
			if(i.first=="ctg" )return 1/i.second(expr);
			if (i.first == "arcctg")return  i.second(1/expr);
			return i.second(expr);
		}
	throw std::exception("undefined function !!!\n");
}

double Name()
{
	Token t = ts.get();//name
	Token t2 = ts.get();//= or ; or + or - or {begin : end : step}
	switch (t2.kind) {
	case '[':
	{
		double exp = expression();
        t2 = ts.get();
		if(t2.kind != ']')throw std::exception("waiting token ']' !!!\n");
		if(static_cast<int>(exp) != exp)throw std::exception("non integeral pow !!!\n");
		return get_value(t.name, (int)exp);
	}
	break;
	case '{':
	{
		if (!is_declarated(t.name))throw std::exception("undefined variable !!!\n");
		double begin = expression();
        set_value(t.name, begin);//возьмем begin , считаем что '{' уже  втретили
		//первое значение перезаписывает старое
		define_is_array(t.name);//определим как массив
		t2 = ts.get();
		if(t2.kind != ':')throw std::exception("waiting token ':'!!!\n");
		double end = expression();//считаем end
		t2 = ts.get();
		if (t2.kind != ':')throw std::exception("waiting token ':'!!!\n");
		double step = expression();//считаем step
		if((begin<end) && (step<0))throw std::exception("begin < end !!!\n");
		if ((begin > end) && (step > 0))throw std::exception("step < 0 !!!\n");
		if (begin < end) {
			begin += step;
				for (; begin <= end+step; begin += step)
					set_value(t.name, begin);//запись массива данных
		}
		else {
			begin += step;
			for (; begin >= end+step; begin += step)
				set_value(t.name, begin);//запись массива данных
		}

		t2 = ts.get();
		if (t2.kind != '}')throw std::exception("waiting token '}'!!!\n");
		return get_value(t.name);

	}
	break;
	case'=':
		return set_value(t.name, expression());
	case'+': {
		Token t3 = ts.get();
		if(t3.kind == '=')return set_value(t.name, get_value(t.name) + expression());
		ts.putback(t3);//вернем значения т.к. они не верны
		ts.putback(t2);//вернем значения т.к. они не верны
		return get_value(t.name);
	}
	case'-': {
		Token t3 = ts.get();
		if (t3.kind == '=')return set_value(t.name, get_value(t.name) - expression());
		ts.putback(t3);//вернем значения т.к. они не верны
		ts.putback(t2);//вернем значения т.к. они не верны
		return get_value(t.name);
	}
	default:
		ts.putback(t2);//для ликвидации задержки
		return get_value(t.name);
	}
}

double up_term() {
    double left = primary();
	Token t = ts.get();
		switch(t.kind) {
		case '^': {
			double d = primary();
			return std::pow(left, d);
		}
		
		case '!': {
			double fact{};
			if (static_cast<int>(left) != left)throw std::exception("non integeral pow !!!\n");
			for (int i = (int)left - 1; i > 0; --i)
				left *= i;
			return left;
		}
		default:
			ts.putback(t);
			return left;
	}
}


double term() {

	double left = up_term();
	Token t = ts.get();
	while(true)
	switch (t.kind) {
	case'*':
		left *= up_term();
		t = ts.get();
		break;
	case'%':
	{
		double d = up_term();
		if (d == 0) {
			throw std::exception("module by zero");
		}
		else {
			left =std::fmod(left, d);
			t = ts.get();
		}
		break;
	}
	case'/':
	{
		double d = up_term();
		if (d == 0) {
			throw std::exception("divide by zero");
		}
		else {
			left /= d;
			t = ts.get();
		}
		break;
	}
	default:
		ts.putback(t);
		return left;
	}
}

double expression() {
	double left = term();
	Token t = ts.get();//
	while(true)
		switch (t.kind) {
		case'+':
			left += term();
			t = ts.get();//
			break;
		case'-':
			left -= term();
			t = ts.get();//
			break;
		default:
			ts.putback(t);
			return left;
		}
}


void clean_up_mess() {

	ts.ignore(print);
}


double declaration() {
	Token t = ts.get();
	bool bl = false;
	if ((t.kind != name )&&(t.kind != const_var))
		throw std::exception("expected name of variable");
	if (t.kind == const_var) {
		t = ts.get();
		bl = true;
	}
	std::string var_name = t.name;

	Token t2 = ts.get();
	if(t2.kind != '=')
		throw std::exception("expected '=' ");

	double d = expression();

	define_name(Variable{ var_name  , d ,bl});
	return d;
}

double statement() 
try{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	//case fnctional: not implement
	//	return declaration_func();
	default:
		ts.putback(t);
		return expression();
	}
}
catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	clean_up_mess();
}
catch (...) {
	std::cerr << "unexpectedly exception!!!\n";
}

void calculate() {
	try {
		while (std::cin) {
			Token t = ts.get();
			while (t.kind == print)t = ts.get();
			if (t.kind == system_key)
				 sys_handle(t);
			else {
				ts.putback(t);
				std::cout << "= " << statement() << std::endl;
			}
		}
		return;
	}
catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	clean_up_mess();
}
catch (...) {
	std::cerr << "unexpectedly exception!!!\n";
   }
}

   