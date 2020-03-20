/* Programmer: Jordan Shinespark
	Purpose: to create a streamlined CC-numbers-generator to speed up play.
	Date: 3/17/20
	
	Version 3.0
		-Release
		
	Version 3.01
		-increased Idle Roll HP gain by 1 for proper effect
		-Added explanations to Crystals
		-Added forgotten effect on Crystal of Laziness
		-Reworded main menu for ease of use
		-Fixed randomGR bug that prevented its use
		-Fixed oversight that caused UCprompt to freeze on rollUntil calcs
	
	Version 3.02
		-Fixed oversight causing UCprompt to freeze on multi-roll calcs
		
	Version 3.1
		-Added Booties effects
		-Provided support for Infinite Diaper
	
	To-Do:
		Fix bugs
		
	Future:
		Add attack rolls to per-Turn calculator
		Add Caretaker action generator
		Integrate BombPoof into Encounters
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
bool makeSure();
bool Forfeit();
int IRTcalc(int penalty, int tier);
int pointCalc(int pTier);
void UseCheck(int UCpen, int UCtier);
void UCprompt();
void HeadMenu();
void Caretakers();
void Traps();
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
void jewelry(int jewel);
int TrapRoll();
int CareGenerator(bool Caring);
int TrapGenerator();
int DiaperGenerator(bool Traps);
int TrapArtist();
int Misfire(bool Caring);
int wandFire();
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
void PrimSiren();
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
void Lapras();
void Milotic();
void Sylveon();
void cLazy();
void cSissy();
void cLittle();
void cDiapers();
void cSquish();
void cImmature();

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
void DivePool();
void SirenSong();
void foyGun();
void MCP();
void TimeDistort();

//Global variables
bool looper = true; //makes the entire program persist until closed
bool check = true; //used by all text prompts to repeat if misinputted
bool perPlayer = true; //repeats Encounter for multiple player generations
bool mother = false; //if mother, then ignore some prompts that are auto-filled
bool rollUntil = false; //used to make a roll repeat indefinitely until hitting threshold
bool status = false;
bool aura = false; //halves UC values when true
bool forfeit = false;
bool tdForfeit = true; //if true, ask if want to forfeit, else don't ask
bool certainty = false; //if true, player verifies to continue. If false, repeat inputs
int rollCount = 0;
int intput;
int intput2;
int intput3;
char charput;
int Itotal;
int Upoints;
int UCTauto = 0; //if -1, adds 1 to UC penalty on that roll
int IRauto = 0;
int FIRauto = 0;
int HCauto = 0;
int foodAuto = 0;
int drinkAuto = 0;
int HPgain = 0;
int Pwet = 0;
int Pmess = 0;
int tRoll = 0;

//Let's make it happen!
main()
{
	HeadMenu();

return 0;
}



//Prompt to repeat
int YesNo(){
	check = true;
   while(check == true){
	   
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


//ensures player can clean misinputs
bool makeSure(){
	
	check = true;
	while(check == true){
		cout<<endl<<"Please review your inputs in this section. Would you like to redo (y/n)? ";
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
		return 1;
   } else {
		return 0;
   }
}



//ask for forfeit
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
		break;
		
		case 0:
			HIGH = 6;
		break;
		
		case 1:
			HIGH = 7;
			bonus = 2;
		break;
		
		case 2:
			HIGH = 11;
			bonus = 2;
		break;
		
		case 3:
			HIGH = 14;
			bonus = 3;
		break;
		
		case 4:
			HIGH = 16;
			bonus = 4;
		break;
		
		default:
			HIGH = 20 + (tier - 4) * 2;
			bonus = 4;
		break;
	}
	
	//generate roll
	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return (die + bonus + penalty);
}



//calculate Point Idle values
int pointCalc(int pTier){
	int die = 1;
	int bonus = 4;
	const int LOW = 1;
	int HIGH = 1;
	time_t seconds;
	
	switch(pTier){
		case 0:
			return 0;
		break;
		
		case 1:
			HIGH = 6;
		break;
		
		case 2:
			HIGH = 8;
		break;
		
		case 3:
			HIGH = 10;
			bonus = 5;
		break;
		
		case 4:
			HIGH = 12;
			bonus = 5;
		break;
		
		default:
			HIGH = 15 + (pTier - 4) * 3;
			bonus = 5;
		break;
	}
	
	//generate roll
	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return (die + bonus);
}



//Processing Use Check
void UseCheck(int UCpen, int UCtier){
	int die [2] = {1, 1};
	int bonus = 3;
	const int LOW = 1;
	int HIGH = 1;
	time_t seconds;
	
	if(UCTauto > 0){
		UCtier += UCTauto;
	}
	
	for(int i = 0; i < 2; i++)
	{	
		switch(UCtier){
		case -1:
		case 0:
			HIGH = 3;
		break;
		case 1:
			HIGH = 5;
		break;
		case 2:
			HIGH = 7;
		break;
		case 3:
			HIGH = 8;
			bonus = 4;
		break;
		case 4:
			HIGH = 10;
			bonus = 4;
		break;
		default:
			 HIGH = 12 + (UCtier - 4) * 2;
			 bonus = 4;
		break;
		}
		
	if(UCTauto == -1){
		bonus++;
	}
	
	//generate roll
	time(&seconds);
	srand((unsigned int) seconds);
	die[i]=(rand()%((HIGH-LOW)+LOW))+1;
		
		if(i==0){sleep(1.2);} //sleep if first calculation to reseed
	}

	Pwet += die[0] + UCpen + bonus;

	Pmess += die[1] + UCpen + bonus;

	if(UCtier == -1){
		Pwet *= 0.5;
		Pmess *= 0.5;
	}
}



//Prompts for UC input from player
void UCprompt()
{
	int temp = 0;
	
	
if((rollCount != 0)||(rollUntil)){
	cout<<endl<<"Encounter has Use Check(s). Please enter..."<<endl;
}

	do{
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

		if((rollUntil != true)&&(rollCount == 0)){
			check = true;
			while(check == true)
			{
			cout<<"Number of Use Checks at once: ";

			  cin>>temp;

			  if((cin.fail())||(temp < 1)){
				cin.clear();
				 cin.ignore();
				 cout<<"Please enter an integer at or above 1."<<endl<<endl;
			  } else {
				check = false;
			  }
			}
		}

	certainty = makeSure();

	}while(!certainty);
	
	if(temp){
		rollCount = temp;
	}

if((rollUntil)||(rollCount > 1))
{
	cout<<endl;
	
	while(rollUntil)
	{
		if(rollCount){
			rollCount = 0;
		}
		
		UseCheck(intput, intput2);	
		cout<<"Total so far: "<<Pwet<<" WHP, "<<Pmess<<" MHP."<<endl;
		
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
	cout<<endl<<"Use Check for values of "<<Pwet<<" WHP and "<<Pmess<<" MHP.";
	
	if(aura){
		cout<<" This roll was halved.";
	}
	
	cout<<endl<<endl<<endl;
}

	UCTauto = 0;
	Pwet = 0;
	Pmess = 0;
	intput = 0;
	intput2 = 0;
	rollCount = 0;
	rollUntil = false;
}



//Base menus
void HeadMenu(){ 											//Main menu
	looper = true;

   while(looper == true) {
	   tdForfeit = true;
   	system("cls");

		cout<<"Welcome to the v3.01 CC defeat printout! How may I assist you today?"<<endl;
		cout<<"Whenever you are prompted with 2 or more inputs, you will be asked if you want to redo inputs for them."<<endl;
		cout<<endl;
		
   	cout<<"Options:"<<endl;
   	cout<<"0- End program"<<endl;
	cout<<"1- Random Encounter generator"<<endl;
	cout<<"2- Trap Roll roller"<<endl;
	cout<<"3- Misfire roller, including general, Wand, and Caretaker"<<endl;
	cout<<"4- Bomb effect calculator"<<endl;
   	cout<<"5- Caretaker Party Wipes"<<endl;
   	cout<<"6- Room calculator"<<endl;
	cout<<"7- Per-turn effect calculator"<<endl;
	cout<<"8- Per-Encounter effect caculator"<<endl;
    cout<<"9- Idle Roll calculator"<<endl;
	cout<<"10- Forced IR calculator"<<endl;
	cout<<"11- Use Check calculator"<<endl;
	cout<<"12- Ghost Regression generator"<<endl;
	cout<<"13- Diaper print randomizer"<<endl;
	cout<<"14- Food calculations"<<endl;
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
		 //ends program
		break;	
		 
		case 1:
			cout<<endl<<"Players encounter Caretaker #"<<CareGenerator(true)<<endl;
			cout<<"Players encounter Room #"<<TrapGenerator()<<endl;
			cout<<"Press [Enter] to return to main menu.";
			getch();
			system("cls");
		break;
		
		case 2:
			system("cls");
			cout<<"Trap Roll generator"<<endl;
			TrapRoll();
			cout<<"Press [Enter] to return to main menu.";
			getch();
			system("cls");
		break;
		 
		case 3:
			cout<<endl<<"Player-cast misfire: #"<<Misfire(false)<<endl;
			cout<<"Wand misfire : #"<<wandFire()<<endl;
			cout<<"Caretaker-cast misfire of: #"<<Misfire(true)<<endl;
			cout<<"Press [Enter] to return to main menu.";
			getch();
			system("cls");
		break;
		
		case 4:
			system("cls");
			BombPoof();
		break;
		 
		case 5:
			Caretakers();
        break;
		 
		case 6:
			Traps();
        break;
		
		case 7:
			perTurn();
		break;
		
		case 8:
			Encounter();
		break;
		 
        case 9:
			IdleRolls();
        break;
		 
		case 10:
			ForcedIR();
		break;
		 
		case 11:
		 	perPlayer = true;
			while(perPlayer == true)
			{
				system("cls");
				UCprompt();
				perPlayer = YesNo();
			}
		break;
		 
		 case 12:
			perPlayer = true;
			while(perPlayer == true)
			{
				system("cls");
				randomGR(0);
				perPlayer = YesNo();
			}
		break;
		
		case 13:
		cout<<endl<<"Generated a no-Traps diaper of #"<<DiaperGenerator(false)<<endl;
		cout<<"Generated a Trap-pool diaper of #"<<DiaperGenerator(true)<<endl;
		cout<<"Press [Enter] to return to main menu and clear the screen.";
		getch();
		system("cls");
		break;
		
		case 14:
		system("cls");
		foodDrink();
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
		 PrimSiren();

         case 11:
         Leavanny();
         break;

         case 12:
         Togekiss();
         break;

         case 13:
         Ninetales();
         break;

         case 14:
         Chansey();
         break;

         case 15:
         Salazzle();
         break;

         case 16:
         Luxray();
         break;

         case 17:
         Nidoqueen();
         break;

         case 18:
         Vaporeon();
         break;

         case 19:
         Audino();
         break;

         case 20:
         Lucario();
         break;

         case 21:
         Ampharos();
         break;

         case 22:
         Ivysaur();
         break;

         case 23:
         Slowpoke();
         break;

         case 24:
         Snorlax();
         break;

         case 25:
         Mew();
         break;

         case 26:
         Galvantula();
         break;

         case 27:
         Ursaring();
         break;

         case 28:
         AlakazamPac();
         break;

         case 29:
      	AlakazamSpo();
         break;

         case 30:
         Victini();
         break;

         case 31:
         Dragonite();
         break;

         case 32:
         Delphox();
         break;

         case 33:
         Smeargle();
         break;

         case 34:
         Shaymin();
         break;
		 
		 case 35:
		 Lapras();
		 break;
		 
		 case 36:
		 Milotic();
		 break;
		 
		 case 37:
		 Sylveon();
		 break;
		 
		 case 38:
		 cLazy();
		 break;
		 
		 case 39:
		 cSissy();
		 break;
		 
		 case 40:
		 cLittle();
		 break;
		 
		 case 41:
		 cDiapers();
		 break;
		 
		 case 42:
		 cSquish();
		 break;
		 
		 case 43:
		 cImmature();
		 break;

         default:
         cout<<"Please input a proper number from 1-43."<<endl;
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
		
		case 39:
		DivePool();
		break;
		
		case 40:
		SirenSong();
		break;
		
		case 41:
		foyGun();
		break;
		
		case 42:
		MCP();
		break;
		
		case 43:
		TimeDistort();
		break;
		
		default:
        cout<<"Please input a proper number from 1-43."<<endl;
        getch();
        system("cls");
		break;
	}
}



//Roller for per-Encounter checks
void Encounter(){
	int UDD = 0;
	bool babble = false;
	bool change = false;
	bool stumble = false;
	bool sleepy = false;
	bool squisher = false;
	int mBottle;
	string bottleType;
	int bottle;
	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"Welcome to the per-Encounter roller! (Warning, this will take some time)"<<endl;
	
	//early squisher check
	if(Die20() > 10){
		squisher = true;
	} else {
		squisher = false;
	}
	
	//early Magic Bottle generator
	mBottle = Die7();
	switch(mBottle){
		case 1:
			bottleType = "Vanilla";
		break;
		
		case 2:
			bottleType = "Powder";
		break;
			
		case 3:
			bottleType = "Fruity";
		break;
		
		case 4:
			bottleType = "Fill";
		break;
		
		case 5:
			bottleType = "Silly";
		break;
		
		case 6:
			bottleType = "Sleepy";
		break;
		
		case 7:
			bottleType = "Water";
		break;
		
		default:
			bottleType = "ERROR";
	}
	
	//certainty check
	cout<<"Wrong input? Type 'y' to continue, anything else goes back. ";
	cin>>charput;
	if((charput != 'y')&&(charput != 'Y')){
		return;
	}
	
	cout<<endl<<endl<<"Now generating calculations";
	
	//Babbler check
	if(Die100() > 50)
	{
		babble = true;
	} else {
		babble = false;
	}
	cout<<".";
	
	
	//Changeless check
	sleep(1.2);
	if(Die100() > 50)
	{
		change = true;
	} else {
		change = false;
	}
	cout<<".";
	sleep(1.3);
	
	
	//UDD roll
	sleep(1.2);
	UDD = Die100();
	cout<<".";
	sleep(1.3);
	
	
	//Clumsy check
	if(Die100() <= 30)
	{
		stumble = true;
	} else {
		stumble = false;
	}
	cout<<".";
	sleep(1.4);
	
	
	//Sleepy check
	if(Die20() > 10)
	{
		sleepy = true;
	} else {
		sleepy = false;
	}
	cout<<".";
	sleep(1.5);
	
	
	//Bottle drink amount
	bottle = Die4();
	bottle+= 2;
	
	cout<<"done"<<endl<<endl;
	
	cout<<"Player drinks "<<bottle<<" WHP from an Auto-Bottle, if applicable."<<endl;
	cout<<"Magic Bottle rolled a "<<bottleType<<" Bomb."<<endl;
	cout<<"Mantra makes party gain 10 RB (activates once per player with Mantra)."<<endl;
	cout<<"Wriggler inflicts 3 RB. Lisp inflicts 1 RB if they speak."<<endl;
	cout<<"Vocab Regression inflicts 3 RB if they speak, or Yipper inflicts 3 RB."<<endl;
	cout<<"Rewarding Diapers inflicts 10 RB if player used their diaper."<<endl<<endl;
	
	if(UDD > 75){ //UD Desire
		cout<<"If player has UD Desire or stronger, they deny a diaper change."<<endl;
	
	} else if(UDD > 50){ //UD Love
		cout<<"If player has UD Love, Adoration, or Addict, they deny a diaper change."<<endl;
	
	} else if(UDD > 10){ //UD Adoration
		cout<<"If player has UD Adoration or Addict, they deny a diaper change."<<endl;
	
	} else { //UD Addict
		cout<<"If player has UD Addict, they deny a diaper change."<<endl;
	}
	
	if(babble)
	{
		cout<<"Babbler: Player is compulsed to babble. 3 RB gained."<<endl;
	}
	if(change)
	{
		cout<<"If an ally has Changeless, this player has forgotten how to change for an Idle Roll."<<endl;
	}
	if(stumble)
	{
		cout<<"Clumsy/Booties: Player stumbles and falls onto their butt. Inflicts 2 RB, or 4 RB if their diaper is messy or Crinkly."<<endl;
	}
	if(sleepy)
	{
		cout<<"Sleepy Diaper: Player gains Sleepy lv. 1."<<endl;
	}
	if(squisher)
	{
		cout<<"Squisher: If undefeated and have Use Levels, player admires their diaper for 10 RB/EP."<<endl;
	}
	if((!sleepy)&&(!stumble)&&(!change)&&(!babble)&&(!squisher))
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
	int mTier = 0; //Mental point idle tier
	int mp = 0;
	int bTier = 0; //Body point idle tier
	int bp = 0;
	int eTier = 0; //Equipment point idle tier
	int ep = 0;
	int rolls = 0;
	int total = 0;
	int bottle = 0;
	int die = 1;
	int leon = 0;
	int leon2 = 0;
	int UDD = 0;
	char leon3 = 'q';
	bool pacifier = false;
	bool magic = false;
	bool squisher = false;
	bool stumble = false;
	bool babble = false;
	bool change = false;
	bool assistant = false;
	bool tiara = false;
	bool necklace = false;
	bool repeat = true;
	const int LOW = 1;
	int HIGH = 10;
	time_t seconds;
	
	if(rollCount > 0)
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

//early pacifier check
    HIGH = 20;	
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		pacifier = true;
	} else {
		pacifier = false;
	}

	do{ //repeat wet/mess/IR/IRT until correct
	//ask wetness
	   check = true;
	   while(check == true)
	   {
		cout<<"Wet level: ";

		  cin>>wet;

		  if((cin.fail())||(wet < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer of at least 0."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }
	   
//early magic pacifier check
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		
		if(die > 10) {
			magic = true;
		} else {
			magic = false;
		}

	//ask messiness
	   check = true;
	   while(check == true)
	   {
		cout<<"Mess level: ";

		  cin>>mess;

		  if((cin.fail())||(mess < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer of at least 0."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }

//early Squisher calc
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		
		if(die > 10) {
			squisher = true;
		} else {
			squisher = false;
		}


	//ask IR penalties
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
	   
//early babble check
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		
		if(die > 10) {
			babble = true;
		} else {
			babble = false;
		}

	//ask IR Tiers
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

	certainty = makeSure();
	}while(!certainty);

	//Assistant check
	HIGH = 100;
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die <= 25){
		assistant = true;
	} else {
		assistant = false;
	}
	
	do{ //repeat rollCount/UCp/UCT until correct
	//ask roll count
	if(mother == false)
	{
	   check = true;
	   while(check == true)
	   {
		cout<<"Number of Idle Rolls being made: ";

		  cin>>rolls;

		  if((cin.fail())||(rolls < 1)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter a positive integer of at least one."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }
	} else {
		rolls = rollCount;
	}

	//ask UC penalties
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
	   
//early HP calc
		time(&seconds);
		srand((unsigned int) seconds);
		HP=((rand()%((HIGH-LOW)+LOW))+1)/50 + 2;
	   
	//ask UC Tiers
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
	  
	certainty = makeSure();
	}while(!certainty);

//early Teehee Tiara check
	HIGH = 20;
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		tiara = true;
	} else {
		tiara = false;
	}

	do{ //repeat Point Idles until correct
	//ask Mental Levels
		check = true;
	   while(check == true)
	   {
		cout<<"Mental Levels (0 if none): ";

		  cin>>mTier;

		  if((cin.fail())||(mTier < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer at or above 0."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }

	//early Pacifier Necklace check
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die > 10) {
		necklace = true;
	} else {
		necklace = false;
	}
	   
	//ask Body Levels
		check = true;
	   while(check == true)
	   {
		cout<<"Body Levels (0 if none): ";

		  cin>>bTier;

		  if((cin.fail())||(bTier < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer at or above 0."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }
	
	//early Auto-Bottle calc
	HIGH = 4;
	time(&seconds);
   	srand((unsigned int) seconds);
   	bottle=(rand()%((HIGH-LOW)+LOW))+1;
	
	bottle += 2;
	
	//ask Equipment Levels
		check = true;
	   while(check == true)
	   {
		cout<<"Equipment Levels (0 if none): ";

		  cin>>eTier;

		  if((cin.fail())||(eTier < 0)){
			cin.clear();
			 cin.ignore();
			 cout<<"Please enter an integer at or above 0."<<endl<<endl;
		  } else {
			check = false;
		  }
	   }
	   
//early Stumble check
	HIGH = 100;
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die <= 30) {
		stumble = true;
	} else {
		stumble = false;
	}
	
	certainty = makeSure();
	}while(!certainty);

if((mother == false)||(status == true))
{
system("cls");
cout<<"Calculating..."<<endl;
} else {
cout<<"Loading...";
}

   
//Process diaper use
	if(wet <= 8){ //if not Infinite Diaper
		switch(wet){
		case 0:
		  break;

		  case 1:
		  case 2:
		  penalty++;
		  break;

		  case 3:
		  penalty ++;
		  tier++;
		  break;

		  case 4:
		  penalty++;
		  tier += 2;
		  break;

		  case 5:
		  penalty += 3;
		  tier += 2;
		  break;

		  case 6:
		  penalty += 3;
		  tier += 3;
		  break;

		  case 7:
		  penalty += 5;
		  tier += 3;
		  break;
		  
		  case 8:
		  penalty += 5;
		  tier += 4;
		  break;

		  default:
		  wet = 0;
		  cout<<"ERROR. Defaulting to 0 use."<<endl;
		  break;
	   }
	   
	} else { //if Infinite Diaper
		penalty += 5 + (wet - 8);
		tier += 4 + (wet - 8);
	}

	if(mess <= 8){ //if not Infinite Diaper
		switch(mess){
		case 0:
		  break;

		  case 1:
		  tier++;
		  break;

		  case 2:
		  penalty++;
		  tier++;
		  break;

		  case 3:
		  penalty++;
		  tier += 2;
		  break;

		  case 4:
		  penalty += 3;
		  tier += 2;
		  break;

		  case 5:
		  penalty += 3;
		  tier += 3;
		  break;

		  case 6:
		  penalty += 4;
		  tier += 3;
		  break;

		  case 7:
		  penalty += 4;
		  tier += 4;
		  break;
		  
		  case 8:
		  penalty += 4;
		  tier += 5;

		  default:
		  mess = 0;
		  cout<<"ERROR. Defaulting to 0 use."<<endl;
		  break;
	   }
	   
	} else { //if Infinite Diaper
		penalty += 4 + (mess - 8);
		tier += 5 + (mess - 8);
	}

	
//calculate Idle Roll
	tier += IRauto;
for(int i = 0; i < rolls; i++){
	total += IRTcalc(penalty, tier);
    sleep(1.4);
}
  
if((mother == false)||(status == true))
{cout<<"Idle Roll done"<<endl;}
   
   
//calculate Use Checks
for(int i = 0; i < rolls; i++){
	UseCheck(UCpen, UCtier);
	sleep(1.2);
}

if((mother == false)||(status == true))
{cout<<"Use Check done"<<endl;}


//calculate Point Idles
for(int i = 0; i < rolls; i++){
	if(mTier > 0){ mp += pointCalc(mTier);}
	if(bTier > 0){ bp += pointCalc(bTier);}
	if(eTier > 0){ ep += pointCalc(eTier);}
}


//Status calculations
if((mother == false)||(status == true)){

	cout<<"Status checks";
	
	sleep(1.3);
	cout<<".";
	
	//Changeless check
    time(&seconds);
   	srand((unsigned int) seconds);
   	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die < 51) {
		change = true;
	} else {
		change = false;
	}
	
	sleep(1.1);
	cout<<".";
	
	//UDD roll
    time(&seconds);
   	srand((unsigned int) seconds);
   	UDD=(rand()%((HIGH-LOW)+LOW))+1;
	
	sleep(1.1);
	cout<<".";
	
	
	//Little Leon generation
	HIGH = 6;
	time(&seconds);
   	srand((unsigned int) seconds);
   	leon=(rand()%((HIGH-LOW)+LOW))+1;
	
	//Little Leon secondary generation
	if(leon == 4){	
		cout<<" last one!";
		sleep(1.1);
		
		HIGH = 3;
		time(&seconds);
		srand((unsigned int) seconds);
		leon2=(rand()%((HIGH-LOW)+LOW))+1;
		
		switch(leon2){
			case 1: leon3 = 'M'; break;
			case 2: leon3 = 'B'; break;
			default: leon3 = 'E'; break;
		}
	}
	
	system("cls");
} else {
	cout<<" done"<<endl<<endl;
}
   
//Print results
	cout<<rolls<<" Idle Roll(s) for a total of "<<total<<" point(s)."<<endl;
	cout<<"Use Check(s) rolled a total of "<<Pwet<<" WHP and "<<Pmess<<" MHP."<<endl;
	cout<<"Player regains "<<HP<<" HP, or "<<(HP + 2)<<" if they used a pacifier this Idle Roll."<<endl;
	cout<<"Player drinks "<<bottle<<" WHP from bottle (if applicable)."<<endl;
	cout<<"Toy Blocks diaper makes player gain 10 RB (if applicable)."<<endl;
	
	//print Point Idles, if applicable
	if(mp||bp||ep){
		cout<<"Point Idles for ";
		
		if(mp){
			cout<<mp<<" MP";
		
			if(bp&&ep){ cout<<", "; //if followed by both
			} else if(bp||ep){ cout<<" and "; //if followed by one
			} else{ cout<<"."<<endl;} //if alone				
		}
		
		if(bp){
			cout<<bp<<" BP";
			
		if(ep){ cout<<", and "; //if all three print
		} else { cout<<"."<<endl;} //if alone
		}
		
		if(ep){
			cout<<ep<<" EP."<<endl;
		}
	} else {
		cout<<"No Point Idles."<<endl;
	}
	cout<<endl;


//print statuses	
if((mother == false)||(status == true))
{
	cout<<endl<<"Statuses (if applicable, or any):"<<endl<<endl;	
	
	//Per-ENC
	if(UDD > 75){ //UD Desire
		cout<<"If player has UD Desire or stronger, they deny a diaper change."<<endl;
	
	} else if(UDD > 50){ //UD Love
		cout<<"If player has to UD Love, Adoration, or Addict, they deny a diaper change."<<endl;
	
	} else if(UDD > 10){ //UD Adoration
		cout<<"If player has UD Adoration or Addict, they deny a diaper change."<<endl;
	
	} else { //UD Addict
		cout<<"If player has UD Addict, they deny a diaper change."<<endl;
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
		cout<<"If player has Clumsy or Booties: Player stumbles. +2 RB or +4 RB if messy or Crinkly Diaper."<<endl;
	}
	
	if(babble) {
		cout<<"If player has Babbler: Player is compulsed to babble. +3 RB."<<endl;
	}
	
	//per Idle
	if(change){
		cout<<"If an ally has Changeless: this player forgets how to change diapers for an Idle Roll."<<endl;
	}
	
	if(tiara){
		cout<<"If player wears Teehee Tiara: Player gains Giggly for 1 IR."<<endl;
	}
	
	if(necklace){
		cout<<"If player wears Pacifier Necklace: Player must use pacifier during next Idle Roll period."<<endl;
	}
	
	if(assistant){
		cout<<"If player has Assistant: Player gains Advocate for 1 IR, if they hadn't last Idle Roll."<<endl;
	}
	
	//if no effect occurs
	if(!(magic)&&!(pacifier)&&!(stumble)&&!(babble)&&!(change)&&!(assistant)&&!(tiara)&&!(necklace)) {
		cout<<"Player suffers no Idle Roll specific effects. How lucky!"<<endl;
	}
	
	cout<<"if player has Little Leon: Player ";
	switch(leon){
		case 1:
			cout<<"is hugged, and has a 3-IR timer status increased by 1 IR."<<endl;
		break;
		
		case 2:
			cout<<"sees his hypno eyes, and rolls an HC check."<<endl;
		break;
		
		case 3:
			cout<<"hears sound advice, and gains 10 additional RB."<<endl;
		break;
		
		case 4:
			cout<<"hears his tail rattle, and gains 5 RB/"<<leon3<<"P."<<endl;
		break;
		
		case 5:
			cout<<"feels his comforting presence, and gains a Pacifier Level."<<endl;
		break;
		
		default:
			cout<<"has their diaper checked, and rolls 1 Use Check."<<endl;
			UCprompt();
		break;
	}
}

cout<<"Press [Enter] to continue."<<endl<<endl;
penalty = 0;
Pwet = 0;
Pmess = 0;
tier = 0;
UCtier = 0;
total = 0;
mp = 0;
bp = 0;
ep = 0;
getch();

if(mother)
{
	repeat = false;
} else {
	repeat = YesNo();
}

}
	IRauto = 0;
	rollCount = 0;
	mother = false;
	status = false;
}



//Forced Idle Roll machine
void ForcedIR(){
	int wet = 0;
	int mess = 0;
	int formWet = 0;
	int formMess = 0;
	int tier = 0;
	int rolls = 1;
	int useCount = 1;
	int total = 0;
	bool repeat = true;
	bool type = false; //if type is true, then diaper use FIR. If false, then other FIR.

while(repeat)
{
system("cls");

	if(rollCount){
		mother = true;
		rolls = rollCount;
	}

if(mother == false)
{
	cout<<"Welcome to the Forced IR calculator!"<<endl;
	cout<<"Remember! When FIRs stack, the extra rolls are turned into Tiers (the calculator will do this for you)."<<endl<<endl;
	
	//receive input 
	check = true;
	while(check == true)
	{	
		cout<<"Is this a diaper use FIR (y/n)? ";
		cin>>charput;
		
		if(cin.fail()||((charput != 'n')&&(charput != 'N')&&(charput != 'y')&&(charput != 'Y'))){
			cin.clear();
			cin.ignore();
			cout<<"Please enter a proper input."<<endl;
		} else {
			check = false;
		}

	   if((charput == 'n')||(charput == 'N')) {
			type = false;
	   } else if((charput == 'y')||(charput == 'Y')) {
			type = true;
	   } else {
		   cout<<"ERROR ON TYPE"<<endl;
	   }
	}
   
} else {
	cout<<"Encounter has Forced Idle Roll(s). Please input..."<<endl<<endl;
	type = false;
}
	do{ //repeat all questions until certain
		if(type)
		{
		   check = true;
		   while(check == true)
		   {
			   if(mother){
					cout<<"Old wet level: ";
			   } else {
				   cout<<"Old wet level (enter -1 to quit to main menu): ";
			   }

			  cin>>formWet;

			  if((cin.fail())||((formWet < 0)&&(mother))||(formWet < -1)){
				cin.clear();
				 cin.ignore();
				 cout<<"Please enter an integer of at least 0."<<endl<<endl;
			  } else if(formWet == -1){
				  return;
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

			  if((cin.fail())||(wet < 0)){ //if cin fails or if a bad value
				cin.clear();
				 cin.ignore();
				 cout<<"Please enter an integer of at least 0."<<endl<<endl;
			  } else if(wet < formWet){
				  cout<<"Please enter an integer that is at least equal to old wet level."<<endl<<endl;
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

			  if((cin.fail())||(formMess < 0)){
				cin.clear();
				 cin.ignore();
				 cout<<"Please enter an integer of at least 0."<<endl<<endl;
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

			  if((cin.fail())||(mess < 0)){ //if cin fails or if a bad value
				cin.clear();
				 cin.ignore();
				 cout<<"Please enter an integer of at least 0."<<endl<<endl;
			  } else if(mess < formMess){
				  cout<<"Please enter an integer that is at least equal to old wet level."<<endl<<endl;
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
	   
	   if((!mother)&&(!type)){
		   check = true;
		   while(check == true)
		   {
			cout<<"Number of FIRs being made: ";

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
	   
	   //if diaper use FIR, calculate number of FIRs rolled
	   if(type){
		useCount = (wet - formWet) + (mess - formMess);
			
		if((wet > 8)&&(formWet < 8)){ //if wet expands into Infinite Diaper range, cutoff FIRs
			useCount -= wet - 8;
		}
		
		if((mess > 8)&&(formMess < 8)){ //if mess expands into Infinite Diaper range, cutoff FIRs
			useCount -= mess - 8;
		}
		
		if((formWet == 0)&&(wet != 0)){ //if gaining first WUL, remove the nonexistent FIR
			useCount -= 1;
		}
		if((formWet >= 8)&&(formMess >= 8)){ //if into Infinite Diaper's capacity, no FIRs are rolled
			useCount = 0;
		}
	   }
	   
	   //catch dumb inputs, like "no increase in ULs", "only the first WUL was gained", and "Infinite Diaper increase when past maximums"
	   if((type)&&(useCount == 0)){
		   certainty = false;
		   cout<<"Cannot do diaper use FIR, no levels were gained with FIRs attached. Repeating prompt."<<endl<<endl;
	   } else {
			certainty = makeSure();
	   }
	}while(!certainty);
   
if(mother != true)
{
	system("cls");
} else {
	cout<<endl;
}
   
//Process diaper use level
	if(wet <= 8){ //if not Infinite Diaper
		switch(wet){
		  case 0:
		  case 1:
		  case 2:
		  break;

		  case 3:
		  tier++;
		  break;

		  case 4:
		  case 5:
		  tier += 2;
		  break;

		  case 6:
		  case 7:
		  tier += 3;
		  break;
		  
		  case 8:
		  tier += 4;
		  break;

		  default:
		  cout<<"ERROR on wet"<<endl;
		  break;
	   }
	} else { //if Infinite Diaper
		tier += 4 + (wet - 8);
	}

	if(mess <= 8){ //if not Infinite Diaper
		switch(mess){
		  case 0:
		  break;
		
		  case 1:
		  case 2:
		  tier++;
		  break;

		  case 3:
		  case 4:
		  tier += 2;
		  break;

		  case 5:
		  case 6:
		  tier += 3;
		  break;

		  case 7:
		  tier += 4;
		  break;
		  
		  case 8:
		  tier += 5;
		  break;
		  

		  default:
		  cout<<"ERROR on mess"<<endl;
		  break;
	   }
	} else { //if Infinite Diaper
		tier += 5 + (mess - 8);
	}
   
	
//calculate FIR
	tier += FIRauto + (rolls - 1) + (useCount - 1);
   total += IRTcalc(0,tier);
   
//Print results
	if(type){
		cout<<"The "<<useCount<<" FIR(s) result in a total of "<<total<<" RB."<<endl;
	} else {
		cout<<"The "<<rolls<<" FIR(s) result in a total of "<<total<<" RB."<<endl;
	}
if(mother == false)
{
	if(type){
		cout<<(wet - formWet)<<" WUL gained. ";
		cout<<(mess - formMess)<<" MUL gained.";
	}
	
} else {
	cout<<"Press [Enter] to return to Encounter."<<endl;
	getch();
}

	if(rollCount)
	{
		rollCount = 0;
		FIRauto = 0;
		repeat = false;
	} else {
		repeat = YesNo();
	}
	
	total = 0;
	tier = 0;
	rolls = 0;
	formWet = 0;
	formMess = 0;
	
} //end of repeat
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
	string name ="Error";
	string effect = "X";
	int points = 0;
	perPlayer = true;
	
while(perPlayer){
	
	do{ //repeat questions until correct
			check = true;
		while(check == true)
		{
			system("cls");
			cout<<"Welcome to the bomb calculator. Please enter bomb style. (Calculations may take some time for RNG)"<<endl;
			cout<<"1- Vanilla"<<endl<<"2- Powder"<<endl<<"3- Fruity"<<endl<<"4- Fill"<<endl<<"5- Silly"<<endl<<"6- Sleepy"<<endl<<"7- Water"<<endl;
			cout<<"Input: ";
			
			cin>>style;

			if((cin.fail())||(style < 1)||(style > 7)){
				cin.clear();
				cin.ignore();
				style = 0;
				cout<<"Please enter an integer between 1 and 7"<<endl<<endl;
				getch();
				system("cls");
			} else {
				check = false;
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
		
	certainty = makeSure();
	}while(!certainty);
	   
	if(hit == 0){ hit = Die20(); sleep(1.2); }
	   
	cout<<"-----"<<endl;
	
	switch(style)
	{
		case 1:
		name = "Vanilla";
		effect = "M";
		break;
		
		case 2:
		name = "Powder";
		effect = "E";
		break;
		
		case 3:
		name = "Fruity";
		effect = "B";
		break;
		
		case 4:
		name = "Fill";
		effect = "F";
		break;
		
		case 5:
		name = "Silly";
		effect = "S";
		break;
		
		case 6:
		name = "Sleepy";
		effect = "l";
		break;
		
		case 7:
		name = "Water";
		effect = "WH";
		
		default:
		name = "Error";
		effect = "X";
		break;
	}
	
	//print out effects
	cout<<name<<" goes off for ";
	
		//Vanilla, Powder, and Fruity
	if(style<4){
	
			//use points variable to calculate 50/50 for Powder Bomb's Enhancement
		if((effect == "E")&&(hit<=15)){
			
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
			
			if(effect == "E")
			{
				cout<<"Press [Enter] to roll for the Use Check."<<endl<<endl;
				getch();
				rollCount = 1;
				UCprompt();
			}
		}
		
	
		//Fill Bomb
	} else if(style == 4)
	{
		if(hit <= 2)
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

		if(hit <= 3)
		{
			cout<<"Silly lv. 2 and "<<damage<<" damage dealt."<<endl;
		} else if (hit <= 6){
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
		
		if(hit <= 3)
		{
			cout<<"Sleepy lv. 3 and "<<damage<<" damage dealt."<<endl;
		} else if(hit <=6){
			cout<<"Sleepy lv. 2 and "<<damage<<" damage dealt."<<endl;
		} else if(hit<=10){
			cout<<"Sleepy lv. 1 and "<<damage<<" damage dealt."<<endl;
		} else {
			cout<<"no effect."<<endl;
		}
		
		//Water Bomb
	} else if(style == 7){
		damage = Die20();
		
		if(damage <= 10){
			damage = 1;
		} else {
			damage = 2;
		}
		
		if(hit <= 4){
			points = Die10();
			cout<<"Bogged, ";
		} else {
			points = Die5();
		}
		
		if(hit<=10){
			cout<<points<<" WHP gained and "<<damage<<" damage dealt."<<endl;
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
	4- body exclusive
	5- equipment exclusive
	*/
	
	int die = 1;
	const int LOW = 1;
	int input = 0;
	int HIGH = 10;
	time_t seconds;
	
