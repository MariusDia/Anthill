#include <SillyAnt.h>

//Constructeur
SillyAnt::SillyAnt(Environment * ptrEnvInit, const Vector2<float> & posInit, Anthill * maisonInit)
:
AntBase(ptrEnvInit, posInit, Vector2<float>::random(), maisonInit)
{
}

//Destructeur
SillyAnt::~SillyAnt(){

}


/**actualise le comportement de la fourmi
 *
 */
void SillyAnt::update(){

	//std::cout << this->qteNourrTransporte << " nourritures \n";
	//std::cout << "(" << this->directionDeplacement[0] << "," << this->directionDeplacement[1] << ")\n";

	//Mort
	if(this->dureeVie<=0){//si fourmi atteint sa fin de vie, elle est détruite
		this->setStatus(destroy);
		std::cout << "Je suis morte \n";
		return;
	}


	//Création de la représentation graphique de la fourmi
	Environment::LocalizedEntity::setRadius(this->getRadius());


	if(qteNourrTransporte==0){//si elle ne transporte pas de nourriture, affiché en blanc
		Renderer * cercle = Renderer::getInstance();
		cercle->drawCircle(getPosition(), getRadius(), Renderer::Color(255,255,255,255));
	}

	else if(qteNourrTransporte>0){//si elle transporte de la nourriture, affiché en vert
		Renderer * cercle = Renderer::getInstance();
		cercle->drawCircle(getPosition(), getRadius(), Renderer::Color(128,255,128,255));
	}




	//Récolter ou déposer si sur un agent
	std::vector<Food*> foods = this->perceive<Food>();//sources de nourriture sur lesquelles se trouve la fourmi
	if(!foods.empty() && this->qteNourrTransporte<5){//si fourmi sur une source de nourriture, prend de la nourriture
		this->prendreNourriture(foods[0]);
		std::cout << "J'ai récolté de la nourriture \n";
	}

	std::vector<Anthill*> anthills = this->perceive<Anthill>();
	if(!anthills.empty() && anthills[0]==this->maison && qteNourrTransporte>0){//si fourmi sur SA fourmilière et qu'elle porte de la nourriture, dépose sa nourriture dedans
		this->deposerNourriture();
		this->directionDeplacement = Vector2<float>::random();
		std::cout << "J'ai déposé de la nourriture \n";
	}


	//Vers où se diriger
	if(this->qteNourrTransporte>=5){//si elle est pleine de nourriture, retourne à la fourmilière
		std::cout << "Je retourne chez moi \n";
		this->tournerVersCible(this->maison);
		this->avancer();
	}
	else if(this->qteNourrTransporte<5){// si la fourmi n'est pas pleine de nourriture, elle continue de chercher aléatoirement
		std::vector<Food*> nourrApercues= this->voirNourriture();
		if(nourrApercues.empty()){//si elle ne voit pas de nourriture, aléatoire
			std::cout << "Je cherche de la nourriture \n";
			float rand = MathUtils::random(-MathUtils::pi/10*(Timer::dt()), MathUtils::pi/10*(Timer::dt()));
			this->rotation(rand);
			this->avancer();
		}
		else { //sinon, elle se dirige vers la nourriture
			std::cout << "J'ai trouvé de la nourriture \n";
			this->tournerVersCible(nourrApercues[0]);
			this->avancer();
		}
	}


	//Viellissement
	this->dureeVie=dureeVie-Timer::dt();

}

