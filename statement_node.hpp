%token ID
%token NUM
%token STRING
%token VOID
%token INT
%token BYTE
%token B
%token BOOL
%token TRUE
%token FALSE
%token RETURN
%token WHILE
%token BREAK
%token CONTINUE
%token SC
%token COMMA

%nonassoc IF
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left RELOP_EQ
%left RELOP_REL
%left BINOP_ADD
%left BINOP_MUL
%right NOT
%left  LPAREN
%left  RPAREN
%left  LBRACE
%left  RBRACE






%{

#include "hw3_output.hpp"
#include "symbol_table.hpp"
#include "generic_syntax.hpp"
#include "types.hpp"
#include <list>
#include <string>

using std::vector;
using std::string;

extern int yylineno;

extern int yylex();

static symbol_table& symtab = symbol_table::instance();

void yyerror(const char* message);

void add_function_symbol(type_syntax* return_type, syntax_token* indentifier_token, list_syntax<formal_syntax>* formal_list);

root_syntax* create_root_syntax(list_syntax<function_declaration_syntax>* function_list);

expression_syntax* validate_bool_expression(expression_syntax* expression);

void print_current_scope();

%}

%code requires
        {
#include "syntax_token.hpp"
#include "abstract_syntax.hpp"
#include "generic_syntax.hpp"
#include "expression_syntax.hpp"
#include "statement_syntax.hpp"
        }

%union
{
    syntax_token*                             token;
    root_syntax*                              root;
    type_syntax*                              type;
    formal_syntax*                            formal;
    function_declaration_syntax*              function;
    statement_syntax*                         statement;
    expression_syntax*                        expression;
    list_syntax<formal_syntax>*               formal_list;
    list_syntax<function_declaration_syntax>* function_list;
    list_syntax<statement_syntax>*            statement_list;
    list_syntax<expression_syntax>*           expression_list;
};

%token <token> VOID
%token <token> INT
%token <token> BYTE
%token <token> B
%token <token> BOOL
%token <token> TRUE
%token <token> FALSE
%token <token> RETURN
%token <token> WHILE
%token <token> BREAK
%token <token> CONTINUE
%token SC
%token COMMA
%token LBRACE
%token RBRACE
%token <token> NUM
%token <token> ID
%token <token> STRING

%right LPAREN
%left RPAREN
%right <token> ASSIGN
%nonassoc <token> IF // TODO: VERIFY IF IN RIGHT POSITION
%nonassoc <token> ELSE
%left <token> OR
%left <token> AND
%left <token> EQOP
%left <token> RELOP
%left <token> ADDOP
%left <token> MULOP
%right <token> NOT

%type <root>            Program
%type <function_list>   Funcs
%type <function>        FuncDecl
%type <type>            RetType
%type <formal_list> 	Formals
%type <formal_list>     FormalsList
%type <formal>          FormalDecl
%type <statement_list>  Statements
%type <statement>   	Statement
%type <expression>      Call
%type <expression_list> ExpList
%type <type>			Type
%type <expression>      Exp
%type <expression>      BoolExp

%%

Program 	: Funcs 										{ $$ = create_root_syntax($1); delete $$; }
;
Funcs   	: %empty                                        { $$ = new list_syntax<function_declaration_syntax>(); }
| FuncDecl Funcs					            { $$ = $2->push_front($1); }
;
FuncDecl 	: RetType ID LPAREN Formals RPAREN              { add_function_symbol($1, $2, $4); }
LBRACE Statements CS RBRACE                   { $$ = new function_declaration_syntax($1, $2, $4, $8); }
;
RetType 	: Type                                          { $$ = $1; }
| VOID                                          { $$ = new type_syntax($1); }
;
Formals 	: %empty                                        { $$ = new list_syntax<formal_syntax>(); }
| FormalsList                                   { $$ = $1; }
;
FormalsList : FormalDecl                                    { $$ = new list_syntax<formal_syntax>($1); }
| FormalDecl COMMA FormalsList                  { $$ = $3->push_front($1); }
;
FormalDecl 	: Type ID                                       { $$ = new formal_syntax($1, $2); }
;
Statements	: Statement	                                    { $$ = new list_syntax<statement_syntax>($1); }
| Statements Statement                          { $$ = $1->push_back($2); }
;
Statement	: LBRACE OS Statements CS RBRACE                { $$ = new block_statement_syntax($3); }
| Type ID SC                                    { $$ = new declaration_statement_syntax($1, $2); }
| Type ID ASSIGN Exp SC                         { $$ = new declaration_statement_syntax($1, $2, $3, $4); }
| ID ASSIGN Exp SC                              { $$ = new assignment_statement_syntax($1, $2, $3); }
| Call SC                                       { $$ = new expression_statement_syntax($1); }
| RETURN SC	                                    { $$ = new return_statement_syntax($1); }
| RETURN Exp SC                                 { $$ = new return_statement_syntax($1, $2); }
| IF LPAREN BoolExp RPAREN OS Statement CS      { $$ = new if_statement_syntax($1, $3, $6); }
| IF LPAREN BoolExp RPAREN OS Statement CS
        ELSE OS Statement CS                          { $$ = new if_statement_syntax($1, $3, $6, $8, $10); }