if(lock == 0){
	cout<<"Welcome to the random Ghost Regression generator!"<<endl<<endl;
}

	do{ //ask all questions and repeat until certain
		if(lock == 0){
				check = true;
			while(check == true)
			{
				cout<<"0- return to main menu"<<endl;
				cout<<"1- any random"<<endl;
				cout<<"2- mental exclusive"<<endl;
				cout<<"3- body or equipment exclusive"<<endl;
				cout<<"4- body exclusive"<<endl;
				cout<<"5- equipment exclusive "<<endl;
				cout<<"Input: ";
			
			cin>>input;

			if((cin.fail())||(input < 0)||(input > 5)){
				cin.clear();
				cin.ignore();
				cout<<"Please enter a proper input between 0 and 5."<<endl;
			} else {
				check = false;
				
				//if return to main menu
				if(input == 0){
					return;
				}
			}
		   }
		}
	
	if(!lock){
		certainty = makeSure();
	} else {
		certainty = true;
	}
	
	}while(!certainty);

	if(lock == 0){lock = input;}
   
   
   switch(lock) {
	   case 0:
	   cout<<"ERROR. Lock trapped at 0 value for unknown reason."<<endl;
	   HIGH = 2;
	   break;
	   
	   case 1: //any random
	   //Low end unchanged
	   HIGH = 48;
	   break;
	   
	   case 2: //mental only
	   //Low end unchanged
	   HIGH = 13;
	   break;
	   
	   case 3: //body or equipment only
		//Add 13 to value to simulate rolling 14-41, see below
	   HIGH = 28;
	   break;
	   
	   case 4: //body only
		//Add 13 to value to simulate rolling 14-26, see below
	   HIGH = 13;
	   break;
	   
	   case 5: //equipment only
		//Add 26 to value to simulate rolling 27-41, see below
	   HIGH = 15;
	   break;
	   
	   case 6: //universal only
		cout<<"We are not doing universal randomGRs right now."<<endl;
		cout<<"Actually, how did you get here??"<<endl;
		HIGH = 48;
	   break;
	   
	   default:
	   HIGH = 2;
	   cout<<"ERROR. Unknown Lock value."<<endl;
   }

