#include <iostream>
#include "hw3_output.hpp"
#include <sstream>



using namespace std;


const std::string output::rules[] = {
        "Program -> Funcs",
        "Funcs -> epsilon",
        "Funcs -> FuncDecl Funcs",
        "FuncDecl -> RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE",
        "RetType -> Type",
        "RetType ->  VOID",
        "Formals -> epsilon",
        "Formals -> FormalsList",
        "FormalsList -> FormalDecl",
        "FormalsList -> FormalDecl COMMA FormalsList",
        "FormalDecl -> Type ID",
        "Statements -> Statement",
        "Statements -> Statements Statement",
        "Statement -> LBRACE Statements RBRACE",
        "Statement -> Type ID SC",
        "Statement -> Type ID ASSIGN Exp SC",
        "Statement -> ID ASSIGN Exp SC",
        "Statement -> Call SC",
        "Statement -> RETURN SC",
        "Statement -> RETURN Exp SC",
        "Statement -> IF LPAREN Exp RPAREN Statement",
        "Statement -> IF LPAREN Exp RPAREN Statement ELSE Statement",
        "Statement -> WHILE LPAREN Exp RPAREN Statement",
        "Statement -> BREAK SC",
        "Statement -> CONTINUE SC",
        "Call -> ID LPAREN ExpList RPAREN",
        "Call -> ID LPAREN RPAREN",
        "ExpList -> Exp",
        "ExpList -> Exp COMMA ExpList",
        "Type -> INT",
        "Type -> BYTE",
        "Type -> BOOL",
        "Exp -> LPAREN Exp RPAREN",
        "Exp -> Exp BINOP Exp",
        "Exp -> ID",
        "Exp -> Call",
        "Exp -> NUM",
        "Exp -> NUM B",
        "Exp -> STRING",
        "Exp -> TRUE",
        "Exp -> FALSE",
        "Exp -> NOT Exp",
        "Exp -> Exp AND Exp",
        "Exp -> Exp OR Exp",
        "Exp -> Exp RELOP Exp",
        "Exp -> LPAREN Type RPAREN Exp"
};

void output::printProductionRule(const int ruleno) {
    std::cout << ruleno << ": " << output::rules[ruleno-1] << "\n";
}



Frame_class frame_manager;

Frame_class& Frame_class::getInstance() {
    return frame_manager;
}


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


bool valid_cast(Type to, Type from){
    if (from == to){
        return true;
    }
    if (to == Type::INT || to == Type::BYTE){
        if (from == Type::INT || from == Type::BYTE){
            return true;
        }
    }
    return false;
}

bool valid_implicit_cast(Type to, Type from) {
    if (to == from) {
        return true;
    }
    if (to == Type::INT && from == Type::BYTE) {
        return true;
    }
    return false;
}


/// ############################################################################## ///
/// ############################    Symbol    ############################///
/// ############################################################################## ///



/// ############################################################################## ///
/// ############################    symTableEntryID    ############################///
/// ############################################################################## ///

void symTableEntryID::print() const{
    output::printID(symbol.name, offset, TypeToSTR(symbol.type));
}

void symTableEntryFunc::print() const{
    std::vector<string> a = typeToStrVector(paramsToTypeVec());
    cout << symbol.name << " " << output::makeFunctionType(TypeToSTR(symbol.type),a);
}

/// ############################################################################## ///
/// ############################    Node_ExpList    ############################///
/// ############################################################################## ///

Node_ExpList::Node_ExpList(Node_Exp* exp) : Generic_Node({exp}){
    exp_list.clear();
    exp_list.push_back(exp->type);
}

Node_ExpList::Node_ExpList(Node_Exp* node_exp, Node_Token* node_token,
                           Node_ExpList* node_expList): Generic_Node({node_exp, node_token, node_expList}) {
    exp_list = node_expList->exp_list;
    exp_list.insert(exp_list.begin(), node_exp->type);
}


/// ############################################################################## ///
/// ############################    Node_FormalDecl    ############################///
/// ############################################################################## ///

Node_FormalDecl::Node_FormalDecl(Node_Exp_Type* node_type, Node_Token* node_token_id)
                : Generic_Node({node_type, node_token_id}), id_symbol(node_type->type, node_token_id->value){
    if (frame_manager.find(id_symbol.name) != nullptr){
        output::errorDef(yylineno, id_symbol.name);
        exit(0);
    }
}


/// ############################################################################## ///
/// ############################    Node_FormalsList    ############################///
/// ############################################################################## ///

Node_FormalsList::Node_FormalsList(Node_FormalDecl* node_formalDecl): Generic_Node({node_formalDecl}) {
    parameter_list.emplace_back(node_formalDecl->id_symbol);
}

Node_FormalsList::Node_FormalsList(Node_FormalDecl* node_formalDecl,
                                   Node_Token* node_comma, Node_FormalsList* node_formalsList)
                                   : Generic_Node({node_formalDecl, node_comma, node_formalsList}) {
    parameter_list = node_formalsList->parameter_list;
    parameter_list.insert(parameter_list.begin(), node_formalDecl->id_symbol);
}

/// ############################################################################## ///
/// ############################    Node_Exp_ID    ############################///
/// ############################################################################## ///