| WHILE LPAREN BoolExp RPAREN OSL Statement CS  { $$ = new while_statement_syntax($1, $3, $6); }
| BREAK SC                                      { $$ = new branch_statement_syntax($1); }
| CONTINUE SC                                   { $$ = new branch_statement_syntax($1); }
;
Call 		: ID LPAREN ExpList RPAREN                      { $$ = new invocation_expression_syntax($1, $3); }
| ID LPAREN RPAREN                              { $$ = new invocation_expression_syntax($1); }
;
ExpList 	: Exp                                           { $$ = new list_syntax<expression_syntax>($1); }
| Exp COMMA ExpList                             { $$ = $3->push_front($1); }
;
Type 		: INT                                           { $$ = new type_syntax($1); }
| BYTE                                          { $$ = new type_syntax($1); }
| BOOL                                          { $$ = new type_syntax($1); }
;
Exp 		: LPAREN Exp RPAREN	                            { $$ = $2; }
| Exp IF LPAREN Exp RPAREN ELSE Exp             { $$ = new conditional_expression_syntax($1, $2, $4, $6, $7); }
| Exp ADDOP Exp                                 { $$ = new arithmetic_expression_syntax($1, $2, $3); }
| Exp MULOP Exp                                 { $$ = new arithmetic_expression_syntax($1, $2, $3); }
| ID                                            { $$ = new identifier_expression_syntax($1); }
| Call                                          { $$ = $1; }
| NUM                                           { $$ = new literal_expression_syntax<int>($1); }
| NUM B                                         { $$ = new literal_expression_syntax<char>($1); delete $2; }
| STRING                                        { $$ = new literal_expression_syntax<string>($1); }
| TRUE                                          { $$ = new literal_expression_syntax<bool>($1); }
| FALSE                                         { $$ = new literal_expression_syntax<bool>($1); }
| NOT Exp                                       { $$ = new not_expression_syntax($1, $2); }
| Exp AND Exp                                   { $$ = new logical_expression_syntax($1, $2, $3); }
| Exp OR Exp                                    { $$ = new logical_expression_syntax($1, $2, $3); }
| Exp RELOP Exp                                 { $$ = new relational_expression_syntax($1, $2, $3); }
| Exp EQOP Exp                                  { $$ = new relational_expression_syntax($1, $2, $3); }
| LPAREN Type RPAREN Exp %prec NOT              { $$ = new cast_expression_syntax($2, $4); }
;
BoolExp     : Exp                                           { $$ = validate_bool_expression($1); }
;
OS          : %empty                                        { symtab.open_scope(); }
;
OSL         : %empty                                        { symtab.open_scope(true); }
;
CS          : %empty                                        { print_current_scope(); symtab.close_scope(); }
;
%%

int main()
{
    symtab.open_scope();
    symtab.add_function("print", fundamental_type::Void, vector<fundamental_type>{fundamental_type::String});
    symtab.add_function("printi", fundamental_type::Void, vector<fundamental_type>{fundamental_type::Int});
    
    int res = yyparse();
    
    print_current_scope();
    symtab.close_scope();
    
    return res;
}

void yyerror(const char* message)
{
    output::errorSyn(yylineno);
}

void add_function_symbol(type_syntax* return_type, syntax_token* indentifier_token, list_syntax<formal_syntax>* formal_list)
{
    string name = indentifier_token->text;
    
    if (symtab.contains_symbol(name))
    {
        output::errorDef(indentifier_token->definition_line, name);
    }
    
    vector<fundamental_type> param_types;
    
    for (formal_syntax* fs : formal_list->get_elements())
    {
        param_types.push_back(fs->type->type);
    }
    
    symtab.add_function(name, return_type->type, param_types);
    
    symtab.open_scope();
    
    for (formal_syntax* fs : formal_list->get_elements())
    {
        if (symtab.contains_symbol(fs->identifier))
        {
            output::errorDef(fs->identifier_token->definition_line, name);
        }
        
        symtab.add_formal(fs->identifier, fs->type->type);
    }
}

expression_syntax* validate_bool_expression(expression_syntax* expression)
{
    if (expression->return_type != fundamental_type::Bool)
    {
        output::errorMismatch(yylineno);
    }
    
    return expression;
}

root_syntax* create_root_syntax(list_syntax<function_declaration_syntax>* function_list)
{
    if (yychar != YYEOF)
    {
        yyerror(nullptr);
    }
    
    return new root_syntax(function_list);
}

void print_current_scope()
{
    output::endScope();
    
    for (symbol* sym : symbol_table::instance().current_scope().get_symbols())
    {
        if (sym->sym_type == symbol_type::Var)
        {
            output::printID(sym->name, sym->offset, types::to_string(sym->type));
        }
        else if (sym->sym_type == symbol_type::Func)
        {
            function_symbol* func_sym = static_cast<function_symbol*>(sym);
            
            vector<string> param_types;
            
            for (fundamental_type ft : func_sym->parameter_types)
            {
                param_types.push_back(types::to_string(ft));
            }
            
            string func_type = output::makeFunctionType(types::to_string(func_sym->type), param_types);
            
            output::printID(sym->name, sym->offset, func_type);
        }
        else
        {
            throw std::runtime_error("unknown symbol type");
        }
    }
}