#include <AntBase.h>

//Constructeur
AntBase::AntBase(Environment * ptrEnvInit, const Vector2<float> & posInit, Vector2<float> dir, Anthill * maisonInit)
:
Agent(ptrEnvInit,posInit, 2),
vitesseDeplacement(1),
directionDeplacement(dir),
dureeVie(MathUtils::random(1000,2500)),
qteNourrTransporte(0),
maison(maisonInit)
{

}

//Destructeur
AntBase::~AntBase(){

}

/**Fait avancer la fourmi en la translatant d'un vecteur d*v*Timmer::dt()
 *
 */
void AntBase::avancer(){

	float t = Timer::dt() * vitesseDeplacement;
	t = vitesseDeplacement;
	Vector2<float> v = directionDeplacement * t;

	this->translate(v);
}

/**Fait tourner la fourmi d'un certain angle
 * applique une roation sur le vecteur directionDeplacement
 * @param angle : angle de rotation(radians)
 */
void AntBase::rotation(const float angle){
	this->directionDeplacement = this->directionDeplacement.rotate(angle);
}

/**Inverse la direction de la fourmi
 *
 */
void AntBase::demitour(){
	this->directionDeplacement.rotate(MathUtils::pi);
}

/**Tourne la fourmi vers une cible
 * @param cible : cible vers laquelle la fourmi doit se trouner
 */
void AntBase::tournerVersCible(const Agent * cible){
	Vector2<float> directionVersCible = this->getPosition().direction(cible->getPosition());//(cos x, sin x)
	this->directionDeplacement = directionVersCible;
}

/**Permet à la fourmi de déposer la nourriture qu'elle transporte
 *
 */
void AntBase::deposerNourriture(){
	float tmp = qteNourrTransporte;
	//enleve la nourriture de la fourmi
	qteNourrTransporte = 0;
	//rajoute la nourriture dans la fourmillière
	maison->depositFood(tmp);
}

/**Permet à la fourmi de prendre de la nourriture d'une source
 *
 */
void AntBase::prendreNourriture(Food * source){
	qteNourrTransporte = source->collectFood(5-qteNourrTransporte);//car une fourmi ne peut transporter pas plus de 5 unités de nourriture
}

/**Permet à la f ourmi de percevoirde la nourriture
 * dans un angle de pi/2
 * à une distance max de 3m
 *
 *@return une liste des sources de nourritures apercues par la fourmi
 */
std::vector<Food*> AntBase::voirNourriture(){
	return this->perceive<Food>(directionDeplacement, MathUtils::pi/2, 3);
}

