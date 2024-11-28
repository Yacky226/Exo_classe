#include <iostream>
#include "TraiteString.h"

int main() {
    try
    {
      
        std::string expression,str;
        expression = "((15+4)+6/2)";
        str = "bonnob";
        TraiteString St(expression) ,St1(str);
        std::cout << "le resultat de " << expression <<" est "<<St.calculatrice()<< std::endl;
      
        std::cout << "Renverse: " << St1.reverse();
        if (St1.palindrome())
            std::cout << "Le mot  " << str << "est un palindrome " << std::endl; 
       
    }
    catch (const std::exception& e) 
    {
       
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
