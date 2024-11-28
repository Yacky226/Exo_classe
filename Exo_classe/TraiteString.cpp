#include "TraiteString.h"
#include "pch.h" //la pile
#include <iostream>
#include <string>
#include <stdexcept> // Pour la gestion des exceptions

// Constructeur qui initialise l'expression et l'itérateur
TraiteString::TraiteString(std::string exp) : expr(exp), expr_index(expr.begin()) {}

//Renverse une chaine de caractère à l'aide d'une pile
std::string TraiteString::reverse()
{
     Stack<char>P;
    int i = 0;
    std::string ch;

    //Parcourir chaque caractère de la chaine et les push
    while (expr_index !=expr.end())
    {
        P.push(*expr_index);
        expr_index++;
    }
    //remettre les caractères dans une nouvelle chaine
    while (!P.is_empty())
    {
        ch.push_back(P.top());
        P.pop();
    }
    return ch;
}

//Verifie si une chaine est un palindrome

bool TraiteString::palindrome()
{
    // Déclaration de l'itérateur
    std::string::iterator it2 = expr.end();

    // Réduction de it2 pour pointer sur le dernier élément valide
    --it2;

    // Parcourir la chaîne en comparant les caractères
    while (expr_index < it2) 
    {
        if (*expr_index != *it2) // Comparaison des caractères pointés par les iterateurs
            return false;
        ++expr_index; // Avancer le premier itérateur
        --it2; // Reculer le deuxième itérateur
    }

    return true;
}

// Méthode pour vérifier si un caractère est un opérateur mathématique
bool TraiteString::isoperateur(char c) const 
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Méthode pour déterminer la priorité des opérateurs
int TraiteString::priorite(char c) const 
{
    if (c == '*' || c == '/') return 2; // Multiplication et division ont la priorité la plus élevée
    if (c == '+' || c == '-') return 1; // Addition et soustraction ont une priorité moyenne
    if (c == '(') return 0;             // Les parenthèses ouvrantes ont la priorité la plus faible
    throw std::logic_error("Symbole non reconnu"); // Exception pour tout autre caractère
}

// Méthode pour effectuer un calcul entre deux opérandes en fonction de l'opérateur
int TraiteString::calcul(int op1, int op2, char opr) 
{
    switch (opr) 
    {
        case '+': return op1 + op2; // Addition
        case '-': return op1 - op2; // Soustraction
        case '*': return op1 * op2; // Multiplication
        case '/':                   // Division
            if (op2 == 0) throw std::logic_error("Division par zero");
            return op1 / op2;
        default:
            throw std::logic_error("Operateur inconnu");
    }
}

// Méthode pour vérifier si l'expression est valide et la convertir en notation postfixée
bool TraiteString::Isvalid() 
{
    Stack<char> stack; // Pile pour les opérateurs
    std::string output; // Résultat en notation postfixée

    // Parcours de l'expression
    while (expr_index != expr.end())
    {
        if (isspace(*expr_index)) 
        { // Ignorer les espaces
            expr_index++;
            continue;
        }

        if (isdigit(*expr_index))
        { // Si le caractère est un chiffre
            while (isdigit(*expr_index)) 
            {
                output += *expr_index++; // Ajouter le chiffre à la sortie
                if (expr_index == expr.end()) break;//Pour ne pas depasser la limite d'iteration
            }
            output += ' '; //  un espace pour séparer les opérandes
        }
        else
            if (*expr_index == '(') 
            {      // Si le caractère est une parenthèse ouvrante
                   stack.push(*expr_index++); // Pousser sur la pile
            }
            else
                if (*expr_index == ')') 
                { // Si le caractère est une parenthèse fermante
                    while (!stack.is_empty() && stack.top() != '(') 
                    { // Dépiler jusqu'à la parenthèse ouvrante
                        output += stack.top();
                        output += ' ';
                        stack.pop();
                    }
                    if (stack.is_empty()) 
                    throw std::logic_error("Parenthese fermante sans correspondance");
                    stack.pop(); // Retirer la parenthèse ouvrante de la pile
                    expr_index++;
                }
                else
                    if (isoperateur(*expr_index)) 
                    { // Si le caractère est un opérateur
                        while (!stack.is_empty() && priorite(stack.top()) >= priorite(*expr_index)) 
                        {
                            output += stack.top();
                            output += ' ';
                            stack.pop();
                        }
                         stack.push(*expr_index++); // Pousser l'opérateur sur la pile
                    }
                    else
                    {
                         throw std::logic_error("Caractere invalide dans l'expression");
                    }
    }

    // Dépiler les opérateurs restants
    while (!stack.is_empty()) 
    {
        if (stack.top() == '(') throw std::logic_error("Parenthese ouvrante sans correspondance");
        output += stack.top();
        output += ' ';
        stack.pop();
    }

    expr = output; // Mettre à jour l'expression avec la notation postfixée
    expr_index = expr.begin(); // Réinitialiser l'itérateur
    return true;
}

// Méthode pour calculer la valeur de l'expression postfixée
int TraiteString::calculatrice() 
{
    if (!Isvalid()) 
    { // Valider et convertir l'expression
        throw std::logic_error("Expression mathematique invalide");
    }

    Stack<int> Pile; // Pile pour stocker les opérandes
    std::string token; // Pour accumuler les nombres multi-chiffres

    // Parcours de l'expression postfixée
    while (expr_index != expr.end()) 
    {
        if (isspace(*expr_index))
        { // Ignorer les espaces
            expr_index++;
            continue;
        }

        if (isdigit(*expr_index)) 
        { // Si le caractère est un chiffre
            token.clear(); // Réinitialiser le token
            while (isdigit(*expr_index)) 
            {
                token += *expr_index++;
                if (expr_index == expr.end()) break;
            }
            Pile.push(std::stoi(token)); // Convertir le nombre et le pousser sur la pile
        }
        else 
            if (isoperateur(*expr_index))
            { // Si le caractère est un opérateur
                if (Pile.size() < 2) throw std::logic_error("Pas assez d'operandes");
                int op2 = Pile.top(); Pile.pop(); // Extraire les deux opérandes
                int op1 = Pile.top(); Pile.pop();
                Pile.push(calcul(op1, op2, *expr_index++)); // Calculer et pousser le résultat
            }
            else 
            {
                 throw std::logic_error("Caractere invalide dans l'expression");
            }
    }

    if (Pile.size() != 1) 
    { // À la fin, il doit rester exactement un élément dans la pile
        throw std::logic_error("Syntaxe invalide");
    }

    return Pile.top(); // Retourner le résultat
}
