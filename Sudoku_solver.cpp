#include <iostream>

void izlasitPuzli(int lauks[][9]);
bool meklēt(int lauks[][9]);
int saņemtLaukumaSaraksts(int lauks[][9], int laukumaSaraksts[][2]);
void printLauks(int lauks[][9]);
bool pieejams(int i, int j, int lauks[][9]);
bool pieejams(int lauks[][9]);

int main(){
  int lauks[9][9];
  izlasitPuzli(lauks);

  if (!pieejams(lauks))
    std::cout << "Nepareizi ievadīti skaitļi" << std::endl;
  else if (meklēt(lauks)){
    std::cout << "Risinājums:" << std::endl;
    printLauks(lauks);
  }
  else
    std::cout << "Šajam sudoku nav risinājuma" << std::endl;

  return 0;
}

void izlasitPuzli(int lauks[][9]){
  std::cout << "Ievadiet Sudoku uzdevumu:" << std::endl;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      std::cin >> lauks[i][j];
}

int saņemtLaukumaSaraksts(int lauks[][9], int laukumaSaraksts[][2]){
  int laukumaSarakstaNumurs = 0;

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (lauks[i][j] == 0){
        laukumaSaraksts[laukumaSarakstaNumurs][0] = i;
        laukumaSaraksts[laukumaSarakstaNumurs][1] = j;
        laukumaSarakstaNumurs++;
      }

  return laukumaSarakstaNumurs;
}

void printLauks(int lauks[][9]){
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++)
      std::cout << lauks[i][j] << " ";
    std::cout << std::endl;
  }
}

bool meklēt(int lauks[][9]){
  int k = 0;
  bool found = false;

  int laukumaSaraksts[81][2];
  int laukumaSarakstaNumurs = saņemtLaukumaSaraksts(lauks, laukumaSaraksts);

  while (!found){
    int i = laukumaSaraksts[k][0];
    int j = laukumaSaraksts[k][1];
    if (lauks[i][j] == 0)
      lauks[i][j] = 1;

    if (pieejams(i, j, lauks)){
      if (k + 1 == laukumaSarakstaNumurs){
        found = true;
      }
      else{
        k++;
      }
    }
    else if (lauks[i][j] < 9){
      lauks[i][j] = lauks[i][j] + 1;
    }
    else{
      while (lauks[i][j] == 9){
        lauks[i][j] = 0;
        if (k == 0){
          return false;
        }
        k--;
        i = laukumaSaraksts[k][0];
        j = laukumaSaraksts[k][1];
      }

      lauks[i][j] = lauks[i][j] + 1;
    }
  }

  return true;
}

bool pieejams(int i, int j, int lauks[][9]){
  for (int kolonna = 0; kolonna < 9; kolonna++)
    if (kolonna != j && lauks[i][kolonna] == lauks[i][j])
      return false;

  for (int rinda = 0; rinda < 9; rinda++)
    if (rinda != i && lauks[rinda][j] == lauks[i][j])
      return false;

  for (int rinda = (i / 3) * 3; rinda < (i / 3) * 3 + 3; rinda++)
    for (int kolonna = (j / 3) * 3; kolonna < (j / 3) * 3 + 3; kolonna++)
      if (rinda != i && kolonna != j && lauks[rinda][kolonna] == lauks[i][j])
        return false;

  return true;
}

bool pieejams(int lauks[][9]){
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (lauks[i][j] != 0)
        if (!pieejams(i, j, lauks))
          return false;

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if ((lauks[i][j] < 0) || (lauks[i][j] > 9))
        return false;

  return true;
}