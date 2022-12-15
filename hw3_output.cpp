#include <iostream>
#include "hw3_output.hpp"
#include <sstream>

using namespace std;

void output::endScope(){
    cout << "---end scope---" << endl;
}

void output::printID(const string& id, int offset, const string& type) {
    cout << id << " " << type <<  " " << offset <<  endl;
}

string typeListToString(const std::vector<string>& argTypes) {
    stringstream res;
    res << "(";
    for(int i = 0; i < argTypes.size(); ++i) {
        res << argTypes[i];
        if (i + 1 < argTypes.size())
            res << ",";
    }
    res << ")";
    return res.str();
}

string valueListsToString(const std::vector<string>& values) {
    stringstream res;
    res << "{";
    for(int i = 0; i < values.size(); ++i) {
        res << values[i];
        if (i + 1 < values.size())
            res << ",";
    }
    res << "}";
    return res.str();
}

string output::makeFunctionType(const string& retType, std::vector<string>& argTypes) {
    stringstream res;
    res << typeListToString(argTypes) << "->" << retType;
    return res.str();
}

void output::errorLex(int lineno){
    cout << "line " << lineno << ":" << " lexical error" << endl;
}

void output::errorSyn(int lineno){
    cout << "line " << lineno << ":" << " syntax error" << endl;
}

void output::errorUndef(int lineno, const string& id){
    cout << "line " << lineno << ":" << " variable " << id << " is not defined" << endl;
}

void output::errorDef(int lineno, const string& id){
    cout << "line " << lineno << ":" << " identifier " << id << " is already defined" << endl;
}

void output::errorUndefFunc(int lineno, const string& id) {
    cout << "line " << lineno << ":" << " function " << id << " is not defined" << endl;
}

void output::errorMismatch(int lineno){
    cout << "line " << lineno << ":" << " type mismatch" << endl;
}

void output::errorPrototypeMismatch(int lineno, const string& id, std::vector<string>& argTypes) {
    cout << "line " << lineno << ": prototype mismatch, function " << id << " expects arguments " << typeListToString(argTypes) << endl;
}

void output::errorUnexpectedBreak(int lineno) {
    cout << "line " << lineno << ":" << " unexpected break statement" << endl;
}

void output::errorUnexpectedContinue(int lineno) {
    cout << "line " << lineno << ":" << " unexpected continue statement" << endl;	
}

void output::errorMainMissing() {
    cout << "Program has no 'void main()' function" << endl;
}

void output::errorByteTooLarge(int lineno, const string& value) {
    cout << "line " << lineno << ": byte value " << value << " out of range" << endl;
}


/// ############################################################################## ///
/// ############################    Node_ExpList    ############################///
/// ############################################################################## ///

Node_ExpList::Node_ExpList(std::shared_ptr<Node_Exp> exp) : Generic_Node({exp}){
    exp_list.clear();
    exp_list.push_back(exp->type);
}

Node_ExpList::Node_ExpList(std::shared_ptr<Node_Exp> node_exp, std::shared_ptr<Node_Token> node_token,
                           std::shared_ptr<Node_ExpList> node_expList): Generic_Node({node_exp, node_token, node_expList}) {
    exp_list = node_expList->exp_list;
    exp_list.insert(exp_list.begin(), node_exp->type);
}


/// ############################################################################## ///
/// ############################    Node_FormalDecl    ############################///
/// ############################################################################## ///

Node_FormalDecl::Node_FormalDecl(std::shared_ptr<Node_Exp_Type> node_type, std::shared_ptr<Node_Token> node_token_id)
                : Generic_Node({node_type, node_token_id}), id_symbol(node_type->type, node_token_id->value){
    if (frame_manager.find(id_symbol.name) != nullptr){
        output::errorDef(yylineno, id_symbol.name);
        exit(0);
    }
}


/// ############################################################################## ///
/// ############################    Node_FormalsList    ############################///
/// ############################################################################## ///

Node_FormalsList::Node_FormalsList(std::shared_ptr<Node_FormalDecl> node_formalDecl): Generic_Node({node_formalDecl}) {
    parameter_list.emplace_back(node_formalDecl->id_symbol);
}

