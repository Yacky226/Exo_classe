#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class TraiteString {
private:
    std::string expr;                       // Expression math�matique � traiter
    std::string::iterator expr_index;       // Iterateur pour parcourir l'expression

public:
    TraiteString(std::string exp); // Constructeur
    std::string reverse();
    bool palindrome();
    bool isoperateur(char c) const;         // V�rifie si un caract�re est un op�rateur
    int priorite(char c) const;             // Retourne la priorit� d'un op�rateur
    int calcul(int op1, int op2, char opr); // Effectue un calcul bas� sur l'op�rateur
    bool Isvalid();                         // V�rifie si l'expression est valide et la convertit
    int calculatrice();                     // �value l'expression convertie
};
