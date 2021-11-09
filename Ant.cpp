
#include <Ant.h>

//Constructeur
Ant::Ant(Environment * ptrEnvInit, const Vector2<float> & posInit, Anthill * maisonInit)
:
AntBasePheromone(ptrEnvInit, posInit, Vector2<float>::random(), maisonInit)
{
}

/**Actualise le comportement de la fourmi
 *
 */
/**actualise le comportement de la fourmi
 *
 */
void Ant::update(){

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




	/*//Récolter ou déposer si sur un agent
	std::vector<Food*> foods = this->perceive<Food>();//sources de nourriture sur lesquelles se trouve la fourmi
	if(!foods.empty() && this->qteNourrTransporte<5){//si fourmi sur une source de nourriture, prend de la nourriture
		this->prendreNourriture(foods[0]);
		std::cout << "J'ai récolté de la nourriture \n";
	}

	std::vector<Anthill*> anthills = this->perceive<Anthill>();
	if(!anthills.empty() && anthills[0]==this->maison && qteNourrTransporte>0){//si fourmi sur SA fourmilière et qu'elle porte de la nourriture, dépose sa nourriture dedans et fait demi tour
		this->deposerNourriture();
		this->demitour();
		std::cout << "J'ai déposé de la nourriture \n";
	}*/
	std::vector<Food*> foods = this->perceive<Food>();//sources de nourriture sur lesquelles se trouve la fourmi
	std::vector<Anthill*> anthills = this->perceive<Anthill>();//fourmilières sur lesquelles se trouve la fourmi

	std::vector<Food*> nourrApercues = this->voirNourriture();//sources de nourriture apercues
	Pheromone * pheApercue = this->choosePheromone();//pheromones apercues

	//Vers où se diriger
	if(this->qteNourrTransporte<5){// si la fourmi NE TRANSPORTE PAS de nourriture



		//1. si fourmi sur une source de nourriture, prend de la nourriture
		if(!foods.empty() && this->qteNourrTransporte<5){
			this->prendreNourriture(foods[0]);
			//std::cout << "J'ai récolté de la nourriture \n";
		}

		//2. si elle voit de la nourriture, elle se dirige vers la nourriture
		else if(!nourrApercues.empty()){
			//std::cout << "J'ai trouvé de la nourriture \n";
			this->tournerVersCible(nourrApercues[0]);
			this->avancer();
		}

		//3. si elle ne voit pas de nourriture mais voit des pheromones, elle se dirige vers les pheromones
		else if(nourrApercues.empty() && pheApercue!=nullptr){
			//std::cout << "J'ai trouvé des phéromones \n";
			this->tournerVersCible(pheApercue);
			this->avancer();
		}

		//4. si elle ne voit ni nourriture, ni pheromones, déplacement aléatoire
		else if(nourrApercues.empty() && pheApercue==nullptr){
			//std::cout << "Je cherche de la nourriture \n";
			float rand = MathUtils::random(-MathUtils::pi/10*(Timer::dt()), MathUtils::pi/10*(Timer::dt()));
			this->rotation(rand);
			this->avancer();
		}
	}
	//si elle TRANSPORTE de la nourriture, retourne à la fourmilière
	else if(this->qteNourrTransporte==5){
		//5. si fourmi sur SA fourmilière, dépose sa nourriture dedans et fait demi tour
		if(!anthills.empty() && anthills[0]==this->maison && qteNourrTransporte>0){
			this->deposerNourriture();
			this->demitour();
			//std::cout << "J'ai déposé de la nourriture \n";
		}
		//6. si elle n'est pas sur son nid
		else {
			//si elle ne voit pas de pheromones, elle retourne à son nid en ligne droite
			if(pheApercue==nullptr){
				//std::cout << "Je retourne chez moi \n";
				this->tournerVersCible(this->maison);
				this->avancer();
			}
			//sinon, elle les suit
			else{
				this->tournerVersCible(pheApercue);
				this->avancer();
			}
		}
	}

	//Phéromones à déposer
	if(this->qteNourrTransporte>0){
		this->putPheromone(100);
	}
	else{
		this->putPheromone(10);
	}

	//Viellissement
	this->dureeVie=dureeVie-Timer::dt();

}
