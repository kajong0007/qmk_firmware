/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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
#pragma once

#include "quantum.h"

#define LAYOUT_all( \
    K00,    K01, K02, K03, K04,    K05, K06, K07, K08,     K09, K69, K68, K67,   K66, K65, K64,                       \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K79, K78, K77, K76, K75,   K74, K73, K72,   K63, K62, K61, K60, \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K89, K88, K87,   K86,   K85, K84, K83,   K82, K81, K80, K90, \
    K30,      K31, K32, K33, K34, K35, K36, K37, K38, K39, K99, K98,      K97,                    K95, K92, K71, K70, \
    K40, K41,   K42, K43, K44, K45, K46, K47, K48, K49, KA9, KA8,    KA6, KA7,        K96,        K94, K93, K91, KA0, \
    K50,  K51,  K52,               K53, K54,            K55,  K56,  K57,  K58,   K59, KA5, KA4,   KA3, KA2, KA1       \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59 }, \
    { K60, K61, K62, K63, K64, K65, K66, K67, K68, K69 }, \
    { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79 }, \
    { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89 }, \
    { K90, K91, K92, K93, K94, K95, K96, K97, K98, K99 }, \
    { KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7, KA8, KA9 }  \
}
