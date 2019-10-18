/* Copyright 2019 Samuel Carroll
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FAMICOM_H
#define FAMICOM_H
#pragma once

#include "quantum.h"


/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/*
NOTE: What follows is the physical layout of the keyboard
      however this is not how the matrix is set up...
F1  F2  F3  F4  F5  F6  F7  F8
 1 2 3 4 5 6 7 8 9 0 - ^ ¥ STOP       CH* INS DEL
ESC Q W E R T Y U I O P @ [ RETURN        UP
CTR A S D F G H J K L ; : ] KANA      LEFT RIGHT
SHIFT Z X C V B N M , . / _ SHIFT        DOWN
       GRPH   SPACE 

NOTE: At first I believed that the keyboard used the following matrix
      from https://wiki.nesdev.com/w/index.php/Family_BASIC_Keyboard#Matrix
+--------------+-------------------------------+--+--------------------------------+
|              |            Column 0           |  |            Column 1            |
+--------------+-------+-------+--------+------+--+--------------------------------+
| $4017 bit    |   4   |   3   |   2    |   1  |  |   4  |   3   |    2   |    1   |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 0        |   ]   |   [   | RETURN |  F8  |  | STOP |   ¥   | RSHIFT |   KANA |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 1        |   ;   |   :   |   @    |  F7  |  |   ^  |   -   |    /   |    _   |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 2        |   K   |   L   |   O    |  F6  |  |   0  |   P   |    ,   |    .   |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 3        |   J   |   U   |   I    |  F5  |  |   8  |   9   |    N   |    M   |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 4        |   H   |   G   |   Y    |  F4  |  |   6  |   7   |    V   |    B   |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 5        |   D   |   R   |   T    |  F3  |  |   4  |   5   |    C   |    F   |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 6        |   A   |   S   |   W    |  F2  |  |   3  |   E   |    Z   |    X   |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 7        |  CTR  |   Q   |  ESC   |  F1  |  |   2  |   1   |  GRPH  | LSHIFT |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+
| Row 8        |  LEFT | RIGHT |   UP   | CLR/ |  |  INS |  DEL  |  SPACE |  DOWN  |
|              |       |       |        | HOME |  |      |       |        |        |
+--------------+-------+-------+--------+------+--+------+-------+--------+--------+

But what I discovered is that this is the output after running through the chips
Using these two as sources for that discovery and the actual pre-chip output/matrix
http://www43.tok2.com/home/cmpslv/Famic/Fambas.htm
https://github.com/olivia/family-kb-arduino

//An Image of the Famicom I/O
http://www43.tok2.com/home/cmpslv/Famic/Fcbio.png

//An image of the actual Famicom matrix
http://www43.tok2.com/home/cmpslv/Famic/Fcbmat.png
Let p3 be column and p2 be rows to get the following matrix

+-------+-------+--------+-------+-------+--------+--------+-------+-------+
|       | Col 1 |  Col 2 | Col 3 | Col 4 |  Col 5 |  Col 6 | Col 7 | Col 8 |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 1 |   F8  | RETURN |   [   |   ]   |  KANA  | RSHIFT |   ¥   |  STOP |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 2 |   F7  |    @   |   ;   |   :   |    _   |    /   |   -   |   ^   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 3 |   F6  |    O   |   L   |   K   |    <   |    .   |   P   |   0   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 4 |   F5  |    I   |   U   |   J   |    M   |    N   |   9   |   8   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 5 |   F4  |    Y   |   G   |   H   |    B   |    V   |   7   |   6   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 6 |   F3  |    T   |   R   |   D   |    F   |    C   |   5   |   4   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 7 |   F2  |    W   |   S   |   A   |    X   |    Z   |   E   |   3   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 8 |   F1  |   ESC  |   Q   |  CTR  | LSHIFT |  GRPH  |   1   |   2   |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+
| Row 9 |  CLR/ |   UP   | RIGHT |  LEFT |  DOWN  |  SPACE |  DEL  |  INS  |
|       |  HOME |        |       |       |        |        |       |       |
+-------+-------+--------+-------+-------+--------+--------+-------+-------+

NOTICE: In the  matrix above vs output ; and : are swapped need to test this!
*/


// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, \
    k08, k09, k10, k11, k12, k13, k14, k15, \
    k16, k17, k18, k19, k20, k21, k22, k23, \
    k24, k25, k26, k27, k28, k29, k30, k31, \
    k32, k33, k34, k35, k36, k37, k38, k39, \
    k40, k41, k42, k43, k44, k45, k46, k47, \
    k48, k49, k50, k51, k52, k53, k54, k55, \
    k56, k57, k58, k59, k60, k61, k62, k63, \
    k64, k65, k66, k67, k68, k69, k70, k71 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k08, k09, k10, k11, k12, k13, k14, k15 }, \
    { k16, k17, k18, k19, k20, k21, k22, k23 }, \
    { k24, k25, k26, k27, k28, k29, k30, k31 }, \
    { k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { k48, k49, k50, k51, k52, k53, k54, k55 }, \
    { k56, k57, k58, k59, k60, k61, k62, k63 }, \
    { k64, k65, k66, k67, k68, k69, k70, k71 }  \
}

#endif
