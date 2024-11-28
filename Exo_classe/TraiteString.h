#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class TraiteString {
private:
    std::string expr;                       // Expression 
    std::string::iterator expr_index;       // Iterateur pour parcourir l'expression

public:
    TraiteString(std::string exp); // Constructeur
    std::string reverse();                   // renverse une chaine de caract�re et la retourne
    bool palindrome();                      //Verifie si une chaine un palindrome
    bool isoperateur(char c) const;         // V�rifie si un caract�re est un op�rateur
    int priorite(char c) const;             // Retourne la priorit� d'un op�rateur
    int calcul(int op1, int op2, char opr); // Effectue un calcul bas� sur l'op�rateur
    bool Isvalid();                         // V�rifie si l'expression est valide et la convertit
    int calculatrice();                     // �value l'expression convertie
};
