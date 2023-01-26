#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN,
    LPAREN, RPAREN,
    INCDEC,
    AND, OR, XOR
} TokenSet;

// Test if a token matches the current token 
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);

#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left; 
    struct _Node *right;
} BTNode;

// The symbol table
extern Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode* assign_expr(void);
extern BTNode* or_expr(void);
extern BTNode* or_expr_tail(BTNode* left);
extern BTNode* xor_expr(void);
extern BTNode* xor_expr_tail(BTNode* left);
extern BTNode* and_expr(void);
extern BTNode* and_expr_tail(BTNode* left);
extern BTNode* addsub_expr(void);
extern BTNode* addsub_expr_tail(BTNode* left);
extern BTNode* muldiv_expr(void);
extern BTNode* muldiv_expr_tail(BTNode* left);
extern BTNode* unary_expr(void);
extern void statement(void);

// Print error message and exit the program
extern void err(ErrorType errorNum);
// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

extern void printAssembly(BTNode* root);
int cur;

static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

//done
TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' ) {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '+') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else {
            lexeme[1] = '\0';
            ungetc(c, stdin);
            return ADDSUB;
        }
        return ADDSUB;
    } else if (c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '-') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else {
            lexeme[1] = '\0';
            ungetc(c, stdin);
            return ADDSUB;
        }
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        int i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN) {
            lexeme[i] = c;
            i++;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } 
    else if (c == '&') {
        //printf("a\n");
        strcpy(lexeme, "&");
        return AND;
    }
    else if (c == '|') {
        strcpy(lexeme, "|");
        return OR;
    }
    else if (c == '^') {
        strcpy(lexeme, "^");
        return XOR;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}

int sbcount = 0;
Symbol table[TBLSIZE];

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// statement := ENDFILE | END | expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        printf("MOV r0 [0]\n");
        printf("MOV r1 [4]\n");
        printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            //printf("%d\n", evaluateTree(retp));
            //printf("Prefix traversal: ");
            //printPrefix(retp);
            //printf("\n");
            cur = -1;
            evaluateTree(retp);
            printAssembly(retp);
            freeTree(retp);
            //printf(">> ");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

//assign_expr: = ID ASSIGN assign_expr | or_expr
BTNode* assign_expr() {
    BTNode* left = or_expr(), * node = NULL;
    if (left->data == ID && match(ASSIGN)) {
        node = makeNode(ASSIGN, getLexeme());
        advance();
        node->left = left;
        node->right = assign_expr();
        return node;
    }
    else {
        return left;
    }
}

//or_expr: = xor_expr or_expr_tail
BTNode* or_expr() {
    BTNode* left = xor_expr();
    return or_expr_tail(left);
}

//or_expr_tail: = OR xor_expr or_expr_tail | NiL
BTNode* or_expr_tail(BTNode* left) {
    BTNode* node = NULL;
    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    }
    else {
        return left;
    }
}

//xor_expr: = and_expr xor_expr_tail
BTNode* xor_expr() {
    BTNode* left = and_expr();
    return xor_expr_tail(left);
}

//xor_expr_tail: = XOR and_expr xor_expr_tail | NiL
BTNode* xor_expr_tail(BTNode* left) {
    BTNode* node = NULL;
    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    }
    else {
        return left;
    }
}

//and_expr: = addsub_expr and_expr_tail
BTNode* and_expr() {
    BTNode* left = addsub_expr();
    return and_expr_tail(left);
}

//and_expr_tail: = AND addsub_expr and_expr_tail | NiL
BTNode* and_expr_tail(BTNode* left) {
    BTNode* node = NULL;
    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    }
    else {
        return left;
    }
}

//addsub_expr      := muldiv_expr addsub_expr_tail 
BTNode* addsub_expr() {
    BTNode* left = muldiv_expr();
    return addsub_expr_tail(left);
}

//addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode* addsub_expr_tail(BTNode* left) {
    BTNode* node = NULL;
    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    }
    else {
        return left;
    }
}
//muldiv_expr: = unary_expr muldiv_expr_tail
BTNode* muldiv_expr() {
    BTNode* left = unary_expr();
    return muldiv_expr_tail(left);
}

//muldiv_expr_tail: = MULDIV unary_expr muldiv_expr_tail | NiL
BTNode* muldiv_expr_tail(BTNode *left) {
    BTNode* node = NULL;
    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    }
    else {
        return left;
    }
}

//unary_expr: = ADDSUB unary_expr | factor
BTNode* unary_expr() {
    BTNode* retp = NULL;
    if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = makeNode(INT, "0");
        retp->right = unary_expr();
    }
    else retp = factor();
    return retp;
}

