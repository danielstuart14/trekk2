/* position.h - Save/read states into/from memory for each tick of
 * an encoder.
 * Copyright (C) 2020 Daniel Stuart <daniel.stuart@pucpr.edu.br>
 * 
 * This file is part of Trekking Project.
 * 
 * Trekking Project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Trekking Project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Trekking Project.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef POSI_H
#define POSI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BLOCK 1000 //Size of each block of allocation https://en.wikipedia.org/wiki/Block_(data_storage)
#define GET_SIZE sizeof(Motors)*(structPos + BLOCK) //MACRO for getting current amount of memory allocated

#define PRINT_VALUES 0 //Print each value of struct

//Struct with 4 16-bit unsigned integers
typedef struct motors {
    u_int16_t Front_Left, Front_Right, Back_Left, Back_Right;
} Motors;

//Global variables
Motors *motors;
u_int32_t structPos = 0;
Motors current = {};

//Function declarations
void test(int);
int saveData(char *);
int readData(char *);
int getRandomState();
void printState();
int addPos();

#endif