#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class TraiteString {
private:
    std::string expr;                       // Expression mathématique à traiter
    std::string::iterator expr_index;       // Iterateur pour parcourir l'expression

public:
    TraiteString(std::string exp); // Constructeur
    std::string reverse();
    bool palindrome();
    bool isoperateur(char c) const;         // Vérifie si un caractère est un opérateur
    int priorite(char c) const;             // Retourne la priorité d'un opérateur
    int calcul(int op1, int op2, char opr); // Effectue un calcul basé sur l'opérateur
    bool Isvalid();                         // Vérifie si l'expression est valide et la convertit
    int calculatrice();                     // Évalue l'expression convertie
};
