/* Programmer: Jordan Shinespark
	Purpose: to create a streamlined CC-numbers-generator to speed up play.
	Date: 1/3/20
	
	Version 1.12
	
	From 1.1:
		-fixed issue where body-equipment GR rolls were also generating mental GRs
	From 1.11:
		-fixed issue where Forced Idle Rolls were stacking atop one another
   From 1.12:
   	-fixed issue where Use Checks were being double-rolled
   From 1.13:
   	-discovered and patched UC rolling at old Tier values
*/

#include <iostream.h>
#include <limits>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
#include <string>
using namespace std;

//Base menus
int YesNo();
bool Forfeit();
int IRTcalc(int penalty, int tier);
void UseCheck(int UCpen, int UCtier);
void UCprompt();
void HeadMenu();
void Caretakers();
void Traps();
void TTs();
void IdleRolls();
void ForcedIR();
void Encounter();
int Die3();
int Die4();
int Die5();
int Die6();
int Die7();
int Die10();
int Die20();
int Die100();
void BombPoof();
int Intensity(int base);
void randomGR(int lock);
int TrapRoll();
int CareGenerator(bool Caring);
int DiaperGenerator(bool Traps);
int TrapArtist();
int Misfire(bool Caring);
void perTurn();
void HypnoCheck(bool Caretaker);
void foodDrink();
void Playtime();

//Caretakers
void Kangaskhan();
void Goodra();
void Wigglytuff();
void Serperior();
void Gardevoir();
void Flygon();
void Boss();
void Miltank();
void Primarina();
void Leavanny();
void Togekiss();
void Ninetales();
void Chansey();
void Salazzle();
void Luxray();
void Nidoqueen();
void Vaporeon();
void Audino();
void Lucario();
void Ampharos();
void Ivysaur();
void Slowpoke();
void Snorlax();
void Mew();
void Galvantula();
void Ursaring();
void AlakazamPac();
void AlakazamSpo();
void Victini();
void Dragonite();
void Delphox();
void Smeargle();
void Shaymin();

//Traps
/*
	1- critical failure
	2- heavy failure
	3- expected failure
	4- resisted
	5- partial success
	6- succeed
*/
void HypnoTV();
void MCL();
void Nursery();
void PowderRoom();
void BounceChair();
void HighChair();
void PowderPath();
void ChangingRoom(bool Caretaker);
void CareChangingRoom();
void PotionChallenge();
void Presentation();
void AlarmTrap();
void PacifierDoor();
void WaterGun();
void MusicRoom();
void SleepyRoom();
void ChangeMachine();
void OddMirror();
void DimWand();
void DrainDiaper();
void BabyVG();
void DiaperVG();
void DragonVG();
void LockDoor();
void TickleMachine();
void Energy();
void BossBomb();
void Ambush();
void PlushPile();
void DiapSuit();
void CareSpecial();
void Ritual();
void ArtRoom();
void TagAlong();
void Storeroom();
void TrainPotty();
void ArmyHoard();
void SeekBottles();

//Toilet Trained
void TTKanga();
void TTMilk();
void TTLucar();
void TTGard();
void TTSerper();
void TTSlow();
void TTPrimar();
void TTLuxray();
void TTAudino();
void TTPotionChal();
void TTPresent();
void TTPaciDoor();
void TTBBomb();
void TTPowP();
void TTStoreroom();
void TTMirror();
void MusicHaunt();
void TTPotty();

//Global variables
bool looper = true;
bool check = true;
bool perPlayer = true;
bool mother = false;
bool rollUntil = false;
bool status = false;
bool aura = false;
bool forfeit = false;
bool tdForfeit = true;
int rollCount = 0;
int intput;
int intput2;
int intput3;
char charput;
int Itotal;
int UCauto = 0;
int IRauto = 0;
int FIRauto = 0;
int HCauto = 0;
int foodAuto = 0;
int drinkAuto = 0;
int HPgain = 0;
int Pwet = 0;
int Pmess = 0;
int tRoll = 0;

main()
{
	HeadMenu();

return 0;
}



//Prompt to repeat
int YesNo(){
	check = true;
   while(check == true)
   {
   	cout<<endl<<"Generate again for another player (y/n)?: ";
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
   	return 0;
   } else {
      return 1;
   }
}



//Forfeit prompt
bool Forfeit(){
	check = true;
   while(check == true)
   {
   	cout<<endl<<"Does the party forfeit to this Caretaker (y/n)?: ";
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
		tdForfeit = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
   	return false;
   } else {
      return true;
   }
}



//calculate Idle Roll Tier value
int IRTcalc(int penalty, int tier){
	int die = 1;
	int bonus = 0;
	const int LOW = 1;
	int HIGH = 1;
	time_t seconds;
	
	switch(tier){
		case -1:
			HIGH = 4;
			bonus = 0;
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		
		case 0:
			HIGH = 6;
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		
		case 1:
			HIGH = 7;
			bonus = 2;
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		
		case 2:
			HIGH = 11;
			bonus = 2;
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		
		case 3:
			HIGH = 14;
			bonus = 3;
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		
		case 4:
			HIGH = 16;
			bonus = 3;
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		
		default:
			HIGH = 20;
			bonus = 3 * (tier - 4);
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
		break;
	}
	
	return (die + bonus + penalty);
}



//Processing Use Check
void UseCheck(int UCpen, int UCtier){
	int die [2] = {1, 1};
	int bonus [2] = {1, 1};
	const int LOW = 1;
	int HIGH;
	time_t seconds;
	
	for(int i = 0; i < 2; i++)
	{	
		switch(UCtier){
		case -1:
		case 0:
			 HIGH = 4;
			time(&seconds);
			srand((unsigned int) seconds);
			die[i]=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		case 1:
			 HIGH = 7;
			time(&seconds);
			srand((unsigned int) seconds);
			die[i]=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		case 2:
			 HIGH = 8;
			 bonus[i] = 2;
			time(&seconds);
			srand((unsigned int) seconds);
			die[i]=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		case 3:
			 HIGH = 9;
			 bonus[i] = 3;
			time(&seconds);
			srand((unsigned int) seconds);
			die[i]=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		default:
			 HIGH = 10;
			 bonus[i] = 5 + 3 * (UCtier - 4);
			time(&seconds);
			srand((unsigned int) seconds);
			die[i]=(rand()%((HIGH-LOW)+LOW))+1;
		break;
		}
		
		if(i==0){sleep(1.2);}
	}

	Pwet += die[0] + UCpen + bonus[0];

	Pmess += die[1] + UCpen + bonus[0];

	if(UCtier == -1){
		Pwet *= 0.5;
		Pmess *= 0.5;
	}
}



//Prompts for UC input from player
void UCprompt()
{
	
if(UCauto != 0)
{
	cout<<endl<<"Encounter has Use Check(s). Please enter..."<<endl;
}

	check = true;
	while(check == true)
	{
	cout<<"Use Check Penalties: ";

	  cin>>intput;

	  if((cin.fail())||(intput < 0)){
		cin.clear();
		 cin.ignore();
		 cout<<"Please enter a positive integer."<<endl<<endl;
	  } else {
		check = false;
	  }
	}

	check = true;
	while(check == true)
	{
	cout<<"Enter -1 for half value base UC roll. Use Check Tiers: ";

	  cin>>intput2;

	  if((cin.fail())||(intput < -1)){
		cin.clear();
		 cin.ignore();
		 cout<<"Please enter an integer at or above -1."<<endl<<endl;
	  } else {
		check = false;
	  }
	}

if((UCauto == 0)&&(rollUntil != true)&&(rollCount == 0))
{
	check = true;
	while(check == true)
	{
	cout<<"Number of Use Checks at once: ";

	  cin>>intput3;

	  if((cin.fail())||(intput3 < 1)){
		cin.clear();
		 cin.ignore();
		 cout<<"Please enter an integer at or above 1."<<endl<<endl;
	  } else {
		check = false;
		if(intput3 > 1){
			intput2 += intput3 - 1;
		}
     }
	}
} else if(rollCount == 0){
	intput2 += UCauto - 1;
}

//if rolling indefinitely
if((rollUntil)||(rollCount > 1))
{
	cout<<endl;
	while(rollUntil)
	{
		UseCheck(intput, intput2);	
		cout<<"So far: "<<Pwet<<" WHP, "<<Pmess<<" MHP."<<endl;
		
		check = true;
	   while(check == true)
	   {
		cout<<"Continue rolling? (y/n): ";
		cin>>charput;

if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
		}
	   }

	   if((charput == 'n')||(charput == 'N')) {
		rollUntil = false;
	   }	
	}
	
	//if multi-rolling
	int rollTemp = rollCount;
	while((rollTemp > 0)&&(rollCount > 1))
	{
		if(rollTemp == rollCount){cout<<"Generation will take a moment."<<endl;}
		UseCheck(intput, intput2);
		sleep(1.7);
		rollTemp--;
	}
	if(rollCount > 1)
	{
		cout<<rollCount<<" Use Checks for a total of "<<Pwet<<" WHP and "<<Pmess<<" MHP."<<endl;
		rollCount = 0;
	}
	
} else {
	UseCheck(intput, intput2);
	if(aura)
	{
		Pwet *= 0.5;
		Pmess *= 0.5;
		aura = false;
	}
	cout<<endl<<"Use Check for values of "<<Pwet<<" WHP and "<<Pmess<<" MHP."<<endl<<endl<<endl;
}

	UCauto = 0;
	Pwet = 0;
	Pmess = 0;
	intput = 0;
	intput2 = 0;
	intput3 = 0;
	rollUntil = false;
}



//Base menus
void HeadMenu(){ 											//Main menu
	looper = true;

   while(looper == true) {
	   tdForfeit = true;
   	system("cls");

		cout<<"Welcome to the v1.1 CC defeat printout! How may I assist you today?"<<endl;
		
		
   	cout<<"Options:"<<endl;
   	cout<<"0- End program"<<endl;	
   	cout<<"1- Caretaker"<<endl;
   	cout<<"2- Trap"<<endl;
   	cout<<"3- TT Encounter"<<endl;
	cout<<"4- Roller for per-Encounter checks"<<endl;
    cout<<"5- Idle Roll Calculator"<<endl;
	cout<<"6- Forced IR Calculator"<<endl;
	cout<<"7- Use Check Roller"<<endl;
	cout<<"8- Generate a random GR"<<endl;
	cout<<"9- Generate a Caretaker"<<endl;
	cout<<"10- Generate a non-Trap diaper"<<endl;
	cout<<"11- Generate any available diaper"<<endl;
	cout<<"12- Calculate a Misfire; creates both types of rolls"<<endl;
	cout<<"13- Calculate per-turn effects"<<endl;
	cout<<"14- Calculations involving food"<<endl;
	cout<<"15- Calculate any Bomb effect"<<endl;
	cout<<endl<<"Input: ";

      	check = true;
      	while(check == true)
         {
      		cin>>intput;

            if(cin.fail()){
					cin.clear();
					cin.ignore();
               intput = 0;
               cout<<"Please enter a number.";
               getch();
               system("cls");
            } else {
             	check = false;
            }
         }

    	switch(intput){
		case 0:
         looper = false;
		 //ends program run
		break;		
		
       	case 1:
         Caretakers();
         break;

         case 2:
         Traps();
         break;

         case 3:
		 TTs();
         break;

		 case 4:
		 Encounter();
		 break;
		 
         case 5:
         IdleRolls();
         break;
		 
		 case 6:
		 ForcedIR();
		 break;
		 
		 case 7:
		 	perPlayer = true;
			while(perPlayer == true)
			{
				system("cls");
				UCprompt();
				perPlayer = YesNo();
			}
		 break;
		 
		 case 8:
			perPlayer = true;
			while(perPlayer == true)
			{
				system("cls");
				randomGR(0);
				perPlayer = YesNo();
			}
		break;

		case 9:
		cout<<endl<<"Players encounter Caretaker #"<<CareGenerator(true)<<endl;
		cout<<"Press [Enter] to return to main menu.";
		getch();
		system("cls");
		break;
		
		case 10:
		cout<<endl<<"Generated a non-Trap diaper of #"<<DiaperGenerator(false)<<endl;
		cout<<"Press [Enter] to return to main menu.";
		getch();
		system("cls");
		break;
		
		case 11:
		cout<<endl<<"Generated a diaper of #"<<DiaperGenerator(true)<<endl;
		cout<<"Press [Enter] to return to main menu.";
		getch();
		system("cls");
		break;
		
		case 12:
		cout<<endl<<"Motherless misfire: #"<<Misfire(false)<<endl;
		cout<<"Mother cast misfire of: #"<<Misfire(true)<<endl;
		cout<<"Press [Enter] to return to main menu.";
		getch();
		system("cls");
		break;
		
		case 13:
		perTurn();
		break;
		
		case 14:
		system("cls");
		foodDrink();
		break;
		
		case 15:
		system("cls");
		BombPoof();
		break;

         default:
         cout<<endl<<"Please enter a proper selection. Press [Enter] to retry.";
         getch();
         system("cls");
         break;
      }
   }

}



//Caretaker menu
void Caretakers(){
	
		system("cls");

   	check = true;
      while(check == true)
      {
		cout<<"Welcome to the caretaker menu! Please enter your roll #."<<endl;
      	cout<<"Or, to go back to the main menu, enter 0."<<endl;
		cout<<"Input: ";

      		cin>>intput;

            if(cin.fail()){
					cin.clear();
					cin.ignore();
               intput = -1;
               cout<<"Please enter a number."<<endl<<endl;
               getch();
               system("cls");
            } else {
             	check = false;
            }
         }
		 
		system("cls");

   	switch(intput){
         case 0:
         cout<<"Returning to main menu...";
         break;

       	case 1:
         Kangaskhan();
         break;

         case 2:
         Goodra();
         break;

         case 3:
         Wigglytuff();
         break;

         case 4:
         Serperior();
         break;

         case 5:
         Gardevoir();
         break;

         case 6:
         Flygon();
         break;

         case 7:
         Boss();
         break;

         case 8:
         Miltank();
         break;

         case 9:
         Primarina();
         break;

         case 10:
         Leavanny();
         break;

         case 11:
         Togekiss();
         break;

         case 12:
         Ninetales();
         break;

         case 13:
         Chansey();
         break;

         case 14:
         Salazzle();
         break;

         case 15:
         Luxray();
         break;

         case 16:
         Nidoqueen();
         break;

         case 17:
         Vaporeon();
         break;

         case 18:
         Audino();
         break;

         case 19:
         Lucario();
         break;

         case 20:
         Ampharos();
         break;

         case 21:
         Ivysaur();
         break;

         case 22:
         Slowpoke();
         break;

         case 23:
         Snorlax();
         break;

         case 24:
         Mew();
         break;

         case 25:
         Galvantula();
         break;

         case 26:
         Ursaring();
         break;

         case 27:
         AlakazamPac();
         break;

         case 28:
      	AlakazamSpo();
         break;

         case 29:
         Victini();
         break;

         case 30:
         Dragonite();
         break;

         case 31:
         Delphox();
         break;

         case 32:
         Smeargle();
         break;

         case 33:
         Shaymin();
         break;

         default:
         cout<<"Please input a proper number from 1-33."<<endl;
         getch();
         system("cls");
         break;
      }
}



//Trap Menu
void Traps(){
	system("cls");

   	check = true;
      while(check == true)
      {
		cout<<"Engaging trap number. Please enter your roll #."<<endl;
      	cout<<"Or, to go back to the main menu, enter 0."<<endl;
		cout<<"Input: ";

      		cin>>intput;

            if(cin.fail()){
					cin.clear();
					cin.ignore();
               intput = -1;
               cout<<"Please enter a number."<<endl<<endl;
               getch();
               system("cls");
            } else {
             	check = false;
            }
      }
	
	switch(intput){
		case 0:
		cout<<"Returning to main menu..."<<endl;
		break;

		case 1:
		HypnoTV();
		break;
		
		case 2:
		MCL();
		break;
		
		case 3:
		Nursery();
		break;
		
		case 4:
		PowderRoom();
		break;
		
		case 5:
		BounceChair();
		break;
		
		case 6:
		HighChair();
		break;
		
		case 7:
		PowderPath();
		break;
		
		case 8:
		ChangingRoom(false);
		break;
		
		case 9:
		CareChangingRoom();
		break;
		
		case 10:
		PotionChallenge();
		break;
		
		case 11:
		Presentation();
		break;
		
		case 12:
		AlarmTrap();
		break;
		
		case 13:
		PacifierDoor();
		break;
		
		case 14:
		WaterGun();
		break;
		
		case 15:
		MusicRoom();
		break;
		
		case 16:
		SleepyRoom();
		break;
		
		case 17:
		ChangeMachine();
		break;
		
		case 18:
		OddMirror();
		break;
		
		case 19:
		DimWand();
		break;
		
		case 20:
		DrainDiaper();
		break;
		
		case 21:
		BabyVG();
		break;
		
		case 22:
		DiaperVG();
		break;
		
		case 23:
		DragonVG();
		break;
		
		case 24:
		LockDoor();
		break;
		
		case 25:
		TickleMachine();
		break;
		
		case 26:
		Energy();
		break;
		
		case 27:
		BossBomb();
		break;
		
		case 28:
		Ambush();
		break;
		
		case 29:
		PlushPile();
		break;
		
		case 30:
		DiapSuit();
		break;
		
		case 31:
		CareSpecial();
		break;
		
		case 32:
		Ritual();
		break;
		
		case 33:
		ArtRoom();
		break;
		
		case 34:
		TagAlong();
		break;
		
		case 35:
		Storeroom();
		break;
		
		case 36:
		TrainPotty();
		break;
		
		case 37:
		ArmyHoard();
		break;
		
		case 38:
		SeekBottles();
		break;
		
		default:
        cout<<"Please input a proper number from 1-38."<<endl;
        getch();
        system("cls");
		break;
	}
}



//TT Menu
void TTs(){
	time_t seconds;
	const int LOW = 1;
	int HIGH = 9;
	int die = 1;
	
	check = true;
	while(check){
		system("cls");
		cout<<"Welcome to the Toilet Trained Encounter menu! Please enter your roll #."<<endl;
		cout<<"Or, to go back to the main menu, enter 0."<<endl;
	
		cin>>intput;

            if(cin.fail()){
				cin.clear();
				cin.ignore();
               intput = -1;
               cout<<"Please enter a number."<<endl<<endl;
               getch();
               system("cls");
            } else {
             	check = false;
            }
	}
	
	switch(intput){
		case 0:
		cout<<"Returning to main menu..."<<endl;
		break;
		
		case 1:
		TTKanga();
		break;
		
		case 2:
		TTMilk();
		break;
		
		case 3:
		TTLucar();
		break;
		
		case 4:
		TTGard();
		break;
		
		case 5:
		TTSerper();
		break;
		
		case 6:
		TTSlow();
		break;
		
		case 7:
		TTPrimar();
		break;
		
		case 8:
		TTLuxray();
		break;
		
		case 9:
		TTAudino();
		break;
		
		case 10:
		TTPotionChal();
		break;
		
		case 11:
		TTPresent();
		break;
		
		case 12:
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
			
			system("cls");
			cout<<"TT ALARM TRAP"<<endl;
			cout<<"Party encounters TT Caretaker #"<<die<<" with +1 AR/damage for 3 turns."<<endl;			
		break;
		
		case 13:
		TTPaciDoor();
		break;
		
		case 14:
		TTBBomb();
		break;

		case 15:
		TTPowP();
		break;
		
		case 16:
		TTStoreroom();
		break;
		
		case 17:
		TTMirror();
		break;
		
		case 18:
		MusicHaunt();
		break;
		
		case 19:
		TTPotty();
		break;
		
		default:
		cout<<"Please input a proper number from 0-19. Press [Enter] to return to main menu."<<endl;
        getch();
        system("cls");
		break;
	}

}



//Roller for per-Encounter checks
void Encounter(){
	int placeholder;
	bool babble = false;
	bool change = false;
	bool stumble = false;
	bool sleepy = false;
	int bottle;
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"Welcome to the per-Encounter roller!"<<endl<<endl;
	cout<<"Now generating calculations";
	
	placeholder = Die100();
	if(placeholder > 50)
	{
		babble = true;
	}
	cout<<".";
	
	sleep(1.2);
	placeholder = Die100();
	if(placeholder > 50)
	{
		change = true;
	}
	
	cout<<".";
	sleep(1.3);
	placeholder = Die100();
	if(placeholder <= 30)
	{
		stumble = true;
	}
	
	cout<<".";
	sleep(1.4);
	placeholder = Die20();
	if(placeholder > 10)
	{
		sleepy = true;
	}
	
	cout<<".";
	sleep(1.5);
	bottle = Die4();
	bottle+= 2;
	
	cout<<"done"<<endl<<endl;
	
	cout<<"Player drinks "<<bottle<<" WHP from an Auto-Bottle, if applicable."<<endl;
	cout<<"Mantra makes party gain 10 RB (activates once per player with Mantra."<<endl;
	cout<<"Lisp inflicts 1 RB if they speak."<<endl;
	cout<<"Vocab Regression inflicts 3 RB if they speak."<<endl<<endl;
	if(babble)
	{
		cout<<"Player babbles uncontrollably. 3 RB gained."<<endl;
	}
	if(change)
	{
		cout<<"Any players who try to change this player forget how to, for this player."<<endl;
	}
	if(stumble)
	{
		cout<<"Player stumbles and falls onto their butt. Inflicts 2 RB, or 4 RB if their diaper is messy or Crinkly."<<endl;
	}
	if(sleepy)
	{
		cout<<"Player gains Sleepy lv. 1, if wearing a Sleepy diaper."<<endl;
	}
	if((!sleepy)&&(!stumble)&&(!change)&&(!babble))
	{
		cout<<"No additional effects occur."<<endl;
	}
	
	perPlayer = YesNo();
}
}



