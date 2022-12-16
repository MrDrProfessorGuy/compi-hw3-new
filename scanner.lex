%{

/* Declarations section */
#include <stdio.h>
#include "parser.tab.hpp"
#include "hw3_output.hpp"
#include "iostream"
//printf("FLEX:: %d: %s\n", yylineno, yytext);
//#define newToken(token_type) token_value = yytext;return token_type;
#define newToken(token_type) token_value = yytext;return token_type;
#define Comment token_value = "\\\\"; return COMMENT;

using namespace std;

std::string token_value;

std::string tokentype_str[] = {"TEST", "VOID", "INT", "BYTE",
                 "B", "BOOL", "AND", "OR", 
                 "NOT", "TRUE", "FALSE", "RETURN", 
                 "IF", "ELSE", "WHILE", "BREAK", 
                 "CONTINUE", "SC", "COMMA", "LPAREN", 
                 "RPAREN", "LBRACE", "RBRACE", "ASSIGN", 
                 "RELOP", "BINOP", "COMMENT", "ID", 
                 "NUM", "STRING"}; 

void showToken(char* token_name);
void newString(char* token_name);
void printString(char* token_name);
void appendString(int token_name);
void str_es(int escapeSequence_type);


//int newToken(int token_type);

//token_illegal   ("{printable}*\\[{printable}*-[n|r|t|0|x{hexa}{hexa}]]"|"{printable}*"{printable}+|"\\n"|"\\r")
//token_string    ("[{printable}*-[{token_illegal}]]")


%}

%option yylineno
%option noyywrap


digit   		([0-9])
hexa            ([0-9A-Fa-f])
letter  		([a-zA-Z])
alphanumeric    ([a-zA-Z0-9])
whitespace		([\t\n\r ])

token_void      (void)
token_int       (int)
token_byte      (byte)
token_b         (b)
token_bool      (bool)
token_and       (and)
token_or        (or)
token_not       (not)
token_true      (true)
token_false     (false)
token_return    (return)
token_if        (if)
token_else      (else)
token_while     (while)
token_break     (break)
token_continue  (continue)
token_sc        (;)
token_comma     (,)
token_lparen    (\()
token_rparen    (\))
token_lbrace    (\{)
token_rbrace    (\})
token_assign    (=)
token_equeality    (==|!=)
token_relop     (<|>|<=|>=)
token_binop_mul     (\*|\/)
token_binop_add    (\+|\-)
token_comment   (\/\/[^\r\n]*[\r|\n|\r\n]?)
token_id        ([a-zA-Z][a-zA-Z0-9]*)
token_num       (0|[1-9]{digit}*)
token_string    (\"([^\n\r\"\\]|\\[rnt"\\])+\")



%%

{token_void}      yylval.NodeToken = (new Node_Token(yytext));
{token_int}       yylval.NodeToken = (new Node_Token(yytext));
{token_byte}      yylval.NodeToken = (new Node_Token(yytext));
{token_b}         yylval.NodeToken = (new Node_Token(yytext));
{token_bool}      yylval.NodeToken = (new Node_Token(yytext));
{token_and}       yylval.NodeToken = (new Node_Token(yytext));
{token_or}        yylval.NodeToken = (new Node_Token(yytext));
{token_not}       yylval.NodeToken = (new Node_Token(yytext));
{token_true}      yylval.NodeToken = (new Node_Token(yytext));
{token_false}     yylval.NodeToken = (new Node_Token(yytext));
{token_return}    yylval.NodeToken = (new Node_Token(yytext));
{token_if}        yylval.NodeToken = (new Node_Token(yytext));
{token_else}      yylval.NodeToken = (new Node_Token(yytext));
{token_while}     yylval.NodeToken = (new Node_Token(yytext));
{token_break}     yylval.NodeToken = (new Node_Token(yytext));
{token_continue}  yylval.NodeToken = (new Node_Token(yytext));
{token_sc}        yylval.NodeToken = (new Node_Token(yytext));
{token_lparen}    yylval.NodeToken = (new Node_Token(yytext));
{token_rparen}    yylval.NodeToken = (new Node_Token(yytext));
{token_lbrace}    yylval.NodeToken = (new Node_Token(yytext));
{token_rbrace}    yylval.NodeToken = (new Node_Token(yytext));
{token_assign}    yylval.NodeToken = (new Node_Token(yytext));
{token_relop}     yylval.NodeToken = (new Node_Token(yytext));
{token_equeality}    yylval.NodeToken = (new Node_Token(yytext));
{token_binop_add}     yylval.NodeToken = (new Node_Token(yytext));
{token_binop_mul}     yylval.NodeToken = (new Node_Token(yytext));

{token_id}        yylval.NodeToken = (new Node_Token(yytext));
{token_num}       yylval.NodeToken = (new Node_Token(yytext));
{token_string}    yylval.NodeToken = (new Node_Token(yytext));

{token_comment}              ;
{whitespace}                 ;
.		output::errorLex(yylineno);exit(0);


%%

