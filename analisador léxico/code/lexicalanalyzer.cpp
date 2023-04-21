#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//token names
#define number   256;
#define id       257;
#define string   258;
#define operator 259;
#define	AND      260;
#define BREAK    261; 
#define DO       262;
#define ELSE     263;
#define ELSEIF   264;
#define END      265;
#define FALSE    266;
#define FOR      267;
#define FUNCTION 268;
#define IF       269;
#define IN       270;
#define LOCAL    271;
#define NIL      272;
#define NOT      273;
#define OR       274;
#define REPEAT   275;
#define RETURN   276;
#define THEN     277;
#define TRUE     278;
#define UNTIL    279;
#define WHILE    280;

//token attributes
#define SUM  300;
#define MIN  301;
#define MUL  302;
#define DIV  303;
#define POT  304;
#define OP   305;
#define CP   306;
#define OB   307;
#define CB   308;
#define OBK  309;
#define CBK  310;
#define SC   311;
#define COL  312;
#define COM  313;
#define IFEQ 314;
#define EQ   315;
#define NE   316;
#define LE   317;
#define LT   318;
#define GE   319;
#define GT   320;
#define DP   321;
#define SP   322;
#define NONE   0;

struct Token{
 int name;
 int attribute;
};

int state = 0;
int start = 0;
int counter = 0; //read symbol counter
char *code;

char *readFile(char *fileName)
{
  FILE *file = fopen(fileName, "r");
  char *code;
  int n = 0;
  int c;

  if(file == NULL) return NULL;

  fseek(file, 0, SEEK_END);
  long f_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  code = new char (f_size);

  while ((c = fgetc(file))!= EOF){
    code[n++] = (char)c;
  }
  code[n] = '\0';
  return code;
}

void fail(){
  printf("[error: unrecognized pattern] ");
  counter++;
  state = 0;
}

bool isDigit(char str){
  if (str == '0' || str == '1' || str == '2' || str == '3' || str == '4' ||
      str == '5' || str == '6' || str == '7' || str == '8' || str == '9')
      return (true);
  return (false);
}

bool isLetter(char str){
  if (isalpha(str) != 0)
    return (true);
  return (false);
}