//Idle Roll Machine
void IdleRolls(){
	int wet = 0;
	int mess = 0;
	int HP = 0;
	int UCtier = 0;
	int UCpen = 0;
	int penalty = 0;
	int tier = 0;
	int rolls = 0;
	int total = 0;
	int bottle = 0;
	bool pacifier = false;
	bool magic = false;
	bool squisher = false;
	bool stumble = false;
	bool babble = false;
	bool suckler = false;
	bool change = false;
	bool assistant = false;
	bool repeat = true;
	const int LOW = 1;
	int HIGH = 10;
	time_t seconds;
	
	if(IRauto != 0)
	{
	mother = true;
	}

while(repeat)
{
	
if(mother == false)
{
system("cls");

//receive input   
	cout<<"Welcome to the Idle Roll calculator! Please enter..."<<endl<<endl;
} else {
	cout<<"Encounter has Idle Roll(s). Please enter..."<<endl<<endl;
}

   check = true;
   while(check == true)
   {
   	cout<<"Wet level: ";

      cin>>wet;

      if((cin.fail())||(wet > 7)||(wet < 0)){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter an integer between 0 and 7."<<endl<<endl;
      } else {
      	check = false;
      }
   }
   
//sneak HP calculation
	HIGH = 100;
	time(&seconds);
	srand((unsigned int) seconds);
	HP=((rand()%((HIGH-LOW)+LOW))+1)/50+1;

   check = true;
   while(check == true)
   {
   	cout<<"Mess level: ";

      cin>>mess;

      if((cin.fail())||(mess > 7)||(mess < 0)){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter an integer between 0 and 7."<<endl<<endl;
      } else {
      	check = false;
      }
   }

      check = true;
   while(check == true)
   {
   	cout<<"Idle Roll Penalties: ";

      cin>>penalty;

      if(cin.fail()){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter a number."<<endl<<endl;
      } else {
      	check = false;
      }
   }

   check = true;
   while(check == true)
   {
   	cout<<"Idle Roll Tiers: ";

      cin>>tier;

      if((cin.fail())||(tier < -1)){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter an integer at or above -1."<<endl<<endl;
      } else {
      	check = false;
      }
   }

if(mother == false)
{
   check = true;
   while(check == true)
   {
   	cout<<"Number of Idle Rolls being made (1 if only one roll, otherwise whatever the Encounter says): ";

      cin>>rolls;

      if((cin.fail())||(rolls < 1)){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter a positive integer."<<endl<<endl;
      } else {
      	check = false;
      }
   }
}
   
   check = true;
   while(check == true)
   {
   	cout<<"Use Check Penalties: ";

      cin>>UCpen;

      if((cin.fail())||(UCpen < 0)){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter a positive integer."<<endl<<endl;
      } else {
      	check = false;
      }
   }
   
   check = true;
   while(check == true)
   {
   	cout<<"Enter -1 for half value base UC roll. Use Check Tiers: ";

      cin>>UCtier;

      if((cin.fail())||(UCtier < -1)){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter an integer at or above -1."<<endl<<endl;
      } else {
      	check = false;
      }
   }

if((mother == false)||(status == true))
{
system("cls");
cout<<"Calculating..."<<endl;
} else {
cout<<"Loading...";
}

   
//Process diaper use
	switch(wet){
   	case 0:
      break;

      case 1:
      penalty++;
      break;

      case 2:
      penalty += 2;
      break;

      case 3:
      penalty += 3;
      tier++;
      break;

      case 4:
      penalty += 4;
      tier += 2;
      break;

      case 5:
      penalty += 5;
      tier += 2;
      break;

      case 6:
      penalty += 7;
      tier += 3;
      break;

      case 7:
      penalty += 10;
      tier += 4;
      break;

      default:
	  wet = 0;
      cout<<"Defaulting to 0 use."<<endl;
      break;
   }

	switch(mess){
   	case 0:
      break;

      case 1:
      penalty += 2;
      break;

      case 2:
      penalty += 3;
      tier++;
      break;

      case 3:
      penalty += 4;
      tier += 2;
      break;

      case 4:
      penalty += 5;
      tier += 2;
      break;

      case 5:
      penalty += 7;
      tier += 3;
      break;

      case 6:
      penalty += 10;
      tier += 4;
      break;

      case 7:
      penalty += 15;
      tier += 5;
      break;

      default:
      mess = 0;
      cout<<"Defaulting to 0 use."<<endl;
      break;
   }

	tier += rolls - 1;
	UCtier += rolls - 1;

	
//calculate Idle Roll
	int die = 1;
	int bonus = 0;
	
	total = IRTcalc(penalty, tier);

	sleep(1.5);
  
if((mother == false)||(status == true))
{
   cout<<"Idle Roll done"<<endl;
}
   
   
//calculate Use Checks
	UseCheck(UCpen, UCtier);
if((mother == false)||(status == true))
{
	cout<<"Use Check done"<<endl;
}

	sleep(1.2);
	HIGH = 4;
	time(&seconds);
   	srand((unsigned int) seconds);
   	bottle=(rand()%((HIGH-LOW)+LOW))+1;
	
	bottle += 2;
	sleep(1.2);
	
if((mother == false)||(status == true))
{
//Boolean status printout calculations
    HIGH = 20;
		
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		pacifier = true;
	}
	sleep(1.6);
	
	time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		magic = true;
	}
	sleep(1.6);
	cout<<"Pacifiers done"<<endl;
	
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		squisher = true;
	}
	sleep(1.7);

    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		babble = true;
	}
	sleep(1.6);
	
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		suckler = true;
	}
	sleep(1.7);
	cout<<"Almost finished!";
	
	HIGH = 100;
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die < 31) {
		stumble = true;
	}
	sleep(1.8);
	
	HIGH = 100;
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die < 26)
	{
		assistant = true;
	}
	sleep(1.3);
	
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die < 51) {
		change = true;
	}
	
	system("cls");
} else {
	cout<<"done"<<endl<<endl;
}
   
//Print results
	cout<<"Idle Roll for a total of "<<total<<" point(s)."<<endl;
	cout<<"Use Check for a total of "<<Pwet<<" WHP and "<<Pmess<<" MHP."<<endl;
	cout<<"Player regains "<<HP<<" HP, or "<<(HP + 2)<<" if they used a pacifier this Idle Roll."<<endl;
	cout<<"Player drinks "<<bottle<<" WHP from bottle (if applicable)."<<endl;
	cout<<"Toy Blocks diaper makes player gain 10 RB before any other effect (if applicable)."<<endl;
if((mother == false)||(status == true))
{
	cout<<"Statuses (if applicable, or any):"<<endl<<endl;
	
	if(suckler) {
		cout<<"Suckler will activate; player cannot remove their pacifier if they have Suckler."<<endl;
	}
	
	if((magic)&&(pacifier))
	{
		cout<<"Player gains up to 2 Pacifier levels (normal + if they have Magic Pacifier)."<<endl;
	} else if(pacifier) {
		cout<<"Player gains 1 Pacifier level from normal Pacifier Checks, if using a pacifier."<<endl;
	} else if(magic) {
		cout<<"Player gains 1 Pacifier level if they have Magic Pacifier."<<endl;
	} else {
		cout<<"Player gains no Pacifier levels."<<endl;
	}
	
	if(stumble) {
		cout<<"If player has Clumsy: Player stumbles. +2 RB or +4 RB if messy or Crinkly Diaper."<<endl;
	}
	
	if(babble) {
		cout<<"If player has Babbler: Player babbles. +3 RB."<<endl;
	}
	
	if(change){
		cout<<"If an ally has Changeless: this player forgets how to change diapers for an Idle Roll."<<endl;
	}
	if(assistant){
		cout<<"If player has Assistant: Player gains Advocate for 1 IR, if they hadn't last Idle Roll."<<endl;
	}
	
	if(!(magic)&&!(pacifier)&&!(suckler)&&!(stumble)&&!(babble)&&!(change)&&!(assistant)) {
		cout<<"Player suffers no Idle Roll specific effects."<<endl;
	}
	
}

cout<<"Press [Enter] to continue."<<endl<<endl;
penalty = 0;
Pwet = 0;
Pmess = 0;
tier = 0;
UCtier = 0;
getch();

if(mother)
{
	repeat = false;
} else {

repeat = YesNo();
}

}
	IRauto = 0;
	mother = false;
	status = false;

}


