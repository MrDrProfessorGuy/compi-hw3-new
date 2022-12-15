%{

/* Declarations section */

#include "hw3_output.hpp"
#include <cstdlib>
#include <memory>


#define YYDEBUG 1


extern int yylex();
int yyerror(const char * message);

#define NewNode(attr, children) $$ = createNode(); $$->setAttributes(attr); $$->setChildren(children);
#define Cast(obj, Type) (std::static_pointer_cast<TYPE>(obj))


%}
%union YYSTYPE {
    Generic_Node* ProgramNode;
    shared_ptr<Node_Token> NodeToken;
    std::shared_ptr<Node_RetType> NodeRetType;
    std::shared_ptr<Node_FormalDecl> NodeFormalDecl;
    std::shared_ptr<Node_FormalsList> NodeFormalsList;
    std::shared_ptr<Node_FuncDecl> NodeFuncDecl;
    std::shared_ptr<Node_FuncsList> NodeFuncsList;
    std::shared_ptr<Node_Statement> NodeStatement;
    std::shared_ptr<Node_StatementList> NodeStatementList;
    std::shared_ptr<Node_Exp> NodeExp;
    std::shared_ptr<Node_ExpList> NodeExpList;
    std::shared_ptr<Node_Call> NodeCall;
    
    
};

%type <ProgramNode> Program
%type <NodeFuncsList> Funcs
%type <NodeFuncDecl> FuncDecl
%type <NodeRetType> RetType
%type <NodeFormalsList> FormalsList
%type <NodeFormalsList> Formals
%type <NodeFormalDecl> FormalDecl
%type <NodeStatementList> Statements
%type <NodeStatement> Statement
%type <NodeExp> Type
%type <NodeCall> Call
%type <NodeExpList> ExpList
%type <NodeExp> Exp


%token <NodeToken> VOID
%token <NodeToken> INT
%token <NodeToken> BYTE
%token <NodeToken> B
%token <NodeToken> BOOL

%token <NodeToken> TRUE
%token <NodeToken> FALSE
%token <NodeToken> RETURN


%token <NodeToken> WHILE
%token <NodeToken> BREAK
%token <NodeToken> CONTINUE
%token <NodeToken> SC
%token <NodeToken> COMMA
%token <NodeToken> LPAREN

%token <NodeToken> LBRACE
%token <NodeToken> RBRACE

%token <NodeToken> ID
%token <NodeToken> NUM
%token <NodeToken> STRING
%nonassoc <NodeToken> IF

%left <NodeToken> OR
%left <NodeToken> AND
%token <NodeToken> ASSIGN
%left <NodeToken> EQUALITY
%left <NodeToken> RELOP
%left <NodeToken> BINOP_ADD
%left <NodeToken> BINOP_MUL
%precedence <NodeToken> NOT
%precedence <NodeToken> RPAREN
%nonassoc <NodeToken> ELSE



%%
Program: Funcs                                                              {output::printProductionRule(1);};
Funcs: /*epsilon*/                                                          %empty {output::printProductionRule(2);};
Funcs: FuncDecl Funcs                                                       {output::printProductionRule(3);};
FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE         {output::printProductionRule(4);};
RetType: Type                                                               {output::printProductionRule(5);};
RetType:  VOID                                                              {output::printProductionRule(6);};
Formals: /*epsilon*/                                                        %empty {output::printProductionRule(7);};
Formals: FormalsList                                                        {output::printProductionRule(8);};
FormalsList: FormalDecl                                                     {output::printProductionRule(9);};
FormalsList: FormalDecl COMMA FormalsList                                   {output::printProductionRule(10);};
FormalDecl: Type ID                                                         {output::printProductionRule(11);};
Statements: Statement                                                       {output::printProductionRule(12);};
Statements: Statements Statement                                            {output::printProductionRule(13);};
Statement: LBRACE Statements RBRACE                                         {output::printProductionRule(14);};
Statement: Type ID SC                                                       {output::printProductionRule(15);};
Statement: Type ID ASSIGN Exp SC                                            {output::printProductionRule(16);};
Statement: ID ASSIGN Exp SC                                                 {output::printProductionRule(17);};
Statement: Call SC                                                          {output::printProductionRule(18);};
Statement: RETURN SC                                                        {output::printProductionRule(19);};
Statement: RETURN Exp SC                                                    {output::printProductionRule(20);};
Statement: IF LPAREN Exp RPAREN Statement                                   {output::printProductionRule(21);};
Statement: IF LPAREN Exp RPAREN Statement ELSE Statement                    {output::printProductionRule(22);};
Statement: WHILE LPAREN Exp RPAREN Statement                                {output::printProductionRule(23);};
Statement: BREAK SC                                                         {output::printProductionRule(24);};
Statement: CONTINUE SC                                                      {output::printProductionRule(25);};
Call: ID LPAREN ExpList RPAREN                                              {output::printProductionRule(26);};
Call: ID LPAREN RPAREN                                                      {output::printProductionRule(27);};
ExpList: Exp                                                                {output::printProductionRule(28);};
ExpList: Exp COMMA ExpList                                                  {output::printProductionRule(29);};
Type: INT                                                                   {output::printProductionRule(30);};
Type: BYTE                                                                  {output::printProductionRule(31);};
Type: BOOL                                                                  {output::printProductionRule(32);};
Exp: LPAREN Exp RPAREN                                                      {output::printProductionRule(33);};
Exp: Exp IF LPAREN Exp RPAREN ELSE Exp                                     {output::printProductionRule(34);};
Exp: Exp BINOP_ADD Exp                                                      {};
Exp: Exp BINOP_MUL Exp                                                      {};
Exp: ID                                                                     {output::printProductionRule(36);};
Exp: Call                                                                   {output::printProductionRule(37);};
Exp: NUM                                                                    {output::printProductionRule(38);};
Exp: NUM B                                                                  {output::printProductionRule(39);};
Exp: STRING                                                                 {output::printProductionRule(40);};
Exp: TRUE                                                                   {output::printProductionRule(41);};
Exp: FALSE                                                                  {output::printProductionRule(42);};
Exp: NOT Exp                                                                {output::printProductionRule(43);};
Exp: Exp AND Exp                                                            {output::printProductionRule(44);};
Exp: Exp OR Exp                                                             {};
Exp: Exp RELOP Exp                                                          {};
Exp: Exp EQUALITY Exp                                                       {};
Exp: LPAREN Type RPAREN Exp                                                 {};
%%

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



