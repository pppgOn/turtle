#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	return node;
}


struct ast_node *make_cmd_forward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_color(struct ast_node *exprRed, struct ast_node *exprGreen, struct ast_node *exprBlue) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 3;
  node->children[0] = exprRed;
  node->children[1] = exprGreen;
  node->children[2] = exprBlue;
  return node;
}


struct ast_node *make_cmd_color_value(double valueRed, double valueGreen, double valueBlue) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 3;
  node->children[0] = make_expr_value(valueRed);
  node->children[1] = make_expr_value(valueGreen);
  node->children[2] = make_expr_value(valueBlue);
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {
	self->x = 0;
	self->y = 0;
	self->angle = 0;
	self->up = false;
}


void ast_eval_recu(const struct ast_node *self, struct context *ctx) {

}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {
	ast_eval_recu(self->unit, ctx);
}

/*
 * print
 */

void ast_print(const struct ast *self) {
	// self.unit
}
