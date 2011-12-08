
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

#include "THStack.h"

#include "HWrapper.h"
#include "Process.h"

using namespace std;

class ProPack : public TObject {
	private:
		map<string, string>	params;
		Process			collisions;
		Process			qcd;
		vector<Process>	mcBackgrounds;
		vector<Process>	signals;
		
		bool                analyzed;
		double				integratedLumiInInvPb;

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

		map<string,string> const 	GetParams() const;
		Process const *				GetCollisions() const;
		Process const *				GetQCD() const;
		vector<Process> const *		GetMCbackgrounds() const;
		vector<Process> const *		GetSignals() const;

		Process*					GetCollisions();
		Process*					GetQCD();
		vector<Process>*			GetMCbackgrounds();
		vector<Process>*			GetSignals();

		void						SetCollisions(Process&);
		void						SetQCD(Process&);
		void						AddMCbackground(Process&);
		void						AddSignal(Process&);

		bool const					HaveCollisions() const;
		bool const					PrepareCollisions() const;
		void 						PrepareCollisions(bool const);

		bool const					HaveQCD() const;
		bool const					PrepareQCD() const;
		void						PrepareQCD(bool const);

		bool const					HaveMCbackgrounds() const;
		bool const					PrepareMCbackgrounds() const;

		bool const					HaveBackgrounds() const;
		bool const					PrepareBackgrounds() const;

		bool const					HaveSignals() const;
		bool const					PrepareSignals() const;

		double const				GetIntegratedLumiInInvPb() const;

		void						BuildQCD();
		bool const					Analyzed() const;
		void						SetAnalyzed();
		void						NormalizeToLumi();

		// Cut flows
		CutFlow 				GetCollisionsCutFlow() const;
		CutFlow 				GetQCDCutFlow() const;
		vector<CutFlow>			GetMCbackgroundsCutFlows() const;
		vector<CutFlow>			GetSignalsCutFlows() const;


		// Useful for plotting
		int	const				GetNumberOfPlots() const;
		HContainer const		GetSignalsHWrappers(string const) const;
		HContainer const 		GetMCbackgroundsHWrappers(string const) const;
		HContainer const 		GetBackgroundsHWrappers(string const) const;
		HWrapper const			GetAvailableHWrapper() const;
		Process					GetAvailableProcess() const;

		ClassDef(ProPack, 1);
};

#endif

