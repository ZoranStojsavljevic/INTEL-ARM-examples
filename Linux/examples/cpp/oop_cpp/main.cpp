#include <iostream>
using std::string;

class AbstractEmployee {
	virtual void AskForPromotion() = 0;
};

class Employee:AbstractEmployee {
private:
	// string Name;
	string Company;
	int Age;

protected:
	string Name;

public:
	void setName (string name) {
		Name = name;
	}

	string getName (void) {
		return Name;
	}

	void setCompany (string company) {
		Company = company;
	}

	string getCompany (void) {
		return Company;
	}

	void setAge (int age) {
		if (age >=18)
			Age = age;
	}

	int getAge (void) {
		return Age;
	}

	Employee (string name, string company, int age) {
		Name = name;
		Company = company;
		Age = age;
	}

	void IntroduceMyself () {
		std::cout << "Name - " << Name << std::endl;
		std::cout << "Company - " << Company << std::endl;
		std::cout << "Age - " << Age << std::endl;
	}

	// Abstraction principle
	// AskForPromotion() must have an implementation in the real class
	void AskForPromotion() {
		if ( Age > 30 )
			std::cout << Name << " got promoted!" << std::endl;
		else
			std::cout << Name << ", sorry, NO promotion for you!" << std::endl;
	}

	// Polymorphism principle (virtual function)
	virtual void work() {
		std::cout << Name << " is checking email, task backlog" << std::endl;
	}
};

// The method AskForPromotion() in Employee class is by default private
// class Developer: Employee {

// Inheritance principle
class Developer: public Employee {
public:
	string FavProgrammingLanguage;
	Developer(string name, string company, int age, string favProgrammingLanguage)
	:Employee(name, company, age)
	{
		FavProgrammingLanguage = favProgrammingLanguage;
	}

	void fixBug() {
		// Using getter from the superclass
		std::cout << getName() << " fixed bug using " << FavProgrammingLanguage << std::endl;
		// This is because Name is declared as protected in superclass
		std::cout << Name << " fixed bug using " << FavProgrammingLanguage << std::endl;
	}

	// Polymorphism principle
	void work() {
		std::cout << Name << " is writing " << FavProgrammingLanguage << " code" << std::endl;
	}
};

// Inheritance principle
class Teacher: public Employee {
public:
	string Subject;
	Teacher(string name, string company, int age, string subject)
	:Employee(name, company, age)
	{
		Subject = subject;
	}

	void PrepareLessons() {
		// This is because Name is declared as protected in superclass
		std::cout << Name << " is preparing " << Subject << " lesson" << std::endl;
	}

	// Polymorphism principle
	void work() {
		std::cout << Name << " is teaching " << Subject << std::endl;
	}
};

int main()
{
	int number;
	// Constructor
	Employee employee1 = Employee ("Saldina", "YT_codeBeauty", 25);
	// --- With introduction of constructor commented out! ---
	// employee1.Name = "Saldina";
	// employee1.Company = "YT_codeBeauty";
	// employee1.Age = 25;
	employee1.IntroduceMyself();

	Employee employee2 = Employee ("John", "Amazon", 35);
	// --- With introduction of constructor commanted out! ---
	// employee2.Name = "John";
	// employee2.Company = "Amazon";
	// employee2.Age = 35;
	employee2.IntroduceMyself();

	employee1.setAge(10);

	std::cout << employee1.getName() << " is " << employee1.getAge() << " years old " << std::endl;

	employee1.AskForPromotion();
	employee2.AskForPromotion();

	Developer d = Developer("Saldina", "YT_codeBeauty", 25, "C++");
	d.fixBug();
	d.AskForPromotion();

	Teacher t = Teacher("Jack", "Cool School", 50, "History");
	t.PrepareLessons();
	t.AskForPromotion();

	// Polymorphism principle
	// d.work();
	// t.work();

	// The most common use of polymorphism is when a parent class
	// reference is used to refer to a child class object
	Employee *e1 = &d;
	Employee *e2 = &t;

	e1->work();
	e2->work();
}
