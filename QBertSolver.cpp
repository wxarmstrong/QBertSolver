#include <iostream> 
#include <fstream>
#include <unordered_map> 
#include <string>
#include <algorithm>
#include <initializer_list>
using namespace std;

ofstream outfile;

unordered_map<long long, unsigned char> umap;

unsigned char compute(string board, unsigned char pos);
void findPaths(string board, unsigned char pos, unsigned char turnsLeft, string curPath);

int main() {

	std::cout << "max_size = " << umap.max_size() << std::endl;
	std::cout << "max_bucket_count = " << umap.max_bucket_count() << std::endl;
	std::cout << "max_load_factor = " << umap.max_load_factor() << std::endl;

	outfile.open("paths.txt");
	string initBoard = "333333333322222223322222233322222333322223333322233333322333333323333333333333333";
	cout << initBoard << endl;
	int minTurns = int(compute(initBoard, 10));
	cout << minTurns << endl;
	findPaths(initBoard, 10, minTurns, "");
	outfile.close();
}

long long getLong(string boardString, unsigned char pos) {

	long long result = 0;
	result = (boardString[64] - '0');

	result = 4 * result + (int)(boardString[56] - '0');
	result = 4 * result + (int)(boardString[55] - '0');

	result = 4 * result + (int)(boardString[48] - '0');
	result = 4 * result + (int)(boardString[47] - '0');
	result = 4 * result + (int)(boardString[46] - '0');

	result = 4 * result + (int)(boardString[40] - '0');
	result = 4 * result + (int)(boardString[39] - '0');
	result = 4 * result + (int)(boardString[38] - '0');
	result = 4 * result + (int)(boardString[37] - '0');

	result = 4 * result + (int)(boardString[32] - '0');
	result = 4 * result + (int)(boardString[31] - '0');
	result = 4 * result + (int)(boardString[30] - '0');
	result = 4 * result + (int)(boardString[29] - '0');
	result = 4 * result + (int)(boardString[28] - '0');

	result = 4 * result + (int)(boardString[24] - '0');
	result = 4 * result + (int)(boardString[23] - '0');
	result = 4 * result + (int)(boardString[22] - '0');
	result = 4 * result + (int)(boardString[21] - '0');
	result = 4 * result + (int)(boardString[20] - '0');
	result = 4 * result + (int)(boardString[19] - '0');

	result = 4 * result + (int)(boardString[16] - '0');
	result = 4 * result + (int)(boardString[15] - '0');
	result = 4 * result + (int)(boardString[14] - '0');
	result = 4 * result + (int)(boardString[13] - '0');
	result = 4 * result + (int)(boardString[12] - '0');
	result = 4 * result + (int)(boardString[11] - '0');
	result = 4 * result + (int)(boardString[10] - '0');

	result = result << 8;
	result += pos;

	return result;
}

unsigned char compute(string board, unsigned char pos)
{
	long long compactBoard = getLong(board, pos);
	unordered_map<long long, unsigned char>::const_iterator got = umap.find(compactBoard);
	if (got != umap.end())
		return (got->second == -1 ? UCHAR_MAX : got->second);
	
	umap[compactBoard] = -1;
	if (compactBoard == pos)
	{
		umap[compactBoard] = 0;
		return 0;
	}

	unsigned char upVal = UCHAR_MAX;
	unsigned char downVal = UCHAR_MAX;
	unsigned char leftVal = UCHAR_MAX;
	unsigned char rightVal = UCHAR_MAX;

	if (board[pos - 9] != '3') {
		unsigned char newPos = pos - 9;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		upVal = compute(newBoard, newPos);
	}
	if (board[pos + 9] != '3') {
		unsigned char newPos = pos + 9;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		downVal = compute(newBoard, newPos);
	}
	if (board[pos - 1] != '3') {
		unsigned char newPos = pos - 1;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		leftVal = compute(newBoard, newPos);
	}
	if (board[pos + 1] != '3') {
		unsigned char newPos = pos + 1;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		rightVal = compute(newBoard, newPos);
	}

	unsigned char minimum = min({ upVal, downVal, leftVal, rightVal });

	umap[compactBoard] = (minimum == UCHAR_MAX ? UCHAR_MAX : minimum + 1);

	return (minimum == UCHAR_MAX ? UCHAR_MAX : minimum + 1);

}

void findPaths(string board, unsigned char pos, unsigned char turnsLeft, string curPath){
	long long compactBoard = getLong(board, pos);

	if (turnsLeft==0)
	{
		outfile << curPath << endl;
		return;
	}

	if (board[pos - 9] != '3') {
		unsigned char newPos = pos - 9;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		long long newCompact = getLong(newBoard, newPos);
		if (umap[newCompact] == turnsLeft - 1)
		{
			string newPath = curPath + "U";
			findPaths(newBoard, newPos, turnsLeft - 1, newPath);
		}
	}
	if (board[pos + 9] != '3') {
		unsigned char newPos = pos + 9;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		long long newCompact = getLong(newBoard, newPos);
		if (umap[newCompact] == turnsLeft - 1)
		{
			string newPath = curPath + "D";
			findPaths(newBoard, newPos, turnsLeft - 1, newPath);
		}
	}
	if (board[pos - 1] != '3') {
		unsigned char newPos = pos - 1;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		long long newCompact = getLong(newBoard, newPos);
		if (umap[newCompact] == turnsLeft - 1)
		{
			string newPath = curPath + "L";
			findPaths(newBoard, newPos, turnsLeft - 1, newPath);
		}
	}
	if (board[pos + 1] != '3') {
		unsigned char newPos = pos + 1;
		string newBoard = board;
		if (newBoard[newPos] != '0') newBoard[newPos]--;
		long long newCompact = getLong(newBoard, newPos);
		if (umap[newCompact] == turnsLeft - 1)
		{
			string newPath = curPath + "R";
			findPaths(newBoard, newPos, turnsLeft - 1, newPath);
		}
	}
}