#include "Player.h"
#include "Farm.h"
#include "GroupADT.h"
#include <string>
#include "Visitor.h"
#include "BTree.h"
#include "ConsoleHandler.h"
#include "Livestock.h"
#include "SingleNode.h"
#include "Queue.h"
#include "Stack.h"


void Player::initializeTree()
{

	convoTree = new BTree<string>(*(new string("Good Day")));
	BTree<string>* tree2 = new BTree<string>(*(new string("How does the game work?")));
	BTree<string>* tree3 = new BTree<string>(*(new string("How can I maximise my earnings?")));
	BTree<string>* tree4 = new BTree<string>(*(new string("The player has to plant crops and rear animals to be sold. Seeds and animals can be bought from the market and sold after that.")));
	BTree<string>* tree5 = new BTree<string>(*(new string("Choose the right plant and animals")));

	convoTree->attachLeft(*tree2);
	convoTree->attachRight(*tree4);
	convoTree->getLeft().attachLeft(*tree3);
	convoTree->getLeft().attachRight(*tree5);
}

Player::~Player()
{
	delete farm;
	delete notifications;
	delete convoTree;
}
Player::Player(Farm& aFarm)
{
	penny = 300;
	farm = &aFarm;
	notifications = new GroupADT();
	initializeTree();
}

void Player::plant()
{
	string seed;
	int quantity;

	vector<Item> inventory = farm->getInventory();
	if (!inventory.empty())
	{
		bool finish = false;

		//prompt seed name
		while (!finish)
		{
			bool valid = false;
			while (!valid)
			{
				cout << endl << "Seed to plant (F-Finish):" << endl;
				getline(cin, seed);
				if (seed == "F" || seed == "f")
				{
					finish = true;
					break;
				}

				for (Item item : inventory)
				{
					if (item.getName() == seed)
					{
						valid = true;
						break;
					}
				}

				if (!valid)
				{
					cout << "Seed cannot be found in inventory..." << endl;
				}
				else
				{
					valid = false;
					//prompt quantity to plant
					while (!valid)
					{
						string quantityToPlant;
						cout << "Quantity to plant:" << endl;
						getline(cin, quantityToPlant);
						try
						{
							quantity = stoi(quantityToPlant);
							if (quantity > 0 && quantity <= farm->getLandSize())
							{
								for (unsigned int i = 0; i < inventory.size(); i++)
								{
									Item item = inventory[i];
									if (item.getName() == seed && item.getQuantity() >= quantity)
									{
										cout << item.getMessage() << endl;
										farm->setLandSize(farm->getLandSize() - quantity);  //reduce land size available
										Item plantedItem = item;
										plantedItem.setQuantity(quantity);
										Livestock newLivestock(plantedItem);
										SingleNode<Livestock>* newNode = new SingleNode<Livestock>(newLivestock);
										farm->getPlantations()->enqueue(*newNode);	//add to plantations
										int updatedQuantity = item.getQuantity() - quantity;
										if (updatedQuantity > 0)
										{
											item.setQuantity(updatedQuantity);
											inventory[i] = item;
										}
										else if (updatedQuantity == 0)
										{
											inventory.erase(inventory.begin() + i);
										}
										farm->setInventory(inventory);
										COORD latestPos = consoleHandler.getCursorPosition();
										consoleHandler.updateConsole(latestPos, *farm, penny);
										valid = true;
										break;
									}
									else if (item.getName() == seed && item.getQuantity() < quantity)
									{
										cout << "Insufficient seeds available in inventory...Only " << item.getQuantity() << " seeds available." << endl;
										break;
									}
								}
							}
							else if (quantity > farm->getLandSize())
							{
								cout << "Insufficient land size..." << endl;
							}
							else
							{
								cout << "Invalid quantity...Please try again" << endl;
							}
						}
						catch (exception e)
						{
							cout << "Invalid input...Only input numbers..." << endl;
						}


					}
				}
			}
		}
	}
	else
	{
		cout << endl << "No items available..." << endl;
		system("pause");

	}

}