//Forced Idle Roll machine
void ForcedIR(){
	int wet = 0;
	int mess = 0;
	int formWet = 0;
	int formMess = 0;
	int penalty = 0;
	int tier = 0;
	int rolls = 0;
	int total = 0;
	bool repeat = true;
	bool type = false; //if type is true, then diaper use FIR. If false, then other FIR.

while(repeat)
{
system("cls");

	if(FIRauto)
	{
		mother = true;
	}

if(mother == false)
{  
	cout<<"Welcome to the Forced IR calculator!"<<endl<<endl;
	
	//receive input 
	check = true;
	while(check == true)
	{	
		cout<<"Is this a diaper use FIR (y/n)? ";
		cin>>charput;
		
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
		}
	}

	   if((charput == 'n')||(charput == 'N')) {
		type = false;
	   } else if((charput == 'y')||(charput == 'Y')) {
		  type = true;
	   } else {
		  check = true;
	   }
   
} else {
	cout<<"Encounter has Forced Idle Roll(s). Please input..."<<endl<<endl;
	type = false;
}
	
	if(type)
	{
	   check = true;
	   while(check == true)
	   {
		cout<<"Old wet level: ";

		  cin>>formWet;

		  if((cin.fail())||(formWet > 6)||(formWet < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer between 0 and 6."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }		
	}	
	   check = true;
	   while(check == true)
	   {
		cout<<"Current wet level: ";

		  cin>>wet;

		  if((cin.fail())||(wet > 7)||(wet < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer between 0 and 7."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }
	   
	if(type)
	{
	   check = true;
	   while(check == true)
	   {
		cout<<"Old mess level: ";

		  cin>>formMess;

		  if((cin.fail())||(formMess > 6)||(formMess < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer between 0 and 6."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }
	}

	   check = true;
	   while(check == true)
	   {
		cout<<"Current mess level: ";

		  cin>>mess;

		  if((cin.fail())||(mess > 7)||(mess < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer between 0 and 7."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }

   check = true;
   while(check == true)
   {
   	cout<<"Idle Roll Tiers: ";

      cin>>tier;

      if((cin.fail())||(tier < -1)){
      	cin.clear();
         cin.ignore();
         cout<<"Please enter an integer at or above -1."<<endl<<endl;
      } else {
      	check = false;
      }
   }
   
if(mother != true)
{
	system("cls");
} else {
	cout<<endl;
}


//Generate bonus Tiers from multi-level diaper use
if(type)
{
	if(formWet < wet)
	{
		if((formWet == 0)&&(wet != 0))
		{
			tier = (wet - 1) + mess - formMess - 1; 
		} else {
			tier = wet - formWet + mess - formMess - 1;
		}
	}
}

   
//Process diaper use level
	switch(wet){
   	case 0:
      break;

      case 1:
      penalty++;
      break;

      case 2:
      penalty += 2;
      break;

      case 3:
      penalty += 3;
      tier++;
      break;

      case 4:
      penalty += 4;
      tier += 2;
      break;

      case 5:
      penalty += 5;
      tier += 2;
      break;

      case 6:
      penalty += 7;
      tier += 3;
      break;

      case 7:
      penalty += 10;
      tier += 4;
      break;

      default:
      cout<<"ERROR"<<endl;
      break;
   }

	switch(mess){
   	case 0:
      break;

      case 1:
      penalty += 2;
      break;

      case 2:
      penalty += 3;
      tier++;
      break;

      case 3:
      penalty += 4;
      tier += 2;
      break;

      case 4:
      penalty += 5;
      tier += 2;
      break;

      case 5:
      penalty += 7;
      tier += 3;
      break;

      case 6:
      penalty += 10;
      tier += 4;
      break;

      case 7:
      penalty += 15;
      tier += 5;
      break;

      default:
      cout<<"ERROR"<<endl;
      break;
   }
   
	
//calculate Idle Roll
	int die = 1;
	int bonus = 0;
	const int LOW = 1;
	int HIGH = 1;
	time_t seconds;
	
	switch(tier)
   {
   	case -1:
         HIGH = 4;
		 //no bonus
      	time(&seconds);
   		srand((unsigned int) seconds);
   		die=(rand()%((HIGH-LOW)+LOW))+1;
	break;
	
   	case 0:
         HIGH = 6;
		 //no bonus
      	time(&seconds);
   		srand((unsigned int) seconds);
   		die=(rand()%((HIGH-LOW)+LOW))+1;
	break;	
	
	case 1:
         HIGH = 7;
		 bonus = 2;
      	time(&seconds);
   		srand((unsigned int) seconds);
   		die=(rand()%((HIGH-LOW)+LOW))+1;
	break;
	
	case 2:
         HIGH = 11;
		 bonus = 1;
      	time(&seconds);
   		srand((unsigned int) seconds);
   		die=(rand()%((HIGH-LOW)+LOW))+1;
	break;
	
	case 3:
         HIGH = 13;
		 bonus = 2;
      	time(&seconds);
   		srand((unsigned int) seconds);
   		die=(rand()%((HIGH-LOW)+LOW))+1;
	break;
	
	case 4:
		 HIGH = 16;
		 bonus = 4;
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
	break;
	
	default:
		 HIGH = 20;
		 bonus = 3 * (tier - 4);
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
	break;
   }
   
   total = die + penalty + bonus;
   
//Print results
	cout<<"Forced IR for a total of "<<total<<" RB."<<endl;
if(mother == false)
{
	if(formWet > wet)
	{
		cout<<"Wet diaper levels were not input properly. ";
	} else if(type){
		cout<<(wet - formWet)<<" WUL gained. ";
	}
	if(formMess > mess) {
		cout<<"Mess diaper levels were not input properly.";
	} else if(type){
		cout<<(mess - formMess)<<" MUL gained.";
	}
	
} else {
	cout<<"Press [Enter] to return to Encounter."<<endl;
}

getch();

	if(FIRauto)
	{
		FIRauto = 0;
		repeat = false;
	} else {
		repeat = YesNo();
	}
	
	total = 0;
	tier = 0;
	penalty = 0;
	bonus = 0;
}
	mother = false;
}



//Rolling a d3
int Die3(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 3;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//Rolling a d4
int Die4(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 4;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//Rolling a d5
int Die5(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 5;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//Rolling a d6
int Die6(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 6;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//Rolling a d7
int Die7(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 7;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//Rolling a d10
int Die10(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 10;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//Rolling a d20
int Die20(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 20;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//Rolling a d100
int Die100(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 100;

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
   die=(rand()%((HIGH-LOW)+LOW))+1;

   return die;
}



//bomb effect generation
void BombPoof(){
	int style = 0;
	int hit = 0;
	int damage = 0;
	int seesaw = 0;
	string name;
	char effect = 'X';
	int points = 0;
	perPlayer = true;
	
while(perPlayer){
	
		check = true;
	while(check == true)
	{
		system("cls");
		cout<<"Welcome to the bomb calculator. Please enter bomb style. (Calculations may take some time for RNG)"<<endl;
		cout<<"1- Vanilla"<<endl<<"2- Powder"<<endl<<"3- Fruity"<<endl<<"4- Fill"<<endl<<"5- Silly"<<endl<<"6- Sleepy"<<endl;
		cout<<"Input: ";
		
		cin>>style;

		if((cin.fail())||(style < 1)||(style > 6)){
			cin.clear();
			cin.ignore();
			style = 0;
			cout<<"Please enter an integer between 1 and 6"<<endl<<endl;
			getch();
			system("cls");
		} else {
			check = false;
		}
	}
   
	if(style >3)
	{
			check = true;
		while(check == true)
	   {
			cout<<"Please input critical seesaw value: ";
			
			cin>>seesaw;

		if((cin.fail())||(seesaw < 0)){
			cin.clear();
			cin.ignore();
			intput = 0;
			cout<<"Please enter an integer valued at least 0"<<endl<<endl;
			getch();
		} else {
			check = false;
			if(seesaw > 4){ seesaw = 5;
			} else { seesaw++; }
		}
	   }
	}
	
		check = true;
	while(check == true)
	{
		cout<<"If the roll is random, enter 0. Else, enter the bomb roll: ";
		
		cin>>hit;

		if((cin.fail())||(hit < 0)||(hit > 20)){
			cin.clear();
			cin.ignore();
			style = 0;
			cout<<"Please enter an integer between 0 and 20"<<endl<<endl;
			getch();
			system("cls");
		} else {
			check = false;
		}
	
	}
	   
	if(hit == 0){ hit = Die20(); sleep(1.2); }
	   
	cout<<"-----"<<endl;
	
	switch(style)
	{
		case 1:
		name = "Vanilla";
		effect = 'M';
		break;
		
		case 2:
		name = "Powder";
		effect = 'E';
		break;
		
		case 3:
		name = "Fruity";
		effect = 'B';
		break;
		
		case 4:
		name = "Fill";
		effect = 'F';
		break;
		
		case 5:
		name = "Silly";
		effect = 'S';
		break;
		
		case 6:
		name = "Sleepy";
		effect = 'l';
		break;
		
		default:
		name = "Error";
		effect = 'X';
		break;
	}
	
	//print out effects
	cout<<name<<" goes off for ";
	
		//Vanilla, Powder, and Fruity
	if(style<4){
	
			//use points variable to calculate 50/50 for Powder Bomb's Enhancement
		if((effect == 'E')&&(hit<=15)){
			
			sleep(1.3);
			points = Die20();
			
			if(points <= 10){
				points = 1;
			} else {
				points = 2;
			}
		
			cout<<"a Use Check, ";
	
			if(points == 1){
				cout<<"1 stack of Enhancement, ";
				points = 0;
			}
		}
		
			//if full hit
		if(hit <= 10){
			for(int i = 0; i < 3; i++)
			{
				points += Die4();
				sleep(1.3);
			}
			damage = Die6();
			
			//if partial hit
		} else if(hit<=15){
			for(int i = 0; i < 2; i++)
			{
				points += points + Die4();
				sleep(1.2);
			}
			damage = Die3();
			
			//if missed
		} else{
			cout<<"no effect."<<endl;
		}
		
		if(hit<= 15){
			cout<<(points/2)<<" RB gained, "<<points<<" "<<effect<<"P gained, and "<<damage<<" damage dealt."<<endl;
			
			if(effect == 'E')
			{
				cout<<"Press [Enter] to roll for the Use Check."<<endl<<endl;
				getch();
				UCauto = 1;
				UCprompt();
			}
		}
		
	
		//Fill Bomb
	} else if(style == 4)
	{
		if(hit <= seesaw)
		{
			points = 15;
		} else if(hit <= 5){
			for(int i = 0; i < 4; i++)
			{
				points += Die3();
				if(i != 3){ sleep(1.2); }
			}
		} else if(hit <= 10){
			for(int i = 0; i < 2; i++)
			{
				points += Die6();
				if(i != 1){ sleep(1.2); }
			}
		} else if(hit <= 15){
			for(int i = 0; i < 2; i++)
			{
				points += Die3();
				if(i != 1){ sleep(1.2); }
			}
		}

		if (hit > 15){
			cout<<"no effect"<<endl;
		} else {
			cout<<points<<" UHP, 1 stack of Hold Helper, and ";
			
			damage = Die6();
			
			cout<<damage<< " damage dealt."<<endl;
			
		}
		
		//Silly Bomb
	} else if(style == 5)
	{	

		damage = Die6();

		if(hit <= seesaw)
		{
			cout<<"Silly lv. 2 and "<<damage<<" damage dealt."<<endl;
		} else if (hit <= 10){
			cout<<"Silly lv. 1 and "<<damage<<" damage dealt."<<endl;
		} else {
			cout<<"no effect."<<endl;
		}
		
		//Sleepy Bomb
	} else if(style == 6)
	{
		damage = Die20();
		
		if(damage <= 10){
			damage = 1;
		} else {
			damage = 2;
		}
		
		if(hit <= seesaw)
		{
			cout<<"Sleepy lv. 3 and "<<damage<<" damage dealt."<<endl;
		} else if(hit <=5){
			cout<<"Sleepy lv. 2 and "<<damage<<" damage dealt."<<endl;
		} else if(hit<=10){
			cout<<"Sleepy lv. 1 and "<<damage<<" damage dealt."<<endl;
		} else {
			cout<<"no effect."<<endl;
		}
		
		//bugged out
	} else {
		cout<<"ERROR"<<endl;
	}
	
	if(mother)
	{
		perPlayer = false;
	} else {
		perPlayer = YesNo();
		system("cls");
	}

	points = 0;
	style = 0;	
}
}



//Generating Intensity Tier roll
int Intensity(int base){
	int input;
	int points;
	int dieRoll;

   check = true;
	while(check == true)
   {
		cout<<endl<<"Please input Intensity Tier bonus: ";
		cin>>input;

   	if((cin.fail())||(input < 0)){
   		cin.clear();
      	cin.ignore();
      	input = 0;
      	cout<<"Please enter a positive integer."<<endl<<endl;
      	getch();
   	} else {
   		check = false;
		cout<<endl;
   	}
   }

   dieRoll = Die10();
   points = (base + input) * 10 + dieRoll;

   return points;
}



//Generate a random Ghost Regression
void randomGR(int lock) {
	/*lock values:
	0- empty, prompts for inputs
	1- any random
	2- mental exclusive
	3- body or equipment exclusive
	*/
	
	int die = 1;
	int LOW = 1;
	int HIGH = 10;
	time_t seconds;
	
if(lock == 0)
{
	cout<<"Welcome to the random Ghost Regression generator!"<<endl<<endl;
	
	check = true;


	while(check == true)
	{
	cout<<"Any random GR? (y/n): ";
	
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
	   lock = 0;
   } else {
	   lock = 1;
   }
}
   
if(lock == 0)
{	
	check = true;
   
   	while(check == true)
	{
	cout<<"Exclusively mental? (y/n): ";
	
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
	   cout<<"Defaulting to body and equipment Ghost Regressions."<<endl;
	   lock = 3;
   } else {
	   lock = 2;
   }
}

   
   switch(lock) {
	   case 0:
	   cout<<"ERROR. Lock trapped at 0 value for unknown reason."<<endl;
	   HIGH = 2;
	   break;
	   
	   case 1:
	   //LOW unchanged
	   HIGH = 29;
	   break;
	   
	   case 2:
	   //LOW unchanged
	   HIGH = 11;
	   break;
	   
	   case 3:
		//Add 11 to value to simulate rolling 12-27
	   HIGH = 16;
	   break;
	   
	   default:
	   HIGH = 2;
	   cout<<"ERROR. Unknown Lock value."<<endl;
   }

//roll for Ghost Regressions according to specifications   
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(lock == 3){ die += 11; }
	
	cout<<"Player receives Ghost Regression: "<<die<<" ";
	
	switch(die) {
		//Mental
		case 1:
		cout<<"Drooling";
		break;
		
		case 2:
		cout<<"Lisp";
		break;
		
		case 3:
		cout<<"Vocab Regression";
		break;
		
		case 4:
		cout<<"Babbler";
		break;
		
		case 5:
		cout<<"Baby Logic";
		break;
		
		case 6:
		cout<<"Diaper Trained";
		break;
		
		case 7:
		cout<<"Squisher";
		break;
		
		case 8:
		cout<<"Enjoyer";
		break;
		
		case 9:
		cout<<"Changeless";
		break;
		
		case 10:
		cout<<"Giggly";
		break;
		
		case 11:
		cout<<"Immature";
		break;
		
		//Body
		case 12:
		cout<<"Baby Fat, Obese, or Blobish (stacks)";
		break;
		
		case 13:
		cout<<"Thumb Suckler";
		break;
		
		case 14:
		cout<<"Quick Filler";
		break;
		
		case 15:
		cout<<"Strong Filler";
		break;
		
		case 16:
		cout<<"Clumsy";
		break;
		
		case 17:
		cout<<"Bad Grip";
		break;
		
		case 18:
		cout<<"Pinkified OR Powdered (choice)";
		break;
		
		case 19:
		cout<<"Girly";
		break;
		
		case 20:
		cout<<"Suckler";
		break;
		
		//Equipment
		case 21:
		cout<<"Plasticified, Foamified, OR Rattle'd (stacks)";
		break;
		
		case 22:
		cout<<"Crinkly Diaper";
		break;
		
		case 23:
		cout<<"Poofy Diaper OR Extra Poof (stacks)";
		break;
		
		case 24:
		cout<<"Baby Clothes";
		break;
		
		case 25:
		cout<<"Frilly Clothes";
		break;
		
		case 26:
		cout<<"Baby Bib";
		break;
		
		case 27:
		cout<<"Diaper Suit/Onesie (choice)";
		break;
		
		case 28:
		cout<<"Devolution";
		break;
		
		case 29:
		cout<<"Assistant";
		
		default:
		cout<<"ERROR. GENERATION FAILED";
	}
	
	cout<<"."<<endl;
}



//Trap roll generator
int TrapRoll(){
	/*returning values
	1- critical failure
	2- heavy failure
	3- expected failure
	4- resisted
	5- partial success
	6- succeed
	*/
	
	int placeholder = 0;
	int seesaw = 0;
	bool disadvan = false;
	bool weapons = false;
	bool advocate = false;
	int die = 1;
	const int LOW = 1;
	const int HIGH = 20;
	time_t seconds;
	
	check = true;
   	while(check == true)
	{
	cout<<endl<<"Disadvantage on traps? (y/n): ";
	
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
	   disadvan = false;
   } else {
	   disadvan = true;
   }
   
	check = true;
   	while(check == true)
	{
	cout<<"Weapons diaper? (y/n): ";
	
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
	   weapons = false;
   } else {
	   weapons = true;
   }
   
	check = true;
   	while(check == true)
	{
	cout<<"Does the player have Advocate? (y/n): ";
	
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
	   advocate = false;
   } else {
	   advocate = true;
   }
   
	check = true;
   	while(check == true)
	{
	cout<<"Critical seesaw bonus: ";
	
   	cin>>seesaw;

   	if((cin.fail())||(intput < 0)){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a positive integer from 1-5. "<<endl;
   	} else {
   		check = false;
		if(seesaw > 4)
		{
			seesaw = 5;
		} else {
			seesaw++;
		}
   	}
   }
   
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(disadvan){
		sleep(1.7);
		time(&seconds);
		srand((unsigned int) seconds);
		placeholder=(rand()%((HIGH-LOW)+LOW))+1;
		
		if(placeholder < die){
			die = placeholder;
		}
	}
	
	if(die <= seesaw) {
		cout<<"Critical Failure."<<endl<<endl;
		return 1;
	} else if(die <= 5){
		cout<<"Heavy Failure."<<endl<<endl;
		return 2;
	} else if((die <= 10)||((die <= 15)&&(advocate))||((die <= 19)&&(advocate)&&(weapons))) {
		cout<<"Expected Failure."<<endl<<endl;
		return 3;
	} else if((die <= 15)||((die <= 19)&&(weapons))) {
		cout<<"Resist."<<endl<<endl;
		return 4;
	} else if(die <= 19) {
		cout<<"Partial Success."<<endl<<endl;
		return 5;
	} else {
		cout<<"Full Success."<<endl<<endl;
		return 6;
	}
}



//Generate a random Caretaker
int CareGenerator(bool Caring){
	time_t seconds;
	const int LOW = 1;
	int HIGH = 32;
    int die = 1;
	
	if(Caring)
	{
		HIGH = 33;
	}
	
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return die;
}



int DiaperGenerator(bool Traps){
	const int LOW = 1;
	int HIGH = 20;
	int die = 1;
	time_t seconds;
	
	if(Traps)
	{
		HIGH = 31;
	}
	
	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return die;
}



int TrapArtist(){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 10;
	time_t seconds;
	
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return die;
}



int Misfire(bool Caring){
	int die = 1;
	const int LOW = 1;
	int HIGH = 25;
	time_t seconds;
	
	if(Caring)
	{
		HIGH = 30;
	}
	
	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return die;
}



void perTurn(){
	int dice;
//player-based turn effects
	bool lazy = false; //25% chance to miss this turn
	bool stumble = false; //30% chance to stumble after attack
	bool grip = false; // 25% chance to drop weapon
	bool slow = false; //50% chance of Slow, if Slowpoke Diaper
	bool vibrate = false; //10% of missing this turn from pleasure, if Enjoyer and Vibrating Diaper
	bool baby = false; //Pacifier Checks every turn, before attacking, if Baby Diaper
	bool supergrip = false; //for protected paws and bad grip stacking
	
//mother-based turn effects
	bool aroma = false; //Pacifier Check, 2 if pacifier
	bool extraPC = false; //Pacifier Check for "if pacifier" auras; for Aroma and Paci-Pop
	int wetAura = 0;
	int messAura = 0;
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"Welcome to the per-turn results generator! (Warning: this may take a bit)"<<endl;
	
	cout<<"Now generating";
	
	dice = Die100();
	//bad grip
	if(dice <= 25)
	{
		grip = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die100();
	//stacking protected paws and bad grip
	if(dice <= 50)
	{
		supergrip = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die100();
	//lazy
	if(dice <= 25)
	{
		lazy = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die100();
	
	//stumble
	if(dice <= 30)
	{
		stumble = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die100();
	//slowpoke diaper
	if(dice <= 50)
	{
		slow = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die100();
	//vibrating diaper turn loss
	if(dice <= 25)
	{
		vibrate = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die20();
	//baby diaper
	if(dice > 10)
	{
		baby = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die20();
	//aroma
	if(dice > 10)
	{
		aroma = true;
	}
	cout<<".";
	sleep(1.2);
	
	dice = Die20();
	//aroma and paci-pop's "if pacifier" roll
	if(dice > 10)
	{
		extraPC = true;
	}
	
	
//print out results
	system("cls");
	cout<<"Results, from player sources:"<<endl<<endl;
	if(supergrip){
		cout<<"If Protected Paws AND Bad Grip, player drops weapon.";
	}
	if(grip){
		cout<<"If Protected Paws OR Bad Grip, player drops weapon.";
	}
	if((supergrip)||(grip)){
		cout<<" Player gains 5 RB if Paw Protection."<<endl;
	}
	if(stumble){
		cout<<"If player is Clumsy, they trip onto their butt after attacking, gaining 2 RB if clean or 4 RB if messy/Crinkly."<<endl;
	}
	if(lazy){
		cout<<"If Lazy, player misses turn."<<endl;
	}
	if(vibrate){
		cout<<"If player wears Vibrating Diaper and has Enjoyer (not GR), player loses turn."<<endl;
	}
	if(slow){
		cout<<"If player wears Slowpoke Diaper, they lose next turn to Slow."<<endl;
	}
	if(baby){
		cout<<"If player wears Baby Diaper, they failed a Pacifier Check."<<endl;
	}
	
cout<<endl<<"From mother sources:"<<endl<<endl;
	if(extraPC){
		cout<<"If player uses a pacifier against Aroma or Paci-Pop Caretakers, they fail a Pacifier Check."<<endl;
	}
	if(aroma){
		cout<<"If Caretaker has Aroma, player loses a Pacifier Check."<<endl;
	}
	
		check = true;
   while(check == true)
   {
   	cout<<endl<<"Do you want to roll Hypnosis-related checks? Ex. Aroma, Lazy Aura. (y/n): ";
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'y')||(charput == 'Y')) {
		HCauto = 1;
		HypnoCheck(true);
   }
   
		check = true;
   while(check == true)
   {
   	cout<<endl<<"Do you want to roll for Use Aura values? Ex. Wet Aura. (y/n): ";
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'y')||(charput == 'Y')) {
		UCauto = 1;
		aura = true;
		UCprompt();
   }
	
	perPlayer = YesNo();
}
}



void HypnoCheck(bool Caretaker){
	int modifier;
	bool disadvan;
	int die;
	
	cout<<endl<<"Welcome to the Hypnosis Check roller!"<<endl;
	
	if((Caretaker)||(HCauto > 0))
	{
		cout<<"This event has Hypnosis Check(s). Please enter..."<<endl;
	} else {
		check = true;
		while(check == true)
		{
		cout<<"The number of HCs being made in a row for one player: ";
		
		cin>>intput;

		if((cin.fail())||(intput < 1)){
			cin.clear();
			cin.ignore();
			intput = 0;
			cout<<"Please enter a positive integer."<<endl;
		} else {
			check = false;
			HCauto = intput;
		}
		}
	}
	
	check = true;
	while(check == true)
	{
	cout<<"HC modifier: ";
	
	cin>>modifier;

	if(cin.fail()){
		cin.clear();
		cin.ignore();
		intput = 0;
		cout<<"Please enter an integer."<<endl;
	} else {
		check = false;
	}
	}
	
	check = true;
   while(check == true)
   {
   	cout<<endl<<"Does player roll HC at disadvantage (y/n)?: ";
   	cin>>charput;

   	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
   		cin.clear();
   		cin.ignore();
   		charput = 'q';
   		cout<<"Please enter a proper input. "<<endl;
   	} else {
   		check = false;
   	}
   }

   if((charput == 'n')||(charput == 'N')) {
		disadvan = false;
   } else {
		disadvan = true;
   }
	
	die = Die20();
	
	if(disadvan)
	{
		sleep(2.1);
		int temp = Die20();
		if(temp > die)
		{
			die = temp;
		}
	}
	
	die += modifier;
	
	if(die > 15)
	{
		cout<<"Hypnosis Check failed, player gains a stack of Hypnotized."<<endl;
		cout<<"HC bonuses from previous HC rolls are reset."<<endl;
		
	} else {
		cout<<"Hypnosis Check succeeded.";
		
		if(die >= 6)
		{
			cout<<" HC bonus increased by 2, unless special roll (then 1).";
		}
		cout<<endl;
	}
	
	cout<<"Press [Enter] to continue.";
	getch();
	
}



void foodDrink(){
	bool bottle = false;
	int bWHP;
	int food;
	int drink;
	int restore = 0;
	int WHP = 0;
	int MHP = 0;
	int i;
	int damage;
	int laxdiu;
	perPlayer = true;
	
	if((foodAuto > 0)||(drinkAuto > 0))
	{
		mother = true;
	}
	
	 while(perPlayer == true)
	 {
		if(mother != true){
				check = true;
			while(check){
			cout<<"Welcome to the food and drink calculator. Please select your food/drink source."<<endl;
			cout<<"0- Return to main menu"<<endl;
			cout<<"1- Lunchbox"<<endl;
			cout<<"2- Moomoo Milk"<<endl;
			cout<<"3- Found after an Encounter"<<endl;
			cout<<"- Kitchen Room attack"<<endl;
			cout<<"Input: ";
			
			cin>>intput;
			
			if((cin.fail())||(intput > 4)||(intput < 0)){
				cin.clear();
				cin.ignore();
				intput = -1;
				cout<<endl<<"Please enter a number between 0 and 4."<<endl<<endl;
				getch();
				system("cls");
			} else {
				check = false;
			}
			}
			
			switch(intput)
			{
				//return to main menu
				case 0:
					return;
				
				//Lunchbox
				case 1:
					system("cls");
					cout<<"Generating";
					
					drink = Die4();
					if(drink > 2){ drink = 2;} else { drink = 1; }
					sleep(1.2);
					food = Die4();
					if(food > 2){ food = 2;} else { food = 1; }
					sleep(1.2);
					
					cout<<".";
					
					//drink healing
					for(i = 0; i < (drink * 2); i++)
					{
						restore += Die3();
						sleep(1);
					}
					cout<<".";
					
					//food healing
					for(i = 0; i < food; i++)
					{
						restore += Die5() + 3;
						sleep(1);
					}
					cout<<".";
					
					//drink WHP
					for(i = 0; i < drink; i++)
					{
						WHP += Die4() + 2;
						sleep(1);
					}
					cout<<".";
					
					//food MHP
					for(i = 0; i < food; i++)
					{
						MHP += Die5() + 1;
					}
					cout<<".";
					
					system("cls");
					cout<<"Lunchbox contained "<<drink<<" containers of juice and "<<food<<" cups of applesauce."<<endl;
					cout<<"Player recovered "<<restore<<" HP."<<endl;
					cout<<"Player gains "<<WHP<<" WHP and "<<MHP<<" MHP."<<endl;
				break;
				
				//Moomoo Milk
				case 2:
					cout<<"Player fully recovers HP."<<endl;
					cout<<"On the following roll, only record WHP."<<endl;
					UCauto = 2;
					UCprompt();
				break;
				
				//Found after Encounter, basic food/drink generation
				case 3:
						check = true;
					while(check){
					cout<<"How many container(s) is this player drinking?: "<<endl;
					
					cin>>drink;
					
					if((cin.fail())||(drink > 4)||(drink < 0)){
						cin.clear();
						cin.ignore();
						drink = 0;
						cout<<"Please enter a number between 0 and 4."<<endl<<endl;
						getch();
					} else {
						check = false;
					}
					}
					
						check = true;
					while(check){
					cout<<"How many container(s) is this player eating?: "<<endl;
					
					cin>>food;
					
					if((cin.fail())||(food > 4)||(food < 0)){
						cin.clear();
						cin.ignore();
						food = 0;
						cout<<"Please enter a number between 0 and 4."<<endl<<endl;
						getch();
					} else {
						check = false;
					}
					}
				
					system("cls");
					cout<<"Generating";
					
					//drink healing
					for(i = 0; i < (drink * 2); i++)
					{
						restore += Die3();
						sleep(1);
					}
					cout<<".";
					
					//food healing
					for(i = 0; i < food; i++)
					{
						restore += Die5() + 3;
						sleep(1);
					}
					cout<<".";
					
					//drink WHP
					for(i = 0; i < drink; i++)
					{
						WHP += Die4() + 2;
						sleep(1);
					}
					cout<<".";
					
					//food MHP
					for(i = 0; i < food; i++)
					{
						MHP += Die5() + 1;
						sleep(1);
					}
					cout<<".";
					
					//auto-bottle generation
					if((drink > 0)&&(Die100() <= 25)){
						bottle = true;
						sleep(1);
					}
					if(bottle){
						bWHP = Die7() + 11;
					}
					
					
					system("cls");
					cout<<"Player recovered "<<restore<<" HP."<<endl;
					cout<<"Player gains "<<WHP<<" WHP and "<<MHP<<" MHP."<<endl;
					if(bottle){
						cout<<"Player is inflicted Auto-Bottle with "<<bWHP<<" WHP inside."<<endl;
					}
				break;
				
				//Kitchen-unique attack
				case 4:
					damage = Die4();
				
				
						check = true;
					while(check){
					cout<<"Did the Caretaker throw food or drink? "<<endl;
					cout<<"1 for drink, 2 for food"<<endl;
					cout<<"Input: ";
					
					cin>>intput;
					
					if((cin.fail())||(intput > 2)||(intput < 1)){
						cin.clear();
						cin.ignore();
						intput = 0;
						cout<<"Please enter 1 or 2."<<endl<<endl;
						getch();
					} else {
						check = false;
					}
					}
					
					system("cls");
					
					cout<<"On the following calculation, only include ";
					UCauto = 1;
					
					//if drink was thrown
					if(intput == 1){
						cout<<"WHP."<<endl;
					//if food was thrown
					} else {
						cout<<"MHP."<<endl;
					}
					
					UCprompt();
					
					if(Die100() <= 30)
					{
						laxdiu = true;
					} else {
						laxdiu = false;
					}
					
					cout<<"Player takes "<<damage<<" damage";
					
					//if drink was thrown
					if((intput == 1)&&(laxdiu))
					{
						cout<<" and suffers Diuretic."<<endl;
					//if food was thrown
					} else if((intput == 1)&&(laxdiu)){
						cout<<" and suffers Laxative."<<endl;
					} else {
						cout<<endl;
					}
					
				break;
				
				default:
				cout<<"ERROR"<<endl;
				break;
			}
		
		//Caretaker food/drink generation
		} else {
			cout<<"Generating Caretaker food calculations..."<<endl<<endl;
			
			//drink WHP
			for(int i = 0; i < drinkAuto; i++)
			{
				WHP += Die4() + 2;
				sleep(1);
			}
			
			//food MHP
			for(int i = 0; i < foodAuto; i++)
			{
				MHP += Die5() + 1;
				sleep(1);
			}
			
			cout<<"Player gains "<<WHP<<" WHP and "<<MHP<<" MHP."<<endl;
			cout<<"Press [Enter] to continue.";
			getch();
		}
	
	//does foodDrink() loop?
	if(mother == true)
	{
		perPlayer = false;
		mother = false;
		foodAuto = 0;
		drinkAuto = 0;
		
	} else {
		perPlayer = YesNo();
		cout<<endl;
		
		restore = 0;
	}
	
		WHP = 0;
		MHP = 0;
	 }
}



int drinking(int rolls){
	if(rolls <= 0){ rolls = 1; }
	
	for(int i = 0; i < rolls; i++){
		sleep(1.2);
		HPgain += Die3();
		sleep(1.2);
		HPgain += Die3();
	}
	
	return HPgain;
}



void Playtime(){
	int food = 0;
	int drink = 0;
	int restore = 0;
	int i;
	int WHP = 0;
	int MHP = 0;
	int bWHP;
	bool bottle;
	
	
	cout<<endl<<endl<<"This Encounter has Playtime, meaning the party's health is not restored normally."<<endl;
	cout<<"But, they do get to have a snack break! Let's see what happens for this player."<<endl;
	
	cout<<"Generating";
	
	//drink and food count
	
	food = Die4()/2 + 1;
	sleep(1.1);
	drink = Die4()/2 + 1;
	sleep(1.1);
	
	cout<<".";
	
	//drink healing
	for(i = 0; i < (drink * 2); i++)
	{
		restore += Die3();
		sleep(1);
	}
	cout<<".";
	
	//food healing
	for(i = 0; i < food; i++)
	{
		restore += Die5() + 3;
		sleep(1);
	}
	cout<<".";
	
	//drink WHP
	for(i = 0; i < drink; i++)
	{
		WHP += Die4() + 2;
		sleep(1);
	}
	cout<<".";
	
	//food MHP
	for(i = 0; i < food; i++)
	{
		MHP += Die5() + 1;
		sleep(1);
	}
	cout<<".";
	
	//auto-bottle generation
	if((drink > 0)&&(Die100() <= 25)){
		bottle = true;
		sleep(1);
	}
	if(bottle){
		bWHP = Die7() + 11;
	}
	
	cout<<endl<<endl<<"Player recovered "<<restore<<" HP."<<endl;
	cout<<"Player gains "<<WHP<<" WHP and "<<MHP<<" MHP."<<endl;
	
	if(bottle){cout<<"Player is inflicted Auto-Bottle with "<<bWHP<<" WHP inside."<<endl;}
	
	cout<<endl;
}
	


//Caretaker Encounters////////////////////////////////////////////////////////////////////
void Kangaskhan(){                                    //Kangaskhan

   perPlayer = true;
	while(perPlayer == true) {
		system("cls");
		cout<<"KANGASKHAN"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}

		Itotal = Intensity(2);

	if(forfeit){
		cout<<"Intensity roll of "<<(Itotal/2)<<" RB/BP."<<endl;
		cout<<"Pouched/Finished Intensity roll of "<<(Itotal/2 + 5)<<" RB/BP."<<endl<<endl;
	} else {
		cout<<"Intensity roll of "<<Itotal<<" RB/BP."<<endl;
		cout<<"Pouched/Finished Intensity roll of "<<(Itotal + 10)<<" RB/BP."<<endl<<endl;
	}

   	perPlayer = YesNo();
   }
}



void Goodra(){                                    //Goodra
	int fifty1 = 51;
	int randEffect;

	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		randEffect = Die3();
		cout<<"GOODRA"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
   
		Itotal = Intensity(2);

		if(forfeit){
			Itotal *= 0.5;
			sleep(1.2);
			fifty1 = Die100();
		}
		
		if(fifty1 > 50){
			switch(randEffect){
				case 1:
					cout<<"Player gains a stack of Obedience";
				break;
				
				case 2:
					cout<<"Player gains Protected Paws";
				break;
				
				case 3:
					cout<<"Player gains Pacifier Gag";
				break;
				
				default:
				cout<<"ERROR"<<endl;
				break;
			}
			cout<<"."<<endl;
		} else {
			cout<<"Goodra's status infliction was resisted."<<endl;
		}
		
		cout<<"Intensity roll of "<<Itotal<<" RB/MP and "<<(Itotal/2)<<" BP."<<endl;
		cout<<"Hogtied? That player gains Magic Pacifier too."<<endl;

      perPlayer = YesNo();
   }
}



void Wigglytuff(){                                    //Wigglytuff
	
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"WIGGLYTUFF"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
	
		Itotal = Intensity(2);

		if(forfeit){
			Itotal *= 0.5; 
			sleep(1.2);
			
			if(Die100() > 50){
				cout<<"Player gains Used Diaper Desire."<<endl;
			} else {
				cout<<"Player resisted the infliction of Used Diaper Desire."<<endl;
			}
		}
		
		cout<<"Intensity roll of "<<Itotal<<" RB/EP."<<endl;
		cout<<"If a player has no Use Levels, they gain 1 UL in both categories."<<endl;

      perPlayer = YesNo();
   }
}



void Serperior(){                                    //Serperior
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"SERPERIOR"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
	
		Itotal = Intensity(1);

		if(forfeit){Itotal *= 0.5;}
		
		cout<<"Intensity roll of "<<Itotal<<" RB/EP."<<endl;
		
		cout<<"Player gains 1 UL in both categories."<<endl;
		cout<<"This Caretaker will only change Max Capacity or Swollen Diapers."<<endl;

      perPlayer = YesNo();
   }
}



void Gardevoir(){                                    //Gardevoir
	
	perPlayer = true;
   while(perPlayer == true) {
	system("cls");
   	cout<<"GARDEVOIR"<<endl;
	
		if(tdForfeit){forfeit = Forfeit();}
	
		Itotal = Intensity(2);
		sleep(1.1);
		
		if(forfeit)
		{
			Itotal *= 0.5;
			
			if(Die100() > 50){
				sleep(1.3);
				randomGR(1);
			} else {
				cout<<"Player resisted the random Ghost Regression."<<endl;
			}
			
			sleep(1.1);
			
			if(Die100() > 50){
				cout<<"Player gains GR: Changeless."<<endl;
			} else{
				cout<<"Player resisted GR: Changeless."<<endl;
			}
		} else {
			randomGR(1);
			cout<<"Player gains GR: Changeless."<<endl;
		}
		
		cout<<"Intensity roll of "<<Itotal<<" RB/MP."<<endl;
		cout<<"Press [Enter] to start the Idle Roll. This will clear the screen."<<endl;
		getch();
		
		IRauto = 1;
		IdleRolls();

      perPlayer = YesNo();
   }
}



void Flygon(){                                    //Flygon
	
	perPlayer = true;
	int die;
	const int LOW = 1;
	int HIGH;
	time_t seconds;
	
   while(perPlayer == true) {
	system("cls");
   	cout<<"FLYGON"<<endl;
	
	HIGH = 100;
	
	if(tdForfeit){forfeit = Forfeit();}
	
   	Itotal = Intensity(1);
	
	if(forfeit)
	{
		Itotal *= 0.5;
		
		sleep(1.2);
		
		if(Die100() > 50){
			cout<<"Players suffer 2 stacks of Holding Help."<<endl;
		} else {
			cout<<"Player was not inflicted with 2 stacks of Holding Help."<<endl;
		}
	} else {
		cout<<"Players suffer 2 stacks of Holding Help."<<endl;
	}
	
		//Auto-Bottle check
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die <= 25)
	{
		HIGH = 7;
		sleep(1.2);
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		die += 11;
		cout<<"Player also gains Auto-Bottle with "<<die<<" WHP contained."<<endl;
	}
	  
	cout<<"Intensity roll of "<<Itotal<<" RB/MP."<<endl;
	  
    //Roll UC until diaper use
	rollUntil = true;
	UCauto = 1;
	UCprompt();

      perPlayer = YesNo();
   }
}



void Boss(){                                    //Bosses
	check = true;
   while(check == true)
   {
		cout<<"Which Boss are you encountering? 1- Latias. 2- Mewtwo. 3- Lugia."<<endl;
   	cin>>intput;

   	if((cin.fail())&&(intput < 3)&&(intput > 0)){
   		cin.clear();
   		cin.ignore();
   		intput = 0;
   		cout<<"Please enter a number."<<endl<<endl;
   		getch();
   	} else {
   		check = false;
   	}
   }


if(intput == 1)												//Latias
{
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"LATIAS/LATIOS (this will take a moment to generate)"<<endl;
		
	if(tdForfeit){
		forfeit = Forfeit();
		cout<<endl;
	}

	int total = 0;
	
	for(int i = 0; i < 3; i++){
		total += Die4();
		sleep(1.2);
	}
		
	if(forfeit){
		total *= 1.5;
		
		if(Die100() > 50){
			sleep(1.1);
			randomGR(1);
		} else {
			cout<<"Player avoided the random Ghost Regression."<<endl;
		}
		
	} else {
		total *= 3;
		randomGR(1);
	}
	
	cout<<total<<" MP/BP/EP and "<<(total / 2)<<" RB."<<endl;

      perPlayer = YesNo();
   }


} else if(intput == 2){                                		//Mewtwo
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"MEWTWO"<<endl;
		
	if(tdForfeit){forfeit = Forfeit();}

   	Itotal = Intensity(3);
	
	sleep(1.1);

	if(forfeit){
		Itotal *= 0.5;
		
		if(Die100() > 50){
			sleep(1.2);
			randomGR(2);
		} else {
			cout<<"Player avoided the random Mental GR."<<endl;
		}
		
		sleep(1.2);
		
		if(Die100() > 50){
			cout<<"Player suffers GR: Changeless."<<endl;
		} else {
			cout<<"Player avoided GR: Changeless."<<endl;
		}
	} else {
		randomGR(2);
		cout<<"Player suffers GR: Changeless."<<endl;
	}
	
	cout<<"Intensity roll of "<<Itotal<<" RB/MP."<<endl;

      perPlayer = YesNo();
   }


} else{                                                		//Lugia
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"LUGIA"<<endl;
		
	if(tdForfeit){forfeit = Forfeit();}
	
   	Itotal = Intensity(2);
	
	sleep(1.1);
	
	if(forfeit){
		Itotal *= 0.5;
		
		if(Die100() > 50){
			sleep(1.1);
			randomGR(3);
		} else {
			cout<<"Player avoided the random Body or Equipment Ghost Regression."<<endl;
		}
	} else {
		randomGR(3);
	}
	
	cout<<"Intensity roll of "<<Itotal<<" RB/BP/EP."<<endl;
	  
    //Roll 2 UC at 5 higher Tiers
	UCauto = 6;
	rollCount = 2;
	UCprompt();
	  
	cout<<"If either point category does not procc diaper use, add enough UHP to use diaper in that category."<<endl;

    perPlayer = YesNo();
   }
   
}
}



void Miltank(){                                     //Miltank
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"MILTANK"<<endl;

	if(tdForfeit){forfeit = Forfeit();}
	
	Itotal = Intensity(1);
	
	if(forfeit){Itotal *= 0.5;}
	
	cout<<"Intensity roll of "<<Itotal<<" RB/BP/EP."<<endl;
	
	//roll 2 UC at 1 higher Tier
	UCauto = 2;
	rollCount = 2;
	UCprompt();
	
	perPlayer = YesNo();
   }
}



void Primarina(){                                  //Primarina
	cout<<"Loading...";
	
	bool enhance = false;
	int i;
	string printType = "";
	int die;
	int total = 0;
	int bombCount = Die3();
	sleep(1.2);
	int bombType = Die3();
	
		perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"PRIMARINA (warning, generation takes a moment)"<<endl<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(0);
	
	switch(bombType)
	{
		case 1:
		cout<<"Vanilla";
		printType = "MP";
		break;
		
		case 2:
		i = 0;
		while((i < bombCount)&&(!enhance)){
			die = Die100();
			if(die > 50){
				enhance = true;
			}
			i++;
			sleep(1.2);
		}
		cout<<"Powder";
		printType = "EP";
		break;
		
		case 3:
		cout<<"Fruity";
		printType = "BP";
		break;
		
		default:
		cout<<"ERROR, BOMB TYPE FAILED"<<endl;
		break;
	}
	
	cout<<" Bombs rain down on the party!"<<endl;
	
	for(i = 0; i < 3; i++)
	{
		sleep(1.4);
		total += Die4();
	}

	if(forfeit){
		total *= 0.5;
		Itotal *= 0.5;
	}
	
	if(enhance){
		cout<<" Player gains a stack of Enhancement.";
	}
	
	cout<<"Player gains "<<total<<" "<<printType<<" and "<<(total / 2 + Itotal)<<" RB."<<endl;
	
	total = 0;
	enhance = false;
	perPlayer = YesNo();
   }
}



void Leavanny(){                                   //Leavanny
	int die;
	
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"LAEVANNY"<<endl;
	   
	if(tdForfeit){forfeit = Forfeit();}
	   
	Itotal = Intensity(1);
	   
	if(forfeit){Itotal *= 0.5;}
	
	cout<<"Intensity roll of "<<Itotal<<" for RB/MP. Player gains Sissy Attire."<<endl;
	
	perPlayer = YesNo();
   }
}



void Togekiss(){                                   //Togekiss
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"TOGEKISS"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(1);
	   
	   if(forfeit){Itotal *= 0.5;}
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP. Any player with Silly is cured."<<endl;
	   
		cout<<"Press [Enter] to start the Idle Roll. This will clear the screen."<<endl;
		getch();
	   
		IRauto = 2;
		IdleRolls();
	
	perPlayer = YesNo();
   }
}



void Ninetales(){                                  //Ninetales
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"NINETALES"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(2);
	   sleep(1.2);
	   
	   if(forfeit){
			Itotal *= 0.5;
		   
			if(Die100()>50){
				cout<<"Player resisted the random Ghost Regression."<<endl;
			} else {
				sleep(1.1);
				randomGR(1);
			}
			
			sleep(1.2);
			
			if(Die100()>50){
				cout<<"Player resisted gaining GR: Changeless."<<endl;
			} else {
				cout<<"Player gains GR: Changeless."<<endl;
			}
	   } else {
		   randomGR(1);
		   cout<<"Player gains GR: Changeless."<<endl;
	   }
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP."<<endl;
	
	perPlayer = YesNo();
   }
}



void Chansey(){                                    //Chansey
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"CHANSEY"<<endl;
	   
	if(tdForfeit){forfeit = Forfeit();}
	
	Itotal = Intensity(0);
	  
	  sleep(1.1);
	  
	if(forfeit){
		Itotal *= 0.5;
		
		if(Die100()>50){
			cout<<"Player avoids the random Ghost Regression."<<endl;
		} else {
			sleep(1.1);
			randomGR(1);
			cout<<"Reminder, this takes effect before the Idle Roll."<<endl;
		}
		
	} else {
		randomGR(1);
	}
	
	cout<<"Intensity roll of "<<Itotal<<" RB/MP/BP."<<endl;
	
	cout<<"Press [Enter] to continue to the Idle Roll. This will clear the screen."<<endl;
	getch();
	
	IRauto = 10;
	IdleRolls();
	
	perPlayer = YesNo();
   }
}



void Salazzle(){									//Salazzle
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"SALAZZLE"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   cout<<"Players suffer the following as if Brainwashed during the Party Wipe: Instant RB +20, IT/IRT +1, IR +7 (if not calculated already)."<<endl;
	   cout<<"This calculator will not add the effects of Brainwashed to the following Intensity roll ."<<endl;
	   
	   Itotal = Intensity(1);
	   
	   if(forfeit){Itotal *= 0.5;}
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP and player now wears a Salandit-themed Hypno Suit."<<endl;
	
	perPlayer = YesNo();
   }
}



void Luxray(){										//Luxray
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"LUXRAY"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	check = true;
   while(check == true)
   {
		cout<<"How many times has the party lost to Luxray (including this time)?"<<endl;
   	cin>>intput;

   	if((cin.fail())&&(intput < 1)){
   		cin.clear();
   		cin.ignore();
   		intput = 0;
   		cout<<"Please enter an integer greater than 0."<<endl<<endl;
   		getch();
   	} else {
   		check = false;
		if(intput > 3)
		{intput = 3;}
   	}
   }
	Itotal = Intensity(intput * 2);
	
	if(forfeit){
		Itotal *= 0.5;
		sleep(1.1);
		
		if(Die100() > 50){
			cout<<"Player gains GR: Diaper Suit."<<endl;
		} else {
			cout<<"Player manages to avoid GR: Diaper Suit."<<endl;
		}
	} else {
		cout<<"Player gains GR: Diaper Suit."<<endl;
	}
	
	cout<<"Intensity roll of "<<Itotal<<" RB/MP/EP."<<endl;
	cout<<"If the party encounters Luxray again, the party starts with"<<intput<<" stack(s) of Obedience."<<endl;
	
	perPlayer = YesNo();
   }
}



void Nidoqueen(){									//Nidoqueen
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"NIDOQUEEN"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(0);
	   
	   if(forfeit){
		   sleep(1.1);
		   
		   if(Die100()>50){
			   cout<<"Player suffers 1 stack of Enhancement before further calculations."<<endl;
		   } else {
			   cout<<"Player avoids the 1 stack of Enhancement."<<endl;
		   }
	   } else {
		   cout<<"Player suffers 1 stack of Enhancement before further calculations."<<endl;
	   }
	   
	   cout<<"NOTE: Player only suffers MHP in the following generation."<<endl;
	   cout<<"If the points do not result in an MUL, they gain enough points for 1 MUL anyway."<<endl<<endl;
	   
	   rollCount = 5;
	   UCprompt();
	   
	   cout<<endl;
	   
	   	check = true;
   while(check == true)
   {
		cout<<"How many MUL did the player gain?: ";
   	cin>>intput;

   	if((cin.fail())&&(intput < 1)){
   		cin.clear();
   		cin.ignore();
   		intput = 0;
   		cout<<"Please enter an integer greater than 0."<<endl<<endl;
   		getch();
   	} else {
   		check = false;
		Itotal += (intput * 10);
   	}
   }
   
   if(forfeit){Itotal *= 0.5;}
   
   cout<<"Intensity roll of "<<(Itotal)<<" RB/EP."<<endl;
	
	perPlayer = YesNo();
   }
}

void Vaporeon(){									//Vaporeon
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"VAPOREON"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(0);
	   
	   if(forfeit){
		   sleep(1.1);
		   
		   if(Die100()>50){
			   cout<<"Player suffers 1 stack of Enhancement before further calculations."<<endl;
		   } else {
			   cout<<"Player avoids the 1 stack of Enhancement."<<endl;
		   }
	   } else {
		   cout<<"Player suffers 1 stack of Enhancement before further calculations."<<endl;
	   }
	   
	   cout<<"NOTE: Player only suffers WHP in the following generation."<<endl;
	   cout<<"If the points do not result in an WUL, they gain enough points for 1 WUL anyway."<<endl<<endl;
	   
	   rollCount = 5;
	   UCprompt();
	   
	   cout<<endl;
	   
	   	check = true;
   while(check == true)
   {
		cout<<"How many WUL did the player gain?: ";
   	cin>>intput;

   	if((cin.fail())&&(intput < 1)){
   		cin.clear();
   		cin.ignore();
   		intput = 0;
   		cout<<"Please enter an integer greater than 0."<<endl<<endl;
   		getch();
   	} else {
   		check = false;
		Itotal += (intput * 10);
   	}
   }
   
   if(forfeit){Itotal *= 0.5;}
   
   cout<<"Intensity roll of "<<(Itotal)<<" RB/EP."<<endl;
	
	perPlayer = YesNo();
   }
}



void Audino(){										//Audino
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"AUDINO"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   cout<<"The following calculations are done at minimum PL."<<endl;
	   
	   rollCount = 2;
	   UCprompt();
	   
	   cout<<endl;
	   
	   	check = true;
   while(check == true)
   {
		cout<<"How many Use Levels did the player gain?"<<endl;
   	cin>>intput;

   	if((cin.fail())&&(intput < 0)){
   		cin.clear();
   		cin.ignore();
   		intput = 0;
   		cout<<"Please enter a positive integer, or zero."<<endl<<endl;
   		getch();
   	} else {
   		check = false;
   	}
   }
   
   Itotal = Intensity(intput + 1);
   
   if(forfeit){Itotal *= 0.5;}
   
   cout<<"Intensity roll of "<<Itotal<<" RB/BP. Player gains 2 stacks of Holding Help."<<endl;
	
	perPlayer = YesNo();
   }
}



void Lucario(){										//Lucario
		perPlayer = true;
   while(perPlayer == true) {
	   bool skew = false;
	   system("cls");
	   cout<<"LUCARIO"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
		check = true;
	while(check == true)
	{
		cout<<"Does the player have Skewed Aura? (y/n): "<<endl;
		cin>>charput;

		if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
			if((charput == 'y')||(charput == 'Y')){
				skew = true;
			}
		}
	}
	   
	if(skew == true)
	{
		Itotal = Intensity(2);
		randomGR(1);
	} else {
		Itotal = Intensity(1);
	}
	
	if(forfeit){Itotal *= 0.5;}
	
	cout<<"Intensity roll of "<<Itotal<<" RB/MP/BP."<<endl;
	
	skew = false;
	perPlayer = YesNo();
   }
}



void Ampharos(){									//Ampharos
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"AMPHAROS"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(1);
	   
	   if(forfeit){Itotal *= 0.5;}
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP. Player suffers 2 stacks of Obedience during next Caretaker Encounter."<<endl;
	
	perPlayer = YesNo();
   }
}



