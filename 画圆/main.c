#include <base.h>

void DrawCircle(int x0, int y0, int r, int r0, int g, int b) {
  int x, y, c;
  for (x = x0 - r; x <= x0 + r; x++) {
    for (y = y0 - r; y <= y0 + r; y++) {
      c = (x - x0) * (x - x0) + (y - y0) * (y - y0);
      if (c - r * r < r && c - r * r > -r) dpointex(x, y, r0, g, b);
      ref(0, 0, SCRW, SCRH);
    }
  }
}

int init() {
  setscrsize(240, 320);
  cls(0, 0, 0);
  DrawCircle(SCRW / 2, SCRH / 2, SCRW / 2, 255, 0, 0);
  ref(0, 0, SCRW, SCRH);
  return 0;
}

int event(int type, int p1, int p2) {
  if (KY_UP == type) {
    switch (p1) {
      case _SRIGHT:
        exit();
        break;
      case _MENU:
        break;
    }
  }

  return 0;
}

int pause() { return 0; }

int resume() { return 0; }
