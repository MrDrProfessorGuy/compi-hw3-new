
#include "hw3_output.hpp"
#include <cstdlib>

#define YYDEBUG 1

extern int yydebug;
extern int yyparse();
extern int yylex();
int yyerror(const char * message);

#define NewNode(attr, children) $$ = createNode(); $$->setAttributes(attr); $$->setChildren(children);
#define Cast(obj, Type) (std::static_pointer_cast<TYPE>(obj))







int main(){
    yydebug = 1;
    
    int token;
    //cout << "max size = " << token_value.max_size() << endl;
    
    while ((token = yyparse())) {
        continue;
        //printf("%d %s %s\n", yylineno, token, yytext);
        //cout << yylineno << " " << tokentype_str[token] << " " << token_value.c_str() << endl;
        //flush(cout);
    }
    
    return 0;
}

int yyerror(const char * message){
    output::errorSyn(yylineno);
    exit(0);
}