void Ivysaur(){										//Ivysaur
	int bomb = 0;
	int die = 0;
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"IVYSAUR (warning: takes a moment to calculate)"<<endl<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   cout<<"Player is changed into Overnight diaper before any further effects."<<endl;
	   
	   //powder bomb crit fail
	   for(int i = 0; i < 3; i++){
		   bomb = Die4();
		   sleep(1.2);
	   }
	   
	   die = Die20();
	   
	   Itotal = Intensity(0);
	   
	   if(die > 10){cout<<" Player gains a stack of Enhancement."<<endl;}
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/BP. Powder bomb inflicts "<<(bomb / 2)<<"RB & "<<bomb<<" BP."<<endl;
	   cout<<"In other words, a total of "<<(Itotal+bomb/2)<<" RB and "<<(Itotal+bomb)<<" BP."<<endl;
	   
		UCauto = 3;
		UCprompt();
		
		cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
		
		IRauto = 3;
		IdleRolls();


		bomb = 0;
	perPlayer = YesNo();
   }
}



void Slowpoke(){									//Slowpoke
	int die = 0;
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"SLOWPOKE"<<endl;
	   
	   die = Die20();
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(0);
	   
	   if(forfeit){
		   Itotal *= 0.5;
		   sleep(1.2);
		   
		 if(Die100()>50){
			cout<<"Player gains GR: Changeless."<<endl;
		 } else {
			cout<<"Player avoids GR: Changeless."<<endl;
		 }
	   } else {
		   cout<<"Player gains GR: Changeless."<<endl;
	   }
	   
	   if(die > 10){
		   cout<<"Player gains GR: Lazy."<<endl;
	   }
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP."<<endl;
	   
	   cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
	   
	   IRauto = 5;
	   IdleRolls();
	   
	perPlayer = YesNo();
   }
}



void Snorlax(){										//Snorlax
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"SNORLAX"<<endl;
	   //generate drink in advance, for speed
	   drinkAuto = Die4();
	   
	   cout<<"Because all of Snorlax's effects ignore forfeit's effects, this Caretaker will generate without the prompt."<<endl<<endl;
	   
	   //Lazy check
	   sleep(1.2);
	   if(Die20() > 10){cout<<" Player gains GR: Lazy. ";}
	   
	   cout<<"Double the RB value from the following Idle Roll, and also apply it to BP."<<endl;
	   
	   cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
		
	   IRauto = 3;
	   IdleRolls();
	   
	   //food generation
	   foodAuto = Die4();
	   sleep(1.2);
	   drinkAuto = Die4();
	   sleep(1.2);
	   
	   //calculate food/drink
	   foodDrink();
	   
	   cout<<"Reminder to apply the Idle Roll's RB to BP, and to double the RB gained."<<endl;
	
	perPlayer = YesNo();
   }
}