//roll for Ghost Regressions according to specifications   
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	//bump up for those not starting at 1 as lowest
	switch(lock){
		case 1:
		case 2:
			//catch empty changes
		break;
		
		case 3:
		case 4:
			//start at Body Traits
			die += 13;
		break;
		
		case 5:
			//start at Equipment Traits
			die += 26;
		break;
		
		case 6:
			//nothing here yet!
		break;
		
		default:
			cout<<"ERROR ON DIE BUMPING"<<endl;
	}
	
	cout<<"Player receives Ghost Regression #"<<die<<": ";
	
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
		
		case 12:
		cout<<"Self-Distractor";
		break;
		
		case 13:
		cout<<"a stack of Used Diaper Desire";
		break;
		
		//Body
		case 14:
		cout<<"Baby Fat, Obese, or Blobish (stacks)";
		break;
		
		case 15:
		cout<<"Thumb Suckler";
		break;
		
		case 16:
		cout<<"Quick Filler";
		break;
		
		case 17:
		cout<<"Strong Filler";
		break;
		
		case 18:
		cout<<"Clumsy";
		break;
		
		case 19:
		cout<<"Bad Grip";
		break;
		
		case 20:
		cout<<"Pinkified OR Powdered (choice)";
		break;
		
		case 21:
		cout<<"Girly";
		break;
		
		case 22:
		cout<<"Suckler";
		break;
		
		case 23:
		cout<<"Butterpaws";
		break;
		
		case 24:
		cout<<"Muscle Unmemory";
		break;
		
		case 25:
		cout<<"Cede to Authority";
		break;
		
		case 26:
		cout<<"Super Soaker OR Mess Master (player's choice, stacks into Super User)";
		break;
		
		//Equipment
		case 27:
		cout<<"Foamified OR Rattle'd (stacks)";
		break;
		
		case 28:
		cout<<"Crinkly Diaper";
		break;
		
		case 29:
		cout<<"Poofy Diaper OR Extra Poof (stacks)";
		break;
		
		case 30:
		cout<<"Baby Clothes";
		break;
		
		case 31:
		cout<<"Frilly Clothes";
		break;
		
		case 32:
		cout<<"Baby Bib";
		break;
		
		case 33:
		cout<<"Diaper Suit/Onesie (choice)";
		break;
		
		case 34:
		cout<<"Pleasure Pamps";
		break;
		
		case 35:
		cout<<"Kiddie Crown";
		break;
		
		case 36:
		cout<<"Teehee Tiara";
		break;
		
		case 37:
		cout<<"Snuggler";
		break;
		
		case 38:
		cout<<"Friendship Bracelet";
		break;
		
		case 39:
		cout<<"Pacifier Necklace";
		break;
		
		case 40:
		cout<<"Plastic Pants";
		break;
		
		case 41:
		cout<<"Resonant Jewels";
		break;
		
		//Universal
		case 42:
		cout<<"Devolution (GR version)";
		break;
		
		case 43:
		cout<<"Assistant";
		break;
		
		case 44:
		cout<<"Little Leon";
		break;
		
		case 45:
		cout<<"Big Pal";
		break;
		
		case 46:
		cout<<"Unlucky";
		break;
		
		case 47:
		cout<<"Potty Rebel";
		break;
		
		case 48:
		cout<<"Permapamps";
		break;
		
		default:
		cout<<"ERROR. GENERATION FAILED";
	}
	
	cout<<"."<<endl;
}



