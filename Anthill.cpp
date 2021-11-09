#include <Anthill.h>


//Constructeur
Anthill::Anthill(Environment * ptrEnvInit, const Vector2<float> & posInit, float radiusInit)
:
Agent(ptrEnvInit,posInit,radiusInit),
nourrDepose(0)
//fourmis(new std::vector<AntBase>)
{
}

//Destructeur
Anthill::~Anthill() {
}


void Anthill::update(){
	/*if(???){
		this->setStatus(destroy);
	}*/
	Environment::LocalizedEntity::setRadius(this->getRadius());

	//Dessine un cercle, suppprimer l'ancien ???
	Renderer * cercle = Renderer::getInstance();
	cercle->drawCircle(getPosition(), getRadius(), Renderer::Color(0,0,255,255));
}

/** Permet aux fourmis de déposer la nourriture qu'elles transportent
 *
 */
void Anthill::depositFood(float quantity){
	this->nourrDepose=+quantity;
}

