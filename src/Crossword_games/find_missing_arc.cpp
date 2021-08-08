#include <iostream>
#include "find_missing_arc.h"
#include "CSPify.h"
using namespace std;

FindMissingArc::FindMissingArc() {}
vector<pair<pair<pair<int, int>, char>, pair<pair<int, int>, char>>> FindMissingArc::get_arcs_to_display() const { return arcs_to_display; }
void FindMissingArc::choose_arc()
{
	int numofarcs = CSPify::q.size();
	int temp = rand() % numofarcs;
	int i = -1;
	for (auto cur : CSPify::q)
	{
		i++;
		if (i % 2 != temp % 2)
			continue;
		if (i != temp)
		{
			arcs_to_display.push_back({{cur.first.first, cur.first.second ? 'D' : 'A'}, {cur.second.first, cur.second.second ? 'D' : 'A'}});

			cout << cur.first.first.first;
			cout << "-";
			cout << cur.first.first.second;
			cout << "-";
			cout << (cur.first.second ? "D " : "A ");

			cout << cur.second.first.first;
			cout << "-";
			cout << cur.second.first.second;
			cout << "-";
			cout << (cur.second.second ? "D" : "A") << "\n";
		}
		else
			answer = {{cur.first.first, cur.first.second ? 'D' : 'A'}, {cur.second.first, cur.second.second ? 'D' : 'A'}};
	}
}
bool FindMissingArc::check(int fx, int fy, char fdir, int sx, int sy, char sdir)
{
	student_answer = {{{fx, fy}, fdir}, {{sx, sy}, sdir}};
	if (answer == student_answer)
		return 1;
	swap(student_answer.first, student_answer.second);
	if (answer == student_answer)
		return 1;
	return 0;
}

void FindMissingArc::startGame()
{
	cout << "Find the missing constraint for the above crossword grid :\n";
	choose_arc();
	int fx, fy, sx, sy;
	string fdir, sdir;
	cin >> fx >> fy >> fdir >> sx >> sy >> sdir;
	bool result = check(fx, fy, fdir[0], sx, sy, sdir[0]);
	if (result)
		cout << "CORRECT\n";
	else
	{
		cout << "WRONG\nAns: ";
		cout << answer.first.first.first << "-" << answer.first.first.second << "-" << answer.first.second << " ";
		cout << answer.second.first.first << "-" << answer.second.first.second << "-" << answer.second.second << "\n";
	}
}