void Mew(){											//Mew
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"MEW"<<endl;
	   
	   cout<<"Because all of Mew's effects ignore forfeit's effects, this Caretaker will generate without the prompt."<<endl<<endl;
	   
	   //chance of random GR
	   if(Die20() > 10){
		   randomGR(1);
	   }
	   
	   cout<<"Apply the RB value from this Idle Roll to all other Points (MP/BP/EP) as well."<<endl;
	   
	   cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
	   
	   IRauto = 1;
	   IdleRolls();
	   
	   UCauto = 1;
	   UCprompt();
	   
	   Playtime();
	
	perPlayer = YesNo();
   }
}



void Galvantula(){									//Galvantula
	bool pink = false;
	bool drool = false;
	int wear;

	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"GALVANTULA"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(2);
	   
	//check if pink
		check = true;
		while(check == true)
		{
			cout<<"Does this player suffer Pinkified or Girly (y/n)?: ";
			cin>>charput;

			if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
				cin.clear();
				cin.ignore();
				charput = 'q';
				cout<<"Please enter a proper input. "<<endl;
			} else {
				check = false;
				if((charput == 'y')||(charput == 'Y')){
					pink = true;
				}
			}
		}
		
	//check if drooling
		check = true;
		while(check == true)
		{
			cout<<"Does the player suffer Drooling (y/n)?: ";
			cin>>charput;

			if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
				cin.clear();
				cin.ignore();
				charput = 'q';
				cout<<"Please enter a proper input. "<<endl;
			} else {
				check = false;
				if((charput == 'y')||(charput == 'Y')){
					drool = true;
				}
			}
		}
		
	//generate GR
	if((forfeit == false)||(Die100()>50)){
		randomGR(2);
	} else {
		cout<<"Player avoided the random Mental GR."<<endl;
	}
	sleep(1.2);
		
		//find second GR possibility
		if(pink&&drool){
			wear = Die3();
		} else if(pink){
			wear = Die20();
			if(wear > 10)
			{
				wear = 2;
			} else {
				wear = 1;
			}
		} else if(drool){
			wear = Die20();
			if(wear > 10)
			{
				wear = 3;
			} else {
				wear = 1;
			}
		} else {
			wear = 1;
		}
		
		//print clothing results
		if(((forfeit)&&(Die100()>50))||(forfeit == false)){
			cout<<"Player gains GR: ";
			
			switch(wear)
			{
				case 1:
				cout<<"Baby Clothes."<<endl;
				break;
				
				case 2:
				cout<<"Frilly Clothes."<<endl;
				break;
				
				case 3:
				cout<<"Baby Bib."<<endl;
				break;
				
				default:
				cout<<"Baby Clothes (ERROR IN NUM GEN)."<<endl;
				break;
			}
		} else {
			cout<<"Player managed to resist the clothing GR."<<endl;
		}
	
	perPlayer = YesNo();
   }
}



void Ursaring(){									//Ursaring
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"URSARING"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(0);
	   
	   if(forfeit){
		   Itotal *= 0.5;
		   sleep(1.2);
		   
		   if(Die100()>50){
				cout<<"Player gains Snuggler."<<endl;
		   } else {
			   cout<<"Player avoids Snuggler."<<endl;
		   }
	   } else {
		   cout<<"Player gains Snuggler."<<endl;
	   }
	   
	   cout<<"Player gains "<<Itotal<<" RB/BP."<<endl;
	   
	   Playtime();
	
	perPlayer = YesNo();
   }
}



void AlakazamPac(){									//Alakazam (Pacifier)
	int fifty;
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"ALAKAZAM- PACIFIERS"<<endl;
	   
	   fifty = Die100();
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   cout<<"Player is Pacified before any further effects."<<endl;
	   
	   Itotal = Intensity(2);
	   
	   if(fifty > 50){
		   cout<<"Player gains Magic Pacifier."<<endl;
	   }
	   
	   if(forfeit){Itotal *= 0.5;}
	   
	   cout<<"Player gains "<<Itotal<<" RB/MP."<<endl;
	  
	   cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
	   
	   IRauto = 1;
	   IdleRolls();
	   
	
	perPlayer = YesNo();
   }
}



void AlakazamSpo(){									//Alakazam (Spoon)
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"ALAKAZAM- SPOONS"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   foodAuto = Die20()/10 + 1;
	   sleep(1.2);
	   drinkAuto = Die20()/10 + 1;

	   Itotal = Intensity(2);
	   
	   if(forfeit){
		   Itotal *= 0.5;
		   sleep(1.2);
		   
		   if(Die100()>50){
			   cout<<"Player GAINS Soft Foods";
		   } else {
			   cout<<"Player AVOIDS soft foods";
		   }
		   cout<<" and ";
		   sleep(1.2);
		   if(Die100()>50){
			   cout<<"GAINS GR: Changeless."<<endl;
		   } else {
			   cout<<"AVOIDS GR: Changeless."<<endl;
		   }
		   
	   } else {
		   cout<<"Player gains Soft Foods and GR: Changeless."<<endl;
	   }
	   
	   cout<<"Player gains "<<Itotal<<" RB/MP."<<endl;
	   
	   foodDrink();
	
	perPlayer = YesNo();
   }
}



void Victini(){										//Victini
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"VICTINI"<<endl;
	   
		cout<<"Because all of Victini's effects ignore forfeit's effects, this Caretaker will generate without the prompt."<<endl<<endl;
	   
	   if(Die100()>50){
		   cout<<"Player gains ";
		   switch(Die3())
		   {
			   case 1:
			   cout<<"GR: Quick Filler";
			   break;
			   
			   case 2:
			   cout<<"GR: Strong Filler";
			   break;
			   
			   case 3:
			   cout<<"GR: Hyper Use";
			   break;
			   
			   default:
			   cout<<"ERROR. Just go with GR: Quick Filler";
			   break;
		   }
		   cout<<"."<<endl;
	   }
	   
	   UCauto = 4;
	   UCprompt();
	   
	   cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
	   
	   IRauto = 3;
	   IdleRolls();
	   
	   Playtime();
	   
	perPlayer = YesNo();
   }
}



void Dragonite(){									//Dragonite
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"DRAGONITE"<<endl;
	   
	   cout<<"Because all of Dragonite's effects ignore forfeit's effects, this Caretaker will generate without the prompt."<<endl<<endl;
	   
	   cout<<"Player changes into Overnight Diaper BEFORE any further effect."<<endl;
	   
	   IRauto = 6;
	   IdleRolls();
	   
	perPlayer = YesNo();
   }
}



void Delphox(){										//Delphox
	int mis = 0;
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"DELPHOX"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   cout<<"The Misfire is not rerolled when generating for several players."<<endl<<endl;
	   
	   cout<<"Delphox casts a random spell on the party!"<<endl;
	   if(mis == 0)
	   {
		   mis = Misfire(false);
	   }
	   cout<<"Delphox casts Misfire #"<<mis<<"! Do not apply this effect until the end."<<endl;
	   
	   Itotal = Intensity(1);
	   
	   if(forfeit){Itotal *= 0.5;}
	   
	   cout<<"This player gains "<<Itotal<<" RB/MP/BP/EP."<<endl;
	   
	perPlayer = YesNo();
   }
}



void Smeargle(){									//Smeargle
	int fifty = 100;
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"SMEARGLE"<<endl;
	   
	   if(tdForfeit){forfeit = Forfeit();}
	   
	   Itotal = Intensity(2);
	   
	   if(forfeit){
		   fifty = Die100();
		   Itotal *= 0.5;
		   
		   if(fifty>50){
				cout<<"Player suffers Pinkified/Powdered (their preference)."<<endl;
				cout<<"If they have either, then instead find a random GR after this calculation."<<endl;
		   } else {
			   cout<<"Player avoids Pinkified/Powdered."<<endl;
		   }	   
	   } else{
		    cout<<"Player suffers Pinkified/Powdered (their preference)."<<endl;
			cout<<"If they have either, then instead find a random GR after this calculation."<<endl;
	   }
	   
	   cout<<"Player gains "<<Itotal<<" RB/BP/EP."<<endl<<endl;

if(fifty > 50){
   check = true;
	while(check == true)
	{
		cout<<"Would you like to generate a random GR (y/n)? ";
		cin>>charput;

		if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter y or n. "<<endl;
		} else {
			check = false;
			if((charput == 'y')||(charput == 'Y')){
				cout<<"Generating random Ghost Regression. ";
				randomGR(1);
			}
		}
	}
}

	perPlayer = YesNo();
   }
}



void Shaymin(){										//Shaymin
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"SHAYMIN"<<endl;
	   
	   cout<<"Shaymin is non-hostile, so they do not have a forfeit."<<endl;
	   
	check = true;
	while(check == true)
	{
		cout<<"Does the player wear a Flower Diaper (y/n)? ";
		cin>>charput;

		if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter y or n. "<<endl;
		} else {
			check = false;
			cout<<endl<<endl;
			if((charput == 'N')||(charput == 'n')){
				cout<<"Player rolls 1 IR and rolls Tiny IT, but are fully healed and can acquire/change into Flower Diapers."<<endl;
				
				Itotal = Intensity(0);
				cout<<"Player gains "<<Itotal<<" RB/MP/BP/EP."<<endl;
				
				IRauto = 1;
				IdleRolls();
			} else {
				cout<<"Player is fully healed, and may acquire/change into Flower Diapers."<<endl;
			}
		}
	}
	   
	perPlayer = YesNo();
   }
}



//Trap Encounters/////////////////////////////////////////////////////////////////////////
void HypnoTV(){										//Hypno TV
	system("cls");
	cout<<"HYPNO TV"<<endl;
	tRoll = TrapRoll();
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"HYPNO TV"<<endl;
	
	switch(tRoll){
		case 1:
		cout<<"Brainwashed for 4 Idle Rolls (also gains MP)."<<endl;
		IRauto = 4;
		break;
		
		case 2:
		cout<<"Brainwashed for 3 Idle Rolls (also gains MP)."<<endl;
		IRauto = 3;
		break;
		
		case 3:
		cout<<"Brainwashed for 2 Idle Rolls (also gains MP)."<<endl;
		IRauto = 2;
		break;
		
		case 4:
		cout<<"Roll 2 HC. If either succeeds, Hypnotized for 1 IR (also gains MP)."<<endl;
		IRauto = 1;
		break;
		
		case 5:
		cout<<"Roll 2 HC. If either succeeds, Hypnotized for 1 IR (also gains MP)."<<endl;
		break;
		
		case 6:
		cout<<"No effect, ignored."<<endl;
		break;
		
		default:
		cout<<"ERROR. Invalid Trap Roll."<<endl;
		break;	
	}
	
	if(tRoll < 5)
	{
		IdleRolls();
	} else if(tRoll == 5){
		
		check = true;
		while(check == true)
		{
			cout<<"Did either 2 Hypnosis Checks succeed? (y/n): "<<endl;
			cin>>charput;

	if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
				cin.clear();
				cin.ignore();
				charput = 'q';
				cout<<"Please enter a proper input. "<<endl;
			} else {
				check = false;
			}
		}
		
		if((charput == 'y')||(charput == 'Y')){
			IRauto = 1;
			IdleRolls();
		}
		
	}
	perPlayer = YesNo();
}
}


void MCL(){											//(Super) Massaging Chair Lock
	bool super = false;
	
	cout<<"(SUPER) MASSAGE CHAIR LOCK"<<endl;
	
	check = true;
	while(check == true)
	{
		cout<<"Is this the Super version?"<<endl;
		cin>>charput;

if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
		}
	}
	
	if((charput == 'y')||(charput == 'Y')){
		super = true;
	}	
	
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"(SUPER) MASSAGE CHAIR LOCK"<<endl<<endl;
	
	tRoll = TrapRoll();
	
	Itotal = Intensity(0);
	
	switch(tRoll){
		case 1:
		cout<<"Intensity roll of "<<(Itotal + 10)<<" for RB/BP. Inflicts 2 stacks Holding Help. PL to minimum until exit."<<endl;
		break;
		
		case 2:
		cout<<"Intensity roll of "<<Itotal<<" Tiny IT for RB/BP. Inflicts Holding Help. PL to minimum until exit."<<endl;
		break;
		
		case 3:
		cout<<"Intensity roll of "<<Itotal<<" Tiny IT for RB/BP. Reduces PL to minimum until exit."<<endl;
		break;
		
		case 4:
		cout<<"Intensity roll of "<<Itotal<<" Tiny IT for RB/BP. Reduces PL by 5 until exit."<<endl;
		break;
		
		case 5:
		cout<<"Intensity roll of "<<(Itotal / 2)<<" Tiny IT for RB/BP. Reduces PL by 3 until exiting."<<endl;
		break;
		
		case 6:
		cout<<"Intensity roll of "<<(Itotal / 4)<<" Tiny IT for RB/BP."<<endl;
		break;
		
		default:
		cout<<"ERROR. Invalid Trap Roll."<<endl;
		break;	
	}
	
if(super)
{
	switch(tRoll){
		case 1:
		case 2:
		cout<<"Vibrating Diaper with Diaper Lock."<<endl;
		break;
		
		case 3:
		case 4:
		case 5:
		cout<<"Vibrating Diaper with Diaper Lock for ";
		break;
		
		case 6:
		cout<<"No additional effect."<<endl;
		break;
		
		default:
		cout<<"STILL INVALID"<<endl;
		break;
	}
	
	if(tRoll == 3)
	{
		cout<<"2 IR"<<endl;
	} else if((tRoll < 6)&&(tRoll > 3))
	{
		cout<<"1 IR"<<endl;
	}
}
	

	perPlayer = YesNo();
}
 }
 
 
void Nursery(){										//Playtime Nursery
	int die = 1;
	const int LOW = 1;
	const int HIGH = 20;
	int dCount = 0;
	int dRoll = 0;

	perPlayer = true;
	while(perPlayer)
{
	system("cls");
	cout<<"PLAYTIME NURSERY"<<endl;
	cout<<"Generating";
	
	//Loop for roll generation
	for(int i = 0; i < 5; i++)
	{
		dRoll = Die20();
		
		if(dRoll > 10)
		{
			dCount++;
		}
		cout<<".";
		sleep(1.6);
	}
	
	if(dCount == 0)
	{
		dCount = 1;
	}
	
	//Generate points gained
	cout<<endl;
	Itotal = Intensity(dCount - 1);
	
	//Roll Idle Roll
	IRauto = 1;
	status = true;
	
	IdleRolls();
	
	cout<<endl;
	
	
	//Roll for Protected Paws and Pacifier Gag
	dRoll = Die20();

	switch(dRoll){
		case 4:
		case 8:
		case 12:
		case 16:
		cout<<"Player gains Protected Paws."<<endl;
		break;
		
		case 5:
		case 10:
		case 15:
		cout<<"Player gains Pacifier Gag."<<endl;
		break;
		
		case 20:
		cout<<"Player gains both Protected Paws and Pacifier Gag."<<endl;
		
		default:
		cout<<"No statuses gained from Trap."<<endl;
		break;
	}
	
	cout<<"Intensity roll of "<<Itotal<<" RB and "<<(Itotal / 2)<<" MP/BP/EP. PL -3 when alarm goes off."<<endl;
	
	dCount = 0;
	perPlayer = YesNo();
}
 }
 
 
 
void PowderRoom(){									//Powder Dust Room
	int trapSize;
	int curSize;
	int Ptotal;
	int Wtotal;
	int Mtotal;
	bool waddle;
	bool crawl;
	bool Enhance;
	
	trapSize = Die4();

	perPlayer = true;
while(perPlayer)
{
	Ptotal = 0;
	Wtotal = 0;
	Mtotal = 0;
	
	system("cls");
	cout<<"POWDER DUST ROOM"<<endl<<endl;
	
	check = true;
	while(check)
	{
		cout<<"Is the player waddling? (y/n): ";
		cin>>charput;

		if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
		}	
	}
	
	if((charput == 'y')||(charput == 'Y'))
	{
		waddle = true;
	} else {
		waddle = false;
	}
	
	check = true;
	while(check)
	{
		cout<<"Is the player crawling? (y/n): ";
		cin>>charput;

		if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
		}	
	}
	
	if((charput == 'y')||(charput == 'Y'))
	{
		crawl = true;
	} else {
		crawl = false;
	}
	
	if(crawl){
		curSize = 3 * trapSize;
	} else if(waddle){
		curSize = 2 * trapSize;
	} else {
		curSize = trapSize;
	}
	
	cout<<"Calculating...";
	
	//loop for Use Points
	for(int i = 0; i < curSize; i++)
	{
		Wtotal += Die6();
		sleep(1.6);
	}
	
	//loop for Points
	for(int i = 0; i < curSize; i++)
	{
		Ptotal += Die5();
		sleep(1.7);
	}
	if(Ptotal > 12){
		Enhance = true;
	} else {
		Enhance = false;
	}
	
	system("cls");
	cout<<"This trap has a size of "<<curSize<<" for this player."<<endl;
	cout<<"This player gains "<<Wtotal<< " WHP, "<<Mtotal<<" MHP, "<<Ptotal<<" RB/EP, and "<<(Ptotal / 2)<<" BP."<<endl;
	if(Enhance)
	{
		cout<<"This player gains a stack of Enhancement."<<endl;
	}
	

	perPlayer = YesNo();
}
 }
 
 
 
void BounceChair(){									//Bouncing Chair Lock
	perPlayer = true;
	int inten;
	int dice;
	
while(perPlayer)
{
	inten = 0;
	tRoll = TrapRoll();
	sleep(1);
	Itotal = Intensity(0);
	
	
	//Generate intensity roll
	if(tRoll == 1)
	{
		inten = 10;
	} else if (tRoll < 5){
		Itotal /= 2;
	} else {
		Itotal /= 4;
	}
	
	
	//Generate Use Checks (if any)
	if(tRoll < 4){
		rollUntil = true;
		UCprompt();
	} else if(tRoll == 4){
		UCauto = 2;
		UCprompt();
	} else if(tRoll == 5){
		UCauto = 1;
		UCprompt();
	}
	

	//Output
	cout<<"Intensity roll of "<<(Itotal + inten)<<" RB/EP."<<endl;
	
	if(tRoll < 3) {
		cout<<"Player gains Used Diaper Desire."<<endl;
	} else if(tRoll == 4) {
		dice = Die100();
		
		if(dice > 50){
			cout<<"Player gains Used Diaper Desire."<<endl;
		}
	}
	
	perPlayer = YesNo();
}
 }
void HighChair(){									//High Chair Dining Room
	int total;
	int dice;
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"HIGH CHAIR DINING ROOM"<<endl;
	
	drinkAuto = Die4();
	sleep(1.6);
	foodAuto = Die4();
	sleep(1.2);
	total = Die10();
	
//Calculate food points
	foodDrink();
	
	
//bonus RB/BP output
	cout<<"Player also gained "<<total<<" RB/BP";
	
//status check
	dice = Die20();
	if(dice > 10)
	{
		cout<<" and a stack of Soft Foods";
	}
	cout<<"."<<endl;

	perPlayer = YesNo();
}
 }
 
 
 
void PowderPath(){									//Concentrated Powder Path
	int trapSize = Die3();
	sleep(1.5);
	trapSize += Die3();
	
	int curSize;
	int counter;
	int Ptotal;
	bool waddle;
	bool crawl;

	perPlayer = true;
while(perPlayer)
{
	counter = 0;
	Ptotal = 0;
	
	system("cls");
	cout<<"CONCENTRATED POWDER PATH"<<endl<<endl;
	
	check = true;
	while(check)
	{
		cout<<"Is the player waddling? (y/n): ";
		cin>>charput;

		if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
		}	
	}
	
	if((charput == 'y')||(charput == 'Y'))
	{
		waddle = true;
	} else {
		waddle = false;
	}
	
	check = true;
	while(check)
	{
		cout<<"Is the player crawling? (y/n): ";
		cin>>charput;

		if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter a proper input. "<<endl;
		} else {
			check = false;
		}	
	}
	
	if((charput == 'y')||(charput == 'Y'))
	{
		crawl = true;
	} else {
		crawl = false;
	}
	
	if(crawl){
		curSize = 3 * trapSize;
	} else if(waddle){
		curSize = 2 * trapSize;
	} else {
		curSize = trapSize;
	}
	
	cout<<"Calculating";
	
	//generate trap triggers
	for(int i = 0; i < curSize; i++)
	{
		if(Die20() > 10)
		{
			counter++;
		}
		sleep(1.4);
		cout<<".";
	}
	if(counter == 0)
	{
		counter = 1;
	}
	
	cout<<endl<<"Generating";
	
	//Point gain
	for(int i = 0; i < counter; i++)
	{
		Ptotal += Die6() + 1;
		sleep(1.8);
		cout<<".";
	}
	
	cout<<endl<<endl;
	
	//Use Checks
	if(counter > 2)
	{
		UCauto = 1;
	} else {
		UCauto = 0;
	}
	
	UCauto += counter;
	
	//Output
	UCprompt();
	
	cout<<"Player gains "<<Ptotal<<" RB/MP/EP.";
	
	if(counter > 2)
	{
		cout<<" Player rolled at 1 higher UC Tier.";
	}
	cout<<endl<<"Player tripped "<<counter<<" traps."<<endl;
	
	perPlayer = YesNo();
}
 }
 
 
 
