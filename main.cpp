#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;

//bracket class
class Bracket {
private:
    int rank1, rank2, score1, score2, roundm, gamem;
    string region, team1, team2, winner;

public:
    //default
    Bracket() {
        rank1 = -1;
        rank2 = -1;
        score1 = -1;
        score2 = -1;
        roundm = -1;
        gamem = -1;
        region = "(NO_REGION)";
        team1 = "(NO_TEAM_1)";
        team2 = "(NO_TEAM_2)";
        winner = "(NO_WINNER)";
    }
    //fully qualified constructor
    Bracket(string region, int rank1, string team1, int score1, int rank2, string team2, int score2, string winner, int roundm, int gamem) {
        setregion(region);
        setrank1(rank1);
        setteam1(team1);
        setscore1(score1);
        setrank2(rank2);
        setteam2(team2);
        setscore2(score2);
        setwinner(winner);
        setroundm(roundm);
        setgamem(gamem);
    }

    //the setter methods
    void setrank1(int rank1) {
        this->rank1 = rank1;
    }
    void setrank2(int rank2) {
        this->rank2 = rank2;
    }
    void setscore1(int score1) {
        this->score1 = score1;
    }
    void setscore2(int score2) {
        this->score2 = score2;
    }
    void setroundm(int roundm) {
        this->roundm = roundm;
    }
    void setgamem(int gamem) {
        this->gamem = gamem;
    }
    void setregion(string region) {
        this->region = region;
    }
    void setteam1(string team1) {
        this->team1 = team1;
    }
    void setteam2(string team2) {
        this->team2 = team2;
    }
    void setwinner(string winner) {
        this->winner = winner;
    }

    //the getter mothods
    int getrank1() {
        return rank1;
    }
    int getrank2() {
        return rank2;
    }
    int getscore1() {
        return score1;
    }
    int getscore2() {
        return score2;
    }
    int getroundm() {
        return roundm;
    }
    int getgamem() {
        return gamem;
    }
    string getregion() {
        return region;
    }
    string getteam1() {
        return team1;
    }
    string getteam2() {
        return team2;
    }
    string getwinner() {
        return winner;
    }

    //get winning team rank utility method
    int getwinnerrank() {
        string winner = getwinner();
        if (getteam1() == winner) {
            return getrank1();
        }
        else if (getteam2() == winner) {
            return getrank2();
        }
        else {
            return 0;
        }
    }
};

//read in data
void streaming(vector<Bracket>& data, string file) {
    string values[10];
    int valuez[10];
    string temp;
    ifstream stream;
    stream.open(file);
    assert(stream.fail() == false);
    data.clear();
    getline(stream, temp);
    while (getline(stream, temp)) {
        for (int i = 0; i < 10; i++) {
            int index = temp.find(',');
            string news = temp.substr(0, index);
            values[i] = news;
            if (values[i].length() < 1) {
                values[i] = -1;
            }
            temp.erase(0, index + 1);
            stringstream ss;
            ss << values[i];
            ss >> valuez[i];
        }
        Bracket tempb(values[0], valuez[1], values[2], valuez[3], valuez[4], values[5], valuez[6], values[7], valuez[8], valuez[9]);
        data.push_back(tempb);
    }
    stream.close();
}

