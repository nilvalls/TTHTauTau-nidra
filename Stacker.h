//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  7 03:28:02 2011 by ROOT version 5.27/06b
// from TTree HMTTree/TauTauTree
// found on file: ditau_nTuple.root
//////////////////////////////////////////////////////////

#ifndef Stacker_h
#define Stacker_h

#include "Plotter.h"
#include "THStack.h"
#include "HWrapper.h"
#include "TemplateContainer.h"
#include "TGraphAsymmErrors.h"


class Stacker : public Plotter {

	public:
		Stacker(std::map<std::string,std::string> const &, bool includeShapeSystematics = false);
		virtual ~Stacker();
		void MakePlots(ProPack const *) ;

	private: 
        std::map<std::string,std::string> params;
        TFile*             stacksFile;
        TemplateContainer* templateContainer;

        TLegend*		GetLegend(ProPack const *);
        THStack*		GetBackgroundStack(ProPack const *, std::string const, double const) const;
        double const	GetMaximum(ProPack const *, std::string const, bool const) const;
        double const	GetMaximum(ProPack const *, std::string const) const;
        double const	GetMaximumWithError(ProPack const *, std::string const) const;
        void            AddShapeSystematicErrors(HWrapper&, std::string);
        std::pair<TGraphAsymmErrors*,TGraphAsymmErrors*>            
                        AddAsymmShapeSystematicErrors(HWrapper& bg, std::string plot);

        float minY;

};

#endif










