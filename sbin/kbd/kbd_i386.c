/*	$OpenBSD: kbd_i386.c,v 1.1 1996/04/22 20:21:55 hannken Exp $	*/

/*
 * Copyright (c) 1996 Juergen Hannken-Illjes
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed for the NetBSD Project
 *	by Juergen Hannken-Illjes.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <machine/pccons.h>
#include <paths.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>

#define NUM_NAMES	10

struct {
	char *name[NUM_NAMES];
	keymap_t map[KB_NUM_KEYS];
} keymaps[] = {

  { { "US/english", "us", "default" },
/*  type       unshift   shift     control   altgr     shift_altgr scancode */
    KB_NONE,   "",       "",       "",       "",       "",  /* 0 unused */
    KB_ASCII,  "\033",   "\033",   "\033",   "",       "",  /* 1 ESCape */
    KB_ASCII,  "1",      "!",      "!",      "",       "",  /* 2 1 */
    KB_ASCII,  "2",      "@",      "\000",   "",       "",  /* 3 2 */
    KB_ASCII,  "3",      "#",      "#",      "",       "",  /* 4 3 */
    KB_ASCII,  "4",      "$",      "$",      "",       "",  /* 5 4 */
    KB_ASCII,  "5",      "%",      "%",      "",       "",  /* 6 5 */
    KB_ASCII,  "6",      "^",      "\036",   "",       "",  /* 7 6 */
    KB_ASCII,  "7",      "&",      "&",      "",       "",  /* 8 7 */
    KB_ASCII,  "8",      "*",      "\010",   "",       "",  /* 9 8 */
    KB_ASCII,  "9",      "(",      "(",      "",       "",  /* 10 9 */
    KB_ASCII,  "0",      ")",      ")",      "",       "",  /* 11 0 */
    KB_ASCII,  "-",      "_",      "\037",   "",       "",  /* 12 - */
    KB_ASCII,  "=",      "+",      "+",      "",       "",  /* 13 = */
    KB_ASCII,  "\177",   "\177",   "\010",   "",       "",  /* 14 backspace */
    KB_ASCII,  "\t",     "\177\t", "\t",     "",       "",  /* 15 tab */
    KB_ASCII,  "q",      "Q",      "\021",   "",       "",  /* 16 q */
    KB_ASCII,  "w",      "W",      "\027",   "",       "",  /* 17 w */
    KB_ASCII,  "e",      "E",      "\005",   "",       "",  /* 18 e */
    KB_ASCII,  "r",      "R",      "\022",   "",       "",  /* 19 r */
    KB_ASCII,  "t",      "T",      "\024",   "",       "",  /* 20 t */
    KB_ASCII,  "y",      "Y",      "\031",   "",       "",  /* 21 y */
    KB_ASCII,  "u",      "U",      "\025",   "",       "",  /* 22 u */
    KB_ASCII,  "i",      "I",      "\011",   "",       "",  /* 23 i */
    KB_ASCII,  "o",      "O",      "\017",   "",       "",  /* 24 o */
    KB_ASCII,  "p",      "P",      "\020",   "",       "",  /* 25 p */
    KB_ASCII,  "[",      "{",      "\033",   "",       "",  /* 26 [ */
    KB_ASCII,  "]",      "}",      "\035",   "",       "",  /* 27 ] */
    KB_ASCII,  "\r",     "\r",     "\n",     "",       "",  /* 28 return */
    KB_CTL,    "",       "",       "",       "",       "",  /* 29 control */
    KB_ASCII,  "a",      "A",      "\001",   "",       "",  /* 30 a */
    KB_ASCII,  "s",      "S",      "\023",   "",       "",  /* 31 s */
    KB_ASCII,  "d",      "D",      "\004",   "",       "",  /* 32 d */
    KB_ASCII,  "f",      "F",      "\006",   "",       "",  /* 33 f */
    KB_ASCII,  "g",      "G",      "\007",   "",       "",  /* 34 g */
    KB_ASCII,  "h",      "H",      "\010",   "",       "",  /* 35 h */
    KB_ASCII,  "j",      "J",      "\n",     "",       "",  /* 36 j */
    KB_ASCII,  "k",      "K",      "\013",   "",       "",  /* 37 k */
    KB_ASCII,  "l",      "L",      "\014",   "",       "",  /* 38 l */
    KB_ASCII,  ";",      ":",      ";",      "",       "",  /* 39 ; */
    KB_ASCII,  "'",      "\"",     "'",      "",       "",  /* 40 ' */
    KB_ASCII,  "`",      "~",      "`",      "",       "",  /* 41 ` */
    KB_SHIFT,  "",       "",       "",       "",       "",  /* 42 shift */
    KB_ASCII,  "\\",     "|",      "\034",   "",       "",  /* 43 \ */
    KB_ASCII,  "z",      "Z",      "\032",   "",       "",  /* 44 z */
    KB_ASCII,  "x",      "X",      "\030",   "",       "",  /* 45 x */
    KB_ASCII,  "c",      "C",      "\003",   "",       "",  /* 46 c */
    KB_ASCII,  "v",      "V",      "\026",   "",       "",  /* 47 v */
    KB_ASCII,  "b",      "B",      "\002",   "",       "",  /* 48 b */
    KB_ASCII,  "n",      "N",      "\016",   "",       "",  /* 49 n */
    KB_ASCII,  "m",      "M",      "\r",     "",       "",  /* 50 m */
    KB_ASCII,  ",",      "<",      "<",      "",       "",  /* 51 , */
    KB_ASCII,  ".",      ">",      ">",      "",       "",  /* 52 . */
    KB_ASCII,  "/",      "?",      "\037",   "",       "",  /* 53 / */
    KB_SHIFT,  "",       "",       "",       "",       "",  /* 54 shift */
    KB_KP,     "*",      "*",      "*",      "",       "",  /* 55 kp * */
    KB_ALT,    "",       "",       "",       "",       "",  /* 56 alt */
    KB_ASCII,  " ",      " ",      "\000",   "",       "",  /* 57 space */
    KB_CAPS,   "",       "",       "",       "",       "",  /* 58 caps */
    KB_FUNC,   "\033[M", "\033[Y", "\033[k", "",       "",  /* 59 f1 */
    KB_FUNC,   "\033[N", "\033[Z", "\033[l", "",       "",  /* 60 f2 */
    KB_FUNC,   "\033[O", "\033[a", "\033[m", "",       "",  /* 61 f3 */
    KB_FUNC,   "\033[P", "\033[b", "\033[n", "",       "",  /* 62 f4 */
    KB_FUNC,   "\033[Q", "\033[c", "\033[o", "",       "",  /* 63 f5 */
    KB_FUNC,   "\033[R", "\033[d", "\033[p", "",       "",  /* 64 f6 */
    KB_FUNC,   "\033[S", "\033[e", "\033[q", "",       "",  /* 65 f7 */
    KB_FUNC,   "\033[T", "\033[f", "\033[r", "",       "",  /* 66 f8 */
    KB_FUNC,   "\033[U", "\033[g", "\033[s", "",       "",  /* 67 f9 */
    KB_FUNC,   "\033[V", "\033[h", "\033[t", "",       "",  /* 68 f10 */
    KB_NUM,    "",       "",       "",       "",       "",  /* 69 num lock */
    KB_SCROLL, "",       "",       "",       "",       "",  /* 70 scroll lock */
    KB_KP,     "7",      "\033[H", "7",      "",       "",  /* 71 kp 7 */
    KB_KP,     "8",      "\033[A", "8",      "",       "",  /* 72 kp 8 */
    KB_KP,     "9",      "\033[I", "9",      "",       "",  /* 73 kp 9 */
    KB_KP,     "-",      "-",      "-",      "",       "",  /* 74 kp - */
    KB_KP,     "4",      "\033[D", "4",      "",       "",  /* 75 kp 4 */
    KB_KP,     "5",      "\033[E", "5",      "",       "",  /* 76 kp 5 */
    KB_KP,     "6",      "\033[C", "6",      "",       "",  /* 77 kp 6 */
    KB_KP,     "+",      "+",      "+",      "",       "",  /* 78 kp + */
    KB_KP,     "1",      "\033[F", "1",      "",       "",  /* 79 kp 1 */
    KB_KP,     "2",      "\033[B", "2",      "",       "",  /* 80 kp 2 */
    KB_KP,     "3",      "\033[G", "3",      "",       "",  /* 81 kp 3 */
    KB_KP,     "0",      "\033[L", "0",      "",       "",  /* 82 kp 0 */
    KB_KP,     ",",      "\177",   ",",      "",       "",  /* 83 kp , */
    KB_NONE,   "",       "",       "",       "",       "",  /* 84 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 85 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 86 0 */
    KB_FUNC,   "\033[W", "\033[i", "\033[u", "",       "",  /* 87 f11 */
    KB_FUNC,   "\033[X", "\033[j", "\033[v", "",       "",  /* 88 f12 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 89 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 90 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 91 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 92 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 93 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 94 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 95 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 96 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 97 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 98 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 99 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 100 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 101 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 102 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 103 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 104 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 105 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 106 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 107 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 108 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 109 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 110 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 111 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 112 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 113 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 114 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 115 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 116 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 117 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 118 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 119 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 120 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 121 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 122 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 123 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 124 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 125 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 126 */
    KB_NONE,   "",       "",       "",       "",       ""   /* 127 */
  },

  { { "German", "german", "deutsch", "ge", "de" },
/*  type       unshift   shift     control   altgr     shift_altgr scancode */
    KB_NONE,   "",       "",       "",       "",       "",  /* 0 unused */
    KB_ASCII,  "\033",   "\033",   "\033",   "",       "",  /* 1 ESCape */
    KB_ASCII,  "1",      "!",      "!",      "",       "",  /* 2 1 */
    KB_ASCII,  "2",      "\"",     "\"",     "\262",   "",  /* 3 2 */
    KB_ASCII,  "3",      "\247",   "\247",   "\263",   "",  /* 4 3 */
    KB_ASCII,  "4",      "$",      "$",      "",       "",  /* 5 4 */
    KB_ASCII,  "5",      "%",      "%",      "",       "",  /* 6 5 */
    KB_ASCII,  "6",      "&",      "&",      "",       "",  /* 7 6 */
    KB_ASCII,  "7",      "/",      "/",      "{",      "",  /* 8 7 */
    KB_ASCII,  "8",      "(",      "\033",   "[",      "",  /* 9 8 */
    KB_ASCII,  "9",      ")",      "\035",   "]",      "",  /* 10 9 */
    KB_ASCII,  "0",      "=",      "=",      "}",      "",  /* 11 0 */
    KB_ASCII,  "\337",   "?",      "\034",   "\\",     "",  /* 12 sz */
    KB_ASCII,  "'",      "`",      "`",      "",       "",  /* 13 = */
    KB_ASCII,  "\177",   "\177",   "\010",   "",       "",  /* 14 backspace */
    KB_ASCII,  "\t",     "\177\t", "\t",     "",       "",  /* 15 tab */
    KB_ASCII,  "q",      "Q",      "\021",   "@",      "",  /* 16 q */
    KB_ASCII,  "w",      "W",      "\027",   "",       "",  /* 17 w */
    KB_ASCII,  "e",      "E",      "\005",   "",       "",  /* 18 e */
    KB_ASCII,  "r",      "R",      "\022",   "",       "",  /* 19 r */
    KB_ASCII,  "t",      "T",      "\024",   "",       "",  /* 20 t */
    KB_ASCII,  "z",      "Z",      "\032",   "",       "",  /* 21 z */
    KB_ASCII,  "u",      "U",      "\025",   "",       "",  /* 22 u */
    KB_ASCII,  "i",      "I",      "\011",   "",       "",  /* 23 i */
    KB_ASCII,  "o",      "O",      "\017",   "",       "",  /* 24 o */
    KB_ASCII,  "p",      "P",      "\020",   "",       "",  /* 25 p */
    KB_ASCII,  "\374",   "\334",   "\374",   "",       "",  /* 26 ue */
    KB_ASCII,  "+",      "*",      "+",      "~",      "",  /* 27 + */
    KB_ASCII,  "\r",     "\r",     "\n",     "",       "",  /* 28 return */
    KB_CTL,    "",       "",       "",       "",       "",  /* 29 control */
    KB_ASCII,  "a",      "A",      "\001",   "",       "",  /* 30 a */
    KB_ASCII,  "s",      "S",      "\023",   "",       "",  /* 31 s */
    KB_ASCII,  "d",      "D",      "\004",   "",       "",  /* 32 d */
    KB_ASCII,  "f",      "F",      "\006",   "",       "",  /* 33 f */
    KB_ASCII,  "g",      "G",      "\007",   "",       "",  /* 34 g */
    KB_ASCII,  "h",      "H",      "\010",   "",       "",  /* 35 h */
    KB_ASCII,  "j",      "J",      "\n",     "",       "",  /* 36 j */
    KB_ASCII,  "k",      "K",      "\013",   "",       "",  /* 37 k */
    KB_ASCII,  "l",      "L",      "\014",   "",       "",  /* 38 l */
    KB_ASCII,  "\366",   "\326",   "\366",   "",       "",  /* 39 oe */
    KB_ASCII,  "\344",   "\304",   "\344",   "",       "",  /* 40 ae */
    KB_ASCII,  "^",      "\260",   "\036",   "",       "",  /* 41 ^ */
    KB_SHIFT,  "",       "",       "",       "",       "",  /* 42 shift */
    KB_ASCII,  "#",      "'",      "#",      "",       "",  /* 43 # */
    KB_ASCII,  "y",      "Y",      "\031",   "",       "",  /* 44 y */
    KB_ASCII,  "x",      "X",      "\030",   "",       "",  /* 45 x */
    KB_ASCII,  "c",      "C",      "\003",   "",       "",  /* 46 c */
    KB_ASCII,  "v",      "V",      "\026",   "",       "",  /* 47 v */
    KB_ASCII,  "b",      "B",      "\002",   "",       "",  /* 48 b */
    KB_ASCII,  "n",      "N",      "\016",   "",       "",  /* 49 n */
    KB_ASCII,  "m",      "M",      "\r",     "\265",   "",  /* 50 m */
    KB_ASCII,  ",",      ";",      ",",      "",       "",  /* 51 , */
    KB_ASCII,  ".",      ":",      ".",      "",       "",  /* 52 . */
    KB_ASCII,  "-",      "_",      "\037",   "",       "",  /* 53 - */
    KB_SHIFT,  "",       "",       "",       "",       "",  /* 54 shift */
    KB_KP,     "*",      "*",      "*",      "",       "",  /* 55 kp * */
    KB_ALT,    "",       "",       "",       "",       "",  /* 56 alt */
    KB_ASCII,  " ",      " ",      "\000",   "",       "",  /* 57 space */
    KB_CAPS,   "",       "",       "",       "",       "",  /* 58 caps */
    KB_FUNC,   "\033[M", "\033[Y", "\033[k", "",       "",  /* 59 f1 */
    KB_FUNC,   "\033[N", "\033[Z", "\033[l", "",       "",  /* 60 f2 */
    KB_FUNC,   "\033[O", "\033[a", "\033[m", "",       "",  /* 61 f3 */
    KB_FUNC,   "\033[P", "\033[b", "\033[n", "",       "",  /* 62 f4 */
    KB_FUNC,   "\033[Q", "\033[c", "\033[o", "",       "",  /* 63 f5 */
    KB_FUNC,   "\033[R", "\033[d", "\033[p", "",       "",  /* 64 f6 */
    KB_FUNC,   "\033[S", "\033[e", "\033[q", "",       "",  /* 65 f7 */
    KB_FUNC,   "\033[T", "\033[f", "\033[r", "",       "",  /* 66 f8 */
    KB_FUNC,   "\033[U", "\033[g", "\033[s", "",       "",  /* 67 f9 */
    KB_FUNC,   "\033[V", "\033[h", "\033[t", "",       "",  /* 68 f10 */
    KB_NUM,    "",       "",       "",       "",       "",  /* 69 num lock */
    KB_SCROLL, "",       "",       "",       "",       "",  /* 70 scroll lock */
    KB_KP,     "7",      "\033[H", "7",      "",       "",  /* 71 kp 7 */
    KB_KP,     "8",      "\033[A", "8",      "",       "",  /* 72 kp 8 */
    KB_KP,     "9",      "\033[I", "9",      "",       "",  /* 73 kp 9 */
    KB_KP,     "-",      "-",      "-",      "",       "",  /* 74 kp - */
    KB_KP,     "4",      "\033[D", "4",      "",       "",  /* 75 kp 4 */
    KB_KP,     "5",      "\033[E", "5",      "",       "",  /* 76 kp 5 */
    KB_KP,     "6",      "\033[C", "6",      "",       "",  /* 77 kp 6 */
    KB_KP,     "+",      "+",      "+",      "",       "",  /* 78 kp + */
    KB_KP,     "1",      "\033[F", "1",      "",       "",  /* 79 kp 1 */
    KB_KP,     "2",      "\033[B", "2",      "",       "",  /* 80 kp 2 */
    KB_KP,     "3",      "\033[G", "3",      "",       "",  /* 81 kp 3 */
    KB_KP,     "0",      "\033[L", "0",      "",       "",  /* 82 kp 0 */
    KB_KP,     ",",      "\177",   ",",      "",       "",  /* 83 kp , */
    KB_NONE,   "",       "",       "",       "",       "",  /* 84 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 85 0 */
    KB_ASCII,  "<",      ">",      "<",      "|",      "",  /* 86 > */
    KB_FUNC,   "\033[W", "\033[i", "\033[u", "",       "",  /* 87 f11 */
    KB_FUNC,   "\033[X", "\033[j", "\033[v", "",       "",  /* 88 f12 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 89 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 90 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 91 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 92 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 93 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 94 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 95 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 96 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 97 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 98 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 99 0 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 100 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 101 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 102 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 103 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 104 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 105 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 106 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 107 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 108 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 109 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 110 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 111 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 112 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 113 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 114 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 115 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 116 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 117 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 118 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 119 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 120 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 121 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 122 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 123 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 124 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 125 */
    KB_NONE,   "",       "",       "",       "",       "",  /* 126 */
    KB_NONE,   "",       "",       "",       "",       ""   /* 127 */
  },

  { { NULL }
  }
};

