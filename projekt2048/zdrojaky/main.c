#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
// moje hlavicky
#include "logikaHry.h"
#include "menu.h"

extern int volbaX, volbaY;
extern bool menuWindow, esc;
extern Velikost velikost;
extern int herni_pole[8][15];
extern int score;
extern char score_text[20];
extern char score_cislo[8];
/*-------------------------------------------------nacitani a ukladani vstupu------------------------------------------------------*/
int main()
{
    bool gtm = false;
    menu();
    int pocetRadku = volbaY;
    int pocetSloupcu = volbaX;
    if (esc == true){
        return 0;
    }
    if (pocetRadku > 2 && pocetRadku < 15){
        velikost.pocY = pocetRadku;
        velikost.podklad_pixY = velikost.pocY * VEL_POLICKA + 28;
        velikost.oknoY = velikost.podklad_pixY + 200;
    }
    else{
        pocetSloupcu = 4;
        pocetRadku = 4;
        velikost.pocY = pocetRadku;
        velikost.podklad_pixY = velikost.pocY * VEL_POLICKA + 28;
        velikost.oknoY = velikost.podklad_pixY + 200;
    }
    if (pocetSloupcu > 2 && pocetRadku < 15){
        velikost.pocX = pocetSloupcu;
        velikost.podklad_pixX = (velikost.pocX * VEL_POLICKA) + 28;
        velikost.oknoX = velikost.podklad_pixX + 200;
    }
    else{
        pocetSloupcu = 4;
        pocetRadku = 4;
        velikost.pocX = pocetSloupcu;
        velikost.podklad_pixX = (velikost.pocX * VEL_POLICKA) + 28;
        velikost.oknoX = velikost.podklad_pixX + 200;
    }
    /*------------------------------------------------ vytvoreni okna renderreru ----------------------------------------------------*/
    SDL_Init(SDL_INIT_VIDEO);
    // Vytvoření okna                      nazev,  x    y     sirka,         vyska,  po vztvoreni zobrazit
    SDL_Window *window = SDL_CreateWindow("2048", 100, 100, velikost.oknoX, velikost.oknoY, SDL_WINDOW_SHOWN);
    // Vytvoření kreslítka
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // qit button
    bool quit = false;

    Nulove_pole();
    herni_pole[nahodna_pozice(velikost.pocY)][nahodna_pozice(velikost.pocX)] = 2;
    /*---------------------------------------------------nacitani obrázků bloku ------------------------------------------------------*/
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    //#pragma region obrazky
    SDL_Surface *image2 = IMG_Load("bloky/2.png");
    assert(image2);
    SDL_Texture *Texture2 = SDL_CreateTextureFromSurface(renderer, image2);
    SDL_FreeSurface(image2);

    SDL_Surface *image4 = IMG_Load("bloky/4.png");
    assert(image4);
    SDL_Texture *Texture4 = SDL_CreateTextureFromSurface(renderer, image4);
    SDL_FreeSurface(image4);

    SDL_Surface *image8 = IMG_Load("bloky/8.png");
    assert(image8);
    SDL_Texture *Texture8 = SDL_CreateTextureFromSurface(renderer, image8);
    SDL_FreeSurface(image8);

    SDL_Surface *image16 = IMG_Load("bloky/16.png");
    assert(image16);
    SDL_Texture *Texture16 = SDL_CreateTextureFromSurface(renderer, image16);
    SDL_FreeSurface(image16);

    SDL_Surface *image32 = IMG_Load("bloky/32.png");
    assert(image32);
    SDL_Texture *Texture32 = SDL_CreateTextureFromSurface(renderer, image32);
    SDL_FreeSurface(image32);

    SDL_Surface *image64 = IMG_Load("bloky/64.png");
    assert(image64);
    SDL_Texture *Texture64 = SDL_CreateTextureFromSurface(renderer, image64);
    SDL_FreeSurface(image64);

    SDL_Surface *image128 = IMG_Load("bloky/128.png");
    assert(image128);
    SDL_Texture *Texture128 = SDL_CreateTextureFromSurface(renderer, image128);
    SDL_FreeSurface(image128);

    SDL_Surface *image256 = IMG_Load("bloky/256.png");
    assert(image256);
    SDL_Texture *Texture256 = SDL_CreateTextureFromSurface(renderer, image256);
    SDL_FreeSurface(image256);

    SDL_Surface *image512 = IMG_Load("bloky/512.png");
    assert(image512);
    SDL_Texture *Texture512 = SDL_CreateTextureFromSurface(renderer, image512);
    SDL_FreeSurface(image512);

    SDL_Surface *image1024 = IMG_Load("bloky/1024.png");
    assert(image1024);
    SDL_Texture *Texture1024 = SDL_CreateTextureFromSurface(renderer, image1024);
    SDL_FreeSurface(image1024);

    SDL_Surface *image2048 = IMG_Load("bloky/2048.png");
    assert(image2048);
    SDL_Texture *Texture2048 = SDL_CreateTextureFromSurface(renderer, image2048);
    SDL_FreeSurface(image2048);
    //#pragma endregion obrazky
    /*--------------------------------------------------------- texty ----------------------------------------------------------------*/
    sprintf(score_cislo, "%d", score);
    strcat(score_text, score_cislo);
    TTF_Init();
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color end = {255, 255, 255, 128};

    TTF_Font *sans = TTF_OpenFont("AnonymousPro-Regular.ttf", 30);
    assert(sans);
    TTF_Font *tucny = TTF_OpenFont("AnonymousPro-Bold.ttf", 60);
    assert(tucny);

    //#pragma region texts
    SDL_Surface *resultW = TTF_RenderText_Solid(tucny, "You win!", white);
    SDL_Texture *resW = SDL_CreateTextureFromSurface(renderer, resultW);

    SDL_Surface *resultL = TTF_RenderText_Solid(tucny, "You lose!", black);
    SDL_Texture *resL = SDL_CreateTextureFromSurface(renderer, resultL);

    SDL_Surface *surface_message = TTF_RenderText_Solid(sans, "Score: 0", black);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface_message);

    SDL_Surface *toMenu = TTF_RenderText_Solid(tucny, " Back to menu ", white);
    SDL_Texture *Back_to_menu = SDL_CreateTextureFromSurface(renderer, toMenu);

    SDL_Surface *Menu = TTF_RenderText_Solid(sans, " menu ", white);
    SDL_Texture *menu = SDL_CreateTextureFromSurface(renderer, Menu);
    //#pragma endregion texts
    
    SDL_FreeSurface(Menu);
    SDL_FreeSurface(resultW);
    SDL_FreeSurface(resultL);
    SDL_FreeSurface(surface_message);
    SDL_FreeSurface(toMenu);
    /*----------------------------------------------------- pozice rects -----------------------------------------------------------------*/
    SDL_Rect score_rect = {.x = 100, .y = 50, .w = 200, .h = 30};
    SDL_Rect rect = {.x = 100, .y = 100, .w = velikost.podklad_pixX, .h = velikost.podklad_pixY};
    SDL_Rect blocksRect = {.x = 110, .y = 110, .w = 110, .h = 110};
    SDL_Rect endOFgame = {.x = (velikost.podklad_pixX / 2) - 50, .y = (velikost.podklad_pixY / 2), .w = 300, .h = 50};
    SDL_Rect backToMenu = {.x = (velikost.podklad_pixX / 2) - 50, .y = (velikost.podklad_pixY / 2) + 200, .w = 300, .h = 50};
    SDL_Rect back = {.x = velikost.podklad_pixX, .y = 50, .w = 100, .h = 30};
    SDL_Event e;
    /*===================================================== Herni smicka =================================================================*/
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
    /*----------------------------------------------------reakce na events----------------------------------------------------------------*/
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                // RIGHT
                if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
                {
                    if(win() == false && lose()== false){
                        rightArrow_eventReaction();
                    }
                }
                // LEFT
                else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
                {
                    if(win() == false && lose()== false){
                        leftArrow_eventReaction();
                    }
                }
                // UP
                else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
                {
                    if(win() == false && lose()== false){
                        upArrow_eventReaction();
                    }
                }
                // DOWN
                else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
                {
                    if(win() == false && lose()== false){
                        downArrow_eventReaction();
                    }
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.clicks == SDL_BUTTON_LEFT)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= backToMenu.x && x <= backToMenu.x + backToMenu.w && y >= backToMenu.y && y <= backToMenu.y + backToMenu.h && (win() == true || lose() == true))
                    {
                        score = 0;
                        Nulove_pole();
                        for (int i = 0; i < 8; i++)
                        {
                            score_cislo[i] = '\0';
                        }
                        for (int i = 7; i < 19; i++)
                        {
                            score_text[i] = '\0';
                        }
                        volbaX = -1;
                        volbaY = -1;
                        menuWindow = false, esc = false;
                        gtm = true, quit = true;
                    }
                    if (x >= back.x && x <= back.x + back.w && y >= back.y && y <= back.y + back.h)
                    {
                        score = 0;
                        Nulove_pole();
                        for (int i = 0; i < 8; i++)
                        {
                            score_cislo[i] = '\0';
                        }
                        for (int i = 7; i < 19; i++)
                        {
                            score_text[i] = '\0';
                        }
                        volbaX = -1;
                        volbaY = -1;
                        menuWindow = false, esc = false;
                        gtm = true, quit = true;
                    }
                }
            }
        }
        /*------------------------------------------------------------ vykreslovani grafiky --------------------------------------------------------------------*/
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // čistý render
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &rect);
        // bloky
        SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255);
        for (int y = 0; y < velikost.pocY; y++)
        {
            blocksRect.y = (y + 1) * 120;
            for (int x = 0; x < velikost.pocX; x++)
            {
                blocksRect.x = (x + 1) * 120;
                if (herni_pole[y][x] != 0)
                {
                    if (herni_pole[y][x] == 2)
                    {
                        SDL_RenderCopy(renderer, Texture2, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 4)
                    {
                        SDL_RenderCopy(renderer, Texture4, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 8)
                    {
                        SDL_RenderCopy(renderer, Texture8, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 16)
                    {
                        SDL_RenderCopy(renderer, Texture16, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 32)
                    {
                        SDL_RenderCopy(renderer, Texture32, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 64)
                    {
                        SDL_RenderCopy(renderer, Texture64, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 128)
                    {
                        SDL_RenderCopy(renderer, Texture128, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 256)
                    {
                        SDL_RenderCopy(renderer, Texture256, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 512)
                    {
                        SDL_RenderCopy(renderer, Texture512, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 1024)
                    {
                        SDL_RenderCopy(renderer, Texture1024, NULL, &blocksRect);
                    }
                    if (herni_pole[y][x] == 2048)
                    {
                        SDL_RenderCopy(renderer, Texture2048, NULL, &blocksRect);
                    }
                }
                else{
                    SDL_RenderFillRect(renderer, &blocksRect);
                }
            }
        }
        // score
        surface_message = TTF_RenderText_Solid(sans, score_text, black);
        text = SDL_CreateTextureFromSurface(renderer, surface_message);
        SDL_RenderCopy(renderer, text, NULL, &score_rect);
        SDL_FreeSurface(surface_message);
        SDL_DestroyTexture(text); 
        //tlacitko menu
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderFillRect(renderer, &back);
        SDL_RenderCopy(renderer, menu, NULL, &back);
        
        if (win() == true)
        {
            SDL_SetRenderDrawColor(renderer, 210, 210, 210, 128);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderCopy(renderer, resW, NULL, &endOFgame);
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            SDL_RenderFillRect(renderer, &backToMenu);
            SDL_RenderCopy(renderer, Back_to_menu, NULL, &backToMenu);
        }

        if (lose() == true)
        {
            SDL_SetRenderDrawColor(renderer, 210, 210, 210, 128);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderCopy(renderer, resL, NULL, &endOFgame);
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            SDL_RenderFillRect(renderer, &backToMenu);
            SDL_RenderCopy(renderer, Back_to_menu, NULL, &backToMenu);
        }
        SDL_RenderPresent(renderer);
    }
    // Uvolnění prostředků
    TTF_CloseFont(sans);
    TTF_CloseFont(tucny);
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(resL);
    SDL_DestroyTexture(resW);
    SDL_DestroyTexture(Back_to_menu);
    SDL_DestroyTexture(Texture2);
    SDL_DestroyTexture(Texture4);
    SDL_DestroyTexture(Texture8);
    SDL_DestroyTexture(Texture16);
    SDL_DestroyTexture(Texture32);
    SDL_DestroyTexture(Texture64);
    SDL_DestroyTexture(Texture128);
    SDL_DestroyTexture(Texture256);
    SDL_DestroyTexture(Texture512);
    SDL_DestroyTexture(Texture1024);
    SDL_DestroyTexture(Texture2048);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    if (gtm == true)
    {
        return main();
    }
    return 0;
}