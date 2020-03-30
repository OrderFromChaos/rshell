#include "token.h"
#include "../rshellutils.h"

std::string Token::stringify() { 
    return joinVector(content, ' '); 
}
