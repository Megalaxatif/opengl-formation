#include "renderer.h"

void glErrorLog(unsigned int error, const char* function, const char* file, int line){
    std::cout << "code d'erreur [" << error << "] de la fonction [" << function << "] dans le fichier [" << file << "] a la ligne [" << line << "]" << "\n";
}
// s'occuper des erreurs precédentes
void glClearErrors(){
    while(glGetError() != GL_NO_ERROR); // faire tourner la boucle jusqu'à ce que glGetError renvoie 0
}