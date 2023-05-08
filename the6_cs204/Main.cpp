#include <iostream>
#include <string>

#include "container.h"

using namespace std;


int main()
{
  Container *containers[3];
  containers[0] = new LinkedList();
  containers[1] = new Stack();
  containers[2] = new Queue();

  int selection = -1;
  int operation = -1;
  int num ;
  while(selection != 3){
    cin >> selection;
    if(selection != 3) {
      cin >> operation;
      if(operation == 0){
	cin >> num;
	containers[selection]->insertElement(num);
      }
      else if(operation == 1) {
	cin >> num;
	containers[selection]->deleteElement(num);
	
      }
      else if(operation == 2)
	containers[selection]->print();
    }
  }

  for(int i = 0; i < 3; i++)
  delete containers[i];

  cout << "Exiting.." << endl;
  return 0;

}
