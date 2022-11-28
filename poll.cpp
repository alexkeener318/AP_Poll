#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string, std::cout, std::cin, std::endl, std::vector, std::ifstream;
// sort poll
void getRankings(vector<string> teamNames, int wins[32], int losses[32], int difficulty[32], vector<string> &rankings){

}

// updateWins/Losses
void updateWins(vector<int> wins, vector<int> losses, int weekNum){

}
// get input to update teams
void getInput(){

}

void populateNums(vector<int> wins, vector<int> losses, int &week){
    ifstream teamInfo("teams.csv");
    string line = "";
    int team = -1;
    while ( getline(teamInfo,line) )
    {
        if(team == -1){
            week = stoi(line);
            team++;
            continue;
        }
        int split = line.find(",");
        int win = stoi(line.substr(0,split));
        int loss = stoi(line.substr(split+1, line.length()-split-1));
        wins[team] = win;
        losses[team] = loss;
        team++;
    }
    teamInfo.close();
}

int main(){
    vector<string> teamNames = {"Alabama","Texas A&M","Auburn","LSU","Georgia","South Carolina","Tennessee","Florida","Vanderbilt","Kentucky",
                                "Ole Miss","Arkansas","USC","Utah","UCLA","Oregon","Baylor","Texas","Oklahoma","TCU","Texas Tech","Kansas State",
                                "Kansas","Oklahoma State","Ohio State","Illinois","Michigan","Iowa","Florida State","Clemson","Wake Forest","Louisville"};
    vector<int> wins;
    vector<int> losses;
    vector<int> difficulty = {10,7,8,9,10,7,9,6,5,6,7,8,9,7,6,8,5,7,7,9,6,8,7,5,10,5,9,4,6,7,3,3};

    vector<string> ranking[32];
    int weekNum = 0;
    populateNums(wins,losses,weekNum);
    //while(weekNum < 20){};

}