//overall info of the bracket
void info(vector<Bracket> bracket, string file) {
    string team1, team2;
    int counter = 0;
    vector<string> finald;
    string regions[4];
    string final4[4];

    //determining if men or women
    if (file == "womens_bracket_2022.csv") {
        regions[0] = "Greensboro";
        regions[1] = "Wichita";
        regions[2] = "Spokane";
        regions[3] = "Bridgeport";
    }
    else if (file == "mens_bracket_2021.csv" || "mens_bracket_2022.csv") {
        regions[0] = "West";
        regions[1] = "South";
        regions[2] = "East";
        regions[3] = "Midwest";
    }
    else {
        return;
    }

    //counting number of games played
    for (int i = 0; i < bracket.size(); i++) {
        counter++;
        if (bracket.at(i).getregion() == "Final Four") {
            team1 = bracket.at(i).getteam1();
            team2 = bracket.at(i).getteam2();
            finald.push_back(team1);
            finald.push_back(team2);
        }
    }

    //finding region of the final 4
    for (int i = 0; i < bracket.size(); i++) {
        for (int j = 0; j < finald.size(); j++) {
            if (bracket.at(i).getregion() != "Final Four" || bracket.at(i).getregion() != "Championship") {
                if (finald.at(j) == bracket.at(i).getwinner()) {
                    if (bracket.at(i).getregion() == regions[0]) {
                        final4[0] = finald.at(j);
                        break;
                    }
                    else if (bracket.at(i).getregion() == regions[1]) {
                        final4[1] = finald.at(j);
                        break;
                    }
                    else if (bracket.at(i).getregion() == regions[2]) {
                        final4[2] = finald.at(j);
                        break;
                    }
                    else if (bracket.at(i).getregion() == regions[3]) {
                        final4[3] = finald.at(j);
                        break;
                    }
                }
            }
        }
    }
    cout << "Total number of games played in tournament: " << counter << "\nThe Final Four contestants are:\n       " << regions[0] << " region:    " << final4[0] << "\n       " << regions[1] << " region:   " << final4[1] << "\n       " << regions[2] << " region:    " << final4[2] << "\n       " << regions[3] << " region: " << final4[3] << endl;
}

//winnin path
void winned(vector<Bracket> bracket) {
    string winnerz;
    vector<Bracket> path;
    //figure out who won
    for (int i = 0; i < bracket.size(); i++) {
        if (bracket.at(i).getregion() == "Championship") {
            winnerz = bracket.at(i).getwinner();
            break;
        }
    }
    //grab their tourney path
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j < bracket.size(); j++) {
            if (bracket.at(j).getroundm() == i) {
                if (bracket.at(j).getwinner() == winnerz) {
                    path.push_back(bracket.at(j));
                    break;
                }
            }
        }
    }
    //display path
    cout << "Path to the championship:" << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << "Round " << path.at(i).getroundm() << ", Game " << path.at(i).getgamem() << ": " << path.at(i).getteam1() << " vs " << path.at(i).getteam2() << ". Winner: " << path.at(i).getwinner() << endl;
    }
}

//prediciton to win at given round
void foresight(vector<Bracket> bracket, int pround, string file) {
    vector<Bracket> yoink;
    string regions[4];
    int regionz[4];
    int index;

    if (file == "womens_bracket_2022.csv") {
        regions[0] = "Greensboro";
        regions[1] = "Wichita";
        regions[2] = "Spokane";
        regions[3] = "Bridgeport";
    }
    else if (file == "mens_bracket_2021.csv" || "mens_bracket_2022.csv") {
        regions[0] = "West";
        regions[1] = "South";
        regions[2] = "East";
        regions[3] = "Midwest";
    }
    else {
        return;
    }

    for (int i = 0; i < bracket.size(); i++) {
        if (bracket.at(i).getroundm() == pround) {
            yoink.push_back(bracket.at(i));
        }
    }

    if(pround != 5){
      regionz[0] = regionz[1] = regionz[2] = regionz[3] = 0;
      for (int i = 0; i < yoink.size(); i++) {
          if (yoink.at(i).getregion() == regions[0]) {
              regionz[0] += yoink.at(i).getwinnerrank();
          }
          else if (yoink.at(i).getregion() == regions[1]) {
              regionz[1] += yoink.at(i).getwinnerrank();
          }
          else if (yoink.at(i).getregion() == regions[2]) {
              regionz[2] += yoink.at(i).getwinnerrank();
          }
          else if (yoink.at(i).getregion() == regions[3]) {
              regionz[3] += yoink.at(i).getwinnerrank();
          }
          else {
              continue;
          }
      }
      
      int low = 200;
      for (int i = 0; i < 4; i++) {
          int templow = regionz[i];
          if (templow < low) {
              low = templow;
              index = i;
          }
      }
  }
  else if(pround == 5){
    string team[4];
    for(int i = 0; i < yoink.size(); i++){
      team[i] = yoink.at(i).getteam1();
      team[i+1] = yoink.at(i).getteam2();
      i++;
    }
    for(int i = 0; i < bracket.size(); i++){
      if(bracket.at(i).getregion() != "Final Four" || bracket.at(i).getregion() != "Championship"){
        for(int j = 0; j < 4; j++){
          if (team[j] == bracket.at(i).getwinner()) {
            if (bracket.at(i).getregion() == regions[0]) {
               regionz[0] = bracket.at(i).getwinnerrank();
                break;
            }
            else if (bracket.at(i).getregion() == regions[1]) {
              regionz[1] = bracket.at(i).getwinnerrank();
              break;
            }
            else if (bracket.at(i).getregion() == regions[2]) {
              regionz[2] = bracket.at(i).getwinnerrank();
              break;
            }
            else if (bracket.at(i).getregion() == regions[3]) {
              regionz[3] = bracket.at(i).getwinnerrank();
              break;
            }
          }
        }
      }
    }
    int low = 200;
    for (int i = 0; i < 4; i++) {
        int templow = regionz[i];
        if (templow < low) {
            low = templow;
            index = i;
        }
    }
  }

    cout << "The region expected to win is: " << regions[index] << endl;
}

