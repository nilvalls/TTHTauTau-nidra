
#define TopoPack_cxx
#include "TopoPack.h"

using namespace std;



// Default constructor
TopoPack::TopoPack(){
	collisions			= new Topology();
	qcd					= new Topology();
	mcBackgrounds		= new vector<Topology*>();
	signals				= new vector<Topology*>();

	analyzed			= false;

	haveCollisions		= false;
	haveMCbackgrounds	= false;
	haveBackgrounds		= false;
	haveQCD				= false;
	haveSignals			= false;
}


// Default destructor
TopoPack::~TopoPack(){
}

int TopoPack::GetOne() const {
	return collisions->GetOne();
}

int TopoPack::GetTwo(){
	return collisions->GetTwo();
}

bool TopoPack::Analyzed(){
	return analyzed;
}

Topology* TopoPack::GetCollisions(){
	return collisions;
}

TopoPack* TopoPack::Clone(){
	TopoPack* result = new TopoPack(*this);
}

void TopoPack::SetAnalyzed(){
	analyzed = true;
}


ClassImp(TopoPack)
