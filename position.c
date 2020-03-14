/* position.c - Save/reads states into/from memory for each tick of
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

#include "position.h"

int main() {
    motors = (Motors*) calloc(BLOCK, sizeof(Motors)); //Allocate part of memory for structs with BLOCK size.
    test(2000); //Run test function with 2000 structs

    free(motors); //Free memory used for structs
    return 0;
}

/*
 *  Function: void test(int)
 *  Description: Create "num" amount of pseudorandom structs, save them to
 *  file and then read the file.
 */
void test(int num) {
    srand(time(NULL)); //Create a seed for pseudorandom number generation
    
    //Print current memory allocated in megabytes or kilobytes
    if (sizeof(Motors) * BLOCK >= 1000000)
        printf("Initial size: %lu MBytes\n", sizeof(Motors) * BLOCK / 1000000);
    else
        printf("Initial size: %lu Kbytes\n", sizeof(Motors) * BLOCK / 1000);

    //Generate pseudorandom values for each struct
    for (u_int32_t i = 0; i < num; i++) {
        getRandomState(); //Pseudorandom generator
        printState(); //Print current values
        if(addPos()) //Add struct to memory
            return;
    }
    
    //Generate unique binary name
    char name[25];
    sprintf(name, "data-%d_%d.bin", (u_int32_t) time(NULL), rand() % 1000);
    saveData(name); //Save structs into file
    memset(motors, 0, structPos * sizeof(Motors)); //Clear memory
    readData(name); //Read structs from file
    
    //Read each struct from memory
    for (u_int32_t i = 0; i < num; i++) {
        current = *(motors + i); //Set struct in "i" position as the current struct
        printState(); //Read values from current
    }
}

/*
 *  Function: int saveData(char *)
 *  Description: Save structs into a binary file with name "name".
 */
int saveData(char *name) {
    FILE *file; //Initialize pointer to "FILE" type data
    file = fopen(name, "wb+"); //Create binary file with name "name"
    if (file == NULL) //Check if nothing went wrong
        return 1;

    printf("Saving %s - Size: %lu\n", name, sizeof(Motors) * structPos);
    fwrite(motors, sizeof(Motors), structPos, file); //Dump structs into file
    
    fclose(file); //Close file and free memory allocated
    return 0;
}

/*
 *  Function: int readData(char *)
 *  Description: Read structs from a binary file with name "name".
 */
int readData(char *name) {
    FILE *file; //Initialize pointer to "FILE" type data
    long fSize; //File size
    file = fopen(name, "rb"); //Open file as read-only binary
    if (file == NULL) //Check if nothing went wrong
        return 1;

    fseek (file, 0, SEEK_END); //Set pointer to file's last byte
    fSize = ftell(file);  //Get amount of bytes from current position to start
    fseek (file, 0, SEEK_SET); //Set pointer to file's first byte
    printf("Reading %s - Size: %lu\n", name, fSize);
    motors = (Motors *) realloc(motors, fSize); //Allocate memory with "fSize" size
    fread(motors, sizeof(Motors), fSize/sizeof(Motors), file); //Load binary into memory
    
    fclose(file); //Close file and free memory allocated
    return 0;
}

/*
 *  Function: int getRandomState()
 *  Description: Add pseudorandom values (from 0 to 65535) to current struct.
 *  Info: http://www.cplusplus.com/reference/cstdlib/rand/
 */
int getRandomState() {
    current.Front_Left = rand() % 65536;
    current.Front_Right = rand() % 65536;
    current.Back_Left = rand() % 65536;
    current.Back_Right = rand() % 65536;

    return 0;
}

/*
 *  Function: void printState()
 *  Description: Print current struct values if PRINT_VALUES is true.
 */
void printState() {
#if PRINT_VALUES
    printf("F_L: %x - F_R: %x\n", current.Front_Left, current.Front_Right);
    printf("B_L: %x - B_R: %x\n\n", current.Back_Left, current.Back_Right);
#endif
}

/*
 *  Function: int addPos()
 *  Description: Print current struct values if PRINT_VALUES is true.
 */
int addPos() {
    /* 
     * Check if structPos (current struct position) is divisible by the BLOCK
     * size, if so, increase the amount of memory allocated.
     */
    if (structPos != 0 && structPos % BLOCK == 0) {
        //Print new memory size allocated in megabytes or kilobytes
        if (GET_SIZE >= 1000000)
            printf("New size: %lu MBytes\n", GET_SIZE / 1000000);
        else
            printf("New size: %lu Kbytes\n", GET_SIZE / 1000);

        //Realloc memory with current size plus BLOCK, times the size of each struct.
        motors = (Motors *) realloc(motors, sizeof(Motors)*(structPos + BLOCK));
        
        //Check if anything went wrong
        if (motors == NULL) {
            printf("Error with realloc!\n");
            return 1;
        }
    }
    *(motors + structPos) = current; //Set next struct as current
    structPos++; //Increase struct position
    return 0;
}