//roll for a jewelry status
void jewelry(int jewel){
	int die = 1;
	const int LOW = 1;
	const int HIGH = 9;
	time_t seconds;
	
	if(jewel == 0){
		//calculate the random jewelry status
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
	} else {
		die = jewel;
	}
	
	
	//print that status
	switch(die){
		case 1:
			cout<<"Pink Gem Necklace";
		break;
		
		case 2:
			cout<<"Brown Gem Bracer";
		break;
		
		case 3:
			cout<<"Green Gem Diaper";
		break;
		
		case 4:
			cout<<"GR: Kiddie Crown";
		break;
		
		case 5:
			cout<<"GR: Teehee Tiara";
		break;
		
		case 6:
			cout<<"GR: Fancy Accessories";
		break;
		
		case 7:
			cout<<"GR: Friendship Bracelet";
		break;
		
		case 8:
			cout<<"GR: Pacifier Necklace";
		break;
		
		case 9:
			cout<<"GR: Resonant Jewels";
		break;
		
		default:
		cout<<"ERROR ON JEWELRY"<<endl;
	}
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
	
	int playerGen = 0;
	int placeholder = 0;
	int seesaw = 0;
	int mod = 0;
	bool disadvan = false;
	bool weapons = false;
	bool advocate = false;
	int die = 1;
	const int LOW = 1;
	const int HIGH = 20;
	time_t seconds;
	
	do{ //repeat until inputs correct
	
		//find Trap Roll (if pre-generated)
			check = true;
		while(check == true)
		{
		cout<<endl<<"If generated separately, enter the Trap Roll (for random, enter 0): ";
		
		cin>>playerGen;

		if((cin.fail())||(playerGen < 0)||(playerGen > 20)){
			cin.clear();
			cin.ignore();
			playerGen = -1;
			cout<<"Please enter a proper input between 1 and 20. "<<endl;
		} else {
			check = false;
		}
	   }

		//ask if disadvantage
		if(playerGen == 0){
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
		}
	   
	   
	   //ask if wearing Weapons diaper
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
	   
	   //ask if player has Advocate
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
	   
	   //ask for Seesaw modifier
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
	   
	   //ask for Trap roll modifier
	 if(playerGen == 0){
	   check = true;
		while(check == true)
		{
		cout<<"Trap Roll modifier (0 if none, else enter as printed): ";
		
		cin>>mod;

		if(cin.fail()){
			cin.clear();
			cin.ignore();
			charput = 'q';
			cout<<"Please enter an integer."<<endl;
		} else {
			check = false;
		}
	   }
   
   //generate Trap Roll
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1+mod;
		
		if(disadvan){
			sleep(1.7);
			time(&seconds);
			srand((unsigned int) seconds);
			placeholder=(rand()%((HIGH-LOW)+LOW))+1+mod;
			
			if(placeholder < die){
				die = placeholder;
			}
		}
 } else {
	 die = playerGen;
 }
 
	certainty = makeSure();
	}while(!certainty);
 
	cout<<"-";
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
	int HIGH = 43;
    int die = 1;
	
	//if only fighting Caretakers
	if(Caring){HIGH = 42;}
	
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	//if non-hostiles removed
	if((Caring == false)&&(die >= 34)){die++;}
	
	return die;
}



int TrapGenerator(){
	time_t seconds;
	const int LOW = 1;
	int HIGH = 43;
    int die = 1;
	
	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return die;
}



