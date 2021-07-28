#include <ctime>
#include <iostream>
#include <math.h>
#include "crossword_generator.h"

int CrosswordGenerator::grid_size;
int CrosswordGenerator::uplen;

const int M = 35;
vector<vector<char>> CrosswordGenerator::grid;
vector<pair<int, int>> CrosswordGenerator::moves;
vector<vector<string>> CrosswordGenerator::bag;
vector<long long int> dist;
vector<long long int> fac;

void CrosswordGenerator::init()
{
	moves = vector<pair<int, int>>({{0, 1}, {1, 0}, {0, -1}, {-1, 0}});
	grid.resize(M, vector<char>(M, '#'));
	dist.resize(M);
	fac.resize(M);
	bag = vector<vector<string>>({{},
								  {},
								  {},
								  {"act", "add", "age", "ago", "air", "all", "and", "any", "are", "arm", "art", "ask", "bad", "bag", "bar", "bed", "big", "bit", "box", "boy", "but", "buy", "bye", "can", "car", "cup", "cut", "dad", "day", "did", "die", "dog", "eat", "end", "eye", "far", "few", "fly", "for", "fun", "gas", "get", "god", "got", "gun", "guy", "had", "has", "hen", "her", "hey", "him", "his", "hit", "hot", "how", "its", "job", "key", "kid", "law", "lay", "leg", "let", "lie", "lot", "low", "man", "may", "men", "met", "mom", "mrs", "new", "nor", "not", "now", "nun", "off", "oft", "oil", "old", "one", "our", "out", "own", "pay", "per", "put", "red", "run", "saw", "say", "sea", "see", "set", "hex", "she", "sir", "sit", "six", "son", "tax", "ten", "the", "too", "top", "try", "two", "use", "war", "was", "way", "who", "why", "win", "yes", "yet", "you"},
								  {"also", "area", "away", "baby", "back", "ball", "bank", "base", "beat", "best", "bill", "blue", "body", "book", "born", "both", "call", "card", "care", "case", "cell", "city", "cold", "come", "cost", "dark", "data", "dead", "deal", "deep", "door", "down", "draw", "drop", "drug", "each", "east", "easy", "edge", "else", "even", "ever", "face", "fact", "fail", "fall", "fast", "fear", "feel", "fill", "film", "find", "fine", "fire", "firm", "fish", "five", "food", "foot", "form", "four", "free", "from", "full", "fund", "game", "girl", "give", "goal", "good", "grow", "hair", "half", "hand", "hang", "hard", "have", "head", "hear", "heat", "help", "here", "high", "hold", "home", "hope", "hour", "huge", "idea", "into", "item", "join", "just", "keep", "kill", "kind", "know", "land", "last", "late", "lead", "left", "less", "life", "like", "line", "list", "live", "long", "look", "lose", "loss", "love", "main", "make", "many", "mean", "meet", "mind", "mint", "miss", "more", "most", "move", "much", "must", "name", "near", "need", "news", "next", "nice", "none", "note", "once", "only", "onto", "open", "over", "page", "pain", "part", "pass", "past", "pick", "plan", "play", "poor", "pull", "push", "race", "rate", "read", "real", "rest", "rich", "rise", "risk", "road", "rock", "role", "room", "rule", "safe", "same", "save", "seat", "seek", "seem", "sell", "send", "shot", "show", "side", "sign", "sing", "site", "size", "skin", "some", "song", "soon", "sort", "star", "stay", "step", "stop", "such", "sure", "take", "talk", "task", "team", "tell", "tend", "term", "test", "than", "that", "them", "then", "they", "this", "thus", "time", "town", "tree", "trip", "true", "turn", "type", "unit", "upon", "very", "view", "vote", "wait", "walk", "wall", "want", "wear", "week", "well", "west", "what", "when", "whom", "wide", "wife", "will", "wind", "wish", "with", "word", "work", "yard", "yeah", "year", "your"},
								  {"above", "admit", "adult", "after", "again", "agent", "agree", "ahead", "allow", "alone", "along", "among", "apply", "argue", "avoid", "batch", "begin", "black", "blood", "board", "break", "bring", "build", "carry", "catch", "cause", "chair", "check", "child", "civil", "claim", "class", "clear", "close", "coach", "color", "could", "court", "cover", "crime", "death", "dream", "drive", "early", "eight", "enjoy", "enter", "event", "every", "exist", "field", "fight", "final", "first", "floor", "focus", "force", "front", "glass", "great", "green", "group", "guess", "happy", "heart", "heavy", "hotel", "house", "human", "image", "issue", "large", "later", "laugh", "learn", "least", "leave", "legal", "level", "light", "local", "major", "maybe", "media", "might", "model", "money", "month", "mouth", "movie", "music", "never", "night", "north", "occur", "offer", "often", "order", "other", "owner", "paper", "party", "peace", "phone", "piece", "place", "plant", "point", "power", "price", "prove", "quilt", "quite", "radio", "raise", "range", "reach", "ready", "right", "scene", "score", "sense", "serve", "seven", "shake", "share", "shoot", "short", "since", "skill", "small", "smile", "sound", "south", "speak", "spend", "sport", "staff", "stage", "stand", "start", "state", "still", "stock", "store", "story", "study", "stuff", "style", "table", "teach", "thank", "their", "there", "these", "thing", "think", "third", "those", "three", "throw", "today", "total", "tough", "trade", "treat", "trial", "truth", "under", "until", "value", "visit", "voice", "watch", "water", "where", "which", "while", "white", "whole", "whose", "woman", "world", "worry", "would", "write", "wrong", "young"},
								  {"across", "action", "affect", "agency", "almost", "always", "amount", "animal", "answer", "anyone", "appear", "around", "arrive", "artist", "assume", "attack", "author", "become", "before", "behind", "better", "beyond", "bright", "budget", "camera", "cancer", "career", "center", "chance", "change", "charge", "choice", "choose", "church", "common", "couple", "course", "create", "debate", "decade", "decide", "degree", "design", "detail", "dinner", "doctor", "during", "effect", "effort", "either", "energy", "enough", "entire", "expect", "expert", "factor", "family", "father", "figure", "finger", "finish", "follow", "forget", "former", "friend", "future", "garden", "grease", "ground", "growth", "happen", "health", "height", "impact", "indeed", "inside", "itself", "lawyer", "leader", "letter", "likely", "listen", "little", "manage", "market", "matter", "member", "memory", "method", "middle", "minute", "modern", "moment", "mother", "myself", "nation", "nature", "nearly", "notice", "number", "office", "option", "others", "parent", "people", "period", "person", "player", "police", "policy", "pretty", "public", "rather", "really", "reason", "recent", "record", "reduce", "region", "relate", "remain", "remove", "report", "result", "return", "reveal", "school", "season", "second", "senior", "series", "annual", "should", "simple", "simply", "single", "sister", "social", "source", "speech", "spring", "street", "strong", "suffer", "summer", "system", "theory", "though", "threat", "toward", "travel", "victim", "weapon", "weight", "window", "within", "wonder", "worker", "writer"},
								  {"account", "address", "against", "already", "another", "article", "because", "believe", "benefit", "between", "billion", "brother", "capital", "central", "century", "certain", "channel", "citizen", "clearly", "college", "company", "compare", "concern", "contain", "control", "country", "culture", "current", "defense", "despite", "develop", "discuss", "disease", "economy", "evening", "exactly", "example", "explain", "federal", "feeling", "finally", "foreign", "forward", "general", "herself", "himself", "history", "however", "hundred", "husband", "imagine", "improve", "include", "instead", "involve", "january", "kitchen", "machine", "manager", "measure", "medical", "meeting", "mention", "message", "million", "mission", "morning", "natural", "network", "nothing", "officer", "outside", "partner", "patient", "pattern", "perform", "perhaps", "picture", "planner", "popular", "prepare", "present", "prevent", "private", "problem", "process", "produce", "product", "program", "project", "protect", "provide", "purpose", "quality", "quickly", "reality", "realize", "receive", "reflect", "require", "respond", "science", "section", "serious", "service", "several", "similar", "society", "soldier", "someone", "special", "station", "student", "subject", "success", "suggest", "support", "surface", "teacher", "thermal", "thought", "through", "tonight", "trouble", "usually", "various", "western", "whether", "without"},
								  {"Congress", "Democrat", "activity", "actually", "although", "analysis", "anything", "approach", "attorney", "audience", "behavior", "building", "business", "campaign", "computer", "consider", "consumer", "continue", "cultural", "customer", "daughter", "decision", "describe", "director", "discover", "division", "economic", "election", "employee", "everyone", "evidence", "exercise", "hospital", "identify", "increase", "indicate", "industry", "interest", "language", "magazine", "maintain", "majority", "marriage", "material", "military", "movement", "national", "official", "painting", "personal", "physical", "politics", "position", "positive", "possible", "practice", "pressure", "probably", "property", "question", "recently", "remember", "research", "resource", "response", "security", "shoulder", "somebody", "southern", "specific", "standard", "strategy", "suddenly", "thousand", "together", "training", "violence", "whatever", "yourself"},
								  {"agreement", "attention", "authority", "available", "beautiful", "candidate", "certainly", "challenge", "character", "community", "condition", "determine", "different", "difficult", "direction", "education", "establish", "everybody", "executive", "financial", "important", "interview", "knowledge", "necessary", "newspaper", "operation", "political", "president", "professor", "recognize", "religious", "represent", "scientist", "situation", "something", "sometimes", "statement", "structure", "treatment"},
								  {"adaptation", "collection", "commercial", "conference", "democratic", "difference", "discussion", "especially", "everything", "experience", "flamboyant", "generation", "government", "horizontal", "hypothesis", "individual", "investment", "management", "particular", "passionate", "population", "production", "skateboard", "successful", "technology", "television", "themselves", "throughout", "understand"},
								  {"environment", "information", "institution", "interesting", "opportunity", "participant", "performance", "significant", "traditional"}});
	uplen = sqrt(grid_size) + 3; //maximum length of words along one axis
	srand(time(NULL));
}
int CrosswordGenerator::random(int a, int b)
{
	return a + rand() % (b - a + 1);
}
void CrosswordGenerator::form_grid()
{
	int md = 1 << (uplen); //2^(max length of word)
	int step = 2;		   //stores how many rows we skipped last time
	int count = 1;		   //stores count of row with word

	vector<int> start(grid_size + 1, 0), end(grid_size + 1, 0), row_num(grid_size, 0);
	for (int i = 1; i <= grid_size; count++)
	{
		int len, val;
		//randomly choose length of word
		while (1)
		{
			val = rand() % (md) + 1;
			for (int j = 0; j <= uplen + 1; j++)
			{
				if (val <= dist[j])
				{
					len = j;
					break;
				}
			}
			if (len > 2 and len <= uplen)
			{
				break;
			}
		}
		if (count == 1)
		{
			if (len == grid_size)
				start[count] = 1;
			else
				start[count] = random(1, 2);
		}
		else if (count == 2)
		{
			if (len == grid_size)
				start[count] = 1;
			else
				start[count] = (grid_size - len + 1) - random(0, 1);
		}
		else
		{
			//assure some overlap of count with count - 2
			if (start[count - 2] <= grid_size / 2)
			{
				//it is left aligned
				start[count] = min(grid_size - len + 1, random(start[count - 2], end[count - 2]));
			}
			else
			{
				//it is right aligned
				end[count] = max(len, random(start[count - 2], end[count - 2]));
				start[count] = end[count] - len + 1;
			}
		}

		for (int j = start[count]; j < start[count] + len; j++)
			grid[i][j] = '.';

		//randomly step by 1 or 2 but don't step 2 consecutively 2 times
		if (step == 1)
		{
			step = 2;
		}
		else
		{
			step = random(1, 2);
		}
		row_num[count] = i;
		i += step;
		end[count] = start[count] + len - 1;
	}

	count = 1;
	for (;; count++)
	{
		if (start[count + 2] == 0)
			break;

		//choose column among some overlapping region
		int start_col = max(start[count], start[count + 2]), end_col = min(end[count], end[count + 2]), col = random(start_col, end_col), row = row_num[count];
		if (row >= 3)
			row -= rand() % 3;
		int len = 0;
		//connect them
		for (int j = row; j <= row_num[count + 2]; j++)
		{
			len++;
			grid[j][col] = '.';
		}
	}
}

