#include <bits/stdc++.h>
#include <dirent.h>
using namespace std;
#include <cstdlib>  // For rand()

using namespace std; // Using the standard namespace


vector<vector<int>> arr = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

// construct a graph from txt file
vector<vector<int>> getGraphFromFile(string path)
{
    string text;
    ifstream fin(path);
    bool weighted;

    int n, e;

    // Ignore headers and comments:
    while (fin.peek() == '%')
        fin.ignore(2048, '\n');

    //fin >> weighted;
    // Number of vertices and edges
    fin >> n >> e;

    vector<set<int>> G(n);

    // Read the data
    int u, v;
    double data;
    for (int l = 0; l < e; l++)
    {
        fin >> u >> v;
        //if (weighted)
            //fin >> data;

        if (u == v)
            continue;

        u--;
        v--;
        G[u].insert(v);
        G[v].insert(u);
    }

    fin.close();

    vector<vector<int>> G_(n);

    for (int i = 0; i < n; i++)
    {
        for (auto u : G[i])
        {
            G_[i].push_back(u);
        }
    }
    return G_;
}

// construct m*n grid graph --> m rows and n columns
vector<vector<int>> constructGridGraph(int m, int n)
{
    vector<vector<int>> G(n * m);
    for (int i = 0; i < n * m; i++)
    {
        // converting indexed vertices to cartesian coordinate form
        int x = i / n;
        int y = i % n;

        // adding neighbour vertices to the adjency list
        for (auto a : arr)
        {
            int x1 = x + a[0];
            int y1 = y + a[1];
            if (x1 >= 0 && x1 < m && y1 >= 0 && y1 < n)
            {
                G[i].push_back(x1 * n + y1);
            }
        }
        sort(G[i].begin(), G[i].end());
    }
    return G;
}

pair<int, int> getBounds(vector<vector<int>> G)
{
    int maxDeg = 0, minDeg = G.size(), n = G.size(), v;
    for (int i = 0; i < n; i++)
    {
        auto u = G[i];
        maxDeg = max(maxDeg, (int)u.size());
        if (minDeg > u.size())
        {
            minDeg = u.size();
            v = i;
        }
        // minDeg = min(minDeg, (int)u.size());
    }
    pair<int, int> bounds;
    bounds.first = ceil((n+1) / (2.0));
    bounds.second = n - floor(maxDeg / 2.0);
    return bounds;
}

bool sortFiles(string x, string y)
{
    int end = x.find_last_of('.');
    string a = x.substr(0, end);

    end = y.find_last_of('.');
    string b = y.substr(0, end);

    int n = min(a.length(), b.length());
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b[i])
            continue;
        if (a[i] == '_')
            return true;
        if (b[i] == '_')
            return false;
        return a[i] < b[i];
    }
    return a.length() < b.length();
}

// vector<vector<int>> getGraph() {
//     int n, e;
//     std:: cout << "Enter size: ";
//     cin >> n >> e;

//     vector<set<int>> G(n);

//     int u, v;
//     for (int l = 0; l < e; l++) {
//         cin >> u >> v;
//         if (u == v) continue;
//         u--;
//         v--;
//         G[u].insert(v);
//         G[v].insert(u);
//     }

//     vector<vector<int>> G_(n);
//     for (int i = 0; i < n; i++) {
//         for (auto u : G[i]) {
//             G_[i].push_back(u);
//         }
//     }

//     return G_;
// }

// returns shuffled array to be labelled
// vector<int> ran(int n){
//     vector<int> random;
//     for(int i=0;i<n;i++){
//         random.push_back(i);
//     }
//     random_shuffle(random.begin(), random.end());
//     return random;
// }

// vector<int> degree(vector<vector<int>> G){
//     vector<int> deg;
//     for(int i=0;i<G.size();i++){
//     deg.push_back(G[i].size());
//     cout<<deg[i];
// }return deg;
// }

