//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2018 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include <stdio.h>
#include "entities.h"

#define WAITING 30000

u32 cicle; // to measure cicles and set random seed
TCharacter hero, enemy; //main characters 

//////////////////////////////////////////////////////////////////
//
// waitingLoop: Waits a bit for mekaing readable messages
//
// 
//
//////////////////////////////////////////////////////////////////
void waitingLoop(){
        cicle=1;
        while (cicle<WAITING){
            cicle++;
        }
    }

//////////////////////////////////////////////////////////////////
//
// printStatus: Print the status of a fight
//
// 
//
//////////////////////////////////////////////////////////////////
void printStatus(){    
     // Print stats
     printf("PLAYER [%d] (a%d) (d%d)\r\n", hero.energy,   hero.attack,   hero.defense);
     printf("ENEMY  [%d] (a%d) (d%d)\r\n", enemy.energy, enemy.attack, enemy.defense);    
}

//////////////////////////////////////////////////////////////////
//
// init: Main initialization
//
// 
//
//////////////////////////////////////////////////////////////////
void init(void) {
    printf("RPG GAME\r\n");
    printf("\r\n");
    printf("PRESS ENTER TO START\r\n");
    
    cicle = 1;
    // Is enter pressed?
    while (!cpct_isKeyPressed(Key_Return) && !cpct_isKeyPressed(Key_Enter)) {
        cpct_scanKeyboard();
        cicle++;
    }
    // Random seed based on the cicles the user has taken until Enter key pressed
    cpct_srand(cicle);
    
    //Character initilization
    initCharacter(100,30,15,&hero);
    initCharacter(90,20,10,&enemy);    
}

//////////////////////////////////////////////////////////////////
//
// main: Main loop
//
// 
//
//////////////////////////////////////////////////////////////////
void main(void) {
    // Let's start!
    init();
    
    // Main Game Loop repeats until somebody dies
    while (1) {
        
        
        // CLS
        putchar(12);
        // Let's print how goes the fight
        printStatus();
      
        // Scan Player Action
        cpct_scanKeyboard();      
        printf("\r\nHERO ACTION (Attack/Defense)??\r\n");
        while (!cpct_isKeyPressed(Key_A) && !cpct_isKeyPressed(Key_D)) {
            cpct_scanKeyboard();
        }
         
        // PLAYER ATTACKS!
        if (cpct_isKeyPressed(Key_A)) {
            printf("HERO ATTACKS!!\r\n");
            receiveAttackCharacter(hero.attack, &enemy);
        } else {
            // PLAYER DEFENDS!
            if (cpct_isKeyPressed(Key_D)) {
                printf("HERO DEFENDS!!\r\n");
                increaseDefenseCharacter(hero.defense, &hero);
            }
        }
      
        // ENEMY DECIDE
        if (cpct_rand() < 64) {
            printf("ENEMY DEFENDS!!\r\n");
            increaseDefenseCharacter(enemy.defense, &enemy);
        } else {
            printf("ENEMY ATTACKS!!\r\n");
            receiveAttackCharacter(enemy.attack, &hero);
        }
    
        waitingLoop();
        
        // Check if the fight is over
        if (hero.energy==0 || enemy.energy==0){
            // Print Result of the Fight
            printf("\r\n\r\n"); 
            printStatus();
            if (hero.energy>0)
                printf("\r\nHERO WINS !!\r\n");    
            else if (enemy.energy>0)
                printf("\r\nENEMY WINS !!\r\n");
                else
                    printf("\r\nIT'S A TIE !!\r\n");             
            //Start another fight
            printf("\r\n\r\n\r\nLET'S START ANOTHER FIGHT !!\r\n");
            waitingLoop();
             //Character re-initilization
            initCharacter(100,30,15,&hero);
            initCharacter(90,20,10,&enemy);
        }
    }
}