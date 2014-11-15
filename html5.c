#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "html5.h"

void html_tag_start(const char *, const char *, ...);
void html_tag_end(const char *);

void html_tag_start(const char *tag, const char *properties, ...) {
va_list args;
	fprintf(stdout, "<%s", tag);
	if (strcmp(properties, "")) {
		va_start(args, properties);
		vfprintf(stdout, properties, args);
		va_end(args);
	}
	fprintf(stdout, ">\n");
}

void html_tag_end(const char *tag) {
	fprintf(stdout, "</%s>\n", tag);
}

void html_start(const char *dir, const char *lang) {
	html_tag_start("!DOCTYPE HTML", "");
	html_tag_start("HTML", " DIR=\"%s\" LANG=\"%s\"", dir, lang);
}

void html_end(void) {
	html_tag_end("HTML");
	fflush(stdout);
}

void html_head_start(void) {
	html_tag_start("HEAD", "");
}

void html_head_end(void) {
	html_tag_end("HEAD");
}

void html_meta(const char *name, const char *value, const char *content) {
	html_tag_start("META", " %s=\"%s\" CONTENT=\"%s\"", name, value, content);
}

void html_title(const char *text, ...) {
va_list args;
	html_tag_start("TITLE", "");
	va_start(args, text);
	vfprintf(stdout, text, args);
	va_end(args);
	html_tag_end("TITLE");
}

void html_style_start(const char *type) {
	html_tag_start("STYLE", " TYPE=\"%s\"", type);
}

void html_style_end(void) {
	html_tag_end("STYLE");
}

void html_text_css(const char *class, const char *properties, ...) {
va_list args;
	fprintf(stdout, "%s { ", class);
	va_start(args, properties);
	vfprintf(stdout, properties, args);
	va_end(args);
	fprintf(stdout, " }\n");
}

void html_body_start(void) {
	html_tag_start("BODY", "");
}

void html_body_end(void) {
	html_tag_end("BODY");
}

void html_div_start(const char *class) {
	if (strcmp(class, "")) html_tag_start("DIV", " CLASS=\"%s\"", class);
	else html_tag_start("DIV", "");
}

void html_div_end(void) {
	html_tag_end("DIV");
}

void html_h1_start(const char *class) {
	if (strcmp(class, "")) html_tag_start("H1", " CLASS=\"%s\"", class);
	else html_tag_start("H1", "");
}

void html_h1_end(void) {
	html_tag_end("H1");
}

void html_a_start(const char *href, const char *target) {
	if (strcmp(href, ""))
		if (strcmp(target, "")) html_tag_start("A", " HREF=\"%s\" TARGET=\"%s\"", href, target);
		else html_tag_start("A", " HREF=\"%s\"", href);
	else
		if (strcmp(target, "")) html_tag_start("A", " TARGET=\"%s\"", target);
		else html_tag_start("A", "");
}

void html_a_end(void) {
	html_tag_end("A");
}

void html_a(const char *href, const char *target, const char *text, ...) {
va_list args;
	html_a_start(href, target);
	va_start(args, text);
	vfprintf(stdout, text, args);
	va_end(args);
	html_a_end();
}

void html_table_start(const char *class) {
	if (strcmp(class, "")) html_tag_start("TABLE", " CLASS=\"%s\"", class);
	else html_tag_start("TABLE", "");
}

void html_table_end(void) {
	html_tag_end("TABLE");
}

void html_caption_start(const char *class) {
	if (strcmp(class, "")) html_tag_start("CAPTION", " CLASS=\"%s\"", class);
	else html_tag_start("CAPTION", "");
}

void html_caption_end(void) {
	html_tag_end("CAPTION");
}

void html_caption(const char *class, const char *text, ...) {
va_list args;
	html_caption_start(class);
	va_start(args, text);
	vfprintf(stdout, text, args);
	va_end(args);
	html_caption_end();
}

void html_tr_start(const char *class) {
	if (strcmp(class, "")) html_tag_start("TR", " CLASS=\"%s\"", class);
	else html_tag_start("TR", "");
}

void html_tr_end(void) {
	html_tag_end("TR");
}

void html_td_start(const char *class, unsigned colspan) {
	if (strcmp(class, ""))
		if (colspan > 1) html_tag_start("TD", " CLASS=\"%s\" COLSPAN=%u", class, colspan);
		else html_tag_start("TD", " CLASS=\"%s\"", class);
	else
		if (colspan > 1) html_tag_start("TD", " COLSPAN=%u", colspan);
		else html_tag_start("TD", "");
}

void html_td_end(void) {
	html_tag_end("TD");
}
