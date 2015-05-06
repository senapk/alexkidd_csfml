#include <stdio.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include "prof.h"
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

    drawText(lim.esquerda, lim.inferior, " =================================================  ");
    drawText(lim.esquerda, lim.superior, " =================================================  ");
    int i = 0;
    for(i = lim.superior; i <= lim.inferior ; i++)
    {
        drawChar(lim.esquerda, i, '|');
        drawChar(lim.direita, i, '|');
    }
}



int main(void) {
    srand(time(NULL));
    sfRenderWindow * janela = iniciar(20, 60, 30);

    Limites limites = {3, 20, 0, 50};

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

        //desenha boneco e tiros e tela
        drawTela(alex, limites);
        drawChar(alex.x, alex.y, alex.face);
        if(tiro.existe == 1)
            drawChar(tiro.obj.x, tiro.obj.y, tiro.obj.face);
        if(enemy.is_ativo == 1)
            drawChar(enemy.obj.x, enemy.obj.y, (char)(enemy.vidas + '0'));

        /* Update the window */
        sfRenderWindow_display(janela);
    }
    while (sfRenderWindow_isOpen(janela)){
        while (sfRenderWindow_pollEvent(janela, &event)){
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(janela);
        }
        sfRenderWindow_clear(janela, sfBlack);
           if(acabou == 2)
               writeText(5,5, "Parabens voce venceu, feche a janela");
           if(acabou == 1)
               writeText(5,5, "Voce eh mesmo muito ruim, feche a janela");

        sfRenderWindow_display(janela);
    }

    finalizar();
    return 0;
}
