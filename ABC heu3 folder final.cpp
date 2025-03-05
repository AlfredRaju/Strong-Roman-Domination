#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <bits/stdc++.h>
#include <dirent.h>
using namespace std;

// Constants
const int NUM_EMPL_BEES = 100;
const int NUM_ONLOOKER_BEES = 100;
const int NUM_FOOD_SOURCES = 1000;
const int MAX_CYCLES =10000;
const double LIMIT =0;
// Objective function to be optimized (example)
double objective_function(const std::vector<int>& solution) {
    double result = 0.0;
    for (int x : solution) {
        result += x;  // Linear function
    }
    return result;
}

// Structure to represent a food source
struct FoodSource {
    std::vector<int> solution;
    double fitness;
    double trial;
};

// Function to generate a random integer between min and max
int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}




vector<int> labelGraph(const std::vector<std::vector<int>>& G) {              //rdf to srdf
    int n = G.size(),i,k=-1,j,p=0;
    set<int> random;
    vector<int> deg;
    vector<vector<int>> labels;
    vector<int> degrees;
    vector<int> label2(n,k);

        int a=0;
    for(i=0;i<n;i++){
        random.insert(i);
    }
                    random_device rd;  // Seed for the random engine
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<int> int_dis(0, 1); // Distribution for integers
        
        for(int i=0;i<n;i++){                   //degrees
            //cout<<G[i].size()<<endl;
            degrees.push_back(G[i].size());
        }
        
        sort(degrees.begin(), degrees.end(), greater<int>());
        
        // for(int i=0;i<n;i++){
        //     cout<<degrees[i];
        // }cout<<endl;

    
    vector<int> label(n,k);     //vector with size n with initial value -1
    
    while(random.size()!=0){                        //heuristic 1
        
    //         random_device rd;  // Seed for the random engine
    // mt19937 gen(rd()); // Mersenne Twister engine
     uniform_int_distribution<int> int_dist(0, n-1); // Distribution for integers

    // Generate a random integer
    int x = int_dist(gen);
        //int x=rand()%n;
        //cout<<x<<" ";
        if(label[x]==-1 && random.size()!=1){
            //cout<<x;
            label[x]=2;
            for(auto j:G[x]){
                if(label[j]==-1){
                label[j]=0;
                random.erase(j);
                //cout<<j;
                }
            }random.erase(x);
        }//cout<<endl;
        
        else if(label[x]==-1 && random.size()==1){
            label[x]=1;
            random.erase(x);
        }
    }

    return label;
}




// Heuristic function to label graph with values 0, 1, 2, 3
std::vector<int> labelGraph_4(const std::vector<std::vector<int>>& originalGraph) {                 //heuristic3
    srand(time(0));  // Seed the random number generator

    std::vector<std::vector<int>> G = originalGraph;  // Make a local copy of the graph
    int n = G.size();
    // std::vector<int> S(n, -1);  // Initialize with -1 to indicate unassigned labels
    // std::vector<int> degrees(n);  // Store degrees of vertices
    std::vector<int> V(n);  // Store vertex indices

    int i,k=-1,j,p=0;
    set<int> random;
    vector<int> deg;
    vector<vector<int>> labels;
    vector<int> degrees;
    
        
        vector<int> lab2;
    vector<int> lab0;
        int a=0;

    for(i=0;i<n;i++){
        random.insert(i);
    }
    
    random_device rd;  // Seed for the random engine
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<int> int_dis(0, 1); // Distribution for integers
        
        for(int i=0;i<n;i++){                   //degrees
            //cout<<G[i].size()<<endl;
            degrees.push_back(G[i].size());
        }

    vector<int> label(n,k);     //vector with size n with initial value -1
    while(random.size()!=0){                        //heuristic 1
 
     uniform_int_distribution<int> int_dist(0, n-1); // Distribution for integers

    // Generate a random integer
    int x = int_dist(gen);
        //int x=rand()%n;
        //cout<<x<<" ";
        if(label[x]==-1 && random.size()!=1 && degrees[x]>1){
            int count=0;
            //cout<<x;
            // label[x]=2;
            // lab2.push_back(x);
            for(auto j:G[x]){
                if(label[j]==-1 || label[j]==0){
                label[j]=0;
                count++;
                // lab0.push_back(j);
                random.erase(j);
                //cout<<j;
                }
            }
            label[x] = 1 + ceil(count/2.0);
            random.erase(x);
        }//cout<<endl;
        
        else if(label[x]==-1 && random.size()!=1 && degrees[x]<2){
            label[x]=1;
            random.erase(x);
        }
        
        else if(label[x]==-1 && random.size()==1){
            label[x]=1;
            random.erase(x);
        }
        
    }
       
    return label;
}



