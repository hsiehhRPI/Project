// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

void PushBack(TrainCar*& head, TrainCar* car) {
	//If completely empty
	if (head== NULL) {
		head = car;
		car->prev = NULL;
		car->next = NULL;
	}
	//If there are other elements in the list
	else {
		TrainCar *tmp = head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = car;
		tmp->next->prev = tmp;
	}
}

void DeleteAllCars(TrainCar* &train) {
	TrainCar* t = train;
	if (t == NULL) {

	}
	else {
		//Idea: Move to the back of the list and start deleting from there
		TrainCar *tmp = train;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		//We moved to the back of the list
		while (tmp->prev != NULL) {
			tmp = tmp->prev;
			delete tmp->next;
		}
		delete tmp;
	}
}

//Custom helper function, size
int SIZE(TrainCar* train) {
	int s = 0;
	TrainCar* p = train;
	if (p == NULL) {
		return 0;
	}
	else {
		while (p != NULL) {
		p = p->next;
		s++;
	}
	return s;
	}
}

//I think we need to initialize all values using this function, but I'm not entierly sure
bool TotalWeightAndCountCars(TrainCar* train, int &total_weight, int &num_engines, int &num_freight_cars, int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars){
	total_weight = 0;
	num_engines = 0;
	num_freight_cars = 0;
	num_passenger_cars = 0;
	num_dining_cars = 0;
	num_sleeping_cars = 0;
	TrainCar* t = train;
	while (t!=NULL){
		if (t->isEngine()==true){
			num_engines += 1;
			total_weight += 150;
		}
		else if (t->isFreightCar()==true){
			num_freight_cars += 1;
			total_weight += t->getWeight();
		}
		else if (t->isDiningCar()==true){
			num_dining_cars+= 1;
			total_weight += 50;
		}
		else if (t->isPassengerCar()==true){
			num_passenger_cars+=1;
			total_weight+=50;
		}
		else if (t->isSleepingCar()==true){
			num_sleeping_cars+=1;
			total_weight+=50;
		}
		t = t->next;
	}
	return true;
}

float CalculateSpeed(TrainCar* train) {
	double s = 0;
	int tw = 0;
	int e = 0;
	TrainCar* t = train;
	while (t!=NULL){
		if (t->isEngine()==true){
			e++;
			tw+=150;
		}
		else if (t->isFreightCar()==true){
			tw+=t->getWeight();
		}
		else {
			tw+=50;
		}
		t = t->next;
	}
	//I know this part is very weird and inefficient
	//but this is the way to do that doesn't produce
	//an incorrect speed value
	s += 550;
	s *= e;
	s *= 3000;
	s *= 3600;
	s /=20;
	s /= 0.02;
	s /= 5280;
	s /= tw;
	s *= 0.01;
	float speed = s;
	return speed;
}
//This needs fixing 
float AverageDistanceToDiningCar(TrainCar* train) {
	//There could have multiple dining areas in a car
	//We will search for a dining car from both right and left of a passenger car
	int carC = 0;
	int dDine = 0;
	int dr = 1;
	int dl = 1;
	TrainCar* t = train;	//This pointer will keep track of what car we are on
	TrainCar* m = train; 	//This pointer will help us find where is the dining car
	while (t->next != NULL) {
		if (t->isPassengerCar() == true) {
			carC ++;
			//Search to the right 
			while (m->next != NULL && m->isDiningCar() != true) {
				dr++;
				m = m->next;
			}
			//Search to the left
			m = t;		//Reset position
			while (m->prev != NULL && m->isDiningCar() != true) {
				dl++;
				m = m->prev;
			}
			//Different possible scenarios
			if (dr == 0 && dl == 0) {
				//If there is no sleeping car
				return 0;
			}
			else if (dr == dl){
				dDine += dr;
			}
			else if (dr == 0 && dl !=0) {
				dDine += dl;
			}
			else if (dr != 0 && dl == 0) {
				dDine += dr;
			}
			else {
				if (dr > dl) {
					dDine += dl;
				}
				else {
					dDine += dr;
				}
			}
			dr *=0;
			dl*=0;
		}
		t = t->next;
		m = t;
	}
	float adtd = (dDine/carC);
	return adtd;
}

