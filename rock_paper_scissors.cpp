#include <iostream>
#include <stdlib.h>


int main() {
  srand (time(NULL));

  int computer = rand() % 3 + 1;
  int user;

  std::cout << "====================\n";
  std::cout << "rock paper scissors!\n";
  std::cout << "====================\n";

  std::cout << "1) ✊\n";
  std::cout << "2) ✋\n";
  std::cout << "3) ✌️\n";

  std::cout << "shoot! ";

  std::cin >> user;

  if (user == 1)
    std::cout << "you choose: ✊\n";
  else if (user == 2)
    std::cout << "you choose: ✋\n";
  else
    std::cout << "you choose: ✌️\n";

  if (computer == 1)
    std::cout << "cpu choose: ✊\n";
  else if (computer == 2)
    std::cout << "cpu choose: ✋\n";
  else
    std::cout << "cpu choose: ✌️\n";

  if (user == computer) {
    std::cout << "tie!! \n";
  }

  // user rock

  else if (user == 1) {
    if (computer == 2) {
      std::cout << "you lose!! cutting!!\n";
    }

    if (computer == 3) {
      std::cout << "you win!! czczc!!\n";
    }
  }

  else if (user == 2) {
    if (computer == 1) {
      std::cout << "you win!! czczc!!\n";
    }
    if (computer == 3) {
      std::cout << "you lose!! cutting!!\n";
    }
  }

  else if (user == 3) {
    if (computer == 1) {
      std::cout << "you lose!! cutting!!\n";
    }

    if (computer == 2) {
      std::cout << "you win!! czczc!!\n";
    }
  }

  return 0;

}