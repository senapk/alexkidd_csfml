#ifndef ALUNO_H
#define ALUNO_H
#include <SFML/Graphics.h>

struct _Obj{
    float x, y, vx, vy;
    char face;
};
typedef struct _Obj Obj;

struct _Tiro{
    Obj obj;
    int existe;
};
typedef struct _Tiro Tiro;

struct _Limites {
    int superior;
    int inferior;
    int esquerda;
    int direita;
};
typedef struct _Limites Limites;

struct _Enemy{
    Obj obj;
    int is_ativo;
    int vidas;
};
typedef struct _Enemy Enemy;

void update(Obj *alex);
void andar(Obj *alex);
void gravidade(Obj *alex, int chao);
void colidir(Obj *alex, int chao);
void pular(sfKeyCode tecla, Obj *alex, int chao);
void atirar(sfKeyCode tecla, Obj *alex, Tiro *tiro);
void atrito(Obj *alex, int chao);
int fora_dos_limites(Obj obj, Limites rect);
void verificar_tiro_saiu(Tiro *tiro, Limites tela);
void limitar_alex(Obj *obj, Limites lim);

void iniciar_inimigo(sfKeyCode tecla, Enemy * inimigo, Limites lim);
void seguir(Obj * enemy, Obj * alex);
void testar_colisao(Obj * alex, Tiro * tiro, Enemy * enemy, int * acabou);
#endif // ALUNO_H
