#include <sstream>

#include "Helper.h"

using namespace std;

namespace Helper {
   vector<string> SplitString(string &s) {
      vector<string> result;
      istringstream iss(s);
      while (iss) {
         string part;
         iss >> part;
         if (part != "")
            result.push_back(part);
      }
      return result;
   }
}
