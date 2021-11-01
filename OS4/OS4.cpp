#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int matrixSize = 1000;

int A[matrixSize][matrixSize];
int B[matrixSize][matrixSize];
int C[matrixSize][matrixSize];

mutex mut;

void multVV(int i, int j, int s) {
	C[i][j] = 0;
	for (int k = 0; k < s; k++) {
		C[i][j] += A[i][k] * B[k][j];
	}
	//mut.lock();
	cout << "Thread ID: " << this_thread::get_id() << endl;
	cout << "C[" << i << ", " << j << "] = " << C[i][j] << endl;
	cout << endl;
	//mut.unlock();
}

void createMatrix(int r, int c, int M[][matrixSize]) {
	srand(time(NULL));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			M[i][j] = rand() % 200;
		}
	}
}

int main() {
	int rowsA = 0;
	int colsArowsB = 0;
	cout << "Enter number of rows for matrix A" << endl;
	cin >> rowsA;
	cout << "Enter number of columns for matrix A" << endl;
	cin >> colsArowsB;
	createMatrix(rowsA, colsArowsB, A);
    int colsB = 0;
	cout << "Enter number of columns for matrix B" << endl;
	cin >> colsB;
	cout << "0 - auto generation/ 1 - by hand"<<endl;
	bool choice;
	cin >> choice;
	if (choice == 0) {
		createMatrix(colsArowsB, colsB, B);
	}
	else {
		for (int i = 0; i < rowsA; i++) {
			for (int j = 0; j < colsArowsB; j++) {
				cout << "Enter A[" << i << ", " << j <<"]"<< endl;
				cin>>A[i][j];
			}
		}
		for (int i = 0; i < colsArowsB; i++) {
			for (int j = 0; j < colsB; j++) {
				cout << "Enter B[" << i << ", " << j << "]" << endl;
				cin >> B[i][j];
			}
		}
	}

	//createMatrix(colsArowsB, colsB, B);
	cout << endl;

	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsArowsB; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < colsArowsB; i++) {
		for (int j = 0; j < colsB; j++) {
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	thread * th = new thread[rowsA * colsB];
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsB; j++) {
			th[j+colsB*i] = thread(multVV, i, j, colsArowsB);
		}
		
	}

	for (int i = 0; i < rowsA*colsB; i++) {
			th[i].join();	
	}
	
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsB; j++) {
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
}