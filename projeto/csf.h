#ifndef CSF_H
#define CSF_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

//inicia uma janela com uma tamanho de celula e a quantida
sfRenderWindow * iniciar(int _cell, int sizeX, int sizeY);
void finalizar();

void drawRect(float x, float y, sfColor cor);

//desenha o texto uma letra por celula
void drawText(float x, float y, const char * meutexto);
//escreve um texto
void writeText(float x, float y, const char * meutexto);
//coloca uma letra dentro de uma celula
void drawChar(float x, float y, char letra);

void playSound(const char * path);

#endif // CSF_H