Node_FormalsList::Node_FormalsList(std::shared_ptr<Node_FormalDecl> node_formalDecl,
                                   std::shared_ptr<Node_Token> node_comma, std::shared_ptr<Node_FormalsList> node_formalsList)
                                   : Generic_Node({node_formalDecl, node_comma, node_formalsList}) {
    parameter_list = node_formalsList->parameter_list;
    parameter_list.insert(parameter_list.begin(), node_formalDecl->id_symbol);
}

/// ############################################################################## ///
/// ############################    Node_Call    ############################///
/// ############################################################################## ///

Node_Call::Node_Call(std::shared_ptr<Node_Token> node_id, std::shared_ptr<Node_Token> node_lparen,
                     std::shared_ptr<Node_ExpList> node_expList, std::shared_ptr<Node_Token> node_rparen)
                     : Generic_Node({node_id, node_lparen, node_expList, node_rparen}), func_id(Symbol::invalidSymbol()){
    // check if func declared
    auto id_entry = frame_manager.find(node_id->value);
    if (id_entry == nullptr || id_entry->entry_type != DeclType::FUNC){
        throw UndDefFuncExc(yylineno, node_id->value);
    }
    func_id = Symbol(id_entry->symbol.type, id_entry->symbol.name);
    func_parameters = node_expList->exp_list;
    // check if func prototype matches func call
    auto func_entry = std::dynamic_pointer_cast<symTableEntryFunc>(id_entry);
    if (func_entry->parameter_list.size() != func_parameters.size()){
        throw PrototypeMismatchExc(yylineno, func_id.name, func_parameters);
    }
    for (int index = 0; index < func_entry->parameter_list.size(); index++){
        if (!valid_cast(func_entry->parameter_list[index].type, func_parameters[index])){
            throw PrototypeMismatchExc(yylineno, func_id.name, func_parameters);
        }
    }
    
}




/// ############################################################################## ///
/// ############################    Node_Statement    ############################///
/// ############################################################################## ///

Node_Statement::Node_Statement(NodeVector children): Generic_Node(children) {

}

/// ############################################################################## ///
/// ############################    Node_Statement_ID_Decl    ############################///
/// ############################################################################## ///

Node_Statement_ID_Decl::Node_Statement_ID_Decl(std::shared_ptr<Node_Exp_Type> node_type,
                                               std::shared_ptr<Node_Token> node_token,
                                               std::shared_ptr<Node_Token> node_sc)
                                               : Node_Statement({node_type, node_token, node_sc}) {
    frame_manager.newEntry(DeclType::VAR, node_token->value, node_type->type);
}

Node_Statement_ID_Decl::Node_Statement_ID_Decl(std::shared_ptr<Node_Exp_Type> node_type,
                                               std::shared_ptr<Node_Token> node_token,
                                               std::shared_ptr<Node_Token> node_assign,
                                               std::shared_ptr<Node_Exp> node_exp,
                                               std::shared_ptr<Node_Token> node_sc)
                                               : Node_Statement({node_type, node_token, node_assign, node_exp, node_sc}) {
    
    frame_manager.newEntry(DeclType::VAR, node_token->value, node_type->type);
    
    if (!valid_implicit_cast(node_type->type, node_exp->type)){
        frame_manager.removeEntryFromCurrentScope(node_token->value);
        output::errorMismatch(yylineno);
    }
}


/// ############################################################################## ///
/// ############################    Node_Statement_ID_Assign    ############################///
/// ############################################################################## ///

Node_Statement_ID_Assign::Node_Statement_ID_Assign(std::shared_ptr<Node_Token> node_id,
                                                   std::shared_ptr<Node_Token> node_assign,
                                                   std::shared_ptr<Node_Exp> node_exp,
                                                   std::shared_ptr<Node_Token> node_sc)
                                                   : Node_Statement({node_id, node_assign, node_exp, node_sc}) {
    
    auto id_entry = frame_manager.find(node_id->value);
    if (id_entry == nullptr){
        throw UndefExc(yylineno, node_id->value);
    }
    
    if (!valid_implicit_cast(id_entry->symbol.type, node_exp->type)){
        throw MismatchExc(yylineno);
    }
    
}


/// ############################################################################## ///
/// ############################    Node_Statement_Call    ############################///
/// ############################################################################## ///

Node_Statement_Call::Node_Statement_Call(std::shared_ptr<Node_Call> node_call, std::shared_ptr<Node_Token> node_sc)
                                        : Node_Statement({node_call, node_sc}){
    
    
    
}