void ChangingRoom(bool Caretaker){							//Changing Room
	system("cls");
	if(Caretaker)
	{
		cout<<"CARETAKER'S ";
	}
	cout<<"CHANGING ROOM"<<endl;
	cout<<"Generating diaper numbers";
	
	int diapers = Die4() + 2;
	sleep(1.3);
	
	int types[6];
	types[0] = 0;
	int typeCount = 0;
	int dice;
	const int LOW = 1;
	const int HIGH = 30;
	time_t seconds;
	int initCount = 0;
	bool redo = false;
	
	
	for(int i = 0; i < diapers; i++)
	{
		dice = DiaperGenerator(true);
				
		for(int j = 0; j <= typeCount; j++)
		{
			if(dice == types[j])
			{
				i -= 1;
				redo = true;
			}
		}
		
		if(redo == false)
		{
			typeCount++;
			types[i] = dice;
			cout<<".";
		} else {
			redo = false;
			cout<<"R";
		}
		
		sleep(1.4);
	}
	
	cout<<endl<<endl<<"Diaper numbers are:"<<endl;
	
	for(int i = 0; i < typeCount; i++)
	{
		cout<<types[i]<<endl;
	}
	
	cout<<endl;
	
	if(Caretaker == false)
	{
	cout<<"Press [Enter] to return to main menu.";
	getch();
	}
	
 }
 
 
 
void CareChangingRoom(){							//Caretaker's Changing Room
	ChangingRoom(true);
	
	cout<<"This changing room is occupied by Caretaker #"<<CareGenerator(false)<<endl;
	
	cout<<endl<<"Press [Enter] to return to main menu.";
	getch();
 }
 
 
 
void PotionChallenge(){								//Potion Challenge
	int dice;
	int points;
	int extra;
	int repeat;
	int i;

	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"POTION CHALLENGE"<<endl<<"Warning: this may load slowly."<<endl<<endl;
	
	points = 0;
	extra = 0;
	repeat = 0;
	

do{	
	if(repeat == 0)
	{
		dice = Die4();
	} else {
		dice = Die3();
	}

	switch(dice)
	{
		case 1:
			for(i = 0; i < 3; i++)
			{
				sleep(1.9);
				points+= Die4();
			}
			cout<<"Player gains "<<points<<" RB/MP and GR: Drooling"<<endl;
			break;
			
		case 2:
			for(i = 0; i < 3; i++)
			{
				sleep(1.9);
				points+= Die4();
			}
			cout<<"Player gains "<<points<<" RB/BP and GR: Baby Fat"<<endl;
		break;
		
		case 3:
			for(i = 0; i < 3; i++)
			{
				sleep(1.9);
				points+= Die4();
			}
			cout<<"Player gains "<<points<<" RB/EP";
			
			sleep(1.3);
			extra = Die100();
			
			if(extra % 2 == 0)
			{
				cout<<" and 1 WUL";
			}
			if(extra % 3 == 0)
			{
				cout<<" and 1 MUL";
			}
			if((extra % 2 != 0)&&(extra % 3 != 0))
			{
				cout<<" and 2 UC"<<endl;
				
				rollCount = 2;
				UCauto = 1;
				UCprompt();
			} else {
			cout<<endl;
			}
		break;
		
		case 4:
			cout<<"Rolled 4! Generating two effects."<<endl;
			repeat = 3;
			sleep(1.3);
		break;
		
		default:
		cout<<"ERROR"<<endl;
		
	}
	
	if(repeat > 0){
		repeat -= 1;
	}
	
}while(repeat > 0);
	
	perPlayer = YesNo();
}
 }
 
 
 
void Presentation(){								//Presentation
	int inten;
	int total;
	
	perPlayer = true;
	system("cls");

	cout<<"PRESENTATION"<<endl;
	tRoll = TrapRoll();
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	IRauto = 1;
	status = true;
	cout<<"PRESENTATION"<<endl;
	
	switch(tRoll){
		case 1:
		cout<<"Brainwashed for 2 Idle Rolls (also gains MP). Inflicts Normal IT for RB/MP."<<endl;
		IRauto = 2;
		inten = 2;
		break;
		
		case 2:
		cout<<"Brainwashed for 1 Idle Roll (also gains MP). Inflicts Normal IT for RB/MP."<<endl;
		inten = 2;
		break;
		
		case 3:
		cout<<"Hypnotized for 1 Idle Roll (also gains MP). Inflicts Small IT for RB/MP."<<endl;
		inten = 1;
		break;
		
		case 4:
		cout<<"Roll 2 HC. If either succeeds, 1 stack of Hypnotized. Idle Roll for 1 IR (also gains MP). Tiny IT for RB/MP."<<endl;
		inten = 0;
		break;
		
		case 5:
		cout<<"Roll 1 HC. Idle Roll for 1 IR (also gains MP)."<<endl;
		break;
		
		case 6:
		cout<<"Idle Roll for 1 IR (also gains MP)."<<endl;
		break;
		
		default:
		cout<<"ERROR. Invalid Trap Roll."<<endl;
		break;	
	}
	
	cout<<endl;
	IdleRolls();
	
	if(tRoll < 5)
	{
		cout<<"Intensity roll of "<<Intensity(inten)<<" RB/MP."<<endl;
	}
	
	cout<<"Remember, the Idle Roll points also apply to MP."<<endl;
	
	perPlayer = YesNo();
}
 
 }
 
 
 
void AlarmTrap(){									//Alarm Trap
	system("cls");
	cout<<"ALARM TRAP"<<endl;
	cout<<"Players encounter Caretaker of #"<<CareGenerator(false)<<endl;
	cout<<"This Caretaker has a bonus of +1 to Attack Rolls and AC for 3 turns."<<endl;
	
	cout<<"Press [Enter] to return to main menu.";
	getch();
 }
 
 
 
void PacifierDoor(){								//Pacifier Door
	int doubler = 0;
	int dice;
	int oldDie;
	int die = 1;
	const int LOW = 1;
	const int HIGH = 2;
	time_t seconds;	
	
	
	system("cls");
	perPlayer = true;
while(perPlayer){
	cout<<"PACIFIER DOOR"<<endl;
do{
	if(doubler > 0)
	{
		oldDie = dice;
		sleep(1.3);
		
		if(oldDie != 4)
		{
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		
			switch(oldDie)
			{
				case 1:
				dice = die + 1;
				break;
				
				case 2:
				if(die == 2)
				{
				dice = 3;
				}
				break;
				
				case 3:
				dice = die;
				break;
				
				default:
				cout<<"ERROR with generating reroll"<<endl;
			}
		
		} else {
			dice = Die3();
		}
		
	} else {
		dice = Die4();
	}
	
	switch(dice)
	{
		case 1:
		cout<<"Tiny IT for RB. Player gains Pacifier Gag."<<endl;
		Itotal = Intensity(0);
		cout<<"Player gains "<<Itotal<<" RB."<<endl;
		break;
		
		case 2:
		cout<<"Tiny IT for RB. Player rolls UC at minimum Potty Limit until diaper is used."<<endl;
		Itotal = Intensity(0);
		cout<<"Player gains "<<Itotal<<" RB."<<endl;
		rollUntil = true;
		UCauto = 1;
		UCprompt();
		break;
		
		case 3:
		cout<<"GR: Drooling. 2 Idle Rolls for all players (does not stack with other effects)."<<endl;
		IRauto = 2;
		IdleRolls();
		break;
		
		case 4:
		doubler = 3;
		cout<<"Rolled a 4! Generating two effects.";
		if(Die100() > 50)
		{
			cout<<" Additionally, all players are Stupified.";
		}
		cout<<endl<<endl<<endl;
		
		break;
		
	}
	
	if(doubler > 0)
	{
		doubler -= 1;
		
	}
	if(doubler == 1)
	{
		cout<<endl;
	}
}while(doubler > 0);
	
	perPlayer = YesNo();
	system("cls");
}
 }
 
 
 
