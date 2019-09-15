/////////////////////////////////////////////////////////////////////////////
// INTEGRITY INSTRUCTIONS

// Explicitly state the level of collaboration on this question
// Examples:
//   * I discussed ideas with classmate(s) [include name(s)]
//   * I worked together with classmate(s) in the lab [include name(s)]
//   * Classmate [include name] helped me debug my code
//   * I consulted website [include url]
//   * None
// A "None" indicates you completed this question entirely by yourself
// (or with assistance from course staff)
/////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT:
// I received help from the following sources: None

// Name: Samer Zumot
// login ID: sizumot
/////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdio.h>
#include "game_core.h"
#include "cs136.h"

int mines(const int c, const int r, const int width, const int height) 
{
  int i = 0;
  if (c < width - 1) {
    if  (mine_at(c + 1, r)) {
      ++i;
    }
  }
  if ((c < width - 1) && (r > 0)) {
    if (mine_at(c + 1, r - 1)) {
      ++i;
    }
  }
  if (r < width - 1) {
    if (mine_at(c, r + 1)) {
      ++i;
    }
  }
  if ((c < width - 1) && (r < height - 1)) {
    if  (mine_at(c + 1, r + 1)) {
      ++i;
    }
  }
  if (c > 0) {
    if (mine_at(c - 1, r)) {
      ++i;
    }
  }
  if ((c > 0) && (r < height - 1)) {
    if  (mine_at(c - 1, r + 1)) {
      ++i;
    }
  }
  if (r > 0) {
    if (mine_at(c, r - 1)) {
      ++i;
    }
    if ((c > 0) && (r > 0)) {
      if  (mine_at(c - 1, r - 1)) {
        ++i;
      }
    }
  }
  return i;
}

bool step(const int c, const int r, const int width, const int height) {
  int i = 0;
  if (r > 0) {
    i = width*r + c;
  } else
    i = c;

  if (mine_at(c,r) == true) {
    *(map + i) = MINE;
    return true;
  } else
    if (*(map + i) == UNKNOWN) {
    *(map + i) = mines(c, r, width, height);
  }
  return false;
}

bool step_adv(const int c, const int r, const int width, const int height) {
  assert(c < width);
  assert(r < height);
  int i = width*r + c;
  if (mine_at(c,r) == true) {
    *(map + i) = MINE;
    return true;
  } else
    if (*(map + i) != UNKNOWN) {
    return false;
  } else {
    *(map + i) = mines(c, r, width, height);
    if (*(map + i) == 0) {
      if (c < width - 1) {
        step_adv(c + 1, r, width, height);
      }
      if ((c < width - 1) && (r < height - 1)) {
        step_adv(c + 1, r + 1, width, height);
      }
      if ((c < width - 1) && (r > 0)) {
        step_adv(c + 1, r - 1, width, height);
      }
      if (r < height - 1) {
        step_adv(c, r + 1, width, height);
      }
      if (c > 0) {
        step_adv(c - 1, r, width, height);
      }
      if ((c > 0) && (r < height - 1)) {
        step_adv(c - 1, r + 1, width, height);
      }
      if (r > 0) {
        step_adv(c, r - 1, width, height);
      }
      if ((c > 0) && (r > 0)) {
        step_adv(c - 1, r - 1, width, height);
      }
    }
    return false;
  }
}


bool mark(const int c, const int r, int width, int height) {

  int i = 0;
  if (r > 0) {
    i = width*r + c;
  } else
    i = c;
  if (*(map + i) == MARKED) {
    *(map + i) = UNKNOWN;
  } else
    if (mine_at(c,r) == true) {
    *(map + i) = MARKED;
  }
  if (all_marked() == true) {
    return true;
  } else 
    return false;
}

void print(int width, int height) {
  int i = 0;
  int j = 0;
  while(j < ((width) * (height))) {
    if (*(map + j) == UNKNOWN) {
      if (i == width - 1) {
        printf("_");
        printf("\n");
      } else
        printf("_ ");
    } else
      if (*(map + j) == MARKED) {
      if (i == width - 1) {
        printf("P");
        printf("\n");
      } else
        printf("P ");
    } else
      if (*(map + j) == MINE) {
      if (i == width - 1) {
        printf("X");
        printf("\n");
      } else
        printf("X ");
    } else
      if (i == width - 1) {
      printf("%d", *(map + j));
      printf("\n");
    } else
      printf("%d ", *(map + j));       
    ++j;
    ++i;
    if (i == width) {
      i = 0;
    }
  }
}
