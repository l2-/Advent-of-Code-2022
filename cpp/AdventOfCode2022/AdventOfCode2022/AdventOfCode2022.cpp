// AdventOfCode2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "precomp.h"

bool problem1()
{
	string contents = TextFileRead("problem1input.txt");
	auto vec = StringSplit(contents, "\n");
	vector<int> bagSizes;
	int currentBagSize = 0;
	for (auto& s : vec)
	{
		if (s == "")
		{
			bagSizes.push_back(currentBagSize);
			currentBagSize = 0;
			continue;
		}
		currentBagSize += stoi(s);
	}
	if (currentBagSize > 0) bagSizes.push_back(currentBagSize);
	std::sort(bagSizes.begin(), bagSizes.end());
	printf("Part ONE: Biggest bag is %d\n", bagSizes[bagSizes.size() - 1]);
	int bag1 = bagSizes[bagSizes.size() - 1];
	int bag2 = bagSizes[bagSizes.size() - 2];
	int bag3 = bagSizes[bagSizes.size() - 3];
	printf("Part TWO: Biggest 3 bags are %d %d %d for a sum of %d\n", bag1, bag2, bag3, bag1 + bag2 + bag3);
	return true;
}
bool problem2()
{
	const int a_dimension = 3;
	const int x_dimension = 3;
	int valueMapping[a_dimension * x_dimension]; // 2d array

	{
		// Could make generate these mappings as well but cba.
		valueMapping[('A' - 'A') + ('X' - 'X') * a_dimension] = 1 + 3;
		valueMapping[('A' - 'A') + ('Y' - 'X') * a_dimension] = 2 + 6;
		valueMapping[('A' - 'A') + ('Z' - 'X') * a_dimension] = 3 + 0;
		valueMapping[('B' - 'A') + ('X' - 'X') * a_dimension] = 1 + 0;
		valueMapping[('B' - 'A') + ('Y' - 'X') * a_dimension] = 2 + 3;
		valueMapping[('B' - 'A') + ('Z' - 'X') * a_dimension] = 3 + 6;
		valueMapping[('C' - 'A') + ('X' - 'X') * a_dimension] = 1 + 6;
		valueMapping[('C' - 'A') + ('Y' - 'X') * a_dimension] = 2 + 0;
		valueMapping[('C' - 'A') + ('Z' - 'X') * a_dimension] = 3 + 3;

		string contents = TextFileRead("problem2input.txt");
		auto vec = StringSplit(contents, "\n");
		int score = 0;
		for (auto& s : vec)
		{
			if (s != "" && s.size() == 3)
			{
				char opponent = s[0];
				char me = s[2];
				int index = (opponent - 'A') + (me - 'X') * a_dimension;
				score += valueMapping[index];
			}
		}
		printf("Part ONE: expected outcome %d\n", score);
	}

	{
		valueMapping[('A' - 'A') + ('X' - 'X') * a_dimension] = 3 + 0;
		valueMapping[('A' - 'A') + ('Y' - 'X') * a_dimension] = 1 + 3;
		valueMapping[('A' - 'A') + ('Z' - 'X') * a_dimension] = 2 + 6;
		valueMapping[('B' - 'A') + ('X' - 'X') * a_dimension] = 1 + 0;
		valueMapping[('B' - 'A') + ('Y' - 'X') * a_dimension] = 2 + 3;
		valueMapping[('B' - 'A') + ('Z' - 'X') * a_dimension] = 3 + 6;
		valueMapping[('C' - 'A') + ('X' - 'X') * a_dimension] = 2 + 0;
		valueMapping[('C' - 'A') + ('Y' - 'X') * a_dimension] = 3 + 3;
		valueMapping[('C' - 'A') + ('Z' - 'X') * a_dimension] = 1 + 6;

		string contents = TextFileRead("problem2input.txt");
		auto vec = StringSplit(contents, "\n");
		int score = 0;
		for (auto& s : vec)
		{
			if (s != "" && s.size() == 3)
			{
				char opponent = s[0];
				char me = s[2];
				int index = (opponent - 'A') + (me - 'X') * a_dimension;
				score += valueMapping[index];
			}
		}
		printf("Part TWO: expected outcome %d\n", score);
	}

	return true;
}
bool problem3()
{
	string contents = TextFileRead("problem3input.txt");
	auto vec = StringSplit(contents, "\n");
	int sum = 0;
	const int numberOfChars = 256; //unnecessary large but still very small
	int occurrences[numberOfChars];
	{
		for (auto& s : vec)
		{
			if (s == "") continue;
			fill(occurrences, occurrences + numberOfChars, 0);
			{
				int i = 0;
				for (; i < s.size() / 2; i++)
				{
					occurrences[s[i]] = min(occurrences[s[i]] + 1, 1);
				}
				for (; i < s.size(); i++)
				{
					if (occurrences[s[i]])
					{
						occurrences[s[i]] = min(occurrences[s[i]] + 1, 2);
					}
				}
			}
			for (int i = 0; i < numberOfChars; i++)
			{
				if (occurrences[i] == 2)
				{
					if (i > 'Z')
					{
						sum += i - 'a' + 1;
					}
					else if (i >= 'A')
					{
						sum += i - 'A' + 27;
					}
				}
			}
		}
		printf("Part ONE: Sum is %d\n", sum);
	}
	sum = 0;
	{
		for (int k = 0; k < vec.size() - 3; k += 3)
		{
			string& s1 = vec[k];
			string& s2 = vec[k + 1];
			string& s3 = vec[k + 2];
			if (s1 == "" || s2 == "" || s3 == "") continue;

			fill(occurrences, occurrences + numberOfChars, 0);
			{
				for (int l = 0; l < 3; l++)
				{
					string& s = vec[k + l];

					for (int i = 0; i < s.size(); i++)
					{
						if (occurrences[s[i]] == l)
						{
							occurrences[s[i]] = min(occurrences[s[i]] + 1, 1 + l);
						}
					}
				}
			}
			for (int i = 0; i < numberOfChars; i++)
			{
				if (occurrences[i] == 3)
				{
					if (i > 'Z')
					{
						sum += i - 'a' + 1;
					}
					else if (i >= 'A')
					{
						sum += i - 'A' + 27;
					}
				}
			}
		}
		printf("Part TWO: Sum is %d\n", sum);
	}
	return true;
}
bool problem4()
{
	string contents = TextFileRead("problem4input.txt");
	auto vec = StringSplit(contents, "\n");
	int overlapping = 0;
	{
		for (auto& s : vec)
		{
			auto lr = StringSplit(s, ",");
			if (lr.size() == 2)
			{
				auto fl0 = StringSplit(lr[0], "-");
				int a = stoi(fl0[0]);
				int b = stoi(fl0[1]);
				auto fl1 = StringSplit(lr[1], "-");
				int c = stoi(fl1[0]);
				int d = stoi(fl1[1]);
				if ((a >= c && b <= d) || (c >= a && d <= b))
				{
					overlapping++;
				}
			}
		}
		printf("Part ONE: %d overlapping.\n", overlapping);
	}
	overlapping = 0;
	{
		for (auto& s : vec)
		{
			auto lr = StringSplit(s, ",");
			if (lr.size() == 2)
			{
				auto fl0 = StringSplit(lr[0], "-");
				int a = stoi(fl0[0]);
				int b = stoi(fl0[1]);
				auto fl1 = StringSplit(lr[1], "-");
				int c = stoi(fl1[0]);
				int d = stoi(fl1[1]);
				if (a <= d && b >= c)
				{
					overlapping++;
				}
			}
		}
		printf("Part TWO: %d overlapping.\n", overlapping);
	}
	return true;
}
void problem5()
{
	string contents = TextFileRead("problem5input.txt");
	auto vec = StringSplit(contents, "\n");
	int nrOfStacks = vec[0].size() / 4 + 1;
	vector<vector<string>> _stacks(nrOfStacks, vector<string>());
	int _line = 0;
	string cratePositionString = " 1";
	for (; _line < vec.size(); _line++)
	{
		int res = strncmp(vec[_line].c_str(), cratePositionString.c_str(), cratePositionString.size());
		if (!res) break;
		for (int j = 0; j < vec[_line].size(); j += 4)
		{
			string substr = vec[_line].substr(j, 4);
			if (strncmp(substr.c_str(), " ", 1))
			{
				_stacks[j / 4].push_back(substr.substr(1, 1));
			}
		}
	}
	for (auto& v : _stacks)
	{
		reverse(v.begin(), v.end());
	}

	{
		int line = _line;
		vector<vector<string>> stacks = _stacks;
		for (; line < vec.size(); line++)
		{
			string& sline = vec[line];
			{
				if (sline == "") continue;
			}
			{
				int res = strncmp(sline.c_str(), " ", 1);
				if (!res) continue;
			}
			{
				int res = strncmp(sline.c_str(), "\n", 1);
				if (!res) continue;
			}
			auto words = StringSplit(sline, " ");
			int amount = stoi(words[1]);
			int source = stoi(words[3]) - 1;
			int dest = stoi(words[5]) - 1;

			for (int i = 0; i < amount; i++)
			{
				string s = stacks[source].back();
				stacks[source].pop_back();
				stacks[dest].push_back(s);
			}
		}
		printf("Part ONE: Top elements are ");
		for (auto& v : stacks)
		{
			printf("%s", v.back().c_str());
		}
		printf("\n");
	}
	{
		int line = _line;
		vector<vector<string>> stacks = _stacks;
		for (; line < vec.size(); line++)
		{
			string& sline = vec[line];
			{
				if (sline == "") continue;
			}
			{
				int res = strncmp(sline.c_str(), " ", 1);
				if (!res) continue;
			}
			{
				int res = strncmp(sline.c_str(), "\n", 1);
				if (!res) continue;
			}
			auto words = StringSplit(sline, " ");
			int amount = stoi(words[1]);
			int source = stoi(words[3]) - 1;
			int dest = stoi(words[5]) - 1;

			stacks[dest].insert(stacks[dest].end(), stacks[source].end() - amount, stacks[source].end());
			stacks[source].erase(stacks[source].end() - amount, stacks[source].end());
		}
		printf("Part TWO: Top elements are ");
		for (auto& v : stacks)
		{
			printf("%s", v.back().c_str());
		}
		printf("\n");
	}
}
void problem6(int windowSize = 14)
{
	vector<string> vec = StringSplit(TextFileRead("problem6input.txt"), "\n");
	for (auto& s : vec)
	{
		if (s.size() < windowSize) continue;
		int occurrences['z' - 'a' + 1];
		fill(occurrences, occurrences + 'z' - 'a' + 1, -1);
		int i = 0;
		int nextOutOfScope = 0;
		for (i = 0; i < windowSize; i++)
		{
			char c = s[i];
			if (occurrences[c - 'a'] > 0) nextOutOfScope = occurrences[c - 'a'];
			occurrences[c - 'a'] = i;
		}
		for (; i < s.size(); i++)
		{
			char oldc = s[i - windowSize];
			char c = s[i];
			if (occurrences[c - 'a'] <= i - windowSize)
			{
				if (nextOutOfScope + windowSize <= i)
				{
					printf("Window size %d: start after %d\n", windowSize, i + 1);
					break;
				}
			}
			else
			{
				nextOutOfScope = max(occurrences[c - 'a'], nextOutOfScope);
			}
			occurrences[c - 'a'] = i;
		}
	}
}
void problem7()
{
	vector<string> vec = StringSplit(TextFileRead("problem7input.txt"), "\n");
	unordered_map<string, int> fileSizes;
	string currentDir = "/";

	auto get_parent = [](string path)
	{
		int offset = 1;
		if (path.back() == '/')
		{
			// ignore the last character in the string
			offset = 2;
		}
		size_t pos = path.find_last_of('/', path.size() - offset);
		if (pos != string::npos)
		{
			return path.substr(0, pos) + "/";
		}
		return path;
	};

	// first pass
	for (int i = 0; i < vec.size(); i++)
	{
		auto& s = vec[i];
		auto splits = StringSplit(s, " ");
		if (splits.size() < 1) continue;
		if (splits[0] == "$" && splits[1] == "cd")
		{
			if (splits[2] == "..")
			{
				if (currentDir != "/")
				{
					currentDir = get_parent(currentDir);
				}
			}
			else if (splits[2] == "/")
			{
				currentDir = "/";
			}
			else
			{
				currentDir += splits[2] + "/";
			}
		}
		else if (splits[0] != "$" && splits[0] != "dir") // <size file>
		{
			string path = currentDir + splits[1];
			fileSizes[path] += stoi(splits[0]);
		}
	}

	// second pass. sum file sizes to their directories
	unordered_map<string, int> dirSizes;
	for (auto& kvp : fileSizes)
	{
		string parent = get_parent(kvp.first);
		while (1)
		{
			dirSizes[parent] += kvp.second;
			string _parent = get_parent(parent);
			if (parent == _parent) break;
			parent = _parent;
		}
	}
	int sum = 0;
	for (auto& kvp : dirSizes)
	{
		printf("dir %s size %d\n", kvp.first.c_str(), kvp.second);
		if (kvp.second < 100000) sum += kvp.second;
	}
	printf("Part ONE: sum %d\n", sum);
	int unused = 70000000 - dirSizes["/"];
	int needed = 30000000;
	int minDirSize = 1e9;
	for (auto& kvp : dirSizes)
	{
		if (unused + kvp.second > needed)
		{
			minDirSize = min(minDirSize, kvp.second);
		}
	}
	printf("Part TWO: dir size %d\n", minDirSize);
}
void problem8()
{
	vector<string> vec = StringSplit(TextFileRead("problem8input.txt"), "\n");
	const int width = vec[0].size();
	const int height = vec.size();
	vector<int> trees(width * height, 0);
	for (int y = 0; y < vec.size(); y++)
	{
		for (int x = 0; x < vec[y].size(); x++)
		{
			char digit = vec[y][x];
			trees[x + y * width] = digit - '0';
		}
	}
	// part 1
	{
		const int yoffset = 1;
		const int xoffset = 1;

		const int left = 0;
		const int right = width - 1;
		const int top = 0;
		const int bottom = height - 1;
		const int leftInner = left + xoffset;
		const int rightInner = right - xoffset;
		const int topInner = top + yoffset;
		const int bottomInner = bottom - yoffset;
		// very sparse so keep as map
		// set will also work but map is near same cost and good for easily looking up indices for debugging
		unordered_map<int, pair<int, int>> visibleIndices;
		{
			// Compares tree at index against given highest and adds to indices if greater. Also sets new highest
			auto visibleIndexDelegate = [width, trees](int x, int y, int& highest, unordered_map<int, pair<int, int>>& visibleIndices)
			{
				int index = x + y * width;
				int innerTree = trees[index];
				if (innerTree > highest)
				{
					visibleIndices.insert({ index, make_pair(x, y) });
					highest = innerTree;
				}
			};

			// top to bottom
			for (int y = topInner; y <= bottomInner; y++)
			{
				// left to right
				{
					int highestX = trees[left + y * width];
					for (int x = leftInner; x <= rightInner; x++)
					{
						visibleIndexDelegate(x, y, highestX, visibleIndices);
					}
				}
				// right to left
				{
					int highestX = trees[right + y * width];
					for (int x = rightInner; x >= leftInner; x--)
					{
						visibleIndexDelegate(x, y, highestX, visibleIndices);
					}
				}
			}

			for (int x = leftInner; x <= rightInner; x++)
			{
				// top to bottom
				{
					int highestY = trees[x + top * width];
					for (int y = topInner; y <= bottomInner; y++)
					{
						visibleIndexDelegate(x, y, highestY, visibleIndices);
					}
				}
				// bottom to top
				{
					int highestY = trees[x + bottom * width];
					for (int y = bottomInner; y >= topInner; y--)
					{
						visibleIndexDelegate(x, y, highestY, visibleIndices);
					}
				}
			}
		}
		int sumVisible = (width * 2 + (height - 2) * 2) + visibleIndices.size();
		printf("Sumvisible %d\n", sumVisible); //21 and 1829
	}
	// part 2
	{
		// part 2 could be done in the same pass as part 1 but this does not change time complexity
		const int yoffset = 1;
		const int xoffset = 1;

		const int left = 0;
		const int right = width - 1;
		const int top = 0;
		const int bottom = height - 1;
		const int leftInner = left + xoffset;
		const int rightInner = right - xoffset;
		const int topInner = top + yoffset;
		const int bottomInner = bottom - yoffset;

		struct Tree
		{
			int x = 0;
			int y = 0;
			int sum = 1;
		};

		const int nod = 10; //number of digits
		// Used to store visibility sums per tree. Could maybe be optimised away but this would only help with memory footprint.
		vector<Tree> treeSums(width * height);
		int maxTreeSum = 0;
		{
			auto treeSumDelegate = [width, trees, nod, &maxTreeSum](int x, int y, int* previousHeights, int outerBoundary, vector<Tree>& treeSums, int variant)
			{
				int index = x + y * width;
				int innerTree = trees[index];
				int sum = abs(variant - outerBoundary); // no blocking tree
				// find the index of the next highest tree
				for (int highest = innerTree; highest < nod; highest++)
				{
					int previous = previousHeights[highest];
					if (previous >= 0)
					{
						sum = min(sum, abs(variant - previous));
					}
				}
				treeSums[index].x = x;
				treeSums[index].y = y;
				treeSums[index].sum *= sum;
				previousHeights[innerTree] = variant;
				maxTreeSum = max(maxTreeSum, treeSums[index].sum);
			};

			// top to bottom
			for (int y = topInner; y <= bottomInner; y++)
			{
				// left to right
				{
					// store indices of last seen height
					int previousHeights[nod] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
					const int outerBoundary = left;
					for (int x = leftInner; x <= rightInner; x++)
					{
						treeSumDelegate(x, y, previousHeights, outerBoundary, treeSums, x);
					}
				}

				// right to left
				{
					// store indices of last seen height
					int previousHeights[nod] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
					const int outerBoundary = right;
					for (int x = rightInner; x >= leftInner; x--)
					{
						treeSumDelegate(x, y, previousHeights, outerBoundary, treeSums, x);
					}
				}
			}

			for (int x = xoffset; x <= width - xoffset - 1; x++)
			{
				// top to bottom
				{
					// store indices of last seen height
					int previousHeights[nod] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
					const int outerBoundary = top;
					for (int y = topInner; y <= bottomInner; y++)
					{
						treeSumDelegate(x, y, previousHeights, outerBoundary, treeSums, y);
					}
				}

				// bottom to top
				{
					// store indices of last seen height
					int previousHeights[nod] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
					const int outerBoundary = bottom;
					for (int y = bottomInner; y >= topInner; y--)
					{
						treeSumDelegate(x, y, previousHeights, outerBoundary, treeSums, y);
					}
				}
			}
		}

		// Biggest tree sum 8
		// Biggest tree sum 291840
		printf("Biggest tree sum %d\n", maxTreeSum);
	}
}
void problem9()
{
	vector<string> vec = StringSplit(TextFileRead("problem9input.txt"), "\n");
	{
		set<pair<int, int>> points;
		pair<int, int> head = { 0, 0 };
		pair<int, int> tail = { 0, 0 };
		points.insert(tail);
		for (auto& s : vec)
		{
			auto split = StringSplit(s, " ");
			int steps = stoi(split[1]);
			int x = head.first;
			int y = head.second;
			int deltaX = 0;
			int deltaY = 0;
			if (split[0] == "R")
			{
				deltaX = 1;
			}
			else if (split[0] == "L")
			{
				deltaX = -1;
			}
			else if (split[0] == "U")
			{
				deltaY = 1;
			}
			else if (split[0] == "D")
			{
				deltaY = -1;
			}
			//printf("%s\n", split[0].c_str());

			for (int i = 0; i < steps; i++)
			{
				head = { x + deltaX * (i + 1), y + deltaY * (i + 1) };
				int _difx = head.first - tail.first;
				int _dify = head.second - tail.second;
				int difx = sgn(_difx) * 1;
				int dify = sgn(_dify) * 1;
				int tailx = tail.first + difx;
				int taily = tail.second + dify;
				if (make_pair(tailx, taily) == head) continue;
				tail = { tail.first + difx, tail.second + dify };
				points.insert(tail);
				//printf("%d %d\n", tail.first, tail.second);
			}
		}
		printf("unique visits %d\n", (int)points.size());
	}
	{
		set<pair<int, int>> points;
		pair<int, int> head = { 0, 0 };
		vector<pair<int, int>>tails(9, make_pair(0, 0));
		points.insert(tails[8]);
		for (auto& s : vec)
		{
			auto split = StringSplit(s, " ");
			int steps = stoi(split[1]);
			int x = head.first;
			int y = head.second;
			int deltaX = 0;
			int deltaY = 0;
			if (split[0] == "R")
			{
				deltaX = 1;
			}
			else if (split[0] == "L")
			{
				deltaX = -1;
			}
			else if (split[0] == "U")
			{
				deltaY = 1;
			}
			else if (split[0] == "D")
			{
				deltaY = -1;
			}
			//printf("%s\n", split[0].c_str());

			for (int i = 0; i < steps; i++)
			{
				head = { x + deltaX * (i + 1), y + deltaY * (i + 1) };
				for (int j = 0; j < tails.size(); j++)
				{
					auto& tail = tails[j];
					pair<int, int> _head = head;
					if (j > 0)
					{
						_head = tails[j - 1];
					}
					int _difx = _head.first - tail.first;
					int _dify = _head.second - tail.second;
					int difx = sgn(_difx) * 1;
					int dify = sgn(_dify) * 1;
					int tailx = tail.first + difx;
					int taily = tail.second + dify;
					if (make_pair(tailx, taily) == _head) continue;
					tail = { tail.first + difx, tail.second + dify };
					if (j == tails.size() - 1)
					{
						points.insert(tail);
						//printf("Knot %d %d %d\n", j, tail.first, tail.second);
					}
				}
			}
		}
		printf("unique visits longtail %d\n", (int)points.size());
	}
}
void problem10()
{
	vector<string> vec = StringSplit(TextFileRead("problem10input.txt"), "\n");
	{
		int registerX = 1;
		int sum = 0;
		const int cycleRegistration = 40;
		int cycle = 0;
		int nextXDelta = 0;
		bool isSet = false;
		const int width = cycleRegistration;
		const int height = 6;
		vector<bool> pixels(width * 6, false);

		auto doCycle = [&]()
		{
			if ((cycle + 20) % cycleRegistration == 0 || cycle == 20)
			{
				sum += cycle * registerX;
			}

			int pixel = (cycle - 1) % cycleRegistration;
			int row = (cycle - 1) / cycleRegistration;
			if (registerX >= pixel - 1 && registerX <= pixel + 1)
			{
				int pixelI = pixel + row * width;
				if (pixelI < pixels.size())
				{
					pixels[pixelI] = true;
				}
			}
		};

		cycle++;

		for (int i = 0; i < vec.size(); i++)
		{
			doCycle();

			auto& s = vec[i];
			if (s != "noop")
			{
				auto split = StringSplit(s, " ");
				nextXDelta = stoi(split[1]);
				isSet = true;
			}
			cycle++;

			if (isSet)
			{
				//printf("cycle %d X %d sum %d\n", cycle, registerX, sum);
				isSet = false;

				doCycle();

				registerX += nextXDelta;
				cycle++;
			}
			//printf("cycle %d X %d sum %d\n", cycle, registerX, sum);
		}

		printf("Part ONE: cycle %d X %d sum %d\n", cycle, registerX, sum);

		printf("Part TWO: sceen\n");
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int pixelI = x + y * width;
				bool pixel = pixels[pixelI];
				if (pixel)
				{
					printf("#");
				}
				else
				{
					printf(".");
				}
			}
			printf("\n");
		}
	}
}
void problem11()
{
	vector<string> vec = StringSplit(TextFileRead("problem11input.txt"), "\n");

	struct Op
	{
		long long var1 = -999;
		long long var2 = -999;
		int op = 0;
	};

	struct Monkey
	{
		int id = 0;
		vector<long long> starting_items;
		Op op_new = Op();
		long long divisble_by = 1;
		int target1 = 0;
		int target2 = 0;
		long long inspected_count = 0;
	};

	vector<Monkey> _monkeys;
	for (int i = 0; i < vec.size(); i++)
	{
		if (StartsWith(vec[i], "Monkey"))
		{
			Monkey _m;
			auto _split = StringSplit(vec[i], " ");
			_m.id = stoi(_split[1]);
			_monkeys.push_back(_m);
			Monkey& m = _monkeys[_monkeys.size() - 1];
			for (int j = 1; j < 6; j++)
			{
				auto& s = vec[i + j];
				if (StartsWith(s, "  Starting"))
				{
					auto split1 = StringSplit(s, " ");
					for (auto& s_split : split1)
					{
						auto split2 = StringSplit(s_split, ",");
						for (auto& ss : split2)
						{
							if (ss != "" && !StartsWith(ss, "Starting") && !StartsWith(ss, "item"))
							{
								m.starting_items.push_back(stoi(ss));
							}
						}
					}
				}
				if (StartsWith(s, "  Operation"))
				{
					auto split1 = StringSplit(s, " ");
					if (split1.size() != 8)
					{
						printf("holup\n");
					}
					Op op;
					if (split1[5] != "old")
					{
						op.var1 = stoi(split1[5]);
					}
					if (split1[7] != "old")
					{
						op.var2 = stoi(split1[7]);
					}
					if (split1[6] == "+")
					{
						op.op = 0;
					}
					if (split1[6] == "-")
					{
						op.op = 1;
					}
					if (split1[6] == "*")
					{
						op.op = 2;
					}
					if (split1[6] == "/")
					{
						op.op = 3;
					}
					m.op_new = op;
				}
				if (StartsWith(s, "  Test"))
				{
					auto split1 = StringSplit(s, " ");
					m.divisble_by = stoi(split1[5]);
				}
				if (StartsWith(s, "    If true"))
				{
					auto split1 = StringSplit(s, " ");
					m.target1 = stoi(split1[9]);
					if (m.target1 == _m.id)
					{
						printf("holdup1\n");
					}
				}
				if (StartsWith(s, "    If false"))
				{
					auto split1 = StringSplit(s, " ");
					m.target2 = stoi(split1[9]);
					if (m.target2 == _m.id)
					{
						printf("holdup1\n");
					}
				}
			}
		}
	}

	int lcm = 1;
	for (auto& m : _monkeys)
	{
		lcm *= m.divisble_by;
	}

	{
		auto monkeys = _monkeys;
		for (int round = 1; round <= 20; round++)
		{
			for (int m_id = 0; m_id < monkeys.size(); m_id++)
			{
				Monkey& m = monkeys[m_id];
				auto& items = m.starting_items;
				for (auto& item : items)
				{
					long long worry_level = item;
					Op op = m.op_new;
					if (op.var1 == -999) op.var1 = worry_level;
					if (op.var2 == -999) op.var2 = worry_level;
					long long new_w_l = 0LL;
					switch (op.op)
					{
					case 0:
						new_w_l = op.var1 + op.var2;
						break;
					case 2:
						new_w_l = op.var1 * op.var2;
						break;
					}
					new_w_l /= 3;
					if (new_w_l % m.divisble_by == 0LL) {
						//printf("%d to %d\n", m_id, m.target1);
						monkeys[m.target1].starting_items.push_back(new_w_l);
					}
					else {
						monkeys[m.target2].starting_items.push_back(new_w_l);
						//printf("%d to %d\n", m_id, m.target2);
					}
					m.inspected_count++;
				}
				m.starting_items.clear();
			}
		}

		vector<long long> inspected_counts;
		for (auto& m : monkeys)
		{
			inspected_counts.push_back(m.inspected_count);
		}
		sort(inspected_counts.begin(), inspected_counts.end(), std::greater<>());
		printf("part 1: sum %lld\n", inspected_counts[0] * inspected_counts[1]);
	}

	{
		auto monkeys = _monkeys;
		for (int round = 1; round <= 1e4; round++)
		{
			for (int m_id = 0; m_id < monkeys.size(); m_id++)
			{
				Monkey& m = monkeys[m_id];
				auto& items = m.starting_items;
				for (auto& item : items)
				{
					long long worry_level = item;
					worry_level %= lcm;
					Op op = m.op_new;
					if (op.var1 == -999) op.var1 = worry_level;
					if (op.var2 == -999) op.var2 = worry_level;
					long long new_w_l = 0LL;
					switch (op.op)
					{
					case 0:
						new_w_l = op.var1 + op.var2;
						break;
					case 2:
						new_w_l = op.var1 * op.var2;
						break;
					}
					if (new_w_l % m.divisble_by == 0LL) {
						//printf("%d to %d\n", m_id, m.target1);
						monkeys[m.target1].starting_items.push_back(new_w_l);
					}
					else {
						monkeys[m.target2].starting_items.push_back(new_w_l);
						//printf("%d to %d\n", m_id, m.target2);
					}
					m.inspected_count++;
				}
				m.starting_items.clear();
			}
		}

		vector<long long> inspected_counts;
		for (auto& m : monkeys)
		{
			inspected_counts.push_back(m.inspected_count);
		}
		sort(inspected_counts.begin(), inspected_counts.end(), std::greater<>());
		printf("part 2: sum %lld\n", inspected_counts[0] * inspected_counts[1]);
	}
}
void problem12()
{
	vector<string> vec = StringSplit(TextFileRead("problem12input.txt"), "\n");
	const int width = vec[0].size();
	const int height = vec.size();
	vector<int> grid(width * height, -1);
	pair<int, int> start;
	pair<int, int> end;
	for (int y = 0; y < height; y++)
	{
		string& s = vec[y];
		for (int x = 0; x < s.size(); x++)
		{
			int index = x + y * width;
			char& c = s[x];
			if (c == 'S')
			{
				start = make_pair(x, y);
				grid[index] = 0;
			}
			else if (c == 'E')
			{
				end = make_pair(x, y);
				grid[index] = 'z' - 'a';
			}
			else
			{
				grid[index] = s[x] - 'a';
			}
		}
	}

	auto check_neighbour = [width, height, grid](pair<int, pair<int, int>> p, int x_offset, int y_offset, deque<pair<int, pair<int, int>>>& q) {
		int x = p.second.first + x_offset;
		int y = p.second.second + y_offset;
		if (x < 0 || x >= width) return;
		if (y < 0 || y >= height) return;
		int index = x + y * width;
		int elevation_this = grid[p.second.first + p.second.second * width];
		int elevation_next = grid[index];
		if (elevation_next >= elevation_this - 1)
		{
			q.push_back({ p.first + 1, make_pair(x, y) });
		}
	};

	auto is_valid_start = [grid, width, height](int x, int y) {
		if (x < 0 || x >= width) return false;
		if (y < 0 || y >= height) return false;
		return grid[x + y * width] == 0;
	};

	vector<int> parts = { 1, 2 };
	for (int part : parts)
	{
		vector<bool> seen(grid.size(), false);
		deque<pair<int, pair<int, int>>> q;
		q.push_back({ 0, end });
		pair<int, int> last = { -1,-1 };
		int round = 0;
		while (!q.empty() && last != start)
		{
			if (is_valid_start(last.first, last.second) && part == 2) break;

			auto p = q.front(); q.pop_front();
			round = p.first;
			last = p.second;
			int index = p.second.first + p.second.second * width;
			if (seen[index]) continue;
			seen[index] = true;
			check_neighbour(p, -1, 0, q);
			check_neighbour(p, 1, 0, q);
			check_neighbour(p, 0, -1, q);
			check_neighbour(p, 0, 1, q);
		}
		printf("part %d: %d steps\n", part, round);
	}
}
void problem13()
{

}
void problem14()
{
	vector<string> vec = StringSplit(TextFileRead("day14.txt"), "\n");
	int max_x = 0;
	int min_x = 999;
	int max_y = 0;
	int min_y = 999;
	vector<pair<pair<int, int>, pair<int, int>>> line_segments;
	for (auto& str : vec) {
		auto ints = StringToInts<int>(str);
		int i = 0;
		pair<int, int> start = { ints[i], ints[i + 1] };
		max_x = max(max_x, ints[i]);
		min_x = min(min_x, ints[i]);
		max_y = max(max_y, ints[i + 1]);
		min_y = min(min_y, ints[i + 1]);
		i += 2;
		for (; i < ints.size(); i += 2) {
			line_segments.push_back({ start, { ints[i], ints[i + 1] } });
			max_x = max(max_x, ints[i]);
			min_x = min(min_x, ints[i]);
			max_y = max(max_y, ints[i + 1]);
			min_y = min(min_y, ints[i + 1]);
			start = { ints[i], ints[i + 1] };
		}
	}
	const int width = (max_x + 1) * 2; //stinky but easy fix for giving sand breathing room
	const int height = max_y + 2;
	vector<char> grid(width * height, '.');

	for (auto& p : line_segments) {
		if (p.first.first != p.second.first && p.first.second != p.second.second) {
			printf("diagonal line %d,%d -> %d,%d\n", p.first.first, p.first.second, p.second.first, p.second.second);
		}

		int x_left = min(p.first.first, p.second.first);
		int x_right = max(p.first.first, p.second.first);
		int y_left = min(p.first.second, p.second.second);
		int y_right = max(p.first.second, p.second.second);
		for (int x = x_left; x <= x_right; x++) {
			grid[x + p.first.second * width] = '#';
		}

		for (int y = y_left; y <= y_right; y++) {
			grid[p.first.first + y * width] = '#';
		}
	}

	// sand comes in until it does not add to the sum of sand anymore (goes into the sink)
	auto is_stable = [&grid, width, height](int x, int y, int part) {
		bool stable_left = false;
		bool stable_right = false;
		bool stable_below = false;

		int index = x + y * width;
		if (grid[index] != '.') return 1;

		if (x <= 0) stable_left = true;
		if (x >= width - 1) stable_right = true;
		if (y >= height - 1) return part < 2 ? 2 : 0;

		if (!stable_below) {
			int below = x + (y + 1) * width;
			stable_below = grid[below] != '.';
			if (!stable_below) return -1;
		}

		if (!stable_left) {
			int left = (x - 1) + y * width;
			int left_below = (x - 1) + (y + 1) * width;
			bool stable_left = grid[left_below] != '.';
			if (!stable_left) return -2;
		}

		if (!stable_right) {
			int right = (x + 1) + y * width;
			int right_below = (x + 1) + (y + 1) * width;
			bool stable_right = grid[right_below] != '.';
			if (!stable_right) return -3;
		}

		return 0;
	};

	vector<int> parts = { 1,2 };
	for (auto& part : parts)
	{
		int sand_x = 500;
		int stable;
		int sand_placed = 0;
		vector<pair<int, int>> sands;
		for (int sand_y = 0; sand_y < height;)
		{
			stable = is_stable(sand_x, sand_y, part);
			//printf("checking %d,%d stable %d\n", sand_x, sand_y, stable);
			if (stable == 1) {
				printf("We filled all the way up %d %d\n", sand_x, sand_y);
				break;
			}
			else if (stable == 0) {
				sand_placed++;
				//printf("sand placed at %d,%d\n", sand_x, sand_y);
				sands.push_back({ sand_x, sand_y });
				grid[sand_x + sand_y * width] = 'o';
				sand_x = 500; sand_y = 0;
			}
			else if (stable == 2) {
				printf("Sink found at %d %d\n", sand_x, sand_y);
				break;
			}
			else {
				if (stable == -1) {
					// move on normally
					sand_y++;
				}
				if (stable == -2) {
					// move to the left
					sand_x--;
					sand_y++;
				}
				if (stable == -3) {
					// move to the right
					sand_x++;
					sand_y++;
				}
			}
		}
		printf("Number of sand placed part %d %d\n", part, sand_placed);

		int min_sand_x = 999;
		int max_sand_x = 0;
		int min_sand_y = 999;
		int max_sand_y = 0;
		for (auto& p : sands) {
			max_sand_x = max(max_sand_x, p.first);
			min_sand_x = min(min_sand_x, p.first);
			max_sand_y = max(max_sand_y, p.second);
			min_sand_y = min(min_sand_y, p.second);
		}
		printf("Sand diagram:\n");
		for (int y = min_sand_y; y < min(max_sand_y + 2, height); y++)
		{
			for (int x = min_sand_x; x < min(max_sand_x + 2, width); x++)
			{
				char c = grid[x + y * width];
				printf("%c", c);
			}
			printf("\n");
		}
	}
}
void problem15()
{
	vector<string> vec = StringSplit(TextFileRead("day15.txt"), "\n");
	int row_to_track = 2000000;

	Timer timer;
	{
		unordered_map<int, set<int>> sensors;
		vector<pair<pair<int, int>, int>> sensor_positions;

		printf("Parsing lines 1 %f\n", timer.elapsed());
		for (auto& s : vec)
		{
			vector<int> ints = StringToInts<int>(s);
			int x1 = ints[0];
			int y1 = ints[1];
			int x2 = ints[2];
			int y2 = ints[3];
			int manhattan_distance = ManhattanDistance(x1, y1, x2, y2);
			sensor_positions.push_back({ {x1, y1}, manhattan_distance });

			sensors[y1].insert(x1); //sensor
			sensors[y2].insert(x2); //beacon
		}

		unordered_map<int, vector<pair<int, int>>> row_coverage_table; // line segments
		for (auto& s : sensor_positions)
		{
			int manhattan_distance = s.second;
			int x1 = s.first.first;
			int y1 = s.first.second;
			for (int y = row_to_track; y < row_to_track + 1; y++) // row
			//for (int y = y1 - manhattan_distance; y < y1 + manhattan_distance + 1; y++) // row necessary for slow
			{
				int start = x1 - manhattan_distance + min(manhattan_distance, abs(y - y1));
				int end = x1 + manhattan_distance - min(manhattan_distance, abs(y - y1));
				if (row_coverage_table.find(y) == row_coverage_table.end()) { row_coverage_table[y].reserve(10); }
				row_coverage_table[y].push_back({ start, end });
			}
		}

		printf("Sorting lines %f\n", timer.elapsed());
		for (auto& kvp : row_coverage_table)
		{
			std::sort(kvp.second.begin(), kvp.second.end());
		}
		printf("Merging lines %f\n", timer.elapsed());
		for (auto& kvp : row_coverage_table)
		{
			vector<pair<int, int>> merged_lines;
			if (kvp.second.size() < 2) continue;
			int last_start = kvp.second[0].first;
			int last_end = kvp.second[0].second;
			for (auto& l : kvp.second)
			{
				if (l.first - 1 > last_end)
				{
					merged_lines.push_back({ last_start, last_end });
					last_start = l.first;
				}
				last_end = max(last_end, l.second);
			}
			merged_lines.push_back({ last_start, last_end });
			kvp.second = merged_lines;
		}

		{
			auto& row = row_coverage_table[row_to_track];
			int sum = 0;
			for (auto& l : row)
			{
				sum += l.second - l.first + 1;
			}
			sum -= sensors[row_to_track].size();
			printf("Part 1: sum %d for row %d %f\n", sum, row_to_track, timer.elapsed());
		}

		// fast
		{
			const long long max_height = 4000000ll;
			const long long max_width = max_height;
			unordered_set<int> acoeffs;
			unordered_set<int> bcoeffs;
			for (auto& s1 : sensor_positions)
			{
				{
					int x = s1.first.first;
					int y = s1.first.second;
					int r = s1.second;
					int a1 = y - x + r + 1;
					int a2 = y - x - r - 1;
					int b1 = y + x + r + 1;
					int b2 = y + x - r - 1;
					acoeffs.insert(a1);
					acoeffs.insert(a2);
					bcoeffs.insert(b1);
					bcoeffs.insert(b2);
				}
			}

			for (auto& a : acoeffs)
			{
				for (auto& b : bcoeffs)
				{
					int x = (b - a) / 2;
					int y = (b + a) / 2;

					bool valid = true;
					for (auto& s : sensor_positions)
					{
						int distance = ManhattanDistance(x, y, s.first.first, s.first.second);
						if (distance <= s.second)
						{
							valid = false;
						}
					}
					if (valid && x >= 0 && y >= 0 && x <= max_width && y <= max_height)
					{
						long long index = x * max_width + (long long)y;
						printf("Part 2: Disconnect at X: %d Y: %d index %lld %f\n", x, y, index, timer.elapsed());
					}
				}
			}
		}

		if (1 == 0) //slow
		{
			printf("Finding disconnect in lines %f\n", timer.elapsed());
			const int max_height = 4000000;
			const int max_width = max_height;
			for (int y = 0; y < max_height; y++)
			{
				if (row_coverage_table.find(y) == row_coverage_table.end()) continue;
				auto& lines = row_coverage_table[y];
				if (lines.size() < 1)
				{
					printf("Y: %d is empty\n", y);
					continue;
				}
				int last_start = lines[0].first;
				int last_end = lines[0].second;
				for (int x_index = 1; x_index < lines.size(); x_index++)
				{
					auto& l = lines[x_index];
					if (l.first > last_end)
					{
						last_start = l.first;
						long long x = last_end + 1;
						bool found = sensors[y].find(x) != sensors[y].end();
						if (x >= 0 && x <= max_width && !found)
						{
							long long index = (x * 4000000ll) + (long long)y;
							printf("Part 2: Disconnect at X: %d Y: %d index %lld %f\n", x, y, index, timer.elapsed());
						}
					}
					last_end = max(last_end, l.second);
				}
			}
		}
	}
}
namespace problem16
{
	// State for problem 16
	struct State16
	{
		int key = 0; // valve
		int cycle = 0; // minute
		int visited = 0; // valves opened
	};