int ClosestEngineToSleeperCar(TrainCar* train) {
	int eDr = 0;
	int eDl = 0;
	int cets = 10000;
	TrainCar* t = train;
	TrainCar* m = train;
	while(t->next!=NULL) {
		if (t->isEngine() == true) {
			//Search to the right
			while (m->isSleepingCar()!= true &&m->next != NULL) {
				eDr++;
				m = m->next;
			}
			m = t;
			//Search to the left
			while (m->isSleepingCar()!= true &&m->prev != NULL) {
				eDl++;
				m = m->prev;
			}

			//Different possible scenarios
			if (eDr == 0 && eDl == 0) {
				//If there is no sleeping car
				return 0;
			}
			else if (eDr == 0 && eDl !=0) {
				cets = eDl;
			}
			else if (eDr != 0 && eDl == 0) {
				cets = eDr;
			}
			else {
				if (eDr > eDl) {
					if (cets > eDl) {
						cets = eDl;
					}
				}
				else {
					if (cets > eDr) {
						cets = eDr;
					}
				}
			}
		}
		t = t->next;
		m = t;
	}
	
	return cets;
}	
/*
- Write a function called std::vector<Trains>ShipeFright(4 arg)
	- First two are TrainCar pointers: (collection of engine, collection fo freight cars)
	- Third: minimum speed
	- Fourth: max num of cars allowed per train
- MUST ACHIEVE MINIMUM SPEED AND MAX CAR REQUIREMENTS
*/



//The following is an attempt to optimize

std::vector<TrainCar*> ShipFreight(TrainCar* &all_engines, TrainCar* &all_freight, int min_speed, int max_cars_per_train) {
	std::vector<TrainCar*> shipments;
	//Idealy, we want to maximize the number of freights per train while meeting the minimum speed and max car requirements
	//The pointers, e/f = current position, ep/fp = previous, en/fn = next
	TrainCar* et = all_engines;
	TrainCar* ft = all_freight;
	TrainCar* f = all_freight;

	int tw = 0;
	int nf = 0;
	while (f != NULL) {
		tw += f->getWeight();
		nf ++;
		f = f->next;
	}
	f = all_freight;		//Reset back to the head of the train
	std::cout << nf << std::endl;
	//Speed should be relatively close to minimum speed if we want to minimize number of trains
	//By rearranging the equation min_speed = (3000*nEngine*550*3600)/20*0.02*5280*(tw+150*nEngine), 
	// nEngine = (min_speed*20*100*0.02*5280*tw)/(3600*550*3000)-(60*20*100*0.02*5280*150)
	//we can get the minimum number of engines needed
	double nEngine = 60;
	nEngine *= 100;
	nEngine *= 20;
	nEngine *= 0.02;
	nEngine*=5280;
	nEngine*=tw;
	double sbeve = 3600;
	sbeve*= 550;
	sbeve*= 3000;
	double sbren = nEngine;
	sbren /= tw;
	sbren *= 150;
	double yee = sbeve-sbren;
	nEngine /= yee;
	int nE = ceil(nEngine);

	//Determining the number of trains needed
	//Ideally, the train length should be as close to max car per train as possible
	int nTrain = (nf/max_cars_per_train)+1;
	int ept = nE/nTrain;
	//Up to this part is okay! 18:58 Feb 20
	int tCount = 0;
	//Just dealing with the engines
	while (tCount < nTrain&&(all_engines!=NULL || all_freight!=NULL)) {
		TrainCar* nT = NULL;
		int t = 0;
		while (t < ept && et->next != NULL) {
			all_engines = all_engines->next;
			//We are always removing the head node and it is causing some complication
			et = all_engines->prev;
			et->next = NULL;
			et->prev = NULL;
			PushBack(nT, et);
			all_engines->prev = NULL;
			et = all_engines;
			t++;
			if (SIZE(all_engines) == 1 && t<ept) {
				TrainCar* e = all_engines;
				PushBack(nT, e);
				all_engines = NULL;
			}
		}
		t *= 0;
		int j = 0;
		while (SIZE(nT) < max_cars_per_train-1 && ft->next!= NULL&&CalculateSpeed(nT)>min_speed) {
			all_freight = all_freight->next;
			ft = all_freight->prev;
			ft->next = NULL;
			ft->prev = NULL;
			PushBack(nT, ft);
			all_freight->prev = NULL;
			ft = all_freight;

			if (SIZE(all_freight) == 1 && SIZE(nT)<max_cars_per_train && CalculateSpeed(nT)>min_speed) {
				TrainCar* t = all_freight;
				PushBack(nT, t);
				all_freight = NULL;
			}
		}
		
		shipments.push_back(nT);
		tCount++;
	}
	while (SIZE(shipments[shipments.size()-1]) < max_cars_per_train-1 && ft->next!= NULL&&CalculateSpeed(shipments[shipments.size()-1])>min_speed) {
			all_freight = all_freight->next;
			ft = all_freight->prev;
			ft->next = NULL;
			ft->prev = NULL;
			PushBack(shipments[shipments.size()-1], ft);
			all_freight->prev = NULL;
			ft = all_freight;

			if (SIZE(shipments[shipments.size()-1]) == 1 && SIZE(shipments[shipments.size()-1])<max_cars_per_train && CalculateSpeed(shipments[shipments.size()-1])>min_speed) {
				TrainCar* t = all_freight;
				PushBack(shipments[shipments.size()-1], t);
				all_freight = NULL;
			}
	}


	return shipments;
}

 void Separate(TrainCar* &train1, TrainCar* &train2, TrainCar* &train3) {
 	train2 = NULL;
 	train3 = NULL;
 	int tl = 0;
 	int dc = 0;
 	int sc = 0;
 	TrainCar* tr = train1;
 	while (tr != NULL) {
 		tl++;
 		tr = tr->next;
 	}
 	tr = train1; //Resetting the position of tr for later use
 	//For the speed to be relatively the same, two trains should weigh as similar as possible
 	//Since there are no freights, the weight is relatively easy to calculate

 	int tSize = 0;
 	int tSize2 = 0;

 	if (tl%2==0) {
 		tSize += (tl/2);
 		tSize2 += (tl/2);

 	}
 	else {
 		tSize += (tl/2);
 		tSize2 += (tl - tSize);
 	}
 	//Finding out whether the first half of the train has more/less engine than the back
 	//By only knowing half of the train, we could work out the number of engine in the latter
 	//To do this, TrainCar pointer tr is stepping through the first half of the train
 	int c = 0;
 	int ef = 0;
 	while (c < tSize) {
 		if (tr->isEngine()==true){
 			ef ++;
 		}
 		c++;
 	}
 	//Assuming we had too many engines in the front, to minimize the cost of link/unlink,
 	//Once we hit another engine, we should switch to add the engine on another train.
 	//Alternatively, we could also skip forward a certain amount of cars that will be for the second train
 	int eCount1 = 0;
 	int eCount2 = 0;
 	//Setting up the first train, in case there is no engine, we leave a space for engine
 	while (train1!=NULL) {
 		while (SIZE(train2) < tSize-1 && eCount1 < 2) {
 			if (tr->isEngine()==true) {
 				eCount1++;
 				train1 = train1->next;
				tr = train1->prev;
				tr->next = NULL;
				tr->prev = NULL;
				PushBack(train2, tr);
				train1->prev = NULL;
				tr = train1;
 			}
 			else {
 				train1 = train1->next;
				tr = train1->prev;
				tr->next = NULL;
				tr->prev = NULL;
				PushBack(train2, tr);
				train1->prev = NULL;
				tr = train1;
 			}
 		}
 		while (SIZE(train3) < tSize2 && eCount2 < 2) {
 		//Make the entire second train first
 			if (tr->isEngine()==true) {
 				eCount2++;
	 			train1 = train1->next;
				tr = train1->prev;
				tr->next = NULL;
				tr->prev = NULL;
				PushBack(train3, tr);
				train1->prev = NULL;
				tr = train1;
	 		}
	 		else if (SIZE(train1)==1) {
	 			TrainCar* t = train1;
				PushBack(train3, t);
				train1 = NULL;
	 		}
	 		else {
	 			train1 = train1->next;
				tr = train1->prev;
				tr->next = NULL;
				tr->prev = NULL;
				PushBack(train3, tr);
				train1->prev = NULL;
				tr = train1;
	 		}
 		}
 		if (SIZE(train2)!=tSize) {
 			while (train1->next!=NULL) {
 				train1 = train1->next;
				tr = train1->prev;
				tr->next = NULL;
				tr->prev = NULL;
				PushBack(train2, tr);
				train1->prev = NULL;
				tr = train1;
 			}
 			if (SIZE(train1)==1) {
	 			TrainCar* t = train1;
				PushBack(train2, t);
				train1 = NULL;
	 		}
 		}

 	}
 }

