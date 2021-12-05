/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Andrew Narvaez
 * Date        : 28 November 2021
 * Description : A program to solve all pairs shortest paths problem with Floyd's algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

/** 
 * Displays the matrix on the screen formatted as a table. 
 */ 
//given print statement
void display_table(long** const matrix, const string &label, long num_vertices, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < std::numeric_limits<long>::max() && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
    //changed to find the correct max_cell_width by taking the max of the max value or the number of vertices, then turning it
    //into a string and taking its length
	int max_cell_width = to_string(max(static_cast<long>(num_vertices - 1), max_val)).length();
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) { 
        cout << static_cast<char>(i + 'A'); 
        for (int j = 0; j < num_vertices; j++) { 
            cout << " " << setw(max_cell_width); 
            if (matrix[i][j] == std::numeric_limits<long>::max()) { 
                cout << "-"; 
            } else if (use_letters) { 
                cout << static_cast<char>(matrix[i][j] + 'A'); 
            } else { 
                cout << matrix[i][j]; 
            } 
        } 
        cout << endl; 
    } 
    cout << endl;
}


void floyds(long** distance, long num_vertices){
    //initiaze path array and vertices array for printing
    long** Paths = new long*[num_vertices];
    long** verts = new long*[num_vertices];
    for(int i = 0; i < num_vertices; i++){
        Paths[i] = new long[num_vertices];
        verts[i] = new long[num_vertices];
        //fill distance array with inf
        for(int j = 0; j < num_vertices; j++){
            verts[i][j] = std::numeric_limits<long>::max();
        }
    }
    for(int i = 0; i < num_vertices; i++){
        for(int k = 1; k < num_vertices; k++){
            Paths[i][k] = distance[i][k];
        }    
    }
    for(int k = 1; k < num_vertices; k++){
        for(int i = 1; i < num_vertices; i++){
            for(int j = 1; j < num_vertices; j++){
                Paths[i][j] = min(Paths[i][j], Paths[i][k]+Paths[k][j]);
            } 
        }
    }
<<<<<<< HEAD
=======
    //print all matrices
    display_table(distance, "Distance matrix:", num_vertices, false);
    display_table(Paths, "Path lengths:", num_vertices, false);
    display_table(verts, "Intermediate vertices:", num_vertices, true);
}


int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
>>>>>>> 627017a81cd3fb57d1b2a33a1132892da3629ab1
    }
}

void clean(long** &matrix){
    //TODO
}

bool load_File(string fileName, long** &distance){
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return false;
    }  

    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    


    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        if(line_number == 1){
                istringstream num;
                int num_vertices;
                num >> num_vertices;

                if(num_vertices < 1 || num_vertices > 26){
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
                    return false;
            }
        }

        while (getline(input_file, line)) {
            

            vector<string> line_split = split(line, " ");
            if(line_split.size() != 3){
                cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                return false;
            }

            



            line_number++;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return false;
    }
    return true;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    long** distance;
    bool flag = load_File(argv[1], distance);
    if(!flag){
        clean(distance);
        return 1;
    } //end of error handling
    

    return 0;
}
