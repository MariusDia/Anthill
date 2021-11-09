#ifndef ANTBASE_H_
#define ANTBASE_H_


#include <Vector2.h>
#include <Timer.h>
#include <cmath>
#include <MathUtils.h>
#include <Agent.h>
#include <Food.h>
#include <Environment.h>
#include <Anthill.h>


class AntBase : public Agent{

public:

	//Attributs
	//vitesses en cm/s
	float vitesseDeplacement;
	Vector2<float> directionDeplacement;
	float dureeVie;
	float qteNourrTransporte;
	Anthill * maison;


	//Constructeur
	AntBase(Environment * ptrEnvInit, const Vector2<float> & posInit, Vector2<float> dir, Anthill * maisonInit);

	//Destructeur
	~AntBase();

	/**Fait avancer la fourmi en la translatant d'un vecteur d*v*Timmer::dt()
	 *
	 */
	void avancer();

	/**Fait tourner la fourmi d'un certain angle
	 * applique une roation sur le vecteur directionDeplacement
	 * @param angle : angle de rotation(radians)
	 */
	void rotation(const float angle);

	/**Inverse la direction de la fourmi
	 *
	 */
	void demitour();

	/**Tourne la fourmi vers une cible
	 * @param cible : cible vers laquelle la fourmi doit se trouner
	 */
	void tournerVersCible(const Agent * cible);

	/**Permet à la fourmi de déposer la nourriture qu'elle transporte
	 *
	 */
	void deposerNourriture();

	/**Permet à la fourmi de prendre de la nourriture d'une source
	 *
	 */
	void prendreNourriture(Food * source);

	/**Permet à la f ourmi de percevoirde la nourriture
	 * dans un angle de pi/2
	 * à une distance max de 3m
	 *
	 *@return une liste des sources de nourritures apercues par la fourmi
	 */
	std::vector<Food*> voirNourriture();

	/**Actualise le comportement de la fourmi
	 *
	 */
	//void update();
	virtual void update()=0;

};

#endif
