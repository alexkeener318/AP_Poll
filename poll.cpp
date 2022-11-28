#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string, std::cout, std::cin, std::endl, std::vector, std::ifstream;
struct team{
    string teamName;
    int wins;
    int losses;
    int ties;
    int difficulty;
    team(string name,int win, int loss, int tie, int diff){
        teamName = name;
        wins = win;
        losses = loss;
        ties= tie;
        diff = diff;
    }
};

// sort poll
void getRankings(vector<string> teamNames, int wins[32], int losses[32], int difficulty[32], vector<string> &rankings){

}

// updateWins/Losses
void updateWins(vector<int> wins, vector<int> losses, int weekNum){

}
// get input to update teams
void getInput(vector<team>* teams, int weekNum){
    cout << "TIME TO ENTER THE RESULTS OF WEEK " << weekNum << endl;
    cout <<"---------------------------------------------" << endl << endl;
    for(int i = 0; i < 32; i++){
        string result = "";
        cout << "Enter 1 if " << teams->at(i).teamName << " won, -1 if they loss, and 0 if they tied: ";
        cin >> result;
        cout << "\n You inputted " << result << endl << endl << endl;
        int num = stoi(result); 
        if(num == 1){
            
        }else if(num == 0){
            cout << teams->at(i).teamName << " TIED THIS WEEK" << endl << endl;
        }
        else if(num == -1){
            cout << teams->at(i).teamName << " LOSS THIS WEEK" << endl << endl;
        }else{
            cout << "Incorrect Number" << endl;
        }
    }
}

void populateNums(vector<team>* teams, int* week){
    ifstream teamInfo("teams.csv");
    string line = "";
    int teamNum = -1;
    while ( getline(teamInfo,line) )
    {
        if(teamNum == -1){
            *week = stoi(line);
            teamNum++;
            continue;
        }
        int split = line.find(",");
        int win = stoi(line.substr(0,split));
        int loss = stoi(line.substr(split+1, line.length()-split-1));
        teams->at(teamNum).wins = win;
        teams->at(teamNum).losses = loss;
        teamNum++;
    }
    teamInfo.close();
}

int main(){
    vector<string> teamNames = {"Alabama","Texas A&M","Auburn","LSU","Georgia","South Carolina","Tennessee","Florida","Vanderbilt","Kentucky",
                                "Ole Miss","Arkansas","USC","Utah","UCLA","Oregon","Baylor","Texas","Oklahoma","TCU","Texas Tech","Kansas State",
                                "Kansas","Oklahoma State","Ohio State","Illinois","Michigan","Iowa","Florida State","Clemson","Wake Forest","Louisville"};
    vector<int> difficulty = {10,7,8,9,10,7,9,6,5,6,7,8,9,7,6,8,5,7,7,9,6,8,7,5,10,5,9,4,6,7,3,3};

    vector<team> teams;
    for(int i = 0; i < 32; i++){
        teams.push_back(team(teamNames[i],0,0,0,difficulty[i]));
    }

    vector<string> ranking;
    int weekNum = 0;

    getInput(&teams, weekNum);
    populateNums(&teams,&weekNum);
    //while(weekNum < 20){};

}