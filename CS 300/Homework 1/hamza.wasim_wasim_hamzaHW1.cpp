//
//  main.cpp
//  CS300 HW1
//
//  Created by Hamza Wasim on 24/10/2023.
//



#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;


template<typename T>
class Stack {
    struct Node {
        pair<int, int> data;
        Node* next;
    };
    Node* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack() {
        while(topNode) {
            Node* oldTop = topNode;
            topNode = topNode->next;
            delete oldTop;
        }
    }

    bool empty() const {
        return topNode == nullptr;
    }

    void push(const pair<int, int>& val) {
        Node* newNode = new Node{val, topNode};
        topNode = newNode;
    }

    pair<int, int> top() const {
        if (topNode) return topNode->data;
        throw runtime_error("Stack is empty.");
    }

    void pop() {
        if (topNode) {
            Node* oldTop = topNode;
            topNode = topNode->next;
            delete oldTop;
        } else {
            throw runtime_error("Stack is empty.");
        }
    }
};



class Maze {
private:
    int M, N;
    struct Cell {
        bool left = true;
        
    
        bool right = true;
        
        bool up = true;
        
        bool down = true;
        bool visited = false;
        
    };
    
    vector<vector<Cell>> maze;

    vector<pair<int, int>> getUnvisitedNeighbours(int i, int j) { //For using in generate function
        vector<pair<int, int>> neighbours;
        
        
        if(i > 0 && !maze[i-1][j].visited){
            neighbours.emplace_back(i-1, j);}
        
        if(i < M-1 && !maze[i+1][j].visited) {
            neighbours.emplace_back(i+1, j);}
        
        if(j > 0 && !maze[i][j-1].visited) {
            neighbours.emplace_back(i, j-1);}
        
        if(j < N-1 && !maze[i][j+1].visited) {
            neighbours.emplace_back(i, j+1);}
        
        
        return neighbours;
    }
    
    vector<pair<int, int>> getAccessibleNeighbours(int i, int j) { //For using solution/path function
        vector<pair<int, int>> neighbours;
        if(i > 0 && !maze[i][j].left) neighbours.emplace_back(i-1, j);  // Left cell
        if(i < M-1 && !maze[i][j].right) neighbours.emplace_back(i+1, j);  // Right cell
        if(j > 0 && !maze[i][j].down) neighbours.emplace_back(i, j-1);  // Down cell
        if(j < N-1 && !maze[i][j].up) neighbours.emplace_back(i, j+1);  // Up cell
        return neighbours;
    }

public:
    Maze(int m, int n) : M(m), N(n), maze(m, vector<Cell>(n)) {}
    
    
    
   
    

    bool solve(int start_i, int start_j, int exit_i, int exit_j,int ID) { //Solve function for finding the path
//        Stack s;
        Stack<pair<int, int>> s;
        vector<vector<bool>> visited(M, vector<bool>(N, false));

        s.push({start_i, start_j});
        visited[start_i][start_j] = true;
        
//        cout<<1;
        
        vector<pair<int,int>> path;


        while(!s.empty()) {
            auto [i, j] = s.top();
            s.pop();
//cout<<check 1
            
            
            
            
     
            if(i == exit_i && j == exit_j) {  // Exit found here.
                
                
                vector<pair<int, int>> finalPath;

                
                string gi = "maze_" + to_string(ID) + "_path_" + to_string(start_i) + "_" + to_string(start_j) + "_" + to_string(exit_i) + "_" + to_string(exit_j) + ".txt";


                ofstream outputFile(gi);
                if (!outputFile) {
                    cerr << "Error opening file for writing.\n";
                    return false;
                }
//cout<<check2
//                cout << "Path found!\n";
                
                
                for (auto it = path.rbegin(); it != path.rend(); ++it) {
                     finalPath.push_back(*it);
                 }
                finalPath.push_back(make_pair(start_i, start_j));

                                for(int h = finalPath.size() -1 ;h>=0;--h){
                
                                    outputFile<<finalPath[h].first<<" "<<finalPath[h].second<<endl;
                                }
                
//                for(auto it = path.rbegin(); it != path.rend(); ++it) {
//                    outputFile << it->first << " " << it->second << endl;
//                }
                
                
                
                
                outputFile.close();
                return true;
            }
            
            
            
            
//            cout<<check3

            auto neighbours = getAccessibleNeighbours(i, j);
            for(auto& neighbour : neighbours) {
                auto [ni, nj] = neighbour;
                //        cout<<2;

                if(!visited[ni][nj]) {
                    visited[ni][nj] = true;
                    //        cout<<3;

                    s.push({ni, nj});
                    path.push_back({ni, nj});  // Add to path
                }
            }
        }//cout<<check4

        cout << "No path found!\n";
        return false;
    }
    //cout<<check5

