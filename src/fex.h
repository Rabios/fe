// Single file version of fex for fe programming language done by Rabia Alhaffar!
// fex is from rxi/aq, Which licensed under MIT!
/*
Copyright (c) 2019 rxi

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifdef FE_H

#ifndef FEX_H
#define FEX_H

typedef struct { const char *name; fe_CFunc fn; } fex_Reg;

void fex_register_funcs(fe_Context *ctx, fex_Reg *t);
fe_Object* fex_read_string(fe_Context *ctx, const char *str);
fe_Object* fex_do_string(fe_Context *ctx, const char *str);
fe_Object* fex_do_file(fe_Context *ctx, const char *filename);

void fex_register_funcs(fe_Context *ctx, fex_Reg *t) {
  int gc = fe_savegc(ctx);
  for (int i = 0; t[i].name; i++) {
    fe_set(ctx, fe_symbol(ctx, t[i].name), fe_cfunc(ctx, t[i].fn));
    fe_restoregc(ctx, gc);
  }
}

static char read_str(fe_Context *ctx, void *udata) {
  char **p = udata;
  if (!**p) { return '\0'; }
  return *(*p)++;
}

fe_Object* fex_read_string(fe_Context *ctx, const char *str) {
  char *p = (char*) str;
  return fe_read(ctx, read_str, &p);
}

fe_Object* fex_do_string(fe_Context *ctx, const char *str) {
  char *p = (char*) str;
  fe_Object *obj = NULL;
  int gc = fe_savegc(ctx);
  for (;;) {
    fe_restoregc(ctx, gc);
    fe_Object *tmp = fe_read(ctx, read_str, &p);
    if (!tmp) { break; }
    obj = fe_eval(ctx, tmp);
  }
  if (obj) { fe_pushgc(ctx, obj); }
  return obj;
}

fe_Object* fex_do_file(fe_Context *ctx, const char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (!fp) { return NULL; }
  fe_Object *obj = NULL;
  int gc = fe_savegc(ctx);
  for (;;) {
    fe_restoregc(ctx, gc);
    fe_Object* tmp = fe_readfp(ctx, fp);
    if (!tmp) { break; }
    obj = fe_eval(ctx, tmp);
  }
  fclose(fp);
  if (obj) { fe_pushgc(ctx, obj); }
  return obj;
}

#endif
#endif