	struct State16Consts
	{
		const State16& start;
		const vector<int>& matrix;
		const vector<int>& non_zero_valves;
		const int key_count;
	};

	long long traverse(const State16& state16, const State16Consts& consts, const int other_players, vector<int64_t>& memoised_table)
	{
		const int opening_cost = 1;
		const int64_t max_cycles = 31; //minutes + 1
		const int64_t max_players = 2;
		if (state16.cycle == 0)
		{
			if (other_players > 0)
			{
				long long pressure = traverse({ consts.start.key, consts.start.cycle, state16.visited },
					{ consts.start, consts.matrix, consts.non_zero_valves, consts.key_count }, other_players - 1, memoised_table);
				return pressure;
			}
			return 0ll;
		}
		int ck = state16.key; // current key
		int visited = state16.visited; // bitmask of non zero opened valves
		int cycle = state16.cycle; // current minute = max - cycle. we count down

		// Index into 4d array with dimensions 
		// x = player count(max 2)
		// y = cycle count(max 30 but 31 is safer)
		// z = key count(max 15 non zero but 59 incl zero is safer)
		// w = visited(max 1 << highest key index. 15 non zero key indices so 1 << 15)
		// size of array = 2^15 * 59 * 31 * 2 = 119,865,344 keys
		// dense data so best use array over map
		int64_t memoisation_key = (int64_t)visited * (int64_t)consts.key_count * max_cycles * max_players
			+ (int64_t)ck * max_cycles * max_players
			+ (int64_t)cycle * max_players
			+ (int64_t)other_players;
		if (memoised_table[memoisation_key] >= 0)
		{
			return memoised_table[memoisation_key];
		}

		int non_zero_key_count = consts.non_zero_valves.size();
		long long max_pressure = 0;

		// For all non-zero-flow unopened valves calculate max pressure
		for (int nzk = 0; nzk < non_zero_key_count; nzk++)
		{
			bool is_visited = (visited & (1 << nzk)) != 0;
			if (!is_visited)
			{
				int travel_cost = consts.matrix[ck + nzk * consts.key_count];
				int open_cycle = cycle - travel_cost - opening_cost;
				if (open_cycle < 0) continue;
				int pressure_open = consts.non_zero_valves[nzk];
				int new_pressure = open_cycle * pressure_open;
				int new_visited = visited | (1 << nzk);
				max_pressure = max(max_pressure, new_pressure + traverse({ nzk, open_cycle, new_visited }, consts, other_players, memoised_table));
			}
		}

		// This is a bit of cheating.
		// When we have multiple players the optimal solution can include us stopping without opening all valves to
		// give the other player something to do early on. To simulate this for each step we simply create a branch
		// where we consider time limit reached and let the next player go.
		// This is only necessary since we do not simulate minute for minute but rather greedily open valves and therefore
		// these extra steps are only necessary when using multiple playes.
		if (other_players > 0)
		{
			max_pressure = max(max_pressure, traverse({ ck, 0, visited }, consts, other_players, memoised_table));
		}
		memoised_table[memoisation_key] = max_pressure;
		return max_pressure;
	}

