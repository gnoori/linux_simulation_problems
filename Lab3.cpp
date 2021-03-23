/*Guzel Noori
Lab3 - 2/20/2021 */
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <cctype>

#define QUICKSORT 0
#define INSERTIONSORT 1
#define BUBBLESORT 2

int **mat;
int N = 0;
int check  = true;

void prompt();
void *matrix(void *arg);
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
bool sorted(int arr[]);
void *sorting(void *arg);


using namespace std;

void prompt(){
	cout << "Press number 1 for Problem 1" << endl; 
	cout << "Press number 2 for Problem 2" << endl;
	cout << "Press number 3 for Exit" << endl;
}

//check if the input is a number
bool check_number(string str){
	for (int i = 0; i<str.length(); i++){
		if (isdigit(str[i])== false){
			return false;
		}
		else{
			return true;
		}
	}
	return true;
}

//populate zeros and ones
bool zerosones() {
	int zeros = 0;
	int ones = 0;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (mat[i][j] == 0) {
				zeros++;
			}
			else if (mat[i][j] == 1) {
				ones++;
			}
		}
	}
	if (zeros == (N*N) || ones == (N*N)) {
		return true;
	}
	return false;
}

//main program
int main(int argc, char **argv) {
	//creating mutex
	int input = 0;
	int M = 0;
	srand(time(NULL));
	if (argc!=2){
		cout << "You did not pass an argument. (./compiledFile a_number)" << endl;
		exit(EXIT_FAILURE);
	}
	else if (isdigit(*argv[1])== false) {
		cout << "Non-numeric and negative elements are not accepted. (./compiledFile a_number)" << endl;
		exit(EXIT_FAILURE);
	} 
	else {
		N = atoi(argv[1]);
		if(N<3){
			cout << "The element passed should be N>=3" << endl;
            cout << "Pass a new argument element: ";
            int a;
            cin >> a;
            N = a;
		}
    while(check==true){
    cout << "Pass element for N again: ";
    cin >> N;
	prompt();
	cin >> input;
	std::string str = std::to_string(input);
	if (input > 3 || input < 1) {
		cout << "Incorrect input. The program accepts inputs only in range of 1-3" << endl;
		prompt();
		cin >> input;
	}
	else if(check_number(str)==false){
		cout << "Non numeric values are not accepted. The program accepts inputs only in range of 1-3" << endl;
		prompt();
		cin >> input;
	}
	else {
    
    FILE * fileName;

	if ((fileName = fopen("problem_1.bin", "w+")) == NULL) {
		cout << "Program could not open problem_1.bin file" << endl;
		exit(-1);
	}
	else {
		//file for mode write/update (w+)
		fileName = fopen("problem_1.bin", "w+");
	}

	FILE * myFile;
	if (fileName != NULL) {
		myFile = fileName;
	}
	mat = new int*[N];
	for (int j = 0; j < N; j++) {
		mat[j] = new int[N];
	}
	if (input == 1) {
		cout<<"Enter M number of threads "<<endl;
		cin>>M;
		if(M <= 0) {
			cout << "M value should be M > 0. Enter the appropriate number for M" << endl;
			cin >> M;
		}else {
		pthread_t threads[M];
		for (int i = 0; i < M; i++) {
			pthread_create(&threads[i], NULL, matrix, (void *)&i);
		}
		for (int i = 0; i < M; i++) {
			pthread_join(threads[i], NULL);
		}
		
		}
	}
	else if (input == 2) {
		cout<<"Enter M number of threads "<<endl;
		cin>>M;
		if(M <= 0) {
			cout << "M value should be M > 0. Enter the appropriate number for M" << endl;
			cin >> M;
		}else {
		pthread_t threads[M];
		for (int i = 0; i < M; i++) {
			pthread_create(&threads[i], NULL, sorting, (void *)&i);
		}
		for (int i = 0; i < M; i++) {
			pthread_join(threads[i], NULL);
		}
		}
		prompt();
		cin >> input;
	}
	else {
		exit(EXIT_SUCCESS);
	}
	
	fclose(myFile);
    int choice;
    cout << "Would you like to continue?"<<endl;
    cout << "press 1 to continue, press 2 to exit: ";
    cin >>choice;
    if (choice == 2){
        check = false;
        pthread_exit(NULL);
    }else{
        check = true;
    }
}
}
return 0;
}
}


