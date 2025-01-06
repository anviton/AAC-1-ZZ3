# Problème du postier chinois

Le problème du postier chinois est un problème de théorie des graphes.

L'objectif est de **trouver le chemin le plus court dans un fraphe qui passe par toutes les arêtes au moins une fois et revient au point de départ**.

![alt text](image.png)

Les étapes de l'algorithme sont les suivantes :

1. **Vérifier les sommets de degré impair**

Le degré (ou valence) d'un sommet d'un graphe est le nombre de liens (arêtes ou arcs) reliant ce sommet, avec les boucles comptées deux fois.

Si des sommets ont un degré impair, on ne peut pas parcourir le graphe en respectant la contrainte de passer exactement une fois par chaque arête.

2. **Equilibrer les sommets impairs**

Si le graphe contient des sommets impairs, il faut les "équilibrer" en ajoutant des arêtes fictives. Pour cela, on connecte les sommets impairs entre eux par des chemins les plus court. 

Cela permet de créer un graphe eulérien où il est possible de trouver un circuit couvrant toutes les arêtes.


3. **Trouver un circuit eulérien**

Lorsque le graphe ne contient que des sommets de degré pair, il est eulérien.

Le circuit eulérien garantit que toutes les arêtes du graphe sont parcourues exactement une fois et que le chemin respecte la contrainte de passer par les routes au moins une fois.

Il suffit donc de connecter ces sommets de manière optimale, en minimisant la longueur des arêtes ajoutées.

