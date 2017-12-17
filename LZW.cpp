#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<sstream>
#include <fstream>
#include <bitset>

using namespace std;

int existe(string temp, string dicionario[], int j){
  for (int i = 0; i < j; i++) {
    if (dicionario[i] == temp)
      return i;
  }
  return -1;
}

string toBinario(int x){
  bitset<8> bits(x);
  //bits = x;
  return bits.to_string();
}

long toDecimal(string x){
  bitset<8> bits(x);
  return bits.to_ulong();
}

void compactar(){
  FILE *entrada;
  string text = "", temp = "";
  string dicionario[20];
  int c;
  int pos, i = 0, j = 0, x = -1;

  entrada = fopen("ArquivoOriginal.txt", "r");
  //saida = fopen("ArquivoSaida.bin", "w");

  ofstream saida ("ArquivoCompactado.bin");

  if (ferror(entrada))
    return ;

  while(!feof(entrada)){
    c = getc(entrada);
    if(c != EOF && c != 10)
      text += c;
  }

  for (int k = 0; k < text.length(); k++) {
    temp = text[k];
    if (existe(temp, dicionario, j) == -1){
      dicionario[j] = text[k];
      j++;
    }
    temp = "";
  }

  while (i < text.length()) {
    temp += text[i];
    pos = existe(temp, dicionario, j);
    if (pos == -1){
      dicionario[j] = temp;
      saida << toBinario(x);
      temp = text[i];
      x = existe(temp, dicionario, j);
      saida << toBinario(x);

      temp = "";
      i++;
      j++;
      x = -1;
    }
    else{
      x = pos;
      i++;
    }
  }

  fclose(entrada);
}

void descompactar(){
  FILE *entrada;
  string text = "", temp = "";
  string dicionario[20];
  char c;
  int i = 0, j = 0;

  entrada = fopen("ArquivoCompactado.txt", "r+");
  //saida = fopen("ArquivoSaida.bin", "w");

  ofstream saida ("ArquivoDescompactado.txt");

  if (ferror(entrada))
    return ;

  while(!feof(entrada)){
    c = getc(entrada);
    if(c != EOF)
      text += c;
  }

  while (i < text.length()) {
    if (text[i] == '0'){
      c = toDecimal(text.substr(i+1, 8));
      saida << c;
      dicionario[j] = c;

      i += 9;
      j++;
    }
    else{
      temp = dicionario[toDecimal(text.substr(i+1, 8))];
      saida << temp;
      i += 9;

      c = toDecimal(text.substr(i, 8));
      saida << c;
      dicionario[j] = temp + c;

      i += 8;
      j++;
    }
  }

  fclose(entrada);
}

int main(void){
  int opcao;

  cout << "0: Compactar" << endl << "1: Descompactar" << endl;
  cin >> opcao;

  switch (opcao) {
    case 0: compactar();
      break;
    case 1: descompactar();
      break;
    default: cout << "Não seja burro";
  }

  return 0;
}

//stringstream convert;

//convert.str("");
//convert.clear();

//convert << x + 1;
//cout << convert.str() + text[i] << endl;
//fputs(convert.str() + text[i], saida);
//fscanf( saida, "%d%s", &x, text[i] );
//cout << std::to_string(x) + text[i] << endl;
