class numList {
public:
	numList ();
	numList (double n1, double n2);
	numList (double n1, double n2, double n3, double n4);
	numList (double n1, double n2, double n3, double n4, double n5, double n6);

	double nums [6];
};

numList::numList () {
}

numList::numList (double n1, double n2) {
	nums [0] = n1; nums [1] = n2;
}

numList::numList (double n1, double n2, double n3, double n4) {
	nums [0] = n1; nums [1] = n2;
	nums [2] = n3; nums [3] = n4;
}

numList::numList (double n1, double n2, double n3, 
				  double n4, double n5, double n6) {
	nums [0] = n1; nums [1] = n2;
	nums [2] = n3; nums [3] = n4;
	nums [4] = n5; nums [5] = n6;
}
