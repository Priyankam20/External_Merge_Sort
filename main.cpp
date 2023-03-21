
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bitset>
using namespace std;
int seeks =0;
int transfers =0;
vector<vector<double>> runs;
int merged_seeks=0;
int merged_transfers=0;
int sortedrun_seeks=0;
int sortedrun_transfers=0;




void intermediate_sorting(ifstream &input_file, uint64_t max_key_in_sortedrun,size_t no_sorted_runs){
    vector<double> numbers;
    for(auto i=0;i<max_key_in_sortedrun && input_file;i++,++transfers ,++sortedrun_transfers){
        double current_number;
        input_file >> current_number;

        if(input_file){
            numbers.push_back(current_number);

        }
        
    }

    sort(numbers.begin(),numbers.end());
    ofstream output_file("sorted_run_" + to_string(no_sorted_runs));
    seeks++; sortedrun_seeks++;
    for(auto j : numbers){
        output_file << j <<endl; transfers++;sortedrun_transfers++;
    }

runs.push_back(numbers);



}

void merge_operation_case1(vector<vector<double>> &runs, vector<double> &t){
    vector<double> let;
    int num=0;
    for(int i=0;i<runs.size();i++){
        let.push_back(0);
        num =num+runs[i].size();
        }
    for(int i=0;i<num;i++,seeks++,transfers++,merged_seeks++,merged_transfers++){
        double mini = DBL_MAX;
        int k=0;
        for(int j=0;j<let.size();j++){
            if(let[j] < runs[j].size() && runs[j][let[j]]< mini){
                mini = runs[j][let[j]];
                k=j;
            }
        }
            t.push_back(mini);
            seeks++;
            transfers++;
            merged_seeks++;
            merged_transfers++;
            let[k]++;
    }
 
}

int main(int argc, char* argv[]) {
    if(argc < 6){
        cout << "error" <<endl;
        return 0;
    }
    string output_file_path;
    string input_file_path = argv[1];
    int m = stoi(argv[2]);
    int k = stoi(argv[3]);
    int n = stoi(argv[4]);
    int b = stoi(argv[5]);

   uint64_t memory_available = m*b;
   uint64_t total_key_size = k*n;
   uint64_t max_key_in_sortedrun = ceil(memory_available/k);
   

    ifstream input_file(input_file_path);
    size_t no_sorted_runs =0;
    while(input_file){
        intermediate_sorting(input_file, max_key_in_sortedrun,no_sorted_runs);
        ++no_sorted_runs;seeks++;sortedrun_seeks++;
    }



   size_t no_submerged_pass =0;
    while(runs.size()>1){
        vector<vector<double>> vec;
        for(int j=0;j<runs.size();j = j+ max_key_in_sortedrun -1){
                    vector<vector<double>> mergevector;
                      for(int i=j;i< j+ max_key_in_sortedrun-1 && i<runs.size();i++){
            mergevector.push_back(runs[i]);
                    
        }
        vector<double> t;
                merge_operation_case1(mergevector, t);
                vec.push_back(t);
                }
        runs.clear();
        runs = vec;
        vec.clear();
      
        ofstream output_file("merged_pass_"+ to_string(no_submerged_pass));
        for(auto i: runs){
            for(auto j: i){
                output_file << j <<",";
            }
            output_file << endl;
        }
        
no_submerged_pass++;
      }
    
    ofstream output_file("output.txt");
    for(auto i : runs){
        for(auto j:i){
            output_file<<j<<endl;
        }
    }



    ofstream out("analysis.txt");
    out << "Total number of seeks:"<< seeks<<endl;
    out << "Total number of transfers:"<< transfers-1<<endl;
    out << "Total number of merged paases:"<< no_submerged_pass<<endl;
    out << "Total number of seeks during sorting phase:"<< sortedrun_seeks<<endl;
    out << "Total number of transfers during sorting phase:"<< sortedrun_transfers-1<<endl;
    out << "Total number of seeks during merged phases:"<< merged_seeks<<endl;
    out << "Total number of tranfers during merged phases:"<< merged_transfers<<endl;
    out << "Total number of cost during sorted run phase:"<< sortedrun_seeks+sortedrun_transfers-1<<endl;
    out << "Total number of cost during merged phase:"<< merged_seeks+merged_transfers<<endl;
    
return 0;
}