/// ############################################################################## ///
/// ############################    Node_Statement_Ret    ############################///
/// ############################################################################## ///


Node_Statement_Ret::Node_Statement_Ret(std::shared_ptr<Node_Token> node_ret, std::shared_ptr<Node_Token> node_sc)
                                        : Node_Statement({node_ret, node_sc}){
    
    if (frame_manager.scopeRetType() != Type::VOID){
        throw MismatchExc(yylineno);
    }
    
}


Node_Statement_Ret::Node_Statement_Ret(std::shared_ptr<Node_Token> node_ret, std::shared_ptr<Node_Exp> node_exp,
                                       std::shared_ptr<Node_Token> node_sc)
                                       : Node_Statement({node_ret, node_exp, node_sc}) {
    
    if (valid_implicit_cast(frame_manager.scopeRetType(), node_exp->type) == false){
        throw MismatchExc(yylineno);
    }
}

/// ############################################################################## ///
/// ############################    Node_Statement_IF    ############################///
/// ############################################################################## ///

Node_Statement_IF::Node_Statement_IF(std::shared_ptr<Node_Token> node_if, std::shared_ptr<Node_Token> node_lparen,
                                     std::shared_ptr<Node_Exp> node_exp, std::shared_ptr<Node_Token> node_rparen,
                                     std::shared_ptr<Node_Statement> node_statement)
                                     : Node_Statement({node_if, node_lparen, node_exp, node_rparen, node_statement}){
    
    if (node_exp->typeCheck({Type::BOOL}) == false){
        throw MismatchExc(yylineno);
    }
}


Node_Statement_IF::Node_Statement_IF(std::shared_ptr<Node_Token> node_if, std::shared_ptr<Node_Token> node_lparen,
                                     std::shared_ptr<Node_Exp> node_exp, std::shared_ptr<Node_Token> node_rparen,
                                     std::shared_ptr<Node_Statement> node_statement1,
                                     std::shared_ptr<Node_Token> node_else,
                                     std::shared_ptr<Node_Statement> node_statement2)
                                     :  Node_Statement({node_if, node_lparen, node_exp, node_rparen, node_statement1, node_else, node_statement2}){
    if (node_exp->typeCheck({Type::BOOL}) == false){
        throw MismatchExc(yylineno);
    }
}


/// ############################################################################## ///
/// ############################    Node_Statement_While    ############################///
/// ############################################################################## ///

Node_Statement_While::Node_Statement_While(std::shared_ptr<Node_Token> node_while,
                                           std::shared_ptr<Node_Token> node_lparen, std::shared_ptr<Node_Exp> node_exp,
                                           std::shared_ptr<Node_Token> node_rparen,
                                           std::shared_ptr<Node_Statement> node_statement)
                                           : Node_Statement({node_while, node_lparen, node_exp, node_rparen, node_statement}) {
    
    if (node_exp->typeCheck({Type::BOOL}) == false){
        throw MismatchExc(yylineno);
    }
}


/// ############################################################################## ///
/// ############################    Node_Statement_LoopMod    ############################///
/// ############################################################################## ///

Node_Statement_LoopMod::Node_Statement_LoopMod(std::shared_ptr<Node_Token> node_loop_mod, std::shared_ptr<Node_Token> node_sc)
                                                : Node_Statement({node_loop_mod, node_sc}){
    
    
    if (!frame_manager.inLoop()){
        if (node_loop_mod->value == "break"){
            throw UnexpectedBreakExc(yylineno);
        }
        throw UnexpectedContinueExc(yylineno);
    }
}


/// ############################################################################## ///
/// ############################    Node_FuncDecl    ############################///
/// ############################################################################## ///

Node_FuncDecl::Node_FuncDecl(std::shared_ptr<Node_Exp_Type> node_retType, std::shared_ptr<Node_Token> node_id,
                             std::shared_ptr<Node_Token> node_lparen, std::shared_ptr<Node_FormalsList> node_formals,
                             std::shared_ptr<Node_Token> node_rparen, std::shared_ptr<Node_Token> node_lbrace,
                             std::shared_ptr<Node_Statement> node_statement, std::shared_ptr<Node_Token> node_rbrace)
                             : Generic_Node({node_retType, node_id, node_lparen, node_formals, node_rparen, node_lbrace, node_statement, node_rbrace}){
    
    
}




















