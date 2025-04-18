# Lab 5: Context Free Grammars and Tokenizers for Boolean Expressions

Lab 5 of 50.051 Programming Language Concepts

## Task 1: Introduction to Context-Free Grammars

As we have seen in class, a Context-Free Grammar (CFG) is a set of recursive rewriting rules (or productions) used to generate patterns of strings. A CFG consists of a set of **terminals** (symbols that appear in the strings), a set of **non-terminals** (symbols that help define the structure but do not appear in the strings), a set of **production rules** connecting symbols to other (combinations of) symbols, and a **start symbol** for the CFG.

In this Lab 5, we will first consider the following CFG for **Boolean expressions**:

```
(1): S → B
(2): B → B OR T
(3): B → T
(4): T → T AND F
(5): T → F
(6): F → ( B )
(7): F → true | false
```

In the CFG above, we can identify the following components:

- **Terminals**: The basic symbols from which strings are formed. In the example grammar explored in this Lab, the terminal symbols are **true**, **false**, the logical operators **AND** and **OR**, and parentheses.
- **Non-terminals**: Symbols that can be replaced with sequences of terminals and non-terminals. In the example, **S**, **B**, **T**, and **F** are non-terminals.
- **Rules/Productions**: Rules that describe how to form strings from the language. Each rule consists of a non-terminal followed by an arrow (→) and a sequence of terminals and/or non-terminals. Our CFG consists of seven production rules, denoted (1–7) and shown above.
- **Start Symbol**: A special non-terminal symbol from which the production starts. In the example, **S** is the start symbol for our CFG.

### Question 1-A

What is the purpose of this CFG?

> This CFG defines the syntax of Boolean expressions.

### Question 1-B

What types of Boolean expressions does it allow?

> It allows for Boolean expressions with true or false separated by the operators AND and OR. These expressions can be surrounded by parentheses and can contain sub-expressions surrounded by parentheses.

### Question 1-C

How can this be used in a compiler for syntax validation?

> During parsing, if the expression cannot be derived with this CFG, we know that the syntax is invalid.

### Question 1-D

Identify the recursive production rules in this CFG. Are they left-recursive? Right-recursive? Both?

> Rules 2 and 4 are left-recursive.

### Question 1-E

What is the significance behind using such recursions? What would happen if recursion was removed from this CFG?

> If recursion was removed from this CFG, we would be unable to parse recursive or nested expressions. Having such recursions allows for the creation of expressions with unlimited complexity, by chaining or nesting expressions. The recursions also define the associativity rules of the operators.

### Question 1-F

What is the point of using additional intermediate symbols **B**, **T** and **F**?

> Having intermediate symbols allows the CFG to define the operator precedence and associativity rules. In this case, the AND operator takes precedence of the OR operator, and both operators are left-associative.

### Question 1-G

How would you modify the CFG in order to include the NOT keyword?

> I would add another rule F => NOT F. Resulting CFG:
>
> ```
> (1): S => B
> (2): B => B OR T
> (3): B => T
> (4): T => T AND F
> (5): T => F
> (6): F => ( B )
> (7): F => true | false
> (8): F => NOT F
> ```

**This concludes Task 1.**

---

## Task 2: Coding a Simple CFG

### Description

In this section, we will discuss the implementation of a simple CFG framework, that we could use for the CFG introduced in Section 1, before the `NOT` keyword was added in Q1-G.

You may open the code in the `CFG_basics.c` file. As you will see, it starts with `#include` statements and `#define` statements, producing the following identifiers:

- `MAX_RHS`: The maximal number of symbols on the RHS of a CFG production rule (arbitrarily set to 10).
- `MAX_SYMBOLS`: The maximal number of symbols in a CFG (arbitrarily set to 10).
- `MAX_RULES`: The maximal number of CFG production rules (arbitrarily set to 10).

You are required to implement the components of a CFG as described below. Only the function prototypes are provided in the code file `CFG_basics.c`. You must complete the definitions. The `main()` function is already provided and contains test cases for your functions. **Do not modify it.**

### Coding a CFG Symbol Object and Its Functions

Our first objective is to define a `struct` for a **CFG symbol**.

We would like the `CFGSymbol` struct to have the following attributes:

- `symbol`: A character string representing the CFG symbol (`"S"`, `"B"`, `"T"`, `"F"`, `"OR"`, `"AND"`, `"("`, `")"`, `"true"`, `"false"`).
- `is_terminal`: An `int` (1 if terminal, 0 if non-terminal).
- `is_start`: An `int` (1 if the start symbol, 0 otherwise).

### Question 2-A

Can you implement the missing code in the `struct CFGSymbol` at the beginning of the code? Show your code.

### Question 2-B

For each possible CFG symbol in our Boolean CFG, describe the values of its attributes.