int DiaperGenerator(bool Traps){
	const int LOW = 1;
	int HIGH = 29;
	int die = 1;
	time_t seconds;
	
	if(Traps)
	{
		HIGH = 42;
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
	int HIGH = 26;
	time_t seconds;
	
	if(Caring)
	{
		HIGH = 31;
	}
	
	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return die;
}



//wand Misfires
int wandFire(){
	int die = 1;
	const int LOW = 1;
	int HIGH = 13;
	time_t seconds;
	
	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	return die;
}



void perTurn(){
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
	
//room-based effects
	int room = 0;
	
	//die for Potion Room effects
	const int LOW = 1;
	const int HIGH = 9;
	time_t seconds;
	int potion = 0;
	int bomb = 0;
	int i;

	
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"Welcome to the per-turn results generator! (Warning: this may take a bit)"<<endl<<endl;
	
	//early potion room generation
	time(&seconds);
	srand((unsigned int) seconds);
	potion=(rand()%((HIGH-LOW)+LOW))+1;
	
	//early bad grip
	if(Die100() <= 25)
	{
		grip = true;
	}
	
//ask for room #
	check = true;
	while(check == true)
	{
	cout<<"Please enter Caretaker's Trap Artist room number (1 if empty, 0 if you wish to return to main menu): ";
	
	cin>>room;

	if((cin.fail())||(room < 0)){
		cin.clear();
		cin.ignore();
		cout<<"Please enter a positive integer between 0-12."<<endl;
	} else {
		check = false;
		
		if(room == 0){
			return;
		}
	}
   }
	   
	cout<<endl<<endl<<"Now generating calculations";
	
	
	//stacking protected paws and bad grip
	if(Die100() <= 50)
	{
		supergrip = true;
	}
	cout<<".";
	sleep(1.2);
	
	//lazy
	if(Die100() <= 25)
	{
		lazy = true;
	}
	cout<<".";
	sleep(1.2);
	
	//stumble
	if(Die100() <= 30)
	{
		stumble = true;
	}
	cout<<".";
	sleep(1.2);
	

	//slowpoke diaper
	if(Die100() <= 50)
	{
		slow = true;
	}
	cout<<".";
	sleep(1.2);
	
	//vibrating diaper turn loss
	if(Die100() <= 25)
	{
		vibrate = true;
	}
	cout<<".";
	sleep(1.2);
	
	//baby diaper
	if(Die20() > 10)
	{
		baby = true;
	}
	cout<<".";
	sleep(1.2);
	
	
	//aroma
	if(Die20() > 10)
	{
		aroma = true;
	}
	cout<<".";
	sleep(1.2);
	

	//aroma and paci-pop's "if pacifier" roll
	if(Die20() > 10)
	{
		extraPC = true;
	}
	
	
//print out results
	system("cls");
	cout<<"Results, from player sources:"<<endl<<endl;
	
	if(supergrip){
		cout<<"Protected Paws AND";
	}
	if(grip){
		cout<<"If either Protected Paws OR";
	}
	if((supergrip)||(grip)){
		cout<<" Bad Grip: player drops weapon. Player gains 5 RB if Paw Protection."<<endl;
	}
	if(stumble){
		cout<<"Clumsy, player trips onto their butt after attacking, gaining 2 RB if clean or 4 RB if messy/Crinkly."<<endl;
	}
	if(lazy){
		cout<<"Lazy: player misses turn."<<endl;
	}
	if(vibrate){
		cout<<"Vibrating Diaper and Enjoyer TRAIT (not GR): player loses turn."<<endl;
	}
	if(slow){
		cout<<"Slowpoke Diaper: player loses next turn to Slow."<<endl;
	}
	if(baby){
		cout<<"Baby Diaper: player gains a Pacifier Level."<<endl;
	}
	
cout<<endl<<"From mother sources:"<<endl<<endl;
	if(extraPC){
		cout<<"If player uses a pacifier against Aroma or Paci-Pop Caretakers, they gain a Pacifier Level."<<endl;
	}
	if(aroma){
		cout<<"If Caretaker has Aroma, player gained a Pacifier Level."<<endl;
	}
	
//Trap Artist room effects
cout<<endl;
	
	switch(room){
		//Trap Rooms with no per-turn effects
		case 1:
		case 7:
		case 8:
		case 9:
		case 12:
			cout<<"Trap Artist Room #"<<room<<" has no per-turn effects to calculate."<<endl<<endl;
		break;
		
		//Dusty Room
		case 2:
			cout<<"The Dusty Room forces a Use Check at half value."<<endl;
			cout<<"If diaper is used, player loses their turn (cannot activate consecutively)."<<endl;
			
			rollCount = 1;
			aura = true;
			UCprompt();
		break;
		
		//Dining Room
		case 3:
			cout<<"In the Dining Room if the player is restrained in a chair, they roll a UC with +1 penalty (this penalty is automatically added to this calculation)."<<endl;
			cout<<"If this is a 3rd turn of being restrained in a row, player gains 1 stack of Enhancement."<<endl;
			
			//ask for room #
			check = true;
			while(check == true)
			{
			cout<<"Is the player making this UC roll (y/n)?: ";
			
			cin>>charput;

			if((cin.fail())||((charput != 'y')&&(charput != 'Y')&&(charput != 'n')&&(charput != 'N'))){
				cin.clear();
				cin.ignore();
				cout<<"Please enter a proper input."<<endl;
			} else {
				check = false;
			}
		   }
		   
			if((charput == 'y')||(charput == 'Y')){
				rollCount = 1;
				UCTauto = -1;
				UCprompt();
			}
		break;
		
		//Potions Room
		case 4:
			cout<<"(May take a moment) In the Potions Room, if the player rolls a 1-5 on their AR, they knock a potion over that"<<endl;
			
			switch(potion){
				case 1:
					cout<<"has party gain a stack of Enhancement."<<endl;
				break;
				
				case 2:
					cout<<"has player recover "<<Die4()<<" HP."<<endl;
				break;
				
				case 3:
					cout<<"inflicts a Vanilla Bomb for ";
					
					for(i = 0; i < 3; i++){
						bomb += Die4();
						
						if(i != 2){
							sleep(1.2);
						}
					}
					
					cout<<bomb<<" MP, "<<(bomb/2)<<" RB, and "<<Die6()<<" damage."<<endl;
				break;
				
				case 4:
					cout<<"inflicts a Powder Bomb for ";
					
					for(i = 0; i < 3; i++){
						bomb += Die4();
						
						if(i != 2){
							sleep(1.2);
						}
					}
					
					cout<<bomb<<" EP, "<<(bomb/2)<<" RB, and "<<Die6()<<" damage.";
					
					if(Die100() > 50){
						cout<<" Player gains a stack of Enhancement.";
					}
					
					cout<<endl;
				break;
				
				case 5:
					cout<<"inflicts a Fruity Bomb for ";
					
					for(i = 0; i < 3; i++){
						bomb += Die4();
						
						if(i != 2){
							sleep(1.2);
						}
					}
					
					cout<<bomb<<" BP, "<<(bomb/2)<<" RB, and "<<Die6()<<" damage."<<endl;
				break;
				
				case 6:
					cout<<"inflicts a Fill Bomb for ";
					
					for(i = 0; i < 2; i++){
						bomb += Die6();
						
						if(i != 1){
							sleep(1.2);
						}
					}
					
					cout<<bomb<<" UHP, 1 stack of Holding Help, and "<<Die6()<<" damage."<<endl;
				break;
				
				case 7:
					cout<<"inflicts a Silly Bomb for Silly lv. 1 and "<<Die4()<<" damage."<<endl;
				break;
				
				case 8:
					cout<<"inflicts Pacified."<<endl;
				break;
				
				case 9:
					cout<<"inflicts a stack of Helplessness as a glass shatters."<<endl;
				break;
				
				case 10:
					cout<<"has player's diaper alter into a Potion diaper."<<endl;
				break;
				
				default:
				cout<<"ERROR on potion room calculation"<<endl;
				break;
			}
			
			cout<<endl;
		break;
		
		//Sparkling Room
		case 5:
			cout<<"The Sparkling Room makes the player roll an HC check with a +1 bonus gained if failing."<<endl;
			HCauto = 1;
			HypnoCheck(false);
			cout<<endl;
		break;
		
		//Tingly Room
		case 6:
			cout<<"In the Tingly Room, rolling 1-5 AR causes the player to drop their weapon."<<endl;
		break;
		
		//Galaxy Room
		case 10:
			cout<<"In the Galaxy Room, the player must roll an HC with +3 bonus (must add manually),"<<endl;
			cout<<"which inflicts stacks of Hypnotized with no effect. On 3 stacks, player gains Empty-Headed rather than Brainwashed."<<endl;
			
			HCauto = 1;
			HypnoCheck(false);
			cout<<endl;
		break;
		
		//Bouncy Room
		case 11:
			cout<<"In the Bouncy Room, if a player is trapped in a bouncy chair, they must roll DC14 with Adeptness or Skill to escape, else lose their turn."<<endl;
			
			if(Die100() <= 25){
				cout<<"Player gains a stack of UDD if their diaper is used."<<endl;
			} else {
				cout<<"Player avoided the stack of UDD even if their diaper was used."<<endl;
			}
			cout<<endl;
		break;
		
		default:
			cout<<"ERROR WITH TRAP ARTIST ROOMS."<<endl;
      break;
	}
	
	//ask for Hypnosis Check
		check = true;
   while(check == true)
   {
   	cout<<"Do you want to roll a Hypnosis check? Sources: Aroma, Lazy Aura, etc. (y/n): ";
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
   
   
   //ask for Use Aura roll
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
		rollCount = 1;
		aura = true;
		UCprompt();
   }
   
   //reset variables
   bomb = 0;
	
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
		cout<<"The number of HCs rolled in a row for one player: ";
		
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
		modifier = 0;
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
		cout<<"Hypnosis Check succeeded, no effect.";
		
		if(die >= 6)
		{
			cout<<" HC bonus increased by 2, unless special roll (then 1).";
		}
		cout<<endl;
	}
	
	cout<<"Press [Enter] to continue."<<endl;
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
	int wetDiu;
	int messLax;
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
					for(i = 0; i < drink; i++)
					{
						restore += Die3() + 3;
						sleep(1);
					}
					cout<<".";
					
					//food healing
					for(i = 0; i < (food * 2); i++)
					{
						restore += Die4();
						sleep(1);
					}
					cout<<".";
					
					//drink WHP
					for(i = 0; i < drink; i++)
					{
						WHP += Die5() + 1;
						sleep(1);
					}
					cout<<".";
					
					//food MHP
					for(i = 0; i < food; i++)
					{
						MHP += Die6() + 2;
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
					rollCount = 2;
					UCprompt();
				break;
				
				//Found after Encounter, basic food/drink generation
				case 3:
					do{ //repeat until user is certain
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
						
					certainty = makeSure();
					}while(!certainty);
				
					system("cls");
					cout<<"Generating";
					
					//drink healing
					for(i = 0; i < drink; i++)
					{
						restore += Die3() + 3;
						sleep(1);
					}
					cout<<".";
					
					//food healing
					for(i = 0; i < (food * 2); i++)
					{
						restore += Die4();
						sleep(1);
					}
					cout<<".";
					
					//drink WHP
					for(i = 0; i < drink; i++)
					{
						WHP += Die5() + 1;
						sleep(1);
					}
					cout<<".";
					
					//food MHP
					for(i = 0; i < food; i++)
					{
						MHP += Die6() + 2;
						sleep(1);
					}
					cout<<".";
					
					//auto-bottle generation
					if((drink)&&(Die100() <= 25)){
						bottle = true;
						sleep(1);
					}
					if(bottle){
						bWHP = Die7() + 11;
					}
					
					//check if diuretic/laxative
					if(drink){
						wetDiu = Die20();
						if(food){
							sleep(1.1);
						}
					}
					if(food){
						messLax = Die20();
					}
					
					
					system("cls");
					cout<<"Player recovered "<<restore<<" HP."<<endl;
					cout<<"Player gains "<<WHP<<" WHP and "<<MHP<<" MHP."<<endl;
					if(bottle){
						cout<<"Player is inflicted Auto-Bottle with "<<bWHP<<" WHP inside."<<endl;
					}
					
					//laxative/diuretic checks
					if((messLax > 10)&&(wetDiu > 10)){
						cout<<"If player wears Food diaper, player gains both Diuretic and Laxative."<<endl;
					}
					
					if((food)&&(messLax > 10)){
						cout<<"If player wears Food diaper, player gains Laxative."<<endl;
					}
					if((drink)&&(wetDiu > 10)){
						cout<<"If player wears Food diaper, player gains Diuretic."<<endl;
					}
				break;
				
				//Kitchen-unique attack
				case 4:
					damage = Die4();
				
				
						check = true;
					while(check){
					cout<<"Did the Caretaker throw food or drink? 1 for drink, 2 for food."<<endl;
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
					
					//drink WHP
					if(intput == 1){
						WHP += Die5() + 1;
						
					//food MHP
					} else {
						WHP += Die6() + 2;
					}
					
					
					if(Die100() <= 30)
					{
						laxdiu = true;
					} else {
						laxdiu = false;
					}
					
					
					//output
					cout<<"Player takes "<<damage<<" damage";
					
					//if drink was thrown
					if(intput == 1)
					{
						if(laxdiu){
							cout<<", gains"<<WHP<<" WHP, and suffers Diuretic."<<endl;
						} else {
							cout<<" and gains "<<WHP<<" WHP."<<endl;
						}
					//if food was thrown
					} else{
						if(laxdiu){
							cout<<", gains"<<WHP<<" MHP, and suffers Laxative."<<endl;
						} else {
							cout<<" and gains "<<WHP<<" MHP."<<endl;
						}
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
				WHP += Die5() + 1;
				sleep(1);
			}
			
			//food MHP
			for(int i = 0; i < foodAuto; i++)
			{
				MHP += Die6() + 2;
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
	int wetDiu;
	int messLax;
	int bWHP = 0;
	
	
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
	for(i = 0; i < drink; i++)
	{
		restore += Die3() + 3;
		sleep(1);
	}
	cout<<".";
	
	//food healing
	for(i = 0; i < (food * 2); i++)
	{
		restore += Die4();
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
		MHP += Die6() + 2;
		sleep(1);
	}
	cout<<".";
	
	//drink Diuretic
	wetDiu = Die100();
	messLax = Die20();
	sleep(1.1);
	cout<<".";
	
	//auto-bottle generation
	if(Die100() <= 25){
		bWHP = Die7() + 11;
	}
	
	cout<<endl<<endl<<"Player recovered "<<restore<<" HP."<<endl;
	cout<<"Player gains "<<WHP<<" WHP and "<<MHP<<" MHP."<<endl;
	
	if(bWHP){cout<<"Player is inflicted Auto-Bottle with "<<bWHP<<" WHP inside."<<endl;}
	
	//Laxative/Diuretic printout
	if((wetDiu > 50)&&(messLax > 10)){
		cout<<"If player wears Food diaper, player gains Diuretic and Laxative."<<endl;
	}
	if(wetDiu > 50){
		cout<<"If player wears Food diaper, player gains Diuretic."<<endl;
	}
	if(messLax > 10){
		cout<<"If player wears Food diaper, player gains Laxative."<<endl;
	}
	
	cout<<endl;
}
	


//Caretaker Encounters////////////////////////////////////////////////////////////////////
void Kangaskhan(){                                    //Kangaskhan

   perPlayer = true;
	while(perPlayer == true) {
		system("cls");
		cout<<"KANGASKHAN"<<endl;
		
		do{
		
			if(tdForfeit){forfeit = Forfeit();}

			Itotal = Intensity(2);
			
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;

	if(forfeit){
		cout<<"Intensity roll of "<<(Itotal/2)<<" RB/BP."<<endl;
		cout<<"Pouched/Finished Intensity roll of "<<(Itotal/2 + 5)<<" RB/BP."<<endl<<endl;
	} else {
		cout<<"Intensity roll of "<<Itotal<<" RB/BP."<<endl;
		cout<<"Pouched/Finished Intensity roll of "<<(Itotal + 10)<<" RB/BP."<<endl<<endl;
	}
	
	cout<<"Kangaskhan changes players into Flower diapers."<<endl;

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
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
   
			Itotal = Intensity(2);
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;

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
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
	
			Itotal = Intensity(2);

			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;

		if(forfeit){
			Itotal *= 0.5; 
			sleep(1.2);
			
			if(Die100() > 50){
				cout<<"Player gains GR: Used Diaper Desire."<<endl;
			} else {
				cout<<"Player resisted the infliction of GR: Used Diaper Desire."<<endl;
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
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
	
			Itotal = Intensity(1);
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;

		if(forfeit){Itotal *= 0.5;}
		
		cout<<"Intensity roll of "<<Itotal<<" RB/EP."<<endl;
		
		cout<<"Player gains 1 UL in both categories."<<endl;
		cout<<"This Caretaker will only change Max Capacity diapers."<<endl;

      perPlayer = YesNo();
   }
}



void Gardevoir(){                                    //Gardevoir
	
	perPlayer = true;
   while(perPlayer == true) {
	system("cls");
   	cout<<"GARDEVOIR"<<endl;
	
		do{
			if(tdForfeit){forfeit = Forfeit();}
	
			Itotal = Intensity(2);
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		
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
		cout<<"Press [Enter] to start the Idle Roll."<<endl;
		getch();
		
		rollCount = 1;
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
	
	do{
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(1);
	
		certainty = makeSure();
		if(!certainty){ tdForfeit = true;}
	}while(!certainty);
	cout<<endl<<endl;
	
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
	HIGH = 100;
   	time(&seconds);
	srand((unsigned int) seconds);
	die=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(die <= 25)
	{
		HIGH = 7;
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		die += 11;
		cout<<"Player also gains Auto-Bottle with "<<die<<" WHP contained."<<endl;
	}
	  
	cout<<"Intensity roll of "<<Itotal<<" RB/BP."<<endl;
	  
    //Roll UC until diaper use
	rollUntil = true;
	UCprompt();
	
	cout<<"Flygon changes players into Food diapers."<<endl;

      perPlayer = YesNo();
   }
}



void Boss(){                                    //Bosses
	int die = Die100();
	int die2;
	
	do{ //loop until certain of boss and if forfeit
		
		//ask for boss
		check = true;
	   while(check == true)
	   {
			cout<<"Which Boss are you encountering?"<<endl;
			cout<<"1- Latias"<<endl<<"2- Mewtwo"<<endl<<"3- Lugia"<<endl<<"4- Alpha Luxray"<<endl<<"5- Flora"<<endl;
			cout<<"6- Gemcutter"<<endl<<"7- Lead Flygon"<<endl;
			cout<<endl<<"Input: ";
			
		cin>>intput;

		if((cin.fail())||(intput > 7)||(intput < 1)){
			cin.clear();
			cin.ignore();
			intput = -1;
			cout<<"Please enter a number between 1 and 7."<<endl<<endl;
		} else {
			check = false;
		}
	   }
   
		//ask for forfeit
		if(tdForfeit){
			forfeit = Forfeit();
			cout<<endl;
		}
   
		certainty = makeSure();
		if(!certainty){ tdForfeit = true;}
	}while(!certainty);


if(intput == 1)												//Latias
{
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
		cout<<"LATIAS/LATIOS (this will take a moment to generate)"<<endl;

		int total = 0;
		
		for(int i = 0; i < 3; i++){
			total += Die4();
			sleep(1.2);
		}
		
		total *= 3;
			
		if(forfeit){
			if(die > 50){
				randomGR(1);
			} else {
				cout<<"Player avoided the random Ghost Regression."<<endl;
			}
			
		} else {
			randomGR(1);
		}
		
		cout<<total<<" MP/BP/EP and "<<(total / 2)<<" RB."<<endl;
		cout<<"All bosses can change players into Boss-themed Diapers."<<endl;

    perPlayer = YesNo();
	die = Die100();
   }


} else if(intput == 2){                                		//Mewtwo
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
		cout<<"MEWTWO"<<endl;
		
		die2 = Die100();

		do{
			Itotal = Intensity(3);
			
			certainty = makeSure();
		}while(!certainty);
			cout<<endl;

		if(forfeit){
			Itotal *= 0.5;
			
			if(die > 50){
				sleep(1.1);
				randomGR(2);
			} else {
				cout<<"Player avoided the random Mental GR."<<endl;
			}
			
			sleep(1.2);
			
			if(die2 > 50){
				cout<<"Player suffers GR: Changeless."<<endl;
			} else {
				cout<<"Player avoided GR: Changeless."<<endl;
			}
		} else {
			sleep(1.1);
			randomGR(2);
			cout<<"Player suffers GR: Changeless."<<endl;
		}
		
		cout<<"Intensity roll of "<<Itotal<<" RB/MP."<<endl;
		cout<<"All bosses can change players into Boss-themed Diapers."<<endl;

    perPlayer = YesNo();
	die = Die100();
   }


} else if(intput == 3){                                     //Lugia
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
		cout<<"LUGIA"<<endl;
		
		do{
			Itotal = Intensity(2);
		
			certainty = makeSure();
		}while(!certainty);
			cout<<endl;
		
		if(forfeit){
			Itotal *= 0.5;
			
			if(die > 50){
				sleep(1.1);
				randomGR(3);
			} else {
				cout<<"Player avoided the random Body or Equipment Ghost Regression."<<endl;
			}
		} else {
			sleep(1.1);
			randomGR(3);
		}
		
		cout<<"Intensity roll of "<<Itotal<<" RB/BP/EP."<<endl;
		  
		//Roll 2 UC at 5 higher Tiers
		UCTauto = 5;
		rollCount = 2;
		UCprompt();
		  
		cout<<"If either point category does not procc diaper use, add enough UHP to use diaper in that category."<<endl;
		cout<<"All bosses can change players into Boss-themed Diapers."<<endl;

    perPlayer = YesNo();
	die = Die100();
   }
   
   
} else if(intput == 4){										//Alpha
	 perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
		cout<<"LUXRAY PRIDE ALPHA"<<endl;
		
		die2 = Die100();
		
		do{
			Itotal = Intensity(2);
		
			certainty = makeSure();
		}while(!certainty);
			cout<<endl;
		
		if(forfeit){
			Itotal *= 0.5;
			
			if(die>50){
				sleep(1.1);
				randomGR(3);
			} else {
				cout<<"Player avoided the random GR."<<endl;
			}
			
			if(die2>50){
				cout<<"Player gains GR: Pacifist."<<endl;
			} else {
				cout<<"Player avoids GR: Pacifist."<<endl;
			}
			
			sleep(1.1);
			
			if(Die100()>50){
				cout<<"Player gains GR: Diaper Suit/Onesie. If stacking, Hypno or Bondage Suit (player preference)"<<endl;
			} else {
				cout<<"Player avoids GR: Diaper Suit/Onesie."<<endl;
			}
			
		} else {
			sleep(1.1);
			randomGR(3);
			cout<<"Player gains GR: Pacifist."<<endl;
			cout<<"Player gains GR: Diaper Suit/Onesie. If stacking, Hypno or Bondage Suit (player preference)"<<endl;
		}
		
		cout<<"Player gains "<<Itotal<<" RB/MP/EP."<<endl;
		cout<<"All bosses can change players into Boss-themed Diapers."<<endl;
		
	perPlayer = YesNo();
	
	die = Die100();
	if(perPlayer){ sleep(1);}
   }


} else if(intput == 5){										//Flora
	int rando [2] = {0, 0};
	int sog;
	 perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"FLORA (best Caretaker don't @ me -Jordan)"<<endl;
		cout<<"This may take a moment."<<endl;
		
		die2 = Die100();
		
		do{
			Itotal = Intensity(1);
			
			certainty = makeSure();
		}while(!certainty);
			cout<<endl;
		
		if(forfeit){
			Itotal *= 0.5;
		} else {
			die = 100;
			die2 = 100;
		}
		
		sleep(1.1);
		sog = Die6() + 7;
		
		//if forfeit and both, or defeated
		if((die>50)&&(die2>50)){
			sleep(1.1);
			rando[0] = Die5();
			sleep(1.1);
			
			//ensure GRs don't stack
			do{
				rando[1] = Die5();
				if(rando[0] == rando[1]){sleep(1.1);}
			}while(rando[0] == rando[1]);
		
		//if forfeit and get one
		} else if((die>50)||(die2>50)){
			sleep(1.1);
			rando[0] = Die5();
			rando[1] = 0;
			
		//if forfeit and neither
		} else {
			rando[0] = 0;
		}
		
		//GR printouts
		if(rando[0] != 0){
			cout<<"Player gains GR: ";
			
			switch(rando[0]){
				case 1:
					cout<<"Vocab Regression";
				break;
				case 2:
					cout<<"Little'd";
				break;
				case 3:
					cout<<"Diaper Suit (of a joey)";
				break;
				case 4:
					cout<<"Suckler";
				break;
				default:
					cout<<"Cede to Authority";
			}
			
			if(rando[1] != 0){
				cout<<" and GR: ";
			}
			
			switch(rando[1]){
				case 0:
					cout<<" but avoids the other GR effect";
				break;
				case 1:
					cout<<"Vocab Regression";
				break;
				case 2:
					cout<<"Little'd";
				break;
				case 3:
					cout<<"Diaper Suit (of a joey)";
				break;
				case 4:
					cout<<"Suckler";
				break;
				default:
					cout<<"Cede to Authority";
			}
			cout<<"."<<endl;
			
		} else {
			cout<<"Player avoids the GR effects."<<endl;
		}
		
		cout<<"Player gains an Auto-Bottle with "<<sog<<" WHP."<<endl;
		cout<<"Player gains "<<Itotal<<" RB/MP/BP."<<endl;
		cout<<"All bosses can change players into Boss-themed Diapers."<<endl;
		
		perPlayer = YesNo();
		die = Die100();
		if(perPlayer){sleep(1);}
	}


}else if(intput == 6){										//Gemcutter
	
	 perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"GEMCUTTER"<<endl;
		
		do{
			Itotal = Intensity(2);
			
			certainty = makeSure();
		}while(!certainty);
			cout<<endl;
		
		if(forfeit){ //if forfeiting
			Itotal *= 0.5;
			sleep(1.1);
			
			if(Die100() > 50){ //random jewelry effect
				cout<<"Player avoided the random jewelry status."<<endl;
			} else {
				cout<<"Player gains jewelry status of ";
				jewelry(0);
				cout<<"."<<endl;
			}
			
			if(Die20() > 10){ //random Equipment GR
				cout<<"Player avoided the random Equipment GR."<<endl;
			} else {
				randomGR(5);
			}
			
		} else { //if not forfeiting
			cout<<"Player gains jewelry status of ";
				jewelry(0);
				cout<<"."<<endl;
				randomGR(5);
		}
		
		cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
		cout<<"All bosses can change players into Boss-themed Diapers."<<endl;
		cout<<"The Gemcutter can also change players into Green Gem Diapers."<<endl;
		
		perPlayer = YesNo();
	}


} else if(intput == 7){										//Lead Flygon
	int magicBottle = 1;

	 perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"LEAD FLYGON"<<endl;
		
		do{
			Itotal = Intensity(2);
			certainty = makeSure();
		}while(!certainty);
		
		if(forfeit){ Itotal *= 0.5; }
		
		magicBottle = (Die20()/10) + 2 + 1;
		
		cout<<"Player gains a Magic Bottle with "<<magicBottle<<" effects inside."<<endl;
		cout<<"Player gains "<<Itotal<<" RB/BP."<<endl;
		cout<<"All bosses can change players into Boss-themed Diapers."<<endl;
		cout<<"Lead Flygon can also change players into Food Diapers."<<endl;
		
		perPlayer = YesNo();
	}
} // end of potential bosses

}



