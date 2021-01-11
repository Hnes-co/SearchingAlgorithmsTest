#include <iostream>
#include <chrono>
#include <random>
#include "ordered_list.h"

using namespace std;

int generateTarget(int low, int high) {

    random_device                   rd;
    mt19937                         gen(rd());
    uniform_int_distribution<int>   dstr(low, high);

    return dstr(gen);
}


Ordered_list create_list(int data_size) {
    Ordered_list the_list;
    int data = 1;

    for(int i = 0; i < data_size; i++)
    {
        the_list.insert(i, data);
        data = data + 2;
    }
    return the_list;
}

int sequential_search(Ordered_list the_list, int target) {
    int comparisons = 0;
    Error_code result = not_present;
    int i;    

    for(i = 0; i < the_list.size(); i++)
    {
        int x;
        the_list.retrieve(i, x);
        cout << "Comparing the target " << target << " to the list position [" << i << "]: " << x << endl;
        if(target == x) {
            result = success;
            comparisons++;
            break;  
        }
        comparisons++;
    }

    switch (result)
    {
    case success:
        cout << "Sequential search was successful, the target " << target << " was found in the list." << endl;
        return comparisons;
        break;

    case not_present:
        cout << "Sequential search was unsuccessful, the target " << target << " was not found in the list." << endl;
        return comparisons;
        break;
    
    default:
        return comparisons;
        break;
    }
    
}


int binary_search(Ordered_list the_list, int target, int top, int bottom, int comparisons) {

    int mid = (bottom + top) / 2;
    if(top > bottom)
    {
        int x;
        the_list.retrieve(mid, x);
        cout << "Comparing the target " << target << " to the list position [" << mid << "]: " << x << endl;
        if(x == target) {
            comparisons++;
            cout << "Binary search was successful, the target " << target << " was found in the list." << endl;
            return comparisons;
        }
        else if(target < x) {
            top = mid - 1;
            comparisons++;
            binary_search(the_list, target, top, bottom, comparisons);
        }
        else if(target > x) {
            bottom = mid + 1;
            comparisons++;
            binary_search(the_list, target, top, bottom, comparisons);
        }
    }
    else if(top < bottom) 
    {
        cout << "Binary search was unsuccessful, the target " << target << " was not found in the list." << endl;
        return comparisons;
    }
    else 
    {
        int x;
        the_list.retrieve(bottom, x);
        cout << "Comparing the target " << target << " to the list position [" << bottom << "]: " << x << endl;
        if(x == target) {
            comparisons++;
            cout << "Binary search was successful, the target " << target << " was found in the list." << endl;
            return comparisons;
        }
        else
        {
            cout << "Binary search was unsuccessful, the target " << target << " was not found in the list." << endl;
            return comparisons;
        }
        
    }
    
}


int main() {
    char input, input2;
    int entries, target, bottom, top;
    Ordered_list list;
    int comparisons = 0;
    Error_code result;
    random_device                   rand_dev;
    mt19937                         generator(rand_dev());
    uniform_int_distribution<int>   distr(1, 999);
    
    
    cout << "Test one search algorithm (1) or compare them? (2) ";
    cin >> input;

    switch (input)
    {
    case '1':
        cout << "Use sequential (s) or binary (b) search? ";
        cin >> input2;
        cout << "How many data entries you want to the list? (1-1000) ";
        cin >> entries;

        list = create_list(entries);
        cout << "Give target value to search for: ";
        cin >> target;

        if(input2 == 's') {
            auto begin = chrono::high_resolution_clock::now();
            comparisons = sequential_search(list, target);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
            cout << "Number of comparisons made: " << comparisons << endl;
            cout << "Time elapsed: " << elapsed.count() << " milliseconds" << endl;
        }
        else if(input2 == 'b') {
            bottom = 0;
            top = list.size() - 1; 
            result = not_present;
            auto begin = chrono::high_resolution_clock::now();
            comparisons = binary_search(list, target, top, bottom, comparisons);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);

            cout << "Number of comparisons made: " << comparisons << endl;
            cout << "Time elapsed: " << elapsed.count() << " milliseconds" << endl;

        }
        else {
            cout << "invalid input." << endl;
        }
        break;
    
    case '2':
        {   
            int reps;

            cout << "How many times you want the algorithms to be tested? (1-50) ";
            cin >> reps;

            int entriesArray[50];
            int targetsArray[50];
            int totalSequentialComparisons = 0;
            int totalBinaryComparisons = 0;
            double sequentialTotalElapsed = 0;
            double binaryTotalElapsed = 0;

            cout << "The data sizes for the searches are: " << endl;
            for(int i = 0; i < reps; i++) {
                entriesArray[i] = distr(generator);
                cout << entriesArray[i] << ", ";
            }
            cout << endl;
            cout << "The targets for the searches are: " << endl;
            for(int i = 0; i < reps; i++) {
                targetsArray[i] = generateTarget(0, entriesArray[i] * 2);
                cout << targetsArray[i] << ", ";;
            }
            cout << endl << endl;

            cout << "Ready to start searching." << endl;
            system("pause");


            for(int i = 0; i < reps; i++) {
                list = create_list(entriesArray[i]);

        
                auto begin = chrono::high_resolution_clock::now();
                comparisons = sequential_search(list, targetsArray[i]);
                auto end = chrono::high_resolution_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);

                totalSequentialComparisons = totalSequentialComparisons + comparisons;
                sequentialTotalElapsed = sequentialTotalElapsed + elapsed.count();

                comparisons = 0;

                bottom = 0;
                top = list.size() - 1;
                auto begin1 = chrono::high_resolution_clock::now();
                comparisons = binary_search(list, targetsArray[i], top, bottom, comparisons);
                auto end1 = chrono::high_resolution_clock::now();
                auto elapsed1 = chrono::duration_cast<chrono::milliseconds>(end1 - begin1);

                totalBinaryComparisons = totalBinaryComparisons + comparisons;
                binaryTotalElapsed = binaryTotalElapsed + elapsed1.count();

            }
            cout << endl << endl;

            cout << "Comparison finished after " << reps << " searches made by both algorithms." << endl;
            cout << "------------------ SEQUENTIAL SEARCH ------------------" << endl;
            cout << "Sequential search performed a total of " << totalSequentialComparisons << " comparisons." << endl;
            cout << "With an average of " << totalSequentialComparisons / reps << " comparisons per search" << endl;
            cout << "Sequential search used a total of " << sequentialTotalElapsed << " milliseconds" << endl;
            cout << "With an average of " << sequentialTotalElapsed / reps << " milliseconds per search" << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "------------------- BINARY SEARCH ---------------------" << endl;
            cout << "Binary search performed a total of " << totalBinaryComparisons << " comparisons." << endl;
            cout << "With an average of " << totalBinaryComparisons / reps << " comparisons per search" << endl;
            cout << "Binary search used a total of " << binaryTotalElapsed << " milliseconds" << endl;
            cout << "With an average of " << binaryTotalElapsed / reps << " milliseconds per search" << endl;
            cout << "-------------------------------------------------------" << endl;


            

            break;
        }
    default:
        cout << "Input must be 1 or 2!!!!" << endl;
        break;
    }



    
    system("pause");


}



