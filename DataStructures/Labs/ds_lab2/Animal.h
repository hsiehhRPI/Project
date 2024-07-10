class Animal {
public:
	//CONSTRUCTORS
	Animal(std::string aName);
	Animal(std::string aName, int aWeight, std::string aDiet, std::string aHabitat);

	//ACCESSORS
	int getWeight() const;									//Expect to return int
	std::string getDiet() const;							//Expect to return std::string
	std::string getHabitat() const;							//Expect to return std::string

	//MODIFIERS
	void setWeight(int aWeight);							//Let user add/change the animal's weight
	void setDiet(std::string aDiet);						//Let user add/change the animal's diet
	void setHabitat(std::string aHabitat);					//Let user add/change the animal's habitat

private:													
//These metrics are necessary for other member functions, we need to prevent 
	int weight;											
	std::string name;
	std::string diet;
	std::string habitat;
};