Node_Exp_ID::Node_Exp_ID(Node_Token* node_token) : Node_Exp(children, Type::INVALID), id(Symbol::invalidSymbol()) {
    auto node_token_id = (Node_Token*)(children[0]);
    auto entry = std::dynamic_pointer_cast<symTableEntryID>(frame_manager.find(node_token_id->value));
    if (!entry->valid) {
        throw UndefExc(yylineno, node_token_id->value);
    }
    set_type(entry->symbol.type);
    id = entry->symbol;
    
}


/// ############################################################################## ///
/// ############################    Node_Call    ############################///
/// ############################################################################## ///

Node_Call::Node_Call(Node_Token* node_id, Node_Token* node_lparen,
                     Node_ExpList* node_expList, Node_Token* node_rparen)
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

Node_Statement_ID_Decl::Node_Statement_ID_Decl(Node_Exp *node_type,
                                               Node_Token* node_token,
                                               Node_Token* node_sc)
                                               : Node_Statement({node_type, node_token, node_sc}) {
    frame_manager.newEntry(DeclType::VAR, node_token->value, node_type->type);
}

Node_Statement_ID_Decl::Node_Statement_ID_Decl(Node_Exp* node_type,
                                               Node_Token* node_token,
                                               Node_Token* node_assign,
                                               Node_Exp* node_exp,
                                               Node_Token* node_sc)
                                               : Node_Statement({node_type, node_token, node_assign, node_exp, node_sc}) {
    
    Node_Exp_Type* node_type_p = dynamic_cast<Node_Exp_Type*>(node_type);
    frame_manager.newEntry(DeclType::VAR, node_token->value, node_type_p->type);
    
    if (!valid_implicit_cast(node_type_p->type, node_exp->type)){
        //frame_manager.removeEntryFromCurrentScope(node_token->value);
        output::errorMismatch(yylineno);
    }
    Log() << "Node_Statement_ID_Decl:: " << TypeToSTR(node_type->type) << " " << node_token->value << std::endl;
}


/// ############################################################################## ///
/// ############################    Node_Statement_ID_Assign    ############################///
/// ############################################################################## ///

Node_Statement_ID_Assign::Node_Statement_ID_Assign(Node_Token* node_id,
                                                   Node_Token* node_assign,
                                                   Node_Exp* node_exp,
                                                   Node_Token* node_sc)
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

Node_Statement_Call::Node_Statement_Call(Node_Call* node_call, Node_Token* node_sc)
                                        : Node_Statement({node_call, node_sc}){
    
    
    
}



/// ############################################################################## ///
/// ############################    Node_Statement_Ret    ############################///
/// ############################################################################## ///


Node_Statement_Ret::Node_Statement_Ret(Node_Token* node_ret, Node_Token* node_sc)
                                        : Node_Statement({node_ret, node_sc}){
    
    if (frame_manager.scopeRetType() != Type::VOID){
        throw MismatchExc(yylineno);
    }
    
}


Node_Statement_Ret::Node_Statement_Ret(Node_Token* node_ret, Node_Exp* node_exp,
                                       Node_Token* node_sc)
                                       : Node_Statement({node_ret, node_exp, node_sc}) {
    
    if (valid_implicit_cast(frame_manager.scopeRetType(), node_exp->type) == false){
        throw MismatchExc(yylineno);
    }
}

/// ############################################################################## ///
/// ############################    Node_Statement_IF    ############################///
/// ############################################################################## ///

Node_Statement_IF::Node_Statement_IF(Node_Token *node_if, Node_Token *node_lparen, Node_Exp *node_exp,
                                     Node_Token *node_rparen, Node_Statement *node_statement)
                                     : Node_Statement({node_if, node_lparen, node_exp, node_rparen, node_statement}){
    
    if (node_exp->typeCheck({Type::BOOL}) == false){
        throw MismatchExc(yylineno);
    }
}

Node_Statement_IF::Node_Statement_IF(Node_Token *node_if, Node_Token *node_lparen, Node_Exp *node_exp,
                                     Node_Token *node_rparen, Node_Statement *node_statement1, Node_Token *node_else,
                                     Node_Statement *node_statement2)
                                     :  Node_Statement({node_if, node_lparen, node_exp, node_rparen, node_statement1, node_else, node_statement2}){
    
    if (node_exp->typeCheck({Type::BOOL}) == false){
        throw MismatchExc(yylineno);
    }
}

/// ############################################################################## ///
/// ############################    Node_Statement_While    ############################///
/// ############################################################################## ///

Node_Statement_While::Node_Statement_While(Node_Token* node_while,
                                           Node_Token* node_lparen, Node_Exp* node_exp,
                                           Node_Token* node_rparen,
                                           Node_Statement* node_statement)
                                           : Node_Statement({node_while, node_lparen, node_exp, node_rparen, node_statement}) {
    
    if (node_exp->typeCheck({Type::BOOL}) == false){
        throw MismatchExc(yylineno);
    }
}


/// ############################################################################## ///
/// ############################    Node_Statement_LoopMod    ############################///
/// ############################################################################## ///

Node_Statement_LoopMod::Node_Statement_LoopMod(Node_Token* node_loop_mod, Node_Token* node_sc)
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

Node_FuncDecl::Node_FuncDecl(Node_Exp_Type* node_retType, Node_Token* node_id,
                             Node_Token* node_lparen, Node_FormalsList* node_formals,
                             Node_Token* node_rparen, Node_Token* node_lbrace,
                             Node_Statement* node_statement, Node_Token* node_rbrace)
                             : Generic_Node({node_retType, node_id, node_lparen, node_formals, node_rparen, node_lbrace, node_statement, node_rbrace}){
    
    
}




