// Feasibility function to correct the solution
std::vector<int> feas(const std::vector<int>& solution, const std::vector<std::vector<int>>& G) {
    std::vector<int> inpop = solution;
    
    // for(int i=0;i<insize;i++){
        for(int j=0;j<inpop.size();j++){
            if(inpop[j]>=2){
                double zeros = 0,new_label=0;
                for(auto u:G[j]){
                    // if(inpop[u]==0){                     // extra condition for common edges
                    //     int count=0;
                    //     for(auto it: G[u]){
                    //         if(inpop[it]>1){
                    //             count++;
                    //         }
                    //     }
                    //     if(count>1){
                    //         inpop[u]=1;
                    //     }
                    // }
                    if(inpop[u]==0){
                    zeros++;
                    }
                }
                new_label = 1 + ceil(zeros/2.0);
                if(new_label>2){
                inpop[j] = new_label;
                }
            }
        }
    
    return inpop;
}


std::vector<int> feasibility(const std::vector<int>& solution, const std::vector<std::vector<int>>& G) {
    std::vector<int> X_new = solution;
                        
        for(int j=0;j<X_new.size();j++){
            if(X_new[j]==0){
                int sum=0;
                bool flag= false;
                for(auto u:G[j]){
                    //cout<<"u is"<<u;
                    if(X_new[u] >1 ){
                        flag=true;
                        break;
                    }
                }
            if(flag==false){
                X_new[j]=1;
            }//cout<<"sum"<<sum<<endl;
            }
        }
    
    return X_new;
}



std::vector<FoodSource> initialize_food_sources(const std::vector<std::vector<int>>& adj_list) {
    std::vector<FoodSource> food_sources(NUM_FOOD_SOURCES);

    for (int i = 0; i < NUM_FOOD_SOURCES; ++i) {
        food_sources[i].solution = labelGraph_4(adj_list);  // Initialize using heuristic function
        food_sources[i].fitness = objective_function(food_sources[i].solution);
        food_sources[i].trial = 0;
    }
    return food_sources;
}

// Employed bee phase
void employed_bee_phase(std::vector<FoodSource>& food_sources, const std::vector<std::vector<int>>& adj_list) {
    int dim = adj_list.size();
    for (int i = 0; i < NUM_EMPL_BEES; ++i) {
        int food_index = i % NUM_FOOD_SOURCES;
        int k = random_int(0, NUM_FOOD_SOURCES - 1);
        while (k == food_index) {
            k = random_int(0, NUM_FOOD_SOURCES - 1);
        }
        int j = random_int(0, dim - 1);
        double phi = (double)random_int(0, RAND_MAX) / RAND_MAX * 2.0 - 1.0; // random double between -1 and 1
        std::vector<int> new_solution = food_sources[food_index].solution;
        int new_value = new_solution[j] + static_cast<int>(phi * (food_sources[food_index].solution[j] - food_sources[k].solution[j]));
        // new_solution[j] = std::max(0, std::min(3, new_value)); // Ensure the value is between 0 and 3
        if(new_solution[j]<0 ){
                new_solution[j]=0;
            }
        
        // else if(new_solution[j]>2){
        //     new_solution[j]=2;
        // }

        // Apply feasibility function
        new_solution = feasibility(new_solution, adj_list);
        new_solution = feas(new_solution, adj_list);
        
        double new_fitness = objective_function(new_solution);
        if (new_fitness < food_sources[food_index].fitness) {
            food_sources[food_index].solution = new_solution;
            food_sources[food_index].fitness = new_fitness;
            food_sources[food_index].trial = 0;
        } else {
            ++food_sources[food_index].trial;
        }
    }
}

// Calculate probabilities based on fitness values
void calculate_probabilities(const std::vector<FoodSource>& food_sources, std::vector<double>& probabilities) {
    double sum_fitness = 0.0;
    for (const auto& source : food_sources) {
        sum_fitness += 1.0 / (1.0 + source.fitness);
    }
    for (int i = 0; i < NUM_FOOD_SOURCES; ++i) {
        probabilities[i] = (1.0 / (1.0 + food_sources[i].fitness)) / sum_fitness;
    }
}