void Player::buy()
{
	string itemName;
	int quantity;
	int totalCost;
	Item itemToBuy;
	bool finish = false;

	cout << endl << "--------------------------" << endl;
	cout << "Items Available In Market" << endl;
	cout << "--------------------------" << endl;
	Item* market = farm->getMarket();
	int length = 6;
	for (int i = 0; i < length; i++)
	{
		market[i].displayDetails("market");
	}

	while (!finish)
	{
		bool valid = false;
		while (!valid)
		{
			cout << endl << "Item to buy (F-Finish):" << endl;
			getline(cin, itemName);

			if (itemName == "F" || itemName == "f")
			{
				finish = true;
				break;
			}

			for (int i = 0; i < length; i++)
			{
				if (market[i].getName() == itemName)
				{
					itemToBuy = market[i];
					valid = true;
					break;
				}
			}

			if (!valid)
			{
				cout << "Invalid item name...Try again" << endl;
			}
			else
			{
				valid = false;
				while (!valid)
				{
					string quantityToBuy;
					cout << "Quantity to buy:" << endl;
					getline(cin, quantityToBuy);
					try
					{
						quantity = stoi(quantityToBuy);
						itemToBuy.setQuantity(quantity);
						valid = true;
					}
					catch (exception e)
					{
						cout << "Invalid input...Only input numbers" << endl;
					}
				}

				if (itemToBuy.getType() == "animal" && quantity > farm->getLandSize()) 
				{
					cout << "Insufficient land size" << endl;
				}
				else 
				{
					totalCost = itemToBuy.getQuantity() * itemToBuy.getCostPrice();
					if (penny >= totalCost)
					{
						COORD latestPos = consoleHandler.getCursorPosition();
						//seed bought will be added to inventory while animals bought will directly be reared and stored in animalsReared
						//add seed bought to inventory
						if (itemToBuy.getType() == "plant")
						{
							bool exist = false;
							vector<Item> inventory = farm->getInventory();
							for (Item& item : inventory)
							{
								if (item.getName() == itemToBuy.getName())
								{
									exist = true;
									item.setQuantity(item.getQuantity() + quantity);

								}
							}
							if (!exist)
							{
								inventory.push_back(itemToBuy);
							}
							farm->setInventory(inventory);
						}
						else
						{
							Livestock livestock(itemToBuy);
							SingleNode<Livestock>* node = new SingleNode<Livestock>(livestock);
							farm->getAnimalsReared()->enqueue(*node);
							farm->setLandSize(farm->getLandSize() - itemToBuy.getQuantity());
						}


						penny = penny - (itemToBuy.getQuantity() * itemToBuy.getCostPrice());	//reduce player's money
						consoleHandler.updateConsole(latestPos, *farm, penny);

					}
				}
				
			}
		}

	}
}


void Player::readNotes()
{
	bool run = true;
	Stack* notes = farm->getNotes();
	string option;
	cout << endl << "-----------" << endl;
	cout << "Read Notes" << endl;
	cout << "-----------" << endl;

	while (run)
	{
		
		run = notes->peek();
		
		if (!run)
		{
			cout << "Notes has finished..." << endl;
			system("pause");
			break;

		}

		notes->pop();
		cout << "Press 'n' to read the next note...";
		getline(cin, option);
	}
}

void Player::harvest()
{
	string name;
	string type;
	bool finish = false;
	while (!finish)
	{
		cout << endl << "Animal / Plant(F-finish):" << endl;
		getline(cin, type);

		if (type == "Animal")
		{
			cout << "Animal Name:" << endl;
			getline(cin, name);
			vector<Livestock> animalsReared = notifications->getAnimalsReared();
			vector<Livestock> updatedLivestock = updateHarvestInventory(animalsReared, name);
			notifications->setAnimalsReared(updatedLivestock);

		}
		else if (type == "Plant")
		{
			cout << "Plant Name:" << endl;
			getline(cin, name);
			vector<Livestock> plantations = notifications->getPlantations();
			vector<Livestock> updatedLivestock = updateHarvestInventory(plantations, name);
			notifications->setPlantations(updatedLivestock);
		}
		else if (type == "F" || type == "f")
		{
			finish = true;
		}
		COORD latestPos = consoleHandler.getCursorPosition();
		consoleHandler.updateConsole(latestPos, *farm, penny);

	}


}

