# ezprompt

`ezprompt` est une petite bibliothèque C qui fournit une interface simple et portable pour créer des invites (prompts) interactives avec gestion de l’historique et des touches fléchées.  
Elle a été pensée pour être intégrée facilement dans des projets tels que des minishells, REPLs ou outils en ligne de commande.

---

## Fonctionnalités

- Création d’une invite personnalisée.
- Lecture de l’entrée utilisateur caractère par caractère.
- Gestion de l’historique intégrée :
  - Chaque saisie validée est automatiquement ajoutée à l’historique.
  - Navigation avec les touches fléchées `↑` et `↓`.
- Effacement du buffer d’entrée après traitement.
- Fonctions utilitaires incluses (`ft_strdup`, `ft_strlen`, etc.).

---

## Exemple d’utilisation

Voici un exemple simple d’un mini-shell utilisant `ezprompt` :

```c
#include "ezprompt.h"
#include <stdio.h>

int main(void)
{
    t_prompt *p;

    p = calloc(1, sizeof(t_prompt));
    if (!p)
        return (1);

    if (init_prompt(p, "myshell> "))
        return (1);

    while (!p->exit_flag)
    {
        if (next_read(p))
            break;

        if (!is_empty(p->input))
        {
            printf("Vous avez tapé : %s\n", p->input);
        }

        if (clear_input(p))
            break;
    }

    free_prompt(p);
    return (0);
}
```
