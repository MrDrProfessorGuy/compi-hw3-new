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