#include <stdio.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include "aluno.h"
#include "csf.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void drawTela(Obj alex, Limites lim)
{

    char texto[500];
    sprintf(texto, "x = %.2f, y = %.2f, vx = %.2f, vy = %.2f",
            alex.x, alex.y, alex.vx, alex.vy);
    writeText(0, 0, texto);
    writeText(0, 1, "Tecle a e d para mover para os lados e espaco para pular");
    writeText(0, 2, "Feche a janela para sair!");

    int i = 0;
    for(i = lim.superior; i <= lim.inferior ; i++)
    {
        drawChar(lim.esquerda, i, '#');
        drawChar(lim.direita, i, '#');
    }
    for(i = lim.esquerda; i <= lim.direita ; i++)
    {
        drawChar(i, lim.superior, '#');
        drawChar(i, lim.inferior, '#');
    }
}

void drawAlex(Obj * alex, float cell, sfSprite * spegasus, sfRenderWindow * janela, char left, char right){
    sfFloatRect peg_rect = sfSprite_getLocalBounds(spegasus);
    float pegxscale = cell/peg_rect.width;
    float pegyscale = cell/peg_rect.height;
    if(alex->face == left){
        sfSprite_setScale(spegasus, (sfVector2f){pegxscale, pegyscale});
        sfSprite_setPosition(spegasus, (sfVector2f){alex->x * cell, alex->y * cell});
        sfRenderWindow_drawSprite(janela, spegasus, NULL);
    }
    if(alex->face == right){
        sfSprite_setScale(spegasus, (sfVector2f){-pegxscale, pegyscale});
        sfSprite_setPosition(spegasus, (sfVector2f){(alex->x + 1) * cell, alex->y * cell});
        sfRenderWindow_drawSprite(janela, spegasus, NULL);
    }
}

void drawEnemy(Obj * obj, float cell, sfSprite * sprite, sfRenderWindow * janela){
    sfFloatRect peg_rect = sfSprite_getLocalBounds(sprite);
    float xscale = cell/peg_rect.width;
    float yscale = cell/peg_rect.height;

    sfSprite_setScale(sprite, (sfVector2f){xscale, yscale});
    sfSprite_setPosition(sprite, (sfVector2f){obj->x * cell, obj->y * cell});
    sfRenderWindow_drawSprite(janela, sprite, NULL);
}

int main(void) {
    srand(time(NULL));
    float cell = 40.0;
    int xcell = 30;
    int ycell = 20;
    Limites limites = {5, 17, 3, 25};
    sfRenderWindow * janela = iniciar(cell, xcell, ycell);

    sfTexture *tpegasus = sfTexture_createFromFile("../resources/alexkidd.png", NULL);
    sfSprite *spegasus = sfSprite_create();
    sfSprite_setTexture(spegasus, tpegasus, 0);

    sfTexture *tenemy = sfTexture_createFromFile("../resources/inimigo.png", NULL);
    sfSprite *senemy = sfSprite_create();
    sfSprite_setTexture(senemy, tenemy, 0);

    sfTexture *ttiro = sfTexture_createFromFile("../resources/meteoro.png", NULL);
    sfSprite *stiro = sfSprite_create();
    sfSprite_setTexture(stiro, ttiro, 0);

    sfTexture *tgalaxia = sfTexture_createFromFile("../resources/galaxia.jpg", NULL);
    sfSprite *sgalaxia = sfSprite_create();
    sfSprite_setTexture(sgalaxia, tgalaxia, 0);

    sfFloatRect gal_rect = sfSprite_getLocalBounds(sgalaxia);
    float xscale = (cell * (limites.direita - limites.esquerda - 1))/gal_rect.width;
    float yscale = (cell * (limites.inferior - limites.superior - 1))/gal_rect.height;

    sfSprite_setScale(sgalaxia, (sfVector2f){xscale, yscale});
    sfSprite_setPosition(sgalaxia, (sfVector2f){cell + limites.esquerda * cell, cell + limites.superior * cell});

    sfMusic * music = sfMusic_createFromFile("../resources/alex.ogg");
    sfMusic_setLoop(music, 1);
    sfMusic_play(music);


    Obj alex = {10, 10, 1.0, 0.0, '>'};
    Tiro tiro = {{0, 0, 0, 0.0, '*'}, 0}; //x, y, vx, vy, face, existe
    Enemy enemy = {{0, 0, 0, 0.0, '#'}, 0, 0};
    sfEvent event;
    int acabou = 0;
    while (sfRenderWindow_isOpen(janela) && !acabou)
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(janela, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(janela);

            if(event.type == sfEvtKeyPressed){
                //passo 05
                pular(event.key.code, &alex, limites.inferior);
                //passo 06
                atirar(event.key.code, &alex, &tiro);
                //passo 10
                iniciar_inimigo(event.key.code, &enemy, limites);
            }
        }
        //passo 02
        andar(&alex);
        //passo 01
        update(&alex);
        update(&tiro.obj);
        update(&enemy.obj);

        //passo 03
        gravidade(&alex, limites.inferior);
        //passo 04
        colidir(&alex, limites.inferior);

        //passo 07
        atrito(&alex, limites.inferior);

        //passo 08
        verificar_tiro_saiu(&tiro, limites);

        //passo 09
        limitar_alex(&alex, limites);

        //passo 11
        seguir(&enemy.obj, &alex);

        //passo 12
        testar_colisao(&alex, &tiro, &enemy, &acabou);
        /* Clear the screen */
        sfRenderWindow_clear(janela, sfBlack);
        sfRenderWindow_drawSprite(janela, sgalaxia, NULL);

        //desenha boneco e tiros e tela
        drawTela(alex, limites);
        drawAlex(&alex, cell, spegasus, janela, '>', '<');

        if(tiro.existe == 1)
            drawAlex(&tiro.obj, cell, stiro, janela, '{', '}');
        if(enemy.is_ativo == 1){
            drawEnemy(&enemy.obj, cell, senemy, janela);
            drawChar(enemy.obj.x + 0.7, enemy.obj.y - 0.7, enemy.vidas + '0');
        }

        /* Update the window */
        sfRenderWindow_display(janela);
    }
    while (sfRenderWindow_isOpen(janela)){
        while (sfRenderWindow_pollEvent(janela, &event)){
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(janela);
            if(event.type ==sfEvtKeyPressed)
                if(event.key.code == sfKeyQ)
                    sfRenderWindow_close(janela);
        }
        sfRenderWindow_clear(janela, sfBlack);
           if(acabou == 2)
               writeText(0,5, "Parabens voce venceu, digite q para sair");
           if(acabou == 1)
               writeText(0,5, "Voce eh mesmo muito ruim, digite q para sair");

        sfRenderWindow_display(janela);
    }

    sfTexture_destroy(tpegasus);
    sfSprite_destroy(spegasus);
    sfTexture_destroy(tenemy);
    sfSprite_destroy(senemy);
    sfTexture_destroy(tgalaxia);
    sfSprite_destroy(sgalaxia);
    sfTexture_destroy(ttiro);
    sfSprite_destroy(stiro);
    sfMusic_destroy(music);
    finalizar();
    return 0;
}
