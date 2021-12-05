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

const long INF = numeric_limits<long>::max();

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

//to contruct path by bactracking verts
vector<char> pathhelp(int i, int j, long** verts){
  vector<char> leftPath, rightPath;
  if(m3[x][y] != '-'){
    leftPath = pathhelp(i, verts[i][j], verts);
    rightPath = pathhelp(verts[i][j], j, verts);
    rightPath.insert(rightPath.end(), leftPath.begin()+1, leftPath.end());
    return rightPath;
  }else{
    if(x!=y){
      leftPath.push_back
    }
  }
}

void printVerticePairs(long** Paths, long** verts, long num_vertices){
  for(int i = 0; i<num_vertices; i++){
    //vector of chars used for storing path
    vector<char> path;
    //first  char in distance pair
    char first = 'A' + i;
    for(int j = 0; j < num_vertices; j++){
      //second in pair
      char second = "A" + j
      //if a == b, distacne between them is zero
      if(first ==second){
        cout << first << " -> " << first << ", distance: 0, path: " << first << endl;
        return;
      }
      path = pathhelp(i, j, verts);

    }
  }
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
                //only update verts if paths[i][j] is changed
                if(Paths[i][j] == Paths[i][k]+Paths[k][j]){
                  verts[i][j] = k;
                }
            } 
        }
    }

    //print all matrices
    display_table(distance, "Distance matrix:", num_vertices, false);
    display_table(Paths, "Path lengths:", num_vertices, false);
    display_table(verts, "Intermediate vertices:", num_vertices, true);
    printVerticePairs(Paths, verts, num_vertices);
}


int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
}

void clean(long** &matrix){
    //TODO
}

bool load_File(string fileName, long** &distance){
    // Create an ifstream object.
    ifstream input_file(fileName);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << fileName << "'." << endl;
        return false;
    }  

    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    


    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        string line;
        getline(input_file, line);
        istringstream ss;
        ss.str (line);
        int num_vertices;
        ss >> num_vertices;
        ss.clear();
        
        if(num_vertices < 1 || num_vertices > 26){
          cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
          return false;        
        }
        line_number++;

        //initiaze 2d matrix of distance to INF and diag to 0;
        distance = new long*[num_vertices];
        for(int i = 0; i < number_vertices; i++){
          distance[i] = new long[num_vertices];
          for(int j = 0; j < number_vertices; j++){
            distance[i][j] = (i == j)? 0 : INF;
          }
        }
        char min_vertex = 'A';
        char max_vertex = 'A' + num_vertices - 1;

        while (getline(input_file, line)) {
            vector<string> line_split = split(line, " ");
            if(line_split.size() != 3){
                cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                return false;
            }
            if(line_split[0][0] < min_vertex || line_split[0][0] > max_vertex) {//may need to check length
              cerr << "Error: Starting vertex '" << line_split[0] << "' on line " << line_number << " is not among values A-" <<      max_vertex << "." << endl;
              return false;
            }
            if(line_split[1][0] < min_vertex || line_split[1][0] > max_vertex){
              cerr << "Error: Ending vertex '" << line_split[0] << "' on line " << line_number << " is not among values A-" <<      max_vertex << "." << endl;
              return false;
            } 
            
            int weight;
            ss.str(line_split[2]);
            if(!(ss >> edge) || edge <= 0){
              cerr << "Error: Invalid edge weight '" << line_split[2] << "' on line " << line_number << "." << endl;
              return false;
            } 

            distance[line_number[0][0] - 'A'][line_number[1][0] - A''
            line_number++;
        }

        // Don't forget to close the file.
        input_file.close();
        
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << fileName << "'.";
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
