/*
   Manoj Adhikari
   project 6, c++

   This is a header file that contains private datas and public functions. This implementation uses a circular doubly linked list
   */
struct node{
			struct node *next;
			struct node *prev;
			int data;
		};
class  Deque{
		int count;
		class node *dummy;
		//Methods
		public:
		Deque();
		~Deque();
		int size();
		void addFirst(int x);
		void addLast(int x);
		int removeFirst();
		int removeLast();
		int getFirst();
		int getLast();
};

