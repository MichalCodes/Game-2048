#include "logikaHry.h"

int herni_pole[8][15];
int randY, randX;
bool novy_blok = false, loseControl = false;
int score = 0;
char score_text[20] = "Score: ";
char score_cislo[8];
Velikost velikost = {.pocX = 4, .pocY = 4, .podklad_pixX = 450, .podklad_pixY = 400};

int S = 5;
int nahodna_pozice(int max)
{ // nahodny generovani cisel
    int N = S;
    N = (5 * N + 3) % 6323;
    N = (4 * N + 2) % 7235;
    int V = N % max;
    S = N;
    return V;
}

void Nulove_pole()
{
    for (int i = 0; i < 8; i++)
    {
        for (int a = 0; a < 15; a++)
        {
            herni_pole[i][a] = 0;
        }
    }
}

bool win()
{
    for (int i = 0; i < 8; i++)
    {
        for (int x = 0; x < 15; x++)
        {
            if (herni_pole[i][x] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool lose()
{
    bool result = true;
    for (int i = 0; i < velikost.pocY; i++)
    {
        for (int a = 0; a < velikost.pocX; a++)
        {
            if (herni_pole[i][a] == 0)
            {
                return false;
            }
        }
    }

    // pokus doprava
    for (int i = 0; i < velikost.pocY; i++)
    {
        for (int x = velikost.pocX - 1; x > 0; x--)
        {
            if (herni_pole[i][x] == herni_pole[i][x - 1] && herni_pole[i][x] != 0 && herni_pole[i][x - 1] != 0)
            {
                result = false;
            }
        }
    }

    // pokus doleva
    for (int i = 0; i < velikost.pocY; i++)
    {
        for (int x = 0; x < velikost.pocX - 1; x++)
        {
            if (herni_pole[i][x] == herni_pole[i][x + 1] && herni_pole[i][x] != 0 && herni_pole[i][x + 1] != 0)
            {
                result = false;
            }
        }
    }
    // pokus nahoru
    for (int x = 0; x < velikost.pocX; x++)
    {
        for (int i = 0; i < velikost.pocY - 1; i++)
        {
            if (herni_pole[i][x] == herni_pole[i + 1][x] && herni_pole[i][x] != 0 && herni_pole[i + 1][x] != 0)
            {
                result = false;
            }
        }
    }
    // pokus dolu
    for (int x = 0; x < velikost.pocX; x++)
    {
        for (int i = velikost.pocY - 1; i > 0; i--)
        {
            if (herni_pole[i][x] == herni_pole[i - 1][x] && herni_pole[i][x] != 0 && herni_pole[i - 1][x] != 0)
            {
                result = false;
            }
        }
    }

    return result;
}

void rightArrow_eventReaction()
{
    //sešoupnu
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int i = 0; i < velikost.pocY; i++)
        {
            for (int x = velikost.pocX - 1; x > 0; x--)
            {
                if (herni_pole[i][x - 1] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i][x - 1];
                    herni_pole[i][x - 1] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    // sectu co jde
    for (int i = 0; i < velikost.pocY; i++)
    {
        for (int x = velikost.pocX - 1; x > 0; x--)
        {
            if (herni_pole[i][x] == herni_pole[i][x - 1] && herni_pole[i][x] != 0 && herni_pole[i][x - 1] != 0)
            {
                herni_pole[i][x] = herni_pole[i][x] + herni_pole[i][x - 1];
                herni_pole[i][x - 1] = 0;
                score += herni_pole[i][x];
                novy_blok = true;
            }
        }
    }
    // sesupnu když sečtením vznikne mezera
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int i = 0; i < velikost.pocY; i++)
        {
            for (int x = velikost.pocX - 1; x > 0; x--)
            {
                if (herni_pole[i][x - 1] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i][x - 1];
                    herni_pole[i][x - 1] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    //Vyhodím nový blok pokud mam
    if (novy_blok == true)
    {
        do
        {
            randY = nahodna_pozice(velikost.pocY);
            randX = nahodna_pozice(velikost.pocX);
        } while (herni_pole[randY][randX] != 0);
        novy_blok = false;
        int nahodnyBlok = nahodna_pozice(2);
        if (nahodnyBlok == 1)
        {
            herni_pole[randY][randX] = 4;
        }
        else
        {
            herni_pole[randY][randX] = 2;
        }
    }
    //přičtu score
    for (int i = 0; i < 8; i++)
    {
        score_cislo[i] = '\0';
    }
    for (int i = 7; i < 19; i++)
    {
        score_text[i] = '\0';
    }
    sprintf(score_cislo, "%d", score);
    strcat(score_text, score_cislo);
}

void leftArrow_eventReaction()
{
    // sesupnu
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int i = 0; i < velikost.pocY; i++)
        {
            for (int x = 0; x < velikost.pocX - 1; x++)
            {
                if (herni_pole[i][x + 1] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i][x + 1];
                    herni_pole[i][x + 1] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    // sectu
    for (int i = 0; i < velikost.pocY; i++)
    {
        for (int x = 0; x < velikost.pocX - 1; x++)
        {
            if (herni_pole[i][x] == herni_pole[i][x + 1] && herni_pole[i][x] != 0 && herni_pole[i][x + 1] != 0)
            {
                herni_pole[i][x] = herni_pole[i][x] + herni_pole[i][x + 1];
                score += herni_pole[i][x];
                herni_pole[i][x + 1] = 0;
                novy_blok = true;
            }
        }
    }
    // sesupnu
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int i = 0; i < velikost.pocY; i++)
        {
            for (int x = 0; x < velikost.pocX - 1; x++)
            {
                if (herni_pole[i][x + 1] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i][x + 1];
                    herni_pole[i][x + 1] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    // novy blok
    if (novy_blok == true)
    {
        do
        {
            randY = nahodna_pozice(velikost.pocY);
            randX = nahodna_pozice(velikost.pocX);
        } while (herni_pole[randY][randX] != 0);
        novy_blok = false;
        int nahodnyBlok = nahodna_pozice(2);
        if (nahodnyBlok == 1)
        {
            herni_pole[randY][randX] = 4;
        }
        else
        {
            herni_pole[randY][randX] = 2;
        }
    }
    // skore
    for (int i = 0; i < 8; i++)
    {
        score_cislo[i] = '\0';
    }
    for (int i = 7; i < 19; i++)
    {
        score_text[i] = '\0';
    }
    sprintf(score_cislo, "%d", score);
    strcat(score_text, score_cislo);
}

void upArrow_eventReaction()
{
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int x = 0; x < velikost.pocX; x++)
        {
            for (int i = 0; i < velikost.pocY - 1; i++)
            {
                if (herni_pole[i + 1][x] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i + 1][x];
                    herni_pole[i + 1][x] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    for (int x = 0; x < velikost.pocX; x++)
    {
        for (int i = 0; i < velikost.pocY - 1; i++)
        {
            if (herni_pole[i][x] == herni_pole[i + 1][x] && herni_pole[i][x] != 0 && herni_pole[i + 1][x] != 0)
            {
                herni_pole[i][x] = herni_pole[i][x] + herni_pole[i + 1][x];
                score += herni_pole[i][x];
                herni_pole[i + 1][x] = 0;
                novy_blok = true;
            }
        }
    }
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int x = 0; x < velikost.pocX; x++)
        {
            for (int i = 0; i < velikost.pocY - 1; i++)
            {
                if (herni_pole[i + 1][x] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i + 1][x];
                    herni_pole[i + 1][x] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    if (novy_blok == true)
    {
        do
        {
            randY = nahodna_pozice(velikost.pocY);
            randX = nahodna_pozice(velikost.pocX);
        } while (herni_pole[randY][randX] != 0);
        novy_blok = false;
        int nahodnyBlok = nahodna_pozice(2);
        if (nahodnyBlok == 1)
        {
            herni_pole[randY][randX] = 4;
        }
        else
        {
            herni_pole[randY][randX] = 2;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        score_cislo[i] = '\0';
    }
    for (int i = 7; i < 19; i++)
    {
        score_text[i] = '\0';
    }
    sprintf(score_cislo, "%d", score);
    strcat(score_text, score_cislo);
}

void downArrow_eventReaction()
{
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int x = 0; x < velikost.pocX; x++)
        {
            for (int i = velikost.pocY - 1; i > 0; i--)
            {
                if (herni_pole[i - 1][x] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i - 1][x];
                    herni_pole[i - 1][x] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    for (int x = 0; x < velikost.pocX; x++)
    {
        for (int i = velikost.pocY - 1; i > 0; i--)
        {
            if (herni_pole[i][x] == herni_pole[i - 1][x] && herni_pole[i][x] != 0 && herni_pole[i - 1][x] != 0)
            {
                herni_pole[i][x] = herni_pole[i][x] + herni_pole[i - 1][x];
                score += herni_pole[i][x];
                herni_pole[i - 1][x] = 0;
                novy_blok = true;
            }
        }
    }
    for (int c = 0; c < velikost.pocX; c++)
    {
        for (int x = 0; x < velikost.pocX; x++)
        {
            for (int i = velikost.pocY - 1; i > 0; i--)
            {
                if (herni_pole[i - 1][x] > 0 && herni_pole[i][x] == 0)
                {
                    herni_pole[i][x] = herni_pole[i - 1][x];
                    herni_pole[i - 1][x] = 0;
                    novy_blok = true;
                }
            }
        }
    }
    if (novy_blok == true)
    {
        do
        {
            randY = nahodna_pozice(velikost.pocY);
            randX = nahodna_pozice(velikost.pocX);
        } while (herni_pole[randY][randX] != 0);
        novy_blok = false;
        int nahodnyBlok = nahodna_pozice(2);
        if (nahodnyBlok == 1)
        {
            herni_pole[randY][randX] = 4;
        }
        else
        {
            herni_pole[randY][randX] = 2;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        score_cislo[i] = '\0';
    }
    for (int i = 7; i < 19; i++)
    {
        score_text[i] = '\0';
    }
    sprintf(score_cislo, "%d", score);
    strcat(score_text, score_cislo);
}