void notgood(vector<Bracket> bracket, int pround){
  vector<Bracket> yoink;
  for (int i = 0; i < bracket.size(); i++) {
    if (bracket.at(i).getroundm() == pround) {
      yoink.push_back(bracket.at(i));
    }
  }
  int index, indef, indes, teamp1, teamp2;
  int high = 0;
  for(int i = 0; i < yoink.size(); i++){
    int temphigh;
    teamp1 = yoink.at(i).getrank1();
    teamp2 = yoink.at(i).getrank2();
    if(teamp2 > teamp1){
      temphigh = teamp2;
      indef = 2;
    }
    else{
      temphigh = teamp1;
      indef = 1;
    }

    if(temphigh > high){
      high = temphigh;
      index = i;
      indes = indef;
    }
  }
  if(indes == 2){
    cout << "The best underdog team is " << yoink.at(index).getteam2() << " which has rank " << yoink.at(index).getrank2() << "." << endl;
  }
  else{
    cout << "The best underdog team is " << yoink.at(index).getteam1() << " which has rank " << yoink.at(index).getrank1() << "." << endl;
  }
  
}

void epicgames(vector<Bracket> bracket, int pround){
  int bigdif, smalldif, indeb, indes;
  vector<Bracket> yoink;
  if(pround == 7){
    for (int i = 0; i < bracket.size(); i++) {
    yoink.push_back(bracket.at(i));
    }
  }
  else{
    for (int i = 0; i < bracket.size(); i++) {
      if (bracket.at(i).getroundm() == pround) {
        yoink.push_back(bracket.at(i));
      }
    }
  }
  bigdif = 0;
  smalldif = 200;
  for(int i = 0; i < yoink.size(); i++){
    int tempdif = abs(yoink.at(i).getscore1() - yoink.at(i).getscore2());
    if(tempdif > bigdif){
      bigdif = tempdif;
      indeb = i;
    }
    if(tempdif < smalldif){
      smalldif = tempdif;
      indes = i;
    }
  }
  cout << "The shoo-in game was:\nRound " << yoink.at(indeb).getroundm() << ", Game " << yoink.at(indeb).getgamem() << ": " << yoink.at(indeb).getteam1() << " vs " << yoink.at(indeb).getteam2() << ". Winner: " << yoink.at(indeb).getwinner() << "\nThe difference was " << bigdif << " points.\n" << endl;

  cout << "The nail-biting game was:\nRound " << yoink.at(indes).getroundm() << ", Game " << yoink.at(indes).getgamem() << ": " << yoink.at(indes).getteam1() << " vs " << yoink.at(indes).getteam2() << ". Winner: " << yoink.at(indes).getwinner() << "\nThe difference was " << smalldif << " points.\n" << endl;
}

void gambling(vector<Bracket> real, vector<Bracket> fake){
  int score = 0;
  int counter = 0;
  for(int i = 0; i < real.size(); i++){
    if(real.at(i).getwinner() == fake.at(i).getwinner()){
      counter++;
      int multiplier = real.at(i).getroundm() * 5;
      score += multiplier;
    }
  }
  cout << "You correctly predicted the winner for " << counter << " games." << endl;
  cout << "This means that you have a score of " << score << "." << endl;
  if(score >= 250){
    cout << "Great job! You could consider entering your predictions to win money!" << endl;
  }
  else{
    cout << "You may want to learn more about basketball to improve your predictions next year." << endl;
  }
}

