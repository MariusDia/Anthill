/*
 * AntBasePheromone.cpp
 *
 *  Created on: 6 mars 2021
 *      Author: jce
 */

#include <AntBasePheromone.h>

AntBasePheromone::AntBasePheromone(Environment * ptrEnvInit, const Vector2<float> & posInit, Vector2<float> dir, Anthill * maisonInit)
:
Agent(ptrEnvInit,posInit, 2),
vitesseDeplacement(1),
directionDeplacement(dir),
dureeVie(MathUtils::random(1000,2500)),
qteNourrTransporte(0),
maison(maisonInit)
{
}

/**Fait avancer la fourmi en la translatant d'un vecteur d*v*Timmer::dt()
 *
 */
void AntBasePheromone::avancer(){

	float t = Timer::dt() * vitesseDeplacement;
	t = vitesseDeplacement;
	Vector2<float> v = directionDeplacement * t;

	this->translate(v);
}

/**Fait tourner la fourmi d'un certain angle
 * applique une roation sur le vecteur directionDeplacement
 * @param angle : angle de rotation(radians)
 */
void AntBasePheromone::rotation(const float angle){
	this->directionDeplacement = this->directionDeplacement.rotate(angle);
}

/**Inverse la direction de la fourmi
 *
 */
void AntBasePheromone::demitour(){
	this->rotation(MathUtils::pi);
}

/**Tourne la fourmi vers une cible
 * @param cible : cible vers laquelle la fourmi doit se trouner
 */
void AntBasePheromone::tournerVersCible(const Agent * cible){
	Vector2<float> directionVersCible = this->getPosition().direction(cible->getPosition());//(cos x, sin x)
	this->directionDeplacement = directionVersCible;
}

/**Permet à la fourmi de déposer la nourriture qu'elle transporte
 *
 */
void AntBasePheromone::deposerNourriture(){
	float tmp = qteNourrTransporte;
	//enleve la nourriture de la fourmi
	qteNourrTransporte = 0;
	//rajoute la nourriture dans la fourmillière
	maison->depositFood(tmp);
}

/**Permet à la fourmi de prendre de la nourriture d'une source
 *
 */
void AntBasePheromone::prendreNourriture(Food * source){
	qteNourrTransporte = source->collectFood(5-qteNourrTransporte);//car une fourmi ne peut transporter pas plus de 5 unités de nourriture
}

/**Permet à la f ourmi de percevoirde la nourriture
 * dans un angle de pi/2
 * à une distance max de 3m
 *
 *@return une liste des sources de nourritures apercues par la fourmi
 */
std::vector<Food*> AntBasePheromone::voirNourriture(){
	return this->perceive<Food>(directionDeplacement, MathUtils::pi/2, 3);
}


/**Permet à la fourmi de déposer des phéromones à chaque déplacement
 *
 */
void AntBasePheromone::putPheromone(float q){
	std::vector<Pheromone*> phe = this->perceive<Pheromone>();
	if(phe.empty()){//si la fourmi n'est pas placé sur une phéromone, elle en place
		new Pheromone(this->getEnvironment(),this->getPosition(),q);
	}
	else{
		phe[0]->addQuantity(q);
	}
}

/**Permet à la fourmi de
 * 	percevoir les pheromones à une distance de 8cm
 * 	en choisir une à suivre
 *	@return la pheromone à suivre si il y en a
 */
Pheromone * AntBasePheromone::choosePheromone() const{
	std::vector<Pheromone*> phe = this->perceive<Pheromone>(directionDeplacement, MathUtils::pi/2, 8);
	if(phe.empty())
		return nullptr;
	else{
		std::vector<float> phePoids(phe.size());
		for(long unsigned int i=0; i<phe.size(); i++){
			phePoids[0]=phe[0]->qtePheDeposee;
		}
		int i = MathUtils::randomChoose(phePoids);
		return phe[i];
	}


}