	void problem16()
	{
		Timer t;
		vector<string> vec = StringSplit(TextFileRead("day16.txt"), "\n");
		unordered_map<string, unordered_map<string, int>> edge_list;
		unordered_map<string, int> _valves;
		for (auto& s : vec)
		{
			vector<string> splits = StringSplit(s, " ");
			string this_v = splits[1].substr(0, 2);
			int this_rate = StringToInts<int>(s)[0];
			_valves[this_v] = this_rate;

			for (int i = 9; i < splits.size(); i++)
			{
				string connected = splits[i].substr(0, 2);
				edge_list[this_v][connected] = 1;
			}
		}

		/*	30-3  + 1 28 20 DD
			30-6  + 1 25 13 DD BB
			30-10 + 1 21 21 DD BB JJ
			30-18 + 1 13 22 DD BB JJ HH
			30-22 + 1 9  3  DD BB JJ HH EE
			30-25 + 1 6  4  DD BB JJ HH EE CC
							 3  4  2  1  0  5

			28*20+25*13+21*21+13*22+9*3+6*2 = 1651	*/

			// setting up distance matrix
		unordered_map<string, int> keys;
		vector<int> non_zero_valves(_valves.size(), 0);
		int key_count = 0;
		int non_zero_key_count = 0;
		for (auto& kvp : _valves)
		{
			if (kvp.second > 0)
			{
				non_zero_valves[key_count] = kvp.second;
				keys[kvp.first] = key_count++;
				non_zero_key_count++;
			}
		}
		non_zero_valves.resize(non_zero_key_count);
		for (auto& kvp : _valves)
		{
			if (kvp.second == 0)
			{
				keys[kvp.first] = key_count++;
			}
		}
		vector<int> matrix(key_count * key_count, 1e9);
		for (auto& kvp : edge_list)
		{
			int x = keys[kvp.first];
			matrix[x + x * key_count] = 0;
			for (auto& dest : kvp.second)
			{
				int y = keys[dest.first];
				matrix[x + y * key_count] = dest.second;
				matrix[y + x * key_count] = dest.second;
			}
		}

		// floyd warshall
		for (int k = 0; k < key_count; k++)
		{
			for (int i = 0; i < key_count; i++)
			{
				for (int j = 0; j < key_count; j++)
				{
					int ij = i + j * key_count;
					int ik = i + k * key_count;
					int kj = k + j * key_count;
					if (matrix[ij] > matrix[ik] + matrix[kj])
					{
						matrix[ij] = matrix[ik] + matrix[kj];
					}
				}
			}
		}

		const int64_t max_cycles = 31; //minutes + 1
		const int64_t max_players = 2;
		vector<long long> memoisation_table((1ll << non_zero_key_count) * key_count * max_cycles * max_players, -1);
		printf("Runtime parsing + reducing:\t %fs\n", t.elapsed());
		t.reset();

		int ck = keys["AA"]; //current key
		long long max_p;

		max_p = traverse({ ck, 30, 0 }, { { ck, 30, 0 }, matrix, non_zero_valves, key_count }, 0, memoisation_table);
		printf("Part 1: Max pressure:\t\t %lld\n", max_p); //1789
		printf("Runtime: p1\t\t\t %fs\n", t.elapsed());
		t.reset();

		max_p = traverse({ ck, 26, 0 }, { { ck, 26, 0 }, matrix, non_zero_valves, key_count }, 1, memoisation_table);
		printf("Part 2: Max pressure:\t\t %lld\n", max_p); // 2496
		printf("Runtime p2:\t\t\t %fs\n", t.elapsed());
	}
}
void problem17()
{
	vector<string> vec = StringSplit(TextFileRead("day17.txt"), "\n");
	vector<bool> moves;
	string& s = vec[0];
	for (auto& c : s)
	{
		moves.push_back(c == '<');
	}

	constexpr u16 mask = 0b111111111;
	vector<u16> column(4, mask);
	constexpr auto bits_to_string = [](const u16 bs)
	{
		string s = ".........";
		for (int x = 0; x < 9; x++)
		{
			char c = '#';
			if (x == 0 || x == 8) c = '|';
			if (bs & (1 << x)) s[9 - 1 - x] = c;
		}
		return s;
	};
	constexpr auto print_column = [](const vector<u16>& column)
	{
		for (int y = column.size() - 1; y >= 4; y--)
		{
			u16 row = column[y];
			string s = bits_to_string(row);
			printf("%s\n", s.c_str());
		}
		printf("+-------+\n");
	};

	constexpr i64 max_depth = 64; // emperically tested to be 32. added a little safety margin
	constexpr i64 rocks = 1000000000000;//2022;
	//constexpr i64 rocks = 100000;//2022;
	printf("%lld rocks\n", rocks);
	constexpr i64 width = 7;
	constexpr i64 start_x = 3;
	constexpr i64 start_y = 4;
	constexpr u64 row_length = 16ll;
	i64 top_index = 0;
	constexpr u64 dash =
			(0b000000000ll) << 48ll
		|	(0b000000000ll) << 32ll
		|	(0b000000000ll) << 16ll
		|	(0b111100000ll) << 00ll;
	constexpr u64 plus =
			(0b000000000ll) << 48ll
		|	(0b010000000ll) << 32ll
		|	(0b111000000ll) << 16ll
		|	(0b010000000ll) << 00ll;
	constexpr u64 corner =
			(0b000000000ll) << 48ll
		|	(0b001000000ll) << 32ll
		|	(0b001000000ll) << 16ll
		|	(0b111000000ll) << 00ll;
	constexpr u64 separator =
			(0b100000000ll) << 48ll
		|	(0b100000000ll) << 32ll
		|	(0b100000000ll) << 16ll
		|	(0b100000000ll) << 00ll;
	constexpr u64 square =
			(0b000000000ll) << 48ll
		|	(0b000000000ll) << 32ll
		|	(0b110000000ll) << 16ll
		|	(0b110000000ll) << 00ll;
	constexpr u64 walls =
			(0b100000001ll) << 48ll
		|	(0b100000001ll) << 32ll
		|	(0b100000001ll) << 16ll
		|	(0b100000001ll) << 00ll;
	constexpr u64 wall = 0b100000001ll;
	vector<u64> shapes = vector<u64>({ dash, plus, corner, separator, square });

	// bottom row = 0
	constexpr auto get_row = [](const u64 shape, const u64 row_index) { return (shape >> (row_index * row_length)) & mask; };
	constexpr auto make_row = [](const u64 row, const u64 row_index) { return row << (row_index * row_length); };
	constexpr auto collides = [](const u64 s1, const u64 s2) { return (s1 & s2) > 0; };
	constexpr auto apply_jet_stream = [](const vector<bool>& moves, const i64 i, u64 s, const u64 walls)
	{
		bool left = moves[i % moves.size()];
		u64 _s;
		if (left) { _s = s << 1; 
		//printf("left\n");
		}
		else { _s = s >> 1; 
		//printf("right\n");
		}
		if ((_s & walls) == 0) { s = _s; }
		return s;
	};
	constexpr auto slide_in_from_top = [](const u64 shape, int i)
	{
		assert(i <= 3);
		// - take bottom row + 0 and put it at top -0

		// * take bottom row + 0 and put it at top -1
		// * take bottom row + 1 and put it at top -0

		// # take bottom row + 0 and put it at top -2
		// # take bottom row + 1 and put it at top -1
		// # take bottom row + 2 and put it at top -0

		// % take bottom row + 0 and put it at top -3
		// % take bottom row + 1 and put it at top -2
		// % take bottom row + 2 and put it at top -1
		// % take bottom row + 3 and put it at top -0

		u64 s = 0;
		for (int j = 0; j <= i; j++)
		{
			int src_row = j;
			int dest_row = 3 - i + j;
			u64 _src_row = get_row(shape, src_row);
			u64 _dst_row = make_row(_src_row, dest_row);
			s |= _dst_row;
		}
		return s;
	};
	constexpr auto calculate_key = [](const i64 shape_index, const i64 jet_index, const i64 depth, const i64 number_of_shapes, const i64 number_of_jets) 
	{
		return jet_index + shape_index * number_of_jets + depth * number_of_shapes * number_of_jets;
	};

	vector<pair<i64, i64>> l1_cache(shapes.size() * moves.size() * max_depth);
	vector<pair<i64, i64>> l2_cache(l1_cache.size());

	Timer t;
	i64 jet_stream = 0;
	i64 max_i = 0;
	for (i64 rock = 0; rock < rocks; rock++)
	{
		//printf("rock %lld\n", rock);
		i64 y = column.size() + start_y;
		u64 shape = shapes[rock % shapes.size()];
		shape = shape >> start_x;

		// aply jet stream until we pass the top of the column
		for (; y > column.size(); y--)
		{
			shape = apply_jet_stream(moves, jet_stream++, shape, walls);
		}

		u64 rows =
				(i64)column[column.size() - 1] << 48ll
			|	(i64)column[column.size() - 2] << 32ll
			|	(i64)column[column.size() - 3] << 16ll
			|	(i64)column[column.size() - 4] << 00ll;

		// Collision with top of column
		bool any_collision = false;
		int offset = 0;
		i64 i = 0;
		while (true)
		{
			for (;; i++)
			{
				// test shape against column
				{
					u64 s = slide_in_from_top(shape, min(i, 3ll));
					bool collision = collides(s, rows);
					for (int j = 3; j >= 0; j--)
					{
						u64 row = get_row(s, j);
						//printf("bts %d %s %s\n", i, bits_to_string(row | wall).c_str(), bits_to_string(get_row(rows, j)).c_str());
					}
					//printf("\n");
					if (collision)
					{	any_collision = true;
						break;
					}
				}

				// aply jet stream
				{
					u64 _shape = apply_jet_stream(moves, jet_stream++, shape, walls);
					u64 s = slide_in_from_top(_shape, min(i, 3ll));
					bool collision = collides(s, rows);
					for (int j = 3; j >= 0; j--)
					{
						u64 row = get_row(s, j);
						//printf("bts %d %s %s\n", i, bits_to_string(row | wall).c_str(), bits_to_string(get_row(rows, j)).c_str());
					}
					//printf("\n");
					if (!collision)
					{
						shape = _shape;
					}
				}

				if (i >= 3) break;
			}

			if (!any_collision)
			{
				offset++;
				if (column.size() - 4 - offset < 0)
				{
					printf("Ran out of rows..\n");
					break;
				}
				rows =
					(i64)column[column.size() - 1 - offset] << 48ll
					| (i64)column[column.size() - 2 - offset] << 32ll
					| (i64)column[column.size() - 3 - offset] << 16ll
					| (i64)column[column.size() - 4 - offset] << 00ll;
			}
			else
			{
				// update column
				for (int j = 0; j < 4; j++)
				{
					i64 index = column.size() - i + j - offset;
					u64 row = get_row(shape, j);
					u16 row_to_insert = row | wall;
					if (row == 0) break;
					if (index < column.size())
					{
						column[index] |= row_to_insert;
					}
					else
					{
						column.push_back(row_to_insert);
						top_index += 1;
					}
				}

				// keep track of max search depth in column to determine max_depth
				if (i + offset > max_i)
				{
					max_i = i + offset;
					printf("Max depth %lld\n", max_i);
				}

				// resize column to stay bounded in size
				if (column.size() >= max_depth)
				{
					auto end = column.end() - 32 - 4;
					auto start = column.begin();
					column.erase(start, end);
					//printf("Resized to %lld\n", column.size());
				}

				const i64 key = calculate_key(rock % shapes.size(), jet_stream % moves.size(), i + offset, shapes.size(), moves.size());
				if (l1_cache[key].first > 0 && l2_cache[key].first == 0)
				{
					l2_cache[key] = { top_index, rock };
					i64 delta_top = top_index - l1_cache[key].first;
					i64 delta_rock = rock - l1_cache[key].second;
					i64 predicted_top = top_index + delta_top;
					i64 predicted_rock = rock + delta_rock;

					//printf("Cycle found for rock %lld height (%lld,%lld) to (%lld,%lld) %lld depth. Prediction size %lld for %lld rocks\n", 
					//	rock, l1_cache[key].first, l1_cache[key].second, l2_cache[key].first, l2_cache[key].second, i + offset, predicted_top, predicted_rock);
					
					i64 multiplier = (rocks - rock) / delta_rock;
					i64 value = multiplier * delta_top;
					rock += multiplier * delta_rock;
					top_index += value;
				}
				else 
				{
					l1_cache[key] = { top_index, rock };
				}
				break;
			}
		}

		// Collision inside column
		if (rock % 1000000000 == 0 && rock)
		{
			double elapsed = t.elapsed();
			double inv_ratio = rocks / (double)rock;
			double expected = (elapsed * inv_ratio) / 3600.0;
			printf("%lld rock elapsed %fs expected %fhrs\n", rock, elapsed, expected);
		}
	}

	//print_column(column);
	printf("Done. Size %lld in %f\n", top_index, t.elapsed());
}
void problem18()
{
	vector<string> vec = StringSplit(TextFileRead("day18.txt"), "\n");
	int3 _min = { 999,999,999 };
	int3 _max = { 0,0,0 };
	for (auto& s : vec)
	{
		auto ints = StringToInts<i32>(s);
		int3 i3 = {ints[0], ints[1], ints[2]};
		_min = min(_min, i3);
		_max = max(_max, i3);
	}
	const i64 width = _max.x + 3;
	const i64 height = _max.y + 3;
	const i64 depth = _max.z + 3;
	i64 x_off = 1;
	i64 y_off = 1;
	i64 z_off = 1;
	vector<bool> grid(width * height * depth, false);
	for (auto& s : vec)
	{
		auto ints = StringToInts<i32>(s);
		i64 x = ints[0] + x_off;
		i64 y = ints[1] + y_off;
		i64 z = ints[2] + z_off;
		i64 index = x + y * width + z * width * height;
		grid[index] = true;
	}

	const auto within_bounds = [width, height, depth](const i64 x, const i64 y, const i64 z) { return x >= 0 && x < width&& y >= 0 && y < height&& z >= 0 && z < depth; };
	const auto to_index = [width, height, depth](const i64 x, const i64 y, const i64 z) { return x + y * width + z * width * height; };
	const vector<int3> translations = vector<int3>({
		{ 1,0,0 }, { -1,0,0 },
		{ 0,1,0 }, { 0,-1,0 },
		{ 0,0,1 }, { 0,0,-1 }
		});
	{
		i64 face_count = 0;
		for (i64 z = z_off; z < depth - z_off; z++)
		{
			for (i64 y = y_off; y < height - y_off; y++)
			{
				for (i64 x = x_off; x < width - x_off; x++)
				{
					i64 index = x + y * width + z * width * height;
					int3 c = make_int3(x, y, z);
					if (grid[index])
					{
						for (auto& _c : translations)
						{
							i64 x = c.x + _c.x, y = c.y + _c.y, z = c.z + _c.z;
							i64 index1 = to_index(x, y, z);
							if (!grid[index1]) face_count++;
						}
					}
				}
			}
		}

		printf("Part 1: Face count %lld\n", face_count);
	}

	{
		i64 face_count = 0;
		vector<bool> visited = grid;
		int3 xyz = make_int3(0);
		deque<int3> bfs;
		bfs.push_back(xyz);
		while (!bfs.empty())
		{
			int3 c = bfs.front();
			bfs.pop_front();
			{
				i64 x = c.x, y = c.y, z = c.z;
				i64 index = x + y * width + z * width * height;
				visited[index] = true;
			}
			
			for (auto& _c : translations)
			{
				i64 x = c.x + _c.x, y = c.y + _c.y, z = c.z + _c.z;
				i64 index1 = to_index(x, y, z);
				if (within_bounds(x, y, z))
				{
					if (grid[index1]) face_count++;
					else if (!visited[index1])
					{
						bfs.push_back(make_int3(x, y, z));
						visited[index1] = true;
					}
				}
			}
		}

		printf("Part 2: Face count %lld\n", face_count);
	}
}
namespace problem19
{
	// The data is too sparse to make efficient use of a custom dense cache. Note that even after reducing the states a lot
	// the range of values for the 9 variables is still to large to be covered entirely by a cache that fits in my RAM.
	// Even after tweaking the values a dictionary still wipes the floor with the cache since its able to cover all cases.
	// number of states
	// empirically determined since the actual max states wouldn't fit in my pc memory nor be actually used in relevant manner
	// 25 mins * 15 ores * 50 clays * 10 obs * 5 orers * 10 clayrs * 5 obsrs * 5 geoders = 234375000 (*4 ~ 1gb)
	//constexpr i64 max_ores = 5;
	//constexpr i64 max_clays = 21;
	//constexpr i64 max_obs = 21;
	//constexpr i64 max_geodes = 5;
	//constexpr i64 max_orers = 5;
	//constexpr i64 max_clayrs = 12;
	//constexpr i64 max_obsrs = 12;
	//constexpr i64 max_geoders = 15;

