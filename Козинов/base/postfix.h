#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <map>
using namespace std;

class TPostfix
{
	map <string, int> priority;
	map <string, int> operations;
	string infix;
	string postfix;
public:
  TPostfix()
  {
	  operations = { { "+",1 },{ "-",2 },{ "*",3 },{ "/",4 },{ "sin",5 },{ "cos",6 },{"log",7} };
	  priority = { { "+",4 },{ "-",4 },{ "*",3 },{ "/",3 },{ "(",1 },{ ")",-1 },{ "sin",2 },{ "cos",2 },{"log",2} };
  }
  string Infix2Space(); // Преобразование строки в строку с проблеами после каждого операнда,переменной,константы
  void SetInfix(string &a) { infix = a; }
  bool isNumber(const string &a);// Проверка на константу
  bool isAlt(const string &a); // Проверка на переменную
  void isCorrectInfix();//Контроль правильности введенной строки
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix();
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
