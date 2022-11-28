#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string, std::cout, std::cin, std::endl, std::vector, std::ifstream, std::ofstream;
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
        difficulty = diff;
    }
};

// sort poll
void getRankings(vector<team>* teams, vector<team>* rankings){
    // copy teams into rankings
    for(int i = 0; i < 32; i++){
        team curr = teams->at(i);
        rankings->at(i) = team(curr.teamName,curr.wins,curr.losses,curr.ties,curr.difficulty);
    }

    // sort the teams
    for(int i = 0; i < 31; i++){
        team curr = rankings->at(i);
        for(int j = i+1; j < 32; j++){
            // tied for wins
            if(curr.wins == rankings->at(j).wins){
                if(curr.losses > rankings->at(j).losses){
                    rankings->at(i) = rankings->at(j);
                    rankings->at(j) = curr;
                    curr = rankings->at(i);
                }else if(curr.losses == rankings->at(j).losses){
                    if(curr.difficulty < rankings->at(j).difficulty){
                        rankings->at(i) = rankings->at(j);
                        rankings->at(j) = curr;
                        curr = rankings->at(i);
                    }
                }
                // more wins
            }else if(curr.wins < rankings->at(j).wins){
                rankings->at(i) = rankings->at(j);
                rankings->at(j) = curr;
                curr = rankings->at(i);
            }
        }
    }

}

// updateWins/Losses
void updateWins(vector<team> teams, int weekNum){
    ofstream info("teams.csv");
    info << weekNum << "\n";
    for(int i = 0; i < 32; i++){
        info << teams[i].wins << "," << teams[i].losses << "," << teams[i].losses << "\n";
    }

}

// get input to update teams
void getInput(vector<team>* teams, int weekNum){
    cout << "TIME TO ENTER THE RESULTS OF WEEK " << weekNum << endl;
    cout <<"---------------------------------------------" << endl << endl;
    for(int i = 0; i < 32; i++){
        string result = "";
        cout << "Enter 1 if " << teams->at(i).teamName << " won,2 for a bye week, -1 if they loss, and 0 if they tied: ";
        cin >> result;
    
        int num = stoi(result); 
        if(num == 1){
            teams->at(i).wins++;
        }else if(num == 0){
            teams->at(i).ties++;
        }
        else if(num == -1){
            teams->at(i).losses++;
        }else{
            cout << "Incorrect Number" << endl;
        }
        cout << teams->at(i).teamName << " is now " << teams->at(i).wins << " - " << teams->at(i).losses << endl;
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
        line.erase(0, split+1);
        split = line.find(",");
        int loss = stoi(line.substr(0,split));
        int tie = stoi(line.substr(split+1, line.length()-split-1));
        
        teams->at(teamNum).wins = win;
        teams->at(teamNum).losses = loss;
        teams->at(teamNum).ties = tie;
        teamNum++;
    }
    teamInfo.close();
}

void outputRankings(vector<team> ranking, int weekNum){
    cout << endl <<  "      AP Poll For Week " << weekNum << endl;
    cout << "----------------------------------" << endl << endl;
    for(int i = 0; i < 25; i++){
        team curr = ranking.at(i);
        int diff = 20 - curr.teamName.length();
        string spaces = "";
        for(int i = 0; i < diff; i++){
            spaces += " ";
        }
        if(i < 9)
            cout <<" " <<  i+1 << ". " << curr.teamName << spaces << curr.wins << "-" << curr.losses << "-" << curr.ties << "    " << curr.difficulty << endl;
        else
            cout << i+1 << ". " << curr.teamName << spaces << curr.wins << "-" << curr.losses << "-" << curr.ties << "    " << curr.difficulty << endl;
    }
    cout << endl <<  "Also recieved votes: " << ranking.at(25).teamName << ", " << ranking.at(26).teamName << ", " << ranking.at(27).teamName << ", " <<
    ranking.at(28).teamName << ", " << ranking.at(29).teamName << ", " << ranking.at(30).teamName << ", " << ranking.at(31).teamName << endl << endl;
}

int main(){
    vector<string> teamNames = {"Alabama","Texas A&M","Auburn","LSU","Georgia","South Carolina","Tennessee","Florida","Vanderbilt","Kentucky",
                                "Ole Miss","Arkansas","USC","Utah","UCLA","Oregon","Baylor","Texas","Oklahoma","TCU","Texas Tech","Kansas State",
                                "Kansas","Oklahoma State","Ohio State","Illinois","Michigan","Iowa","Florida State","Clemson","Wake Forest","Louisville"};
    vector<int> difficulty = {10,7,8,9,10,7,9,6,5,6,7,8,9,7,6,8,5,7,7,9,6,8,7,5,10,5,9,4,6,7,3,3};

    vector<team> teams;
    vector<team> ranking;
    for(int i = 0; i < 32; i++){
        teams.push_back(team(teamNames[i],0,0,0,difficulty[i]));
        ranking.push_back(team("",0,0,0,0));
    }
    int weekNum = 0;
    populateNums(&teams,&weekNum);
    int input = 0;
    string in = "";
    cout << "options:\n0 - Enter info for a new week\n1 - View the current rankings\n2 - Exit\n";
    cin >> in;
    input = stoi(in);
    while(input != 2){
        if(input == 0){
            getInput(&teams, weekNum);
            updateWins(teams, weekNum);
        }else if(input == 1){
            populateNums(&teams,&weekNum);
            getRankings(&teams, &ranking);
            outputRankings(ranking, weekNum);
        }
        cout << "options:\n0 - Enter info for a new week\n1 - View the current rankings\n2 - Exit\n";
        cin >> in;
        input = stoi(in);
    }
    cout << "Exiting!" << endl;
    
}