// Onlooker bee phase
void onlooker_bee_phase(std::vector<FoodSource>& food_sources, const std::vector<std::vector<int>>& adj_list, const std::vector<double>& probabilities) {
    int dim = adj_list.size();
    int i = 0;
    int t = 0;
    while (t < NUM_ONLOOKER_BEES) {
        int i = random_int(0, NUM_FOOD_SOURCES - 1);
        if ((double)random_int(0, RAND_MAX) / RAND_MAX < probabilities[i]) {
            ++t;
            int k = random_int(0, NUM_FOOD_SOURCES - 1);
            while (k == i) {
                k = random_int(0, NUM_FOOD_SOURCES - 1);
            }
            int j = random_int(0, dim - 1);
            double phi = (double)random_int(0, RAND_MAX) / RAND_MAX * 2.0 - 1.0; // random double between -1 and 1
            std::vector<int> new_solution = food_sources[i].solution;
            int new_value = new_solution[j] + static_cast<int>(phi * (food_sources[i].solution[j] - food_sources[k].solution[j]));
            new_solution[j]=new_value;
            if(new_solution[j]<0){
                new_solution[j]=0;
            }
            
        //     else if(new_solution[j]>2){
        //     new_solution[j]=2;
        // }
            // new_solution[j] = std::max(0, std::min(3, new_value)); // Ensure the value is between 0 and 3

            // Apply feasibility function
            new_solution = feasibility(new_solution, adj_list);
            new_solution = feas(new_solution, adj_list);

            double new_fitness = objective_function(new_solution);
            if (new_fitness < food_sources[i].fitness) {
                food_sources[i].solution = new_solution;
                food_sources[i].fitness = new_fitness;
                food_sources[i].trial = 0;
            } else {
                ++food_sources[i].trial;
            }
        }
        // i = (i + 1) % NUM_FOOD_SOURCES;
    }
}

// Scout bee phase
void scout_bee_phase(std::vector<FoodSource>& food_sources, const std::vector<std::vector<int>>& adj_list) {
    for (int i = 0; i < NUM_FOOD_SOURCES; ++i) {
        if (food_sources[i].trial > LIMIT) { // Change condition to trial > LIMIT
            food_sources[i].solution = labelGraph_4(adj_list);  // Reinitialize using heuristic function
            food_sources[i].solution = feasibility(food_sources[i].solution, adj_list);  // Apply feasibility function
            food_sources[i].solution = feas(food_sources[i].solution, adj_list);
            food_sources[i].fitness = objective_function(food_sources[i].solution);
            food_sources[i].trial = 0;
        }
    }
}

// Function to print food sources (for debugging)
void print_food_sources(const std::vector<FoodSource>& food_sources) {
    for (int i = 0; i < NUM_FOOD_SOURCES; ++i) {
        std::cout << "Food Source " << i + 1 << ": [";
        for (int x : food_sources[i].solution) {
            std::cout << x << " ";
        }
        std::cout << "] Fitness: " << food_sources[i].fitness << " Trial: " << food_sources[i].trial << "\n";
    }
    std::cout << "\n";
}

// int main() {
//     // User input 
    
//         int num_vertices, num_edges;
//     std::cout << "Enter number of vertices: ";
//     std::cin >> num_vertices;
//     // std::cout << "Enter number of edges: ";
//     std::cin >> num_edges;

//     // Initialize adjacency list
//     std::vector<std::vector<int>> adj_list(num_vertices);
//     // std::cout << "Enter edges (pairs of vertices 0-indexed):\n";
//     for (int i = 0; i < num_edges; ++i) {
//         int u, v;
//         std::cin >> u >> v;
//         u--;
//         v--;
//         adj_list[u].push_back(v);
//         adj_list[v].push_back(u);
//     }

//     // Initialize population using heuristic function
//     std::vector<FoodSource> food_sources = initialize_food_sources(adj_list);

//     // Initialize probabilities vector
//     std::vector<double> probabilities(NUM_FOOD_SOURCES);

 

//     // Find the best solution
//     FoodSource best_source = *std::min_element(food_sources.begin(), food_sources.end(), [](const FoodSource& a, const FoodSource& b) {
//         return a.fitness < b.fitness;
//     });

//     // Output the best solution found
//     std::cout << "Best solution found: ";
//     for (int x : best_source.solution) {
//         std::cout << x << " ";
//     }
//     std::cout << "\nFitness: " << best_source.fitness << std::endl;
//        // Main loop for ABC algorithm
//     for (int cycle = 0; cycle < MAX_CYCLES; ++cycle) {
//         std::cout << "Cycle " << cycle + 1 << "\n";

