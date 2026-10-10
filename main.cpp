#include "random.h"
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>
int MAXGUESS{15};
int TotalGuesses{15};
class Session {
public:
  Session(const std::string_view word, std::string& guesses, std::string& state,
          int wrongGuessCount, bool isPlaying)
      : m_word{word}, m_guesses{guesses}, m_currentState{state},
        m_wrongGuesses{wrongGuessCount}, m_isPlaying{isPlaying} {}

  void displayWordAsUnderScores() {
    std::string wordInUs;
    for (int i{0}; i < m_word.length(); ++i) {
      wordInUs += "_";
    }
    std::cout << "The word is: " << m_word << '\n';
    std::cout << "The word: " << wordInUs << '\n';
    m_currentState = wordInUs;
  }
  std::string_view getCurrentState() { return m_currentState; }
  bool getIsPlaying() { return m_isPlaying; }
  bool getReachedMaxG() { return m_wrongGuesses > MAXGUESS; }
  bool handleWinLoss();
  void updateCurrentState();
  std::vector<int> findIdxOfGuess(char);
  void updateGuessUI();
  std::string_view getWord() { return m_word; }

private:
  std::string_view m_word;
  std::string& m_guesses;
  std::string& m_currentState;
  int m_wrongGuesses;
  bool m_isPlaying;
};
namespace WordList {
enum Words {
  mystery,
  broccoli,
  account,
  almost,
  sphagetti,
  opinion,
  beautiful,
  distance,
  luggage
};

}

std::string_view getEnumString(int idx) {
  switch (idx) {
  case WordList::mystery:
    return "mystery";
  case WordList::broccoli:
    return "broccoli";
  case WordList::account:
    return "account";
  case WordList::almost:
    return "almost";
  case WordList::sphagetti:
    return "sphagetti";
  case WordList::opinion:
    return "opinion";
  case WordList::beautiful:
    return "beautiful";
  case WordList::distance:
    return "distance";
  case WordList::luggage:
    return "luggage";
  default:
    return "Invalid";
    break;
  }
}
void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
char getGuess() {
  while (true) {
    std::cout << "Enter your next letter: ";

    char c{};
    std::cin >> c;

    if (!std::cin) {
      std::cin.clear();
      std::cout << "That wasn't a valid input.  Try again.\n";
      ignoreLine();
      continue;
    }

    ignoreLine();

    if (c < 'a' || c > 'z') {
      std::cout << "That wasn't a valid input.  Try again.\n";
      continue;
    }

    return c;
  }
}

std::string_view getRandomWord() {
  int randomIDX{Random::get(0, 8)};
  std::string_view word{getEnumString(randomIDX)};
  return word;
}

void displayStart() {
  std::cout << "Welcome to C++man " << '\n';
  std::cout << "To win: guess the word, To lose run out of pluses" << '\n';
}
void Session::updateCurrentState() {
  int totalCount{};
  if (m_currentState.length() != m_word.length()) {
    assert("The word and session state don't have the same length");
  }
  updateGuessUI();
  char c{getGuess()};
  m_guesses += c;
  std::vector<int> idx{findIdxOfGuess(c)};
  if (idx.empty()) {
    m_wrongGuesses += 1;
    TotalGuesses -= 1;
    std::cout << "You guessed wrong! You have " << TotalGuesses << " left"
              << '\n';
  }
  if (idx.size() >= 2) {
    for (int i{0}; i < m_currentState.length(); i++) {
      for (int value : idx) {
        m_currentState[value] = c;
      }
    }
  }
  for (int value : idx) {
    m_currentState[value] = c;
  }
  totalCount += 1;
  std::cout << "The word: " << m_currentState << '\n';
  std::cout << "Guesses Remaining: " << TotalGuesses << '\n';
}
void Session::updateGuessUI() {
  std::vector<char> guessedChars{};
  for (int i{0}; i < std::ssize(m_guesses); ++i) {
    guessedChars.push_back(m_guesses[i]);
  }
  std::cout << "Guessed Chars: ";
  for (auto value : guessedChars) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

std::vector<int> Session::findIdxOfGuess(char c) {
  std::vector<int> idxs{};
  for (int i{0}; i < m_word.length(); ++i) {
    if (c == m_word[i]) {
      std::cout << c << " was found";
      idxs.push_back(i);
    }
  }
  return idxs;
}

int main() {

  bool inGame = true;
  std::string guesses{};
  std::string state{};
  const std::string word{getRandomWord()};
  int wronGuessCount{};
  Session session{word, guesses, state, wronGuessCount, true};
  displayStart();
  session.displayWordAsUnderScores();
  while (!session.getReachedMaxG() &&
         session.getWord() != session.getCurrentState()) {
    session.updateCurrentState();
  }
  if (session.getReachedMaxG()) {
    std::cout << "You lose! The word was " << session.getWord() << '\n';
  } else if (session.getWord() == session.getCurrentState()) {
    std::cout << "You Won!\n";
  }

  return 0;
}