void WaterGun(){									//Water Gun Turret
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"WATER GUN TURRET"<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"5 UC for WHP. Large IT for EP. Player suffers Enhancement and Holding Help."<<endl;
		Itotal = Intensity(3);
		UCauto = 5;
		break;
		
		case 2:
		cout<<"4 UC for WHP. Normal IT for EP. Player suffers Enhancement and Holding Help."<<endl;
		Itotal = Intensity(2);
		UCauto = 4;
		break;
		
		case 3:
		cout<<"3 UC for WHP. Small IT for EP. Player suffers Holding Help."<<endl;
		Itotal = Intensity(1);
		UCauto = 3;
		break;
		
		case 4:
		cout<<"2 UC for WHP. Tiny IT for EP. Player suffers Holding Help for 2 Idle Rolls."<<endl;
		Itotal = Intensity(0);
		UCauto = 2;
		break;
		
		case 5:
		cout<<"1 UC for WHP. Tiny IT for EP at 1/2 total. Player suffers Holding Help for 1 Idle Roll."<<endl;
		Itotal = Intensity(0) / 2;
		UCauto = 1;
		break;
		
		case 6:
		cout<<"No effect, dodged."<<endl;
		break;
		
		default:
		cout<<"ERROR"<<endl;
	}
	
	if(UCauto)
	{
		UCprompt();
		cout<<"Player gains "<<Itotal<<" EP."<<endl;
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void MusicRoom(){									//Music Room
	perPlayer = true;
	
	system("cls");

	cout<<"MUSIC ROOM"<<endl;
	tRoll = TrapRoll();
	
while(perPlayer)
{
	system("cls");
	cout<<"MUSIC ROOM"<<endl;
	
	switch(tRoll)
	{
		case 1:
		cout<<"Minimal PL until exiting room. Large IT for RB/BP. Stupified."<<endl;
		Itotal = Intensity(3);
		break;
		
		case 2:
		cout<<"PL -10 until exiting room. Normal IT for RB/BP."<<endl;
		Itotal = Intensity(2);
		break;
		
		case 3:
		cout<<"PL -7 until exiting room. Normal IT for RB/BP."<<endl;
		Itotal = Intensity(2);
		break;
		
		case 4:
		cout<<"PL -5 until exiting room. Small IT for RB/BP."<<endl;
		Itotal = Intensity(1);
		break;
		
		case 5:
		cout<<"PL -3 until exiting room. Tiny IT for RB/BP."<<endl;
		Itotal = Intensity(0);
		break;
		
		case 6:
		cout<<"PL -1 until exiting room. Tiny IT for RB/BP at 1/2 total."<<endl;
		Itotal = Intensity(0) / 2;
		break;
	}
	
	cout<<"Player gains "<<Itotal<<" RB/BP."<<endl;
	
	perPlayer = YesNo();
}
 }
void SleepyRoom(){									//Sleepy Room
	perPlayer = true;
	
	system("cls");
	cout<<"SLEEPY ROOM"<<endl;
	tRoll = TrapRoll();
while(perPlayer)
{
	system("cls");
	cout<<"SLEEPY ROOM"<<endl;
	
	switch(tRoll)
	{
		case 1:
		cout<<"Diaper alters into Overnight. Roll 1 Idle Roll at 4 higher Tiers."<<endl;
		IRauto = 5;
		break;
		
		case 2:
		cout<<"Diaper alters into Overnight. Roll 1 Idle Roll at 3 higher Tiers."<<endl;
		IRauto = 4;
		break;
		
		case 3:
		cout<<"Diaper alters into Overnight. Roll 1 Idle Roll at 2 higher Tiers."<<endl;
		IRauto = 3;
		break;
		
		case 4:
		cout<<"1 Idle Roll at 1 higher Tier. Leave room with Sleepy lv. 1."<<endl;
		IRauto = 2;
		break;
		
		case 5:
		cout<<"Leave room with Sleepy lv. 1."<<endl;
		break;
		
		case 6:
		cout<<"No effect."<<endl;
		break;
	}
	
	if(IRauto)
	{
		IdleRolls();
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void ChangeMachine(){								//Change Machine
	perPlayer = true;
	int odds;
while(perPlayer)
{
	system("cls");
	cout<<"CHANGE MACHINE"<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"Player is inflicted with Pacifier Gag with Magic Pacifier. ";
		
		case 2:
		if(tRoll == 2)
		{
			cout<<"Player is inflicted with Pacifier Gag. ";
		}
		case 3:
		cout<<"Player recieves a random diaper change from the Changing Room list."<<endl;
		break;
		
		case 4:
		cout<<"75% chance of random diaper change from Changing Room list."<<endl;
		break;
		
		case 5:
		cout<<"25% chance of random diaper change from Changing Room list."<<endl;
		break;
		
		case 6:
		cout<<"No effect, avoided."<<endl;
		break;
		
		default:
		cout<<"ERROR"<<endl;
		break;	
	}
	
	sleep(1.2);
	odds = Die100();
	
	if((((odds <= 50)&&(tRoll == 4))||((odds <= 75)&&(tRoll == 5))||(tRoll < 4)))
	{
		cout<<"Player is changed into a diaper of #"<<DiaperGenerator(true)<<endl;
	} else {
		cout<<"Player avoids a diaper change."<<endl;
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void OddMirror(){									//Odd Mirror
	perPlayer = true;
	int odds1;
	int odds2;
	int GRs;
	
	system("cls");
	cout<<"ODD MIRROR"<<endl;
	
	tRoll = TrapRoll();
	
while(perPlayer)
{
	GRs = 0;
	system("cls");
	cout<<"ODD MIRROR"<<endl;
	
	switch(tRoll)
	{
		case 1:
		cout<<"2 UC. 20 RB. 2 random Ghost Regressions. Stupified."<<endl;
		UCauto = 2;
		GRs = 2;
		break;
		
		case 2:
		cout<<"2 UC. 10 RB. 1 random Ghost Regression."<<endl;
		UCauto = 2;
		GRs = 1;
		break;
		
		case 3:
		cout<<"1 UC. 8 RB. 1 random Ghost Regression."<<endl;
		UCauto = 1;
		GRs = 1;
		break;
		
		case 4:
		cout<<"50% chance of 1 UC and/or Ghost Regression, separately. 5 RB."<<endl;
		sleep(1.2);
		odds1 = Die100();
		sleep(1.2);
		odds2 = Die100();
		
		if(odds1 > 50)
		{
			cout<<"Player rolls 1 UC. ";
			UCauto = 1;
		}
		if(odds2 > 50)
		{
			cout<<"Player rolls 1 Ghost Regression.";
			GRs = 1;
		}
		cout<<endl;
		
		break;
		
		case 5:
		cout<<"5 RB."<<endl;
		break;
		
		case 6:
		cout<<"No effect, ignored."<<endl;
	}
	
	if(UCauto)
	{
		UCprompt();
	}
	if(GRs)
	{
		for(int i = 0; i < GRs; i++)
		{
			sleep(1.2);
			randomGR(1);
		}
	}
	
	if(tRoll < 5)
	{
		perPlayer = YesNo();
	} else {
		cout<<"Press [Enter] to return to main menu."<<endl;
		getch();
	}
}
 }
 
 
 
void DimWand(){										//Dimensional Wand
	perPlayer = true;
	int GRs;
	cout<<"DIMENSIONAL WAND"<<endl;
	tRoll = TrapRoll();
while(perPlayer)
{
	GRs = 0;
	system("cls");
	cout<<"DIMENSIONAL WAND"<<endl;
	
	switch(tRoll)
	{
		case 1:
		cout<<"5 Idle Rolls with random diaper change and Ghost Regression. GR: Infantile. Stupified."<<endl;
		IRauto = 5;
		GRs = 1;
		break;
		
		case 2:
		cout<<"3 Idle Rolls with random diaper change and Ghost Regression. GR: Infantile. Stupified."<<endl;
		IRauto = 3;
		GRs = 1;
		break;
		
		case 3:
		cout<<"3 Idle Rolls. Random diaper change. GR: Shorty. Stupified."<<endl;
		IRauto = 3;
		break;
		
		case 4:
		cout<<"2 Idle Rolls. Random diaper change. GR: Shorty."<<endl;
		break;
		
		case 5:
		cout<<"1 Idle Roll. GR: Drooling."<<endl;
		break;
		
		case 6:
		cout<<"No effect, dodged."<<endl;
		break;
	}
	
	if(IRauto)
	{
		IdleRolls();
	}
	if(GRs)
	{
		for(int i = 0; i < GRs; i++)
		{
			sleep(1.2);
			randomGR(1);
		}
	}
	
	if(tRoll != 6)
	{
	perPlayer = YesNo();
	} else {
		cout<<"Press [Enter] to return to main menu."<<endl;
		getch();
	}
}
 }
 
 
 
void DrainDiaper(){									//Draining Diaper Trap
	perPlayer = true;
	system("cls");
	cout<<"DRAINING DIAPER TRAP"<<endl;
	tRoll = TrapRoll();
	int dice = 1;
	const int LOW = 1;
	const int HIGH = 10;
	time_t seconds;
	
while(perPlayer)
{
	system("cls");
	cout<<"DRAINING DIAPER TRAP"<<endl;
	
	switch(tRoll)
	{
		case 1:
		cout<<"3 Idle Rolls with a random Trap Diaper. Timer does not decrease."<<endl;
		IRauto = 3;
		break;
		
		case 2:
		cout<<"3 Idle Rolls with a random Trap Diaper. Timer decreases accordingly."<<endl;
		IRauto = 3;
		break;
		
		case 3:
		cout<<"2 Idle Rolls with a random Trap Diaper. Timer decreases accordingly."<<endl;
		IRauto = 2;
		break;
		
		case 4:
		cout<<"1 Idle Roll with a random Trap Diaper. Timer decreases accordingly."<<endl;
		IRauto = 1;
		break;
		
		case 5:
		cout<<"Random Trap Diaper for 1 less IR on lock."<<endl;
		break;
		
		case 6:
		cout<<"Random Trap Diaper for 2 less IR on lock."<<endl;
		break;
	}
	
	time(&seconds);
	srand((unsigned int) seconds);
	dice=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(IRauto)
	{
		sleep(1.2);
		IdleRolls();
	}
	
	cout<<endl<<"Player has diaper altered into diaper #"<<(dice + 19)<<endl;
	
	perPlayer = YesNo();
}
 }
void BabyVG(){										//Baby Video Game Room
	perPlayer = true;
	int rolls;
	int penalty;
	int pValue;
	int dice = 1;
	const int LOW = 1;
	time_t seconds;
	
	system("cls");
	cout<<"BABY VIDEO GAME ROOM"<<endl;
	tRoll = TrapRoll();
	
while(perPlayer)
{
	rolls = 0;
	penalty = 0;
	pValue = 0;

	system("cls");
	cout<<"BABY VIDEO GAME ROOM"<<endl;
	
	if(tRoll < 4)
	{
		cout<<"Diaper altered into Progress Bar Diaper."<<endl;
	}
	
	switch(tRoll)
	{
		case 1:
		cout<<"3 Idle Rolls. RB/MP +5 per hit, roll 1d4 + 4 for hits."<<endl;
		IRauto = 3;
		rolls = 4;
		penalty = 4;
		pValue = 5;
		break;
		
		case 2:
		cout<<"3 Idle Rolls. RB/MP +5 per hit, roll 1d4 + 2 for hits."<<endl;
		IRauto = 3;
		rolls = 4;
		penalty = 2;
		pValue = 5;
		break;
		
		case 3:
		cout<<"2 Idle Rolls. RB/MP + 4 per hit, 1d2 + 2 for hits."<<endl;
		IRauto = 2;
		rolls = 2;
		penalty = 2;
		pValue = 4;
		break;
		
		case 4:
		cout<<"2 Idle Rolls. RB/MP +3 per hit, 1d2 + 2 for hits."<<endl;
		IRauto = 2;
		rolls = 2;
		penalty = 2;
		pValue = 3;
		break;
		
		case 5:
		cout<<"1 Idle Roll. RB/MP +4 per hit, 1d2 for hits."<<endl;
		IRauto = 1;
		rolls = 2;
		penalty = 0;
		pValue = 4;
		break;
		
		case 6:
		cout<<"1 Idle Roll. No hits taken."<<endl;
		IRauto = 1;
		rolls = 0;
		break;
	}
	
	if(IRauto)
	{
		status = true;
		IdleRolls();
	}
	
	if(rolls)
	{
		sleep(1.2);
		
		time(&seconds);
		srand((unsigned int) seconds);
		dice=(rand()%((rolls-LOW)+LOW))+1;
		
		dice += penalty;
		
		cout<<"Player gains "<<(dice * pValue)<<" RB/MP."<<endl;
	}
	
	perPlayer = YesNo();
}
 }
void DiaperVG(){									//Diaper Video Game Room
	perPlayer = true;
	int rolls;
	int penalty;
	int pValue;
	int Upoints;
	int dice = 1;
	const int LOW = 1;
	time_t seconds;
	
	system("cls");
	cout<<"DIAPER VIDEO GAME ROOM"<<endl;
	tRoll = TrapRoll();
	
while(perPlayer)
{
	rolls = 0;
	penalty = 0;
	pValue = 0;
	Upoints = 3;

	system("cls");
	cout<<"DIAPER VIDEO GAME ROOM"<<endl;
	
	switch(tRoll)
	{
		case 1:
		cout<<"3 Idle Rolls. RB/EP +5 and UHP +3 per hit, roll 1d4 + 4 for hits."<<endl;
		IRauto = 3;
		rolls = 4;
		penalty = 4;
		pValue = 5;
		break;
		
		case 2:
		cout<<"3 Idle Rolls. RB/EP +5 and UHP +3 per hit, roll 1d4 + 2 for hits."<<endl;
		IRauto = 3;
		rolls = 4;
		penalty = 2;
		pValue = 5;
		break;
		
		case 3:
		cout<<"2 Idle Rolls. RB/EP + 4 and UHP +3 per hit, 1d2 + 2 for hits."<<endl;
		IRauto = 2;
		rolls = 2;
		penalty = 2;
		pValue = 4;
		break;
		
		case 4:
		cout<<"2 Idle Rolls. RB/EP +3 and UHP +2 per hit, 1d2 + 2 for hits."<<endl;
		IRauto = 2;
		rolls = 2;
		penalty = 2;
		pValue = 3;
		Upoints = 2;
		break;
		
		case 5:
		cout<<"1 Idle Roll. RB/EP +4 and UHP +3 per hit, 1d2 for hits."<<endl;
		IRauto = 1;
		rolls = 2;
		penalty = 0;
		pValue = 4;
		break;
		
		case 6:
		cout<<"1 Idle Roll. No hits taken."<<endl;
		IRauto = 1;
		rolls = 0;
		break;
	}
	
	if(IRauto)
	{
		status = true;
		IdleRolls();
		cout<<endl;
	}
	
	if(rolls)
	{
		sleep(1.2);
		
		time(&seconds);
		srand((unsigned int) seconds);
		dice=(rand()%((rolls-LOW)+LOW))+1;
		
		dice += penalty;
		
		cout<<"Player gains "<<(dice * pValue)<<" RB/EP and "<<(dice * Upoints)<<" UHP."<<endl;
	}
	
	if(tRoll < 4)
	{
		cout<<"Diaper altered into Progress Bar Diaper."<<endl;
	}
	
	perPlayer = YesNo();
}
 }
void DragonVG(){									//Dragon Video Game Room
	perPlayer = true;
	int rolls;
	int penalty;
	int pValue;
	int dice = 1;
	const int LOW = 1;
	time_t seconds;
	
	system("cls");
	cout<<"BABY VIDEO GAME ROOM"<<endl;
	tRoll = TrapRoll();
	
while(perPlayer)
{
	rolls = 0;
	penalty = 0;
	pValue = 0;

	system("cls");
	cout<<"BABY VIDEO GAME ROOM"<<endl;
	
	if(tRoll < 4)
	{
		cout<<"Diaper altered into Progress Bar Diaper."<<endl;
	}
	
	switch(tRoll)
	{
		case 1:
		cout<<"3 Idle Rolls. RB/BP +5 per hit, roll 1d4 + 4 for hits."<<endl;
		IRauto = 3;
		rolls = 4;
		penalty = 4;
		pValue = 5;
		break;
		
		case 2:
		cout<<"3 Idle Rolls. RB/BP +5 per hit, roll 1d4 + 2 for hits."<<endl;
		IRauto = 3;
		rolls = 4;
		penalty = 2;
		pValue = 5;
		break;
		
		case 3:
		cout<<"2 Idle Rolls. RB/BP + 4 per hit, 1d2 + 2 for hits."<<endl;
		IRauto = 2;
		rolls = 2;
		penalty = 2;
		pValue = 4;
		break;
		
		case 4:
		cout<<"2 Idle Rolls. RB/BP +3 per hit, 1d2 + 2 for hits."<<endl;
		IRauto = 2;
		rolls = 2;
		penalty = 2;
		pValue = 3;
		break;
		
		case 5:
		cout<<"1 Idle Roll. RB/BP +4 per hit, 1d2 for hits."<<endl;
		IRauto = 1;
		rolls = 2;
		penalty = 0;
		pValue = 4;
		break;
		
		case 6:
		cout<<"1 Idle Roll. No hits taken."<<endl;
		IRauto = 1;
		rolls = 0;
		break;
	}
	
	if(IRauto)
	{
		status = true;
		IdleRolls();
	}
	
	if(rolls)
	{
		sleep(1.2);
		
		time(&seconds);
		srand((unsigned int) seconds);
		dice=(rand()%((rolls-LOW)+LOW))+1;
		
		dice += penalty;
		
		cout<<"Player gains "<<(dice * pValue)<<" RB/BP."<<endl;
	}
	
	perPlayer = YesNo();
}
 }
void LockDoor(){									//Lock Door
	perPlayer = true;
	int counter;
	time_t seconds;
	int dice;
	int die;
	int rounding;
	const int TLOW = 1;
	const int THIGH = 2;
	system("cls");
	cout<<"Lock Door"<<endl;
	
	tRoll = TrapRoll();
	
while(perPlayer)
{
	counter = 0;
	rounding = 0;
	system("cls");
	cout<<"Lock Door"<<endl;
	
	if(tRoll < 6)
	{
		cout<<"Diaper Lock";
	}
	if(tRoll < 4)
	{
		cout<<". ";
	}
	
	switch(tRoll)
	{
		case 1:
		counter = 4;
		break;
		
		case 2:
		counter = 3;
		break;
		
		case 3:
		counter = 2;
		break;
		
		case 4:
		cout<<" for 1 less IR on timer. ";
		counter = 1;
		break;
		
		case 5:
		cout<<" for 2 less IR on timer. ";
		counter = -1;
		break;
		
		case 6:
		cout<<"No effect, first key was the right one."<<endl;
		break;
	}
	
if(tRoll != 6)
{
	if((counter % 2 != 0)&&(counter > 0))
	{
		rounding = 1;
	}
		
	dice = Die3();
	
	if(counter == 0)
	{
		dice = 3;
		rounding = 1;
	} else if(counter == -1){
		die = Die100();
		
		if(die > 50)
		{
			dice = 3;
			rounding = 1;
		} else {
			dice = 4;
		}
	}
	
	switch(dice)
	{
		case 1:
		cout<<"Player rolls "<<counter<<" Wet Use Checks."<<endl;
		UCauto = counter;
		break;
		
		case 2:
		cout<<"Player rolls "<<counter<<" Mess Use Checks."<<endl;
		UCauto = counter;
		break;
		
		case 3:
		UCauto = counter / 2 + rounding;
		cout<<"Player rolls "<<UCauto<<" Use Checks."<<endl;
		break;
		
		case 4:
		cout<<"Player does not make any additional rolls."<<endl;
		break;
		
		default:
		cout<<"ERROR. Dice generated wrong."<<endl;
		break;
	}
	
	if(UCauto)
	{
		UCprompt();
	}
}

	perPlayer = YesNo();
}
 }
void TickleMachine(){								//Tickling Machine
	perPlayer = true;
	int inten;
while(perPlayer)
{
	inten = 0;
	system("cls");
	cout<<"TICKLING MACHINE"<<endl;
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"Silly lv. 2 and Normal IT for RB. Minimum PL until exiting trap."<<endl;
		inten = 2;
		break;
		
		case 2:
		cout<<"Silly lv. 2 and Small IT for RB. Minimum PL until exiting trap."<<endl;
		inten = 1;
		break;
		
		case 3:
		cout<<"Silly lv. 1 and Small IT for RB. PL -10 until exiting trap."<<endl;
		inten = 1;
		break;
		
		case 4:
		cout<<"Silly lv. 1 and Tiny IT for RB. PL -8 until exiting trap."<<endl;
		break;
		
		case 5:
		cout<<"Tiny IT for RB. PL -5 until exiting trap."<<endl;
		break;
		
		case 6:
		cout<<"No effect, avoided."<<endl;
		break;
		
		default:
		cout<<"ERROR, trap roll broken."<<endl;
		break;
	}
	
	if(tRoll != 6)
	{
		Itotal = Intensity(inten);
		
		cout<<"Player gains "<<Itotal<<" RB."<<endl;
	}
	
	perPlayer = YesNo();
}
 }
void Energy(){										//Energy Room
	perPlayer = true;
	const int LOW = 1;
	const int HIGH = 100;
	int dice;
	time_t seconds;
	
while(perPlayer)
{
	system("cls");
	cout<<"ENERGY ROOM"<<endl;
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"Player gains Skewed Aura and rolls 1 Forced Idle Roll."<<endl;
		cout<<"Press [Enter] to begin calculation.";
		getch();
		FIRauto = 1;
		ForcedIR();
		break;
		
		case 2:
		Itotal = Intensity(0);
		cout<<"Player gains Skewed Aura, and Tiny IT roll for "<<Itotal<<" RB."<<endl;
		break;
		
		case 3:
		cout<<"Player gains Skewed Aura."<<endl;
		break;
		
		case 4:
		cout<<"Player gains GR: Devolution."<<endl;
		break;
		
		case 5:
		sleep(1);
		
		dice = Die100();
		
		if(dice > 50)
		{
			cout<<"Player gains GR: Devolution."<<endl;
		} else {
			cout<<"No effect, resisted."<<endl;
		}
		break;
		
		case 6:
		cout<<"No effect, resisted."<<endl;
		break;	
		
		default:
		cout<<"ERROR"<<endl;
		break;
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void BossBomb(){									//Boss Bomb
	perPlayer = true;
	
	int die;
	int dTotal;
	const int LOW = 1;
	int HIGH = 5;
	time_t seconds;
	
	
	system("cls");
	cout<<"BOSS BOMB"<<endl;
	
	tRoll = TrapRoll();
	
while(perPlayer)
{
	dTotal = 10;
	system("cls");
	cout<<"BOSS BOMB"<<endl;
	
	switch(tRoll)
	{
		case 1:
		HIGH = 30;
		cout<<"Critical failure"<<endl;
		break;
		
		case 2:
		HIGH = 25;
		cout<<"Heavy failure"<<endl;
		break;
		
		case 3:
		HIGH = 20;
		cout<<"Expected failure"<<endl;
		break;
		
		case 4:
		HIGH = 15;
		cout<<"Resisted"<<endl;
		break;
		
		case 5:
		HIGH = 10;
		cout<<"Partial success."<<endl;
		break;	
		
		case 6:
		cout<<"Full success. No effect, realized fake."<<endl;
		break;
		
		default:
		cout<<"ERROR"<<endl;
	}
	
	if(tRoll != 6)
	{
		for(int i=0; i < 2; i++)
		{
			time(&seconds);
			srand((unsigned int) seconds);
			dTotal+=(rand()%((HIGH-LOW)+LOW))+1;
			
			if(i == 0){	sleep(1.2); }
		}
		
		switch(tRoll)
		{
			case 1:
			cout<<"Player gains 2 Use Levels in both categories."<<endl;
			break;
			
			case 2:
			cout<<"Player gains 1 Use Level in both categories."<<endl;
			break;
			
			case 3:
			HIGH = 2;
			time(&seconds);
			srand((unsigned int) seconds);
			die=(rand()%((HIGH-LOW)+LOW))+1;
			if(die == 1)
			{
				cout<<"Player gains 1 Wet Use Level."<<endl;
			} else {
				cout<<"Player gains 1 Mess Use Level."<<endl;
			}
			break;
			
			case 4:
			case 5:
			UCauto = 2;
			UCprompt();
			break;
			
			default:
			cout<<"USE ERROR"<<endl;
			break;
		}
		
		if((tRoll < 4)||((Die100() <= 50)&&(tRoll == 4))||((Die100() <= 25)&&(tRoll == 5)))
		{
			cout<<"Party is Stupified (first generation only)."<<endl;
		} else {
			cout<<"No Stupified status to party."<<endl;
		}
		
		cout<<"Player gains "<<dTotal<<" RB."<<endl;	
	}
	
	
	perPlayer = YesNo();
}
 }
 
 
 
void Ambush(){										//Ambush
	system("cls");
	cout<<"AMBUSH"<<endl<<endl;
	
	cout<<"Generated a Caretaker of #"<<CareGenerator(false)<<endl;
	
	cout<<"Roll to hit against two players as if Caretaker is attacking both. Caretaker gets a 2 on initiative in ensuing combat."<<endl;
	
	cout<<"Press [Enter] to return to main menu."<<endl;
	getch();
 }
 
 
 
void PlushPile(){									//Plushie Pile
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"PLUSHIE PILE"<<endl;
	
	tRoll = TrapRoll();
	
	IRauto = 1;
	
	switch(tRoll)
	{
		case 1:
		cout<<"Advocate for 2 IR and Snuggler. 1 Idle Roll, also applied to EP."<<endl;
		break;
		
		case 2:
		cout<<"Advocate for 2 IR and Snuggler. 1d5 RB/EP."<<endl;
		break;
		
		case 3:
		cout<<"Advocate for 1 IR and Snuggler. 1d5 RB/EP."<<endl;
		break;
		
		case 4:
		cout<<"Snuggler for 1 IR. 1d5 RB/EP."<<endl;
		break;
		
		case 5:
		cout<<"Snuggler for 1 IR."<<endl;
		break;
		
		case 6:
		cout<<"No effect, resisted."<<endl;
		IRauto = 0;
		break;
		
		default:
		cout<<"ERROR"<<endl;
		break;
	}
	
	cout<<endl;
	
	if(IRauto)
	{
		IdleRolls();
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void DiapSuit(){									//Diaper Suit Ambush
	int dice;
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"DIAPER SUIT AMBUSH"<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"Hypno Suit AND Bondage Suit. Diaper Lock."<<endl;
		break;
		
		case 2:
		cout<<"Hypno Suit AND Bondage Suit."<<endl;
		break;
		
		case 3:
		dice = Die100();
		if(dice > 50)
		{
			cout<<"Hypno Suit."<<endl;
		} else {
			cout<<"Bondage Suit."<<endl;
		}
		break;
		
		case 4:
		dice = Die100();
		if(dice > 50)
		{
			cout<<"Hypno Suit ";
		} else {
			cout<<"Bondage Suit ";
		}
		cout<<" for 2 IR."<<endl;
		break;
		
		case 5:
		dice = Die100();
		if(dice > 50)
		{
			cout<<"Hypno Suit ";
		} else {
			cout<<"Bondage Suit ";
		}
		cout<<" for 1 IR."<<endl;
		break;
		
		case 6:
		cout<<"No effect, dodged."<<endl;
		break;
		
		default:
		cout<<"ERROR"<<endl;
		break;
	}
	
	perPlayer = YesNo();
}
 }
	
	
	
void CareSpecial(){									//Caretaker's Special Room
	int dice;

	system("cls");
	cout<<"CARETAKER'S SPECIAL ROOM"<<endl;
	cout<<"Warning! This program may take a moment to load."<<endl;
	
	do{
		dice = CareGenerator(false);
		sleep(1.2);
	}while(dice == 7);
	
	cout<<"Generated Caretaker of #"<<dice<<endl;
	
	do{
		//Trap Artist roll
		dice = Die10();
		sleep(1.4);
	}while(dice == 1);
	
	cout<<"Generated Trap Artist room of #"<<dice<<endl;
	
	cout<<endl<<"Press [Enter] to return to main menu."<<endl;
	getch();
 }
 
 
 
void Ritual(){										//Baby Ritual
	int ro[3];
	ro[0] = 0;
	ro[1] = 0;
	ro[2] = 0;
	int dice;
	int i;

	system("cls");
	cout<<"BABY RITUAL"<<endl;
	cout<<"Warning, this may take a while!"<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		for(i = 0; i < 3; i++)
		{
			ro[i] = Misfire(false);
			sleep(1.2);
			
			if(((i == 1)&&(ro[1] == ro[0]))||((i == 2)&&(ro[2] == ro[1])))
			{
				i--;
			}
		}
		cout<<"Magical misfire rolls of: #"<<ro[0]<<", #"<<ro[1]<<", and #"<<ro[2]<<endl;
		break;
		
		case 2:
		for(i = 0; i < 2; i++)
		{
			ro[i] = Misfire(false);
			sleep(1.2);
			
			if((i == 1)&&(ro[1] == ro[0]))
			{
				i--;
			}
		}
		cout<<"Magical misfire rolls of: #"<<ro[0]<<"and #"<<ro[1]<<endl;
		break;
		
		case 3:
		ro[0] = Misfire(false);
		cout<<"Magical misfire roll of: #"<<ro[0]<<endl;
		break;
		
		case 4:
		dice = Die20() + 3;
		sleep(1.5);
		ro[0] = Misfire(false);
		
		cout<<"Calculate hit/miss on players with an AR of "<<dice<<" and magical misfire roll of #"<<ro[0]<<endl;
		break;
		
		case 5:
		cout<<"No effect, symbol disrupted."<<endl;
		break;
		
		case 6:
		cout<<"Ritual hijacked, players get a free cast of magic!"<<endl;
		break;
		
		default:
		cout<<"ERROR"<<endl;
		break;
	}
	
	cout<<"Press [Enter] to return to main menu."<<endl;
	getch();
	
 }
 
 
 
void ArtRoom(){										//Smeargle's Art Room
	int inspire;
	perPlayer = true;
while(perPlayer)
{
	inspire = 0;
	system("cls");
	cout<<"SMEARGLE'S ART ROOM"<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		Itotal = Intensity(1);
		
		cout<<"Inflicts Pinkified or Powdered for 4 IR (player picks)."<<endl;
		cout<<"IT roll of "<<Itotal<<" RB/BP/EP."<<endl;
		break;
		
		case 2:
		Itotal = Intensity(0);
		
		cout<<"Inflicts Pinkified or Powdered (player picks)."<<endl;
		cout<<"IT roll of "<<Itotal<<" RB/BP/EP."<<endl;
		break;
		
		case 3:
		cout<<"Inflicts Pinkified or Powdered (player picks)."<<endl;
		break;
		
		case 4:
		cout<<"Inflicts Pinkified or Powdered for 2 IR (player picks)."<<endl;
		break;
		
		case 5:
		cout<<"Inflicts Pinkified or Powdered for 1 IR(player picks)."<<endl;
		break;
		
		case 6:
		inspire = Die3();
		sleep(1.7);
		inspire = Die3();
		
		cout<<"Players are inspired by the art for "<<inspire<<" RB/BP/EP."<<endl;
		break;
		
		default:
		cout<<"ERROR."<<endl;
		break;
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void TagAlong(){									//Mimikyu's Tag-Along
	system("cls");
	cout<<"MIMIKYU'S TAG-ALONG"<<endl;
	
	tRoll = TrapRoll();
	
	tRoll = 1;
	
	switch(tRoll)
	{
		case 1:
		cout<<"Lowest RB player suffers Mimikyu Plush for 4 IR. Small IT for RB to all players."<<endl;
		Itotal = Intensity(1);
		cout<<"Players rolled "<<Itotal<<" RB."<<endl;
		break;
		
		case 2:
		cout<<"Lowest RB player suffers Mimikyu Plush. Tiny IT for RB to all players."<<endl;
		Itotal = Intensity(0);
		cout<<"Players rolled "<<Itotal<<" RB."<<endl;
		break;
		
		case 3:
		cout<<"Lowest RB player suffers Mimikyu Plush."<<endl;
		break;
		
		case 4:
		cout<<"Random player suffers Mimikyu Plush for 2 IR."<<endl;
		break;
		
		case 5:
		cout<<"Random player suffers Mimikyu Plush for 1 IR."<<endl;
		break;
		
		case 6:
		cout<<"No effect, ignored."<<endl;
		break;
		
		default:
		cout<<"ERROR"<<endl;
		break;
	}
	
	cout<<endl<<"Press [Enter] to return to main menu.";
	getch();
	
 }
 
 
 
void Storeroom(){									//Item Room
	int rolls = 0;
	int curses = 2;
	system("cls");
	cout<<"ITEM ROOM"<<endl;
	
	int items[4];
	items[0] = 0;
	items[1] = 0;
	items[2] = 0;
	items[3] = 0;
	
	int die = 1;
	const int LOW = 1;
	int HIGH = 13;
	time_t seconds;
	
	cout<<"Loading";
	
	//test for cursed items	
	for(int i = 0; i < 4; i++)
	{
		
	if(curses == 0)
	{
		HIGH = 8;
	}
		
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 8)
	{
		curses -= 1;
	}
	
	items[i] = die;
	cout<<".";
	sleep(1.2);
	}
	
	cout<<endl<<endl<<"Found items of numbers:"<<endl;
	for(int i = 0; i < 4; i++)
	{
		cout<<items[i];
		
		if(items[i] > 8)
		{
			cout<<" (cursed)";
		}
		
		cout<<endl;
	}
	
	cout<<endl<<"Press [Enter] to return to main menu.";
	getch();
	
 }
 
 
 
void TrainPotty(){									//Training Potties
	int dice;
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"TRAINING POTTIES"<<endl;
	cout<<"Warning: program may load in spurts."<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"Player gains GR: Quick Filler & Diaper Trained, and 1 Use Level in both categories."<<endl;
		break;
		
		case 2:
		dice = Die100();
		cout<<"Player gains ";
		if(dice > 50)
		{
			cout<<"GR: Quick Filler";
		} else {
			cout<<"GR: Diaper Trained";
		}
		cout<<" and 1 Use Level in both categories."<<endl;
		break;
		
		case 3:
		dice = Die100();
		cout<<"Player gains ";
		if(dice > 50)
		{
			cout<<"GR: Quick Filler.";
		} else {
			cout<<"GR: Diaper Trained.";
		}
		sleep(1.7);
		dice = Die100();
		if(dice > 50)
		{
			cout<<"Gained 1 Wet Use Level."<<endl;
		} else {
			cout<<"Gained 1 Mess Use Level."<<endl;
		}
		break;
		
		case 4:
		cout<<"Player gains GR: Diaper Trained and rolls 2 Use Checks."<<endl;
		UCauto = 2;
		UCprompt();
		break;
		
		case 5:
		cout<<"Player gains GR: Diaper Trained and rolls 1 Use Check."<<endl;
		UCauto = 1;
		UCprompt();
		break;
		
		case 6:
		cout<<"Player's diaper mysteriously cleaned to 0 Use Levels."<<endl;
		break;
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void ArmyHoard(){									//Plush Army Hoard
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"PLUSH ARMY HOARD"<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"Player gains Help Hoard, rolls Normal IT for RB/BP/EP, and gains GR: Baby Clothes."<<endl;
		Itotal = Intensity(2);
		break;
		
		case 2:
		cout<<"Player gains Help Hoard, rolls Small IT for RB/BP/EP, and gains GR: Baby Clothes."<<endl;
		Itotal = Intensity(1);
		break;
		
		case 3:
		cout<<"Player gains 2 Helpers, rolls Small IT for RB/BP/EP, and gains GR: Baby Clothes."<<endl;
		Itotal = Intensity(1);
		break;
		
		case 4:
		cout<<"Player gains 2 Helpers, and rolls Tiny IT for RB/BP/EP."<<endl;
		Itotal = Intensity(0);
		break;
		
		case 5:
		cout<<"Player gains 1 Helper, and rolls Tiny IT for RB/BP/EP."<<endl;
		Itotal = Intensity(0);
		break;
		
		case 6:
		cout<<"Player gains 1 Helper, despite their best attempts."<<endl;
		break;
	}
	
	if(tRoll != 6)
	{
		cout<<"Player rolled "<<Itotal<<" for RB/BP/EP."<<endl;
	}
	
	perPlayer = YesNo();
}
 }
 
 
 
void SeekBottles(){									//Seeking Bottles
	int die = 1;
	const int LOW = 1;
	const int HIGH = 8;
	time_t seconds;
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"SEEKING BOTTLES"<<endl;
	
	tRoll = TrapRoll();
	
	switch(tRoll)
	{
		case 1:
		cout<<"Player gains Auto-Bottle with 24 WHP. Inflicts Pacified for the next encounter."<<endl;
		break;
		
		case 2:
		cout<<"Player gains Auto-Bottle with 18 WHP. Inflicts Pacified for the next Encounter."<<endl;
		break;
		
		case 3:
		cout<<"Player gains Auto-Bottle with 18 WHP."<<endl;
		break;
		
		case 4:
		cout<<"Player gains Auto-Bottle with 12 WHP."<<endl;
		break;
		
		case 5:
		cout<<"Player gains Auto-Bottle with ";
		
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		
		cout<<(die + 2)<<" WHP."<<endl;
		break;
		
		case 6:
		cout<<"No effect, avoided."<<endl;
		break;
	}
	
	perPlayer = YesNo();
}
 }



//Toilet Trained Encounters///////////////////////////////////////////////////////////////
void TTKanga(){									//TT Kangaskhan
		perPlayer = true;
	while(perPlayer)
	{
		cout<<"TT KANGASKHAN"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
			check = true;
		while(check){
			cout<<"Was the player Pouched/Finished (y/n)? ";
			
			cin>>charput;

			if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
				cin.clear();
				cin.ignore();
				charput = 'q';
				cout<<"Please enter y or n. "<<endl;
			} else {
				check = false;
				if((charput == 'y')||(charput == 'Y')){
					Itotal = Intensity(2);
				} else {
					Itotal = Intensity(1);
				}
			}
		}
		
		if(forfeit){Itotal *= 0.5;}
		
		cout<<"Player gains "<<Itotal<<" RB/BP."<<endl;
		
		perPlayer = YesNo();
	}
}



void TTMilk(){									//TT Miltank
		perPlayer = true;
	while(perPlayer)
	{
		cout<<"TT Miltank"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(1);
		
		if(forfeit){Itotal *= 0.5;}
		
		cout<<"Player gains "<<Itotal<<" RB/BP."<<endl;
		cout<<"A Clamped player gains 1 WUL. A player finished with a Used Finisher gains 1 MUL."<<endl;
		
		perPlayer = YesNo();
	}
}



void TTLucar(){									//TT Lucario
		perPlayer = true;
	while(perPlayer)
	{
		cout<<"TT LUCARIO"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
			check = true;
		while(check){
			cout<<"Does this player have Skewed Aura (y/n)? ";
			
			cin>>charput;

			if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
				cin.clear();
				cin.ignore();
				charput = 'q';
				cout<<"Please enter y or n. "<<endl;
			} else {
				check = false;
				
				cout<<endl;
				
				Itotal = Intensity(1);
				
				if((charput == 'y')||(charput == 'Y')){
					randomGR(1);
				}
				
				if(forfeit){Itotal *= 0.5;}
				
				cout<<"Player gains "<<Itotal<<" RB/MP/BP."<<endl;
			}
		}
		
		perPlayer = YesNo();
	}
}



void TTGard(){									//TT Gardevoir
		perPlayer = true;
	while(perPlayer)
	{
		cout<<"TT GARDEVOIR"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(2);
		
			check = true;
		while(check){
			cout<<"Was the player Hypnotized (h) or Brainwashed (b)? N for no: ";
			
			cin>>charput;

			if((cin.fail())||((charput != 'h')&&(charput != 'H')&&(charput != 'B')&&(charput != 'b')&&(charput != 'N')&&(charput != 'n'))){
				cin.clear();
				cin.ignore();
				charput = 'q';
				cout<<"Please enter y, b, or n. "<<endl;
			} else {
				check = false;
				
				switch(charput){
					case 'b':
					case 'B':
						cout<<"Player gains 50 RB. ";
						
					case 'h':
					case 'H':
						randomGR(2);
					break;
					
					case 'n':
					case 'N':
					break;
					
					default:
						cout<<"ERROR."<<endl;
					break;
				}
			}
		}
		
		if(tdForfeit){forfeit = Forfeit();}
		
		cout<<"Player gains "<<Itotal<<" RB/MP."<<endl;
		
		perPlayer = YesNo();
	}
}



void TTSerper(){								//TT Serperior
	int fifty;
		perPlayer = true;
	while(perPlayer)
	{
		cout<<"TT SERPERIOR"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
		fifty = Die100();
		
		Itotal = Intensity(1);
		UCauto = 3;
		UCprompt();
		
		if(forfeit){
			Itotal *= 0.5;
			if(fifty > 50){
				cout<<"Player gains 2 stacks of Holding Help."<<endl;
			} else {
				cout<<"Player avoids the 2 stacks of Holding Help."<<endl;
			}
		} else {
			cout<<"Player gains 2 stacks of Holding Help."<<endl;
		}
		
		cout<<"Player gains "<<Itotal<<" RB/EP and 1 Use Level in both categories."<<endl;
		
		perPlayer = YesNo();
	}
}



void TTSlow(){									//TT Slowpoke
		perPlayer = true;
	while(perPlayer)
	{
		cout<<"TT SLOWPOKE"<<endl;
		
		cout<<"Because Slowpoke's effects ignore forfeit, the forfeit prompt is ignored."<<endl<<endl;
		
		cout<<"Before any further effect, the player gains RB/MP +10. The following is done with the new state of the player."<<endl;
		cout<<"Press [Enter] to begin the Idle Roll."<<endl;
		getch();
		
		IRauto = 5;
		IdleRolls();
		
		if(Die100() <= 60){
			cout<<"Player gains GR: Lazy."<<endl;
		}
		
		perPlayer = YesNo();
	}
}



void TTPrimar(){								//TT Primarina
	cout<<"Loading...";
	
	bool enhance = false;
	int fifty;
	string printType = "";
	int die;
	int total = 0;
	int bombCount = Die3();
	sleep(1.2);
	int bombType = Die3();
	
		perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"TT PRIMARINA (warning, generation takes a moment)"<<endl;
		
		cout<<"Because Primarina's effects ignore forfeit, forfeit will not be prompted."<<endl<<endl;
	
	switch(bombType)
	{
		case 1:
		cout<<"Vanilla";
		printType = "MP";
		break;
		
		case 2:
		fifty = Die100();
		if(die > 50){
			enhance = true;
		}
		sleep(1.2);
		
		cout<<"Powder";
		printType = "EP";
		break;
		
		case 3:
		cout<<"Fruity";
		printType = "BP";
		break;
		
		default:
		cout<<"ERROR, BOMB TYPE FAILED"<<endl;
		break;
	}

	cout<<" Bombs rain down on the party!"<<endl;
	
	for(int i = 0; i < 3; i++)
	{
		sleep(1.4);
		total += Die4();
	}
	
	if(total<20){
		cout<<"Player gains "<<total<<" "<<printType<<" and 10 RB.";
	} else {
		cout<<"Player gains "<<total<<" "<<printType<<" and "<<(total / 2)<<" RB.";
	}

	if(enhance){
		cout<<" Player gains a stack of Enhancement.";
	}
	cout<<endl;
	
	total = 0;
	enhance = false;
	perPlayer = YesNo();
   }
}



void TTLuxray(){								//TT Luxray
		perPlayer = true;
	while(perPlayer)
	{
		cout<<"TT LUXRAY"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(1);
		
		if(forfeit){
			Itotal *= 0.5;
			sleep(1.2);
			
			if(Die100()>50){
				cout<<"Player gains GR: Diaper Suit."<<endl;
			} else {
				cout<<"Player avoided GR: Diaper Suit."<<endl;
			}
		} else {
			cout<<"Player gains GR: Diaper Suit."<<endl;
		}
		
		cout<<"Player gains "<<Itotal<<" RB/MP/EP. Should the party reencounter Luxray from Stubborn,"<<endl;
		cout<<"the party will start with a stack of Obedience."<<endl;
		
		perPlayer = YesNo();
	}
}



void TTAudino(){								//TT Audino
		perPlayer = true;
	while(perPlayer){
		cout<<"TT AUDINO"<<endl;
		
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(1);
		
		if(forfeit){
			Itotal *= 0.5;
			sleep(1.2);
			
			if(Die100()>50){
				cout<<"Player suffers 2 stacks of Holding Help."<<endl;
			} else {
				cout<<"Player avoided the stacks of Holding Help."<<endl;
			}
		} else {
			cout<<"Player suffers 2 stacks of Holding Help."<<endl;
		}
		
		cout<<"Player gains "<<Itotal<<" RB/BP/EP."<<endl;
		
		cout<<"For the following UC roll, treat the player as if their PL is at minimum."<<endl;
		
		UCauto = 3;
		UCprompt();
		
		perPlayer = YesNo();
	}
}



void TTPotionChal(){							//TT Potion Challenge
	int dice;
	int extra;

	system("cls");
	cout<<"TT POTION CHALLENGE"<<endl<<endl;
	
		dice = Die4();

	switch(dice)
	{
		case 1:
			cout<<"No effect. Lucky devil!"<<endl;
		break;
			
		case 2:
			cout<<"Player gains 10 RB/MP and GR: Drooling."<<endl;
		break;
		
		case 3:
			cout<<"Player gains 10 RB/BP and GR: Baby Fat."<<endl;
		break;
		
		case 4:
			sleep(1.2);
			cout<<"Player gains 10 RB/EP";
			
			extra = Die100();
			
			if(extra % 2 == 0){
				cout<<" and 1 WUL";
			}
			if(extra % 3 == 0){
				cout<<" and 1 MUL";
			} else if(extra % 2 != 0){
				cout<<" and rolls 2 UCs."<<endl;
				
				UCauto = 2;
				UCprompt();
			}
			
			if((extra % 2 == 0)||(extra % 3 == 0)){
				cout<<"."<<endl;
			}
		break;
		
		default:
		cout<<"ERROR"<<endl;
		break;
		
	}
	
	cout<<"Press [Enter] to return to main menu."<<endl;
	getch();
}



void TTPresent(){								//TT Presentation
		system("cls");
		cout<<"TT PRESENTATION"<<endl;
		
		tRoll = TrapRoll();
		
		switch(tRoll){
			case 1:
			cout<<"Player is Brainwashed for 2 Idle Rolls. For the Idle Roll, add the same RB total to MP."<<endl;
			IRauto = 2;
			IdleRolls();
			break;
			
			case 2:
			cout<<"Player is Brainwashed for an Idle Roll. For the Idle Roll, add the same RB total to MP."<<endl;
			IRauto = 1;
			IdleRolls();
			break;
			
			case 3:
			cout<<"Player is Hypnotized for 1 IR. For the Idle Roll, add the same RB total to MP."<<endl;
			IRauto = 1;
			IdleRolls();
			break;
			
			case 4:
			HCauto = 2;
			HypnoCheck(true);
			
			IRauto = 1;
			IdleRolls();
			break;
			
			case 5:
			HCauto = 1;
			HypnoCheck(true);
			
			IRauto = 1;
			IdleRolls();
			break;
			
			case 6:
			IRauto = 1;
			IdleRolls();
			break;
			
			default:
			cout<<"ERROR"<<endl;
			break;
		}
		
		cout<<"Press [Enter] to return to main menu."<<endl;
		getch();
}



void TTPaciDoor(){								//TT Pacifier Door
	int doubler = 0;
	int dice;
	int oldDie;
	int die = 1;
	const int LOW = 1;
	const int HIGH = 2;
	time_t seconds;	
	
	
	system("cls");
	perPlayer = true;
while(perPlayer){
	cout<<"TT PACIFIER DOOR"<<endl;
do{
	if(doubler > 0)
	{
		oldDie = dice;
		sleep(1.3);
		
		if(oldDie != 4)
		{
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		
			switch(oldDie)
			{
				case 1:
				dice = die + 1;
				break;
				
				case 2:
				if(die == 2)
				{
				dice = 3;
				}
				break;
				
				case 3:
				dice = die;
				break;
				
				default:
				cout<<"ERROR with generating reroll"<<endl;
			}
		
		} else {
			dice = Die3();
		}
		
	} else {
		dice = Die4();
	}
	
	switch(dice)
	{
		case 1:
		cout<<"Player gains 5 RB."<<endl;
		break;
		
		case 2:
		cout<<"Player gains 10 RB and their diaper alters into Pacifier print."<<endl;
		cout<<"Player rolls UC at minimum Potty Limit until diaper is used, and 1 Idle Roll afterwards."<<endl;
		rollUntil = true;
		UCauto = 1;
		UCprompt();
		
		IRauto = 1;
		IdleRolls();
		break;
		
		case 3:
		cout<<"GR: Drooling. Player rolls 2 Idle Rolls."<<endl;
		IRauto = 2;
		IdleRolls();
		break;
		
		case 4:
		doubler = 3;
		cout<<"Rolled a 4! Generating two effects."<<endl<<endl<<endl;
		
		break;
		
	}
	
	if(doubler > 0)
	{
		doubler -= 1;
		
	}
	if(doubler == 1)
	{
		cout<<endl;
	}
}while(doubler > 0);
	
	perPlayer = YesNo();
	system("cls");
}
}



void TTBBomb(){									//TT Boss Bomb
	int bPoints = 0;
	char fifty = ' ';
	system("cls");
	cout<<"TT Boss Bomb"<<endl;
	tRoll = TrapRoll();
		
		switch(tRoll){
			case 1:
				cout<<"Party is Stupified and gains 2 MUL/WUL. Party gains just enough points to gain 2 RTiers."<<endl;
			break;
			
			case 2:
				bPoints = 10 + Die100()/2;
				sleep(1.1);
				bPoints += Die100()/2;
				cout<<"Party gains "<<bPoints<<" RB, becomes Stupified, and gains 1 WUL/MUL."<<endl;
			break;
			
			case 3:
				if(Die100() > 50){
					fifty = 'M';
				} else {
					fifty = 'W';
				}
				sleep(1.1);
				bPoints = 10 + Die100()/4;
				sleep(1.2);
				bPoints += Die100()/4;
				
				cout<<"Party gains "<<bPoints<<" RB, becomes Stupified, and gains 1 "<<fifty<<"UL."<<endl;
			break;
			
			case 4:
				bPoints = 10 + Die20();
				sleep(1.2);
				
				cout<<"Party gains "<<bPoints<<" RB";
				
				if(Die100() >50){
					cout<<" and becomes Stupified.";
				}
				cout<<endl;
				
				UCauto = 2;
				UCprompt();
			break;
			
			case 5:
				bPoints = 10 + Die10();
				sleep(1.2);
				
				cout<<"Party gains "<<bPoints<<" RB";
				
				if(Die100() <= 25){
					cout<<" and becomes Stupified.";
				}
				cout<<endl;
				
				UCauto = 2;
				UCprompt();
			break;
			
			case 6:
				cout<<"No effect, party realized the fake."<<endl;
			break;
			
			default:
			cout<<"ERROR"<<endl;
			break;
		}
		
	cout<<"Press [Enter] to return to main menu."<<endl;
	getch();
}



void TTPowP(){									//TT Powder Path
	int trapSize = Die3();
	sleep(1.5);
	trapSize += Die3() - 1;
	
	int counter;
	int Ptotal;

	perPlayer = true;
while(perPlayer)
{
	counter = 0;
	Ptotal = 0;
	
	system("cls");
	cout<<"TT POWDER PATH"<<endl<<endl;
	
	cout<<"Calculating";
	
	//generate trap triggers
	for(int i = 0; i < trapSize; i++)
	{
		if(Die20() > 10)
		{
			counter++;
		}
		sleep(1.4);
		cout<<".";
		
	}
	if(counter == 0)
	{
		counter = 1;
	}
	
	cout<<endl<<"Generating";
	
	//Point gain
	for(int i = 0; i < counter; i++)
	{
		Ptotal += Die6() + 1;
		sleep(1.8);
		cout<<".";
	}
	
	cout<<endl<<endl;
		
		
	//Output
	if((counter > 1)&&(Ptotal > (counter * 3))){
		cout<<"Player gains 1 MUL/WUL."<<endl;
	} else {
	UCauto = counter;
		UCprompt();
	}
	
	if(Ptotal < 10){ Ptotal = 10; }
	
	cout<<"Player gains "<<Ptotal<<" RB/MP/BP/EP and tripped "<<counter<<" traps for a hallway of size "<<trapSize<<"."<<endl;
	
	perPlayer = YesNo();
}
}



void TTStoreroom(){								//TT Storeroom
	int rolls = 0;
	system("cls");
	cout<<"TT ITEM ROOM"<<endl;
	cout<<"(No cursed items can be generated)"<<endl;
	
	int items[3];
	items[0] = 0;
	items[1] = 0;
	items[2] = 0;
	
	int die = 1;
	const int LOW = 1;
	int HIGH = 8;
	time_t seconds;
	
	cout<<"Loading";
	
	//test for cursed items	
	for(int i = 0; i < 3; i++)
	{
		
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	items[i] = die;
	cout<<".";
	sleep(1.2);
	}
	
	cout<<endl<<endl<<"Found items of numbers:"<<endl;
	for(int i = 0; i < 3; i++)
	{
		cout<<items[i];
		cout<<endl;
	}
	
	cout<<endl<<"Press [Enter] to return to main menu.";
	getch();
}



void TTMirror(){								//TT Odd Mirror
	
		system("cls");
		cout<<"TT ODD MIRROR"<<endl;
		
		tRoll = TrapRoll();
		
		switch(tRoll){
			case 1:
			UCauto = 3;
			UCprompt();
			
			cout<<"Party gains 20 RB, 2 Ghost Regressions from their Resonances, and becomes Stupified."<<endl;
			break;
			
			case 2:
			UCauto = 2;
			UCprompt();
			
			cout<<"Party gains 15 RB and 1 Ghost Regression from their Resonance."<<endl;
			break;
			
			case 3:
			UCauto = 1;
			UCprompt();
			
			cout<<"Party gains 10 RB and 1 Ghost Regression from their Resonance."<<endl;
			break;
			
			case 4:
			if(Die100() > 50){
				cout<<"Party gains 1 Ghost Regression from their Resonance and 8 RB."<<endl;
			} else {
				cout<<"Party gains 8 RB."<<endl;
			}
			break;
			
			case 5:
				cout<<"Party gains 5 RB."<<endl;
			break;
			
			case 6:
				cout<<"Party moved on from the mirror with no ill effects."<<endl;
			break;
			
			default:
			cout<<"ERROR"<<endl;
			break;
		}
		
		cout<<"Press [Enter] to return to main menu."<<endl;
		getch();
}



void MusicHaunt(){								//TT Musical Haunt
	system("cls");
	cout<<"TT MUSICAL HAUNT"<<endl;
	
	Itotal = Intensity(2);
	
	randomGR(2);
	
	cout<<"Party gains "<<Itotal<<" RB/BP/EP and becomes Stupified."<<endl;
		
	cout<<"Press [Enter] to return to main menu."<<endl;
	getch();
}



void TTPotty(){									//TT Training Potty
		perPlayer = true;
	while(perPlayer)
	{
		system("cls");
		cout<<"TT TRAINING POTTIES"<<endl;
		
		tRoll = TrapRoll();
		
		switch(tRoll){
			case 1:
				cout<<"Player gains 20 RB, GR: Quick Filler & Diaper Trained, as well as 1 MUL/WUL."<<endl;
			break;
			
			case 2:
				cout<<"Player gains 15 RB, GR: Quick Filler & Diaper Trained, as well 1 MUL/WUL."<<endl;
			break;
			
			case 3:
				cout<<"Player gains 10 RB, GR: Quick Filler & Diaper Trained, as well as 1 ";
				
				if(Die100() > 50)
				{ cout<<"M";
				} else { cout<<"W"; }
				
				cout<<"UL."<<endl;
			break;
			
			case 4:
				cout<<"Player gains 10 RB and GR: ";
				
				if(Die100() > 50)
				{ cout<<"Quick Filler";
				} else { cout<<"Diaper Trained"; }
				
				cout<<", before the following UC roll."<<endl;
				
				UCauto = 3;
				UCprompt();
			break;
			
			case 5:
				cout<<"Player gains 10 RB and GR: Diaper Trained, before the following UC roll."<<endl;
			break;
			
			case 6:
				cout<<"No effect, the magic does not trigger and the door opens."<<endl;
			break;
			
			default:
			cout<<"ERROR"<<endl;
			break;
		}
		
		perPlayer = YesNo();
	}
}