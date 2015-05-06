#include "csf.h"
#include <string.h>

static sfRenderWindow* janela;
static sfRectangleShape *rect;
static sfText* text;
static sfFont* font;
static sfMusic *som;
static int cell = 20;

sfRenderWindow * iniciar(int _cell, int sizeX, int sizeY)
{
    cell = _cell;
    sfVideoMode mode = {cell * sizeX, cell * sizeY, 32};
    janela = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(janela, 20);
    if (!janela)
        return NULL;

    font = sfFont_createFromFile("../resources/inconsolata.otf");
    if (!font)
        return NULL;
    text = sfText_create();
    sfText_setFont(text, font);
    sfText_setColor(text, sfWhite);

    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){cell, cell});
    return janela;
}


void drawRect(float x, float y, sfColor cor)
{
    sfRectangleShape_setPosition(rect, (sfVector2f){x * cell, y * cell});
    sfRectangleShape_setFillColor(rect, cor);
    sfRenderWindow_drawRectangleShape(janela, rect, NULL);
}


void drawText(float x, float y, const char * meutexto)
{
    int tam = strlen(meutexto);
    int i = 0;
    for(i = 0; i < tam; i++){
        drawChar(x + i, y, meutexto[i]);
    }
}

void writeText(float x, float y, const char * meutexto)
{
    sfText_setString(text, meutexto);
    sfText_setCharacterSize(text, cell);
    sfText_setPosition(text, (sfVector2f){x * cell, y * cell});
    sfRenderWindow_drawText(janela, text, NULL);
}

void drawChar(float x, float y, char letra){
    char texto[2];
    texto[0] = letra;
    texto[1] = '\0';
    sfText_setString(text, texto);
    sfText_setCharacterSize(text, cell);
    sfText_setPosition(text, (sfVector2f){(x + 0.25) * cell, (y - 0.25) * cell});
    sfRenderWindow_drawText(janela, text, NULL);
}

void finalizar(){
    sfMusic_destroy(som);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfRectangleShape_destroy(rect);
    sfRenderWindow_destroy(janela);
}

void playSound(const char * path){
    if(som != NULL)
        sfMusic_destroy(som);
    som = sfMusic_createFromFile(path);
    sfMusic_play(som);
}