//main
int main() {
    vector<Bracket> data, predict;
    int menuop1, menuop2;
    string filename, predictname;
    bool stateofmain;

    cout << "Program 5: March Madness Frenzy\nCS 141, Spring 2022, UIC\n" << endl;
    cout << "This program reads in data from NCAA Basketball Tournaments (aka March Madness). It provides overall information regarding the data, allows you to see the path taken to the championship, uses rankings of teams to determine which region is expected to win at a given round and to find the best underdog team, and calculates point differences within the games. You can also compare the actual brackets to your own predictions!\n" << endl;
    cout << "Enter the name of the file with the data for the NCAA tournament:" << endl;
    cin >> filename;
    cout << endl;

    streaming(data, filename);
    //cout << data.size();
    stateofmain = true;

    while (stateofmain) {

        cout << "\nSelect a menu option: \n   1. Display overall information about the data\n   2. Display the path of the winning team to the championship\n   3. Determine which region is expected to win the championship based on a given round\n   4. Identify the best underdog within a given round\n   5. Find the shoo-in and nail-biting games within a given round, or overall\n   6. Compare the actual brackets to your predicted brackets\n   7. Exit\nYour choice --> ";
        cin >> menuop1;

        switch (menuop1) {
            //overall info
        case 1:
            cout << endl;
            info(data, filename);
            break;

            //winning path of winner
        case 2:
            winned(data);
            break;

            //pick a region
        case 3:
            cout << "Enter a round to be evaluated:\n   Select 2 for round 2\n   Select 3 for round 3 'Sweet 16'\n   Select 4 for round 4 'Elite 8'\n   Select 5 for round 5 'Final 4'\nYour choice --> ";
            cin >> menuop2;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "no" << endl;
            }
            else if (menuop2 == 2 || menuop2 == 3 || menuop2 == 4 || menuop2 == 5) {
                cout << "Analyzing round " << menuop2 << "...\n" << endl;
                foresight(data, menuop2, filename);
            }
            else {
                cout << "not pickable" << endl;
            }
            break;

            //underdog
        case 4:
            cout << "Enter a round to be evaluated:\n   Select 2 for round 2\n   Select 3 for round 3 'Sweet 16'\n   Select 4 for round 4 'Elite 8'\n   Select 5 for round 5 'Final 4'\n   Select 6 for round 6 'Championship'\nYour choice --> ";
            cin >> menuop2;
            if(cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "no" << endl;
            }
            else if (menuop2 == 2 || menuop2 == 3 || menuop2 == 4 || menuop2 == 5 || menuop2 == 6) {
                notgood(data, menuop2);
            }
            else {
                cout << "not pickable" << endl;
            }
            break;

            //close and not close games
        case 5:
            cout << "Enter a round to be evaluated:\n   Select 1 for round 1\n   Select 2 for round 2\n   Select 3 for round 3 'Sweet 16'\n   Select 4 for round 4 'Elite 8'\n   Select 5 for round 5 'Final 4'\n   Select 6 for round 6 'Championship'\n   Select 7 for the overall tournament\nYour choice --> ";
            cin >> menuop2;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "no" << endl;
            }
            else if (menuop2 == 1 || menuop2 == 2 || menuop2 == 3 || menuop2 == 4 || menuop2 == 5 || menuop2 == 6) {
                cout << "Analyzing round " << menuop2 << "...\n" << endl;
                epicgames(data, menuop2);
            }
            else if(menuop2 == 7){
              cout << "Analyzing the overall tournament..." << endl;
              epicgames(data, menuop2);
            }
            else {
                cout << "not pickable" << endl;
            }

            break;

            //compare
        case 6:
            cout << "Enter the name of the file with your predicted brackets:" << endl;
            cin >> predictname;
            streaming(predict, predictname);
            
            gambling(data, predict);
            break;

            //exit
        case 7:
            stateofmain = false;
            cout << "Exiting program..." << endl;
            break;

        default:
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cout << "\nInvalid value.  Please re-enter a value from the menu options below." << endl;
            cin.clear();
            break;
        }

    }



}