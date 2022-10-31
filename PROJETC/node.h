//
// Created by Teij Jayantilal on 24/10/2022.
#include <stdio.h>
#include <stdlib.h>
#ifndef PROJETC_NODE_H
#define PROJETC_NODE_H
//Structure de tableaux pour les nœuds
#define ALPHABET_SIZE 26
typedef struct s_letter_node
{
char letter;
struct s_letter_node * sons [ALPHABET_SIZE] ;
} t_letter_node, *p_letter_node ;
#endif //PROJETC_NODE_H
