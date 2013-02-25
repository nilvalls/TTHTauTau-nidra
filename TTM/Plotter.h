#ifndef TTMPlotter_h
#define TTMPlotter_h

#include "Branches.h"
#include "TMVAEvaluator.h"
#include "../Plotter.h"

using namespace std;

class TTMPlotter : public Plotter {

	public:
		TTMPlotter(map<string,string> const &);
		~TTMPlotter();

	protected:

	private:
		TTM_TMVAEvaluator*		mva;
		void	FillHistos(HContainer*, Branches*, bool const, Trigger const *, weightCounter *);

};

#endif










