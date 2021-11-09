#include <Food.h>

//Constructeur
Food::Food(Environment * ptrEnvInit, const Vector2<float> & posInit, float initQteNourrture)
:
Agent(ptrEnvInit,posInit, MathUtils::circleRadius(initQteNourrture)),
qteNourriture(initQteNourrture)
{
}

//Destructeur
Food::~Food() {
}

/**accesseur qteNourriture
 *@return qteNourriture
 */
float Food::getFoodQuantity() const{
	return qteNourriture;
}


/**
 * ne pourra jamais renvoyer plus de nourriture qu’il n’en reste à disposition
 * @param quantity :quantité de nourriture demandée
 * @return : quantité de nourriture accordée
 */
float Food::collectFood(float quantity){
	if(qteNourriture>=quantity){
		qteNourriture = qteNourriture - quantity;
		this->update();
		return quantity;
	}
	else {
		qteNourriture = 0;
		this->update();
		return quantity;
	}
}

void Food::update(){
	//appelé quand on collecte de la nourriture dessus donc pas besoin de mettre un attribut "à changer" ???
	if(qteNourriture==0){
		this->setStatus(destroy);
	}
	else if(qteNourriture>0){
		Environment::LocalizedEntity::setRadius(MathUtils::circleRadius(qteNourriture));


		Renderer * cercle = Renderer::getInstance();
		cercle->drawCircle(getPosition(), getRadius(), Renderer::Color(154,235,38,255));
	}
}



