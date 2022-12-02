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
    int prevRank;
    team(string name,int win, int loss, int tie, int diff, int preran){
        teamName = name;
        wins = win;
        losses = loss;
        ties= tie;
        difficulty = diff;
        prevRank = preran;
    }
};

// sort poll
void getRankings(vector<team>* teams, vector<team>* rankings, int weekNum){
    // copy teams into rankings
    for(int i = 0; i < 32; i++){
        team curr = teams->at(i);
        rankings->at(i) = team(curr.teamName,curr.wins,curr.losses,curr.ties,curr.difficulty, curr.prevRank);
    }

    // sort the teams
    for(int i = 0; i < 31; i++){
        team curr = rankings->at(i);
        for(int j = i+1; j < 32; j++){
            // Uses tie breakers if wins are the same
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
            // Lowers it's ranking if it has less wins than the comparison team
            }else if(curr.wins < rankings->at(j).wins){
                rankings->at(i) = rankings->at(j);
                rankings->at(j) = curr;
                curr = rankings->at(i);
            }
        }
    }

}

// Writes to the csv file the new updated stats for each team
void updateWins(vector<team> teams, int weekNum){
    ofstream info("teams.csv");
    info << weekNum << "\n";
    for(int i = 0; i < 32; i++){
        info << teams[i].wins << "," << teams[i].losses << "," << teams[i].ties << "," << teams[i].prevRank << "\n";
    }

}

// Gets the results of the past week for each team and updates each team object
void getInput(vector<team>* teams, int weekNum){
    cout << "TIME TO ENTER THE RESULTS OF WEEK " << weekNum << endl;
    cout <<"---------------------------------------------" << endl << endl;
    for(int i = 0; i < 32; i++){
        string result = "";
        cout << teams->at(i).teamName << " was " << teams->at(i).wins << "-" << teams->at(i).losses << "-" << teams->at(i).ties << " last week" << endl;
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
        }else if(num == 2){
            cout << "";
        }else{
            cout << "Incorrect Number" << endl;
        }
        cout << teams->at(i).teamName << " is now " << teams->at(i).wins << "-" << teams->at(i).losses << "-" << teams->at(i).ties << endl << endl;
    }
}

// Pulls the data from the csv to implement into each team struct
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
        line.erase(0, split+1);
        split = line.find(",");
        int tie = stoi(line.substr(0,split));
        int prevRank = stoi(line.substr(split+1, line.length()-split-1));
        
        teams->at(teamNum).wins = win;
        teams->at(teamNum).losses = loss;
        teams->at(teamNum).ties = tie;
        teams->at(teamNum).prevRank = prevRank;
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
        int rankDif = curr.prevRank - (i+1);
        string rankNum = "";
        if(rankDif == 0){
            rankNum += " -";
        }else if(rankDif > 0){
            rankNum += "+" + std::to_string(rankDif);
        }else{
            rankNum += std::to_string(rankDif);
        }
        for(int i = 0; i < diff; i++){
            spaces += " ";
        }
        if(i < 9)
            cout <<" " <<  i+1 << ". " << curr.teamName << spaces << curr.wins << "-" << curr.losses << "-" << curr.ties << "    " << rankNum << endl;
        else
            cout << i+1 << ". " << curr.teamName << spaces << curr.wins << "-" << curr.losses << "-" << curr.ties << "    " << rankNum << endl;
    }
    cout << endl <<  "Also recieved votes: " << ranking.at(25).teamName << ", " << ranking.at(26).teamName << ", " << ranking.at(27).teamName << ", " <<
    ranking.at(28).teamName << ", " << ranking.at(29).teamName << ", " << ranking.at(30).teamName << ", " << ranking.at(31).teamName << endl << endl;
}

// Updates each team's previous rank for use in the AP Poll output
void updatePrevRank(vector<team>* ranking, vector<team>* teams){
    for(int i = 0; i < 32; i++){
        string name = ranking->at(i).teamName;
        for(int j = 0; j < 32; j++){
            if(teams->at(j).teamName == name){
                teams->at(j).prevRank = i+1;
            }
        }
    }
}

// Sets all the stats besides previous rank to 0 for each team
void resetSeason(vector<team>* teams){
    for(int i = 0; i < 32; i++){
        teams->at(i).wins = 0;
        teams->at(i).losses = 0;
        teams->at(i).ties = 0;
    }
}

int main(){
    vector<string> teamNames = {"Alabama","Texas A&M","Auburn","LSU","Georgia","South Carolina","Tennessee","Florida","Vanderbilt","Kentucky",
                                "Ole Miss","Arkansas","USC","Utah","UCLA","Oregon","Baylor","Texas","Oklahoma","TCU","Texas Tech","Kansas State",
                                "Kansas","Oklahoma State","Ohio State","Illinois","Michigan","Iowa","Florida State","Clemson","Wake Forest","Louisville"};
    vector<int> difficulty = {10,7,8,9,10,7,9,6,5,6,7,8,9,7,6,8,5,7,7,9,6,8,7,5,10,5,9,4,6,7,3,3};
    vector<team> teams;
    vector<team> ranking;
    // populates vectors with dummy data
    for(int i = 0; i < 32; i++){
        teams.push_back(team(teamNames[i],0,0,0,difficulty[i],0));
        ranking.push_back(team("",0,0,0,0,0));
    }
    int weekNum = 0;
    populateNums(&teams,&weekNum);

    // sets up values for user input
    int input = 0;
    string in = "";
    cout << "options:\n0 - Enter info for a new week\n1 - View the current rankings\n5 - Reset the season\n2 - Exit\n";
    cin >> in;
    input = stoi(in);

    while(input != 2){
        if(input == 0){
            weekNum++;
            getInput(&teams, weekNum);
            updateWins(teams, weekNum);
            updatePrevRank(&ranking, &teams);
            updateWins(teams, weekNum);
        }else if(input == 1){
            getRankings(&teams, &ranking, weekNum);
            outputRankings(ranking, weekNum);
        }else if(input == 5){
            weekNum = 0;
            updatePrevRank(&ranking, &teams);
            resetSeason(&teams);
            updateWins(teams, weekNum);
        }
        cout << "options:\n0 - Enter info for a new week\n1 - View the current rankings\n5 - Reset the season\n2 - Exit\n";
        cin >> in;
        input = stoi(in);
    }
    cout << "Exiting!" << endl;
    
}