void Miltank(){                                     //Miltank
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"MILTANK"<<endl;

	do{
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(1);
	
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		
	if(forfeit){Itotal *= 0.5;}
		
	cout<<"Intensity roll of "<<Itotal<<" RB/BP/EP."<<endl;
	
	//roll 2 UC at 1 higher Tier
	UCTauto = 1;
	rollCount = 2;
	UCprompt();
	
	cout<<"Miltank changes players into Farm diapers."<<endl;
	
	perPlayer = YesNo();
   }
}



void Primarina(){                                  //Primarina (Mischief)
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
		cout<<"PRIMARINA, Mischief (warning, generation takes a moment)"<<endl<<endl;
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
		
			Itotal = Intensity(0);
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	
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



void PrimSiren(){									//Primarina (Siren)
	perPlayer = true;
   while(perPlayer == true) {
		system("cls");
		cout<<"PRIMARINA (SIREN)"<<endl<<endl;
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
			
			Itotal = Intensity(2);
			
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		
		if(forfeit){
			Itotal *= 0.5;
			
			if(Die100()>50){
				cout<<"Player gains Enlightened."<<endl;
			} else {
				cout<<"Player avoided Enlightened."<<endl;
			}
		} else {
			cout<<"Player gains Enlightened."<<endl;
		}
		
		cout<<"If player is not wearing a Swim diaper, they gain Bogged."<<endl;
		cout<<"Player gains "<<Itotal<<" RB/MP/EP."<<endl;
		
		perPlayer = YesNo();
   }
}



void Leavanny(){                                   //Leavanny
	int die;
	
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"LAEVANNY"<<endl;
	   
	do{
		if(tdForfeit){forfeit = Forfeit();}
		   
		Itotal = Intensity(2);
	
		certainty = makeSure();
		if(!certainty){ tdForfeit = true;}
	}while(!certainty);
	cout<<endl<<endl;
	   
	if(forfeit){
		Itotal *= 0.5;
			sleep(1.1);
			if(Die100()>50){
				cout<<"Player gains GR: Frilly Clothes."<<endl;
			} else {
				cout<<"Player avoided GR: Frilly Clothes."<<endl;
			}
		} else {
			cout<<"Player gains GR: Frilly Clothes."<<endl;
		}
	
	cout<<"Intensity roll of "<<Itotal<<" for RB/MP."<<endl;
	
	perPlayer = YesNo();
   }
}



void Togekiss(){                                   //Togekiss
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"TOGEKISS"<<endl;
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(1);
		   
		   	certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
	   if(forfeit){Itotal *= 0.5;}
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP. Any player with Silly is cured."<<endl;
	   
		cout<<"Press [Enter] to start the Idle Roll."<<endl;
		getch();
	   
		//roll 1 IR and UC at 1 higher Tier each
		IRauto = 1;
		rollCount = 1;
		IdleRolls();
		
		UCTauto = 1;
		rollCount = 1;
		UCprompt();
	
	perPlayer = YesNo();
   }
}



void Ninetales(){                                  //Ninetales
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"NINETALES"<<endl;
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(2);
		   
		  	certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
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
	   
	do{
		if(tdForfeit){forfeit = Forfeit();}
		
		Itotal = Intensity(0);
		
		certainty = makeSure();
		if(!certainty){ tdForfeit = true;}
	}while(!certainty);
	cout<<endl<<endl;
	  
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
	
	cout<<"Press [Enter] to continue to the Idle Roll. "<<endl;
	getch();
	
	rollCount = 3;
	IdleRolls();
	
	perPlayer = YesNo();
   }
}



void Salazzle(){									//Salazzle
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"SALAZZLE"<<endl;
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   cout<<"Players suffer the following as if Brainwashed during the Party Wipe: Instant RB +20, IT/IRT +1, IR +7 (if not calculated already)."<<endl;
		   cout<<"This calculator has had the Intensity bonus added to the following Intensity roll."<<endl;
		   
		   Itotal = Intensity(1);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
	   if(forfeit){
		   Itotal *= 0.5;
		   sleep(1.1);
		   
		   if(Die100()>50){
			   cout<<"Player gains GR: Hypno Suit (Salandit theme)."<<endl;
		   } else {
			   cout<<"Player avoided the GR: Diaper Suit."<<endl;
		   }
	   } else {
		   cout<<"Player gains GR: Hypno Suit (Salandit theme)."<<endl;
	   }
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP."<<endl;
	
	perPlayer = YesNo();
   }
}



void Luxray(){										//Luxray
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"LUXRAY"<<endl;
	   
	do{
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
	
		certainty = makeSure();
		if(!certainty){ tdForfeit = true;}
	}while(!certainty);
	cout<<endl<<endl;
	
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
	
	cout<<"Luxray changes players into Safari diapers."<<endl;
	
	perPlayer = YesNo();
   }
}



void Nidoqueen(){									//Nidoqueen
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"NIDOQUEEN"<<endl;
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(0);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
	   if(forfeit){
		   Itotal *= 0.5;
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
   
   cout<<"Intensity roll of "<<(Itotal)<<" RB/EP."<<endl;
   cout<<"This Caretaker only changes Max Capacity diapers."<<endl;
	
	perPlayer = YesNo();
   }
}



void Vaporeon(){									//Vaporeon
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"VAPOREON"<<endl;
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(0);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
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
   cout<<"This Caretaker only changes Max Capacity diapers."<<endl;
	
	perPlayer = YesNo();
   }
}



void Audino(){										//Audino
		perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"AUDINO"<<endl;
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(intput + 1);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
	   
	   cout<<"The following calculations are done at minimum PL."<<endl;
	   
	   rollCount = 3;
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
   
   
   
   if(forfeit){
	   Itotal *= 0.5;
	   sleep(1.1);
	   
	   if(Die100()>50){
		   cout<<"Player gains 2 stacks of Holding Help."<<endl;
	   } else {
		   cout<<"Player avoided the 2 stacks of Holding Help."<<endl;
	   }
   } else {
	   cout<<"Player gains 2 stacks of Holding Help."<<endl;
   }
   
   cout<<"Intensity roll of "<<Itotal<<" RB/BP."<<endl;
   cout<<"This Caretaker only changes Max Capacity diapers."<<endl;
	
	perPlayer = YesNo();
   }
}



void Lucario(){										//Lucario
		perPlayer = true;
   while(perPlayer == true) {
	   bool skew = false;
	   system("cls");
	   cout<<"LUCARIO"<<endl;
	
	do{
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
	
		certainty = makeSure();
		if(!certainty){ tdForfeit = true;}
	}while(!certainty);
	cout<<endl<<endl;
	
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
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(1);
	   
	   		certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
	   if(forfeit){Itotal *= 0.5;}
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/MP. Player suffers 2 stacks of Obedience during next Caretaker Encounter."<<endl;
	
	perPlayer = YesNo();
   }
}



void Ivysaur(){										//Ivysaur
	int bomb = 0;
	perPlayer = true;
   while(perPlayer == true) {
	   system("cls");
	   cout<<"IVYSAUR (warning: takes a moment to calculate)"<<endl<<endl;
	   
		do{
			if(tdForfeit){forfeit = Forfeit();}
	   
			cout<<"Player is changed into Overnight diaper before any further effects."<<endl;
		   
			Itotal = Intensity(0);
	   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
	   //powder bomb crit fail
	   for(int i = 0; i < 3; i++){
		   bomb = Die4();
		   sleep(1.2);
	   }
	   
	   if(Die20() > 10){cout<<" Player gains a stack of Enhancement."<<endl;}
	   
	   cout<<"Intensity roll of "<<Itotal<<" RB/BP. Powder bomb inflicts "<<(bomb / 2)<<"RB & "<<bomb<<" BP."<<endl;
	   cout<<"In other words, a total of "<<(Itotal+bomb/2)<<" RB and "<<(Itotal+bomb)<<" BP."<<endl;
		
		cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
		
		rollCount = 2;
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
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(0);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
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
	   
	   rollCount = 3;
	   IdleRolls();
	   
	   cout<<"Slowpoke changes diapers into Slowpoke diapers."<<endl;
	   
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
	   
	   cout<<"Snorlax changes diapers into Sleepy diapers."<<endl;
	
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
	   
	   rollCount = 1;
	   IdleRolls();

	   Playtime();
	   
	   cout<<"Mew changes diapers into Mew diapers."<<endl;
	
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
	   
		do{
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
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		
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
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(0);
	   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
	   if(forfeit){
		   Itotal *= 0.5;
		   sleep(1.2);
		   
		   if(Die100()>50){
				cout<<"Player gains GR: Snuggler."<<endl;
		   } else {
			   cout<<"Player avoids GR: Snuggler."<<endl;
		   }
	   } else {
		   cout<<"Player gains GR: Snuggler."<<endl;
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
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   cout<<"Player is Pacified before any further effects."<<endl;
		   
		   Itotal = Intensity(2);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
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
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   foodAuto = Die20()/10 + 1;
		   sleep(1.2);
		   drinkAuto = Die20()/10 + 1;

		   Itotal = Intensity(2);
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
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
	   
	   UCTauto = 2;
	   rollCount = 1;
	   UCprompt();
	   
	   cout<<"Press [Enter] to start the Idle Roll."<<endl<<endl;
		getch();
	   
	   IRauto = 2;
	   rollCount = 1;
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
	   
	   IRauto = 1;
	   rollCount = 3;
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
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   cout<<"The Misfire is not rerolled when generating for several players."<<endl<<endl;
		   
		   cout<<"Delphox casts a random spell on the party!"<<endl;
		   if(mis == 0)
		   {
			   mis = Misfire(false);
		   }
		   cout<<"Delphox casts Misfire #"<<mis<<"! Do not apply this effect until the end."<<endl;
		   
		   Itotal = Intensity(1);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		   
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
	   
		do{
		   if(tdForfeit){forfeit = Forfeit();}
		   
		   Itotal = Intensity(2);
		   
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
	   
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
	   
	   cout<<"Shaymin is non-hostile, so they do not have a forfeit. You also cannot redo on these inputs."<<endl;

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



void Lapras(){										//Lapras
	int die;
  perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"LAPRAS"<<endl<<endl;
		
		die = Die6();
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
			
			Itotal = Intensity(1);
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		
		if(forfeit){
			Itotal *= 0.5;
			sleep(1.1);
			
			if(Die100() > 50){
				cout<<"Player avoided gaining GR: Life Jacket."<<endl;
			} else {
				cout<<"Player gained GR: Life Jacket."<<endl;
			}
			
		} else {
			cout<<"Player gained GR: Life Jacket."<<endl;
		}
		
		cout<<"Player gained "<<Itotal<<" RB/MP and "<<(die + 4)<<" WHP."<<endl;
		
		perPlayer = YesNo();
	}
}



void Milotic(){										//Milotic
  perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"MILOTIC"<<endl<<endl;
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
			
			if(forfeit){Itotal *= 0.5;}
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		
		cout<<"Player gains "<<Itotal<<" RB/EP and 2 WUL."<<endl;
		cout<<"This Caretaker only changes Max Capacity diapers."<<endl;
		
		perPlayer = YesNo();
	}
}



void Sylveon(){										//Sylveon
	int die;
  perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"SYLVEON"<<endl;
		
		die = Die3();
		
		do{
			if(tdForfeit){forfeit = Forfeit();}
			
			Itotal = Intensity(1);
		
			certainty = makeSure();
			if(!certainty){ tdForfeit = true;}
		}while(!certainty);
		cout<<endl<<endl;
		
		//clothing generation
		if(forfeit){
			Itotal *= 0.5;
			
			//if not resisted
			if(Die100() > 50){
				cout<<"Player gains GR: ";
				sleep(1.1);
				
				switch(Die3()){
					case 1:
					cout<<"Baby Clothes";
					break;
					
					case 2:
					cout<<"Frilly Clothes";
					break;
					
					case 3:
					cout<<"Royal Garb";
					break;
				}
				cout<<"."<<endl;
				
			//if resisted
			} else {
				cout<<"Player resisted the clothes GR."<<endl;
			}
			
		//if not forfeit
		} else {
			cout<<"Player gains GR: ";
				
			switch(Die3()){
				case 1:
				cout<<"Baby Clothes";
				break;
				
				case 2:
				cout<<"Frilly Clothes";
				break;
				
				case 3:
				cout<<"Royal Garb";
				break;
			}
			cout<<"."<<endl;
		}
		
		//accessory generation
		if(forfeit){
			sleep(1.2);
			
			//if not resisted
			if(Die100() > 50){
				cout<<"Player gains ";
				switch(die){
					case 1:
					cout<<"GR: Fancy Accessories";
					break;
					
					case 2:
					cout<<"GR: Plastic Pants";
					break;
					
					case 3:
					cout<<"GR: Royal Garb";
					break;
					
					case 4:
					cout<<"Protected Paws";
					break;
					
					case 5:
					cout<<"Baby Bib";
					break;
				}
				cout<<"."<<endl;
			
			//if resisted
			} else {
				cout<<"Player resisted the accessory effect."<<endl;
			}
		
		//if not forfeit
		} else {
			cout<<"Player gains ";
				switch(die){
					case 1:
					cout<<"GR: Fancy Accessories";
					break;
					
					case 2:
					cout<<"GR: Plastic Pants";
					break;
					
					case 3:
					cout<<"GR: Royal Garb";
					break;
					
					case 4:
					cout<<"Protected Paws";
					break;
					
					case 5:
					cout<<"Baby Bib";
					break;
				}
				cout<<"."<<endl;
		}
		
		cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
		
		perPlayer = YesNo();
	}
}



void cLazy(){										//Lazy Crystal
		perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"CRYSTAL OF LAZINESS"<<endl;
		cout<<"This Caretaker cannot be forfeited to."<<endl;
		
		Itotal = Intensity(2);
		
		cout<<"Player gains GR: Lazy for 1 IR, if they hadn't already."<<endl;
		cout<<"Player gains "<<Itotal<<" RB/MP."<<endl;
		
	perPlayer = YesNo();
	}
}



void cSissy(){										//Sissy Crystal
		perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"CRYSTAL OF SISSINESS"<<endl;
		cout<<"This Caretaker cannot be forfeited to."<<endl;
		
		Itotal = Intensity(2);
		
		cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
		
	perPlayer = YesNo();
	}
}



void cLittle(){										//Little Crystal
		perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"CRYSTAL OF LITTLENESS"<<endl;
		cout<<"This Caretaker cannot be forfeited to."<<endl;
		
		Itotal = Intensity(2);
		
		cout<<"Player gains "<<Itotal<<" RB/BP."<<endl;
		
	perPlayer = YesNo();
	}
}



void cDiapers(){									//Diaper Crystal
		perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"CRYSTAL OF DIAPERS"<<endl;
		cout<<"This Caretaker cannot be forfeited to."<<endl;
		
		Itotal = Intensity(2);
		
		cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
		
	perPlayer = YesNo();
	}
}



