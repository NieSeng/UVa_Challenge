using namespace std;
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>


struct Coordinate
{
	int x, y;

	Coordinate(int xval, int yval) : x(xval), y(yval) {}

	//  因為要使用 std::find 所以需要定義 ==
	bool operator==(const Coordinate& pt) const
	{
		return (x == pt.x && y == pt.y);
	}
};

enum class Direction
{
	North = 0,
	East = 1,
	South = 2,
	West =3
};

enum class InputType
{
	SetGridSize,
	PlaceRobot,
	RobotAction
};

class Robot
{
public:
	Robot() :
		islost_(false),
		gridsize_(Coordinate(0, 0)),
		location_(Coordinate(0, 0)),
		facing_(Direction::North)
	{}

	void resetRobot(const Coordinate& grid)
	{
		islost_ = false;
		gridsize_ = Coordinate(grid.x, grid.y);
		location_ = Coordinate(0, 0);
		facing_ = Direction::North;
		falling_memory_.clear();
	}

	void placeRobot(const Coordinate& loc, Direction dir)
	{
		islost_ = false;
		location_= Coordinate(loc.x, loc.y);
		facing_ = dir;
	}

	void exeCommand(string command_line)
	{
		for (char command : command_line)
		{
			if (!islost_)
			{
				switch (command)
				{
				case 'L':
					turnLeft();
					break;

				case 'R':
					turnRight();
					break;

				case 'F':
					tryMoveForward();
					break;
				}
			}
		}
	}

	string getStatus()
	{
		string result;

		result = to_string(location_.x) + " "
			+ to_string(location_.y) + " "
			+ getDirectionChar(facing_);

		if (islost_)
		{
			result += " LOST";
		}
		return result;
	}
private:
	bool islost_;
	Coordinate gridsize_;
	Coordinate location_;
	Direction facing_;
	vector<Coordinate> falling_memory_;

	void turnLeft()
	{
		facing_ = (Direction)(((int)facing_ + 3) % 4);
	}

	void turnRight()
	{
		facing_ = (Direction)(((int)facing_ + 1) % 4);
	}

	void tryMoveForward()
	{
		Coordinate next_loc = Coordinate(0, 0);

		switch (facing_)
		{
		case Direction::North:
			next_loc = Coordinate(location_.x,
				location_.y + 1);
			break;

		case Direction::South:
			next_loc = Coordinate(location_.x,
				location_.y - 1);
			break;

		case Direction::East:
			next_loc = Coordinate(location_.x + 1,
				location_.y);
			break;

		case Direction::West:
			next_loc = Coordinate(location_.x - 1,
				location_.y);
			break;
		}

		if (next_loc.x < 0 || next_loc.x > gridsize_.x ||
			next_loc.y < 0 || next_loc.y > gridsize_.y)
		{
			auto search_memory = find(falling_memory_.begin(),
									  falling_memory_.end(),
									  location_);

			if (search_memory != falling_memory_.end())
			{
				// has falling memory, do nothing
			}
			else
			{
				islost_ = true;
				falling_memory_.push_back(location_);
			}
		}
		else
		{
			location_ = next_loc;
		}
	}

	char getDirectionChar(Direction dir)
	{
		switch (dir)
		{
		case Direction::North:	return 'N';
		case Direction::East:	return 'E';
		case Direction::South:	return 'S';
		case Direction::West:	return 'W';
		default:
			throw invalid_argument("Invalid direction enum");
		}
	}
};

Direction getFaceDirection(char dir)
{
	switch (dir)
	{
	case 'N': return Direction::North;
	case 'E': return Direction::East;
	case 'S': return Direction::South;
	case 'W': return Direction::West;
	default:
		throw invalid_argument("Invalid direction character");
	}
}

InputType determineInputType(string input_line, Coordinate& pt, Direction& facing)
{
	string token;
	vector<string> tokens;
	InputType result;
	istringstream iss(input_line);
	

	while (iss >> token)
	{
		tokens.push_back(token);
	}

	if (tokens.size() == 2)
	{
		pt = Coordinate(stoi(tokens[0]), stoi(tokens[1]));
		result = InputType::SetGridSize;
	}
	else if (tokens.size() == 3)
	{
		pt = Coordinate(stoi(tokens[0]), stoi(tokens[1]));
		facing = getFaceDirection(tokens[2][0]);
		result = InputType::PlaceRobot;
	}
	else
	{
		result = InputType::RobotAction;
	}

	return result;
}

int main()
{
	string input_line;
	string output_line;
	InputType input_type;
	Direction dir;
	Coordinate pt = Coordinate(0, 0);
	Robot robot = Robot();

	//ofstream outfile("debug_output.txt");  // 開啟一個檔案（如果不存在就建立）
	//if (!outfile) {
	//	// 確保檔案開啟成功
	//	cerr << "Failed to open file!" << endl;
	//	return 1;
	//}

	while (getline(cin, input_line))
	{
		// if (input_line == "Q") break;

		input_type = determineInputType(input_line, pt, dir);
		switch (input_type)
		{
		case InputType::SetGridSize:
			robot.resetRobot(pt);
			break;

		case InputType::PlaceRobot:
			robot.placeRobot(pt, dir);
			break;

		case InputType::RobotAction:
			robot.exeCommand(input_line);
			output_line = robot.getStatus();
			cout << output_line << endl;

			//outfile << output_line << endl;
			break;
		}
	}

	// outfile.close();
}