//factor           := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode* factor(void) {
    BTNode* retp = NULL, * left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    }
    else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    }
    else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        retp->right = makeNode(INT, "1");
        if (match(ID)) {
            retp->left = makeNode(ID, getLexeme());
            advance();
        }
        else {
            error(NOTNUMID);
        }
    }
    else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    }
    else {
        error(NOTNUMID);
    }
    return retp;
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}

int check_table(char* str) {
    for (int i = 0 ; i < TBLSIZE ; i++) {
        if (strcmp(str, table[i].name) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_var_zero(BTNode* root) {
    if (root != NULL) {
        int is = 0;
        if (root->data == ID) is = 1;
        if (root->left != NULL) is = is_var_zero(root->left);
        if (root->right != NULL) is |= is_var_zero(root->right);
        return is;
    }
}

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                if (check_table(root->lexeme)) {
                    retval = getval(root->lexeme);
                }
                else {  
                    error(NOTFOUND);
                }
                break;
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                break;
            case INCDEC:
                rv = evaluateTree(root->left);
                if (strcmp(root->lexeme, "++") == 0) {
                    retval = rv + 1;
                }
                else if (strcmp(root->lexeme, "--") == 0) {
                    retval = rv - 1;
                }
                break;
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0) {
                        if (is_var_zero(root->right)) {
                            retval = 0;
                        }
                        else {
                            error(DIVZERO);
                        }
                    }
                    else {
                        retval = lv / rv;
                    }
                }
                break;
            case AND:
            case OR:
            case XOR:
                if (strcmp(root->lexeme, "&") == 0) {
                    retval = lv & rv;
                }
                else if (strcmp(root->lexeme, "|") == 0) {
                    retval = lv | rv;
                }
                else if (strcmp(root->lexeme, "^") == 0) {
                    retval = lv ^ rv;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

int get_mp(char *str) {
    for (int i = 0; i < TBLSIZE; i++) {
        if (strcmp(str, table[i].name) == 0) {
            return i;
        }
    }
}

void printAssembly(BTNode* root) {
    //printf("in\n");
    //printf("MOV r0, [0]\n");
    //printf("MOV r1, [1]\n");
    //printf("MOV r2, [2]\n");
    if (root == NULL) return;
    switch (root->data) {
        case ID:
            cur += 1;
            printf("MOV r%d [%d]\n", cur, get_mp(root->lexeme) * 4);
            break;
        case INT:
            cur += 1;
            printf("MOV r%d %d\n", cur, atoi(root->lexeme));
            break;
        case ASSIGN:
            //printAssembly(root->left);
            printAssembly(root->right);
            printf("MOV [%d] r%d\n", get_mp(root->left->lexeme) * 4, cur);
            break;
        case INCDEC:
            if (strcmp(root->lexeme, "++") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("ADD r%d r%d\n", cur - 1, cur);
                cur -= 1;
                printf("MOV [%d] r%d\n", get_mp(root->left->lexeme) * 4, cur);
            }
            else if (strcmp(root->lexeme, "--") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("SUB r%d r%d\n", cur - 1, cur);
                cur -= 1;
                printf("MOV [%d] r%d\n", get_mp(root->left->lexeme) * 4, cur);
            }
            break;
        case ADDSUB:
        case MULDIV:
        case AND:
        case OR:
        case XOR:
            if (strcmp(root->lexeme, "+") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("ADD r%d r%d\n", cur - 1, cur);
                cur -= 1;
            }
            else if (strcmp(root->lexeme, "-") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("SUB r%d r%d\n", cur - 1, cur);
                cur -= 1;
            }
            else if (strcmp(root->lexeme, "*") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("MUL r%d r%d\n", cur - 1, cur);
                cur -= 1;
            }
            else if (strcmp(root->lexeme, "/") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("DIV r%d r%d\n", cur - 1, cur);
                cur -= 1;
            }
            else if (strcmp(root->lexeme, "&") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("AND r%d r%d\n", cur - 1, cur);
                cur -= 1;
            }
            else if (strcmp(root->lexeme, "|") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("OR r%d r%d\n", cur - 1, cur);
                cur -= 1;
            }
            else if (strcmp(root->lexeme, "^") == 0) {
                printAssembly(root->left);
                printAssembly(root->right);
                printf("XOR r%d r%d\n", cur - 1, cur);
                cur -= 1;
            }
            break;
        default:
            break;
    }
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
int main() {
    freopen("input.txt", "w", stdout);
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}