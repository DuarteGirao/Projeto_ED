
#include "relogio.h"

Relogio *CriarRelogio(int _velocidade)
{
    Relogio *R = (Relogio *)malloc(sizeof(Relogio));
    if (!R)
    {
        return NULL;
    }

    R->Tinicio = time(NULL);
    R->Velocidade = _velocidade;
    return R;
}
void DestruirRelogio(Relogio *R)
{
    free(R);
}
time_t GetTempo(Relogio *R)
{
    if (!R)
    {
        return 0;
    }

    return time(NULL);
}