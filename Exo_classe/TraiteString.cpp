#include "TraiteString.h"
#include "pch.h" //la pile
#include <iostream>
#include <string>
#include <stdexcept> // Pour la gestion des exceptions

// Constructeur qui initialise l'expression et l'it�rateur
TraiteString::TraiteString(std::string exp) : expr(exp), expr_index(expr.begin()) {}

//Renverse une chaine de caract�re � l'aide d'une pile
std::string TraiteString::reverse()
{
     Stack<char>P;
    int i = 0;
    std::string ch;

    //Parcourir chaque caract�re de la chaine et les push
    while (expr_index !=expr.end())
    {
        P.push(*expr_index);
        expr_index++;
    }
    //remettre les caract�res dans une nouvelle chaine
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
    // D�claration de l'it�rateur
    std::string::iterator it2 = expr.end();

    // R�duction de it2 pour pointer sur le dernier �l�ment valide
    --it2;

    // Parcourir la cha�ne en comparant les caract�res
    while (expr_index < it2) 
    {
        if (*expr_index != *it2) // Comparaison des caract�res point�s par les iterateurs
            return false;
        ++expr_index; // Avancer le premier it�rateur
        --it2; // Reculer le deuxi�me it�rateur
    }

    return true;
}

// M�thode pour v�rifier si un caract�re est un op�rateur math�matique
bool TraiteString::isoperateur(char c) const 
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// M�thode pour d�terminer la priorit� des op�rateurs
int TraiteString::priorite(char c) const 
{
    if (c == '*' || c == '/') return 2; // Multiplication et division ont la priorit� la plus �lev�e
    if (c == '+' || c == '-') return 1; // Addition et soustraction ont une priorit� moyenne
    if (c == '(') return 0;             // Les parenth�ses ouvrantes ont la priorit� la plus faible
    throw std::logic_error("Symbole non reconnu"); // Exception pour tout autre caract�re
}

// M�thode pour effectuer un calcul entre deux op�randes en fonction de l'op�rateur
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

// M�thode pour v�rifier si l'expression est valide et la convertir en notation postfix�e
bool TraiteString::Isvalid() 
{
    Stack<char> stack; // Pile pour les op�rateurs
    std::string output; // R�sultat en notation postfix�e

    // Parcours de l'expression
    while (expr_index != expr.end())
    {
        if (isspace(*expr_index)) 
        { // Ignorer les espaces
            expr_index++;
            continue;
        }

        if (isdigit(*expr_index))
        { // Si le caract�re est un chiffre
            while (isdigit(*expr_index)) 
            {
                output += *expr_index++; // Ajouter le chiffre � la sortie
                if (expr_index == expr.end()) break;//Pour ne pas depasser la limite d'iteration
            }
            output += ' '; //  un espace pour s�parer les op�randes
        }
        else
            if (*expr_index == '(') 
            {      // Si le caract�re est une parenth�se ouvrante
                   stack.push(*expr_index++); // Pousser sur la pile
            }
            else
                if (*expr_index == ')') 
                { // Si le caract�re est une parenth�se fermante
                    while (!stack.is_empty() && stack.top() != '(') 
                    { // D�piler jusqu'� la parenth�se ouvrante
                        output += stack.top();
                        output += ' ';
                        stack.pop();
                    }
                    if (stack.is_empty()) 
                    throw std::logic_error("Parenthese fermante sans correspondance");
                    stack.pop(); // Retirer la parenth�se ouvrante de la pile
                    expr_index++;
                }
                else
                    if (isoperateur(*expr_index)) 
                    { // Si le caract�re est un op�rateur
                        while (!stack.is_empty() && priorite(stack.top()) >= priorite(*expr_index)) 
                        {
                            output += stack.top();
                            output += ' ';
                            stack.pop();
                        }
                         stack.push(*expr_index++); // Pousser l'op�rateur sur la pile
                    }
                    else
                    {
                         throw std::logic_error("Caractere invalide dans l'expression");
                    }
    }

    // D�piler les op�rateurs restants
    while (!stack.is_empty()) 
    {
        if (stack.top() == '(') throw std::logic_error("Parenthese ouvrante sans correspondance");
        output += stack.top();
        output += ' ';
        stack.pop();
    }

    expr = output; // Mettre � jour l'expression avec la notation postfix�e
    expr_index = expr.begin(); // R�initialiser l'it�rateur
    return true;
}

// M�thode pour calculer la valeur de l'expression postfix�e
int TraiteString::calculatrice() 
{
    if (!Isvalid()) 
    { // Valider et convertir l'expression
        throw std::logic_error("Expression mathematique invalide");
    }

    Stack<int> Pile; // Pile pour stocker les op�randes
    std::string token; // Pour accumuler les nombres multi-chiffres

    // Parcours de l'expression postfix�e
    while (expr_index != expr.end()) 
    {
        if (isspace(*expr_index))
        { // Ignorer les espaces
            expr_index++;
            continue;
        }

        if (isdigit(*expr_index)) 
        { // Si le caract�re est un chiffre
            token.clear(); // R�initialiser le token
            while (isdigit(*expr_index)) 
            {
                token += *expr_index++;
                if (expr_index == expr.end()) break;
            }
            Pile.push(std::stoi(token)); // Convertir le nombre et le pousser sur la pile
        }
        else 
            if (isoperateur(*expr_index))
            { // Si le caract�re est un op�rateur
                if (Pile.size() < 2) throw std::logic_error("Pas assez d'operandes");
                int op2 = Pile.top(); Pile.pop(); // Extraire les deux op�randes
                int op1 = Pile.top(); Pile.pop();
                Pile.push(calcul(op1, op2, *expr_index++)); // Calculer et pousser le r�sultat
            }
            else 
            {
                 throw std::logic_error("Caractere invalide dans l'expression");
            }
    }

    if (Pile.size() != 1) 
    { // � la fin, il doit rester exactement un �l�ment dans la pile
        throw std::logic_error("Syntaxe invalide");
    }

    return Pile.top(); // Retourner le r�sultat
}
