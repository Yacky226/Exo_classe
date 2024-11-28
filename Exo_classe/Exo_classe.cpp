#include <iostream>
#include "TraiteString.h"

int main() {
    try {
        // Demande à l'utilisateur d'entrer une expression mathématique
        std::string expression,str;
       // std::cout << "Entrez une expression mathematique : ";
      //  std::getline(std::cin, expression);
        expression = "((15+4)+6/3)";
        str = "bonnob";
        TraiteString St(expression) ,St1(str);
        /*if (St.Isvalid())
        {
            std::cout << "expression valide" << std::endl;
        }
        else
            std::cout << "expression invalide" << std::endl;*/
        std::cout << "le resultat de " << expression <<" est "<<St.calculatrice()<< std::endl;
       

        std::cout << "Renverse: " << St1.reverse();
        if (St1.palindrome())
            std::cout << "Le mot  " << str << "est un palindrome " << std::endl; 
        // Création de l'objet TraiteString
        //TraiteString calculatrice(expression);

        // Calcul et affichage du résultat
      ////  int resultat = calculatrice.calculatrice();
      //  std::cout << "Le resultat de l'expression est : " << resultat << std::endl;

    }
    catch (const std::exception& e) {
        // Gestion des erreurs (ex. syntaxe invalide, division par zéro)
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
