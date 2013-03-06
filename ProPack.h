
#ifndef ProPack_h
#define ProPack_h

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

#include "ColoredOutput.h"

#include "THStack.h"

#include "HWrapper.h"
#include "Process.h"
#include "PContainer.h"

using namespace std;

class ProPack : public TObject {
	private:
		map<string, string>	params;
		Process			collisions;
		Process			qcd;
		vector<Process>	mcBackgrounds;
		vector<Process>	signals;
		PContainer		pContainer;
		
		bool                analyzed;
		double				integratedLumiInInvPb;
		bool				normalizedToLumi;

		bool                haveCollisions;
		bool                haveQCD;
		bool                haveMCbackgrounds;
		bool                haveBackgrounds;
		bool                haveSignals;

		bool				prepareCollisions;
		bool				prepareQCD;
		bool				prepareMCbackgrounds;
		bool				prepareSignals;


	public :
		// Default constructor
		ProPack();
		ProPack(ProPack const &);
		ProPack(const map<string,string>&);
		virtual ~ProPack();

		void Update(ProPack *);

		map<string,string> const 	GetParams() const;
		Process const *				GetCollisions() const;
		Process const *				GetQCD() const;
		vector<Process> const *		GetMCbackgrounds() const;
		vector<Process> const *		GetSignals() const;
		PContainer const *			GetPContainer() const;

		Process*					GetCollisions();
		Process*					GetQCD();
		vector<Process>*			GetMCbackgrounds();
		vector<Process>*			GetSignals();
		PContainer *				GetPContainer();

		void						SetCollisions(Process&, const vector<string> iNtuplePath=vector<string>());
		void						SetQCD(Process&);
		void						AddMCbackground(Process&, const vector<string> iNtuplePath=vector<string>());
		void						RemoveMCbackground(const string);
		void						CombineAndRemoveMCbackgrounds(const vector<string>, const string, const string, const string, const int);
		void						AddSignal(Process&, const vector<string> iNtuplePath=vector<string>());

		bool const					HaveCollisions() const;
		bool const					PrepareCollisions() const;
		void 						PrepareCollisions(bool const);

		bool const					HaveQCD() const;
		bool const					PrepareQCD() const;
		void						PrepareQCD(bool const);

		bool const					HaveMCbackgrounds() const;
		bool const					HaveMCbackground(const string);
		bool const					PrepareMCbackgrounds() const;

		bool const					HaveBackgrounds() const;
		bool const					PrepareBackgrounds() const;

		bool const					HaveSignals() const;
		bool const					PrepareSignals() const;

		double const				GetIntegratedLumiInInvPb() const;

		void						BuildQCD();
		bool const					Analyzed() const;
		bool const					NormalizedToLumi() const;
		void						SetAnalyzed();
		void						NormalizeToLumi();

/*		// Cut flows
		CutFlow 					GetCollisionsCutFlow() const;
		CutFlow 					GetQCDCutFlow() const;
		vector<CutFlow>				GetMCbackgroundsCutFlows() const;
		vector<CutFlow>				GetSignalsCutFlows() const; //*/


		// Useful for plotting
		int	const					GetNumberOfPlots() const;
		HContainer const			GetSignalsHWrappers(string const) const;
		HContainer const 			GetMCbackgroundsHWrappers(string const) const;
		HContainer const 			GetBackgroundsHWrappers(string const) const;
		HWrapper const				GetAvailableHWrapper() const;
		HWrapper const				GetAvailableHWrapper(string const) const;
		Process						GetAvailableProcess() const;

		// Misc
		void						DistributeProcesses();
		//vector<Process>				GetProcesses();
		vector<Process*>				GetProcesses();
		Process*					GetProcess(string const);
		string						GetProccessNamesToAnalyze();
		string						GetProccessNamesToPlot();
		bool 						PlotProcess(string const);
		bool const					IsStringThere(string const, string const) const;
		void						PrintProcessList() const;

		ClassDef(ProPack, 1);
};

#endif

