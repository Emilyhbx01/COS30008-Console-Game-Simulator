#pragma once
#include <iostream>
using namespace std;
#include "Farm.h"
#include "GroupADT.h"
#include <string>
#include "Visitor.h"
#include "BTree.h"
#include <Windows.h>

class Player 
{
	private:
		int penny;
		Farm* farm;
		GroupADT* notifications;
		BTree<string>* convoTree;
		void initializeTree() 
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

	public:
		~Player()
		{
			delete farm;
			delete notifications;
			delete convoTree;
		}
		Player(Farm& aFarm) 
		{
			penny = 300;
			farm = &aFarm;
			notifications = new GroupADT();
			initializeTree();
		}

		void plant() 
		{
			string seed;
			int quantity;
			bool hasItems = false;
			
			vector<Item> inventory = farm->getInventory();
			cout << endl << "----------------" << endl;
			cout << "Items Available" << endl;
			cout << "----------------" << endl;

			for (Item item : inventory) 
			{
				cout << "Item:" << item.getName() << endl;
				cout << "Quantity:" << item.getQuantity() << endl << endl;
				hasItems = true;
			} 
			
			if (hasItems) 
			{
				bool finish = false;

				//prompt seed name
				while (!finish)
				{
					bool valid = false;
					while (!valid) 
					{
						cout << "Seed to plant (F-Finish):" << endl;
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
										int index = -1;
										for (Item item : inventory)
										{
											index++;
											if (item.getName() == seed && item.getQuantity() >= quantity)
											{
												cout << item.getMessage() << endl;
												farm->setLandSize(farm->getLandSize() - quantity);  //reduce land size available
												Item plantedItem = item;
												plantedItem.setQuantity(quantity);
												Livestock newLivestock = Livestock(plantedItem);
												SingleNode<Livestock>* newNode = new SingleNode<Livestock>(newLivestock);
												farm->getPlantations()->enqueue(*newNode);	//add to plantations
												int updatedQuantity = inventory[index].getQuantity() - quantity;
												if (updatedQuantity > 0)
												{
													inventory[index].setQuantity(updatedQuantity);
												}
												else if (updatedQuantity == 0)
												{
													inventory.erase(inventory.begin() + index);
												}
												farm->setInventory(inventory);
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
				cout << "No items available..." << endl;
				Sleep(500);
			}
			
		}

		void buy() 
		{
			string itemName;
			int quantity;
			int totalCost;
			Item item;
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
							item = market[i];
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
								item.setQuantity(quantity);
								valid = true;
							}
							catch (exception e)
							{
								cout << "Invalid input...Only input numbers" << endl;
							}
						}

						totalCost = item.getQuantity() * item.getCostPrice();
						if (penny >= totalCost)
						{
							//seed bought will be added to inventory while animals bought will directly be reared and stored in animalsReared
							//add seed bought to inventory
							if (item.getType() == "plant")
							{
								bool exist = false;
								vector<Item> inventory = farm->getInventory();
								for (Item item : inventory)
								{
									if (item.getName() == itemName)
									{
										exist = true;
										item.setQuantity(item.getQuantity() + quantity);
									}
								}
								if (!exist)
								{
									inventory.push_back(item);
									farm->setInventory(inventory);
								}
							}
							else
							{
								Queue* animalsReared = farm->getAnimalsReared();
								Livestock livestock(item);
								SingleNode<Livestock>* node = new SingleNode<Livestock>(livestock);
								animalsReared->enqueue(*node);
								farm->setLandSize(farm->getLandSize() - item.getQuantity());
							}

							penny = penny - (item.getQuantity() * item.getCostPrice());	//reduce player's money
						}
						else
						{
							cout << "Insufficient penny...You only have " << penny << " penny" << endl;
						}
					}
				}
				
			}
		}

		void readNotes() 
		{
			bool run = true;
			Stack* notes = farm->getNotes();
			string option;

			cout << endl <<  "-----------" << endl;
			cout << "Read Notes" << endl;
			cout << "-----------" << endl;
			
			while (run)
			{
				cout << "1) Next" << endl;
				cout << "2) Finish" << endl;
				cout << "Enter your choice:" << endl;
				getline(cin, option);
				
				if (option == "1") 
				{
					run = notes->peek();
					if (!run) 
					{
						cout << "Notes has finished..." << endl;
					}

					notes->pop();
					Sleep(500);
				}
				else if (option == "2") 
				{
					run = false;
				}

			
			}
		}

		void harvest()
		{
			string name;
			string type;
			bool finish = false;
			while (!finish) 
			{
				cout << "Animal / Plant(F-finish):" << endl;
				getline(cin, type);

				if (type == "animal")
				{
					cout << "Animal Name:" << endl;
					getline(cin, name);
					vector<Livestock> animalsReared = notifications->getAnimalsReared();
					vector<Livestock> updatedLivestock = updateHarvestInventory(animalsReared, name);
					notifications->setAnimalsReared(updatedLivestock);

				}
				else if (type == "plant")
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

			}
			
			
		}

		vector<Livestock> updateHarvestInventory(vector<Livestock> livestock,string name) 
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

		void talk() 
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

		void sell() 
		{
			
			cout << endl << "--------------------------" << endl;
			cout << "Items In Harvest Inventory" << endl;
			cout << "--------------------------" << endl;

			vector<Item> harvestInventory = farm->getHarvestInventory();
			if(harvestInventory.empty())
			{
				cout << "No items available..." << endl;
				Sleep(500);
			}
			else 
			{
				string itemName;
				int quantity;
				bool valid = false;
				for (Item item : harvestInventory)
				{
					item.displayDetails("harvest");
				}

				while (!valid) 
				{
					cout << "Item to sell:" << endl;
					getline(cin, itemName);
					for (Item item : harvestInventory)
					{
						if (item.getName() == itemName)
						{
							valid = true;
							break;
						}
					}
				}
			
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

		void checkNotifications()
		{
			bool finish = false;
			string option;
			notifications->display();
			while (!finish) 
			{
				cout << endl << "Press 'f' when done reading..." << endl;
				getline(cin,option);
				if (option == "F" || option == "f") 
				{
					finish = true;
				}
			}
		}

		void accept(Visitor& visitor) 
		{
			visitor.visit(*this);
		}

		int getPenny() 
		{
			return penny;
		}

		GroupADT& getNotifications() 
		{
			return *notifications;
		}

		
};