//Probem 1
void *matrix(void *arg) {
	cout << "Matrix below: " << endl;
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	int count_zero = 0;
	int count_one = 0;
	int difference = 0;
	
    bool b = zerosones();

	for (int j = 0; j < N; j++) {
		for (int k = 0; k < N; k++) {
			mat[j][k] = rand() % 2;
			fwrite(&mat, sizeof(int), N*N, fopen("problem_1.bin", "wb"));
		}
	}
	//Parameter wb - open a binary file and write into it
	fclose(fopen("problem_1.bin", "wb"));
	while (b == false) {
		pthread_mutex_lock(&m);
		int c = rand() % N;
		int d = rand() % N;
		for (int i = -1;i <= 1;i++) {
			for (int j = -1;j <= 1;j++) {
				if (((d - j) >= 0) && ((d - j) <= (N - 1))) {
					if (((c - i) >= 0) && ((c - i) <= (N - 1))) {
						if (!(i == 0 && j == 0)) {
							if ((mat[c - i][d - j]) == 0) {
								count_zero++;
							}
							else if ((mat[c - i][d - j]) == 1) {
								count_one++;
							}
						}
					}
				}
			}
		}
		if (count_zero > count_one) {
			mat[c][d] = 0;
		}
		else if (count_one > count_zero) {
			mat[c][d] = 1;
		}
		else {
			if (mat[c][d] == 1) {
				mat[c][d] = 0;
			}
			else {
				mat[c][d] = 1;
			}
		}
		difference++;
		cout << endl;
        //UPDATE
		count_zero = 0;
		count_one = 0;

		for (int n = 0; n < N; n++) {
			for (int c = 0;c < N;c++) {
				printf("%d ", mat[n][c]);
			}
			cout << "\n";
		}
		b = zerosones();
			
		if (difference == 3500) {
			b = true;
		}
		if (b == true) {
			pthread_exit(NULL);
			exit(0);
		}
		fread(&mat, sizeof(int), N*N, fopen("problem_1.bin", "rb"));
		pthread_mutex_unlock(&m);
	}
	fclose(fopen("problem_1.bin", "rb"));
    return 0;
}

/*Sorting functions got them from GeeksForGeeks*/
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

bool sorted(int arr[]) {
		for (int i = 1;i < (N*N);i++) {
			if (arr[i-1] > arr[i]) {
				return false;
			}
		}
		return true;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; 
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pivot = partition(arr, low, high);
		quickSort(arr, low, pivot - 1);
		quickSort(arr, pivot + 1, high);
	}
}

void insertionSort(int arr[], int size)
{
	int key, j;
	for (int i = 1; i < size; i++)
	{
		key = arr[i];
		j = i;
		while (j >= 0 && arr[j-1] > key)
		{
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = key;
	}
}
void bubbleSort(int arr[], int size)
{
	int i, j;
	int temp;
	for (i = 0; i < size - 1; i++){
		for (j = 0; j < size-i-1; j++){
			if (arr[j] > arr[j+1]){
				swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

//Problem 2
void *sorting(void *arg) {
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	int initial_array[N*N];
	FILE* file;
	srand(time(NULL));
	file = fopen("problem_2.txt", "w");
	for (int j = 0; j < (N*N); j++) {	
		initial_array[j] = rand() % 100;
		fprintf(file, "%d ", initial_array[j]);
	}
	fclose(file);
	FILE *file1 = fopen("problem_2.txt", "r");
	int arr1[N*N];
	for (int i = 0;i < (N*N);i++) {
		fscanf(file1, "%d", &arr1[i]);
	}
	fclose(file);
	cout << "Given sequence of numbers"<<endl;
	for (int i = 0; i < (N*N); i++)
	{
		cout << arr1[i] << " ";
	}
    cout << endl;

	while(sorted(arr1)==false) {
		pthread_mutex_lock(&m);
		int c = rand() % (N*N);
		int d = rand() % (N*N);
        int choose_sort = (rand() % 3)+1;
        cout << endl;
        cout << "Randomly Generated (i, j) pair: ";
		cout << "("<< c<< ","<< d << ")"  << endl;
		int size;
		if (c <= d) {
			size = d - c;
		}
		else {
			size = c - d;
		}

		int temp[size];
        int j = 0;
		if (c <= d) {
			for (int i = c;i <=d;i++) {
				temp[j] = arr1[i];
				j++;
			}
		}
		else if (c > d) {
			for (int i = d;i <= c;i++) {
				temp[j] = arr1[i];
				j++;
			}
		}

		if (choose_sort == 0) {
            cout << "Quick sort is being used" <<endl;
			if (c <= d) {
				quickSort(temp, c, d);
			}
			else if (c > d) {
				quickSort(temp, d, c);
			}
		}
		else if (choose_sort == 1) {
            cout << "Insertion sort is being used"<<endl;
			insertionSort(temp, size+1);		
		}
		else if (choose_sort == 2) {
            cout << "Bubble sort is being used"<<endl;
			bubbleSort(temp, size+1);
		}
		FILE *file2 = fopen("problem_2.txt", "w+");
		if (sorted(arr1) == true) {
            cout << "It is already sorted"<<endl;
		
			for (int j = 0; j < (N*N); j++) {
				fprintf(file2, "%d ",arr1[j]);
                cout << initial_array[j] << " " <<endl; 
			}
			fclose(file2);
			pthread_exit(NULL);
		}
		else {
			int q = 0;
			if (c <= d) {
				for (int i = c;i <= d;i++) {
					arr1[i] = temp[q];
					q++;
                    cout << arr1[i] << " ";
				}
                cout << endl;
                cout << "Sorted from xi - xj" << endl;
                for (int s = c; s<=d; s++){
                    cout << arr1[s] << " ";
                }
                cout << endl;
			}
			else if (c > d) {
				for (int i = d;i <= c;i++) {
					arr1[i] = temp[q];
					q++;
                    cout << arr1[i]<< " ";
				}
                cout << "Sorted from xi - xj" << endl;
                for (int s = d; s<=d; s++){
                    cout << arr1[s] << " ";
                }
                cout << endl; 
			}
		}
        FILE *myFile2 = fopen("problem_2.txt", "w");
			for (int j = 0; j <(N*N); j++) {
				fprintf(myFile2, "%d ", arr1[j]);
			}
			fclose(myFile2);
		pthread_mutex_unlock(&m);
	}
	return 0;
}