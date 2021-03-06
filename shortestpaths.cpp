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
  //check if vert[i][j] is equal to INF
  if(verts[i][j] != INF){
    leftPath = pathhelp(i, verts[i][j], verts);
    rightPath = pathhelp(verts[i][j], j, verts);
    rightPath.insert(rightPath.end(), leftPath.begin()+1, leftPath.end());
    return rightPath;
  }else{
      leftPath.push_back('A'+j);
      if(i != j){
        leftPath.push_back('A'+i);
      }
      return leftPath;
    }
  }


void printVerticePairs(long** Paths, long** verts, long num_vertices){
  vector<char> path;
  for(int i = 0; i<num_vertices; i++){
    //first  char in distance pair
    char first = 'A' + i;
    for(int j = 0; j < num_vertices; j++){
      //second in pair
      char second = 'A' + j;
      //if a == b, distacne between them is zero
      if(i == j){
        cout << first << " -> " << first << ", distance: 0, path: " << first << endl;
      }else{
        path = pathhelp(i, j, verts);
      //since path is constructed by bactracking, you must reverse it
        reverse(path.begin(), path.end());

      //print path
        cout << first << " -> " << second << ", distance: ";
        if(Paths[i][j] == INF){
            cout << "infinity, path: none";
        }else{
            cout << Paths[i][j] << ", path: " << path.at(0);
            //k needs to be unsigned int because path.size returns a value with that type
            for(long unsigned int k = 1; k< path.size(); k ++){
                cout << " -> " << path.at(k);
            }
        }
      cout << endl;
      }
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
        //fill array of verticies with dashes
        fill_n(verts[i], num_vertices, INF);
    }
    for(int i = 0; i < num_vertices; i++){
        for(int k = 0; k < num_vertices; k++){
            Paths[i][k] = distance[i][k];
        }    
    }
    for(int k = 0; k < num_vertices; k++){
        for(int i = 0; i < num_vertices; i++){
            for(int j = 0; j < num_vertices; j++){
                if(Paths[i][k] != INF && Paths[k][j] !=INF){
                    //only update verts if paths[i][j] is changed
                    if(Paths[i][j] > Paths[i][k]+Paths[k][j]){
                        verts[i][j] = k;
                    }
                    Paths[i][j] = min(Paths[i][j], Paths[i][k]+Paths[k][j]);
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

void clean(long** &matrix, const int &num_vertices){
    for(int i = 0; i < num_vertices; i++){
      delete [] matrix[i];
    }
    delete [] matrix;
}

vector<string> split(const string& s, const string &delimiter){
  size_t pos_start = 0, pos_end, delimiterLen = delimiter.length();
  string key;
  vector<string> res;

  while((pos_end = s.find(delimiter, pos_start)) != string::npos){
    key = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delimiterLen;
    res.push_back(key);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

bool load_File(string fileName, long** &distance, int num_vertices){
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
        ss >> num_vertices;
        ss.clear();
        
        if(num_vertices < 1 || num_vertices > 26){
          cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
          return false;        
        }
        line_number++;

        //initiaze 2d matrix of distance to INF and diag to 0;
        distance = new long*[num_vertices];
        for(int i = 0; i < num_vertices; i++){
          distance[i] = new long[num_vertices];
          for(int j = 0; j < num_vertices; j++){
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
            if(!(ss >> weight) || weight <= 0){
              cerr << "Error: Invalid edge weight '" << line_split[2] << "' on line " << line_number << "." << endl;
              return false;
            } 

            distance[line_split[0][0] - 'A'][line_split[1][0] - 'A'] = weight;
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
    int num_vertices;
    bool flag = load_File(argv[1], distance, num_vertices);
    if(!flag){
        clean(distance, num_vertices);
        return 1;
    } //end of error handling
    
    return 0;
}
