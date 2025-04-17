#include <ctype.h>
#include <stdio.h>
#include <string.h>
// Maximum number of tokens in a Boolean expression
#define MAX_TOKENS 20
// Maximum length for Boolean values ("true" and "false")
#define MAX_LENGTH 10

// Struct for CFG symbols
typedef struct {
  char *symbol;
  int is_terminal;
  int is_start;
} CFGSymbol;

// Generic function to initialize a CFGSymbol
void init_CFGSymbol(CFGSymbol *symbol, char *text, int is_terminal,
                    int is_start) {
  symbol->symbol = text;
  symbol->is_terminal = is_terminal;
  symbol->is_start = is_start;
}

// Specific initializer for terminal symbols
void init_Terminal(CFGSymbol *symbol, char *text) {
  init_CFGSymbol(symbol, text, 1, 0);
}

// Tokenizer function
// - str: The input Boolean expression, e.g., "true AND (false OR true)".
// - symbols: The array that will contain up to MAX_TOKENS CFGSymbols after
// tokenization.
// - symbol_count: An integer denoting the number of CFGSymbols in the symbols
// array.
// - and_sym: The CFGSymbol for the terminal symbol "AND".
// - or_sym: The CFGSymbol for the terminal symbol "OR".
// - true_sym: The CFGSymbol for "true".
// - false_sym: The CFGSymbol for "false".
// - lparen: The CFGSymbol for "(".
// - rparen: The CFGSymbol for ")"
void tokenizeBooleanExpression(char *str, CFGSymbol *symbols, int *symbol_count,
                               CFGSymbol *and_sym, CFGSymbol *or_sym,
                               CFGSymbol *true_sym, CFGSymbol *false_sym,
                               CFGSymbol *lparen, CFGSymbol *rparen) {
  *symbol_count = 0;       // Reset token count
  char buffer[MAX_LENGTH]; // Token buffer
  int i = 0;

  while (str[i] != '\0') {
    // Skip whitespace
    if (isspace(str[i])) {
      ++i;
      buffer[0] = '\0';
      continue;
    }

    CFGSymbol match;
    match.symbol = "";

    // Reset buffer
    buffer[0] = '\0';
    int j = 0;

    while (str[i + j] != '\0') {
      buffer[j] = str[i + j];
      buffer[j + 1] = '\0';
      int partial_match = 0;

      // Check through all possible tokens
      // strncmp tells me whether or not I have a partial match
      // I still need to check if I have a full match
      if (!strncmp(buffer, and_sym->symbol, j + 1)) {
        // Expected character found, check if full match has been found
        if (strlen(buffer) == strlen(and_sym->symbol)) {
          // Full match found, store match and stop looking for this token
          match = *and_sym;
        } else
          partial_match = 1;
      }
      if (!strncmp(buffer, or_sym->symbol, j + 1)) {
        // Expected character found, check if full match has been found
        if (strlen(buffer) == strlen(or_sym->symbol)) {
          // Full match found, store match and stop looking for this token
          match = *or_sym;
        } else
          partial_match = 1;
      }
      if (!strncmp(buffer, true_sym->symbol, j + 1)) {
        // Expected character found, check if full match has been found
        if (strlen(buffer) == strlen(true_sym->symbol)) {
          // Full match found, store match and stop looking for this token
          match = *true_sym;
        } else
          partial_match = 1;
      }
      if (!strncmp(buffer, false_sym->symbol, j + 1)) {
        // Expected character found, check if full match has been found
        if (strlen(buffer) == strlen(false_sym->symbol)) {
          // Full match found, store match and stop looking for this token
          match = *false_sym;
        } else
          partial_match = 1;
      }
      if (!strncmp(buffer, lparen->symbol, j + 1)) {
        // Expected character found, check if full match has been found
        if (strlen(buffer) == strlen(lparen->symbol)) {
          // Full match found, store match and stop looking for this token
          match = *lparen;
        } else
          partial_match = 1;
      }
      if (!strncmp(buffer, rparen->symbol, j + 1)) {
        // Expected character found, check if full match has been found
        if (strlen(buffer) == strlen(rparen->symbol)) {
          // Full match found, store match and stop looking for this token
          match = *rparen;
        } else
          partial_match = 1;
      }

      // Check if any partial matches. If none, either add the best
      // found match and continue tokenization or error
      if (!partial_match) {
        if (strcmp(match.symbol, "")) {
          // Existing match
          symbols[*symbol_count] = match;
          ++*symbol_count;
          i += strlen(match.symbol);
          break;
        } else {
          printf("[ERROR] Unexpected character: %c\n", str[i + j]);
          return;
        }
      }

      ++j;
    }
  }
}

// Main function for testing tokenizer functionality
int main() {
  // ==== Test Case 1: Terminal Initialization ====
  printf("\n[Test Case 1] Terminal Initialization\n");
  CFGSymbol and_sym, or_sym, true_sym, false_sym, lparen, rparen;

  init_Terminal(&and_sym, "AND");
  init_Terminal(&or_sym, "OR");
  init_Terminal(&true_sym, "true");
  init_Terminal(&false_sym, "false");
  init_Terminal(&lparen, "(");
  init_Terminal(&rparen, ")");

  printf("Expected: AND OR true false ( )\n");
  printf("Actual  : %s %s %s %s %s %s\n", and_sym.symbol, or_sym.symbol,
         true_sym.symbol, false_sym.symbol, lparen.symbol, rparen.symbol);

  // ==== Test Case 2: init_CFGSymbol directly ====
  printf("\n[Test Case 2] init_CFGSymbol() for Non-Terminal\n");
  CFGSymbol sym;
  init_CFGSymbol(&sym, "B", 0, 1);
  printf("Expected: B terminal=0 start=1\n");
  printf("Actual  : %s terminal=%d start=%d\n", sym.symbol, sym.is_terminal,
         sym.is_start);

  // ==== Test Case 3: Tokenize Simple Boolean Expression ====
  printf("\n[Test Case 3] Tokenizing Expression: true AND false\n");
  char expr1[] = "true AND false";
  CFGSymbol tokens1[MAX_TOKENS];
  int count1 = 0;

  tokenizeBooleanExpression(expr1, tokens1, &count1, &and_sym, &or_sym,
                            &true_sym, &false_sym, &lparen, &rparen);

  printf("Expected Tokens: true AND false\nActual Tokens  : ");
  for (int i = 0; i < count1; i++) {
    printf("%s ", tokens1[i].symbol);
  }
  printf("\n");

  // ==== Test Case 4: Tokenize with Parentheses and OR ====
  printf("\n[Test Case 4] Tokenizing Expression: (true OR false)\n");
  char expr2[] = "(true OR false)";
  CFGSymbol tokens2[MAX_TOKENS];
  int count2 = 0;

  tokenizeBooleanExpression(expr2, tokens2, &count2, &and_sym, &or_sym,
                            &true_sym, &false_sym, &lparen, &rparen);

  printf("Expected Tokens: ( true OR false )\nActual Tokens  : ");
  for (int i = 0; i < count2; i++) {
    printf("%s ", tokens2[i].symbol);
  }
  printf("\n");

  // ==== Test Case 5: Invalid input (should catch error) ====
  printf("\n[Test Case 5] Tokenizing Invalid Expression: true && false\n");
  char expr3[] = "true && false";
  CFGSymbol tokens3[MAX_TOKENS];
  int count3 = 0;

  tokenizeBooleanExpression(expr3, tokens3, &count3, &and_sym, &or_sym,
                            &true_sym, &false_sym, &lparen, &rparen);

  printf("Expected: Error on unexpected character '&'\n");

  return 0;
}