vector<vector<int>> heuristic(vector<vector<int>> G, int insize) {
    int n = G.size(),i,k=-1,j,p=0;
    set<int> random;
    vector<int> deg;
    vector<vector<int>> labels;
    vector<int> degrees;
    vector<int> label2(n,k);
    while(p<insize){
        int a=0;
    // vector<vector<int>> dup;
    // for(auto u:G){
    //     dup.push_back(u);       //deep copy
    // }
    
    //while(p<1000){
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
    //int y=int_dis(gen);
    //cout<<y<<" ";
    //int y=1;
            //srand(static_cast<unsigned int>(std::time(nullptr)));
       //if(j<1000){
       if(p<1000){
         //if(y==0){
       //cout<<y<<" ";
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
       }
       
      
      else{
      while(a<n-1){
          if(label[a]==-1){
              label[a]=2;
              for(auto j:G[a]){
                if(label[j]==-1){
                label[j]=0;
                 auto it = remove(degrees.begin(), degrees.end(), j);
                 degrees.erase(it);
                //cout<<j;
                }
            }degrees.erase(degrees.begin() + a);
          }
           
      a++;}

      if(a==n-1 && label[a]==-1)
      {
        label[a]=1;
        //degrees.erase(degrees.begin() + a);
      }
      }
    
    // for(auto u:label){
    //     cout<<u;
    // }cout<<endl;
    labels.push_back(label);
    p++;
    }
    return labels;
}


