# include <stdlib.h>
# include <stdio.h>

int readFile(char* file){

  FILE* fichier = NULL;
  int carac = 0;
  
  fichier = fopen(file, "r");
  
  if (fichier != NULL)
    {
      carac = fgetc(fichier);
      nbVertices = 0;
      while (carac != "\n") // recuperation du nombre de sommets
        {
	  carac = fgetc(fichier);
	  nbVertices += atoi(carac);
        }
      // creer une liste de nbVertices listes d'adjacence
      AdjacenceList[] l = malloc(nbVertices*sizeof(AdjacenceList));
      // initialisation des listes d'adjacence
      for (int i =0; i < nbVertices; i++){
	l[i] = malloc(nbVertices*sizeof(int));
      }

      int i = 1;
      while (i <= nbVertices){
	while(carac != ":"){
	  carac = fgetc(fichier);
	}
	while (carac != "\n"){
	  int j = 0;
	  char* vertex = "";
	  while(carac != " "){ // parcours des voisins du ieme sommet
	    vertex += carac;
	  }
	  l[i][j] = atoi(vertex);
	  j++;
	}
	i++;
      }
      
      fclose(fichier);
    }
  
  return 0;
}
