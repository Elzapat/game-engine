# Mise en place du projet
* Création de tout les fichiers nécessaires (compilation, arborescence, répo git) (12 septembre)

# Première phase
* Création des diagrammes UML pour les classes `Vector3` et `Particule` (12 septembre)
* Implémentation de la classe `Vector3` (12 septembre)
  * https://en.wikipedia.org/wiki/Cross_product
  * https://en.wikipedia.org/wiki/Dot_product
  * https://en.wikibooks.org/wiki/C++_Programming/Operators/Operator_Overloading
* Implémentation de la classe `Particule` (19 septembre)
* Début de l'implémentation d'un renderer basé sur Vulkan (13 septembre 2022 jusqu'en 2094, au moins)
  * https://vulkan-tutorial.com
  * https://registry.khronos.org/vulkan/
* Implémentation de l'UI avec `ImGui` intégré à Vulkan
    * https://github.com/ocornut/imgui/blob/master/examples/example_glfw_vulkan/main.cpp
    * https://github.com/felipunky/DigitalSignature/blob/master/DigitalSignature/main.cpp
* Implémentation de `PhysicWorld`
* Controle des attributs d'une `Particule` avec des sliders

# Deuxième phase
* Création des diagrammes UML pour toutes les classes des forces et contacts
* Multiplication des meshes affichés à l'écran
    * https://gitlab.steamos.cloud/jupiter/vulkan-examples/-/tree/master/examples/dynamicuniformbuffer
* Affichage d'une sphère
    * http://www.songho.ca/opengl/gl_sphere.html
* Implémentation des générateurs de forces
* Implémentation des générateurs de contacts
* Implémentation des resolveurs de contacts
* Création d'une démo graphique qui montre un amas de particule 
    * Problème de téléportations des particules bloqués au milieu de beaucoup d'autres, on ne sait pas encore comment fix