extern char *__progname;

void
kbd_list()
{
	int i, j;

	printf("tables available:\n%-16s %s\n\n", "encoding", "nick names");
	for (i = 0; keymaps[i].name[0]; i++) {
		printf("%-16s",keymaps[i].name[0]);
		for (j = 1; j < NUM_NAMES && keymaps[i].name[j]; j++)
			printf(" %s", keymaps[i].name[j]);
		printf("\n");
	}
}

void
kbd_set(name, verbose)
	char *name;
	int verbose;
{
	int i, j, fd;
	keymap_t *map = NULL;

	for (i = 0; keymaps[i].name[0]; i++)
		for (j = 0; j < NUM_NAMES && keymaps[i].name[j]; j++)
			if (strcmp(keymaps[i].name[j], name) == 0) {
				name = keymaps[i].name[0];
				map = keymaps[i].map;
				break;
			}

	if (map == NULL) {
		fprintf(stderr, "%s: no such keymap: %s\n", __progname, name);
		exit(1);
	}

	if ((fd = open(_PATH_CONSOLE, O_RDONLY)) < 0)
		err(1, "%s", _PATH_CONSOLE);

	if (ioctl(fd, CONSOLE_SET_KEYMAP, map) < 0)
		err(1, "CONSOLE_SET_KEYMAP");

	close(fd);

	if (verbose)
		fprintf(stderr, "keyboard mapping set to %s\n", name);
}
