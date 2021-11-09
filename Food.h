#ifndef FOOD_H_
#define FOOD_H_

#include "Agent.h"
#include <MathUtils.h>
#include <Renderer.h>


class Food : public Agent{
public:

	float qteNourriture;

	/**Constructeur
	 *
	 */
	Food(Environment * ptrEnvInit, const Vector2<float> & posInit, float initQteNourrture);

	//Destructeur
	~Food();

	/**accesseur qteNourriture
	 *@return qteNourriture
	 */
	float getFoodQuantity() const;


	/**
	 * ne pourra jamais renvoyer plus de nourriture qu’il n’en reste à disposition
	 * @param quantity :quantité de nourriture demandée
	 * @return : quantité de nourriture accordée
	 */
	float collectFood(float quantity);

	/**
	 *
	 */
	void update();
};

#endif
