#include "menu.h"

typedef struct
{
    int LHx;
    int LHy;
    int PDx;
    int PDy;
} BtnField;

int volbaX = 0, volbaY = 0;
bool menuWindow = false, esc = false;

void menu()
{
/*----------------------------------------------------- okno ------------------------------------------------------*/
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("SDL experiments", 100, 100, 880, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
/*---------------------------------------------------- texty -------------------------------------------------------*/
    TTF_Init();
    SDL_Color black = {0, 0, 0, 255};
    TTF_Font *tucny = TTF_OpenFont("AnonymousPro-Bold.ttf", 60);
    assert(tucny);
    TTF_Font *sans = TTF_OpenFont("AnonymousPro-Regular.ttf", 70);
    assert(sans);

    SDL_Surface *MenuSurface = TTF_RenderText_Solid(tucny, "Menu", black);
    SDL_Texture *MenuTexture = SDL_CreateTextureFromSurface(renderer, MenuSurface);

    SDL_Surface *iks = TTF_RenderText_Solid(sans, "X", black);
    SDL_Texture *X = SDL_CreateTextureFromSurface(renderer, iks);

    SDL_Surface *cisla = TTF_RenderText_Solid(sans, "3", black);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, cisla);

    SDL_Surface *Splay = TTF_RenderText_Solid(tucny, " Play ", black);
    SDL_Texture *play = SDL_CreateTextureFromSurface(renderer, Splay);
    
    SDL_FreeSurface(MenuSurface);
    SDL_FreeSurface(iks);
    SDL_FreeSurface(Splay);

    SDL_Rect MenuRect = {.x = 370, .y = 20, .w = 150, .h = 80};
    SDL_Rect Xrect = {.x = 415, .y = 200, .w = 60, .h = 60};
/*--------------------------------------------------- buttons ------------------------------------------------------*/
    SDL_Rect *buttons;
    buttons = (SDL_Rect *)malloc(20 * sizeof(SDL_Rect));
    // Recty pro buttons
    int XX = 120, YY = 150;
    for (int i = 0; i < 13; i++)
    {
        buttons[i].x = XX;
        buttons[i].y = YY;
        buttons[i].w = 50;
        buttons[i].h = 50;
        XX += 60;
        if (XX >= 420)
        {
            XX = 120;
            YY += 60;
        }
    }
    XX = 480;
    YY = 150;
    for (int i = 13; i < 19; i++)
    {
        buttons[i].x = XX;
        buttons[i].y = YY;
        buttons[i].w = 50;
        buttons[i].h = 50;
        XX += 60;
        if (XX >= 780)
        {
            XX = 480;
            YY += 60;
        }
    }
    SDL_Rect playButton = {.x = 370, .y = 500, .w = 160, .h = 80};

    SDL_Event e;
    int num = 3;
    char number[4];
    /*===================================================== Herni smycka =========================================================*/
    while (!menuWindow)
    {
        while (SDL_PollEvent(&e))
        {
    /*--------------------------------------------------- Reakce na events -------------------------------------------------------*/        
            if (e.type == SDL_QUIT)
            {
                menuWindow = true;
                esc = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.clicks == SDL_BUTTON_LEFT)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    for (int i = 0; i < 13; i++)
                    {
                        if (x >= buttons[i].x && x <= buttons[i].x + buttons[i].w && y >= buttons[i].y && y <= buttons[i].y + buttons[i].h)
                        {
                            volbaX = i + 3;
                        }
                    }
                    for (int i = 13; i < 19; i++)
                    {
                        if (x >= buttons[i].x && x <= buttons[i].x + buttons[i].w && y >= buttons[i].y && y <= buttons[i].y + buttons[i].h)
                        {
                            volbaY = i - 10;
                        }
                    }
                    if (x >= playButton.x && x <= playButton.x + playButton.w && y >= playButton.y && y <= playButton.y + playButton.h)
                    {
                        menuWindow = true;
                    }
                }
            }
        }
    /*--------------------------------------------------- vykreslovani ---------------------------------------------------*/        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        //Napis menu
        SDL_RenderCopy(renderer, MenuTexture, NULL, &MenuRect);
        // volby pro X
        for (int i = 0; i < 13; i++)
        {
            for (int a = 0; a < 4; a++)
            {
                number[a] = '\0';
            }
            if (volbaX == i + 3)
            {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
            }
            sprintf(number, "%d", num);
            if(num > 9){
                cisla = TTF_RenderText_Solid(tucny, number, black);
            }
            else{
                cisla = TTF_RenderText_Solid(sans, number, black);
            }
            text = SDL_CreateTextureFromSurface(renderer, cisla);
            SDL_RenderFillRect(renderer, &buttons[i]);
            SDL_RenderCopy(renderer, text, NULL, &buttons[i]);
            SDL_FreeSurface(cisla);
            SDL_DestroyTexture(text);
            num++;
        }
        num = 3;
        //Volby pro Y
        for (int i = 13; i < 19; i++)
        {
            for (int a = 0; a < 4; a++)
            {
                number[a] = '\0';
            }
            if (volbaY == i - 10)
            {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
            }
            sprintf(number, "%d", num);
            cisla = TTF_RenderText_Solid(sans, number, black);
            text = SDL_CreateTextureFromSurface(renderer, cisla);
            SDL_RenderFillRect(renderer, &buttons[i]);
            SDL_RenderCopy(renderer, text, NULL, &buttons[i]);
            SDL_FreeSurface(cisla);
            SDL_DestroyTexture(text);
            num++;
        }
        num = 3;
        //X mezi
        SDL_RenderCopy(renderer, X, NULL, &Xrect);
        //Play button
        SDL_RenderFillRect(renderer, &playButton);
        SDL_RenderCopy(renderer, play, NULL, &playButton);
        SDL_RenderPresent(renderer);
    }
/*-------------------------------------------- Uvolňování prostředků --------------------------------------*/    
    free(buttons);
    TTF_CloseFont(sans);
    TTF_CloseFont(tucny);       
    SDL_DestroyTexture(MenuTexture);
    SDL_DestroyTexture(X);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(play);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
