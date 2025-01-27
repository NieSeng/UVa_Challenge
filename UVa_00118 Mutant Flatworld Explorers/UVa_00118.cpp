using namespace std;
#include<algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>

int SPACE_SIZE_X;
int SPACE_SIZE_Y;


struct Coordinate
{
	int X;
	int Y;
	Coordinate(int x = 0, int y = 0)
	{
		X = x;
		Y = y;
	}

	bool operator==(const Coordinate& pt) const
	{
		return (X == pt.X && Y == pt.Y);
	}
};

enum class InputType
{
	ChessboardSize,
	PlaceRobot,
	RobotAction
};


class Robot
{
	public:
		enum class Direction
		{
			North = 0,
			East = 1,
			South = 2,
			West = 3
		};

		bool IsLost;
		Coordinate Loc;
		Direction Facing;
		vector<Coordinate> LostMemory;

		Robot()
		{
			IsLost = false;
			Loc = Coordinate();
			Facing = Direction::North;
			LostMemory.clear();
		}

		void PlaceRobot(int locX, int locY, char facing)
		{
			IsLost = false;
			Loc = Coordinate(locX, locY);
			Facing = CharToDirection(facing);
		}

		void ExecuteInstruction(string instructions)
		{
			for (char action : instructions)
			{
				ExecuteAction(action);
				if (IsLost)
				{
					break;
				}
			}
			cout << GetRobotStatus() << endl;
		}

	private:
		Direction CharToDirection(char facing)
		{
			Direction direction;
			switch (facing)
			{
			case 'N':
				direction = Direction::North;
				break;
			case 'E':
				direction = Direction::East;
				break;
			case 'S':
				direction = Direction::South;
				break;
			case 'W':
				direction = Direction::West;
				break;
			default:
				throw invalid_argument("Invalid direction");
				break;
			}
			return direction;
		}

		char DirectionToChar(Direction facing)
		{
			char direction;
			switch (facing)
			{
			case Direction::North:
				direction = 'N';
				break;
			case Direction::East:
				direction = 'E';
				break;
			case Direction::South:
				direction = 'S';
				break;
			case Direction::West:
				direction = 'W';
				break;
			default:
				throw invalid_argument("Invalid direction");
				break;
			}
			return direction;
		}

		void ExecuteAction(char action)
		{
			switch (action)
			{
			case 'L':
				TurnLeft();
				break;
			case 'R':
				TurnRight();
				break;
			case 'F':
				DoMoveForwardProcess();
				break;
			default:
				break;
			}
		}

		void TurnLeft()
		{
			Facing = (Direction)(((int)Facing + 3) % 4);
		}

		void TurnRight()
		{
			Facing = (Direction)(((int)Facing + 1) % 4);
		}

		void DoMoveForwardProcess()
		{
			Coordinate forwardLoc = GetForwardLoc();
			if (!HasLostExperience(forwardLoc))
			{
				if (CheckIsLost(forwardLoc))
				{
					IsLost = true;
					LostMemory.push_back(forwardLoc);
				}
				else
				{
					Loc = forwardLoc;
				}
			}
			else
			{
				// do nothing
			}
		}

		Coordinate GetForwardLoc()
		{
			Coordinate forwardLoc = Loc;
			switch (Facing)
			{
				case Robot::Direction::North:
					forwardLoc.Y++;
					break;
				case Robot::Direction::East:
					forwardLoc.X++;
					break;
				case Robot::Direction::South:
					forwardLoc.Y--;
					break;
				case Robot::Direction::West:
					forwardLoc.X--;
					break;
				default:
					break;
			}
			return forwardLoc;
		}

		bool HasLostExperience(Coordinate loc)
		{
			bool hasLostExperience = false;
			for (Coordinate lostLoc : LostMemory)
			{
				if (lostLoc == loc)
				{
					hasLostExperience = true;
					break;
				}
			}
			return hasLostExperience;
		}

		bool CheckIsLost(Coordinate forwardLoc)
		{
			bool isLost;

			isLost = (forwardLoc.X < 0 || forwardLoc.X > SPACE_SIZE_X || forwardLoc.Y < 0 || forwardLoc.Y > SPACE_SIZE_Y);

			return isLost;
		}

		string GetRobotStatus()
		{
			string status;
			status = to_string(Loc.X) + " " + to_string(Loc.Y) + " " + DirectionToChar(Facing);
			if (IsLost)
			{
				status += " LOST";
			}
			return status;
		}
};

static InputType GetInputType(string inputLine)
{
	InputType inputType;
	regex regexChessboardSize("^[0-9]+ [0-9]+$");
	regex regexPlaceRobot("^[0-9]+ [0-9]+ [NESW]$");

	if (regex_match(inputLine, regexChessboardSize))
	{
		inputType = InputType::ChessboardSize;
	}
	else if (regex_match(inputLine, regexPlaceRobot))
	{
		inputType = InputType::PlaceRobot;
	}
	else
	{
		inputType = InputType::RobotAction;
	}

	return inputType;
}

static void ParseChessboardSize(string inputLine)
{
	string strVal;
	vector<string> strValues;


	// 將 readline 轉換為 string stream
	stringstream strStream(inputLine);

	// 以空格為分割讀取資料
	while (getline(strStream, strVal, ' '))
	{
		strValues.push_back(strVal);
	}

	// 讀取 strValues 裡的資料，轉換成 int
	SPACE_SIZE_X = stoi(strValues[0]);
	SPACE_SIZE_Y = stoi(strValues[1]);
}

static void ParsePlaceRobot(string inputLine, int &locX, int &locY, char &facing)
{
	string strVal;
	vector<string> strValues;
	vector<char> charValues;

	// 將 readline 轉換為 string stream
	stringstream strStream(inputLine);

	// 以空格為分割讀取資料
	while (getline(strStream, strVal, ' '))
	{
		strValues.push_back(strVal);
	}

	// 讀取 strValues 裡的資料
	locX = stoi(strValues[0]);
	locY = stoi(strValues[1]);

	// 將 strValues 裡的 [2] 資料，轉換成 char
	charValues.assign(strValues[2].begin(), strValues[2].end());
	facing = charValues[0];
}

int main() 
{	
	int locX, locY;
	char facing;
	string inputLine;
	InputType inputType;

	// Default value of robot
	Robot robot;

	while (getline(cin, inputLine))
	{
		inputType = GetInputType(inputLine);
		switch (inputType)
		{
			case InputType::ChessboardSize:
				ParseChessboardSize(inputLine);
				robot = Robot();
				break;

			case InputType::PlaceRobot:
				ParsePlaceRobot(inputLine, locX, locY, facing);
				robot.PlaceRobot(locX, locY, facing);
				break;

			case InputType::RobotAction:
				robot.ExecuteInstruction(inputLine);
				break;
		}
	}
}