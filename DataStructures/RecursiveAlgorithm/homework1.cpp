/*
* @author :  152120171108 Halitcan Turan
* @author :  152120181008 Yasin Binler
* @brief  :  This program determine blobs in a file , calculates number of pixels making up these blobs  and center of mass in coordinates.
* @date   :  23/10/2020
*/

#include<iostream>
#include<fstream>
#include <string> 

using namespace std;

/**
* @brief  :  This function converts the star to the space.
* @param  :  pixel(2D array)
* @param  :	 i , j(coordinates of pixels) 
* @param  :	 row,col(size of 2D array)
*/

void space(char pixel[][60], int i, int j, int ro, int co) {
	if (i < 0 || j < 0 || i >= ro || j >= co || pixel[i][j] != '*')
		return;
	pixel[i][j] = ' ';
	space(pixel, i - 1, j, ro, co);
	space(pixel, i + 1, j, ro, co);
	space(pixel, i, j - 1, ro, co);
	space(pixel, i, j + 1, ro, co);
}
/**
* @brief  :  This function marks the pixels of blobs.
* @param  :  char pixel(2D array)
* @param  :	 int i , j(coordinates of pixels) 
* @param  :	 int row,col(size of 2D array)
*/
void star(char pixel[][60], int i, int j, int ro, int co) {
	if (i < 0 || j < 0 || i >= ro || j >= co || pixel[i][j] != 'x')
		return;
	pixel[i][j] = '*';
	star(pixel, i - 1, j, ro, co);
	star(pixel, i + 1, j, ro, co);
	star(pixel, i, j - 1, ro, co);
	star(pixel, i, j + 1, ro, co);
}
/**
* @brief  :  This function prints the information about blobs.
* @param  :  char pixel(2D array)
* @param  :	 int row,col(size of 2D array)
* @param  :	 int blob
*/
void print(char pixel[][60], int row, int col, int blob)
{
	double numofpixel = 0, massofrow = 0, massofcol = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (pixel[i][j] == '*') {
				numofpixel++;
				massofrow += i;
				massofcol += j;
			}
		}
	}
	cout << "Blob No : " << blob << "  NumOfPixel :  " << numofpixel << "  COMRow :" << massofrow / numofpixel << "  COMCol :" << massofcol / numofpixel << endl;

}
/**
* @brief  :  This function calculate the numbers  of blobs.
* @param  :	 int row,col(size of 2D array)
*/
void blobcounter(char pixel[][60], int row, int col) {
	int blobno = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (pixel[i][j] == 'x') {
				blobno++;
				star(pixel, i, j, row, col);
				print(pixel, row, col, blobno);
				space(pixel, i, j, row, col);
			}
		}
	}
}


void main()
{
	fstream Inputfile;
	char name_of_file[20];
	string input;

	cout << "Enter the file name :";
	cin.getline(name_of_file, 20);

	Inputfile.open(name_of_file, ios::in);
	int row = 0, col = 0;

	Inputfile >> row;
	Inputfile >> col;

	char pixels[50][60];

	for (int i = -1; i < row; i++)
	{
		getline(Inputfile, input);
		for (int j = 0; j < input.length(); j++)
		{
			pixels[i][j] = input[j];
		}
	}


	for (int i = -2; i < row + 2; i++)
	{
		if (i == -2 || i == row + 1)cout << "  ";
		if (i == -1 || i == row)cout << " ";

		for (int j = -2; j < col + 2; j++)
		{
			if ((i == -2 || i == row + 1) && j >= 0 && j <= col - 1)
			{
				if (j < 10)cout << j;
				else cout << j % 10;
			}
			if ((i == -1 || i == row) && j >= -1 && j <= col)
			{
				if (j == -1 || j == col)cout << "+";
				else cout << "-";
			}
			if (i > -1 && i < row)
			{
				if (j == -2 || j == col + 1)
				{
					if (i < 10)cout << i;
					else cout << i % 10;
				}
				else if (j == -1 || j == col) cout << "|";
				else cout << pixels[i][j];
			}
		}
		cout << endl;
	}
	cout << endl << endl;
	blobcounter(pixels, row, col);
	system("pause");
}