	constexpr i64 number_of_bots = 4;
	//constexpr i64 time_limit = 24;
	//constexpr i64 max_mat[number_of_bots] = { max_ores, max_clays ,max_obs, max_geodes };
	//constexpr i64 max_bots[number_of_bots] = { max_orers, max_clayrs ,max_obsrs, max_geoders };
	struct State;
	struct Robot
	{
		i64 materials[number_of_bots] = { 0,0,0,0 };

		bool buildable(const State& state) const;
	};
	struct BluePrint
	{
		Robot robots[number_of_bots] = {};
		i64 max_materials[number_of_bots] = {};
	};
	struct State
	{
		// ore, clay, obsidian, geode
		i64 materials[number_of_bots] = { 0,0,0,0 };
		i64 robots[number_of_bots] = { 0,0,0,0 };

		i64 minute = 0;

		void collect()
		{
			for (i64 i = 0; i < number_of_bots; i++) materials[i] += robots[i];
		}
		void build(const Robot& r, i64 i)
		{
			robots[i]++;
			materials[0] -= r.materials[0];
			materials[1] -= r.materials[1];
			materials[2] -= r.materials[2];
		}
		// Compress state space by not considering excess materials
		void cap(const BluePrint& bp, const i64 time_limit)
		{
			for (i64 i = 0; i < number_of_bots; i++)
			{
				robots[i] = min(robots[i], bp.max_materials[i]);
			}

			i64 t = time_limit - minute;
			for (i64 i = 0; i < 3; i++)
			{
				materials[i] = min(materials[i], t * bp.max_materials[i] - robots[i] * (t - 1));
			}
		}
		//bool exceeds(const i64 time_limit) const
		//{
		//	if (minute >= time_limit + 1) return true;
		//	for (i64 i = 0; i < number_of_bots; i++)
		//	{
		//		if (materials[i] >= max_mat[i]) return true;
		//		if (robots[i] >= max_bots[i]) return true;
		//	}
		//	return false;
		//}
		//i64 key() const
		//{
		//	i64 _key = minute * ((max_mat[0] * max_mat[1] * max_mat[2] * max_mat[3]) * (max_bots[0] * max_bots[1] * max_bots[2] * max_bots[3]))
		//		+ materials[0] * ((max_mat[1] * max_mat[2] * max_mat[3]) * (max_bots[0] * max_bots[1] * max_bots[2] * max_bots[3]))
		//		+ materials[1] * ((max_mat[2] * max_mat[3]) * (max_bots[0] * max_bots[1] * max_bots[2] * max_bots[3]))
		//		+ materials[2] * ((max_mat[3]) * (max_bots[0] * max_bots[1] * max_bots[2] * max_bots[3]))
		//		+ materials[3] * ((max_bots[0] * max_bots[1] * max_bots[2] * max_bots[3]))
		//		+ robots[0] * (max_bots[1] * max_bots[2] * max_bots[3])
		//		+ robots[1] * (max_bots[2] * max_bots[3])
		//		+ robots[2] * (max_bots[3])
		//		+ robots[3];
		//	return _key;
		//}
		
