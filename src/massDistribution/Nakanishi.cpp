#include "crpropa/massDistribution/Nakanishi.h"

namespace crpropa{ 

double Nakanishi::getHIScaleheight(const Vector3d &position) const{
	
	double R = sqrt(pow(position.x,2)+pow(position.y,2));	//radius in galactic plane
	double scaleheight = 1.06*pc*(116.3 +19.3*R/kpc+4.1*pow(R/kpc,2)-0.05*pow(R/kpc,3));
	return scaleheight;
	}

double Nakanishi::getHIPlanedensity(const Vector3d &position) const {
	
	double R = sqrt(pow(position.x,2)+pow(position.y,2));	//radius in galactic plane
	double planedensity = 0.94/ccm*(0.6*exp(-R/(2.4*kpc))+0.24*exp(-pow((R-9.5*kpc)/(4.8*kpc),2)));
	return planedensity;
	}


double Nakanishi::getH2Scaleheight(const Vector3d &position) const {

	double R = sqrt(pow(position.x,2)+ pow(position.y,2)); //radius in galactic plane
	double scaleheight = 1.06*pc*( 10.8*exp(0.28*R/kpc)+42.78);
	return scaleheight;
}

double Nakanishi::getH2Planedensity(const Vector3d &position) const {

	double R = sqrt(pow(position.x,2)+pow(position.y,2)); //radius in galactic plane
	double planedensity =0.94/ccm*(11.2*exp(-R*R/(0.874*kpc*kpc)) +0.83*exp(-pow((R-4*kpc)/(3.2*kpc),2)));
	return planedensity;
}

double Nakanishi::getHIDensity(const Vector3d &position) const {
	
	double n = 0; //density
	double planedensity = getHIPlanedensity(position);
	double scaleheight = getHIScaleheight(position);
	n= planedensity*pow(0.5,pow(position.z/scaleheight,2));
		
	return n;
}

double Nakanishi::getH2Density(const Vector3d &position) const {
	
	double n = 0; //density
	double planedensity = getH2Planedensity(position);
	double scaleheight = getH2Scaleheight(position);
	n= planedensity*pow(0.5,pow(position.z/scaleheight,2));
	
	return n;
}
	
double Nakanishi::getDensity(const Vector3d &position) const {
	double n = 0;
	if(isforHI)
		n += getHIDensity(position);
	if(isforH2)
		n += getH2Density(position);
	
	//check if any density is activ and give warning if not
	bool anyDensityActive = isforHI||isforH2;

	if(anyDensityActive == false){
		KISS_LOG_WARNING
			<< "\n called getDensity on deactivated Nakanishi \n"
			<< "returned 0 density\n"
			<< "please activate\n";
	}	
	
	return n;
}

double Nakanishi::getNucleonDensity(const Vector3d &position) const {
	double n = 0;
	if(isforHI)
		n += getHIDensity(position);
	if(isforH2)
		n += 2*getH2Density(position);	// weight 2 for molecular hydrogen
	
	//check if any density is activ and give warning if not
	bool anyDensityActive = isforHI||isforH2;

	if(anyDensityActive == false){
		KISS_LOG_WARNING
			<< "\n tryed to get nucleon-density although all density-types are deaktivated \n"
			<< "density-module: Nakanishi\n"
			<< "returned 0 density\n"
			<< "please use constant Density with 0 \n";
	}	
	
	return n;
}

bool Nakanishi::getIsForHI() {
	return isforHI;
}

bool Nakanishi::getIsForHII() {
	return isforHII;
}
bool Nakanishi::getIsForH2() {
	return isforH2;
}

void Nakanishi::setIsForHI(bool HI) {
	isforHI = HI;
}

void Nakanishi::setIsForH2(bool H2) {
	isforH2 = H2;
}

std::string Nakanishi::getDescription() {
	
	std::stringstream s;
	s << "Density modell Nakanishi: ";
	s<< "HI component is ";
	if(isforHI==false)
		s<< "not ";
	s<< "activ. H2 component is ";
	if(isforH2==false)
		s<<"not "; 
	s<<"activ. Nakanishi has no HII component.";
	
	return s.str();
}

} //namespace crpropa
