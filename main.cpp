#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

const int Pnd = 156;

class CSquare {
public:
    string BoredSquares;
    string CodeID;

    string getBoredSquares() const;
    string getCodeID() const;

    void setSquareName(const string&);
    void setCodeID(const string&);

    friend istream& operator>>(istream& is, CSquare& s);
    friend ostream& operator<<(ostream& os, const CSquare& s);
};

void CSquare::setSquareName(const string& SquareName) {
    BoredSquares = SquareName;
}

void CSquare::setCodeID(const string& ID) {
    CodeID = ID;
}

string CSquare::getBoredSquares() const {
    return BoredSquares;
}

string CSquare::getCodeID() const {
    return CodeID;
}

ostream& operator<<(ostream& os, const CSquare& s) {
    os << s.getBoredSquares() << ' ';
    os << s.getCodeID() << ' ';
    return os;
}

istream& operator>>(istream& is, CSquare& s) {
    is >> s.BoredSquares;
    is >> s.CodeID;
    return is;
}

class CPlayer {
public:
    string MonoPlayerName;
    int PlayerMoney{};
    int PlayerPosition{};
};

int Random() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 6);
    return dis(gen);
}

int main() {
    CPlayer Player1;
    CPlayer Player2;

    Player1.MonoPlayerName = "hamster";
    Player2.MonoPlayerName = "pumpkin";
    Player1.PlayerMoney = 1500;
    Player2.PlayerMoney = 1500;
    Player1.PlayerPosition = 0;
    Player2.PlayerPosition = 0;

    ifstream squareFile("sqaures.txt");
    string boredSquares[26];
    if (!squareFile) {
        cout << "Cannot open the file!" << endl;
        return 1; // Exit the program with an error code
    }

    for (int i = 0; i < 26; ++i) {
        getline(squareFile, boredSquares[i]);
        cout << boredSquares[i] << " has been stored in the array! At position " << i << endl;
    }

    squareFile.close();

    for (int boredRounds = 0; boredRounds < 20; ++boredRounds) {
        cout << Player1.MonoPlayerName << " Rolls " << Random() << endl;
        Player1.PlayerPosition = (Player1.PlayerPosition + Random()) % 26;
        cout << Player1.MonoPlayerName << " lands on " << boredSquares[Player1.PlayerPosition] << endl;

        if (Player1.PlayerPosition == 25 || Player1.PlayerPosition == 51) {
            Player1.PlayerMoney += 200;
            cout << Player1.MonoPlayerName << " passes go and collects $" << Pnd << "200" << endl;
        }

        cout << Player2.MonoPlayerName << " Rolls " << Random() << endl;
        Player2.PlayerPosition = (Player2.PlayerPosition + Random()) % 26;
        cout << Player2.MonoPlayerName << " lands on " << boredSquares[Player2.PlayerPosition] << endl;

        if (Player2.PlayerPosition == 25 || Player2.PlayerPosition == 51) {
            Player2.PlayerMoney += 200;
            cout << Player2.MonoPlayerName << " passes go and collects $" << Pnd << "200" << endl;
        }
    }

    cout << "Game Over!" << endl;
    cout << Player1.MonoPlayerName << " has $" << Pnd << Player1.PlayerMoney << endl;
    cout << Player2.MonoPlayerName << " has $" << Pnd << Player2.PlayerMoney << endl;

    if (Player1.PlayerMoney > Player2.PlayerMoney) {
        cout << Player1.MonoPlayerName << " Wins!" << endl;
    }
    else if (Player2.PlayerMoney > Player1.PlayerMoney) {
        cout << Player2.MonoPlayerName << " Wins!" << endl;
    }
    else {
        cout << "It's a Draw!" << endl;
    }

    return 0;
}
