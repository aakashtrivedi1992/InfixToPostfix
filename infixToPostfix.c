#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct stack *stackPointer;

typedef struct stack
{
   int element;
   stackPointer nextItem;
} stack;

typedef stackPointer STACK;


//This method checks to see if the stack is empty.
int isEmpty(STACK S)
{
   return (S->nextItem == NULL);
}

//This method creates a stack of char elements.
STACK createStack(void)
{
   STACK S = (STACK) malloc(sizeof(stack));

   if (S == NULL)
   {
      printf("Out of space!!!");
   }

   S->nextItem == NULL;

   return S;
}

//This method makes the stack null.
void makeNull(STACK S)
{
   if (S != NULL)
   {
      S->nextItem = NULL;
   }
   
   else
   {
      printf("Must use createStack first");
   }
}

//This function pushes or adds an element to the stack.
void push(int x, STACK S)
{
   stackPointer tmpCell = (stackPointer) malloc(sizeof (stack));

   if (tmpCell == NULL)
   {
      printf("Out of space!!!");
   }
   
   else
   {
      tmpCell->element = x;
      tmpCell->nextItem = S->nextItem;
      S->nextItem = tmpCell;
   }
}

//This function returns the top element of the stack.
int top(STACK S)
{
   if(isEmpty(S))
   {
   }
   
   else
   {
      return S->nextItem->element;
   }

   return 0;
}

//This function pops the top element off of the stack and returns it.
int pop(STACK S)
{
   stackPointer firstCell = (stackPointer) malloc(sizeof (stack));

   if(isEmpty(S))
   {
      printf("Empty stack");
      return 0;
   }
   
   else
   {
      firstCell = S->nextItem;
      S->element = firstCell->element;
      S->nextItem = S->nextItem->nextItem;
      free(firstCell);
   
      return S->element;
   }
}

//This function checks the priority of the operators used.
int checkPriority(char op)
{
   int priority = 0;

   if (op == '*' || op == '/' || op == '&')
   {
      priority = 2;
   }
   
   else if (op == '+' || op == '-')
   {
      priority = 1;
   }

   return priority;
}

//This function checks whether the character in the expression is an operator or not.
int isOperator(char item)
{
   if (item == '+' || item == '-' || item == '*' || item == '/' || item == '(' || item == ')')
   {
      return 1;
   }

   return 0;
}

//This function converts the infix expression to postfix.
void infixToPostfix(char* inf, char* postf, STACK S) //STACK is now ints
{
   int i = 0;
   int p = 0;
   char tmpChar;

   while (inf[i])
   {
      if (inf[i] == ' ' || inf[i] == '\t')
      {
         i++;
      }
      
      else if (isOperator(inf[i]) == 0)
      {
         postf[p] = inf[i];
         i++;
         p++;
      }
      
      else if (inf[i] == '(')
      {
         push(inf[i], S);
         i++;
      }
      
      else if (inf[i] == ')')
      {
         tmpChar = pop(S);
      
         while (tmpChar != '(')
         {
            postf[p] = tmpChar;
            p++;
            tmpChar = pop(S);
         }
      
         i++;
      }
      
      else if (isOperator(inf[i]) == 0)
      {
         STACK smallS = createStack();
         int temp = 0, power=0, total=0;
         while (!isOperator(inf[i]) && (inf[i] != '\0') && (inf[i] !=' ') && (inf[i] != '\t'))
         {
            push(inf[i] -
               '0', smallS);
            printf(
               "Added number %d to stack.\n", inf[i] - '0');
            i++;
         }
         while (!isEmpty(smallS))
         {
            temp = pop(smallS);
            total = total + temp * (10 ^ power);
            power++;
         };
      //postf[p] = inf[i];
         postf[p] = total;
         i++;
         p++;
      }
      else //now we know its an operator + - * /
      {
         if (isEmpty(S) == 1)
         {
            push(inf[i], S);
         }
         
         else
         {
            while (checkPriority(top(S)) >= checkPriority(inf[i]))
            {
               postf[p] = pop(S);
               p++;
            }
         
            push(inf[i], S);
         }
      
         i++;
      }
   }

   while (isEmpty(S) == 0)
   {
      postf[p] = pop(S);
      p++;
   }

   p = '\0';
}

//This function prints out the contents of the postfix expression.
void printResult(char* postfixArray)
{
   printf("\nPostfix Expression: ");

   while ((postfixArray != NULL) && (*postfixArray != '\0'))
   {
      printf("%c", *postfixArray);
      postfixArray++;
   }

   printf("\n\n");
}

//This function evaluates the postfix expression.
int evaluateExpression(char* postfixArray, STACK S)
{
   int operand1 = 0;
   int operand2 = 0;
   int result = 0;

   while((postfixArray != NULL) && (*postfixArray != '\0'))
   {
      if (isOperator(*postfixArray) == 0)
      {
         push(*postfixArray - '0', S);
      	//printf("just pushed %d\n", *postfixArray - '0');
      }
      
      else //it is an operator
      {
         operand2 = pop(S);
         operand1 = pop(S);
      
         switch (*postfixArray)
         {
            case '+':
               result = operand1 + operand2;
               break;
         
            case '-':
               result = operand1 - operand2;
               break;
         
            case '*':
               result = operand1 * operand2;
               break;
         
            case '/':
               result = operand1 / operand2;
               break;
         }
      
         push(result, S);
      }
   
      postfixArray++;
   }

   return result;
}

//This is the main function which asks the user to enter an infix expression and calls the other functions of this program to change it to postfix and evaluate the postfix expression.
int main(int argc, char* *argv)
{
   char infixExpression[50] = { 0 };
   char postfixExpression[50] = { 0 };

   int result = 0;

   STACK theStack = createStack();

   printf("Enter an expression in infix form with each character followed by a space.\n(SINGLE DIGIT NUMBERS ONLY)\n\n");
   printf("Infix Expression: ");

   fgets(infixExpression, sizeof(infixExpression), stdin);

   infixExpression[strlen(infixExpression) - 1] = '\0';

   infixToPostfix(infixExpression, postfixExpression, theStack);

   printResult(postfixExpression);

   result = evaluateExpression(postfixExpression, theStack);

   printf("Result: %i\n\n\n", result);

   return 0;
}
