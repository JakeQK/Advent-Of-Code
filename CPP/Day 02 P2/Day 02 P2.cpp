#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct Set
{
public:
	int blue_cubes = 0;
	int red_cubes = 0;
	int green_cubes = 0;
};

struct Game
{
public:
	Game(int id) {
		ID = id;
		sets = vector<Set>();
	}

	int ID;
	vector<Set> sets;

};

enum seek_mode
{
	beginning,
	current
};

class StringReader
{
public:
	StringReader(string& _str)
	{
		m_str = _str;
	}

	string readChars(size_t count)
	{
		string result = m_str.substr(m_currentOffset, count);
		m_currentOffset += count;
		return result;
	}

	void seek(size_t offset, seek_mode mode)
	{
		switch (mode)
		{
		case beginning:
			m_currentOffset = offset;
			break;
		case current:
			m_currentOffset += offset;
			break;
		}
	}

	size_t find(string _str, size_t offset = 0)
	{
		return m_str.find(_str, offset);
	}

	size_t getCurrentOffset() {
		return m_currentOffset;
	}

	bool end_of_stream() {
		if (m_currentOffset >= m_str.length())
		{
			return true;
		}
		return false;
	}

private:
	string m_str;
	size_t m_currentOffset = 0;
};

enum parser_mode {
	cube_count
};

Game gameParser(string line)
{
	Game game(0);

	StringReader reader(line);
	reader.seek(5, beginning);
	game.ID = stoi(reader.readChars(reader.find(":") - 5));

	reader.seek(2, current);

	parser_mode mode = cube_count;

	Set tmpSet;

	while (!reader.end_of_stream())
	{
		size_t offset = reader.find(" ", reader.getCurrentOffset());
		int count = stoi(reader.readChars(offset - reader.getCurrentOffset()));
		reader.seek(1, current);

		switch (reader.readChars(1).c_str()[0])
		{
		case 'b':
			tmpSet.blue_cubes = count;
			reader.seek(3, current);
			break;
		case 'g':
			tmpSet.green_cubes = count;
			reader.seek(4, current);
			break;
		case 'r':
			tmpSet.red_cubes = count;
			reader.seek(2, current);
			break;
		}

		string token = reader.readChars(1);
		if (token == ";" || token == "")
		{
			game.sets.push_back(tmpSet);

			if (reader.end_of_stream())
			{
				break;
			}

			tmpSet = Set();
		}

		reader.seek(1, current);
	}

	return game;
}

int main()
{
	char filepath[FILENAME_MAX];
	GetCurrentDirectoryA(FILENAME_MAX, filepath);
	strcat_s(filepath, "\\input.txt");

	ifstream ifs(filepath);

	if (!ifs.is_open())
	{
		cout << "failed to load input.txt" << endl;
		return 0;
	}

	string line;
	vector<Game> games;
	int sum = 0;

	while (getline(ifs, line))
	{
		games.push_back(gameParser(line));
	}

	for (auto& game : games)
	{
		int min_red = 0;
		int min_green = 0;
		int min_blue = 0;

		for (auto& set : game.sets)
		{
			if (set.red_cubes > min_red)
			{
				min_red = set.red_cubes;
			}

			if (set.green_cubes > min_green)
			{
				min_green = set.green_cubes;
			}

			if (set.blue_cubes > min_blue)
			{
				min_blue = set.blue_cubes;
			}
		}

		sum += (min_red * min_green * min_blue);
	}

	cout << sum << endl;
}