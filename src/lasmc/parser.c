#include "node.h"
#include "token.h"

typedef enum {
    NODE_RULE_OP_ON,
    NODE_RULE_OP,
    NODE_RULE_TARGET,
    NODE_RULE_NONE,
} node_rule_type;

struct node_rule {
    char           *keyword;
    node_type       type;
    node_rule_type  rule;
};

static const struct node_rule rules[] = {
    { "add", NTYPE_ADD, NODE_RULE_OP_ON },
    { "sub", NTYPE_SUB, NODE_RULE_OP_ON },
    { "mov", NTYPE_MOV, NODE_RULE_OP },
    { "nop", NTYPE_NOP, NODE_RULE_NONE },
    { "halt", NTYPE_HALT, NODE_RULE_NONE },
};

static char
skip_comma (TokenStream *stream)
{
    Token *tkn = token_stream_next (stream);

    if (tkn->type != TOK_COMMA) {
        g_message ("Expected comma:");
        token_dump (tkn);
        return 0;
    }

    return 0; // TODO
}

static char
parse_reg (TokenStream *stream)
{
    Token *tkn = token_stream_next (stream);

    if (tkn->type != TOK_REGISTER) {
        g_message ("Expected register:");
        token_dump (tkn);
        return 0;
    }

    return 0; // TODO
}

static void
parse_operand (TokenStream *stream, node_op *op)
{
    Token *tkn = token_stream_next (stream);

    switch (tkn->type) {
        case TOK_NUMBER:
            op->type = NOP_IMMEDIATE;
            op->value = 0; // TODO
            break;
        case TOK_REGISTER:
            op->type = NOP_REGISTER;
            op->value = 0; // TODO
            break;
        default:
            g_message ("Expected number or register");
            token_dump (tkn);
    }
}

GPtrArray *
parse (TokenStream *stream, GHashTable *labels)
{
    GPtrArray *nodes = g_ptr_array_new ();
    Token *tkn = NULL;

    while ((tkn = token_stream_next (stream))) {

        if (tkn->type == TOK_LABEL) {
            g_hash_table_insert (labels, tkn->val, GINT_TO_POINTER (nodes->len));
            continue;
        }

        if (tkn->type != TOK_COMMAND) {
            g_message ("Expected command:");
            token_dump (tkn);
            return NULL;
        }

        for (int i = 0; i < sizeof(rules) / sizeof(struct node_rule); i++) {
            if (g_strcmp0 (rules[i].keyword, tkn->val) == 0) {
                switch (rules[i].rule) {
                    case NODE_RULE_OP_ON: {
                        node_op_on op;
                        char dest = parse_reg(stream);
                        op.op.dest = dest;
                        skip_comma (stream);
                        char source = parse_reg(stream);
                        op.source = source;
                        skip_comma (stream);
                        parse_operand (stream, (node_op *) &op);
                        g_ptr_array_add (nodes, node_new_op_on (rules[i].type, NCOND_NONE, op));
                        break;
                    }
                    case NODE_RULE_OP:{
                        node_op op;
                        char dest = parse_reg(stream);
                        op.dest = dest;
                        skip_comma (stream);
                        parse_operand (stream, &op);
                        g_ptr_array_add (nodes, node_new_op (rules[i].type, NCOND_NONE, op));
                        break;
                    }
                    case NODE_RULE_TARGET:
                        tkn = token_stream_next (stream);
                        if (tkn->type != TOK_LABEL) {
                            g_message ("Expected label:");
                            token_dump (tkn);
                            return NULL;
                        }
                        g_ptr_array_add (nodes, node_new_target (rules[i].type, NCOND_NONE, tkn->val));
                        break;
                    case NODE_RULE_NONE:
                        g_ptr_array_add (nodes, node_new (rules[i].type, NCOND_NONE));
                        break;
                    default:
                        g_error ("Unknown rule %i", rules[i].rule);
                }
                break;
            }
        }
    }

    return nodes;
}
