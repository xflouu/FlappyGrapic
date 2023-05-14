# FlappyGrapic

FlappyGrapic est un jeu inspiré du célèbre jeu Flappy Bird. Le but du jeu est de faire voler un oiseau à travers des tuyaux sans toucher les obstacles.

## Comment jouer

- Utilisez la barre espace pour faire monter l'oiseau.

- Évitez les tuyaux en passant à travers les espaces entre eux.

- Si l'oiseau touche un tuyau ou le sol, la partie est terminée.

## Comment exécuter le jeu

Le jeu a été développé en C++ avec la bibliothèque Grapic. Pour exécuter le jeu, vous devez avoir Grapic installé sur votre ordinateur. Vous pouvez ensuite compiler et exécuter le code à l'aide de votre compilateur C++.

## Fonctionnalités
 
- Génération aléatoire des tuyaux et leur déplacement
- Images
- Détection de collision entre l'oiseau et les tuyaux

## Contrôles

Les touches que vous pouvez utiliser pour jouer à FlappyGrapic sont les suivantes :
- Utilisez uniquement la barre espace pour faire monter l'oiseau
- Appuyez sur la touche R pour recommencer la partie à tout moment

## Progression

**21 avril 2023** :
- Ajustement des paramètres de l'oiseau

**28 avril 2023** :
  
- Génération des tuyaux (à changer pour rendre indépendant les tuyaux du haut et celui du bas)

- Commencement du système de collision (problème de collision au niveau du trou entre les deux tuyaux (NB: si il y a collision, l'arrière plan change de couleur))

**2 mai 2023** :

- Nouvelle génération de tuyaux indépendants (tuyaux haut et tuyaux bas)
- Détection des collisions avec les tuyaux et le sol
- Ajouts des images pour les oiseaux et le fond

**5 mai 2023** :
- Ajout des images pour les tuyaux
- Utilisation des vecteurs pour faire bouger les tuyaux et le fond
- Ajout d'un bouton pour recommencer une partie (R)

**6 mai 2023** :
- Ajout d'un écran de Game Over