		bool operator==(const State& other_state) const
		{
			if (minute != other_state.minute) return false;
			for (i64 i = 0; i < number_of_bots; i++)
			{
				if (materials[i] != other_state.materials[i]) return false;
				if (robots[i] != other_state.robots[i]) return false;
			}
			return true;
		}

		struct HashFunction
		{
			size_t operator()(const State& state) const
			{
				return state.hash();
			}
		};

		i64 hash() const
		{
			return simple_hash({ materials[0], materials[1], materials[2], materials[3],
				robots[0] , robots[1] , robots[2], robots[3], minute });
		}
	};
	bool Robot::buildable(const State& state) const { return state.materials[0] >= materials[0] && state.materials[1] >= materials[1] && state.materials[2] >= materials[2]; }

	i64 traverse_max_geodes(const BluePrint& bp, State state, vector<i8>& cache, unordered_map<State, i8, State::HashFunction>& seen, const i64 time_limit)
	{
		//i64 key = state.key();
		//bool exceeds = state.exceeds();
		if (state.minute + 1 > time_limit)
		{
			return 0;
		}
		state.minute += 1;

		state.cap(bp, time_limit);

		//i64 key = state.key();
		//bool exceeds = state.exceeds(time_limit);

		if (seen.find(state) != seen.end()) return seen[state];
		//if (!exceeds && cache[key] >= 0) return cache[key];
		State next = state; next.collect();

		i64 geodes = next.materials[3];
		bool build_all = true;
		for (i64 i = 0; i < number_of_bots; i++)
		{
			const Robot& bot = bp.robots[i];
			if (next.robots[i] < bp.max_materials[i])
			{
				// is buildable BEFORE collecting
				if (bot.buildable(state))
				{
					State next_cp = next;
					next_cp.build(bot, i);
					geodes = max(geodes, traverse_max_geodes(bp, next_cp, cache, seen, time_limit));
				}
				else
				{
					build_all = false;
				}
			}
		}

		// if we can build all we dont just stand around
		if (!build_all)
		{
			geodes = max(geodes, traverse_max_geodes(bp, next, cache, seen, time_limit));
		}
		
		// Used to keep a cap on the memory thats allowed to be used or it can grow very big.
		// Necessary before we reduced the states
		//if (state.minute < 29) 
		{
			seen[state] = geodes;
		}
		//if (!exceeds) cache[key] = geodes;
		return geodes;
	}

