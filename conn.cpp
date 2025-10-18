#include <iostream>
#include <vector>
#include <map>
#include <tuple>

constexpr int GOAL = 4;

std::string who_is_winner(std::vector<std::string> moves);
bool is_there_a_winner(const char& player, std::pair<char, int>& counter);
char find_vertical_winner(std::map<char, std::vector<char>>& gstate);
char find_horizontal_winner(std::map<char, std::vector<char>>& gstate);
char find_main_diagonal_winner(std::map<char, std::vector<char>>& gstate);
char find_secondary_diagonal_winner(std::map<char, std::vector<char>>& gstate);

int main() {
    std::vector<std::string> moves_1 = {
        "A_Yellow", "B_Red", "B_Yellow", "C_Red",
        "G_Yellow", "C_Red", "C_Yellow", "D_Red",
        "G_Yellow", "D_Red", "G_Yellow", "D_Red",
        "F_Yellow", "E_Red", "D_Yellow"
    };

    std::vector<std::string> moves_2 = {
        "F_Yellow", "G_Red",
        "D_Yellow", "C_Red",
        "A_Yellow", "A_Red",
        "E_Yellow", "D_Red",
        "D_Yellow", "F_Red",
        "B_Yellow", "E_Red",
        "C_Yellow", "D_Red",
        "F_Yellow", "D_Red",
        "D_Yellow", "F_Red",
        "G_Yellow", "C_Red",
        "F_Yellow", "E_Red",
        "A_Yellow", "A_Red",
        "C_Yellow", "B_Red",
        "E_Yellow", "C_Red",
        "E_Yellow", "G_Red",
        "A_Yellow", "A_Red",
        "G_Yellow", "C_Red",
        "B_Yellow", "E_Red",
        "F_Yellow", "G_Red",
        "G_Yellow", "B_Red",
        "B_Yellow", "B_Red"
    };

    std::cout << "The winner is: " << who_is_winner(moves_1) << std::endl;
    std::cout << "The winner is: " << who_is_winner(moves_2) << std::endl;
    return 0;
}

std::string who_is_winner(std::vector<std::string> moves)
{
    std::map<char, std::vector<char>> gstate;
    for(const auto& move: moves)
        gstate[move[0]].push_back(move[2]);

    char win = 0;
    if(!win) win = find_vertical_winner(gstate);
    if(!win) win = find_horizontal_winner(gstate);
    if(!win) win = find_secondary_diagonal_winner(gstate);
    if(!win) win = find_main_diagonal_winner(gstate);

    return (win == 'Y') ? "Yellow" : (win == 'R') ? "Red" : "Not Found";
}

bool is_there_a_winner(const char& player, std::pair<char, int>& counter) {
    if(counter.first == player) {
        counter.second++;
        if(counter.second == GOAL) return true;
    } else
        counter = { player, 1 };
    return false;
}

char find_vertical_winner(std::map<char, std::vector<char>>& gstate) {
    for(char k = 'A'; k < 'H'; k++) {
        std::pair<char, int> counter = std::make_pair(0, 0);
        for(const auto& player: gstate[k]) {
            if(is_there_a_winner(player, counter)) return player;
        }
    }
    return 0;
}

char find_horizontal_winner(std::map<char, std::vector<char>>& gstate) {
    for(std::size_t i = 0; i < 6; i++) {
        std::pair<char, int> counter = std::make_pair(0, 0);

        for(char k = 'A'; k < 'H'; k++) {
            if(gstate[k].size() <= i) {
                counter = {0, 0};
                continue;
            }

            char player = gstate[k][i];
            if(is_there_a_winner(player, counter)) return player;
        }
    }
    return 0;
}

char find_main_diagonal_winner(std::map<char, std::vector<char>>& gstate) {
    for(int i = 5; i >= 0; i--) {
        std::pair<char, int> counter = std::make_pair(0, 0);
        int dgn = i - 1;
        for(char k = 'A'; k < 'H'; k++) {
            dgn++;
            if(gstate[k].size() <= static_cast<std::size_t>(dgn)) {
                counter = {0, 0};
                continue;
            }

            char player = gstate[k][dgn];
            if(is_there_a_winner(player, counter)) return player;
        }
    }
    
    for(char j = 'B'; j < 'H'; j++) {
        std::pair<char, int> counter = std::make_pair(0, 0);
        int dgn = -1;
        for(char k = j; k < 'H'; k++) {
            dgn++;
            if(gstate[k].size() <= static_cast<std::size_t>(dgn)) {
                counter = {0, 0};
                continue;
            }

            char player = gstate[k][dgn];
            if(is_there_a_winner(player, counter)) return player;
        }
    }
    return 0;
}

char find_secondary_diagonal_winner(std::map<char, std::vector<char>>& gstate) {
    for(char j = 'A'; j < 'H'; j++) {
        std::pair<char, int> counter = std::make_pair(0, 0);
        int dgn = -1;
        for(char k = j; k >= 'A'; k--) {
            dgn++;
            if(gstate[k].size() <= static_cast<std::size_t>(dgn)) {
                counter = {0, 0};
                continue;
            }

            char player = gstate[k][dgn];
            if(is_there_a_winner(player, counter)) return player;
        }
    }

    for(int i = 1; i < 6; i++) {
        std::pair<char, int> counter = std::make_pair(0, 0);
        int dgn = i - 1;
        for(char k = 'G'; k >= 'A'; k--) {
            dgn++;
            if(gstate[k].size() <= static_cast<std::size_t>(dgn)) {
                counter = {0, 0};
                continue;
            }

            char player = gstate[k][dgn];
            if(is_there_a_winner(player, counter)) return player;
        }
    }

    return 0;
}
