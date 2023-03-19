#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value_exp(double value1, double value2){
	return make_expr_value(value1*pow(10, value2));
}

struct ast_node *make_expr_value(double value) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	return node;
}

struct ast_node *make_expr_binop(struct ast_node *expr0, struct ast_node *expr1, char c) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BINOP;
	node->u.op = c;
	node->children_count = 2;
  node->children[0] = expr0;
	node->children[1] = expr1;
	return node;
}

struct ast_node *make_expr_unop(struct ast_node *expr, char c) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_UNOP;
	node->u.op = c;
	node->children_count = 1;
  node->children[0] = expr;
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

struct ast_node *make_cmd_backward(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_position(struct ast_node *exprX, struct ast_node *exprY) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 1;
  node->children[0] = exprX;
	node->children[1] = exprY;
  return node;
}

struct ast_node *make_cmd_print(struct ast_node *toPrint) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_PRINT;
  node->children_count = 1;
  node->children[0] = toPrint;
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

struct ast_node *make_cmd_left(struct ast_node *expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HEADING;
  node->children_count = 1;
  node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_home() {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HOME;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_up() {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
	node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_down(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  node->children_count = 0;
  return node;
}

struct ast_node *make_fcn_sin(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.cmd = FUNC_SIN;
  node->children_count = 1;
	node->children[0] = expr;
  return node;
}

struct ast_node *make_fcn_cos(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.cmd = FUNC_COS;
  node->children_count = 1;
	node->children[0] = expr;
  return node;
}

struct ast_node *make_fcn_tan(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.cmd = FUNC_TAN;
  node->children_count = 1;
	node->children[0] = expr;
  return node;
}

struct ast_node *make_fcn_sqrt(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.cmd = FUNC_SQRT;
  node->children_count = 1;
	node->children[0] = expr;
  return node;
}

struct ast_node *make_fcn_random(struct ast_node *expr0, struct ast_node *expr1){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.cmd = FUNC_RANDOM;
  node->children_count = 2;
	node->children[0] = expr0;
	node->children[1] = expr1;
  return node;
}

struct ast_node *make_cmd_block(struct ast_node *cmds){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_BLOCK;
	node->children_count = 1;
  node->children[0] = cmds;
	return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_REPEAT;
	node->children_count = 2;
	node->children[0] = expr;
  node->children[1] = cmd;
	return node;
}


struct ast_node *make_cmd_set(char *name, struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SET;
	//we set the name directly inside the cmd set
	node->u.name = calloc(strlen(name)+1, sizeof(char));
	strcpy(node->u.name, name);
	node->children_count = 1;
  node->children[0] = expr;
	return node;
}

struct ast_node *make_expr_name(char *name){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_NAME;
	node->u.name = calloc(strlen(name)+1, sizeof(char));
	strcpy(node->u.name, name);
	node->children_count = 0;
	return node;
}

struct ast_node *make_cmd_proc(char *name, struct ast_node *cmd){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_PROC;
	//we set the name directly inside the cmd set
	node->u.name = calloc(strlen(name)+1, sizeof(char));
	strcpy(node->u.name, name);
	node->children_count = 1;
  node->children[0] = cmd;
	return node;
}

struct ast_node *make_cmd_call(char *name){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_CALL;
	node->u.name = calloc(strlen(name)+1, sizeof(char));
	strcpy(node->u.name, name);
	node->children_count = 0;
	return node;
}

void ast_destroy(struct ast *self) {

}

/*
	get the associate node of a variable or a procedure in the given set
*/
struct ast_node *get_from_context(char *name, struct ast_set *self){
	if (self->unit == NULL) {
		return NULL;
	}
	struct ast_node_set *actual = self->unit;
	while (actual != NULL) {
		if (strcmp(name, actual->name) == 0) {
			return actual->node;
		}
		actual = actual->next;
	}
	return NULL;
}

/*
	add a variable or a procedure to the given set
*/
void set_to_context(char *name, struct ast_node *node, struct ast_set *self) {
	if (self->unit == NULL) {
		struct ast_node_set *set = calloc(1, sizeof(struct ast_node_set));
		set->name = calloc(strlen(name)+1, sizeof(char));
		strcpy(set->name, name);
		set->node = node;
		set->next = NULL;
		self->unit = set;
		return;
	}
	struct ast_node_set *prec = self->unit;
	struct ast_node_set *actual = prec->next;
	while (actual != NULL) {
		if (strcmp(name, actual->name) == 0) {
			free(actual->node);
			actual->node = node;
			return;
		}
		prec = actual;
		actual = prec->next;
	}
	if (strcmp(name, prec->name) == 0) {
		prec->node = node;
		return;
	}
	struct ast_node_set *set = calloc(1, sizeof(struct ast_node_set));
	set->name = calloc(strlen(name)+1, sizeof(char));
	strcpy(set->name, name);
	set->node = node;
	set->next = NULL;
	prec->next = set;

}

void free_ast_node_set(struct ast_node_set *self){
	if (self != NULL) {
		free_ast_node_set(self->next);
		free(self->name);
		self->name = NULL;
		if (self->next != NULL) {
			free(self->next);
			self->next = NULL;
		}
	}
}

void free_ast_set(struct ast_set *self){
	free_ast_node_set(self->unit);
	free(self->unit);
	self->unit = NULL;
}

/*
 * context
 */

void context_reset(struct context *self){
	self->x = 0;
	self->y = 0;
	self->angle = 90;
	self->up = false;
	free_ast_set(self->variables);
	struct ast_node_set *pi = calloc(1, sizeof(struct ast_node_set));
	pi->name = calloc(3, sizeof(char));
	strcpy(pi->name, "PI");
	pi->node = make_expr_value(3.14159265358979323846);
	pi->next = NULL;

	struct ast_node_set *sqrt2 = calloc(1, sizeof(struct ast_node_set));
	sqrt2->name = calloc(6, sizeof(char));
	strcpy(sqrt2->name, "SQRT2");
	sqrt2->node = make_expr_value(1.41421356237309504880);
	sqrt2->next = pi;

	struct ast_node_set *sqrt3 = calloc(1, sizeof(struct ast_node_set));
	sqrt3->name = calloc(6, sizeof(char));
	strcpy(sqrt3->name, "SQRT3");
	sqrt3->node = make_expr_value(1.7320508075688772935);
	sqrt3->next = sqrt2;

	self->variables->unit = sqrt3;
	free_ast_set(self->procedures);
	self->procedures->unit = NULL;
 }

void context_create(struct context *self) {
	self->x = 0;
	self->y = 0;
	self->angle = 90;
	self->up = false;
	self->variables = calloc(1, sizeof(struct ast_set));
	self->procedures = calloc(1, sizeof(struct ast_set));

	struct ast_node_set *pi = calloc(1, sizeof(struct ast_node_set));
	pi->name = calloc(3, sizeof(char));
	strcpy(pi->name, "PI");
	pi->node = make_expr_value(3.14159265358979323846);
	pi->next = NULL;

	struct ast_node_set *sqrt2 = calloc(1, sizeof(struct ast_node_set));
	sqrt2->name = calloc(6, sizeof(char));
	strcpy(sqrt2->name, "SQRT2");
	sqrt2->node = make_expr_value(1.41421356237309504880);
	sqrt2->next = pi;

	struct ast_node_set *sqrt3 = calloc(1, sizeof(struct ast_node_set));
	sqrt3->name = calloc(6, sizeof(char));
	strcpy(sqrt3->name, "SQRT3");
	sqrt3->node = make_expr_value(1.7320508075688772935);
	sqrt3->next = sqrt2;

	self->variables->unit = sqrt3;
	self->procedures->unit = NULL;


}

double transform_radian(double angle){
	return angle*PI/180;
}

double ast_eval_expr(const struct ast_node *self, struct context *ctx){
	switch (self->kind) {
		case KIND_EXPR_BINOP:
			switch (self->u.op) {
				case '+':
					return ast_eval_expr(self->children[0], ctx) + ast_eval_expr(self->children[1], ctx);
				case '-':
					return ast_eval_expr(self->children[0], ctx) - ast_eval_expr(self->children[1], ctx);
				case '*':
					return ast_eval_expr(self->children[0], ctx) * ast_eval_expr(self->children[1], ctx);
				case '/':
					return ast_eval_expr(self->children[0], ctx) / ast_eval_expr(self->children[1], ctx);
				case '^':
					return pow(ast_eval_expr(self->children[0], ctx), ast_eval_expr(self->children[1], ctx));
				default :
					fprintf(stderr, "Unknown opperator %c\n", self->u.op);
					exit(1);
			}
		case KIND_EXPR_UNOP:
			if (self->u.op == '-') {
				return -ast_eval_expr(self->children[0], ctx);
			}else{
				return ast_eval_expr(self->children[0], ctx);
			}
		case KIND_EXPR_FUNC:
			switch (self->u.func) {
				case FUNC_SIN:
					return sin(ast_eval_expr(self->children[0], ctx));
				case FUNC_COS:
					return cos(ast_eval_expr(self->children[0], ctx));
				case FUNC_TAN:
					return tan(ast_eval_expr(self->children[0], ctx));
				case FUNC_SQRT:
					return sqrt(ast_eval_expr(self->children[0], ctx));
				case FUNC_RANDOM:
					return ( ( double )rand() * ( ast_eval_expr(self->children[1], ctx) - ast_eval_expr(self->children[0], ctx) ) ) / ( double )RAND_MAX + ast_eval_expr(self->children[0], ctx);
				default:
					fprintf(stderr, "Unknown function\n");
					exit(3);
			}
			break;
		case KIND_EXPR_NAME:
			struct ast_node *expr = get_from_context(self->u.name, ctx->variables);
			if (expr == NULL) {
				fprintf(stderr, "var %s isn't set !\n", self->u.name);
				exit(4);
			}
			return ast_eval_expr(expr, ctx);
			break;
		default:
			break;
	}
	return self->u.value;
}


void ast_eval_recu(const struct ast_node *self, struct context *ctx) {
	switch (self->kind) {
		case KIND_EXPR_VALUE:
			printf("%f \n", self->u.value);
			break;
		case KIND_CMD_SIMPLE:
			switch (self->u.cmd) {
				case CMD_FORWARD:
					ctx->x += ast_eval_expr(self->children[0], ctx)*cos(transform_radian(ctx->angle));
					ctx->y -= ast_eval_expr(self->children[0], ctx)*sin(transform_radian(ctx->angle));
					if (!ctx->up) {
						printf("LineTo %f %f\n", ctx->x, ctx->y);
					}
					break;
				case CMD_BACKWARD:
					ctx->x -= ast_eval_expr(self->children[0], ctx)*cos(transform_radian(ctx->angle));
					ctx->y += ast_eval_expr(self->children[0], ctx)*sin(transform_radian(ctx->angle));
					if (!ctx->up) {
						printf("LineTo %f %f\n", ctx->x, ctx->y);
					}
	 				break;
				case CMD_RIGHT:
					ctx->angle -= ast_eval_expr(self->children[0], ctx);
					break;
				case CMD_LEFT:
	 				ctx->angle += ast_eval_expr(self->children[0], ctx);
	 				break;
				case CMD_HEADING:
	 				ctx->angle = ast_eval_expr(self->children[0], ctx) + 90;
	 				break;
				case CMD_POSITION:
	 				ctx->x = ast_eval_expr(self->children[0], ctx);
					ctx->y = ast_eval_expr(self->children[1], ctx);
					printf("MoveTo %f %f\n", ctx->x, ctx->y);
	 				break;
				case CMD_HOME:
	 				context_reset(ctx);
					printf("MoveTo %f %f\n", ctx->x, ctx->y);
	 				break;
				case CMD_UP:
	 				ctx->up = true;
	 				break;
				case CMD_DOWN:
	 				ctx->up = false;
	 				break;
				case CMD_COLOR:
					printf("Color %f %f %f\n", ast_eval_expr(self->children[0], ctx), ast_eval_expr(self->children[1], ctx), ast_eval_expr(self->children[2], ctx));
					break;
				case CMD_PRINT:
	 				fprintf(stderr, "print ");
					ast_print_recu(self->children[0]);
					fprintf(stderr, "\n");
	 				break;
				default:
					fprintf(stderr, "type of commands not found\n");
					exit(1);
			}
			break;
		case KIND_CMD_BLOCK:
			ast_eval_recu(self->children[0], ctx);
			break;
		case KIND_CMD_SET:
			set_to_context(self->u.name, self->children[0], ctx->variables);
			break;
		case KIND_CMD_PROC:
			set_to_context(self->u.name, self->children[0], ctx->procedures);
			break;
		case KIND_CMD_CALL:
			struct ast_node *cmd = get_from_context(self->u.name, ctx->procedures);
			if (cmd == NULL) {
				fprintf(stderr, "proc %s isn't set !\n", self->u.name);
				exit(4);
			}
			ast_eval_recu(cmd, ctx);
			break;
		case KIND_CMD_REPEAT:
			int nb_repeat = floor(ast_eval_expr(self->children[0], ctx));
			if (nb_repeat < 0) {
				fprintf(stderr, "number of repeat must be positif, actual value : %d\n", nb_repeat);
				exit(2);
			}
			for (size_t i = 0; i < nb_repeat; i++) {
				ast_eval_recu(self->children[1], ctx);
			}
			break;
		default :
			fprintf(stderr, "Unknown command\n");
			exit(1);
	}
	if (self->next != NULL) {
		ast_eval_recu(self->next, ctx);
	}
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {
	srand(time(0));
	ast_eval_recu(self->unit, ctx);
}

/*
 * print
 */


void ast_print_recu(const struct ast_node *self) {

	switch (self->kind) {
		case KIND_EXPR_VALUE:
			fprintf(stderr, "%f ", self->u.value);
			break;
		case KIND_CMD_SIMPLE:
			switch (self->u.cmd) {
				case CMD_FORWARD:
					fprintf(stderr, "forward ");
					break;
				case CMD_BACKWARD:
					fprintf(stderr, "backward ");
					break;
				case CMD_RIGHT:
					fprintf(stderr, "right ");
					break;
				case CMD_LEFT:
					fprintf(stderr, "left ");
					break;
				case CMD_HEADING:
	 				fprintf(stderr, "heading ");
	 				break;
				case CMD_POSITION:
					fprintf(stderr, "position ");
					break;
				case CMD_HOME:
					fprintf(stderr, "home ");
					break;
				case CMD_UP:
					fprintf(stderr, "up ");
					break;
				case CMD_DOWN:
					fprintf(stderr, "down ");
					break;
				case CMD_COLOR:
					fprintf(stderr, "color ");
					break;
				case CMD_PRINT:
	 				fprintf(stderr, "print ");
					break;
				default:
					fprintf(stderr, "commands not found\n");
					exit(1);
			}
			for (size_t i = 0; i < self->children_count; i++) {
		 		ast_print_recu(self->children[i]);
		 	}
			break;
		case KIND_EXPR_BINOP:
			switch (self->u.op) {
				case '+':
				 	ast_print_recu(self->children[0]);
					fprintf(stderr, " + ");
					ast_print_recu(self->children[1]);
					break;
				case '-':
					ast_print_recu(self->children[0]);
					fprintf(stderr, " - ");
					ast_print_recu(self->children[1]);
					break;
				case '*':
					ast_print_recu(self->children[0]);
					fprintf(stderr, " * ");
					ast_print_recu(self->children[1]);
					break;
				case '/':
					ast_print_recu(self->children[0]);
					fprintf(stderr, " / ");
					ast_print_recu(self->children[1]);
					break;
				case '^':
					ast_print_recu(self->children[0]);
					fprintf(stderr, " ^ ");
					ast_print_recu(self->children[1]);
					break;
				default :
					fprintf(stderr, "Unknown opperator %c\n", self->u.op);
					exit(1);
			}
			break;
		case KIND_EXPR_UNOP:
			if (self->u.op == '-') {
				fprintf(stderr, "- ");
				ast_print_recu(self->children[0]);
			}else{
				fprintf(stderr, "(");
				ast_print_recu(self->children[0]);
				fprintf(stderr, ")");
			}
			break;
		case KIND_CMD_BLOCK:
			fprintf(stderr, "{");
			ast_print_recu(self->children[0]);
			fprintf(stderr, "}");
			break;
		case KIND_CMD_SET:
			fprintf(stderr, "set %s", self->u.name);
			ast_print_recu(self->children[0]);
			break;
		case KIND_EXPR_NAME:
			fprintf(stderr, "%s", self->u.name);
			break;
		case KIND_EXPR_FUNC:
			switch (self->u.func) {
				case FUNC_SIN:
					fprintf(stderr, "sin (");
					ast_print_recu(self->children[0]);
					fprintf(stderr, ")");
					break;
				case FUNC_COS:
					fprintf(stderr, "cos (");
					ast_print_recu(self->children[0]);
					fprintf(stderr, ")");
					break;
				case FUNC_TAN:
					fprintf(stderr, "tan (");
					ast_print_recu(self->children[0]);
					fprintf(stderr, ")");
					break;
				case FUNC_SQRT:
					fprintf(stderr, "sqrt (");
					ast_print_recu(self->children[0]);
					fprintf(stderr, ")");
					break;
				case FUNC_RANDOM:
					fprintf(stderr, "random (");
					ast_print_recu(self->children[0]);
					fprintf(stderr, ",");
					ast_print_recu(self->children[1]);
					fprintf(stderr, ")");
					break;
			}
			break;
		default :
			fprintf(stderr, "commands not found\n");
			exit(1);
	}

 	if (self->next != NULL) {
 		fprintf(stderr,"\n");
 		ast_print_recu(self->next);
 	}
 }

void ast_print(const struct ast *self) {
	ast_print_recu(self->unit);
	fprintf(stderr,"\n");
}