void cSquish(){										//Squish Crystal
		perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"CRYSTAL OF SQUISHINESS"<<endl;
		cout<<"This Caretaker cannot be forfeited to."<<endl;
		
		Itotal = Intensity(1);
		
		cout<<"Player gains "<<Itotal<<" RB/BP."<<endl;
		
		rollUntil = true;
		UCprompt();
		
	perPlayer = YesNo();
	}
}



void cImmature(){									//Immature Crystal
		perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"CRYSTAL OF IMMATURITY"<<endl;
		cout<<"This Caretaker cannot be forfeited to."<<endl;
		
		Itotal = Intensity(2);
		
		cout<<"Player gains "<<Itotal<<" RB/MP."<<endl;
		
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
		rollCount = 4;
		break;
		
		case 2:
		cout<<"Brainwashed for 3 Idle Rolls (also gains MP)."<<endl;
		rollCount = 3;
		break;
		
		case 3:
		cout<<"Brainwashed for 2 Idle Rolls (also gains MP)."<<endl;
		rollCount = 2;
		break;
		
		case 4:
		cout<<"Roll 2 HC. If either succeeds, Hypnotized for 1 IR (also gains MP)."<<endl;
		rollCount = 1;
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
			rollCount = 1;
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
	rollCount = 1;
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
	bool waddle;
	bool crawl;
	bool powder;
	
	trapSize = Die4();

	perPlayer = true;
while(perPlayer)
{
	
	system("cls");
	cout<<"POWDER DUST ROOM (warning, calculation may take a while)"<<endl<<endl;
	
	do{
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
	
		certainty = makeSure();
	}while(!certainty);
	
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
	
	if(trapSize > 3){
		powder = true;
	} else {
		powder = false;
	}
	
	//calculate points
	cout<<"Calculating";
	for(int i = 0; i < curSize; i++)
	{
		if(i != 0){sleep(1.2);}
		Ptotal += Die6();
		cout<<".";
	}
	
	system("cls");
	
	if(powder){
		cout<<"This player gains GR: Powderified."<<endl;
	}

	cout<<"This trap has a size of "<<curSize<<" for this player."<<endl;
	cout<<"This player gains "<<Ptotal<<" RB/EP, and "<<(Ptotal / 2)<<" BP."<<endl;
	
	Ptotal = 0;
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
	do{
		tRoll = TrapRoll();
		Itotal = Intensity(0);
		
		certainty = makeSure();
	}while(!certainty);
	
	
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
		rollCount = 2;
		UCprompt();
	} else if(tRoll == 5){
		rollCount = 1;
		UCprompt();
	}
	

	//Output
	cout<<"Intensity roll of "<<(Itotal + inten)<<" RB/EP."<<endl;
	
	if(tRoll < 3) {
		cout<<"Player gains GR: Used Diaper Desire."<<endl;
	} else if(tRoll == 4) {
		dice = Die100();
		
		if(dice > 50){
			cout<<"Player gains GR: Used Diaper Desire."<<endl;
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
	system("cls");
	cout<<"Please wait...";
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
	cout<<"CONCENTRATED POWDER PATH (warning: calculation will take some time)"<<endl<<endl;
	
	do{
		
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
	
		certainty = makeSure();
	}while(!certainty);
	
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
	
	//Point gain
	cout<<endl<<"Generating";
	
	for(int i = 0; i < counter; i++)
	{
		Ptotal += Die4() + 2;
		sleep(1.8);
		cout<<".";
	}
	
	cout<<endl<<endl;
	
	//printouts
	if(counter >= 4)
	{
		UCTauto = 1;
		cout<<"Player rolls at 1 higher UC Tier on their Use Checks (automatic)."<<endl;
		cout<<"Player gains GR: Powderified."<<endl;
	}
	
	cout<<"Player tripped "<<counter<<" traps."<<endl;
	cout<<"Player gains "<<Ptotal<<" RB/MP/EP."<<endl;
	
	
	//Use Check(s)
	rollCount = counter;
	UCprompt();
	
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
		dice = Die5();
	} else {
		dice = Die4();
	}

	points = 0;
	
	switch(dice)
	{
		case 1:
			for(i = 0; i < 3; i++)
			{
				sleep(1.9);
				points+= Die4();
			}
			cout<<"Player gains "<<points<<" RB/MP and GR: Drooling."<<endl;
			break;
			
		case 2:
			for(i = 0; i < 3; i++)
			{
				sleep(1.9);
				points+= Die4();
			}
			cout<<"Player gains "<<points<<" RB/BP and GR: Baby Fat."<<endl;
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
			
			if(extra % 2 == 0){
				cout<<" and 1 WUL";
			}
			if(extra % 3 == 0){
				cout<<" and 1 MUL.";
			}
			if((extra % 2 != 0)&&(extra % 3 != 0)){
				cout<<" and 2 UC."<<endl;
				
				rollCount = 2;
				UCprompt();
			} else {
			cout<<endl;
			}
		break;
		
		case 4:
			sleep(1.1);
			points = Die6() + 4;
			
			cout<<"Player gains "<<points<<" RB and diaper alters into a Potions Diaper."<<endl;
		break;
		
		case 5:
			cout<<"Rolled 5! Generating two effects. Player also gains 1 stack of Enhancement."<<endl;
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
	rollCount = 1;
	status = true;
	cout<<"PRESENTATION"<<endl;
	
	switch(tRoll){
		case 1:
		cout<<"Brainwashed for 2 Idle Rolls (also gains MP). Inflicts Normal IT for RB/MP."<<endl;
		rollCount = 2;
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
	int dice = 0;
	int oldDie;
	int die = 1;
	bool idle = false;
	const int LOW = 1;
	const int HIGH = 3;
	time_t seconds;	
	
	
	system("cls");
	perPlayer = true;
while(perPlayer){
	cout<<"PACIFIER DOOR"<<endl;
do{
	if(doubler > 0){ //if multi-rolling from repeat roll
		oldDie = dice;
		sleep(1.3);
		
		if(oldDie != 5){ //if the second reroll of the 2 effects
		time(&seconds);
		srand((unsigned int) seconds);
		die=(rand()%((HIGH-LOW)+LOW))+1;
		
			switch(oldDie){ //prevent repeat of same effect
				case 1: //if first was 1, increase by 1 since can't be 1
				dice = die + 1;
				break;
				
				case 2: //if first was 2 and second is not 1, bump up one
				if(die != 1){
					dice = die + 1;
				}
				break;
				
				case 3: //if first was 3 and second is 3, bump up one
				if(die == 3){
					dice = 4;
				}
				break;
				
				case 4: //if first was 4, no change necessary so pass on
				dice = die;
				break;
				
				default:
				cout<<"ERROR with generating reroll"<<endl;
			}
		
		} else { //if the first reroll from rolling the 2 effects
			dice = Die4();
		}
		
	} else { //doing the first roll
		dice = Die5();
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
			UCprompt();
		break;
		
		case 3:
			cout<<"GR: Drooling. 2 Idle Rolls for all players (does not stack)."<<endl;
			if(!idle){
				rollCount = 2;
				IdleRolls();
			} else {
				cout<<"Idle Rolls do not repeat, can only roll them once."<<endl;
			}
		break;
		
		case 4:
			cout<<"Small IT for RB and diaper alters into a Pacifier Diaper."<<endl;
			Itotal = Intensity(0);
			cout<<"Player gains "<<Itotal<<" RB."<<endl;
		break;
		
		case 5:
			doubler = 3;
			cout<<"Rolled a 5! Generating two effects.";
			if(Die100() > 50)
			{
				cout<<" Additionally, all players are Stupified.";
			}
			cout<<endl<<endl<<endl;
		break;
		
		default:
			cout<<"ERROR IN POTIONS"<<endl;
		
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
	
	if(tRoll <= 2){
		cout<<"Bogged."<<endl;
	} else if(tRoll == 3){
		sleep(1.1);
		if(Die100()>50){
			cout<<"Player gains Bogged."<<endl;
		} else {
			cout<<"Player avoided Bogged."<<endl;
		}
	} else if(tRoll == 4){
		sleep(1.1);
		if(Die100()>75){
			cout<<"Player gains Bogged."<<endl;
		} else {
			cout<<"Player avoided Bogged."<<endl;
		}
	}
	
	switch(tRoll)
	{
		case 1:
		cout<<"Large IT for EP. 1 UC for WHP at 2 higher Tiers."<<endl;
		Itotal = Intensity(3);
		rollCount = 1;
		UCTauto = 2;
		break;
		
		case 2:
		cout<<"Normal IT for EP. 1 UC for WHP at 1 higher Tier."<<endl;
		Itotal = Intensity(2);
		rollCount = 1;
		UCTauto = 1;
		break;
		
		case 3:
		cout<<"Small IT for EP. 1 UC for WHP."<<endl;
		Itotal = Intensity(1);
		rollCount = 1;
		break;
		
		case 4:
		cout<<"Tiny IT for EP. 1 UC for WHP."<<endl;
		Itotal = Intensity(0);
		rollCount = 1;
		break;
		
		case 5:
		cout<<"1 UC for WHP, gain half total. Tiny IT for EP at half total."<<endl;
		Itotal = Intensity(0) / 2;
		rollCount = 1;
		break;
		
		case 6:
		cout<<"No effect, dodged."<<endl;
		break;
		
		default:
		cout<<"ERROR"<<endl;
	}
	
	if(rollCount)
	{
		cout<<"Player gains "<<Itotal<<" EP."<<endl;
		UCprompt();
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
	system("cls");
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
		cout<<"Diaper alters into Overnight before further effect. Roll 3 Idle Rolls."<<endl;
		rollCount = 3;
		break;
		
		case 2:
		cout<<"Diaper alters into Overnight before further effect. Roll 2 Idle Rolls."<<endl;
		rollCount = 2;
		break;
		
		case 3:
		cout<<"Diaper alters into Overnight before further effect. Roll 1 Idle Roll."<<endl;
		rollCount = 1;
		break;
		
		case 4:
		cout<<"Leave room with Sleepy lv. 2. 1 Idle Roll."<<endl;
		rollCount = 1;
		break;
		
		case 5:
		cout<<"Leave room with Sleepy lv. 1."<<endl;
		break;
		
		case 6:
		cout<<"No effect."<<endl;
		break;
	}
	
	if(rollCount)
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
		rollCount = 2;
		GRs = 2;
		break;
		
		case 2:
		cout<<"2 UC. 10 RB. 1 random Ghost Regression."<<endl;
		rollCount = 2;
		GRs = 1;
		break;
		
		case 3:
		cout<<"1 UC. 8 RB. 1 random Ghost Regression."<<endl;
		rollCount = 1;
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
			rollCount = 1;
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
	
	if(rollCount){
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
		rollCount = 5;
		GRs = 1;
		break;
		
		case 2:
		cout<<"3 Idle Rolls with random diaper change and Ghost Regression. GR: Infantile. Stupified."<<endl;
		rollCount = 3;
		GRs = 1;
		break;
		
		case 3:
		cout<<"3 Idle Rolls. Random diaper change. GR: Shorty. Stupified."<<endl;
		rollCount = 3;
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
	
	if(rollCount)
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
	const int HIGH = 13;
	time_t seconds;
	
while(perPlayer)
{
	system("cls");
	cout<<"DRAINING DIAPER TRAP"<<endl;
	
	switch(tRoll)
	{
		case 1:
		cout<<"3 Idle Rolls with a random Trap Diaper. Timer does not decrease."<<endl;
		rollCount = 3;
		break;
		
		case 2:
		cout<<"3 Idle Rolls with a random Trap Diaper. Timer decreases accordingly."<<endl;
		rollCount = 3;
		break;
		
		case 3:
		cout<<"2 Idle Rolls with a random Trap Diaper. Timer decreases accordingly."<<endl;
		rollCount = 2;
		break;
		
		case 4:
		cout<<"1 Idle Roll with a random Trap Diaper. Timer decreases accordingly."<<endl;
		rollCount = 1;
		break;
		
		case 5:
		cout<<"Random Trap Diaper for 2 Idle Rolls."<<endl;
		break;
		
		case 6:
		cout<<"Random Trap Diaper for 1 Idle Roll."<<endl;
		break;
	}
	
	time(&seconds);
	srand((unsigned int) seconds);
	dice=(rand()%((HIGH-LOW)+LOW))+1;
	
	if(rollCount)
	{
		sleep(1.2);
		IdleRolls();
	}
	
	cout<<endl<<"Player has diaper altered into diaper #"<<(dice + 29)<<endl;
	
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
		rollCount = 3;
		rolls = 4;
		penalty = 4;
		pValue = 5;
		break;
		
		case 2:
		cout<<"3 Idle Rolls. RB/MP +5 per hit, roll 1d4 + 2 for hits."<<endl;
		rollCount = 3;
		rolls = 4;
		penalty = 2;
		pValue = 5;
		break;
		
		case 3:
		cout<<"2 Idle Rolls. RB/MP + 4 per hit, 1d2 + 2 for hits."<<endl;
		rollCount = 2;
		rolls = 2;
		penalty = 2;
		pValue = 4;
		break;
		
		case 4:
		cout<<"2 Idle Rolls. RB/MP +3 per hit, 1d2 + 2 for hits."<<endl;
		rollCount = 2;
		rolls = 2;
		penalty = 2;
		pValue = 3;
		break;
		
		case 5:
		cout<<"1 Idle Roll. RB/MP +4 per hit, 1d2 for hits."<<endl;
		rollCount = 1;
		rolls = 2;
		penalty = 0;
		pValue = 4;
		break;
		
		case 6:
		cout<<"1 Idle Roll. No hits taken."<<endl;
		rollCount = 1;
		rolls = 0;
		break;
	}
	
	if(rollCount)
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
		rollCount = 3;
		rolls = 4;
		penalty = 4;
		pValue = 5;
		break;
		
		case 2:
		cout<<"3 Idle Rolls. RB/EP +5 and UHP +3 per hit, roll 1d4 + 2 for hits."<<endl;
		rollCount = 3;
		rolls = 4;
		penalty = 2;
		pValue = 5;
		break;
		
		case 3:
		cout<<"2 Idle Rolls. RB/EP + 4 and UHP +3 per hit, 1d2 + 2 for hits."<<endl;
		rollCount = 2;
		rolls = 2;
		penalty = 2;
		pValue = 4;
		break;
		
		case 4:
		cout<<"2 Idle Rolls. RB/EP +3 and UHP +2 per hit, 1d2 + 2 for hits."<<endl;
		rollCount = 2;
		rolls = 2;
		penalty = 2;
		pValue = 3;
		Upoints = 2;
		break;
		
		case 5:
		cout<<"1 Idle Roll. RB/EP +4 and UHP +3 per hit, 1d2 for hits."<<endl;
		rollCount = 1;
		rolls = 2;
		penalty = 0;
		pValue = 4;
		break;
		
		case 6:
		cout<<"1 Idle Roll. No hits taken."<<endl;
		rollCount = 1;
		rolls = 0;
		break;
	}
	
	if(rollCount)
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
		rollCount = 3;
		rolls = 4;
		penalty = 4;
		pValue = 5;
		break;
		
		case 2:
		cout<<"3 Idle Rolls. RB/BP +5 per hit, roll 1d4 + 2 for hits."<<endl;
		rollCount = 3;
		rolls = 4;
		penalty = 2;
		pValue = 5;
		break;
		
		case 3:
		cout<<"2 Idle Rolls. RB/BP + 4 per hit, 1d2 + 2 for hits."<<endl;
		rollCount = 2;
		rolls = 2;
		penalty = 2;
		pValue = 4;
		break;
		
		case 4:
		cout<<"2 Idle Rolls. RB/BP +3 per hit, 1d2 + 2 for hits."<<endl;
		rollCount = 2;
		rolls = 2;
		penalty = 2;
		pValue = 3;
		break;
		
		case 5:
		cout<<"1 Idle Roll. RB/BP +4 per hit, 1d2 for hits."<<endl;
		rollCount = 1;
		rolls = 2;
		penalty = 0;
		pValue = 4;
		break;
		
		case 6:
		cout<<"1 Idle Roll. No hits taken."<<endl;
		rollCount = 1;
		rolls = 0;
		break;
	}
	
	if(rollCount)
	{
		status = true;
		cout<<"Press [Enter] to begin Idle Roll."<<endl;
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
		rollCount = counter;
		break;
		
		case 2:
		cout<<"Player rolls "<<counter<<" Mess Use Checks."<<endl;
		rollCount = counter;
		break;
		
		case 3:
		rollCount = counter / 2 + rounding;
		cout<<"Player rolls "<<rollCount<<" Use Checks."<<endl;
		break;
		
		case 4:
		cout<<"Player does not make any additional rolls."<<endl;
		break;
		
		default:
		cout<<"ERROR. Dice generated wrong."<<endl;
		break;
	}
	
	if(rollCount)
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
			rollCount = 2;
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
	
	cout<<"Roll to hit against two players as if Caretaker is attacking both. Caretaker will be the last to move when combat begins."<<endl;
	cout<<"Combat MUST be engaged in this Encounter. Forfeits are allowed turn 1."<<endl;
	
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
	
	rollCount = 1;
	
	switch(tRoll)
	{
		case 1:
		cout<<"Advocate for 2 IR and GR: Snuggler. 1 Idle Roll, also applied to EP."<<endl;
		break;
		
		case 2:
		cout<<"Advocate for 2 IR and GR: Snuggler. 1d5 RB/EP."<<endl;
		break;
		
		case 3:
		cout<<"Advocate for 1 IR and GR: Snuggler. 1d5 RB/EP."<<endl;
		break;
		
		case 4:
		cout<<"GR: Snuggler for 1 IR. 1d5 RB/EP."<<endl;
		break;
		
		case 5:
		cout<<"GR: Snuggler for 1 IR."<<endl;
		break;
		
		case 6:
		cout<<"No effect, resisted."<<endl;
		rollCount = 0;
		break;
		
		default:
		cout<<"ERROR"<<endl;
		break;
	}
	
	cout<<endl;
	
	if(rollCount)
	{
		cout<<"Press [Enter] to begin Idle Roll."<<endl;
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
		rollCount = 2;
		UCprompt();
		break;
		
		case 5:
		cout<<"Player gains GR: Diaper Trained and rolls 1 Use Check."<<endl;
		rollCount = 1;
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



void DivePool(){									//Diving FoY Pool
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"DIVING FOY POOL"<<endl<<endl;
	
	cout<<"Encounter starts with Pool Prep, players may gain Floaties, GR: Life Jacket, or change into a Swim diaper beforehand."<<endl;
	
	do{
		Itotal = Intensity(0);
		
		tRoll = TrapRoll();
		
		certainty = makeSure();
	}while(!certainty);
	
	cout<<"If player is not wearing a Swim diaper, they gain "<<(Die20()/10+1)<<" WULs."<<endl;
	
	switch(tRoll)
	{
		case 1:
			cout<<"Bogged."<<endl;
			sleep(1.1);
			
			if(Die100()>50){
				cout<<"Little'd."<<endl;
			} else {
				cout<<"Teenified."<<endl;
			}
			
			cout<<"Player gains "<<(Itotal + 10)<<" RB/EP."<<endl;
		break;
		
		case 2:
			cout<<"Bogged."<<endl;
			sleep(1.1);
			
			if(Die100()>75){
				cout<<"Little'd."<<endl;
			} else {
				cout<<"Teenified."<<endl;
			}
			
			cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
		break;
		
		case 3:
			sleep(1.1);
			
			if(Die100()>50){
				cout<<"Bogged."<<endl;
			} else {
				cout<<"Player avoided Bogged."<<endl;
			}
			
			cout<<"Teenified."<<endl;
			cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
		break;
		
		case 4:
			sleep(1.1);
			
			if(Die100()>75){
				cout<<"Bogged."<<endl;
			} else {
				cout<<"Player avoided Bogged."<<endl;
			}
			sleep(1.1);
			
			if(Die100()>50){
				cout<<"Teenified."<<endl;
			} else {
				cout<<"Player avoided Teenified but instead gains "<<(Itotal + 10)<<" RB/BP."<<endl;
			}			
		break;
		
		case 5:
		sleep(1.1);
		
			if(Die100()>50){
				cout<<"Teenified."<<endl;
			} else {
				cout<<"Player avoided Teenified but instead gains "<<Itotal<<" RB/BP."<<endl;
			}
		break;
		
		case 6:
		cout<<"Player "<<Itotal<<" RB/BP."<<endl;
		break;
	}
	
	perPlayer = YesNo();
 }
}



void SirenSong(){									//Siren's Ballad
	perPlayer = true;
	
while(perPlayer)
{
	system("cls");
	cout<<"SIREN'S BALLAD"<<endl;
	
	cout<<"Encounter starts with Pool Prep, players may inflict Floaties, GR: Life Jacket, or change into a Swim diaper beforehand."<<endl;
	
	do{
		tRoll = TrapRoll();
		Itotal = Intensity(0);
		
		certainty = makeSure();
	}while(!certainty);
	
	cout<<"If player is not wearing a Swim diaper, they gain "<<(Die20()/10+1)<<" WULs."<<endl;
	
	if(tRoll < 5){cout<<"Player gains Enlightened."<<endl;}
	
	switch(tRoll)
	{
		case 1:
			randomGR(2);
			cout<<"Player gains "<<(Itotal + 20)<<" RB/MP."<<endl;
		break;
		
		case 2:
			randomGR(2);
			cout<<"Player gains "<<(Itotal + 10)<<" RB/MP."<<endl;
		break;
		
		case 3:
			sleep(1.1);
			
			if(Die100()>50){
				randomGR(2);
			} else {
				cout<<"Player avoided the random GR."<<endl;
			}
			cout<<"Player gains "<<(Itotal + 10)<<" RB/MP."<<endl;
		break;
		
		case 4:
		case 5:
			cout<<"Player gains "<<(Itotal + 10)<<" RB/MP."<<endl;
		break;
		
		case 6:
			cout<<"Player gains "<<Itotal<<" RB/MP."<<endl;
		break;
	}
	
	perPlayer = YesNo();
 }
}



void foyGun(){										//FoY Water Gun Turret
	int die;
	int die2;
	perPlayer = true;
while(perPlayer)
{
	system("cls");
	cout<<"FOY WATER GUN TURRET"<<endl;
	
	tRoll = TrapRoll();
	
	if(tRoll <= 3){
		cout<<"Player gains Little'd."<<endl;
		sleep(1.1);
	} else if(tRoll == 4){
		sleep(1.2);
		if(Die100()>50){
			cout<<"Player gains Little'd."<<endl;
		} else {
			cout<<"Player gains Teenified."<<endl;
		}
	} else if(tRoll == 5){
		cout<<"Player gains Teenified."<<endl;
	}
	
	switch(tRoll)
	{
		case 1:
			cout<<"Player gains GR: ";
			
			die = Die4();
			//generate first GR
			switch(die){
				case 1:
					cout<<"Immature";
				break;
				case 2:
					cout<<"Baby Logic";
				break;
				case 3:
					cout<<"Vocab Regression";
				break;
				
				case 4:
					cout<<"Self-Distractor";
				break;
			}
			sleep(1.1);
			cout<<" and ";
			
			//ensure GRs don't stack for second
			do{
				die2 = Die4();
				if(die == die2){sleep(1.1);}
			}while(die == die2);
			
			//generate second GR
			switch(die2){
				case 1:
					cout<<"Immature.";
				break;
				case 2:
					cout<<"Baby Logic.";
				break;
				case 3:
					cout<<"Vocab Regression.";
				break;
				
				case 4:
					cout<<"Self-Distractor.";
				break;
			}
		cout<<endl;
		break;
		
		case 2:
			cout<<"Player gains GR: ";
			
			die = Die4();
			switch(die){
				case 1:
					cout<<"Immature ";
				break;
				case 2:
					cout<<"Baby Logic ";
				break;
				case 3:
					cout<<"Vocab Regression ";
				break;
				
				case 4:
					cout<<"Self-Distractor ";
				break;
			}
		break;
		
		case 3:
			if(Die100()>50){
				cout<<"Player gains GR: ";
				
				sleep(1.1);
				die = Die4();
				switch(die){
					case 1:
						cout<<"Immature ";
					break;
					case 2:
						cout<<"Baby Logic ";
					break;
					case 3:
						cout<<"Vocab Regression ";
					break;
					
					case 4:
						cout<<"Self-Distractor ";
					break;
				}
			} else {
				cout<<"Player avoided the random effect."<<endl;
			}
		break;
		
		case 6:
		cout<<"No effect, avoided."<<endl;
		break;
	}
	
	perPlayer = YesNo();
 }
}



void MCP(){											//Multicolor Crystal Path
	int jewels [2];
	const int LOW = 1;
	const int HIGH = 9;
	time_t seconds;
	int val;
	
	perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"MULTICOLOR CRYSTAL PATH (what a mouthful)"<<endl;
		
		tRoll = TrapRoll();
		
		if(tRoll == 1){
			val = 0;
		} else {
			val = 1;
		}
		for(int i = 0; i < 2; i++){
			time(&seconds);
			srand((unsigned int) seconds);
			jewels[i]=(rand()%((HIGH-LOW)+LOW))+1;
			
			if(i != 1){ sleep(1.1); }
		}
		
		switch(tRoll){
			case 1: //critical failure
				Itotal = Intensity(2);
				
				cout<<"Player gains";
				jewelry(jewels[0]);
				cout<<" and ";
				jewelry(jewels[1]);
				cout<<"."<<endl<<"Player gains "<<Itotal<<" RB/EP."<<endl;
			break;
			
			case 2: //heavy failure
				Itotal = Intensity(2);
				cout<<"Player gains";
				jewelry(jewels[1]);
				cout<<"."<<endl<<"Player gains "<<Itotal<<" RB/EP."<<endl;
			break;
			
			case 3: //expected failure
				Itotal = Intensity(1);
				cout<<"Player gains";
				jewelry(jewels[1]);
				cout<<"."<<endl<<"Player gains "<<Itotal<<" RB/EP."<<endl;
			break;
			
			case 4: //resisted
				Itotal = Intensity(1);
				
				if(Die100() > 50){
					cout<<"Player gains";
					jewelry(jewels[1]);
				} else {
					cout<<"Player avoided the random Jewelry status.";
				}
				cout<<"."<<endl<<"Player gains "<<Itotal<<" RB/EP."<<endl;
			break;
			
			case 5: //partial success
				Itotal = Intensity(1);
				cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
			break;
			
			case 6: //full success
				Itotal = Intensity(0);
				cout<<"Player gains "<<Itotal<<" RB/EP."<<endl;
			break;
			
			default:
				cout<<"ERROR"<<endl;
		}
			
		perPlayer = YesNo();
	}
}



void TimeDistort(){									//Time Distortion
	int GRs [2];
	system("cls");
	cout<<"TIME DISTORTION"<<endl;

	tRoll = TrapRoll();

	perPlayer = true;
	while(perPlayer){
		system("cls");
		cout<<"TIME DISTORTION"<<endl;
		
		Itotal = 0;
		GRs[0] = Die3();
		
		switch(tRoll){
			case 1:
				cout<<"Critical failure."<<endl;
				
				Itotal = Intensity(1);
				
				cout<<"Player gains the following GRS: Little'd, Immature, and Baby Clothes."<<endl;
			break;
			
			case 2:
			case 3:
				if(tRoll == 2){
					cout<<"Heavy failure."<<endl;
				} else {
					cout<<"Expected failure."<<endl;
				}
				
				if(tRoll == 2){
					Itotal = Intensity(1);
				} else {
					Itotal = Intensity(0);
				}
				
				GRs[1] = (Die20()/10) + 1;
				
				cout<<"Player gains GRs: ";
				
				switch(GRs[0]){
					case 1: //if first is 1, second is bumped by 1
						GRs[1]++;
						
						cout<<"Little'd and ";
					break;
					
					case 2: //if first is 2, bump up to 3 if 2
						if(GRs[1] == 2){
							GRs[1]++;
						}
						
						cout<<"Immature and ";
					break;
					
					case 3: //if first is 3, no change to second GR
						cout<<"Baby Clothes and ";
					break;
					
					default:
						cout<<"ERROR on first GR calc and ";
				}
				
				switch(GRs[1]){
					case 1:
						cout<<"Little'd."<<endl;
					break;
					
					case 2:
						cout<<"Immature."<<endl;
					break;
					
					case 3:
						cout<<"Baby Clothes."<<endl;
					break;
					
					default:
						cout<<"ERROR on second GR calc."<<endl;
				}			
			break;
			
			case 4:
				cout<<"Resisted."<<endl;
				
				Itotal = Intensity(0);
				
				cout<<"Player gains GR: ";
				switch(GRs[0]){
					case 1:
						cout<<"Little'd."<<endl;
					break;
					
					case 2:
						cout<<"Immature."<<endl;
					break;
					
					case 3:
						cout<<"Baby Clothes."<<endl;
					break;
					
					default:
						cout<<"ERROR on second GR calc"<<endl;
				}
			break;
			
			case 5:
				cout<<"Partial success."<<endl;
				
				cout<<"Player gains GR: ";
				switch(GRs[0]){
					case 1:
						cout<<"Little'd."<<endl;
					break;
					
					case 2:
						cout<<"Immature."<<endl;
					break;
					
					case 3:
						cout<<"Baby Clothes."<<endl;
					break;
					
					default:
						cout<<"ERROR on second GR calc"<<endl;
				}
			break;
			
			case 6:
				cout<<"Full success."<<endl;
				
				Itotal = Intensity(0);
			break;
			
			default:
				cout<<"ERROR"<<endl;
		}
		
		if(Itotal != 0){
			cout<<"Player gains "<<Itotal<<" RB/MP/BP/EP."<<endl;
		}
		
		perPlayer = YesNo();
	}
}