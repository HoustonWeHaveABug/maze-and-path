#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mtrand.h"
#include "html5.h"

#define N_OPENED 1
#define S_OPENED 2
#define W_OPENED 4
#define E_OPENED 8
#define V_MARKED 16
#define P_MARKED 32
#define SZPX_MIN 400

typedef struct cell_s cell_t;

struct cell_s {
	int mask;
	unsigned rank;
	cell_t *root;
};

void init_cell(cell_t *);
cell_t *find_root(cell_t *);
int create_maze(unsigned, unsigned, unsigned, cell_t *);
void add_to_queue(cell_t *, int, cell_t *, cell_t **, unsigned *);
int search_path(unsigned, unsigned, cell_t *, cell_t *);
void text_output(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, const cell_t *);
unsigned test_class(unsigned, const char *, const char *);
void html_output(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, const cell_t *);

void init_cell(cell_t *cell) {
	cell->mask = 0;
	cell->rank = 0;
	cell->root = cell;
}

cell_t *find_root(cell_t *cell) {
	if (cell->root != cell) cell->root = find_root(cell->root);
	return cell->root;
}

int create_maze(unsigned r, unsigned c, unsigned rc, cell_t *cells) {
int mask;
unsigned *walls, w = rc*2-r-c, i, opened, rcm1 = rc-1, rcmr = rc-r, rw, cm1 = c-1;
cell_t *cell1, *cell2, *root1, *root2;
	if (!(walls = malloc(sizeof(unsigned)*w))) return 0;
	for (i = 0; i < w; i++) walls[i] = i;
	smtrand((unsigned long)time(NULL));
	opened = 0;
	while (opened < rcm1) {
		if (walls[i = emtrand(w)] < rcmr) {
			rw = walls[i]/cm1;
			cell1 = &cells[rw*cm1+walls[i]%cm1+rw];
			cell2 = cell1+1;
			mask = E_OPENED;
		}
		else {
			cell1 = &cells[walls[i]/c*c+walls[i]%c-rcmr];
			cell2 = cell1+c;
			mask = S_OPENED;
		}
		if (!(cell1->mask & mask) && (root1 = find_root(cell1)) != (root2 = find_root(cell2))) {
			if (root1->rank < root2->rank) root1->root = root2;
			else if (root1->rank > root2->rank) root2->root = root1;
			else {
				root1->rank++;
				root2->root = root1;
			}
			cell1->mask += mask;
			cell2->mask += mask >> 1;
			opened++;
		}
		walls[i] = walls[--w];
	}
	free(walls);
	return 1;
}

void add_to_queue(cell_t *root, int mask, cell_t *cell, cell_t **queue, unsigned *szqueue) {
	if ((root->mask & mask) && !(cell->mask & V_MARKED)) {
		cell->mask += V_MARKED;
		cell->root = root;
		queue[(*szqueue)++] = cell;
	}
}

int search_path(unsigned c, unsigned rc, cell_t *cell1, cell_t *cell2) {
unsigned szqueue, i;
cell_t **queue, *cell;
	if (!(queue = malloc(sizeof(cell_t *)*rc))) return 0;
	cell1->mask += V_MARKED;
	queue[0] = cell1;
	szqueue = 1;
	for (i = 0; i < szqueue && queue[i] != cell2; i++) {
		add_to_queue(queue[i], N_OPENED, queue[i]-c, queue, &szqueue);
		add_to_queue(queue[i], E_OPENED, queue[i]+1, queue, &szqueue);
		add_to_queue(queue[i], S_OPENED, queue[i]+c, queue, &szqueue);
		add_to_queue(queue[i], W_OPENED, queue[i]-1, queue, &szqueue);
	}
	for (cell = cell2; cell; cell = cell->root) cell->mask += P_MARKED;
	free(queue);
	return 1;
}

void text_output(unsigned r, unsigned c, unsigned sr, unsigned sc, unsigned er, unsigned ec, unsigned rc, const cell_t *cells) {
unsigned i, ipc, j;
	fprintf(stdout, "Maze %ux%u\nPath from %u,%u to %u,%u\n", r, c, sr, sc, er, ec);
	fprintf(stdout, "+");
	for (i = 0; i < c; i++) fprintf(stdout, "-+");
	fprintf(stdout, "\n");
	for (i = 0; i < rc; i += c) {
		ipc = i+c;
		fprintf(stdout, "|");
		for (j = i; j < ipc; j++) {
			fprintf(stdout, cells[j].mask & P_MARKED ? "O":" ");
			fprintf(stdout, cells[j].mask & E_OPENED ? ((cells[j].mask & P_MARKED) && (cells[j+1].mask & P_MARKED) ? "O":" "):"|");
		}
		fprintf(stdout, "\n+");
		for (j = i; j < ipc; j++) {
			fprintf(stdout, cells[j].mask & S_OPENED ? ((cells[j].mask & P_MARKED) && (cells[j+c].mask & P_MARKED) ? "O":" "):"-");
			fprintf(stdout, "+");
		}
		fprintf(stdout, "\n");
	}
	fflush(stdout);
}

unsigned test_class(unsigned colspan, const char *class, const char *lastclass) {
	if (strcmp(class, lastclass)) {
		html_td_start(lastclass, colspan);
		html_td_end();
		return 1;
	}
	else return colspan+1;
}

