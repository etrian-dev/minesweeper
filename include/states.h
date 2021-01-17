// just useful enums shared between classes

/*
 * states.h
 * This file is part of minesweeper
 *
 * Copyright (C) 2021 - etrian-dev
 *
 * minesweeper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * minesweeper is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with minesweeper. If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

enum State {MINE=-1, COVERED = 0, UNCOVERED = 1};
enum Flag {UNFLAGGED = false, FLAGGED = true};

#endif // STATE_H_INCLUDED