	void problem19()
	{
		vector<BluePrint> bps;
		{
			vector<string> vec = StringSplit(TextFileRead("day19.txt"), "\n");
			for (auto& s : vec)
			{
				auto ints = StringToInts<i64>(s);
				BluePrint bp;
				bp.robots[0] = { ints[1], 0,		0,		0 };
				bp.robots[1] = { ints[2], 0,		0,		0 };
				bp.robots[2] = { ints[3], ints[4],	0,		0 };
				bp.robots[3] = { ints[5], 0,		ints[6],0 };
				for (i64 i = 0; i < number_of_bots; i++)
				{
					i64 max_mat = 0;
					for (i64 j = 0; j < number_of_bots; j++)
					{
						max_mat = max(max_mat, bp.robots[j].materials[i]);
					}
					bp.max_materials[i] = max(max_mat, bp.max_materials[i]);
				}
				bp.max_materials[number_of_bots - 1] = 999;

				bps.push_back(bp);
			}
		}

		State start_state;
		start_state.robots[0] = 1;
		vector<pair<pair<i32, i32>, i32>> parts = vector<pair<pair<i32, i32>, i32>>({
			{{ 1, 24 }, bps.size()},
			{{ 2, 32 }, 3}
			});
		Timer t;
		for (auto& pt : parts)
		{
			i64 index = 1;
			i64 sum = 0;
			i64 time_limit = pt.first.second;
			for (auto i = 0; i < pt.second; i++)
			{
				auto& bp = bps[i];
				//vector<i8> cache((time_limit + 1) * max_ores * max_clays * max_obs * max_orers * max_clayrs * max_obsrs * max_geoders * max_geodes, -1);
				vector<i8> cache;
				unordered_map<State, i8, State::HashFunction> seen;
				i64 geodes = traverse_max_geodes(bp, start_state, cache, seen, time_limit);
				printf("%lld geodes at %lld %fs\n", geodes, index, t.elapsed());
				if (pt.first.first == 1) 
				{
					sum += index * geodes;
				}
				else
				{
					if (!sum) sum = 1;
					sum *= geodes;
				}
				index++;
			}
			printf("Part %d Sum %lld\n", pt.first.first, sum);
		}
	}
}
void problem20()
{
	vector<i64> numbers;
	{
		vector<string> vec = StringSplit(TextFileRead("day20.txt"), "\n");
		for (auto& s : vec)
		{
			i64 i = StringToInts<i64>(s)[0];
			numbers.push_back(i);
		}
	}

	struct pair_hash
	{
		std::size_t operator() (const std::pair<i64, i64>& pair) const {
			return simple_hash({ pair.first, pair.second });
		}
	};

	constexpr auto print_vector1 = [](const vector<pair<i64, i64>> v) { for (auto& p : v) printf("%lld, ", p.first); printf("\n"); };
	constexpr auto find_first_non_seen = [](const vector<pair<i64, i64>>& v, const unordered_set<pair<i64, i64>, pair_hash>& seen)
	{
		if (v.size() == seen.size()) return -1ll;
		i64 value = v.size();
		i64 min_index = 0;
		for (i64 i = 0; i < v.size(); i++)
		{
			auto& p = v[i];
			if (seen.find(p) == seen.end())
			{
				if (p.second < value)
				{
					value = p.second;
					min_index = i;
				}
			}
		}
		return min_index;
	};

	Timer t;
	vector<i64> intervals = vector<i64>({ 1000, 2000, 3000 });
	{
		// Fast solution. Works by shuffling the indices rather than the numbers
		t.reset();
		vector<i64> indices(numbers.size(), -1);
		for (i64 i = 0; i < indices.size(); i++) indices[i] = i;
		for (i64 i = 0; i < indices.size(); i++)
		{
			i64 offset = numbers[i];
			i64 index = find(indices.begin(), indices.end(), i) - indices.begin();
			i64 new_index = nmod<i64>(offset + index, numbers.size() - 1);
			indices.erase(indices.begin() + index);
			indices.insert(indices.begin() + new_index, i);
			//move(indices, index, new_index); // move -> set is identical to erase -> insert
			//indices[new_index] = i;
		}

		i64 _0_index = find(numbers.begin(), numbers.end(), 0) - numbers.begin();
		i64 offset = find(indices.begin(), indices.end(), _0_index) - indices.begin();
		i64 sum = 0;
		for (auto& i : intervals)
		{
			i64 index = nmod<i64>(i + offset, numbers.size());
			sum += numbers[indices[index]];
			printf("%lld %lld\n", index, numbers[indices[index]]);
		}
		printf("Part 1: %lld %fs\n", sum, t.elapsed()); // 7584
	}
	{
		// Slow solution. Uses std::rotate to rotate the elements around
		t.reset();
		vector<pair<i64, i64>> _numbers;
		for (i64 i = 0; i < numbers.size(); i++) _numbers.push_back({ numbers[i], i });

		unordered_set<pair<i64, i64>, pair_hash> seen;
		i64 index = find_first_non_seen(_numbers, seen);
		while (index != -1)
		{
			auto& p = _numbers[index];
			seen.insert(p);
			i64 i = p.first;
			i64 new_index = index + i;
			// retarded shit

			new_index = nmod<i64>(new_index, _numbers.size() - 1);
			move(_numbers, index, new_index);

			index = find_first_non_seen(_numbers, seen);
		}

		i64 offset = 0;
		for (auto& p : _numbers) { if (p.first == 0) break; else offset++; }
		i64 sum = 0;
		for (auto& i : intervals)
		{
			i64 index = nmod<i64>(i + offset, _numbers.size());
			sum += _numbers[index].first;
			printf("%lld %lld\n", index, _numbers[index].first);
		}
		printf("Part 1: %lld %fs\n", sum, t.elapsed()); // 7584
	}
	{
		// fast
		t.reset();
		i64 key = 811589153;
		i64 rounds = 10;
		vector<i64> _numbers = numbers;
		for (auto& p : _numbers) p *= key;
		vector<i64>& numbers = _numbers;
		vector<i64> indices(numbers.size(), 0);
		for (i64 i = 0; i < numbers.size(); i++) indices[i] = i;
		for (i64 j = 0; j < rounds; j++)
		{
			printf("Round %lld\n", j);
			for (i64 i = 0; i < indices.size(); i++)
			{
				i64 offset = numbers[i];
				i64 index = find(indices.begin(), indices.end(), i) - indices.begin();
				i64 new_index = nmod<i64>(offset + index, numbers.size() - 1);
				indices.erase(indices.begin() + index);
				indices.insert(indices.begin() + new_index, i);
			}
		}
		i64 _0_index = find(numbers.begin(), numbers.end(), 0) - numbers.begin();
		i64 offset = find(indices.begin(), indices.end(), _0_index) - indices.begin();
		i64 sum = 0;
		for (auto& i : intervals)
		{
			i64 index = nmod<i64>(i + offset, numbers.size());
			sum += numbers[indices[index]];
			printf("%lld %lld\n", index, numbers[indices[index]]);
		}
		printf("Part 2: %lld %fs\n", sum, t.elapsed()); // 7584
	}
	{
		// slow
		t.reset();
		vector<pair<i64, i64>> _numbers;
		i64 key = 811589153;
		i64 rounds = 10;
		for (i64 i = 0; i < numbers.size(); i++) _numbers.push_back({ numbers[i] * key, i });
		for (i64 j = 0; j < rounds; j++)
		{
			printf("Round %lld\n", j);
			unordered_set<pair<i64, i64>, pair_hash> seen;
			i64 index = find_first_non_seen(_numbers, seen);
			while (index != -1)
			{
				auto& p = _numbers[index];
				seen.insert(p);
				i64 i = p.first;
				i64 new_index = index + i;
				// retarded shit

				new_index = nmod<i64>(new_index, _numbers.size() - 1);
				move(_numbers, index, new_index);

				index = find_first_non_seen(_numbers, seen);
			}
			//print_vector1(_numbers);
		}
		i64 offset = 0;
		for (auto& p : _numbers) { if (p.first == 0) break; else offset++; }
		i64 sum = 0;
		for (auto& i : intervals)
		{
			i64 index = nmod<i64>(i + offset, _numbers.size());
			sum += _numbers[index].first;
			printf("%lld %lld\n", index, _numbers[index].first);
		}
		printf("Part 2: %lld %fs\n", sum, t.elapsed());
	}

}
namespace problem21
{
	using namespace cnl;
	typedef i64 customreturntype;
	//typedef double customreturntype;
	//typedef fraction<i64, i64> customreturntype;
	customreturntype resolve(const unordered_map<string, string>& decls, string expression, string& full_expr)
	{
		vector<string> splits = StringSplit(expression, " ");
		vector<i64> ints = StringToInts<i64>(expression);
		if (ints.size() == 1)
		{
			i64 result = 0;
			string_to<i64>(splits[0], result);
			return (customreturntype)result;
			//return make_fraction(result);
		}
		else if (splits.size() == 1)
		{
			auto p = *decls.find(splits[0]);
			if (p.first != "humn")
			{
				string replacement = "(" + p.second + ")";
				ReplaceAllInPlace(full_expr, expression, replacement);
			}
			return resolve(decls, p.second, full_expr);
		}

		customreturntype term1 = resolve(decls, splits[0], full_expr);
		//if (term1.denominator > 1 && term1.numerator % term1.denominator == 0) term1 = make_fraction(term1.numerator / term1.denominator);
		//if (term1.denominator > (1 << 24)) term1 = make_fraction(term1.numerator / term1.denominator);
		customreturntype term2 = resolve(decls, splits[2], full_expr);
		//if (term2.denominator > 1 && term2.numerator % term2.denominator == 0) term2 = make_fraction(term2.numerator / term2.denominator);
		//if (term2.denominator > (1 << 24)) term2 = make_fraction(term2.numerator / term2.denominator);

		customreturntype answer = -1;
		//customreturntype answer = make_fraction(-1);
		switch (splits[1][0])
		{
		case '+':
			answer = term1 + term2;
			break;
		case '-':
			answer = term1 - term2;
			break;
		case '*':
			answer = term1 * term2;
			break;
		case '/':
			answer = term1 / term2;
			break;
		};
		return answer;
	}