void html_output(unsigned r, unsigned c, unsigned sr, unsigned sc, unsigned er, unsigned ec, unsigned rc, const cell_t *cells) {
char class[2], lastclass[2];
unsigned sz = c*2+1, px = 1, i, ipc, colspan, j;
	while (sz*px < SZPX_MIN) px++;
	html_start("ltr", "en");
	html_head_start();
	html_meta("HTTP-EQUIV", "Content-Type", "text/html; charset=utf-8");
	html_title("Maze and Path Generator\n");
	html_style_start("text/css");
	html_text_css("BODY", "font-family: Verdana, Geneva, Arial, Helvetica, sans-serif;");
	html_text_css("DIV", "overflow: auto; padding: 2px 6px 2px 6px; text-align: center;");
	html_text_css("DIV.header", "background-color: #008844;");
	html_text_css("H1", "font-size: 18px;");
	html_text_css("A", "color: #CCCCCC; text-decoration: none;");
	html_text_css("A:hover", "color: #EEEEEE;");
	html_text_css("DIV.data", "background-color: #44CC88;");
	html_text_css("TABLE", "border-collapse: collapse; margin: 6px auto 6px auto;");
	html_text_css("CAPTION", "background-color: #008844; color: #EEEEEE; font-size: 14px; font-weight: bold;");
	html_text_css("TD", "height: %upx; width: %upx;", px, px);
	html_text_css("TD.w", "background-color: black;");
	html_text_css("TD.p", "background-color: #EEEEEE;");
	html_text_css("TD.o", "background-color: #888888;");
	html_style_end();
	html_head_end();
	html_body_start();
	html_div_start("header");
	html_h1_start("");
	html_a("https://zestedesavoir.com/forums/sujet/1571/un-petit-labyrinthe/", "_blank", "Maze and Path Generator\n");
	html_h1_end();
	html_div_end();
	html_div_start("data");
	html_table_start("");
	html_caption("", "Maze %ux%u - Path from %u,%u to %u,%u\n", r, c, sr, sc, er, ec);
	html_tr_start("");
	html_td_start("w", sz);
	html_td_end();
	html_tr_end();
	for (i = 0; i < rc; i += c) {
		ipc = i+c;
		html_tr_start("");
		colspan = 1;
		strcpy(class, "w");
		strcpy(lastclass, "?");
		for (j = i; j < ipc; j++) {
			strcpy(lastclass, class);
			strcpy(class, cells[j].mask & P_MARKED ? "p":"o");
			colspan = test_class(colspan, class, lastclass);
			strcpy(lastclass, class);
			strcpy(class, cells[j].mask & E_OPENED ? ((cells[j].mask & P_MARKED) && (cells[j+1].mask & P_MARKED) ? "p":"o"):"w");
			colspan = test_class(colspan, class, lastclass);
		}
		html_td_start(class, colspan);
		html_td_end();
		html_tr_end();
		html_tr_start("");
		colspan = 1;
		strcpy(class, "w");
		strcpy(lastclass, "?");
		for (j = i; j < ipc; j++) {
			strcpy(lastclass, class);
			strcpy(class, cells[j].mask & S_OPENED ? ((cells[j].mask & P_MARKED) && (cells[j+c].mask & P_MARKED) ? "p":"o"):"w");
			colspan = test_class(colspan, class, lastclass);
			strcpy(lastclass, class);
			strcpy(class, "w");
			colspan = test_class(colspan, class, lastclass);
		}
		html_td_start(class, colspan);
		html_td_end();
		html_tr_end();
	}
	html_table_end();
	html_div_end();
	html_body_end();
	html_end();
}

int main(void) {
unsigned r, c, sr, sc, er, ec, rc, output, i;
cell_t *cells;
	fscanf(stdin, "%u", &r);
	if (!r) return EXIT_FAILURE;
	fscanf(stdin, "%u", &c);
	if (!c) return EXIT_FAILURE;
	fscanf(stdin, "%u,%u", &sr, &sc);
	if (!sr || sr > r || !sc || sc > c) return EXIT_FAILURE;
	fscanf(stdin, "%u,%u", &er, &ec);
	if (!er || er > r || !ec || ec > c) return EXIT_FAILURE;
	fscanf(stdin, "%u", &output);
	if (output > 2) return EXIT_FAILURE;
	rc = r*c;
	if (!(cells = malloc(sizeof(cell_t)*rc))) return EXIT_FAILURE;
	for (i = 0; i < rc; i++) init_cell(&cells[i]);
	if (!create_maze(r, c, rc, cells)) {
		free(cells);
		return EXIT_FAILURE;
	}
	for (i = 0; i < rc; i++) cells[i].root = NULL;
	if (!search_path(c, rc, &cells[(sr-1)*c+sc-1], &cells[(er-1)*c+ec-1])) {
		free(cells);
		return EXIT_FAILURE;
	}
	if (output == 1) text_output(r, c, sr, sc, er, ec, rc, cells);
	else if (output == 2) html_output(r, c, sr, sc, er, ec, rc, cells);
	free(cells);
	return EXIT_SUCCESS;
}
