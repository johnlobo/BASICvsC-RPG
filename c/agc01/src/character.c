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
#include "entities.h"

//////////////////////////////////////////////////////////////////
//
// initCharacter: Initilizes a character
//
// input e: energy, a: attack, d: defense, ch character
//
//////////////////////////////////////////////////////////////////
void initCharacter(u8 e, u8 a, u8 d, TCharacter *ch){
    ch->energy = e;
    ch->attack = a;
    ch->defense = d;
}

//////////////////////////////////////////////////////////////////
//
// recieveAttackCharacter: substracts energy from character 
//
// input a: energy, ch: character
//
//////////////////////////////////////////////////////////////////
void receiveAttackCharacter(u8 a, TCharacter *ch){
    // Only substracts when enough energy, otherwise energy = 0
    if (ch->energy>= a)
        ch->energy -= a;
    else
        ch->energy = 0;
}

//////////////////////////////////////////////////////////////////
//
// increaseDefenseCharacter: Increases energy of a character
//
// input a: energy, ch: character
//
//////////////////////////////////////////////////////////////////
void increaseDefenseCharacter(u8 d, TCharacter *ch){
    ch->energy += d;
}