### Question 2-C

Implement the function `init_CFGSymbol()`, which initializes a CFGSymbol based on input parameters. Show your code.

### Question 2-D

Implement `init_Terminal()`, `init_NonTerminal()`, and `init_StartSymbol()` functions, reusing your function from Question 2-C. Show your code.

### Coding a CFG Production Rule Object and Its Functions

Our next step is to define a `struct` for a **CFG production rule**.
The `CFGProductionRule struct` should contain:

- `lhs`: The left-hand side symbol (a non-terminal).
- `rhs`: The right-hand side symbols (defined as an array of `CFGSymbol`).
- `rhs_length`: Number of symbols in the `rhs` array.

### Question 2-E

Implement the missing components for the `CFGProductionRule`. Show your code.

### Question 2-F

Why must `lhs` always be a **non-terminal**? Explain what would happen if it was a terminal symbol.

### Question 2-G

Implement `createProductionRule()`, ensuring `lhs` is **not a terminal**. Show your code.

### Question 2-H

Implement `printProductionRule()` to display production rules correctly. Show your code.

### Coding a CFG Object and Its Functions

Finally, we will define a CFG struct containing:

- `symbols`: Array of `CFGSymbol` elements.
- `startSymbol`: The start symbol.
- `rules`: Array of `CFGProductionRule` elements.
- `symbol_count`: Number of symbols.
- `rule_count`: Number of rules.

### Question 2-I

Implement the `CFG` struct. Show your code.

### Question 2-J

Implement `init_CFG()`, ensuring the start symbol is assigned correctly. Show your code.

### Question 2-K

Implement `printCFG()`, displaying rules in the format `(k) lhs --> rhs`. Show your code.

**Note:** If your codes are correctly implemented, the test cases in the main function should display something similar to what is shown below.

```
## INPUT: Suppose we have the following CFG rules stored in the CFG object:
1.  S → B
2.  B → B OR T
3.  B → T
4.  T → T AND F
5.  T → F
6.  F → ( B )
7.  F → true
8.  F → false

## When calling printCFG(&cfg);, the output will be:
(1) S --> B
(2) B --> B OR T
(3) B --> T
(4) T --> T AND F
(5) T --> F
(6) F --> ( B )
(7) F --> true
(8) F --> false
```

**This concludes Task 2.**

---

## Task 3: Implementing a Simple Tokenizer

### Description

In this section, we will discuss the implementation of a simple tokenizer that we could use for the Boolean expression CFG framework we built in Section 2.

You may open the code in the `tokenizer.c` file. As you will see, it starts with `#include` statements and `#define` statements, producing the following identifiers:

- `MAX_TOKENS`: The maximum number of tokens a Boolean expression can contain.
- `MAX_LENGTH`: The maximum number of characters for a Boolean value (`true` or `false`).

Start by copy-pasting the code you have produced in the previous task for the `CFGSymbol` struct, `init_CFGSymbol()` function, and `init_Terminal()`.

Our objective in this task is to write a tokenizer that will read a sequence of Boolean values, logical operators, and parentheses, such as:

`"true AND (false OR true)"`

It will produce an array of `CFGSymbols`, whose symbols will later be printed on screen as:

`Token(true) Token(AND) Token(() Token(false) Token(OR) Token(true) Token())`

Later on, we could use this array of `CFGSymbols` with our CFG to verify if a Boolean expression is syntactically valid.

### Writing a Simplified Maximal Munch Algorithm for Our Tokenizer

You may assume that the input strings only consist of Boolean values (`true`, `false`), logical operators (`AND`, `OR`), and parentheses (`(`, `)`). The tokenizer should:

- Ignore spaces.
- Detect errors (e.g., unexpected characters like `"!true"`).
- Tokenize multi-character symbols (`true`, `false`, `AND`, `OR`) correctly.

### Question 3-A

Implement the struct for `CFG symbols`. Show your code.

### Question 3-B

Implement the function `init_CFGSymbol()`. Show your code.

### Question 3-C

Implement the function `init_Terminal()`. Show your code.

### Question 3-D

Why are we reusing the `init_Terminal()` function, but not the `init_NonTerminal()` function here?

### Question 3-E

What would be the regular expression (RegEx) to check whether a string `"s"` is a valid Boolean keyword (`true` or `false`)? Is RegEx even needed for this task?

### Question 3-F

What would be the **pseudo-code** for our maximal munch algorithm? Keep it as simple as possible. Show your pseudo-code.

### Implementing a tokenizing function

In the `tokenizer.c` file, there is a function `tokenizeBooleanExpression()`. This function receives:

- `str`: The input Boolean expression, e.g., `"true AND (false OR true)"`.
- `symbols`: The array that will contain up to `MAX_TOKENS` `CFGSymbols` after tokenization.
- `symbol_count`: An integer denoting the number of `CFGSymbols` in the symbols array.
- `and_sym`: The `CFGSymbol` for the terminal symbol `"AND"`.
- `or_sym`: The `CFGSymbol` for the terminal symbol `"OR"`.
- `true_sym`: The `CFGSymbol` for `"true"`.
- `false_sym`: The `CFGSymbol` for `"false"`.
- `lparen`: The `CFGSymbol` for `"("`.
- `rparen`: The `CFGSymbol` for `")"`.

### Question 3-G

Implement the function `tokenizeBooleanExpression()`. Your function should read the input string character by character, identify valid tokens, ignore spaces (do not tokenize them!) and store them in the array `symbols`. It should also update `symbol_count` accordingly and detect errors if any. Reuse the function prototype and show your code.

**Note:** To help you, we have assembled test cases in the `main()` function. If your function is correct, it should produce the following output, below.

```
[Test Case 1] Terminal Initialization
Expected: AND OR true false ( )
Actual : AND OR true false ( )

[Test Case 2] init_CFGSymbol() for Non-Terminal
Expected: B terminal=0 start=1
Actual : B terminal=0 start=1

[Test Case 3] Tokenizing Expression: true AND false
Expected Tokens: true AND false
Actual Tokens : true AND false

[Test Case 4] Tokenizing Expression: (true OR false)
Expected Tokens: ( true OR false )
Actual Tokens : ( true OR false )

[Test Case 5] Tokenizing Invalid Expression: true && false
[ERROR] Unexpected character: &
Expected: Error on unexpected character '&'
```

**This concludes Task 3.**

---

## Task 4: Implementing a Manual Derivation for Our CFG

### Description

In this section, we will discuss the implementation of a manual derivation engine for Boolean expressions.

Our objective is to define several functions:

1. `startDerivation()`: Initializes the derivation process with the start symbol (`S`).
2. `applyProductionRule()`: Applies a production rule from the CFG.
3. `checkDerivation()`: Checks if the derived sequence matches the tokenized input.

### Question 4-A

Consider the Boolean expression `true AND (false OR true)`. What is a valid derivation for this expression? List the production rules used and which symbol was modified. Indicate the position index of each replacement.

### Initializing the Array of CFGSymbols

The function `startDerivation()` receives:

- `derivation`: An array of `CFGSymbols`, initially empty.
- `derivation_length`: Integer, initially `0`.
- `cfg`: CFG object, which will be used for derivation.

We want the following function behavior:

- It retrieves the start symbol (`S`).
- It then assigns it as the first element in the `derivation` array.
- It updates `derivation_length` accordingly.

### Question 4-B

Implement `CFGSymbol` Struct. Show your code.

### Question 4-C

Implement `CFGProductionRule` Struct. Show your code.

### Question 4-D

Implement `CFG` Struct. Show your code.

### Question 4-E

Implement `startDerivation()`. Show your code.

### Applying a Production Rule on a Given Symbol

The function `applyProductionRule()` receives:

- `derivation`: Array of `CFGSymbols`.
- `derivation_length`: Integer count.
- `cfg`: CFG object.
- `ruleIndex`: Index of the production rule.
- `position`: Position of symbol to replace.

We want the following function behavior:

- It checks if LHS of rule matches the symbol at `position`.
- It then replaces symbol at `position` with RHS of the rule.
- It updates `derivation_length` accordingly.
- It handles shifting of elements if RHS is longer than LHS.

### Question 4-F

Implement `applyProductionRule()`. Show your code.

### Checking for a Valid Derivation

The function `checkDerivation()` receives:

- `derivation`: Derived sequence of symbols.
- `derivation_length`: Integer count.
- `tokens`: Array of `CFGSymbols` from tokenizer.
- `token_count`: Integer count.

We want the following function behavior:

- It compares derived sequence with tokenized input.
- If all elements match, it prints "`Derivation successful!`".
- If a mismatch is found, it prints "`Mismatch at position X`".

### Question 4-G

Implement `checkDerivation()`. Show your code.

**Note:** To help you, we have assembled test cases in the `main()` function. If your function is correct, it should produce the following output below.

```
=== Test Manual Derivation Engine ===

[Test] startDerivation:
S

[Test] applyProductionRule: Rule 1 (S → B)
B

[Test] applyProductionRule: Rule 2 (B → T)
T

[Test] applyProductionRule: Rule 3 (T → F)
F

[Test] checkDerivation
[Test] Length mismatch (1 token vs 2 tokens)
Derivation unsuccessful: Length mismatch.
[Test] Symbol mismatch at position 0
Derivation unsuccessful: Mismatch at position 0: expected F, got T
[Test] Exact match with tokens
Derivation successful!
```

**This concludes Task 4.**