vector<Livestock> Player::updateHarvestInventory(vector<Livestock> livestock, string name)
{
	bool valid = false;
	vector<Livestock> updatedLivestock = livestock;

	for (unsigned int i = 0; i < livestock.size(); i++)
	{
		Item item = livestock[i].getItem();
		if (item.getName() == name)
		{
			valid = true;
			cout << "Harvesting..." << endl;
			farm->setLandSize(farm->getLandSize() + item.getQuantity());	//update landsize
			vector<Item> harvestInventory = farm->getHarvestInventory();
			updatedLivestock.erase(updatedLivestock.begin() + i);
			bool exist = false;

			for (unsigned int j = 0; j < harvestInventory.size(); j++)
			{
				Item harvestItem = harvestInventory[j];
				if (harvestItem.getName() == name)	//if there is already the same plant or animals in the harvest inventory, just increase the quantity
				{
					exist = true;
					Item updatedItem = item;
					updatedItem.setQuantity(updatedItem.getQuantity() + harvestItem.getQuantity());
					harvestInventory[j] = updatedItem;
					break;
				}
			}

			if (!exist)
			{
				harvestInventory.push_back(item);
			}

			farm->setHarvestInventory(harvestInventory);
			break;
		}

		if (!valid)
		{
			cout << "Invalid name..." << endl;
		}
	}
	return updatedLivestock;
}

void Player::talk()
{
	cout << endl << "Questions you can ask:" << endl;
	convoTree->display();
	cout << "Press 'f' to finish talking..." << endl;
	cout << endl << "You: " << convoTree->getKey() << endl;
	while (true)
	{
		cout << "You: ";
		string question;
		getline(cin, question);
		if (question == "F" || question == "f")
		{
			break;
		}
		BTree<string>* searchTree = &(convoTree->search(question));
		if (searchTree->isEmpty())
		{
			cout << "Invalid question..." << endl;
		}
		else
		{
			cout << "Mayor:" << searchTree->getKey() << endl;
		}
	}


}

void Player::sell()
{


	vector<Item> harvestInventory = farm->getHarvestInventory();
	if (harvestInventory.empty())
	{
		cout << endl << "No items available..." << endl;
		system("pause");

	}
	else
	{
		string itemName;
		int quantity;
		bool finish = false;
		
		while (!finish) 
		{
			bool valid = false;

			while (!valid)
			{
				cout << endl << "Item to sell(F-Finish):" << endl;
				getline(cin, itemName);

				if (itemName == "f" || itemName == "F") 
				{
					finish = true;
					break;
				}
				
				
				for (Item item : harvestInventory)
				{
					if (item.getName() == itemName)
					{
						valid = true;
						break;
					}
				}

				if (!valid)
				{
					cout << "Invalid item name...Try again" << endl;
				}
				else
				{
					valid = false;
					while (!valid)
					{
						string quantityToSell;
						cout << "Quantity to sell:" << endl;
						getline(cin, quantityToSell);
						try
						{
							quantity = stoi(quantityToSell);

							if (quantity > 0)
							{

								for (unsigned int i = 0; i < harvestInventory.size(); i++)
								{
									Item item = harvestInventory[i];
									if (item.getName() == itemName)
									{
										if (item.getQuantity() >= quantity)
										{
											penny = penny + quantity * item.getSellingPrice();
											int updatedQuantity = item.getQuantity() - quantity;

											if (updatedQuantity > 0)
											{
												item.setQuantity(updatedQuantity);
												harvestInventory[i] = item;
											}
											else if (updatedQuantity == 0)
											{
												harvestInventory.erase(harvestInventory.begin() + i);
											}
											farm->setHarvestInventory(harvestInventory);	//update inventory quantity
											valid = true;
											COORD latestPos = consoleHandler.getCursorPosition();
											consoleHandler.updateConsole(latestPos, *farm, penny);
										}
										else
										{
											cout << "Insufficient quantity to sell...You only have " << item.getQuantity() << " " << item.getName() << "..." << endl;
										}

										break;
									}

								}
							}
							else
							{
								cout << "Invalid quantity..." << endl;
							}

						}
						catch (exception e)
						{
							cout << "Invalid input...Only input numbers..." << endl;
						}
					}
				}
				
				
			}

			
		}
		
	}

}

void Player::viewPlantations() 
{
	cout << endl << "------------" << endl;
	cout << "Plantations" << endl;
	cout << "------------" << endl;
	farm->getPlantations()->displayQueue();

	cout << endl << "---------------" << endl;
	cout << "Animals Reared" << endl;
	cout << "---------------" << endl;
	farm->getAnimalsReared()->displayQueue();
	system("pause");

}

void Player::checkNotifications()
{
	notifications->display();
	system("pause");

}

void Player::accept(Visitor& visitor)
{
	visitor.visit(*this);
}

int Player::getPenny()
{
	return penny;
}

GroupADT& Player::getNotifications()
{
	return *notifications;
}


