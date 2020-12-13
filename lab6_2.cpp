// ---------------------------------------------------------------------------------------
// AUTHOR:			Aleksei Sorokin
// FILENAME:		lab6_2.cpp
// SPECIFICATION:	An expression binary tree (creating, printing and evaluation)
// FOR:				CS 2413 Data Structure Section 504
// ---------------------------------------------------------------------------------------

#include"iostream"
#include"cstdlib"
#include<malloc.h>
#include<iomanip>

#define MAX_SIZE_INPUT_STRING 50

using namespace std;

union information
{
	int number; // if node contains integer
	char oper; // if node contains operator
};

struct st
{
	int 		isoper; // operator (or bracket) or not 
	information type;
};


 struct node{
	st					data; 
	struct node 		*left;
	struct node 		*right;
	};

// --------------------------------------------------------------------------------
// NAME: new_node
// INPUT Param.: data - a structure st variable that cotaints data  
// OUTPUT Param.: new_node - *node
// PURPOSE: create a new node// ---------------------------------------------------------------------------------
	
node *new_node(st data)
{
	node *new_node;
	new_node = (node*)malloc(sizeof(node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return(new_node);
};

// --------------------------------------------------------------------------------
// NAME: push
// INPUT Param.: stack - st stack, top - integer that points to the top element of stack, c - st variable that will be pushed.  
// OUTPUT Param.: None
// PURPOSE: push a variable into stack// ---------------------------------------------------------------------------------
	
void push (st stack[], int *top, st c) 
{
	if (*top == MAX_SIZE_INPUT_STRING - 1)
		cout << "\nOverflow";
	else 
	{	(*top)++;
		if (c.isoper == 1)
		{
			(stack[*top]).isoper = 1;
			(stack[*top]).type.oper = c.type.oper;
		}
		else
		{
		(stack[*top]).isoper = 0;
		(stack[*top]).type.number = c.type.number;
		}
	}
}	

// --------------------------------------------------------------------------------
// NAME: peek
// INPUT Param.: stack - a st stack, top - position of the top element.
// OUTPUT Param.: a st variable - top element of the stack.
// PURPOSE: To get a top element from the the stack(without removing)// ---------------------------------------------------------------------------------

st peek (st stack[], int top)
{
	st ret; // return 
	if (top == -1)
	{
		cout << "\nUnderflow";
		ret.isoper = 1;
		ret.type.oper = '\0';
		return(ret);
	}
	else 
	{
		if (stack[top].isoper == 1)
		{
			ret.isoper = 1;
			ret.type.oper = stack[top].type.oper;
		}
		else
		{
			ret.isoper = 0;
			ret.type.number = stack[top].type.number;
		}
		return(ret);
	}
}

// --------------------------------------------------------------------------------
// NAME: pop
// INPUT Param.: stack - a st stack, top - position of the top element.
// OUTPUT Param.: a st variable.
// PURPOSE: To remove a top element from the the stack// ---------------------------------------------------------------------------------

st pop (st stack[], int *top)
{
	st ret; // return
	if (*top == -1)
	{
		ret.isoper = 1;
		ret.type.oper = '\0';
		return(ret);
	}
	else 
	{
		if (stack[*top].isoper == 1)
		{
			ret.isoper = 1;
			ret.type.oper = stack[*top].type.oper;
		}
		else
		{
			ret.isoper = 0;
			ret.type.number = stack[*top].type.number;
		}
		(*top)--;
		return(ret);
	}
}

// --------------------------------------------------------------------------------
// NAME: isbalance
// INPUT Param.: string - a char string
// OUTPUT Param.: integer: 1 - balanced, 0 - unbalanced .
// PURPOSE: to check that a given an arithmetic expression, that uses braces “{“ & ”}” 
//			or parenthesis ”(“ &, ”)” or brackets ”[“ & ”]” as grouping symbols, is
//			using them in a matching and balanced way. // ---------------------------------------------------------------------------------

int isbalance(char string[])
{
	st stack[MAX_SIZE_INPUT_STRING], elem;
	int len = strlen(string);
	int top = -1;
	for (int i = 0; i < len; i++)
		if (string[i] == '(' || string[i] == '[' || string[i] == '{')
		{
			elem.isoper = 1;
			elem.type.oper = string[i];
			push (stack, &top, elem);
		}
		else if (string[i] == ')' || string[i] == ']' || string[i] == '}')
			{
				elem = pop (stack, &top);
				if (elem.type.oper == '\0' || elem.type.oper == '(' && string [i] != ')' 
					|| elem.type.oper == '[' && string [i] != ']' || elem.type.oper == '{' && string [i] != '}')
					return(0);
			}
	if (top != -1)
		return(0);
	else return(1);
}	

// --------------------------------------------------------------------------------
// NAME: convert_into_postfix
// INPUT Param.: string - an initial char string, postfix - a st array in postfix,
//				 postfix_len - the length of the array in postfix notation. 
// OUTPUT Param.: NONE
// PURPOSE: To convert arithmetic expressions in infix notation
//					into their equivalent expressions in postfix notation// ---------------------------------------------------------------------------------

void convert_to_postfix (char string[], st postfix[], int *postfix_len)
{
	st stack[MAX_SIZE_INPUT_STRING], elem;
	int top = -1, balanced, string_len = strlen(string), number = 0;
	balanced = isbalance(string);
	if (balanced)
	{
		string[string_len] = ')';
		elem.isoper = 1;
		elem.type.oper = '(';
		push(stack, &top, elem);
		for (int i = 0; i <= string_len; i++)
		if (string[i] == '(' || string[i] == '{' || string[i] == '[')
		{
			elem.isoper = 1;
			elem.type.oper = string[i];
			push(stack, &top, elem);
		}
		else if (string[i] == ')' || string[i] == '}' || string[i] == ']')
			{
				elem = pop(stack, &top);
				while (elem.type.oper != '(' && elem.type.oper != '{' && elem.type.oper != '[')
				{
					if (elem.isoper == 1)
					{
					postfix[*postfix_len] = elem;
					(*postfix_len)++;
					}
					else
					{
						
					}
					elem = pop(stack, &top);
				}
			}
		else if (string[i] == '*' || string[i] == '/')
			{
				while ((peek(stack, top)).type.oper == '*' || (peek(stack, top)).type.oper == '/')
				{
					elem = pop(stack, &top);
					postfix[*postfix_len] = elem;
					(*postfix_len)++;
				}
				elem.isoper = 1;
				elem.type.oper = string[i];
				push(stack, &top, elem);
			}
		else if (string[i] == '-' || string[i] == '+' || string[i] == '%')
			{
				while ((peek(stack, top)).type.oper == '*' || (peek(stack, top)).type.oper == '/' ||
					(peek(stack, top)).type.oper == '+' || (peek(stack, top)).type.oper == '-' || 
					(peek(stack, top)).type.oper == '%')
				{
					elem = pop(stack, &top);
					postfix[*postfix_len] = elem;
					(*postfix_len)++;
				}
				elem.isoper = 1;
				elem.type.oper = string[i];
				push(stack, &top, elem);
			}
		else if (string[i] >= '0' && string[i] <= '9')
		{
			number*=10;
			number += (int)string[i] - 48;
			if (!(string[i+1] <= '9' && string[i+1] >= '0')) 
			{
				elem.isoper = 0;
				elem.type.number = number;
				postfix[*postfix_len] = elem;
				(*postfix_len)++;
				number = 0;
			}
		}
		// if string[i] is a space or other character but operators, I just ignore it
			
		
		
	}
	else cout << "\nThe expression is not balanced";
}

// --------------------------------------------------------------------------------
// NAME: create
// INPUT Param.: 
// OUTPUT Param.: a pointer to the root of an expression binary tree.
// PURPOSE: To create an expression tree.// ---------------------------------------------------------------------------------


node *create ()
{
	node *root, *stack[MAX_SIZE_INPUT_STRING];
	char str[MAX_SIZE_INPUT_STRING];
	st postfix[MAX_SIZE_INPUT_STRING];
	int postfix_len = 0, top = -1;
	cout << "\nPlease, enter The input expression in infix notation\n";
	cin.clear();
	fflush(stdin);
	scanf ("%[^\n]%*c", str);
	convert_to_postfix(str, postfix, &postfix_len); // convert to postfix notation
	for(int i = 0; i < postfix_len; i++) // read elements from postfix notation
		if(postfix[i].isoper == 0) // if an element is a number
		{
			root = new_node(postfix[i]); // create a new_node (contains number)
			top++;
			stack[top] = root; // push it into the stack
		}
		else // if an element is a operator
		{
			root = new_node(postfix[i]); // create a new_node (contains operator)
			node *n1, *n2; // pop two top nodes from the stack
			n1 = stack[top];
			top--;
			n2 = stack[top];
			top--;
			root->right = n1; // make them children of the new_node 
			root->left = n2;
			top++;
			stack[top] = root; // push it into the stack
		}
	root = stack[top]; // last element of the stack will be the root of an expression binary tree
	top--;
	return(root);
}

// --------------------------------------------------------------------------------
// NAME: precedence
// INPUT Param.: first - node, second - node, left_or_right - integer
// first is always an operator, second can be a number // left = 0, right = 1
// OUTPUT Param.: integer: 1 - higher precedence, 0 - not
// PURPOSE: To check the order of operations// ---------------------------------------------------------------------------------

int precedence (node *first, node *second, int left_or_right)
{
	int answer;
	if (second->data.isoper == 0)
		answer = 0;
	else if (left_or_right == 1)
	{
		if (first->data.type.oper == '/' || first->data.type.oper == '*')
		answer = 1;
		else if (second->data.type.oper == '+' || second->data.type.oper == '-' || second->data.type.oper == '%')
			answer = 1;
			else answer = 0;
	}
	else if ((first->data.type.oper == '/' || first->data.type.oper == '*') && 
		(second->data.type.oper == '+' || second->data.type.oper == '-' || second->data.type.oper == '%'))
		answer = 1;
		else answer = 0;
	return(answer);
}

// --------------------------------------------------------------------------------
// NAME: infix
// INPUT Param.: root - a pointer to the root of an expression binary tree.
// OUTPUT Param.: NONE
// PURPOSE: to print expression from a given tree, in infix notation
//			Inorder traversal// ---------------------------------------------------------------------------------

void infix (node *root)
{
	if (root != NULL)
	{
		if(root->data.isoper == 1) 
		{
			if (precedence(root, root->left, 0)) // checking for brackets;
			{
				cout << "(";
				infix(root->left);
				cout << ")";
			}
			else infix(root->left);
			cout <<  root->data.type.oper;
			if (precedence(root, root->right, 1)) // checking for brackets;
			{
				cout << "(";
				infix(root->right);
				cout << ")";
			}
			else infix(root->right);
		}
		else cout << root->data.type.number;
	}		
}

// --------------------------------------------------------------------------------
// NAME: prefix
// INPUT Param.: root - a pointer to the root of an expression binary tree.
// OUTPUT Param.: NONE
// PURPOSE: to print expression from a given tree, in prefix notation
//			Preorder traversal// ---------------------------------------------------------------------------------

void prefix(node *root)
{
	if (root != NULL)
	{
		if(root->data.isoper == 1)
			cout << " " << root->data.type.oper;
		else cout << " " << root->data.type.number;
		prefix(root->left);
		prefix(root->right);
	}		
}

// --------------------------------------------------------------------------------
// NAME: operation
// INPUT Param.: left - integer, right - integer, op(operator) - char.
// OUTPUT Param.: ans(answer) -i nteger
// PURPOSE: to get the result of given operation between two integers// ---------------------------------------------------------------------------------

int operation (int left, int right, char op)
{
	int ans;
	if (op == '-')
		ans = left - right;
	if (op == '+')
		ans = left + right;
	if (op == '*')
		ans = left * right;
	if (op == '/')
		ans = left / right;
	if (op == '%')
		ans = left % right;
	return(ans);
}

// --------------------------------------------------------------------------------
// NAME: calculate
// INPUT Param.: root - a pointer to the root of an expression binary tree.
// OUTPUT Param.: integer - answer
// PURPOSE: to calculate and print the result of the created Expression Tree
//			recursive function, calculates left and right subtrees first.// ---------------------------------------------------------------------------------

int calculate(node *root)
{
	int l, r; // left, right
	if (root->data.isoper == 1)
	{
		l = calculate(root->left);
		r = calculate(root->right);
		return(operation (l, r, root->data.type.oper));
	}
	else return(root->data.type.number);
}




	
int main()
{
	node *root = NULL;
	int answer;
	char key = ' ';
	cout << "Enter '1' to create an expression tree";
	cout << "\nEnter '2' to print expression from a given tree, in prefix notation";
	cout << "\nEnter '3' to print expression from a given tree, in infix notation";
	cout << "\nEnter '4' to calculate and print the result of the created Expression Tree";
	cout << "\nEnter '0' to exit";
	while(key != '0')
	{
		cin.clear();
		fflush(stdin);
		cout << "\nEnter a number: ";
		cin >> key;
		switch (key)
		{
		case '1': root = create();
			break;
		case '2': prefix(root);
			break;
		case '3': infix(root);
			break;
		case '4': {
			answer = calculate(root);
			cout << "\nThe answer is " << answer;
			break;
			}
		case '0': cout << "End of the program";
			break;
		default:  cout << "Wrong input, try again\n";
		}
	}
	return(0);
}
