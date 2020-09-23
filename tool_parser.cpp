#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// using pair (a, b) to indicates that
typedef vector<double> coord;
pair<coord, coord> coordinates;

class Path
{
  private:
  int type;
  vector<coord> coords;
  public:
  Path(int t, vector<coord> &v): type(t), coords(v){}
  Path(int t): type(t){}
  void setCoord(vector<coord> &v) {
    coords = v;
  }
  string tostring() {
    cout << "type is " << type << endl;
    cout << "the coords is \n";
    for (auto coord : coords) {
      for (auto c : coord) {
        cout << c << " ";
      } cout << endl;
    }
  }
  int gettype() { return type; }
  vector<coord> getv() { return coords; }
};

void add(vector<Path> &path, int t, vector<coord> &coords) {
  path.push_back(Path(t, coords));
}


// split the coordinates string
void split(const string &s, vector<double> &v, const string &c) {
  string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while (string::npos != pos2) {
    v.push_back(stod(s.substr(pos1, pos2-pos1)));
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if (pos1 != s.length()) {
    v.push_back(stod(s.substr(pos1)));
  }
}

void parser(string filename, vector<Path> &vpath) {
  ifstream input(filename);
  string s;
  bool flag = false;
  while (true) {
    if (!flag) {
      getline(input, s);
      if(input.eof()) break;
    } else {
      flag = false;
    }
    if (s.substr(0, 11) == "PAINT/COLOR") {
      int dot = s.find(',');
      int type = stoi(s.substr(dot+1, s.length()-dot-1));
      vector<coord> vc;
      while (getline(input, s)) {
        if (s.substr(0, 11) == "PAINT/COLOR") {
          flag = true;
          break;
        }
        if (s.substr(0, 4) == "GOTO") {
          vector<double> coords;
          split(s.substr(5), coords, ",");
          vc.push_back(coords);
        }
      }
      cout << type << endl;
      for (auto a : vc) {
        for(auto b : a) {
          cout << b << " ";
        } cout << endl;
      }
      add(vpath, type, vc);
    }
  }
}


int main() {
  vector<Path> vpath;
  parser("tool1.txt", vpath);
  for (int i = 0; i < vpath.size(); i++) {
    int type = vpath[i].gettype();
    vector<coord> vc = vpath[i].getv();
    cout << "type is " << type << endl;
    for (auto coord : vc) {
      for (auto c : coord) {
        cout << c << " ";
      } cout << endl;
    } 
  }
}

