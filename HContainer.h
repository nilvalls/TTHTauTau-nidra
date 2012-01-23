
#ifndef HContainer_h
#define HContainer_h

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

#include "HWrapper.h"
#include "CutFlow.h"

#include "TH1F.h"
#include "TH2F.h"

using namespace std;
//using namespace Common;


class HContainer{
	private:
		map<string, HWrapper> container;

	public :
		// Default constructor
		HContainer();
		HContainer(const HContainer&);
		virtual ~HContainer();

		void 							Add(HWrapper const &);
		void 							Add(string const, HWrapper const &);
		HWrapper *						Get(string const);
		HWrapper const *				Get(string const) const;
		vector<string> const			GetNames() const;
		TH1 const *						GetHisto(string const) const;
		map<string, HWrapper> const &	GetContainer() const; 
		void							clear();
		int const						size() const;
		map<string, HWrapper>::const_iterator begin() const;
		map<string, HWrapper>::const_iterator end() const;


		void Fill(string const, double const, float const);
		void Fill(string const, double const, double const, float const);
		bool Exists(string const);
		void SetMarkerStyle(int const);
		void SetFillStyle(int const);
		void SetFillColor(int const);
		void SetLineColor(int const);
		void SetLineWidth(int const, int const);
		void NormalizeTo(double const);
		void ScaleBy(double const);
		void ApplyRosls(double const, CutFlow const *);
		void Add(HContainer const &, double const iFactor=1.0);
		void Positivize();

		ClassDef(HContainer, 1);
};

#endif