//An attempt to try to optimize comfort, the framework is below

/*
void Separate(TrainCar* train1, TrainCar* train2, TrainCar* train3) {
 	int tw = 0;
 	int tl = 0;
 	int dc = 0;
 	int sc = 0;
 	TrainCar* tr = train1;
 	while (tr->next != NULL) {
 		if (tr->isEngine()==true) {
 			tw+=150;
 		}
 		else {
 			tw+=50;
 		}
 		tr = tr->next;
 		tl++;
 	}
 	tr = train1; //Resetting the position of tr for later use
 	//For the speed to be relatively the same, two trains should weigh as similar as possible
 	//Since there are no freights, the weight is relatively easy to calculate
 	//Metrics of the first train, ideally these things should be the same for two train
 	int tSize = tl/2;
 	int dpt = dc/2;
 	int spt = sc/2;
 	//Finding out whether the first half of the train has more/less dining/sleeping/engine than the back
 	//By only knowing half of the train, we could work out the number of dining/sleeping/engine in the latter
 	//To do this, TrainCar pointer tr is stepping through the first half of the train
 	int c = 0;
 	int df = 0;
 	int sf = 0;
 	int ef = 0;
 	while (c < tSize) {
 		if (tr->isEngine()==true){
 			ef ++;
 		}
 		else if (tr->isDiningCar()==true) {
 			df++;
 		}
 		else if (tr->isSleepingCar()==true) {
 			sf++;
 		}
 		c++;
 	}
 	//When actually separating the train, we need to check it's neighboring cars 
 	//If both neighboring cars are needed in one of the train, we shouldn't separate their link
 	//We should also balance the number of sleeping/dining/passenger cars per train

 }
 */