    void generate(int start_i = 0, int start_j = 0) { //Functioning for genrating the Maze
        srand(static_cast<unsigned>(time(nullptr)));  // Seed for randomness
//        Stack s;
        Stack<pair<int, int>> s;
        s.push({start_i, start_j});
        maze[start_i][start_j].visited = true;
        //cout<<check6

        while(!s.empty()) {
            auto [i, j] = s.top();
            auto neighbours = getUnvisitedNeighbours(i, j);

            if(!neighbours.empty()) {
                int randomIndex = rand() % neighbours.size();
                auto [ni, nj] = neighbours[randomIndex];
                //cout<<check7

                // Remove walls between current cell and chosen neighbour
                if(ni == i+1) {
                    maze[i][j].right = false;
                    maze[ni][nj].left = false;
                } else if(ni == i-1) {
                    maze[i][j].left = false;
                    maze[ni][nj].right = false;
                } else if(nj == j+1) {
                    maze[i][j].up = false;
                    maze[ni][nj].down = false;
                } else if(nj == j-1) {
                    maze[i][j].down = false;
                    maze[ni][nj].up = false;
                }
                //cout<<check8

                maze[ni][nj].visited = true;
                s.push({ni, nj});
            } else {
                s.pop();
            }
        }
    }
    //cout<<check9


    void saveMazeToFile(const string& filename) {  //Function for saving the file with the maze
        ofstream outputFile(filename);
        if (!outputFile) {
            cerr << "Failed to open file for writing." << endl;
            return;
        }
        outputFile << M << " " << N << endl;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                outputFile << "x=" << i << " y=" << j
                           << " l=" << maze[i][j].left
                           << " r=" << maze[i][j].right
                           << " u=" << maze[i][j].up
                           << " d=" << maze[i][j].down << endl;
            }
        }
        //cout<<check10

        outputFile.close();
//        cout << "Maze saved to " << filename << endl;
    }
};

int main() {
    
//    Maze m(5, 5);
//    m.generate();
//    m.saveMazeToFile("mazeoutput.txt");
//    
//    int start_i = 0, start_j = 0, exit_i = 4, exit_j = 4;
//    m.solve(start_i, start_j, exit_i, exit_j);
    
    
    
    
    
            int K, M, N;
            cout << "Enter the number of mazes: ";
            cin >> K;
            cout << "Enter the number of rows and columns (M and N): ";
            cin >> M >> N;
    
            vector<Maze> mazes;

            for (int i = 0; i < K; ++i) {
                Maze mi(M, N);
                mi.generate();
                mi.saveMazeToFile("maze_" + to_string(i + 1) + ".txt");
                mazes.push_back(mi);
            }
        
        cout<<"All mazes are generated."<<endl;
        cout<<"Enter a maze ID between 1 to 5 inclusive to find a path: ";
        int P;
        cin>>P;
        int start_x , start_y , exit_x , exit_y ;
        cout <<endl<< "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
        cin >> start_x >> start_y;
        cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
        cin >> exit_x >> exit_y;
    
    
    
    mazes[P - 1].solve(start_x, start_y, exit_x, exit_y,P);
    
    
//    mP.solve(start_i, start_j, exit_i, exit_j);
    
    
    
    
    
    
    
    return 0;
}