	void problem21()
	{
		unordered_map<string, string> decls;
		{
			vector<string> vec = StringSplit(TextFileRead("day21.txt"), "\n");
			for (auto& s : vec)
			{
				vector<string> splits = StringSplit(s, " ");
				string key = splits[0].substr(0, splits[0].size() - 1);
				string value = "";
				for (i64 i = 1; i < splits.size() - 1; i++)
				{
					value += splits[i] + " ";
				}
				value += splits[splits.size() - 1];
				decls[key] = value;
			}
		}
		{
			string root = decls["root"];
			string __ = "";
			customreturntype answer = resolve(decls, root, __);
			printf("Part 1: Answer %lld\n", answer);
		}
		{
			auto splits = StringSplit(decls["root"] , " ");
			decls["root"] = splits[0] + " - " + splits[2];
			string root = decls["root"];
			if (splits[1][0] != '+') printf("Found operator %s but only + is supported\n", splits[1].c_str());
			bool _ = false;
			string expression = root;
			customreturntype ans = resolve(decls, root, expression);

			expression = root;
			customreturntype f0 = resolve(decls, splits[2], expression);

			//decls["humn"] = "3375719472770"; //answer
			//expression = root;
			//customreturntype f1 = resolve(decls, splits[0], expression);

			//decls["humn"] = "3375719472770"; //answer
			//expression = root;
			//customreturntype f001 = resolve(decls, root, expression);

			//decls["humn"] = "0";
			//expression = root;
			//customreturntype f00 = resolve(decls, root, expression);

			//i64 t = 5ll << 39;
			//decls["humn"] = to_string(t);
			//expression = root;
			//customreturntype f01 = resolve(decls, root, expression);

			// sadly the following doesnt work.
			// I spent hours trying to figure out a fix for what i think is due to shitty integer division or floating point precision loss
			// but Im not sure that is even it
			// fx(x) = Ax - b => Ax = b
			// fx(x) = x = b/A
			// fx(x) = A(x - 4) - b => Ax - 4A = b
			// (A(0) - 4A - b) - (A(1) - 4A - b) = -A
			// A(0) - 4A - b = -4A - b => fx(0) = -cA - b
			// fx(0) = A(0) - b = -b
			// fx(1) = A(1) - b = A - b
			// fx(1) - fx(0) = A - b - (-b) = A
			// fx(50)- fx(5) = 50A-b-(5A-B)=45A
			// (-fx(0)/(fx(1)-fx(0)))		

			// another idea is the find the symbol humn and add all operations on it to a stack while working bottom up
			// then applying the inverse of those operations by popping from the stack to the other side of the equation

			printf("Part 2: solve for humn.. %s\n", expression.c_str());

			/*
			* > main.py
			* from sympy import symbols, solve
			* 
			* y = symbols("humn")
			* expr = "{COPY PASTE}"
			* print(solve(expr, y))
			*/

			// could also be solved by applying the non humn side ops in reverse order
		}
	}
}
void problem22()
{
	enum class Cell
	{
		VOID = 0, EMPTY = 1, BLOCKED = 2
	};

	vector<Cell> grid;
	i64 width = 0;
	i64 height = 0;
	i64 x = -1;
	i64 y = -1;
	string moves = "";
	{
		vector<string> vec = StringSplit(TextFileRead("day22.txt"), "\n");
		width = vec[0].length();
		height = vec.size() - 2;
		grid.resize(width * height);
		for (i64 _y = 0; _y < height; _y++)
		{
			auto& s = vec[_y];
			for (i64 _x = 0; _x < width; _x++)
			{
				Cell c = Cell::VOID;
				char chr = _x < s.length() ? s[_x] : ' ';
				switch (chr)
				{
				case ' ':
					c = Cell::VOID;
					break;
				case '.':
					c = Cell::EMPTY;
					if (x < 0 || y < 0) { x = _x; y = _y; }
					break;
				case '#':
					c = Cell::BLOCKED;
					break;
				}
				grid[_x + _y * width] = c;
			}
		}
		moves = vec[vec.size() - 1];
	}

	i64 dx = 1;
	i64 dy = 0;
	i64 rotation = 0;
	constexpr auto turn = [](i64& rotation, i64& dx, i64& dy, const i8 c) 
	{
		dx = 0; dy = 0;
		i64 d_rot = 0;
		if (c == 'L') d_rot = -1; else if (c == 'R') d_rot = 1;
		rotation = nmod(rotation + d_rot, 4ll);
		i8 facing = ' ';
		switch (rotation)
		{
		case 3:
			// upwards
			dy = -1;
			facing = '^';
			break;
		case 0:
			// right
			dx = 1;
			facing = '>';
			break;
		case 1:
			// downwards
			dy = 1;
			facing = 'v';
			break;
		case 2:
			// left
			dx = -1;
			facing = '<';
			break;
		}
		//printf("Facing %c %lld\n", facing, d_rot);
	};
	constexpr auto between = [](const i64 a, const i64 b, const i64 c) { return a >= b && a < c; };
	const auto redirect = [width, height](i64& rotation, i64& dx, i64& dy, i64& x, i64& y) 
	{
		i64 __dx = dx;
		i64 __dy = dy;
		i64 __x = x;
		i64 __y = y;
		i64 __rot = rotation;
		i64 _turn = -1;
		// hard coding this because it seems easier
		// https://imgur.com/a/nSZNgkm
		// 
		// 1
		// v green top left to bottom left
		if (between(x, 50, 100) && y == height - 1 && dy < 0) { i64 _x = 0; y = x + 100; x = _x; rotation = 0; _turn = 0; }
		// v green bottom left to top left
		else if (between(y, 150, 200) && x == width - 1 && dx < 0) { i64 _y = 0; x = y - 150 + 50; y = _y; rotation = 1; _turn = 1; }

		// 2
		// v yellow top left to bottom left
		else if (between(y, 0, 50) && x == 49 && dx < 0) { x = 0; y = 149 - y; rotation = 0; _turn = 2; }
		// v yellow bottom left to top left
		else if (between(y, 100, 150) && x == width - 1 && dx < 0) { x = 50; y = 149 - y; rotation = 0; _turn = 3; }

		// 3
		// v cyan top left to cyan top left
		else if (between(y, 50, 100) && x == 49 && dx < 0) { i64 _y = 100; x = y - 50; y = _y; rotation = 1; _turn = 4; }
		// v cyan top left to cyan top left
		else if (between(x, 0, 50) && y == 99 && dy < 0) { i64 _x = 50; y = x + 50; x = _x; rotation = 0; _turn = 5; }

		// 4
		// v pink top right to pink bottom left
		else if (between(x, 100, 150) && y == height - 1 && dy < 0) { x = x - 100; _turn = 6; }
		// v pink bottom left to pink top right
		else if (between(x, 0, 50) && y == 0 && dy > 0) { x = x + 100; _turn = 7; }

		// 5
		// v orange bottom left to orange bottom left
		else if (between(y, 150, 200) && x == 50 && dx > 0) { i64 _y = 149; x = y - 100; y = _y; rotation = 3; _turn = 8;	}
		// v orange bottom left to orange bottom left
		else if (between(x, 50, 100) && y == 150 && dy > 0) { i64 _x = 49; y = x + 100; x = _x; rotation = 2; _turn = 9;	}

		// 6
		// v purple bottom right to purple top right
		else if (between(y, 100, 150) && x == 100 && dx > 0) { x = 149; y = 149 - y; rotation = 2; _turn = 10; }
		// v purple top right to purple bottom right
		else if (between(y, 0, 50) && x == 0 && dx > 0) { x = 99; y = 149 - y; rotation = 2; _turn = 11; }

		// 7
		// v blue top right to blue top right
		else if (between(y, 50, 100) && x == 100 && dx > 0) { i64 _y = 49; x = y + 50; y = _y; rotation = 3; _turn = 12;	}
		// v blue top right to blue top right
		else if (between(x, 100, 150) && y == 50 && dy > 0) { i64 _x = 99; y = x - 50; x = _x; rotation = 2; _turn = 13;	}

		// set dx dy
		turn(rotation, dx, dy, ' ');
		// need to separate rotation and rotation offset due to 3d wrap around...
		i64 bp = 0;
	};
	const auto move = [width, height, grid, redirect](const i64 steps, i64& rotation, i64& dx, i64& dy, i64& x, i64& y)
	{
		for (i64 step = 0; step < steps; step++)
		{
			i64 next_x = nmod(x + dx, width);
			i64 next_y = nmod(y + dy, height);
			i64 next_rotation = rotation;
			i64 next_index = next_x + next_y * width;
			while (true)
			{
				Cell cell = grid[next_index];
				switch (cell)
				{
				case Cell::BLOCKED:
					//printf("Blocked\n");
					return;
				case Cell::EMPTY:
					x = next_x;
					y = next_y;
					rotation = next_rotation;
					//printf("Moved to %lld %lld\n", x + 1, y + 1);
					goto outer;
				case Cell::VOID:
					// part 1
					//{
					//	// keep walking until first non void cell
					//	next_x = nmod(next_x + dx, width);
					//	next_y = nmod(next_y + dy, height);
					//	next_index = next_x + next_y * width;
					//}
					{
						//next_x = nmod(next_x + dx, width);
						//next_y = nmod(next_y + dy, height);
						i64 _next_x = next_x;
						i64 _next_y = next_y;
						redirect(next_rotation, dx, dy, _next_x, _next_y);
						next_x = _next_x;
						next_y = _next_y;
						next_index = next_x + next_y * width;
					}
					break;
				}
			}
		outer: { }
		}
	};

	i64 cursor = 0;
	i64 next_rotation_cursor = cursor;
	while (cursor < moves.length())
	{
		std::size_t found_l = moves.find("L", cursor);
		std::size_t found_r = moves.find("R", cursor);
		bool no_turn = found_l == string::npos && found_r == string::npos;
		if (found_l == string::npos) found_l = moves.length();
		if (found_r == string::npos) found_r = moves.length();
		next_rotation_cursor = min({ found_l, found_r, moves.length()});
		i64 steps = 0;
		string_to<i64>(moves.substr(cursor, next_rotation_cursor - cursor), steps);
		// simulate steps
		move(steps, rotation, dx, dy, x, y);

		//printf("%lld %lld %lld %lld\n", rotation, x + 1, y + 1, (y + 1) * 1000 + (x + 1) * 4 + rotation);

		if (!no_turn)
		{
			i8 next_rotation = moves.substr(next_rotation_cursor, 1)[0];
			// simulate rotation
			turn(rotation, dx, dy, next_rotation);

			//printf("%lld %lld %lld %lld\n", rotation, x + 1, y + 1, (y + 1) * 1000 + (x + 1) * 4 + rotation);
		}
		else { break; }

		cursor = next_rotation_cursor + 1;
	}
	printf("R:%lld x:%lld y:%lld\n", rotation, x + 1, y + 1);
	printf("Answer: %lld\n", (y + 1) * 1000 + (x + 1) * 4 + rotation); //174140 too high should be 37415
}
namespace problem23
{
	struct State
	{
		Point p;
		Point next_p;
		i64 rotation = 0;
	};
	typedef unordered_map<Point, State, PointKeyHasher> StateMap;

