#include <iostream>
#define SIZE 1000

template <class Item>
class Fila {
 private:
  int front, rear, tamV;
  Item *v;
  void resize();
  bool isFull() {return (rear+1)%tamV == front;};
 public:
  Fila(int size = SIZE) {front = rear = -1; v = new Item[size]; tamV = size;};
  ~Fila() {if (v != nullptr) delete [] v;};
  bool isEmpty() {return front == -1;};
  void enqueue(Item x);
  Item dequeue();
  Item peek();
};

template <class Item>
void Fila<Item>::resize() {
  Item *tempV = new Item[2*tamV];
  int i = 0, j = front;
  do {
	tempV[i] = v[j];
	j = (j+1)%tamV;
  } while (j != front);
  front = 0;
  rear = tamV-1;
  v = tempV;
}

template <class Item>
void Fila<Item>::enqueue(Item x) {
  if (isFull()) resize();
  else if (isEmpty()) front++;
  rear = (rear+1)%tamV;
  v[rear] = x;
}

template <class Item>
Item Fila<Item>::dequeue() {
  if (isEmpty()) {
	std::cout << "Sem elemento\n";
	return Item();
  }
  Item temp = v[front];
  front == rear ? front = rear = -1 : front = (front+1)%tamV;
  return temp;
}

template <class Item>
Item Fila<Item>::peek() {
  if (isEmpty()) {
	std::cout << "Sem elemento\n";
	return Item();
  }
  return v[front];
}