Token nextToken(){
  Token token;
  char c;
  char str[20];
  memset(str, 0, sizeof(str));

  while(code[counter] != EOF){
    switch(state){
      case 0:
        c = code[counter];
        if((c == ' ') || (c == '\n')){
          counter++;
          state = 0;
        }
        else if(isDigit(c)) state = 1;
        else if(c == '_' || isLetter(c)) state = 5;
        else if(c == '"') state = 7;
        else if(c == '+') state = 10;
        else if(c == '-') state = 11;
        else if(c == '*') state = 12;
        else if(c == '/') state = 13;
        else if(c == '^') state = 14;
        else if(c == '(') state = 15;
        else if(c == ')') state = 16;
        else if(c == '{') state = 17;
        else if(c == '}') state = 18;
        else if(c == '[') state = 19;
        else if(c == ']') state = 20;
        else if(c == ';') state = 21;
        else if(c == ':') state = 22;
        else if(c == ',') state = 23;
        else if(c == '=') state = 24;
        else if(c == '~') state = 27;
        else if(c == '<') state = 29;
        else if(c == '>') state = 32;
        else if(c == '.') state = 35;
        else if(c == '@') state = 999;
        else fail();

        break;
      
      case 1:
        do {
          strncat(str, &c, 1);
          counter++;
          c = code[counter]; 
        }
        while (isDigit(c));

        state = 0;
        printf("<number, %s> ", str);
        token.name = number;
        token.attribute = atoi(str);
        
        memset(str, 0, sizeof(str));
        return(token);

        break;
      
      case 5:
        do {
          strncat(str, &c, 1);
          counter++;
          c = code[counter];
        }
        while (c == '_' || isLetter(c) || isDigit(c));

        state = 0;
        printf("<%s,> ", str);
        token.name = *str;
        token.attribute = NONE;

        memset(str, 0, sizeof(str));
        return(token);

        break;

      case 7:
        do {
          strncat(str, &c, 1);
          counter++;
          c = code[counter];
        }
        while (c != '"');
        
        strncat(str, &c, 1);
        counter++;

        state = 0;
        printf("<Literal,%s> ", str);
        token.name = *str;
        token.attribute = NONE;
        
        memset(str, 0, sizeof(str));
        return(token);

        break;

      case 10:
        counter++;
        state = 0;
        printf("<operator, SUM> ");
        
        token.name = operator;
        token.attribute = SUM;
        return(token);

        break;
      
      case 11:
        counter++;
        state = 0;
        printf("<operator, MIN> ");
        
        token.name = operator;
        token.attribute = MIN;
        return(token);

        break;
      
      case 12:
        counter++;
        state = 0;
        printf("<operator, MUL> ");
        
        token.name = operator;
        token.attribute = MUL;
        return(token);

        break;


      case 13:
        counter++;
        state = 0;
        printf("<operator, DIV> ");
        
        token.name = operator;
        token.attribute = DIV;
        return(token);

        break;

      case 14:
        counter++;
        state = 0;
        printf("<operator, POT> ");
        
        token.name = operator;
        token.attribute = POT;
        return(token);

        break;

      case 15:
        counter++;
        state = 0;
        printf("<operator, OP> ");
        
        token.name = operator;
        token.attribute = OP;
        return(token);

        break;

      case 16:
        counter++;
        state = 0;
        printf("<operator, CP> ");
        
        token.name = operator;
        token.attribute = CP;
        return(token);

        break;

      case 17:
        counter++;
        state = 0;
        printf("<operator, OB> ");
        
        token.name = operator;
        token.attribute = OB;
        return(token);

        break;

      case 18:
        counter++;
        state = 0;
        printf("<operator, CB> ");
        
        token.name = operator;
        token.attribute = CB;
        return(token);

        break;

      case 19:
        counter++;
        state = 0;
        printf("<operator, OBK> ");
        
        token.name = operator;
        token.attribute = OBK;
        return(token);

        break;

      case 20:
        counter++;
        state = 0;
        printf("<operator, CBK> ");
        
        token.name = operator;
        token.attribute = CBK;
        return(token);

        break;

      case 21:
        counter++;
        state = 0;
        printf("<operator, SC> ");
        
        token.name = operator;
        token.attribute = SC;
        return(token);

        break;

      case 22:
        counter++;
        state = 0;
        printf("<operator, COL> ");
        
        token.name = operator;
        token.attribute = COL;
        return(token);

        break;

      case 23:
        counter++;
        state = 0;
        printf("<operator, COM> ");
        
        token.name = operator;
        token.attribute = COM;
        return(token);

        break;

      case 24:
        counter++;
        c = code[counter];

        if(c == '=') state = 25;
        else state = 26;

        break;
      
      case 25:
        state = 0;
        printf("<operator, IFEQ> ");
        
        token.name = operator;
        token.attribute = IFEQ;
        return(token);

        break;
      
      case 26:
        state = 0;
        printf("<operator, EQ> ");
        
        token.name = operator;
        token.attribute = EQ;
        return(token);
        
        break;

      case 27:
        counter++;
        c = code[counter];

        if(c == '=') state = 28;
        else fail();
        
        break;
      
      case 28:
        state = 0;
        printf("<operator, NE> ");
        
        token.name = operator;
        token.attribute = NE;
        return(token);
        
        break;
      
      case 29:
        counter++;
        c = code[counter];

        if(c == '=') state = 30;
        else state = 31;

        break;
      
      case 30:
        state = 0;
        printf("<operator, LE> ");
        
        token.name = operator;
        token.attribute = LE;
        return(token);
        
        break;
      
      case 31:
        state = 0;
        printf("<operator, LT> ");
        
        token.name = operator;
        token.attribute = LT;
        return(token);
        
        break;
      
      case 32:
        counter++;
        c = code[counter];

        if(c == '=') state = 33;
        else state = 34;

        break;
      
      case 33:
        state = 0;
        printf("<operator, GE> ");
        
        token.name = operator;
        token.attribute = GE;
        return(token);
        
        break;
      
      case 34:
        state = 0;
        printf("<operator, GT> ");
        
        token.name = operator;
        token.attribute = GT;
        return(token);
        
        break;
      
      case 35:
        counter++;
        c = code[counter];

        if(c == '.') state = 36;
        else state = 37;

        break;
      
      case 36:
        state = 0;
        printf("<operator, DP> ");
        
        token.name = operator;
        token.attribute = DP;
        return(token);
        
        break;
      
      case 37:
        state = 0;
        printf("<operator, SP> ");
        
        token.name = operator;
        token.attribute = SP;
        return(token);
        
        break;
      
      case 999:
        token.name = EOF;
        token.attribute = -1;
        return(token);
    }
  }
}

int main(){
	Token token;
	code = readFile("code.txt");
	while(token.name != EOF) token = nextToken();
}