//         // Employed bee phase
//         employed_bee_phase(food_sources, adj_list);
//         std::cout << "After Employed Bee Phase:\n";
//         print_food_sources(food_sources);

//         // Calculate probabilities
//         calculate_probabilities(food_sources, probabilities);

//         // Onlooker bee phase
//         onlooker_bee_phase(food_sources, adj_list, probabilities);
//         std::cout << "After Onlooker Bee Phase:\n";
//         print_food_sources(food_sources);

//         // Scout bee phase
//         scout_bee_phase(food_sources, adj_list);
//         std::cout << "After Scout Bee Phase:\n";
//         print_food_sources(food_sources);

//         // std::cout << "\n";
//     }
//   // Output the best solution found
//     std::cout << "Best solution found: ";
//     for (int x : best_source.solution) {
//         std::cout << x << " ";
//     }
//     std::cout << "\nFitness: " << best_source.fitness << std::endl;
//     return 0;
// }



#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

// Include the necessary function declarations and structures here
// ...

int main() {
    // Set the folder path
    std::string folder_path = "C:\\Users\\alfre\\OneDrive\\Desktop\\phd\\Graphs\\New folder2";

    // Initialize vector to hold adjacency lists for each graph
    std::vector<std::vector<std::vector<int>>> graphs;

    // Read graphs from files in the folder
    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
        std::ifstream file(entry.path());
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << entry.path() << std::endl;
            continue;
        }

        int num_vertices, num_edges;
        file >> num_vertices >> num_edges;

        std::vector<std::vector<int>> adj_list(num_vertices);

        for (int i = 0; i < num_edges; ++i) {
            int u, v;
            file >> u >> v;
            u--;  // Adjust for 0-indexed vertices
            v--;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }

        graphs.push_back(adj_list);
    }

    // Process each graph
    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
        std::ifstream file(entry.path());
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << entry.path() << std::endl;
            continue;
        }

        int num_vertices, num_edges;
        file >> num_vertices >> num_edges;

        std::vector<std::vector<int>> adj_list(num_vertices);

        for (int i = 0; i < num_edges; ++i) {
            int u, v;
            file >> u >> v;
            u--;  // Adjust for 0-indexed vertices
            v--;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }

        // Initialize population using heuristic function
        std::vector<FoodSource> food_sources = initialize_food_sources(adj_list);

        // Initialize probabilities vector
        std::vector<double> probabilities(NUM_FOOD_SOURCES);

        // Main loop for ABC algorithm
        for (int cycle = 0; cycle < MAX_CYCLES; ++cycle) {
            // Employed bee phase
            employed_bee_phase(food_sources, adj_list);

            // Calculate probabilities
            calculate_probabilities(food_sources, probabilities);

            // Onlooker bee phase
            onlooker_bee_phase(food_sources, adj_list, probabilities);

            // Scout bee phase
            scout_bee_phase(food_sources, adj_list);
        }


                   // Find the best solution   for heuristic3
    FoodSource best_source = *std::min_element(food_sources.begin(), food_sources.end(), [](const FoodSource& a, const FoodSource& b) {
        return a.fitness < b.fitness;
    });

        // Process all solutions through the feas function, update them and compute new fitness
        double min_fitness = std::numeric_limits<double>::infinity();               //for rdf to srdf
        std::vector<int> best_solution;
        for (auto& source : food_sources) {
            source.solution = feas(source.solution, adj_list);
            source.fitness = objective_function(source.solution);
            if (source.fitness < min_fitness) {
                min_fitness = source.fitness;
                best_solution = source.solution;
            }
        }

        // Output the modified solutions stored in food sources
        // std::cout << "\nModified solutions stored in food sources for file: " << entry.path().filename() << "\n";
        // for (const auto& source : food_sources) {
        //     // std::cout << "[";
        //     for (int x : source.solution) {
        //         // std::cout << x << " ";
        //     }
        //     // std::cout << "] Fitness: " << source.fitness << "\n";
        // }

        //Output the best solution found
        // std::cout << "Best solution found in file: " << entry.path().filename() << "\n";
        // for (int x : best_solution) {  // best_source.solution for heuristic3 && best_solution for rdf to srdf
        //     std::cout << x << " ";
        // }
        std::cout  << entry.path().filename() << " " << best_source.fitness << std::endl;  // min_fitness for rdf to srdf && best_source.fitness for heuristic3
    }

    return 0;
}