void CrosswordGenerator::print_grid()
{
	for (int i = 1; i <= grid_size; i++)
	{
		for (int j = 1; j <= grid_size; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void CrosswordGenerator::transpose()
{
	for (int i = 1; i <= grid_size; i++)
	{
		for (int j = 1; j < i; j++)
		{
			swap(grid[i][j], grid[j][i]);
		}
	}
}

void CrosswordGenerator::remove2()
{
	for (int i = 1; i <= grid_size; i++)
	{
		for (int j = 1; j <= grid_size; j++)
		{
			if (grid[i][j] == '.' && grid[i + 1][j] == '.' && grid[i - 1][j] == '#' && grid[i + 2][j] == '#')
			{
				if (i != 1)
					grid[i - 1][j] = '.';
				else
					grid[i + 2][j] = '.';
			}
		}
	}
}
void CrosswordGenerator::remove1()
{
	for (int i = 1; i <= grid_size; i++)
	{
		for (int j = 1; j <= grid_size; j++)
		{
			int cur = 0;
			for (int k = 0; k < 4; k++)
			{
				if (grid[i + moves[k].first][j + moves[k].second] == '#')
					cur++;
			}
			if (cur == 4)
			{
				grid[i][j] = '#';
			}
		}
	}
}

void CrosswordGenerator::distribution() //Makes binomial distribution
{
	fac[0] = 1;
	for (int i = 1; i <= uplen; i++)
	{
		fac[i] = i * fac[i - 1];
	}
	dist[0] = 1;
	for (int i = 1; i <= uplen; i++)
	{
		dist[i] = fac[uplen] / (fac[i] * fac[uplen - i]) + dist[i - 1];
	}
}

void CrosswordGenerator::generate_crossword()
{
	init();
	distribution();
	form_grid();
	remove2();
	remove1();
	if (rand() % 2)
		transpose();
}