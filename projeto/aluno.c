struct Obj{
    int x, y, vx, vy;
    char face;
};

/*
 * Em update a posicao de alex em x aumenta de vx,
 * e a posicao de alex em y aumenta de vy
 */
void update(Obj &alex)
{
    alex.x += alex.vx;
    alex.y += alex.vy;
}

/*
 * Se a tecla for 'd',
 *     - a velocidade de alex em x aumenta em 1. Porem ela nao pode passar de 2.
 *     - a face de Alex muda para '>'
 *
 * Se a tecla for 'a',
 *     - a velocidade de alex em x diminui em 1. Porem ela nao pode passar de -2.
 *     - a face de Alex muda para '<'
 */
void andar(char tecla, Obj &alex)
{
    if(tecla == 'd')
    {
        if(alex.vx < 2)
            alex.vx++;
        alex.face = '>';

    }
    if(tecla == 'a')
    {
        if(alex.vx > -2)
            alex.vx--;
        alex.face = '<';
    }
}

//se alex nao estiver tocando no chao, ou seja,
//alex.y < chao - 2, a velocidade vy de alex deve
//ser aumentada em 1
void gravidade(Obj &alex, int chao)
{
    if(alex.y<chao -2)
        alex.vy++;
}

/* Se alex tentar atravessar o chao, ou seja,
 * seu y for >= chao, entao o faca voltar para
 * cima do chao, y deve ser igual a chao - 1.
 * Alem disso a velocidade dele em y deve se
 * tornar zero ao bater no chao
 */
void colidir(Obj &alex, int chao)
{
}

//se alex estiver tocando o chao, ou seja,
//y = chao -1
//e a tecla for o 'w', a velocidade de
//alex na vertical deve diminuir em 3.
//Para cima diminui, lembre-se disso!
void pular(char tecla, Obj &alex, int chao)
{
}

struct Tiro{
    int x, y;
    bool existe;
    int vx;
};


/* Hora de atirar Alex Kidd, caso a tecla apertada for 'l',
 * Alex da um tiro pra direita com velocidade vx 5.
 * Se a tecla for 'j', entao o tiro tem velocidade -5.
 * O tiro sai da posicao onde alex esta no momento
 * do disparo.
 * Se a bala ja existe, entao nao faça nada
 */

void atirar(char tecla, Obj &alex, Tiro &tiro)
{
    if(tiro.existe == false)
        return;
}

/*
 * Pode ver que sua bala nao se mexeu, temos que ensinar o computador
 * a atualizAR A posicao da sua bala.
 * Altere x da bala de acordo com o vx dela, como voce fez com a funcao
 * que faz o update da posiçao do Alex.
 */
void update_tiro(Tiro &tiro)
{
}

/*
 * Atualiza um vetor de objetos usando o vx e o vy de cada um deles
 */
void update_vetor(Obj vet[], int tam);


/*
 * Verifica se ouve colisao do Obj A com algum elemento do vetor de Objetos.
 */
bool detect_colisao(Obj vet[], int tam, Obj A);

/*
 *
 */

#endif

