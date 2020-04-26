//
//  Expression stack
//      - void ExprPush(expr):  push expr onto the stack
//      - int ExprPop():        pop and return the top of the expr stack
//      - int ExprTop():        return the top of the expr stack
//      - void ExprPut(expr):   replace the top of the expr stack with expr
//

(ExprPush)
    @SP                 // push the value onto the expr stack
    A=M-1
    D=M
    @EP
    M=M+1
    A=M
    M=D
    @SP                 // pop the return address from the stack and return
    M=M-1
    A=M+1
    A=M
    0;JMP

(ExprPop)
    @768                // check for bottom of stack
    D=A
    @EP
    D=M-D
    @ExprPop_exit
    D;JLE
    @EP                 // pop the top of the expr stack to RETVAL
    M=M-1
    A=M+1
    D=M
(ExprPop_exit)
    @RETVAL             // write the result (or 0 for bottom of stack) to RETVAL
    M=D
    @SP                 // pop the return address from the stack and return
    M=M-1
    A=M+1
    A=M
    0;JMP

(ExprTop)
    @EP                 // copy the top of the expr stack to RETVAL
    A=M
    D=M
    @RETVAL
    M=D
    @SP                 // pop the return address from the stack and return
    M=M-1
    A=M+1
    A=M
    0;JMP

(ExprPut)
    @SP                 // push the value onto the expr stack
    A=M-1
    D=M
    @EP
    A=M
    M=D
    @SP                 // pop the return address from the stack and return
    M=M-1
    A=M+1
    A=M
    0;JMP


