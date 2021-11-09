
#include <Pheromone.h>


//Constructeur
Pheromone::Pheromone(Environment * ptrEnvInit, const Vector2<float> & posInit, float qtePheInit = 1000)
:
Agent(ptrEnvInit,posInit, 1),
qtePheDeposee(qtePheInit)
{
}

//Destructeur
Pheromone::~Pheromone(){

}

/**Accesseur
 * @return qtePheDeposee
 */
float Pheromone::getQuantity() const{
	return this->qtePheDeposee;
}

/**Setter
 * @pre qte > 0
 * @post qtePheDeposee modifiée
 */
void Pheromone::addQuantity(const float qte){
	this->qtePheDeposee = this->qtePheDeposee + qte;
}

/**actualise le comportement de la pheromone
 *
 */
void Pheromone::update(){
	//Mort
	if(this->qtePheDeposee<0.01)
		this->setStatus(destroy);


	//Création de la représentation graphique de la pheromone
	Environment::LocalizedEntity::setRadius(this->getRadius());
	Renderer * cercle = Renderer::getInstance();
	cercle->drawCircle(getPosition(), getRadius(), Renderer::Color(0,128,128,std::min(this->qtePheDeposee, 255.0f)));


	//Viellissement
	this->qtePheDeposee = this->qtePheDeposee - (0.01*this->qtePheDeposee*Timer::dt());
}
