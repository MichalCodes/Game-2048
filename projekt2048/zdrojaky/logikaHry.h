#pragma once

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pocX;
    int pocY;
    int podklad_pixX;
    int podklad_pixY;
    int oknoX;
    int oknoY;
} Velikost;

#define MAX_X_BLOKY 15
#define MAX_Y_BLOKY 8
#define VEL_POLICKA 120

int nahodna_pozice(int max);
void Nulove_pole();
bool win();
bool lose();
void rightArrow_eventReaction();
void leftArrow_eventReaction();
void upArrow_eventReaction();
void downArrow_eventReaction();
