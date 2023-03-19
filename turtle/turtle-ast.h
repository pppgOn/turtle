#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
	CMD_UP,
	CMD_DOWN,
	CMD_RIGHT,
	CMD_LEFT,
	CMD_HEADING,
	CMD_FORWARD,
	CMD_BACKWARD,
	CMD_POSITION,
	CMD_HOME,
	CMD_COLOR,
	CMD_PRINT,
};

// internal functions
enum ast_func {
	FUNC_COS,
	FUNC_RANDOM,
	FUNC_SIN,
	FUNC_SQRT,
	FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
	KIND_CMD_SIMPLE,
	KIND_CMD_REPEAT,
	KIND_CMD_BLOCK,
	KIND_CMD_PROC,
	KIND_CMD_CALL,
	KIND_CMD_SET,

	KIND_EXPR_FUNC,
	KIND_EXPR_VALUE,
	KIND_EXPR_UNOP,
	KIND_EXPR_BINOP,
	KIND_EXPR_BLOCK,
	KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
	enum ast_kind kind; // kind of the node

	union {
		enum ast_cmd cmd;	 // kind == KIND_CMD_SIMPLE
		double value;			 // kind == KIND_EXPR_VALUE, for literals
		char op;						// kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
		char *name;				 // kind == KIND_EXPR_NAME, the name of procedures and variables
		enum ast_func func; // kind == KIND_EXPR_FUNC, a function
	} u;

	size_t children_count;	// the number of children of the node
	struct ast_node *children[AST_CHILDREN_MAX];	// the children of the node (arguments of commands, etc)
	struct ast_node *next;	// the next node in the sequence
};


// TODO: make some constructors to use in parser.y
// for example:
struct ast_node *make_expr_value(double value);
struct ast_node *make_expr_value_exp(double value1, double value2);
struct ast_node *make_cmd_color(struct ast_node *exprRed, struct ast_node *exprGreen, struct ast_node *exprBlue);
struct ast_node *make_cmd_color_value(double valueRed, double valueGreen, double valueBlue);
struct ast_node *make_cmd_forward(struct ast_node *expr);
struct ast_node *make_cmd_right(struct ast_node *expr);
struct ast_node *make_cmd_backward(struct ast_node *expr);
struct ast_node *make_cmd_left(struct ast_node *expr);
struct ast_node *make_cmd_heading(struct ast_node *expr);
struct ast_node *make_cmd_print(struct ast_node *toPrint);
struct ast_node *make_cmd_position(struct ast_node *exprX, struct ast_node *exprY);
struct ast_node *make_cmd_home();
struct ast_node *make_cmd_up();
struct ast_node *make_cmd_down();

struct ast_node *make_cmd_set(char *name, struct ast_node *expr);
struct ast_node *make_expr_name(char *name);
struct ast_node *make_cmd_proc(char *name, struct ast_node *cmd);
struct ast_node *make_cmd_call(char *name);

struct ast_node *make_fcn_sin(struct ast_node *expr);
struct ast_node *make_fcn_cos(struct ast_node *expr);
struct ast_node *make_fcn_tan(struct ast_node *expr);
struct ast_node *make_fcn_sqrt(struct ast_node *expr);
struct ast_node *make_fcn_random(struct ast_node *expr0, struct ast_node *expr1);

struct ast_node *make_expr_binop(struct ast_node *expr0, struct ast_node *expr1, char c);
struct ast_node *make_expr_unop(struct ast_node *expr, char c);

struct ast_node *make_cmd_block(struct ast_node *cmds);
struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd);
// root of the abstract syntax tree
struct ast {
	struct ast_node *unit;
};

// linked list to handle variables and procedures
struct ast_set {
	struct ast_node_set *unit;
};

struct ast_node_set {
	char *name;
	struct ast_node *node;
	struct ast_node_set *next;
};

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);

// the execution context
struct context {
	double x;
	double y;
	double angle;
	bool up;
	struct ast_set *variables;
	struct ast_set *procedures;
};

// add, read and free the linked list (ast_set)
struct ast_node *get_from_context(char *name, struct ast_set *self);
void set_to_context(char *name, struct ast_node *node, struct ast_set *self);
void free_ast_set(struct ast_set *self);

// create an initial context
void context_create(struct context *self);

void ast_print_recu(const struct ast_node *self);
// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);


void ast_eval_recu(const struct ast_node *self, struct context *ctx);
// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);

#endif /* TURTLE_AST_H */
