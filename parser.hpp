#if !defined (PARSER_)
#define PARSER_


#include <iostream>
#include<string>
#include<math.h>
#include<algorithm>
#include<deque>
#include<vector>
#include<exception>
#include<type_traits>

const char number = '8';
const std::string quit = "exit";
const std::string help = "help";
const char print = ';';//���������� ������
const char let = 'l';//���������� ������������� ����������
const char name = 'a';//���������� ����������
const char functional = 'e';//���������� �������
const char fnctional = 'f';//���������� ���������
const char system_key = 'b';//���������� ��������� �����
const char variable_expr = 'c';//���������� ��������� ����������
const char const_var = 'd';
const std::string declkey = "let";
const std::string function = "function";
const std::string cnst = "const";



class Variable {
public:
	std::string name;
	//double value;
	std::vector<double>value;//������ ����� �� ���� ������� � ������
	//�� ��������� - ������ ������� ����� 1(��� ������������� ����������)
	//��� �������� �������� ���������� ���������� ����� ������������ ������ 
	//� ��������� {begin:end:step},��� step - ��� �� ���������, �������� [begin , end]
	bool is_constant;//�� ��������� �� ���������
	//Variable(std::string, double , bool is_cnst = false);
	bool is_array{false};//�.�. �������� �� ������ ���������� ��������
	Variable(const std::string, const double, const bool is_cnst);
	Variable(const Variable&v);
	Variable();
	
};

class Token {
public:
	double value;
	char kind;
	std::string name;
	Token();
	Token(char);
	Token(std::string);
	Token(char, double);
	Token(char , std::string);
};

class Token_Stream {
public:
	Token_Stream();
	Token get();//������ �� ������� ������
	void putback(Token);
	void ignore(char);
	//bool empty();
	//void reset(Token t = {});//����e������������ ������
private:
	std::deque<Token>buffer_t;
};

namespace decl {
	extern std::vector<Variable> var_table;

	extern Token_Stream ts;
}

//const char extract(std::string);

double RETURN_FUNCTION(std::string, double);

double Get_func();

double up_term();

bool is_functional(std::string);

bool is_array(std::string);

void define_is_array(std::string name);

bool is_const_var(std::string);

double Name();

bool is_variable_expr(std::string);

void sys_handle(Token);

bool is_system_key(std::string);

void print_help(); 

double get_value(std::string name  , size_t pos = 0.);

bool is_declarated(std::string var);

double set_value(std::string name, double value , double old_value = 0.);

bool is_declarated(std::string var);

double define_name(Variable);

double expression();

double up_term();

double term();

void clean_up_mess();

double declaration();

double statement();

void calculate();

#endif

