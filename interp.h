//
//  interp.h
//
//
//  Created by Pierce Cunneen April 5
//
//

#include <vector>
#include "Token.h"
#include "env.h"
#include "Parser.h"

#ifndef INTERP_H
#define INTERP_H


Token* interp(ASTNode *, env *);
Token interpArithmeticExpression(ASTNode *, env *);




#endif
