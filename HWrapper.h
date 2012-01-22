
#ifndef HWrapper_h
#define HWrapper_h

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

#include "configParser/config.h"

#include "TRandom.h"
#include "TTimeStamp.h"

#include "TH1F.h"
#include "TH2F.h"

using namespace std;
//using namespace Common;


class HWrapper{
	private:
		string  name;
		TH1*	histo;
		TH1F	histo1;
		TH2F	histo2;
		bool	isTH2F;
		bool	isTH1F;
		float	xbins[100000];
		string	xbinLabels[100000];
		float	xMinVis;
		float	xMaxVis;
		float	yMinVis;
		float	yMaxVis;
		float	zMinVis;
		float	zMaxVis;
		bool	logx;
		bool	logy;
		bool	logz;
		bool	showOverFlow;
		bool	showUnderFlow;
		bool	showText;
		bool	centerLabels;
		string	TH1Type;
		bool	hasVariableWidthBins;
		double	NOEraw;


	public :
		// Default constructor
		HWrapper();
		HWrapper(const HWrapper&);
		HWrapper(string, string, const Config&);
		virtual ~HWrapper();

		TH1 const *		GetHisto() const;
		TH1 *			GetHisto();
		string			GetName() const;
		float const		GetMinXVis() const;
		float const		GetMaxXVis() const;
		float const		GetMinYVis() const;
		float const		GetMaxYVis() const;
		float const		GetMinZVis() const;
		float const		GetMaxZVis() const;
		string			GetXTitle() const;
		string			GetYTitle() const;
		string			GetZTitle() const;
		bool const		GetLogX() const;
		bool const		GetLogY() const;
		bool const		GetLogZ() const;
		bool const		ShowOverFlow() const;
		bool const		ShowUnderFlow() const;
		bool const		ShowText() const;
		bool const		CenterLabels() const;
		bool const		IsTH1F() const;
		bool const		IsTH2F() const;
		bool const		HasVariableWidthBins() const;
		void			Fill(double, double);
		void			Fill(double, double, double);
		double const	GetNOEraw() const;
		double const	GetMaximum() const;
		double const	GetMaximumWithError() const;


		void	SetHisto(TH1 const &);
		void	SetHisto(TH1*);
		void	SetIsTH1F(bool const);
		void	SetIsTH2F(bool const);
		void	SetMaximum(double const);
		void	ResetMaximum(double const iFactor=1.1);
		void	Add(TH1 const &, double const iFactor=1.0);
		void	Add(HWrapper const &, double const iFactor=1.0);
		void	NormalizeTo(double const);
		void	ScaleBy(double const);
		void	Positivize();
		void	FillRandom(string const);

		void	SetLineWidth(int const,int iColor=0);
		void	SetFillStyle(int const,int iColor=0);
		void	SetFillColor(int const);
		void	SetLineColor(int const);
		void	SetMarkerStyle(int const);


		ClassDef(HWrapper, 1);
};

#endif