	void problem23()
	{
		StateMap _states;
		{
			vector<string> vec = StringSplit(TextFileRead("day23.txt"), "\n");
			for (i64 y = 0; y < vec.size(); y++)
			{
				for (i64 x = 0; x < vec[0].length(); x++)
				{
					if (vec[y][x] == '#')
					{
						Point p = { x ,y };
						_states[p] = { p, p, 0};
					}
				}
			}
		}

		const Point offsets[12] = {
			 {-1, -1}, {0, -1}, {1, -1} ,
			 {-1, 1}, {0, 1}, {1, 1} ,
			 {-1, 1}, {-1, 0}, {-1, -1} ,
			 {1, 1}, {1, 0}, {1, -1} 
		};
		const auto kernel_indices = {0,1,2,3,4,5,7,10};
		const auto test_kernel = [kernel_indices, offsets](const StateMap& states, const Point p)
		{
			bool result = true;
			for (auto i : kernel_indices) {	Point offset = offsets[i]; Point _p = { p.x + offset.x, p.y + offset.y }; if (states.find(_p) != states.end()) { result = false; break; } }
			return result;
		};
		const auto test_points = [offsets](const StateMap& states, const Point p, const i64 rotation, Point& next_p) {
			Point offset1 = offsets[rotation * 3 + 0];
			Point offset2 = offsets[rotation * 3 + 1];
			Point offset3 = offsets[rotation * 3 + 2];
			Point p1 = { p.x + offset1.x, p.y + offset1.y };
			Point p2 = { p.x + offset2.x, p.y + offset2.y };
			Point p3 = { p.x + offset3.x, p.y + offset3.y };
			if (states.find(p1) == states.end() && states.find(p2) == states.end() && states.find(p3) == states.end())
			{
				next_p = p2;
				return true;
			}
			next_p = p;
			return false;
		};
		constexpr auto find_bounds = [](const StateMap& states, i64& min_x, i64& min_y, i64& max_x, i64& max_y) {
			for (auto& kvp : states)
			{
				Point p = kvp.second.p;
				min_x = min(min_x, p.x); min_y = min(min_y, p.y); max_x = max(max_x, p.x); max_y = max(max_y, p.y);
			}
		};
		constexpr auto count_empty = [](const StateMap& states, const i64 min_x, const i64 min_y, const i64 max_x, const i64 max_y) {
			i64 result = 0;
			for (i64 y = min_y; y <= max_y; y++)
			{
				for (i64 x = min_x; x <= max_x; x++)
				{
					Point p = { x, y };
					if (states.find(p) != states.end()) { }
					else { result++; }
				}
			}
			return result;
		};
		const auto print_states_map = [test_kernel](const StateMap& states, bool test = false)
		{
			i64 min_x = 0, min_y = 0, max_x = 8, max_y = 8;
			find_bounds(states, min_x, min_y, max_x, max_y);

			for (i64 y = min_y; y <= max_y; y++)
			{
				string s = "";
				for (i64 x = min_x; x <= max_x; x++)
				{
					Point p = { x, y };
					bool star = false;
					if (test) { star = test_kernel(states, p); }
					if (states.find(p) != states.end()) { if (star) s += "*"; else s += "#"; } else { s += "."; }
				}
				printf("%s\n", s.c_str());
			}
		};

		printf("round 0\n");
		print_states_map(_states);
		const i64 steps = 10;
		const auto parts = { 1ll, 2ll };
		bool no_moves = true;
		for (auto& part : parts)
		{
			i64 step = 0;
			StateMap states = _states;
			for (;; step++)
			{
				no_moves = true;
				if (part == 1 && step >= steps) break;
				unordered_map<Point, i64, PointKeyHasher> distinct_state_counter;
				for (auto& kvp : states)
				{
					if (!test_kernel(states, kvp.first))
					{
						kvp.second.next_p = kvp.second.p;
						for (i64 r_offset = 0; r_offset < 4; r_offset++)
						{
							i64 _rot = (kvp.second.rotation + r_offset) % 4;
							Point next_p;
							bool is_free = test_points(states, kvp.second.p, _rot, next_p);
							if (is_free)
							{
								kvp.second.next_p = next_p;
								distinct_state_counter[next_p]++;
								break;
							}
						}
					}
				}

				StateMap next_states_map;
				for (auto& kvp : states)
				{
					State s = kvp.second;
					if (distinct_state_counter.find(kvp.second.next_p) != distinct_state_counter.end())
					{
						i64 count = distinct_state_counter[kvp.second.next_p];
						if (count == 1)
						{
							no_moves = false;
							s.p = s.next_p;
						}
					}
					s.next_p = s.p;
					s.rotation = (s.rotation + 1) % 4;
					next_states_map[s.p] = s;
				}

				states = next_states_map;
				if (part == 2 && no_moves) { step++; break; }
			}
			i64 result = 0;
			{
				i64 min_x = 10e9, min_y = 10e9, max_x = -10e9, max_y = -10e9;
				find_bounds(states, min_x, min_y, max_x, max_y);
				result = count_empty(states, min_x, min_y, max_x, max_y);

				printf("Last round %lld\n", step);
				print_states_map(states);
			}
			printf("Part %lld answer %lld after steps %lld\n", part, result, step);
			// part 2 should be 999
		}		
	}
}
namespace problem24
{
#define BFS 0
#if BFS
	struct State
	{
		Point pos;
		i64 t = 0;
	};
	struct StateKeyHasher
	{
		std::size_t operator()(const State& k) const
		{
			return simple_hash({ k.pos.x, k.pos.y, k.t });
		}
	};
	inline bool operator==(const State& lhs, const State& rhs) { return all_equal({ lhs.pos.x, lhs.pos.y, lhs.t }, { rhs.pos.x, rhs.pos.y, rhs.t }); }
#endif

	void problem24()
	{
		struct Blizzard
		{
			Point pos;
			i64 dx = 0, dy = 0;
		};
		i64 width = 0;
		i64 height = 0;
		vector<Blizzard> blizzards;
		vector<u64> walls;
		Point start;
		Point end;
		// Run BFS or per time step
		// Maybe use bitmasks to store the rows for fast intersection check? YES much faster than hashset
		// I tried to reduce number of states with time % lcm(width-2, height-2) which is the inner board dimensions but no positive performance impact was achieved.
		{
			vector<string> vec = StringSplit(TextFileRead("day24.txt"), "\n");
			width = vec.size();
			height = vec[0].size();
			walls.resize(height);
			for (i64 x = 0; x < width; x++)
			{
				auto& s = vec[x];
				for (i64 y = 0; y < height; y++)
				{
					Point p = { x, y };
					if (x == 0ll && s[y] == '.') start = p;
					if (x == width - 1ll && s[y] == '.') end = p;
					if (s[y] == '#')
					{
						u64 _wall = 1ll << x;
						walls[y] |= _wall;
					}
					Blizzard b;
					b.pos = p;
					if (s[y] == '<') { b.dy = -1ll; blizzards.push_back(b); }
					if (s[y] == '>') { b.dy = +1ll; blizzards.push_back(b); }
					if (s[y] == '^') { b.dx = -1ll; blizzards.push_back(b); }
					if (s[y] == 'v') { b.dx = +1ll; blizzards.push_back(b); }
				}
			}
		}
		constexpr auto build_rows = [](const vector<Blizzard>& blizzards, const i64 width, const i64 height, const i64 t)
		{
			vector<u64> bitmasks(height, 0ll);
			for (auto& b : blizzards)
			{
				Point p = b.pos;
				p.x = nmod(p.x + b.dx * t - 1, width - 2) + 1;
				p.y = nmod(p.y + b.dy * t - 1, height - 2) + 1;
				u64& row = bitmasks[p.y];
				row |= (1ll << p.x);
			}
			return bitmasks;
		};
		constexpr auto is_valid_position = [](const vector<u64>& blizzard_rows, const vector<u64>& walls, const i64 width, const i64 height, const Point pos)
		{
			i64 this_row = 1ull << pos.x;
			i64 env_row = blizzard_rows[pos.y];
			return (this_row & env_row) == 0;
		};
		vector<pair<Point, Point>> paths = vector<pair<Point, Point>>({
			{start, end},
			{end, start},
			{start, end}
			});
		for (auto& part : {1ll,2ll})
		{
			i64 t = 1;
			for (i64 i = 0; i < paths.size(); i++)
			{
				if (part == 1ll && i > 0) break;

				Timer timer;

				Point start = paths[i].first;
				Point end = paths[i].second;

#if !BFS
				// Considers each possible position at timestep t. Idea from reddit. My own implementation. Roughly 2x faster than BFS
				unordered_set<Point, PointKeyHasher> points;
				points.insert(start);
				while (points.find(end) == points.end())
				{
					auto bitmasks = build_rows(blizzards, width, height, t);
					unordered_set<Point, PointKeyHasher> next_points(points.size());
					for (auto& p : points)
					{
						// p is not in wall
						if (p == start || (Inbetween(p.x, 1, width - 2) && Inbetween(p.y, 1, height - 2)))
						{
							// p is not in blizzard
							if (is_valid_position(bitmasks, walls, width, height, p))
							{
								// add all neighbours for p including own spot
								next_points.insert(p);
								next_points.insert({ p.x + 1,p.y });
								next_points.insert({ p.x - 1,p.y });
								next_points.insert({ p.x,	p.y + 1 });
								next_points.insert({ p.x,	p.y - 1 });
							}
						}
					}
					points = next_points;
					t++;
				}
#else
				// Naive BFS traversal. My own idea and implementation
				unordered_set<State, StateKeyHasher> seen;
				unordered_map<i64, vector<u64>> time_bitmasks_map;
				queue<State> q;
				q.push({ start, t });
				while (!q.empty())
				{
					State s = q.front(); q.pop();
					auto& p = s.pos;
					if (s.pos == end) { break; }
					// s has not been seen before
					if (seen.find(s) == seen.end())
					{
						seen.insert(s);
						// p is not in wall
						if (p == start || (Inbetween(p.x, 1, width - 2) && Inbetween(p.y, 1, height - 2)))
						{
							if (time_bitmasks_map.find(s.t) == time_bitmasks_map.end()) time_bitmasks_map[s.t] = build_rows(blizzards, width, height, s.t);
							auto& bitmasks = time_bitmasks_map[s.t];
							bool valid = is_valid_position(bitmasks, walls, width, height, s.pos);
							// p is not in blizzard
							if (valid)
							{
								// add all neighbours for p including own spot
								q.push({ {s.pos.x + 1,	s.pos.y		}, s.t + 1 });
								q.push({ {s.pos.x - 1,	s.pos.y		}, s.t + 1 });
								q.push({ {s.pos.x,		s.pos.y + 1	}, s.t + 1 });
								q.push({ {s.pos.x,		s.pos.y - 1	}, s.t + 1 });
								q.push({ {s.pos.x, s.pos.y}, s.t + 1 });
								t = s.t;
							}
						}
					}
				}
#endif
				printf("Part %lld path %lld found for %lld steps in %fs\n", part, i, t, timer.elapsed());
			}
		}
	}
#undef BFS
}
namespace problem25
{
	const string digits = "=-012";
	i64 from_snafu(const string& s)
	{
		if (s == "") return 0;
		i64 digit = (find(digits.begin(), digits.end(), s[s.size() - 1]) - digits.begin()) - 2;
		return from_snafu(s.substr(0, s.size() - 1)) * 5 + digit;
	}

	string to_snafu(i64 num)
	{
		if (num)
		{
			i64 q = (num + 2ll) / 5ll;
			i64 remainder = (num + 2ll) % 5;
			return to_snafu(q) + digits[remainder];
		}
		return "";
	}

	void problem25()
	{
		i64 sum = 0;
		{
			vector<string> vec = StringSplit(TextFileRead("day25.txt"), "\n");
			for (auto& s : vec)
			{
				i64 snaf = from_snafu(s);
				string ssnaf = to_snafu(snaf);
				printf("%s \t\t %lld \t\t %s\n", s.c_str(), snaf, ssnaf.c_str());
				sum += snaf;
			}
		}
		printf("SNAFU sum \t %lld \t\t%s\n", sum, to_snafu(sum).c_str());
	}
}
int main()
{
	problem16::problem16();
	return 0;
}