#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

void distribute_apple() {
    vector<int> weights;
    int weight;
    
    while (true) {
        cout << "Enter apple weight in grams (-1 to stop): ";
        cin >> weight;
        if (weight == -1) {
            break;
        }
        weights.push_back(weight);
    }
    
    int ram_paid = 50;
    int sham_paid = 30;
    int rahim_paid = 20;
    
    int total_weight = 0;
    for (int w : weights) {
        total_weight += w;
    }
    
    vector<int> ram_weights, sham_weights, rahim_weights;
    int ram_weight_sum = 0, sham_weight_sum = 0, rahim_weight_sum = 0;
    
    for (int i = 0; i < weights.size(); ++i) {
        int w = weights[i];
        int max_payment = max({ram_paid, sham_paid, rahim_paid});
        
        if (ram_weight_sum + w <= ram_paid * total_weight / 100) {
            ram_weights.push_back(w);
            ram_weight_sum += w;
        } else if (sham_weight_sum + w <= sham_paid * total_weight / 100) {
            sham_weights.push_back(w);
            sham_weight_sum += w;
        } else {
            rahim_weights.push_back(w);
            rahim_weight_sum += w;
        }
    }
    
   
    cout << "Distribution Result:\n";
    cout << "Ram : ";
    for (int weight : ram_weights) {
        cout << weight << " ";
    }
    cout << "\nSham : ";
    for (int weight : sham_weights) {
        cout << weight << " ";
    }
    cout << "\nRahim : ";
    for (int weight : rahim_weights) {
        cout << weight << " ";
    }
}

int main() {
    distribute_apple();
    return 0;
}
