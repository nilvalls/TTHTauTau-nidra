
#ifndef PContainer_h
#define PContainer_h

#include <TROOT.h>
#include <math.h>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

#include "Process.h"

using namespace std;
//using namespace Common;


class PContainer{
	private:
		map<string, Process> container;

	public :
		// Default constructor
		PContainer();
		PContainer(const PContainer&);
		virtual ~PContainer();

		void 							Add(Process const &);
		void 							Add(string const, Process const &);
		Process *						Get(string const);
		Process const *					Get(string const) const;
		bool const 						Exists(string const) const;
		vector<string> const			GetNames() const;
		map<string, Process> *			GetContainer(); 
		map<string, Process> const *	GetContainer() const; 
		void							clear();
		int const						size() const;
		map<string, Process>::const_iterator begin() const;
		map<string, Process>::const_iterator end() const;

		int								GetNumberOfCollisionProcesses();
		int								GetNumberOfQCDProcesses();
		int								GetNumberOfMCbackgroundProcesses();
		int								GetNumberOfSignalProcesses();

		vector<Process*>				GetCollisionProcesses();
		vector<Process*>				GetQCDProcesses();
		vector<Process*>				GetMCbackgroundProcesses();
		vector<Process*>				GetSignalProcesses();

		ClassDef(PContainer, 1);
};

#endif

