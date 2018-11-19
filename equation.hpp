#if !defined(EQ_PARSING)
#define EQ_PARSING

#include"parser.hpp"

class Function {

public:
	std::string equation;
	std::string name;
	Variable  * var_ptr;
	Function();
	Function(const std::string, const std::string,  Variable*);
};

namespace decl {
		extern std::vector<Function>func_table;
}


Variable * this_var(std::string);

double define_func();

double declaration_func();

bool is_declarated_func(std::string);

double get_value_func(size_t pos = 0);

double read_equation(const std::string);

#endif