vector<vector<int>> heuristic3(vector<vector<int>> G, int insize) {
    int n = G.size(),i,k=-1,j,p=0;
    set<int> random;
    vector<int> deg;
    vector<vector<int>> labels;
    vector<int> degrees;
    
    
    while(p<insize){
        
        vector<int> lab2;
    vector<int> lab0;
        int a=0;
    // vector<vector<int>> dup;
    // for(auto u:G){
    //     dup.push_back(u);       //deep copy
    // }
    
    //while(p<1000){
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
    //int y=int_dis(gen);
    //cout<<y<<" ";
    //int y=1;
            //srand(static_cast<unsigned int>(std::time(nullptr)));
       //if(j<1000){
       if(p<1000){
         //if(y==0){
       //cout<<y<<" ";
    while(random.size()!=0){                        //heuristic 1
        
    //         random_device rd;  // Seed for the random engine
    // mt19937 gen(rd()); // Mersenne Twister engine
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
       }
       
       //if(p > 699){                       //This is the only condition different from H1

    //} 
    
    // for(auto u:label){
    //     cout<<u;
    // }cout<<endl;
    labels.push_back(label);
    p++;
    }
    
    // for(int i=0;i<insize;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<labels[i][j]<<" ";
    //     }cout<<endl;
    // }
    return labels;
}



vector<int> Sum(vector<vector<int>> inpop, int insize){       //fscore
    vector<int> sums;
    for(int i=0;i<insize;i++){
        int sum=0;
    for(auto u:inpop[i]){
        sum +=u;
    }
    sums.push_back(sum);}
    
    return sums;
}

int minm(vector<int> v){                    //min and max pos
    auto min=min_element(v.begin(),v.end());
    // auto max=max_element(v.begin(),v.end());
    int minpos=distance(v.begin(), min);
    // cout<< "min"<< minpos<<endl;
    // int maxpos=distance(v.begin(),max);
    //cout<<endl<<*min<<pos;
    // vector<int> pos;
    // pos.push_back(minpos);
    // pos.push_back(maxpos);
    return minpos;
}

vector<vector<int>> feasibility(vector<vector<int>> X_new,int insize,vector<vector<int>> G){
    for(int i=0;i<insize;i++){
                        
        for(int j=0;j<X_new[i].size();j++){
            if(X_new[i][j]==0){
                int sum=0;
                bool flag= false;
                for(auto u:G[j]){
                    //cout<<"u is"<<u;
                    if(X_new[i][u] >1 ){
                        flag=true;
                        break;
                    }
                }
            if(flag==false){
                X_new[i][j]=1;
            }//cout<<"sum"<<sum<<endl;
            }
        }
    }
return X_new;
    
}


vector<vector<int>> updt(vector<vector<int>> X_old, vector<vector<int>> X_new, vector<int> usum1, vector<int> usum2,int insize)
{
    int i=0;
    while(i<insize){
        if(usum1[i]<usum2[i]){
            for(int j=0;j<X_old[i].size();j++){             //can take usum1.size also bcoz of number of vertices
                X_new[i][j]=X_old[i][j];
            }
        }
   i++; }
   return X_new; 
}


vector<vector<int>> feas(vector<vector<int>> inpop, int insize, vector<vector<int>> G){
    for(int i=0;i<insize;i++){
        for(int j=0;j<inpop[i].size();j++){
            if(inpop[i][j]>=2){
                double zeros = 0,new_label=0;
                for(auto u:G[j]){
                    // if(inpop[i][u]==0){                     // extra condition for common edges
                    //     int count=0;
                    //     for(auto it: G[u]){
                    //         if(inpop[i][it]>1){
                    //             count++;
                    //         }
                    //     }
                    //     if(count>1){
                    //         inpop[i][u]=1;
                    //     }
                    // }
                    if(inpop[i][u]==0){
                    zeros++;
                    }
                }
                new_label = 1 + ceil(zeros/2.0);
                if(new_label>2){
                inpop[i][j] = new_label;
                }
            }
        }
    // for(auto u:inpop[i]){
    //     cout<<u;
    //}cout<<endl;
    } 
    
    return inpop;
}



vector<vector<int>> mutation(vector<vector<int>> inpop,int insize, vector<vector<int>> G,int best)
{
    random_device rd;  // Seed for the random engine
    mt19937 gen(rd());
    
    int choice=1, r=0.1;
    int v,w,x,y,z,pop=0;
    int size=inpop[1].size();
    // vector<vector<int>> mutinpop;
    vector<vector<int>> mutinpop(insize, vector<int>(size));        //declare the size
    
     while(pop<insize){
        vector<int> cross1;
        vector<int> cross2;
        vector<int> cross3;
        vector<vector<int>> dumcross;
        vector<int> sum1;
        // vector<vector<int>> mutinpop;       //inpop after mutation
        
    // for(int i=0;i<1;i++){
    uniform_int_distribution<int> int_dis(0,insize-1 );
     v = int_dis(gen);
     w = int_dis(gen);
     x = int_dis(gen);
     y = int_dis(gen);
     z = int_dis(gen);
     
    // }
        //cout<<x<<"  "<<y<<endl;
    //     for(int j=0;j<inpop[x].size();j++){
            
        
        for(int i=0;i<inpop[0].size();i++){
            int p;
            if(choice==1){
                p=inpop[x][i] + r*(inpop[y][i]-inpop[z][i]);
            }
            if(choice==2){
                p=inpop[best][i] + r*(inpop[x][i] - inpop[y][i]);
            }
            if(choice==3){
                p=inpop[pop][i] + r*(inpop[best][i] - inpop[pop][i]) + r*(inpop[x][i] - inpop[y][i]);
            }
            if(choice==4){
                p=inpop[best][i] + r*(inpop[x][i] - inpop[y][i]) + r*(inpop[z][i] - inpop[w][i]); 
            }
            if(choice==5){
                p=inpop[x][i] + r*(inpop[y][i] - inpop[z][i]) + r*(inpop[w][i] - inpop[v][i]);
            }
            
            // cout<<"p is"<<p<<endl;
            if(p<0){
                p=0;
            }
            // if(p>2){
            //     p=2;
            // }
            mutinpop[pop][i] = p; 
        }
        
        
        // sum1=Sum(mutinpop,1);
        
        // for(int i=0;i<sum1.size();i++){
        //     cout<<sum1[i]<<" ";
        // }
        
        
        // for(int i=0;i<mutinpop[0].size();i++){
        //     cout<<"mut" << mutinpop[pop][i]<<" ";
        // }cout<<endl;
        

    pop++;
         
     }
     
    //       for(int j=0;j<mutinpop.size();j++){
    //           for(int i=0;i<mutinpop[0].size();i++){
    //         cout<< mutinpop[j][i]<<" ";
    //     }cout<<endl;
    //  }
     
     
     mutinpop = feasibility(mutinpop,insize,G);
    //  mutinpop = feas(mutinpop,insize,G);
     
    //  cout<<"after"<<endl;
    //  for(int j=0;j<mutinpop.size();j++){
    //           for(int i=0;i<mutinpop[0].size();i++){
    //         cout<< mutinpop[j][i]<<" ";
    //     }cout<<endl;
    //  }
        return mutinpop;
}



vector<vector<int>> selcross(vector<vector<int>> inpop,int insize, vector<vector<int>> G, int itr)
{
    random_device rd;  // Seed for the random engine
    mt19937 gen(rd());
    
    int x,y,a=0;
    int size=inpop[1].size();
    
     while(itr>0){
        vector<int> cross1;
        vector<int> cross2;
        vector<vector<int>> dumcross;
        vector<int> sum1;
        vector<vector<int>> cross;
        
    for(int i=0;i<2;i++){
    uniform_int_distribution<int> int_dis(0,insize-1 );
     x = int_dis(gen);
     y = int_dis(gen);
    }
        //cout<<x<<"  "<<y<<endl;
        for(int j=0;j<inpop[x].size();j++){
            

        cross1.push_back(inpop[x][j]);
        cross2.push_back(inpop[y][j]);
        
    }
    //     cout<<cross1.size()<<endl;
    //   for (auto u : cross1) {
    //     std::cout << u << " ";
    // }
    // std::cout << std::endl;
        
        dumcross.push_back(cross1);
        dumcross.push_back(cross2);
        
        // for(int i=0;i<2;i++){
        //     cout<<"before";
        //     for(int j=0;j<cross1.size();j++){
        //         cout<<dumcross[i][j]<<" ";
        //     }cout<<endl;
        // }
        
        sum1=Sum(dumcross,2);
        
        // for(int i=0;i<sum1.size();i++){
        //     cout<<sum1[i]<<" ";
        // }
    
    uniform_int_distribution<int> int_dis(0,size-1);
    int k= int_dis(gen);
    int l= int_dis(gen);
    int p=0;
    vector<int> dum;
    //cout<<endl<<"k and l"<<k<<" "<<l<<endl;
    
    if(k<l){
        for(int i=0;i<1;i++){
        for(int j=k+1;j<l;j++){
            dum.push_back(dumcross[i][j]);
            dumcross[i][j]=dumcross[i+1][j];
            dumcross[i+1][j]=dum[p];
            p++;
        }
    }
    }
    else if(l<k){
        for(int i=0;i<1;i++){
        for(int j=l+1;j<k;j++){
            dum.push_back(dumcross[i][j]);
            dumcross[i][j]=dumcross[i+1][j];
            dumcross[i+1][j]=dum[p];
            p++;
        }
    }
    }
        
        
        // for(int i=0;i<2;i++){
        //     cout<<"after";
        //     for(int j=0;j<cross1.size();j++){
        //         cout<<dumcross[i][j]<<" ";
        //     }cout<<endl;
        // }
        
        dumcross=feasibility(dumcross,2,G);   //feasibility and mutation
        dumcross=feas(dumcross,2,G);
        vector<int> child_cost=Sum(dumcross,2);
        
        // for(int i=0;i<child_cost.size();i++){
        //     cout<<child_cost[i]<<" ";
        // }cout<<endl;
        
        if(child_cost[0]<sum1[0]){
            for(int i=0;i<inpop[x].size();i++){
                inpop[x][i]=dumcross[0][i];
            }
        }
        
        if(child_cost[1]<sum1[1]){                      //compare and replace
            for(int i=0;i<inpop[x].size();i++){
                inpop[y][i]=dumcross[1][i];
            }
        } 
    itr--;
         
     }
    //  inpop=feas(inpop,insize,G);
        return inpop;
}




vector<vector<int>> sorted(vector<vector<int>> final,int insize,vector<int> sums){
        // Create a vector of pairs (solution, cost)
    vector<pair<vector<int>, int>> solutionCostPairs;
    for (size_t i = 0; i < insize; ++i) {
        solutionCostPairs.emplace_back(final[i], sums[i]);
    }

    // Sort the pairs based on cost (second element of pair)
    sort(solutionCostPairs.begin(), solutionCostPairs.end(),
         [](const pair<vector<int>, int>& a, const pair<vector<int>, int>& b) {
             return a.second < b.second;
         });

    // Extract the sorted solutions
    vector<vector<int>> sortedSolutions;
    for (const auto& pair : solutionCostPairs) {
        sortedSolutions.push_back(pair.first);
    }
    
    
//  for (const auto& pair : solutionCostPairs) {
//         for (int val : pair.first) {
//             cout << val << " ";
//         }
//         cout << "->"<< pair.second << endl; // Print the cost at the end
//     }
    
    return sortedSolutions;
    
}
                        
                        




int RAO(vector<vector<int>> G, int itr) {       //heuristic results
    int n=G.size();
    int insize=1000;
    //vector<vector<int>> inpop(insize,vector<int> (n));        //inpop is initial population
    // for(int i=0;i<insize;i++){
     vector<vector<int>> inpop=heuristic3(G,insize);
     
         vector<int> sums=Sum(inpop,insize);

    int minpos=minm(sums);
    
    // for(int i=0;i<inpop[0].size();i++){              //print the min solution
    //     cout<<inpop[minpos][i]<<" ";
    // }

    auto minss=min_element(sums.begin(), sums.end());
    // cout<<"best is "<< *minss<<endl;
    
     vector<vector<int>> second=mutation(inpop,insize,G,minpos);           //mutation
     
       vector<int> sums2=Sum(second,insize);

    minpos=minm(sums);
    // for(int i=0;i<inpop[0].size();i++){
    //     cout<<second[minpos][i]<<" ";
    // }
    auto mins=min_element(sums2.begin(), sums2.end());
    // cout<<"best is "<< *mins<<endl;
    // //  vector<vector<int>> final= cross(inpop,second,insize,G);       ////crossover for randomly selected solutions
    
    // sums=Sum(final,insize);
    
    // for(int i=0;i<insize;i++){
    //     cout<< sums[i]<< " ";
    // }
    
    // minpos=minm(sums);
    
    // for(int i=0;i<inpop[0].size();i++){
    //     cout<<final[minpos][i]<<" ";
    // }
    
    // for(int i=0;i<insize;i++){
    //     cout<<sums[i]<<endl;
    // }
    
    // auto min=min_element(sums.begin(), sums.end());
    // cout<<"best is "<< *min<<endl<<endl;
    
    
    inpop = sorted(inpop,insize,sums);           /////////sorted
    // cout<<"inpop"<<endl;
    second = sorted(second,insize,sums2);
    // cout<<"second"<<endl;
    auto start = inpop.begin(); // Starting from the second element
    auto end = inpop.begin() + 500;   // Up to but not including the fifth element

    // Copying the specified range
    vector<vector<int>> copy;
    std::copy(start, end, std::back_inserter(copy));
    
    start = second.begin();
    end = second.begin() + 500;
    
    std::copy(start, end, std::back_inserter(copy));

    //Print copied vector of vectors
    // cout<<"val"<<endl;
    // for (const auto& vec : copy) {
    //     for (int val : vec) {
    //         cout <<val << " ";
    //     }
    //     cout << endl;
    // }

    // cout<<"valllll"<<endl;
///////////////////////////////////////////////////////////////////////
    
    copy = selcross(copy,insize,G,50000);
        sums=Sum(copy,insize);
    
    // for(int i=0;i<insize;i++){
    //     cout<< sums[i]<< " ";
    // }
    
    //     for (const auto& vec : finale) {
    //     for (int val : vec) {
    //         cout <<val << " ";
    //     }
    //     cout << endl;
    // }
    
    minpos=minm(sums);
    
    // for(int i=0;i<inpop[0].size();i++){
    //     cout<<copy[minpos][i]<<" ";
    // }
    
    // for(int i=0;i<insize;i++){
    //     cout<<sums[i]<<endl;
    // }
    
    auto mink=min_element(sums.begin(), sums.end());
    // cout<<"best is "<< *mink<<endl;
    int q=*mink;
    
    return q;                                         
}


// int main() {
//     srand(static_cast<unsigned>(std::time(nullptr)));
//     vector<vector<int>> G = getGraph();
//     vector<int> best;
//     float avg;
//     //for(int i=1;i<20;i++){
//         //for(int j=0;j<10;j++){
//     RAO(G, 1000);
//     //best.push_back(sums);   //v gets the fscores of heuristics
//     //}
//     //}
//     //minmax(v);
//     // for(auto u:best){
//     //     avg+=u;
//     // }
//     // auto min=min_element(best.begin(), best.end());
//     // std :: cout<<" avg is:"<<(avg/best.size())<<endl;
//     // std :: cout<<"min is:"<<*min;
    
//     return 0;
    
// }


int main()
{
    DIR *dr;
    struct dirent *en;
    // string inputFolder = "C:\\Users\\Yashpal\\Desktop\\project\\2nd sem\\ACO\\Rayni random graphs";
    // string outputFile = "C:\\Users\\Yashpal\\Desktop\\project\\2nd sem\\ACO\\RayniResults.txt";

    string inputFolder = "C:\\Users\\alfre\\OneDrive\\Desktop\\phd\\Graphs\\New folder1";
    string outputFile = "C:\\Users\\alfre\\OneDrive\\Desktop\\phd\\Graphs\\cestout\\DErdf1.txt";
    dr = opendir(inputFolder.c_str()); // open all directory
    vector<string> files;

    if (dr)
    {
        while ((en = readdir(dr)) != NULL)
        {
            string fileName = en->d_name;
            if (fileName == "." || fileName == "..")
                continue;
            files.push_back(fileName);
        }
        closedir(dr); // close all directory
        sort(files.begin(), files.end(), sortFiles);

        ofstream ofs(outputFile);

        for (auto fileName : files)
        {
            string path = inputFolder + "\\" + fileName;
            vector<vector<int>> G = getGraphFromFile(path);
            pair<int, int> bounds = getBounds(G);

            int v;
            v = RAO(G, 1000);

            int end = fileName.find_last_of('.');
            fileName = fileName.substr(0, end);

            string result = fileName + " " + to_string(bounds.first) + " " + to_string(bounds.second) + " " + to_string(v) + '\n';
            cout << result;
            if (ofs.is_open())
            {
                ofs << result;
            }
            else
            {
                cout << "Did'nt write to result for " << fileName << endl;
            }
        }

        ofs.close();
    }

   
}

                                                
                                                